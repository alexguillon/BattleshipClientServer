#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{

    printf("Le serveur a crashé ou un joueur s'est déconnecté.\n Fin du jeu.\n");

    exit(0);
}
void write_server_square(int sockfd, char buffer[2])
{
    int n = write(sockfd, buffer, 2);
    if (n < 0)
        error("Erreur");
}
void write_server_data(int sockfd, int tab[10][10])
{
    int n = write(sockfd, tab, 100*sizeof(int));
    if (n < 0)
        error("Erreur");
}
void draw_legends(){
  printf("LEGENDES :\n");
  printf("__________\n");
  printf(" - \033[43mPorte Avion\033[0m\n");
  printf(" - \033[46mSous Marin\033[0m\n");
  printf(" - \033[41mTorpilleur\033[0m\n");
  printf("__________ \n");
}
void draw_grid(int grid[10][10]){
  char data[10][10][30];
  for(int i=0;i<10;i++){
  for(int j=0;j<10;j++){
    char str[30];
    if(grid[i][j]==0){
      strcpy(str," ");
      strcpy(data[i][j],str);
    }
    else if(grid[i][j]==1){
      strcpy(str,"\033[41mX\033[0m");
      strcpy(data[i][j],str);
    }
    else if(grid[i][j]==2 || grid[i][j]==3){
      strcpy(str,"\033[46mX\033[0m");
        strcpy(data[i][j],str);
    }
    else if(grid[i][j]==4){
      strcpy(str,"\033[43mX\033[0m");
      strcpy(data[i][j],str);
    }
  }
 }
  // Now str contains the integer as characters
  printf("    A | B | C | D | E | F | G | H | I | J | \n");
  printf("   -------------------------------------------\n");
  printf("0 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[0][0], data[0][1], data[0][2], data[0][3], data[0][4], data[0][5], data[0][6], data[0][7], data[0][8], data[0][9]);
  printf("   -------------------------------------------\n");
  printf("1 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[1][0], data[1][1], data[1][2], data[1][3], data[1][4], data[1][5], data[1][6], data[1][7], data[1][8], data[1][9]);
  printf("   -------------------------------------------\n");
  printf("2 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[2][0], data[2][1], data[2][2], data[2][3], data[2][4], data[2][5], data[2][6], data[2][7], data[2][8], data[2][9]);
  printf("   -------------------------------------------\n");
  printf("3 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[3][0], data[3][1], data[3][2], data[3][3], data[3][4], data[3][5], data[3][6], data[3][7], data[3][8], data[3][9]);
  printf("   -------------------------------------------\n");
  printf("4 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[4][0], data[4][1], data[4][2], data[4][3], data[4][4], data[4][5], data[4][6], data[4][7], data[4][8], data[4][9]);
  printf("   -------------------------------------------\n");
  printf("5 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[5][0], data[5][1], data[5][2], data[5][3], data[5][4], data[5][5], data[5][6], data[5][7], data[5][8], data[5][9]);
  printf("   -------------------------------------------\n");
  printf("6 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[6][0], data[6][1], data[6][2], data[6][3], data[6][4], data[6][5], data[6][6], data[6][7], data[6][8], data[6][9]);
  printf("   -------------------------------------------\n");
  printf("7 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[7][0], data[7][1], data[7][2], data[7][3], data[7][4], data[7][5], data[7][6], data[7][7], data[7][8], data[7][9]);
  printf("   -------------------------------------------\n");
  printf("8 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[8][0], data[8][1], data[8][2], data[8][3], data[8][4], data[8][5], data[8][6], data[8][7], data[8][8], data[8][9]);
  printf("   -------------------------------------------\n");
  printf("9 | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n", data[9][0], data[9][1], data[9][2], data[9][3], data[9][4], data[9][5], data[9][6], data[9][7], data[9][8], data[9][9]);


}

int contains(char c,char tab[10]){
    for(int i=0;i<10;i++){
        if(c==tab[i])
            return 1;
    }
    return 0;
}
int getNumberInTab(char c, char tab[10]){
    if(c=='0')
        return 0;
    for(int i=0;i<10;i++){
        if(c==tab[i])
            return i;
    }
    return -1;
}

void fill_data(int sockfd){


 int grid_player[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            grid_player[i][j]=0;
        }
    }
    printf("Pour commencer, veuillez placer votre torpilleur (2 cases).\n");
    draw_grid(grid_player);
    printf("Choisissez les deux cases que vous voulez remplir (par exemple 0D-0E ou 4C-5C).\n");
    char lettres[10]={'A','B','C','D','E','F','G','H','I','J'};
    char nombres[10]={'0','1','2','3','4','5','6','7','8','9'};
    char placementTorpilleur[5];
    int placementTorpilleurCorrect=0;
    while(placementTorpilleurCorrect==0){
        scanf("%s",placementTorpilleur);
    if(strlen(placementTorpilleur)==5){
        int check;
        if(placementTorpilleur[0]=='0')
            check=1;
        else
            check=contains(placementTorpilleur[0],nombres);


        if(placementTorpilleur[0]==placementTorpilleur[3] && check==1){
            int check2=contains(placementTorpilleur[1],lettres);
            if(check2==1){
                int placement1=getNumberInTab(placementTorpilleur[1],lettres);
                int placement2=getNumberInTab(placementTorpilleur[4],lettres);
               int line = placementTorpilleur[0]-'0';
                if(placement1==(placement2+1)|| placement1==(placement2-1)){
                    placementTorpilleurCorrect=1;
                    grid_player[line][placement1]=1;
                    grid_player[line][placement2]=1;
                }
            }
        }
        if(placementTorpilleur[1]==placementTorpilleur[4] && check==1){
              int check3=contains(placementTorpilleur[1],lettres);
              if(check3==1){
                int placement3=getNumberInTab(placementTorpilleur[0],nombres);
                int placement4=getNumberInTab(placementTorpilleur[3],nombres);
                int column = getNumberInTab(placementTorpilleur[1],lettres);
                if(placement3==(placement4+1)|| placement3==(placement4-1)){
                    placementTorpilleurCorrect=1;
                    grid_player[placement3][column]=1;
                    grid_player[placement4][column]=1;
                }
              }
        }
    }
        if(placementTorpilleurCorrect==0)
            printf("Mauvais placement du torpilleur. Veuillez réessayer.\n");
    }
    printf("Le \033[41mTorpilleur\033[0m a bien été placé.\n");
    draw_grid(grid_player);

    int attenteSousMarins=0;

    while(attenteSousMarins<2){
        if(attenteSousMarins==0){
            printf("Bien maintenant nous allons placer ensemble votre premier sous marin (3 cases).\n");
        }else if(attenteSousMarins==1){
            printf("Parfait ! Plaçons désormais votre deuxième sous marin (3 cases).\n");
        }
    printf("Choisissez les trois cases que vous voulez remplir (par exemple 4H-4I-4J ou 1E-2E-3E).\n");
    char placementSousMarin[8];
    int placementSousMarinCorrect=0;
     while(placementSousMarinCorrect==0){
        scanf("%s",placementSousMarin);
    if(strlen(placementSousMarin)==8){
        int check;
        if(placementSousMarin[0]=='0')
            check=1;
        else
            check=contains(placementSousMarin[0],nombres);
        if(placementSousMarin[0]==placementSousMarin[3] && placementSousMarin[3]==placementSousMarin[6] && check==1){
            int check2=contains(placementSousMarin[1],lettres);
            if(check2==1){
                int placement1=getNumberInTab(placementSousMarin[1],lettres);
                int placement2=getNumberInTab(placementSousMarin[4],lettres);
                int placement3=getNumberInTab(placementSousMarin[7],lettres);
                int line = placementSousMarin[0]-'0';
                if(((placement1==(placement2+1) && placement2==(placement3+1)) || (placement1==(placement2-1)) && placement2==(placement3-1)) && grid_player[line][placement1]==0 && grid_player[line][placement2]==0 && grid_player[line][placement3]==0){
                    placementSousMarinCorrect=1;
                    int firstSM=2;
                    int secondSM=3;
                    int value;
                    if(attenteSousMarins==0)
                        value=2;
                    else
                        value=3;
                    grid_player[line][placement1]=value;
                    grid_player[line][placement2]=value;
                    grid_player[line][placement3]=value;
                    attenteSousMarins++;
                }
            }
        }else if( placementSousMarin[1]== placementSousMarin[4] && placementSousMarin[4]== placementSousMarin[7]){
              int check3=contains(placementSousMarin[1],lettres);
              if(check3==1){
                int placement4=getNumberInTab(placementSousMarin[0],nombres);
                int placement5=getNumberInTab(placementSousMarin[3],nombres);
                int placement6=getNumberInTab(placementSousMarin[6],nombres);
                int column = getNumberInTab(placementSousMarin[1],lettres);
                if(((placement4==(placement5+1)&&placement5==(placement6+1)) || (placement4==(placement5-1)&& placement5==(placement6-1))) && grid_player[placement4][column]==0 && grid_player[placement5][column]==0 && grid_player[placement6][column]==0){
                    placementSousMarinCorrect=1;
                    int firstSM=2;
                    int secondSM=3;
                    int value;
                    if(attenteSousMarins==0)
                        value=2;
                    else
                        value=3;
                    grid_player[placement4][column]=value;
                    grid_player[placement5][column]=value;
                    grid_player[placement6][column]=value;
                    attenteSousMarins++;
                }
              }
        }
    }
        if(placementSousMarinCorrect==0)
            printf("Mauvais placement du sous marin. Veuillez réessayer.\n");
    }
    if(attenteSousMarins==1){
        printf("Le premier \033[46mSous Marin\033[0m a bien été placé.\n");
        draw_grid(grid_player);
    }
  }
    printf("Les \033[46mSous Marins\033[0m ont bien été placés.\n");
    draw_grid(grid_player);

   printf("Parfait ! Finissons cette étape en plaçant votre porte avion ! (4 cases).\n");
   printf("Choisissez les trois cases que vous voulez remplir (par exemple 6B-6C-6D-6E ou 0J-1J-2J-3J).\n");

    char placementPorteAvion[11];
    int placementPorteAvionCorrect=0;
    while(placementPorteAvionCorrect==0){
        scanf("%s",placementPorteAvion);
    if(strlen(placementPorteAvion)==11){
       int check;
        if(placementPorteAvion[0]=='0')
            check=1;
        else
            check=contains(placementPorteAvion[0],nombres);
        if(placementPorteAvion[0]==placementPorteAvion[3] && placementPorteAvion[3]==placementPorteAvion[6] && placementPorteAvion[6]==placementPorteAvion[9] && check==1){
            int check2=contains(placementPorteAvion[1],lettres);
            if(check2==1){
                int placement1=getNumberInTab(placementPorteAvion[1],lettres);
                int placement2=getNumberInTab(placementPorteAvion[4],lettres);
                int placement3=getNumberInTab(placementPorteAvion[7],lettres);
                int placement4=getNumberInTab(placementPorteAvion[10],lettres);
                int line = placementPorteAvion[0]-'0';
                if(((placement1==(placement2+1) && placement2==(placement3+1) && placement3==(placement4+1)) || (placement1==(placement2-1)) && placement2==(placement3-1)&& placement3==(placement4-1)) && grid_player[line][placement1]==0 && grid_player[line][placement2]==0 && grid_player[line][placement3]==0 && grid_player[line][placement4]==0){
                    placementPorteAvionCorrect=1;
                    grid_player[line][placement1]=4;
                    grid_player[line][placement2]=4;
                    grid_player[line][placement3]=4;
                    grid_player[line][placement4]=4;
                }
            }
        }else if( placementPorteAvion[1]== placementPorteAvion[4] && placementPorteAvion[4]== placementPorteAvion[7] && placementPorteAvion[7]== placementPorteAvion[10]){
              int check3=contains(placementPorteAvion[1],lettres);
              if(check3==1){
                int placement4=getNumberInTab(placementPorteAvion[0],nombres);
                int placement5=getNumberInTab(placementPorteAvion[3],nombres);
                int placement6=getNumberInTab(placementPorteAvion[6],nombres);
                int placement7=getNumberInTab(placementPorteAvion[9],nombres);
                int column = getNumberInTab(placementPorteAvion[1],lettres);
                if(((placement4==(placement5+1)&&placement5==(placement6+1)&&placement6==(placement7+1)) || (placement4==(placement5-1)&& placement5==(placement6-1)&& placement6==(placement7-1))) && grid_player[placement4][column]==0 && grid_player[placement5][column]==0 && grid_player[placement6][column]==0 && grid_player[placement7][column]==0){
                    placementPorteAvionCorrect=1;
                    grid_player[placement4][column]=4;
                    grid_player[placement5][column]=4;
                    grid_player[placement6][column]=4;
                    grid_player[placement7][column]=4;
                }
              }
        }
    }
        if(placementPorteAvionCorrect==0)
            printf("Mauvais placement du porte avion. Veuillez réessayer.\n");
  }
    printf("Le \033[43mPorte Avion\033[0m a bien été placé.\n");

    printf("Parfait ! Votre grille a bien été remplie.\n");
  write_server_data(sockfd,grid_player);
  draw_legends();
  draw_grid(grid_player);
}
/*
 * Socket Read Functions
 */

/* Reads a message from the server socket. */
void recv_msg(int sockfd, char * msg)
{
    /* All messages are 3 bytes. */
    memset(msg, 0, 4);
    int n = read(sockfd, msg, 3);

    if (n < 0 || n != 3) /* Not what we were expecting. Server got killed or the other client disconnected. */
        error("Erreur");


}

/* Reads an int from the server socket. */
int recv_int(int sockfd)
{
    int msg = 0;
    int n = read(sockfd, &msg, sizeof(int));

    if (n < 0 || n != sizeof(int))
        error("Erreur");



    return msg;
}

/*
 * Socket Write Functions
 */
 void write_server_msg(int cli_sockfd, char * msg)
 {
     int n = write(cli_sockfd, msg, strlen(msg));
     if (n < 0)
         error("Erreur");
 }
/* Writes an int to the server socket. */
void write_server_int(int sockfd, int msg)
{
    int n = write(sockfd, &msg, sizeof(int));
    if (n < 0)
        error("Erreur");


}

/*
 * Connect Functions
 */

/* Sets up the connection to the server. */
int connect_to_server(char * hostname, int portno)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Get a socket. */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("Erreur");

    /* Get the address of the server. */
    server = gethostbyname(hostname);

    if (server == NULL) {
        printf("Erreur, serveur injoignable.\n");
        exit(0);
    }

	/* Zero out memory for server info. */
	memset(&serv_addr, 0, sizeof(serv_addr));

	/* Set up the server info. */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);

	/* Make the connection. */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting to server");



    return sockfd;
}
int check_square(char * data){
  int nbr=data[0]-'0';
  if(nbr>=0 && nbr<=9 && data[1]>='A' && data[1]<='J')
    return 1;
  return 0;
}

void take_turn(int sockfd)
{
    char buffer[2];
    int valid;
    while (1) { /* Ask until we receive. */
        printf("Entrez une case (par exemple 4B)\n");
	      scanf("%s",buffer);
        valid = check_square(buffer);
        if (valid==1){
            printf("\n");
            write_server_square(sockfd, buffer);
            break;
        }
        else
            printf("\n Format de case invalide. Veuillez réessayer.\n");
    }
    printf("ok\n");
}

int main(int argc, char *argv[])
{
    /* Make sure host and port are specified. */
    if (argc < 3) {
       printf("Utilisation du port %s\n", argv[0]);
       exit(0);
    }

    /* Connect to the server. */
    int sockfd = connect_to_server(argv[1], atoi(argv[2]));

    /* The client ID is the first thing we receive after connecting. */
    int id = recv_int(sockfd);



    char msg[4];


    printf("La bataille navale - Par Lilian Jude et Alexandre Guillon\n");

    /* Wait for the game to start. */
    do {
        recv_msg(sockfd, msg);
        if (!strcmp(msg, "HLD"))
            printf("En attente d'un second joueur...\n");
    } while ( strcmp(msg, "SRT") );

    while(1) {
          recv_msg(sockfd, msg);
          if (!strcmp(msg, "FIG")) { /* Take a turn. */
  	        printf("Remplissez votre grille...\n");
  	        fill_data(sockfd);
          }
          else if (!strcmp(msg, "WFG")) { /* Move was invalid. Note that a "TRN" message will always follow an "INV" message, so we will end up at the above case in the next iteration. */
              printf("Votre adversaire remplit sa grille.\n");
          }
          else if (!strcmp(msg, "STP")) { /* Move was invalid. Note that a "TRN" message will always follow an "INV" message, so we will end up at the above case in the next iteration. */
              printf("\n LE JEU COMMENCE ! \n");
          }
          else if (!strcmp(msg, "NTR")) { /* Move was invalid. Note that a "TRN" message will always follow an "INV" message, so we will end up at the above case in the next iteration. */
              printf("\n Votre adversaire est en train de jouer. \n");
          }
          else if (!strcmp(msg, "TRN")) { /* Move was invalid. Note that a "TRN" message will always follow an "INV" message, so we will end up at the above case in the next iteration. */
              printf("\n A votre tour ! \n");
              take_turn(sockfd);
          }
        }
      close(sockfd);
      return 0;
}
