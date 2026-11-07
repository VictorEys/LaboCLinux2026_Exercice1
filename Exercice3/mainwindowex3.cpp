#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h>     // Pour fork() et execl()
#include <sys/types.h>  // Pour les types comme pid_t
#include <sys/wait.h>   // Pour wait() et les macros WIFEXITSTATUS / WEXITSTATUS
#include <fcntl.h> 
#include <unistd.h>

MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");

  const char *nomGrp1, *nomGrp2, *nomGrp3;
  int idFils1 = -1, idFils2 = -1 ,idFils3 = -1 , status;

  int fd = open("Trace.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
  if(fd < 0)
  {
    perror("Erreur lors de l'ouverture du fichier Trace.log\n");
  }
  else
  {
    dup2(fd, STDERR_FILENO);
    ::close(fd);


    if(recherche1Selectionnee())
    {
      if((nomGrp1 = getGroupe1()) == NULL)
      {
        fprintf(stderr, "Erreur : Auncun groupe saisi pour le 1.\n");
      }
      else
      {
        if((idFils1 = fork()) < 0)
        {
          perror("Erreur lors du fork fils 1.\n");
        }
        else
        {
          if(idFils1 == 0)
          {
            execl("./Lecture", "Lecture", nomGrp1, NULL);

            perror("Erreur de l'execl <Lecture> du fils 1.\n");
            exit(1);
          }
        }
      }
    }

    if(recherche2Selectionnee())
    {
      if((nomGrp2 = getGroupe2()) == NULL)
        fprintf(stderr,"Erreur : Auncun groupe saisi pour le 2.\n");
      else
      {
        if((idFils2 = fork()) < 0)
          perror("Erreur lors du fork fils 2\n");
        else
        {
          if(idFils2 == 0)
          {
            execl("./Lecture", "Lecture", nomGrp2, NULL);

            perror("Erreur de l'execl <Lecture> du fils 2\n");
            exit(1);
          }
        }
      }
    }

    if(recherche3Selectionnee())
    {
      if((nomGrp3 = getGroupe3()) == NULL)
        fprintf(stderr, "Erreur : Auncun groupe saisi pour le 3.\n");
      else
      {
        if((idFils3 = fork()) < 0)
          perror("Erreur lors du fork fils 3.\n");
        else
        {
          if(idFils3 == 0)
          {
            execl("./Lecture", "Lecture", nomGrp3, NULL);

            perror("Erreur de l'execl <Lecture> du fils 3.\n");
            exit(1);
          }
        }
      }    
    }

    if(idFils1 > 0)
    {
      waitpid(idFils1, &status, 0);
      if(WIFEXITED(status))
        setResultat1(WEXITSTATUS(status));
    }

    if(idFils2 > 0)
    {
      waitpid(idFils2, &status, 0);
      if(WIFEXITED(status))
        setResultat2(WEXITSTATUS(status));
    }

    if(idFils3 > 0)
    {
      waitpid(idFils3, &status, 0);
      if(WIFEXITED(status))
        setResultat3(WEXITSTATUS(status));
    }
  }
}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();

  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  qApp->quit();
}
