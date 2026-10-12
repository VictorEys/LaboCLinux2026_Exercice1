#include "FichierUtilisateur.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>

int estPresent(const char* nom)
{
  int fd, compt = 1;
  UTILISATEUR buf;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
  {
    return -1;
  }
  else
  {
    while(read(fd,&buf, sizeof(UTILISATEUR)) > 0)
    {
      if(strcmp(nom, buf.nom) == 0)
      {
        close(fd);
        return compt;
      }
      compt++;
    }
    close(fd);
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int i, somme = 0, ret;
  for(i = 0; motDePasse[i] != '\0'; i++)
  {
    somme += (i + 1) *motDePasse[i];
  }

  ret = somme % 97;

  return ret;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  int fd, rc;
  UTILISATEUR buf;

  if((fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
  {
    perror("Erreur de open()");
    return;
  }
  else
  {
    if((rc = lseek(fd, 0, SEEK_END)) == -1)
    {
      perror("Erreur de lseek");
      close(fd);
      return;
    } 

    strcpy(buf.nom, nom);
    buf.hash = hash(motDePasse);

    write(fd, &buf, sizeof(UTILISATEUR));
    close(fd);
  }
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  int fd, rc, h1;
  UTILISATEUR tmp;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
    return -1;
  else
  {
    if((rc = lseek(fd, (pos -1)*sizeof(UTILISATEUR), SEEK_SET)) == -1)
    {
      perror("Erreur lseek");
      close(fd);
      return -1;
    }
    else
    {
      read(fd, &tmp, sizeof(UTILISATEUR));
      if((h1 = hash(motDePasse)) == tmp.hash)
      {
        close(fd);
        return 1;
      }
        
      close(fd);
      return 0;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int compt = 0, fd;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1) 
    return -1;
  else
  {
    while((read(fd, &vecteur[compt], sizeof(UTILISATEUR)) > 0))
    {
      compt++;
    }

    close(fd);
  }


  return compt;
}
