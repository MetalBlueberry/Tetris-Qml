#ifndef QMLTETRIS_H
#define QMLTETRIS_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "tetris.h"


class QmlTetris : public QQuickPaintedItem
{
    Q_OBJECT
public:
    enum TetrisEventType : int{
        GameLost,
        NewLine,
        NewFigure,
        FixedFigure,
        ScreenUpdate,
    };
    Q_ENUM(TetrisEventType)
    QmlTetris();
    explicit QmlTetris(QQuickItem *parent);

    void paint(QPainter *painter);
    static void eventHandlerFunction(void *object,Tetris::TetrisEventType event);

    Q_INVOKABLE void setup(int display_width, int display_height);
    Q_INVOKABLE bool moveLeft();
    Q_INVOKABLE bool moveRight();
    Q_INVOKABLE bool moveDown();
    Q_INVOKABLE bool rotateLeft();
    Q_INVOKABLE bool rotateRight();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void generateNewFigure(unsigned char number);
    Q_INVOKABLE void fixFigure();
    Q_INVOKABLE bool removeLine();
    Q_INVOKABLE void insertLine(int position, QList<int> values);
    Q_INVOKABLE int getDisplayWidth();
    Q_INVOKABLE int getDisplayHeight();


public slots:

signals:
    void tetrisEvent(TetrisEventType event);
private:
    Tetris *tetris;
    QMap<int,QColor> *colors;
};

#endif // QMLTETRIS_H
