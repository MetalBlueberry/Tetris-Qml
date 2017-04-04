#include "tetris.h"


Tetris::Tetris(int screen_width, int screen_height)
{
    this->display_height = screen_height;
    this->display_width = screen_width;
    display = new unsigned char [screen_height * screen_width];

    figure_x = 0;
    figure_y = 0;
    figure = new unsigned char [4*4];
}

Tetris::~Tetris()
{
    delete [] display;
    delete [] figure;
}


void Tetris::reset()
{
    memset(display,0,display_height*display_width);
    memset(figure,0,4*4);
    sendEvent(TetrisEventType::screenUpdate);
}

bool Tetris::moveLeft()
{
    if(canMoveLeft()){
        figure_x--;
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::moveRight()
{
    if( canMoveRight()){
        figure_x++;
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::moveDown()
{
    if( canMoveDown()){
        figure_y++;
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::moveUp()
{
    if(canMoveUp()) {
        figure_y--;
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::rotateLeft()
{
    unsigned char aux[4*4];
    memset(aux,0,4*4);
    if(canRotateLeft(aux)){
        memcpy(figure,aux,4*4);
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::rotateRight()
{
    unsigned char aux[4*4];
    memset(aux,0,4*4);
    if(canRotateRight(aux)){
        memcpy(figure,aux,4*4);
        sendEvent(TetrisEventType::screenUpdate);
        return true;
    }
    return false;
}

bool Tetris::canMoveLeft()
{
    return !checkColission(figure,figure_x-1,figure_y);
}

bool Tetris::canMoveRight()
{
    return !checkColission(figure,figure_x+1,figure_y);
}

bool Tetris::canMoveDown()
{
    return !checkColission(figure,figure_x,figure_y+1);
}

bool Tetris::canMoveUp()
{
    return !checkColission(figure,figure_x,figure_y-1);
}

bool Tetris::canRotateRight()
{
    unsigned char aux[4*4];
    memset(aux,0,4*4);
    return canRotateRight(aux);
}

bool Tetris::canRotateRight(unsigned char * aux)
{
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            aux[(x)*4 + (3-y) ] = figure[y*4 + x];
        }
    }
    moveToTopLeft(aux);
    return !checkColission(aux,figure_x,figure_y);


}

bool Tetris::canRotateLeft()
{
    unsigned char aux[4*4];
    memset(aux,0,4*4);
    return canRotateLeft(aux);
}

bool Tetris::canRotateLeft(unsigned char * aux)
{
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            aux[(3-x)*4 + (y) ] = figure[y*4 + x];
        }
    }
    moveToTopLeft(aux);
    return !checkColission(aux,figure_x,figure_y);
}


void Tetris::setEventHandler(Tetris::TetrisEvent handler, void * object)
{
    eventHandler = handler;
    this->object = object;
}

void Tetris::getDisplay(unsigned char * const external_display)
{
    //Copy screen to display
    /*for(int y = 0; y < display_height; y++){
        for(int x = 0; x < display_width; x++){
            external_display[getDisplayPosition(x,y)] = display[getDisplayPosition(x,y)];
        }
    }*/
    memcpy(external_display,display,display_height*display_width);

    //Copy figure to display
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            int position = getDisplayPosition(x+figure_x,y+figure_y);
            //Prevents drawing outside display;
            if(position == -1){
                continue;
            }
            external_display[position] += figure[y*4 + x ];
        }
    }
}


int Tetris::getDisplayWidth()
{
    return display_width;
}

int Tetris::getDisplayHeight()
{
    return display_height;
}

void Tetris::getFigure(unsigned char * const external_figure)
{
    memcpy(external_figure,figure,4*4);
}

void Tetris::getFigure(int number, unsigned char * const external_figure)
{
    generateNewFigure(number,external_figure);
}

int Tetris::getDisplayPosition(int x, int y)
{
    if (x >= display_width || y >= display_height || x < 0 || y < 0){
        return -1;
    }
    return y*display_width + x;
}

void Tetris::sendEvent(Tetris::TetrisEventType event)
{
    eventHandler(object,event);
}

bool Tetris::checkColission(unsigned char * const fig, int fig_x, int fig_y)
{
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            int position = getDisplayPosition(fig_x+x,fig_y+y);
            if((position == -1 && fig[y*4 + x] > 0)
                    ||
                    (display[position]>0 && fig[y*4+x] > 0 )){
                return true;
            }
        }
    }
    return false;
}

void Tetris::moveToTopLeft(unsigned char *fig)
{
    //Test X;
    bool isClear = true;
    while(isClear){
        for(int x = 0; x <4;x++){
            if(fig[0*4 + x]>0){
                isClear = false;
                break;
            }
        }
        if(isClear){
            //Displace all upwards and try again
            for(int y = 0; y < 4; y++){
                for(int x = 0; x < 4; x++){
                    if(y==3){
                        fig[y*4 +x] = 0;
                    }else{
                        fig[y*4 +x] = fig[(1+y)*4 +x];
                    }
                }
            }
        }
    }
    //Test Y
    isClear = true;
    while(isClear){
        for(int y = 0; y <4;y++){
            if(fig[y*4 + 0]>0){
                isClear = false;
                break;
            }
        }
        if(isClear){
            //Displace all leftward and try again
            for(int y = 0; y < 4; y++){
                for(int x = 0; x < 4; x++){
                    if(x==3){
                        fig[y*4 +x] = 0;
                    }else{
                        fig[y*4 +x] = fig[(y)*4 +x+1];
                    }
                }
            }
        }
    }
}

void Tetris::fixFigure()
{
    //Copy figure to display
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            int position = getDisplayPosition(x+figure_x,y+figure_y);
            //Prevents drawing outside display;
            if(position == -1){
                continue;
            }
            display[position] += figure[y*4 + x ];
        }
    }
    sendEvent(TetrisEventType::fixedFigure);
    if(figure_y<=lost_y){
        sendEvent(TetrisEventType::gameLost);
    }

}

bool Tetris::removeLine()
{
    for(int y = 0; y < display_height; y++){
        bool lineComplete = true;
        for(int x = 0; x < display_width; x++){
            if(display[getDisplayPosition(x,y)]==0){
                lineComplete = false;
                break;
            }
        }
        if(lineComplete){
            for(int y_aux= y; y_aux > 0;y_aux--){
                for(int x = 0; x < display_width; x++){
                    display[getDisplayPosition(x,y_aux)] = display[getDisplayPosition(x,y_aux-1)];
                }
            }
            sendEvent(TetrisEventType::newLine);
            sendEvent(TetrisEventType::screenUpdate);
            return true;
        }
    }
    return false;
}

void Tetris::insertLine(int position, unsigned char * const values)
{
    for(int y_aux= 0; y_aux < position ;y_aux++){
        for(int x = 0; x < display_width; x++){
            display[getDisplayPosition(x,y_aux)] = display[getDisplayPosition(x,y_aux+1)];
        }
    }
    for(int x = 0; x < display_width; x++){
        display[getDisplayPosition(x,position)] = values[x];
    }
    if(figure_y>lost_y){
        figure_y--;
    }
    sendEvent(TetrisEventType::screenUpdate);
}

void Tetris::generateNewFigure(unsigned char number)
{
    //int nume = 5;
    generateNewFigure(number,figure);
    figure_x = display_width/2 - 2;
    figure_y = 0;
    sendEvent(TetrisEventType::newFigure);
    sendEvent(TetrisEventType::screenUpdate);

}

void Tetris::generateNewFigure(unsigned char number, unsigned char *buffer)
{
    switch (number) {
    case 1:{
        int fig[4][4] = FIGURE1;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 2:{
        int fig[4][4] = FIGURE2;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 3:{
        int fig[4][4] = FIGURE3;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 4:{
        int fig[4][4] = FIGURE4;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 5:{
        int fig[4][4] = FIGURE5;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 6:{
        int fig[4][4] = FIGURE6;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    case 7:{
        int fig[4][4] = FIGURE7;
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                buffer[y*4 + x] = fig[y][x] * number;
            }
        }
        break;
    }
    default:
        break;
    }

}

