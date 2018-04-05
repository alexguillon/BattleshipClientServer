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
int prev_turn = 1;

int porteAvionCoule_1 = 0;
int porteAvionCoule_2 = 0;
int sousMarinCoule1_1 = 0;
int sousMarinCoule1_2 = 0;
int sousMarinCoule2_1 = 0;
int sousMarinCoule2_2 = 0;
int torpilleurCoule_1 = 0;
int torpilleurCoule_2 = 0;
int stockPorteAvion_1[4][2];
int stockPorteAvion_2[4][2];
int stockSousMarin1_1[3][2];
int stockSousMarin1_2[3][2];
int stockSousMarin2_1[3][2];
int stockSousMarin2_2[3][2];
int stockTorpilleur_1[2][2];
int stockTorpilleur_2[2][2];

void checkBoat(int * cli_sockfd, int player) {
  if (player == 1) {
    if (grille_joueur1_game[stockPorteAvion_2[0][0]][stockPorteAvion_2[0][1]] == 1) {
      if (grille_joueur1_game[stockPorteAvion_2[1][0]][stockPorteAvion_2[1][1]] == 1) {
        if (grille_joueur1_game[stockPorteAvion_2[2][0]][stockPorteAvion_2[2][1]] == 1) {
          if (grille_joueur1_game[stockPorteAvion_2[3][0]][stockPorteAvion_2[3][1]] == 1) {
            if (porteAvionCoule_2 == 0) {
              write_client_msg(cli_sockfd[0], "PAT");
              write_client_msg(cli_sockfd[1], "PAC");
              porteAvionCoule_2 = 1;
            }
          }
        }
      }
    }
    if (grille_joueur1_game[stockSousMarin1_2[0][0]][stockSousMarin1_2[0][1]] == 1) {
      if (grille_joueur1_game[stockSousMarin1_2[1][0]][stockSousMarin1_2[1][1]] == 1) {
        if (grille_joueur1_game[stockSousMarin1_2[2][0]][stockSousMarin1_2[2][1]] == 1) {
          if (sousMarinCoule1_2 == 0) {
            write_client_msg(cli_sockfd[0], "SMT");
            write_client_msg(cli_sockfd[1], "SMC");
            sousMarinCoule1_2 = 1;
          }
        }
      }
    }
    if (grille_joueur1_game[stockSousMarin2_2[0][0]][stockSousMarin2_2[0][1]] == 1) {
      if (grille_joueur1_game[stockSousMarin2_2[1][0]][stockSousMarin2_2[1][1]] == 1) {
        if (grille_joueur1_game[stockSousMarin2_2[2][0]][stockSousMarin2_2[2][1]] == 1) {
          if (sousMarinCoule2_2 == 0) {
            write_client_msg(cli_sockfd[0], "SMT");
            write_client_msg(cli_sockfd[1], "SMC");
            sousMarinCoule2_2 = 1;
          }
        }
      }
    }
    if (grille_joueur1_game[stockTorpilleur_2[0][0]][stockTorpilleur_2[0][1]] == 1) {
      if (grille_joueur1_game[stockTorpilleur_2[1][0]][stockTorpilleur_2[1][1]] == 1) {
        if (torpilleurCoule_2 == 0) {
          write_client_msg(cli_sockfd[0], "TOT");
          write_client_msg(cli_sockfd[1], "TOC");
          torpilleurCoule_2 = 1;
        }
      }
    }
  } else {
    if (grille_joueur2_game[stockPorteAvion_1[0][0]][stockPorteAvion_1[0][1]] == 1) {
      if (grille_joueur2_game[stockPorteAvion_1[1][0]][stockPorteAvion_1[1][1]] == 1) {
        if (grille_joueur2_game[stockPorteAvion_1[2][0]][stockPorteAvion_1[2][1]] == 1) {
          if (grille_joueur2_game[stockPorteAvion_1[3][0]][stockPorteAvion_1[3][1]] == 1) {
            if (porteAvionCoule_1 == 0) {
              write_client_msg(cli_sockfd[1], "PAT");
              write_client_msg(cli_sockfd[0], "PAC");
              porteAvionCoule_1 = 1;
            }
          }
        }
      }
    }
    if (grille_joueur2_game[stockSousMarin1_1[0][0]][stockSousMarin1_1[0][1]] == 1) {
      if (grille_joueur2_game[stockSousMarin1_1[1][0]][stockSousMarin1_1[1][1]] == 1) {
        if (grille_joueur2_game[stockSousMarin1_1[2][0]][stockSousMarin1_1[2][1]] == 1) {
          if (sousMarinCoule1_1 == 0) {
            write_client_msg(cli_sockfd[1], "SMT");
            write_client_msg(cli_sockfd[0], "SMC");
            sousMarinCoule1_1 = 1;
          }
        }
      }
    }
    if (grille_joueur2_game[stockSousMarin2_1[0][0]][stockSousMarin2_1[0][1]] == 1) {
      if (grille_joueur2_game[stockSousMarin2_1[1][0]][stockSousMarin2_1[1][1]] == 1) {
        if (grille_joueur2_game[stockSousMarin2_1[2][0]][stockSousMarin2_1[2][1]] == 1) {
          if (sousMarinCoule2_1 == 0) {
            write_client_msg(cli_sockfd[1], "SMT");
            write_client_msg(cli_sockfd[0], "SMC");
            sousMarinCoule2_1 = 1;
          }
        }
      }
    }
    if (grille_joueur2_game[stockTorpilleur_1[0][0]][stockTorpilleur_1[0][1]] == 1) {
      if (grille_joueur2_game[stockTorpilleur_1[1][0]][stockTorpilleur_1[1][1]] == 1) {
        if (torpilleurCoule_1 == 0) {
          write_client_msg(cli_sockfd[1], "TOT");
          write_client_msg(cli_sockfd[0], "TOC");
          torpilleurCoule_1 = 1;
        }
      }
    }

  }
}

void fillBoatArray() {
  int cptPA1 = 0;
  int cptPA2 = 0;
  int cptT1 = 0;
  int cptT2 = 0;
  int cptSM1_1 = 0;
  int cptSM1_2 = 0;
  int cptSM2_1 = 0;
  int cptSM2_2 = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (grille_joueur1_placement[i][j] == 4) {
        stockPorteAvion_1[cptPA1][0] = i;
        stockPorteAvion_1[cptPA1][1] = j;
        cptPA1++;
      }
      if (grille_joueur2_placement[i][j] == 4) {
        stockPorteAvion_2[cptPA2][0] = i;
        stockPorteAvion_2[cptPA2][1] = j;
        cptPA2++;
      }
      if (grille_joueur1_placement[i][j] == 1) {
        stockTorpilleur_1[cptT1][0] = i;
        stockTorpilleur_1[cptT1][1] = j;
        cptT1++;
      }
      if (grille_joueur2_placement[i][j] == 1) {
        stockTorpilleur_2[cptT2][0] = i;
        stockTorpilleur_2[cptT2][1] = j;
        cptT2++;
      }
      if (grille_joueur1_placement[i][j] == 2) {
        stockSousMarin1_1[cptSM1_1][0] = i;
        stockSousMarin1_1[cptSM1_1][1] = j;
        cptSM1_1++;
      }
      if (grille_joueur2_placement[i][j] == 2) {
        stockSousMarin1_2[cptSM1_2][0] = i;
        stockSousMarin1_2[cptSM1_2][1] = j;
        cptSM1_2++;
      }
      if (grille_joueur1_placement[i][j] == 3) {
        stockSousMarin2_1[cptSM2_1][0] = i;
        stockSousMarin2_1[cptSM2_1][1] = j;
        cptSM2_1++;
      }
      if (grille_joueur2_placement[i][j] == 3) {
        stockSousMarin2_2[cptSM2_2][0] = i;
        stockSousMarin2_2[cptSM2_2][1] = j;
        cptSM2_2++;
      }
    }
  }
}

void error(const char * msg) {
  perror(msg);
  pthread_exit(NULL);
}

int is_Game_Over() {
  int loop = 2;
  int win = -1;
  for (int player = 1; player <= loop; player++) {
    for (int i = 0; i < 10 && win == -1; i++) {
      for (int j = 0; j < 10 && win == -1; j++) {
        if (player == 1) {
          if (grille_joueur1_placement[i][j] != 0 && (grille_joueur2_game[i][j] == 0 || grille_joueur2_game[i][j] == 2)) {
            win = 0;
          }
        } else {
          if (grille_joueur2_placement[i][j] != 0 && (grille_joueur1_game[i][j] == 0 || grille_joueur1_game[i][j] == 2)) {
            win = 0;
          }
        }
      }
    }
    if (win == -1)
      return player;
    else
      win = -1;
  }
  return 0;
}
void write_client_data(int sockfd, int tab[10][10]) {
  int n = write(sockfd, tab, 100 * sizeof(int));
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
      } else if (grid[i][j] == 1) {
        strcpy(str, "\033[42mO\033[0m");
        strcpy(data[i][j], str);
      } else if (grid[i][j] == 2) {
        strcpy(str, "\033[41mX\033[0m");
        strcpy(data[i][j], str);
      }
    }
  }

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

void draw_grid_placement(int grid[10][10]) {
  char data[10][10][30];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      char str[30];
      if (grid[i][j] == 0) {
        strcpy(str, " ");
        strcpy(data[i][j], str);
      } else if (grid[i][j] == 1) {
        strcpy(str, "\033[41mX\033[0m");
        strcpy(data[i][j], str);
      } else if (grid[i][j] == 2 || grid[i][j] == 3) {
        strcpy(str, "\033[46mX\033[0m");
        strcpy(data[i][j], str);
      } else if (grid[i][j] == 4) {
        strcpy(str, "\033[43mX\033[0m");
        strcpy(data[i][j], str);
      }
    }
  }

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
void recv_msg(int sockfd, char * msg) {
  memset(msg, 0, 4);
  int n = read(sockfd, msg, 3);

  if (n < 0 || n != 3)
    error("Erreur ");
}

void recv_grid(int src[10][10], int cli_sockfd, int player) {
  int msg[10][10];
  int n = read(cli_sockfd, msg, 100 * sizeof(int));
  memcpy(src, msg, 100 * sizeof(int));
  printf("------------------GRILLE DU JOUEUR %i------------------------\n", player);
  draw_grid_placement(src);
}

void recv_grid_game(int src[10][10], int cli_sockfd, int player) {
  int msg[10][10];
  int n = read(cli_sockfd, msg, 100 * sizeof(int));
  memcpy(src, msg, 100 * sizeof(int));
}

void recv_square(int sockfd, int data[2]) {
  int tmp[2];
  int n = read(sockfd, tmp, 2 * sizeof(int));
  memcpy(data, tmp, 2 * sizeof(int));
}

void write_client_msg(int cli_sockfd, char * msg) {
  int n = write(cli_sockfd, msg, strlen(msg));
  if (n < 0)
    error("Erreur");
}

void write_client_int(int cli_sockfd, int msg) {
  int n = write(cli_sockfd, & msg, sizeof(int));
  if (n < 0)
    error("Erreur");
}

void write_clients_msg(int * cli_sockfd, char * msg) {
  write_client_msg(cli_sockfd[0], msg);
  write_client_msg(cli_sockfd[1], msg);
}

void write_clients_int(int * cli_sockfd, int msg) {
  write_client_int(cli_sockfd[0], msg);
  write_client_int(cli_sockfd[1], msg);
}

int setup_listener(int portno) {
  int sockfd;
  struct sockaddr_in serv_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("Erreur");

  memset( & serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0)
    error("Erreur");

  return sockfd;
}

void get_clients(int lis_sockfd, int * cli_sockfd) {
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  int num_conn = 0;
  while (num_conn < 2) {
    listen(lis_sockfd, 253 - player_count);
    clilen = sizeof(cli_addr);
    cli_sockfd[num_conn] = accept(lis_sockfd, (struct sockaddr * ) & cli_addr, & clilen);
    if (cli_sockfd[num_conn] < 0)
      error("Erreur");

    write(cli_sockfd[num_conn], & num_conn, sizeof(int));

    pthread_mutex_lock( & mutexcount);
    player_count++;
    printf("Le nombre de joueurs actifs est désormais de %i.\n", player_count);
    pthread_mutex_unlock( & mutexcount);

    if (num_conn == 0) {
      write_client_msg(cli_sockfd[0], "HLD");
    }
    num_conn++;
  }
}

int get_update(int * cli_sockfd, int sockfd, int player, int coup[2]) {
  int value = 0;
  if (player == 1) {
    if (grille_joueur2_placement[coup[0]][coup[1]] != 0) {
      grille_joueur1_game[coup[0]][coup[1]] = 1;
      printf("Le joueur 1 a touché l'adversaire\n");
      write_client_msg(cli_sockfd[1], "HBT");
      if (is_Game_Over() == 0)
        value = 3;
      else
        value = is_Game_Over();
    } else {
      grille_joueur1_game[coup[0]][coup[1]] = 2;
      printf("Le joueur 1 n'a pas touché l'adversaire\n");
      write_client_msg(cli_sockfd[1], "HNT");
    }
    write_client_data(sockfd, grille_joueur1_game);
  } else {
    if (grille_joueur1_placement[coup[0]][coup[1]] != 0) {
      grille_joueur2_game[coup[0]][coup[1]] = 1;
      printf("Le joueur 2 a touché l'adversaire\n");
      write_client_msg(cli_sockfd[0], "HBT");
      if (is_Game_Over() == 0)
        value = 4;
      else
        value = is_Game_Over();
    } else {
      grille_joueur2_game[coup[0]][coup[1]] = 2;
      printf("Le joueur 2 n'a pas touché l'adversaire\n");
      write_client_msg(cli_sockfd[0], "HNT");
    }
    write_client_data(sockfd, grille_joueur2_game);
  }
  return value;
}

int play(int * cli_sockfd, int player, int data[2]) {
  int value = 5;
  int tmp[2];
  while (value == 5 || value == 4 || value == 3) {
    if (player == 1) {
      write_client_msg(cli_sockfd[1], "TRN");
      write_client_msg(cli_sockfd[0], "NTR");
      recv_square(cli_sockfd[1], tmp);
      value = get_update(cli_sockfd, cli_sockfd[1], 2, tmp);
      checkBoat(cli_sockfd, 2);
      memcpy(data, tmp, 2 * sizeof(int));
    } else {
      write_client_msg(cli_sockfd[0], "TRN");
      write_client_msg(cli_sockfd[1], "NTR");
      recv_square(cli_sockfd[0], tmp);
      value = get_update(cli_sockfd, cli_sockfd[0], 1, tmp);
      checkBoat(cli_sockfd, 1);
      memcpy(data, tmp, 2 * sizeof(int));
    }
    if (value == 1) {
      write_client_msg(cli_sockfd[1], "WIN");
      write_client_msg(cli_sockfd[0], "LOS");
    } else if (value == 2) {
      write_client_msg(cli_sockfd[1], "LOS");
      write_client_msg(cli_sockfd[0], "WIN");
    }
  }
  return value;
}

int check_square(char * data) {
  int nbr = data[0] - '0';
  if (nbr >= 0 && nbr <= 9 && data[1] >= 'A' && data[1] <= 'J')
    return 1;
  return 0;
}

void * run_game(void * thread_data) {
  int * cli_sockfd = (int * ) thread_data;

  char msg[4];
  printf("Remplissage des grilles...\n");
  write_clients_msg(cli_sockfd, "SRT");

  write_client_msg(cli_sockfd[0], "FIG");
  write_client_msg(cli_sockfd[1], "WFG");
  recv_grid(grille_joueur1_placement, cli_sockfd[0], 1);

  printf("La grille du joueur 1 a été remplie. .\n");

  write_client_msg(cli_sockfd[1], "FIG");
  write_client_msg(cli_sockfd[0], "WFG");
  recv_grid(grille_joueur2_placement, cli_sockfd[1], 2);
  fillBoatArray();
  printf("Les grilles sont remplies. Le jeu commence... \n");
  write_clients_msg(cli_sockfd, "STP");
  int gameOver = 0;
  while (gameOver != 1) {
    int square[2];
    printf("Au tour du joueur %i \n", (prev_turn + 1));
    int value = play(cli_sockfd, prev_turn, square);
    if (value == 1) {
      printf("Le joueur 2 a gagné !\n");
      gameOver = 1;
    } else if (value == 2) {
      printf("Le joueur 1 a gagné !\n");
      gameOver = 1;
    }
    prev_turn = turn;
    turn = (turn + 1) % 2;
  }
  printf("\n Deconnexion des joueurs...\n");

  close(cli_sockfd[0]);
  close(cli_sockfd[1]);

  pthread_mutex_lock( & mutexcount);
  player_count--;
  printf("Le nombre de joueurs actifs est désormais de %i.\n", player_count);
  player_count--;
  printf("Le nombre de joueurs actifs est désormais de %i.\n", player_count);
  pthread_mutex_unlock( & mutexcount);

  printf("\n La partie est terminée.\n");

  free(cli_sockfd);

  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("Erreur\n");
    exit(1);
  }

  int lis_sockfd = setup_listener(MYPORT);
  pthread_mutex_init( & mutexcount, NULL);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 0; j++) {
      grille_joueur1_game[i][j] = 0;
      grille_joueur2_game[i][j] = 0;
    }
  }
  while (1) {
    if (player_count <= 252) {
      int * cli_sockfd = (int * ) malloc(2 * sizeof(int));
      get_clients(lis_sockfd, cli_sockfd);
      pthread_t thread;
      int result = pthread_create( & thread, NULL, run_game, (void * ) cli_sockfd);
      if (result) {
        printf("Erreur de création du thread.. %i\n", result);
        exit(-1);
      }
    }
  }

  close(lis_sockfd);

  pthread_mutex_destroy( & mutexcount);
  pthread_exit(NULL);
}
