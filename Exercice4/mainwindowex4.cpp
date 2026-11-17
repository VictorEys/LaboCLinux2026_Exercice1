#include "mainwindowex4.h"
#include "ui_mainwindowex4.h"

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 


extern MainWindowEx4 *w;

int idFils1, idFils2, idFils3;
void HandlerSIGCHLD(int sig);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowEx4::MainWindowEx4(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx4)
{
  ui->setupUi(this);
  ui->pushButtonAnnulerTous->setVisible(false);

  // armement de SIGCHLD
  struct sigaction A;
  A.sa_handler = HandlerSIGCHLD;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0;

  if(sigaction(SIGCHLD, &A, NULL) == -1)
  {
    perror("Erreur de sigaction\n");
    exit(1);
  }
}

MainWindowEx4::~MainWindowEx4()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::setGroupe1(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx4::setGroupe2(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx4::setGroupe3(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx4::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx4::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx4::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx4::traitement1Selectionne()
{
  return ui->checkBoxTraitement1->isChecked();
}

bool MainWindowEx4::traitement2Selectionne()
{
  return ui->checkBoxTraitement2->isChecked();
}

bool MainWindowEx4::traitement3Selectionne()
{
  return ui->checkBoxTraitement3->isChecked();
}

const char* MainWindowEx4::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe3()
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
void MainWindowEx4::on_pushButtonDemarrerTraitements_clicked()
{
  fprintf(stderr,"Clic sur le bouton Demarrer Traitements\n");
  
  const char *nomGrp1, *nomGrp2, *nomGrp3;

  int fd = open("Trace.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
  if(fd < 0)
  {
    perror("Erreur lors de l'ouverture du fichier Trace.log\n");
  }
  else
  {
    dup2(fd, STDERR_FILENO);
    ::close(fd);


    if(traitement1Selectionne())
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
            execl("./Traitement", "Traitement", nomGrp1, "200", NULL);

            perror("Erreur de l'execl <Traitement> du fils 1.\n");
            exit(1);
          }
        }
      }
    }

    if(traitement2Selectionne())
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
            execl("./Traitement", "Traitement", nomGrp2, "450", NULL);

            perror("Erreur de l'execl <Traitement> du fils 2\n");
            exit(1);
          }
        }
      }
    }

    if(traitement3Selectionne())
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
            execl("./Traitement", "Traitement", nomGrp3, "700", NULL);

            perror("Erreur de l'execl <Traitement> du fils 3.\n");
            exit(1);
          }
        }
      }    
    }
  }
}

void MainWindowEx4::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();

  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx4::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  qApp->quit();
}

void MainWindowEx4::on_pushButtonAnnuler1_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler1\n");
  if(idFils1 > 0)
  {
    kill(idFils1, SIGUSR1);
  }
}

void MainWindowEx4::on_pushButtonAnnuler2_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler2\n");
  if(idFils2 > 0)
  {
    kill(idFils2, SIGUSR1);
  }
}

void MainWindowEx4::on_pushButtonAnnuler3_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler3\n");
  if(idFils3 > 0)
  {
    kill(idFils3, SIGUSR1);
  }
}

void MainWindowEx4::on_pushButtonAnnulerTous_clicked()
{
  // fprintf(stderr,"Clic sur le bouton Annuler tout\n");
  // NOTHING TO DO --> bouton supprimé
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Handlers de signaux //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HandlerSIGCHLD(int sig)
{
  (void)sig;
  int id, status;

  id = wait(&status);

  if(id != -1 && WIFEXITED(status))
  {
    int resultat = WEXITSTATUS(status);

    if(id == idFils1)
    {
      w->setResultat1(resultat);
      idFils1 = 0;
    }
    else
    {
      if(id == idFils2)
      {
        w->setResultat2(resultat);
        idFils2 = 0;
      }
      else
      {
        if(id == idFils3)
        {
          w->setResultat3(resultat);
          idFils3 = 0;
        }
      }
    }
  }
}