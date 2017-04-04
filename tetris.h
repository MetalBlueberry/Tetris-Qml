/*
    This library helps you to manage a tetris game.
    Copyright (C) 2017  (MetalBlueberry) MetalBlueberry@gmail.com



    tetris.h is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    tetris.h is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TETRIS_H
#define TETRIS_H

#include "figures.h"

#ifdef ARDUINO
    #include <arduino.h>
#else
    #include <cstring>
#endif

class Tetris
{

public:
    enum TetrisEventType : int{
        gameLost,
        newLine,
        newFigure,
        fixedFigure,
        screenUpdate,
    };
    typedef void(*TetrisEvent)(void*,TetrisEventType);
    Tetris(int display_width, int display_height);
    ~Tetris();

    // resets the board
    void reset();

    //Move commands, returns false if the figure can't make the movement
    bool moveLeft();
    bool moveRight();
    bool moveDown();
    bool moveUp();
    bool rotateLeft();
    bool rotateRight();


    //cheack commands, returns false if the figure can't make the movement
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    bool canMoveUp();
    bool canRotateRight();
    //store the data in aux
    bool canRotateRight(unsigned char *aux);
    bool canRotateLeft();
    //store the data in aux
    bool canRotateLeft(unsigned char *aux);


    //function to call when an event occurs
    void setEventHandler(TetrisEvent handler, void *object);

    /*Saves the display in external_display array
     * Example:
     * unsigned char disp[tetris->getDisplayHeight()][tetris->getDisplayWidth()];
     * tetris->getDisplay(&disp[0][0]);
     * //get the screen position with disp[y][x]
     */
    void getDisplay(unsigned char * const external_display);
    int getDisplayWidth();
    int getDisplayHeight();
    /* Saves the current figure in external_figure array
     * Example:
     * unsigned char fig[4][4];
     * tetris->getFigure(&fig[0][0]);
     * //fig[y][x]
     */
    void getFigure(unsigned char * const external_figure);
    /* Saves the figure number in external_figure array
     * Example:
     * unsigned char fig[4][4];
     * //figure Nº 5, all the figures are defined in figures.h
     * tetris->getFigure(5,&fig[0][0]);
     * //fig[y][x]
     */
    void getFigure(int number,unsigned char * const external_figure);


    //creates new figure and position it at the top
    void generateNewFigure(unsigned char number);
    //prints the current figure to the screen and allows you create a new one
    void fixFigure();
    //remove the first line found from the top and return true if succeed
    bool removeLine();
    //insert one line at position
    void insertLine(int position, unsigned char * const values);

    //you lose the game if the figure is fixed at this value or lower
    int lost_y = 0;

private:
    int display_width;
    int display_height;
    unsigned char * display;
    int figure_x;
    int figure_y;
    unsigned char * figure;

    int getDisplayPosition(int x, int y);
    void sendEvent(TetrisEventType event);
    TetrisEvent eventHandler;
    void *object;

    bool checkColission(unsigned char * const fig, int fig_x, int fig_y);
    void moveToTopLeft(unsigned char * fig);

    void generateNewFigure(unsigned char number,unsigned char *buffer);
};

#endif // TETRIS_H
