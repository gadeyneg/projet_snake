#include "mainwindow.h"
#include "ui_mainwindow.h"

//quelques variables globales utiles, que je n'avais pas envie d'ajouter aux paramètres de mainwindow
//pour ne pas surcharger la classe.
std::vector<Joueur> meilleurs;
int current_gen;
QTimer *timer;
int delai = 1000;
bool can_play = false;
std::stringstream sstm;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connection des boutons.
    QObject::connect(ui->pushButton_2,&QPushButton::clicked, this, &MainWindow::launchSnake);
    QObject::connect(ui->pushButton,&QPushButton::clicked, this, &MainWindow::backtomenue);
    QObject::connect(ui->pushButton_4,&QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(ui->pushButton_3,&QPushButton::clicked, this, &MainWindow::launchAI);
    QObject::connect(ui->pushButton_5,&QPushButton::clicked, this, &MainWindow::gotonext);
    QObject::connect(ui->pushButton_6,&QPushButton::clicked, this, &MainWindow::gotoprevious);
    QObject::connect(ui->pushButton_7,&QPushButton::clicked, this, &MainWindow::speedtimer);
    QObject::connect(ui->pushButton_8,&QPushButton::clicked, this, &MainWindow::slowtimer);

    //initialisation du menu principal. On aurait pu le faire avec bactomenu(), mais cette methode
    //réalise ausis des choses inutiles au premier lancement.
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->progressBar->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::backtomenue(){
    if(!can_play){
        //on était en simulation d'AI, il faut arreter le timer
        timer->stop();
    }
    can_play = false;
    ui->label->hide();
    ui->label_2->hide();
    ui->label_4->hide();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
}

void MainWindow::launchSnake(){
    can_play=true;
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label->show();
    ui->label_2->show();
    m_controller.setCible(Cible(Point(5,5)));
    m_controller.setSnake(Serpent(Point(10,10)));
    ui->label->setController(&m_controller);
    ui->label->draw();
    m_controller.setDrawer(ui->label);
}

void MainWindow::launchAI(){
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label_3->show();
    int pop_size = 3000;
    int gen_size = 30;
    ui->progressBar->show();
    ui->progressBar->setRange(0,gen_size);
    ui->progressBar->setValue(0);
    qApp->processEvents();
    //création de la table de joueurs.
    Population ma_pop = Population(pop_size);
    for(int i=0; i< gen_size ; i++){          //i<nombre de générations.
        ma_pop.sort();
        meilleurs.push_back(ma_pop.m_listeJoueurs[0]);
        ma_pop=Population(ma_pop);
        if(i%5==0){
            ui->progressBar->setValue(i);
            qApp->processEvents();
        }
    }
    ui->progressBar->hide();
    ui->label_3->hide();
    //faire apparaitre l'interface.
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->label->show();
    m_controller.setCible(Cible(Point(5,5)));
    m_controller.setSnake(Serpent(Point(10,10)));
    ui->label->setController(&m_controller);
    ui->label->draw();
    m_controller.setDrawer(ui->label);
    //initier la démonstration.
    current_gen=0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(proceed()));
    timer->start(delai);
    //on voudra faire qqc toutes les 1 secondes.
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    std::string message = "generation ";
    std:: string res = message + std::to_string(current_gen);
    ui->label_4->setText(QString::fromStdString(res));
    ui->label_4->show();
}

//touches utilisées pour controler le snake.
//elles sont inactives si on est en mode simulation.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(can_play){
    if(event->key() == Qt::Key_Q)
    {
        m_controller.action(LEFT);
    }

    if(event->key() == Qt::Key_D)
    {
        m_controller.action(RIGHT);
    }

    if(event->key() == Qt::Key_Z)
    {
        m_controller.action(UP);
    }

    if(event->key() == Qt::Key_S)
    {
        m_controller.action(DOWN);
    }

    if(event->key() == Qt::Key_N and m_controller.m_snake.getPerdu())
    {
        m_controller.m_snake.setPerdu(false);
        Point p_cible(5,5);
        Cible cible(p_cible);
        m_controller.setCible(cible);

        Point p_snake(10,10);
        Serpent serpent(p_snake);
        m_controller.setSnake(serpent);
    }

    }
    ui->label->draw();
}

void MainWindow::gotonext()
{
    if(current_gen<meilleurs.size()-2){
        current_gen+=1;
        m_controller.resetSnake();
        std::string message = "generation ";
        std:: string res = message + std::to_string(current_gen);
        ui->label_4->setText(QString::fromStdString(res));
    }else{
        timer->stop();
        backtomenue();
    }
}

void MainWindow::gotoprevious()
{
    if(current_gen!=0){
        current_gen-=1;
        m_controller.resetSnake();
        std::string message = "generation ";
        std:: string res = message + std::to_string(current_gen);
        ui->label_4->setText(QString::fromStdString(res));
    }
}

void MainWindow::proceed(){

    if(!m_controller.m_snake.getPerdu()){
        m_controller.nextMove(meilleurs[current_gen].m_reseau);
        ui->label->draw();
    }else{
        gotonext();
    }
}

void MainWindow::speedtimer()
{
    if(delai>150){
        delai = delai*2/3;
        timer->setInterval(delai);
    }
}

void MainWindow::slowtimer()
{
    if(delai<800){
        delai = delai*3/2;
        timer->setInterval(delai);
    }
}
