#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <cstring>
#include "protocole.h" // contient la cle et la structure d'un message

int idQ;
int pid1,pid2;

int main()
{
  MESSAGE requete;
  pid_t destinataire;

  // Armement du signal SIGINT
  // TO DO (etape 6)

  // Creation de la file de message
  fprintf(stderr,"(SERVEUR) Creation de la file de messages\n");
  if((idQ = msgget(CLE, IPC_CREAT | IPC_EXCL | 0600)) == -1)
  {
    perror("Erreur de msgget");
  }

  // Attente de connection de 2 clients
  fprintf(stderr,"(SERVEUR) Attente de connection d'un premier client...\n");
  // TO DO (etape 5)
  fprintf(stderr,"(SERVEUR) Attente de connection d'un second client...\n");
  // TO DO (etape 5)

  while(1) 
  {
    // TO DO (etapes 3, 4 et 5)
  	fprintf(stderr,"(SERVEUR) Attente d'une requete...\n");
    if((msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 1, 0) == -1))
    {
      perror("Erreur msgrcv SERVEUR\n");
      exit(1);
    }

    fprintf(stderr,"(SERVEUR) Requete recue de %d : --%s--\n",requete.expediteur,requete.texte);

    char temp[80] = "(SERVEUR) ";
    strcat(temp, requete.texte);
    strcpy(requete.texte, temp);
    fprintf(stderr, "APRES MODIFICATION : %s\n", requete.texte);

    destinataire = requete.expediteur;
    requete.type = destinataire;
    fprintf(stderr,"(SERVEUR) Envoi de la reponse a %d\n",destinataire);
    if((msgsnd(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 0)) == -1)
    {
      perror("Erreur de msgsnd SERVEUR\n");
    }

    kill(destinataire, SIGUSR1);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)
