#include "draw.h"
#include "controller.h"

Draw::Draw(QWidget *parent) : QLabel(parent)
{
    m_lost=false;
}

Draw::~Draw(){

}

void Draw::setController(Controller* ptr)
{
    m_controller=ptr;
}

void Draw::setLost(bool val)
{
    m_lost=val;
}

void Draw::draw()
{
    //dessin un jeux classique
    m_image = QImage(600, 600, QImage::Format_RGB32);

    if(!m_controller->m_snake.getPerdu()){
        for(int i=0; i<600; i++){
            for(int j=0; j<600; j++){
                m_image.setPixel(i, j, qRgb(255, 255, 255));
            }
        }

        unsigned long taille = m_controller->m_snake.getCorps().size();
        for(unsigned long i = 0;  i < taille; i++){
            if(i==taille-1){
                this->drawCarre(SIZE*m_controller->m_snake.getCorps()[i].getX(), SIZE*m_controller->m_snake.getCorps()[i].getY(), SIZE, 2);
            }else{
                this->drawCarre(SIZE*m_controller->m_snake.getCorps()[i].getX(), SIZE*m_controller->m_snake.getCorps()[i].getY(), SIZE, 1);
            }
        }

        this->drawCarre(SIZE*m_controller->m_cible.getCible().getX(), SIZE*m_controller->m_cible.getCible().getY(), SIZE, 0);
    }else{
        for(int i=0; i<600; i++){
            for(int j=0; j<600; j++){
                m_image.setPixel(i, j, qRgb(0, 0, 0));
            }
        }
    }

    this->setPixmap(QPixmap::fromImage(m_image));
}

void Draw::drawCarre(int x, int y, int taille, int couleur) //créé un carré, utilisé pour "déssiner" le serpent et sa cible
{
    //couleur : 0 pour rouge (cible), 1 pour vert clair (corps), 2 pour
    int a = 0;
    int b = 0;

    switch(couleur){
        case 0 :
          a=255;
          b=0;
        break;
        case 1 :
          a=185;
          b=255;
        break;
        case 2 :
          a = 125;
          b = 255;
        break;
    }

    for(int i=0; i<taille-1; i++){
        for(int j=0; j<taille-1; j++){
            m_image.setPixel(x+i, y+j, qRgb(a, b, 0));
        }
    }
}
