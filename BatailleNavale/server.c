#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int player_count = 0;
pthread_mutex_t mutexcount;
int MYPORT = 4321;

int grille_joueur1_placement[10][10];
int grille_joueur2_placement[10][10];
int grille_joueur1_game[10][10];
int grille_joueur2_game[10][10];
int turn = 0;
int prev_turn=1;

void error(const char *msg)
{
    perror(msg);
    pthread_exit(NULL);
}

void write_client_data(int sockfd, int tab[10][10])
{
    int n = write(sockfd, tab, 100*sizeof(int));
    if (n < 0)
        error("Erreur");
}
void draw_grid_game(int grid[10][10]) {
	char data[10][10][30];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			char str[30];
			if (grid[i][j] == 0) {
				strcpy(str, " ");
				strcpy(data[i][j], str);
			}
			else if (grid[i][j] == 1) {
				strcpy(str, "\033[42mO\033[0m");
				strcpy(data[i][j], str);
			}
			else if (grid[i][j] == 2) {
				strcpy(str, "\033[41mX\033[0m");
				strcpy(data[i][j], str);
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

void draw_grid_placement(int grid[10][10]){
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
 void recv_msg(int sockfd, char * msg)
 {
     /* All messages are 3 bytes. */
     memset(msg, 0, 4);
     int n = read(sockfd, msg, 3);

     if (n < 0 || n != 3) /* Not what we were expecting. Server got killed or the other client disconnected. */
         error("ERROR reading message from server socket.");
 }

/* Reads an int from a client socket. */
void recv_grid(int src[10][10], int cli_sockfd,int player)
{
    int msg[10][10];
    int n = read(cli_sockfd, msg, 100*sizeof(int));
    /*for(int i=0;i<10;i++){
      for(int j=0;j<10;j++)
        printf("(%i, %i) = %i \n",i,j,msg[i][j]);
    }*/
    memcpy(src, msg, 100*sizeof(int));
    printf("------------------GRILLE DU JOUEUR %i------------------------\n",player);
    draw_grid_placement(src);
}

void recv_grid_game(int src[10][10], int cli_sockfd,int player)
{
    int msg[10][10];
    int n = read(cli_sockfd, msg, 100*sizeof(int));
    /*for(int i=0;i<10;i++){
      for(int j=0;j<10;j++)
        printf("(%i, %i) = %i \n",i,j,msg[i][j]);
    }*/
    memcpy(src, msg, 100*sizeof(int));
}

void recv_square(int sockfd,int data[2]){
  int tmp[2];
  int n=read(sockfd,tmp,2*sizeof(int));
  memcpy(data, tmp, 2*sizeof(int));
}
/*
 * Socket Write Functions
 */

/* Writes a message to a client socket. */
void write_client_msg(int cli_sockfd, char * msg)
{
    int n = write(cli_sockfd, msg, strlen(msg));
    if (n < 0)
        error("ERROR writing msg  to client socket");
}

/* Writes an int to a client socket. */
void write_client_int(int cli_sockfd, int msg)
{
    int n = write(cli_sockfd, &msg, sizeof(int));
    if (n < 0)
        error("ERROR  writing int to client socket");
}

/* Writes a message to both client sockets. */
void write_clients_msg(int * cli_sockfd, char * msg)
{
    write_client_msg(cli_sockfd[0], msg);
    write_client_msg(cli_sockfd[1], msg);
}

/* Writes an int to both client sockets. */
void write_clients_int(int * cli_sockfd, int msg)
{
    write_client_int(cli_sockfd[0], msg);
    write_client_int(cli_sockfd[1], msg);
}

/*
 * Connect Functions
 */

/* Sets up the listener socket. */
int setup_listener(int portno)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    /* Get a socket to listen on */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening listener socket.");

    /* Zero out the memory for the server information */
    memset(&serv_addr, 0, sizeof(serv_addr));

	/* set up the server info */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Bind the server info to the listener socket. */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR binding listener socket.");


    /* Return the socket number. */
    return sockfd;
}

/* Sets up the client sockets and client connections. */
void get_clients(int lis_sockfd, int * cli_sockfd)
{
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    /* Listen for two clients. */
    int num_conn = 0;
    while(num_conn < 2)
    {
        /* Listen for clients. */
	    listen(lis_sockfd, 253 - player_count);

        /* Zero out memory for the client information. */

        clilen = sizeof(cli_addr);
	    /* Accept the connection from the client. */
        cli_sockfd[num_conn] = accept(lis_sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (cli_sockfd[num_conn] < 0)
            /* Horrible things have happened. */
            error("ERROR accepting a connection from a client.");



        /* Send the client it's ID. */
        write(cli_sockfd[num_conn], &num_conn, sizeof(int));


        /* Increment the player count. */
        pthread_mutex_lock(&mutexcount);
        player_count++;
        printf("Le nombre de joueurs actifs est désormais de %d.\n", player_count);
        pthread_mutex_unlock(&mutexcount);

        if (num_conn == 0) {
            /* Send "HLD" to first client to let the user know the server is waiting on a second client. */
            write_client_msg(cli_sockfd[0],"HLD");
        }
        num_conn++;
    }
}



void get_update(int sockfd,int player,int coup[2]){
  if(player==1){
    if(grille_joueur2_placement[coup[0]][coup[1]]!=0){
      grille_joueur1_game[coup[0]][coup[1]]=1;
      printf("Le joueur 1 a touché l'adversaire\n");
    }
    else{
      grille_joueur1_game[coup[0]][coup[1]]=2;
      printf("Le joueur 1 n'a pas touché l'adversaire\n");
    }
    write_client_data(sockfd,grille_joueur1_game);
  }else{
    if(grille_joueur1_placement[coup[0]][coup[1]]!=0){
      grille_joueur2_game[coup[0]][coup[1]]=1;
      printf("Le joueur 2 a touché l'adversaire\n");
    }
    else{
      grille_joueur2_game[coup[0]][coup[1]]=2;
      printf("Le joueur 2 n'a pas touché l'adversaire\n");
    }
    write_client_data(sockfd,grille_joueur2_game);
  }

}


void play(int * cli_sockfd, int player,int data[2])
{
  int tmp[2];
    if(player == 1){
      write_client_msg(cli_sockfd[1], "TRN");
      write_client_msg(cli_sockfd[0], "NTR");
      recv_square(cli_sockfd[1],tmp);
      get_update(cli_sockfd[1],2,tmp);
      memcpy(data, tmp, 2*sizeof(int));
    }else{
      write_client_msg(cli_sockfd[0], "TRN");
      write_client_msg(cli_sockfd[1], "NTR");
      recv_square(cli_sockfd[0],tmp);
      get_update(cli_sockfd[0],1,tmp);
      memcpy(data, tmp, 2*sizeof(int));
    }
}

int check_square(char * data){
  int nbr=data[0]-'0';
  if(nbr>=0 && nbr<=9 && data[1]>='A' && data[1]<='J')
    return 1;
  return 0;
}

void *run_game(void *thread_data)
{
    int *cli_sockfd = (int*)thread_data; /* Client sockets. */

    /* Send the start message. */

    char msg[4];
    printf("Remplissage des grilles...\n");
    write_clients_msg(cli_sockfd, "SRT");

    write_client_msg(cli_sockfd[0], "FIG");
    write_client_msg(cli_sockfd[1], "WFG");
    recv_grid(grille_joueur1_placement,cli_sockfd[0],1);

    printf("La grille du joueur 1 a été remplie. .\n");

    write_client_msg(cli_sockfd[1], "FIG");
    write_client_msg(cli_sockfd[0], "WFG");
    recv_grid(grille_joueur2_placement,cli_sockfd[1],2);

    printf("Les grilles sont remplies. Le jeu commence... \n");
    //printf("Case grille 1 : %i\n",grille_joueur1[0][0]);
    write_clients_msg(cli_sockfd, "STP");
    int gameOver=0;
    while(gameOver==0){
    int square[2];
      printf("Au tour du joueur %i \n",turn+1);
      play(cli_sockfd, prev_turn,square);
      prev_turn=turn;
      turn = (turn + 1) % 2;
      gameOver=0;
    }
  }

int main(int argc, char *argv[])
{

    /* Make sure a port was specified. */
    if (argc < 2) {
        printf("ERROR, no port provided\n");
        exit(1);
    }

    int lis_sockfd = setup_listener(MYPORT); /* Listener socket. */
    pthread_mutex_init(&mutexcount, NULL);
  for(int i=0;i<10;i++){
    for(int j=0;j<0;j++){
      grille_joueur1_game[i][j]=0;
      grille_joueur2_game[i][j]=0;
    }
  }
    while (1) {
        if (player_count <= 252) { /* Only launch a new game if we have room. Otherwise, just spin. */
            int *cli_sockfd = (int*)malloc(2*sizeof(int)); /* Client sockets */
            /* Get two clients connected. */
            get_clients(lis_sockfd, cli_sockfd);
            pthread_t thread; /* Don't really need the thread id for anything in this case, but here it is anyway. */
            int result = pthread_create(&thread, NULL, run_game, (void *)cli_sockfd); /* Start a new thread for this game. */
            if (result){
                printf("Thread creation failed with return code %d\n", result);
                exit(-1);
            }
        }
    }

    close(lis_sockfd);

    pthread_mutex_destroy(&mutexcount);
    pthread_exit(NULL);
}
