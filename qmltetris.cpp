#include "qmltetris.h"
#include <QDebug>


QmlTetris::QmlTetris() : QmlTetris(nullptr)
{

}

QmlTetris::QmlTetris(QQuickItem *parent): QQuickPaintedItem(parent)
  ,tetris(new Tetris(10,25))
  ,colors(new QMap<int,QColor>())
{
    tetris->setEventHandler(&QmlTetris::eventHandlerFunction,this);
    colors->insert(1,Qt::green);
    colors->insert(2,Qt::blue);
    colors->insert(3,Qt::lightGray);
    colors->insert(4,Qt::black);
    colors->insert(5,Qt::gray);
    colors->insert(6,Qt::red);
    colors->insert(7,Qt::yellow);
}

void QmlTetris::paint(QPainter *painter)
{
    unsigned char disp[tetris->getDisplayHeight()][tetris->getDisplayWidth()];
    tetris->getDisplay(&disp[0][0]);
    painter->setRenderHint(QPainter::Antialiasing);
    for(int y = 0 ; y < tetris->getDisplayHeight();y++){
        for(int x = 0 ; x < tetris->getDisplayWidth();x++){

            if(disp[y][x] > 0){
            painter->fillRect(x*width()/tetris->getDisplayWidth(),
                              y*height()/tetris->getDisplayHeight(),
                              width()/tetris->getDisplayWidth(),
                              height()/tetris->getDisplayHeight(),
                              colors->value(disp[y][x]));
            painter->setPen(Qt::black);
            painter->setBrush(Qt::NoBrush);
            painter->drawRect(x*width()/tetris->getDisplayWidth(),
                              y*height()/tetris->getDisplayHeight(),
                              width()/tetris->getDisplayWidth(),
                              height()/tetris->getDisplayHeight()
                              );
            }
        }
    }
}

void QmlTetris::eventHandlerFunction(void *object, Tetris::TetrisEventType event)
{
    QmlTetris *item = static_cast<QmlTetris*>(object);
    if(event == Tetris::TetrisEventType::screenUpdate){
        item->update();
    }else{
        emit item->tetrisEvent((TetrisEventType)event);
    }
}

void QmlTetris::setup(int display_width, int display_height)
{
   delete tetris;
   tetris = new Tetris(display_width,display_height);
   tetris->setEventHandler(&QmlTetris::eventHandlerFunction,this);
}

bool QmlTetris::moveLeft()
{
    return tetris->moveLeft();
}

bool QmlTetris::moveRight()
{
    return tetris->moveRight();
}

bool QmlTetris::moveDown()
{
    return tetris->moveDown();
}

bool QmlTetris::rotateLeft()
{
    return tetris->rotateLeft();
}

bool QmlTetris::rotateRight()
{
   return tetris->rotateRight();
}

void QmlTetris::reset()
{
    tetris->reset();
}

void QmlTetris::generateNewFigure(unsigned char number)
{
    tetris->generateNewFigure(number);
}

void QmlTetris::fixFigure()
{
    tetris->fixFigure();
}

bool QmlTetris::removeLine()
{
    return tetris->removeLine();
}

void QmlTetris::insertLine(int position,  QList<int> values)
{
    unsigned char temp_values[tetris->getDisplayWidth()];
    for(int x = 0; x < tetris->getDisplayWidth();x++){
        temp_values[x] = (unsigned char)values.at(x);
    }
    tetris->insertLine(position,temp_values);
}

int QmlTetris::getDisplayWidth()
{
    return tetris->getDisplayWidth();
}

int QmlTetris::getDisplayHeight()
{
    return tetris->getDisplayHeight();
}
