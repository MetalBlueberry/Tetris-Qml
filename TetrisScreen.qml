import QtQuick 2.7
import Tetris 1.0

Rectangle{
    // anchors.centerIn: parent
    id: base
    // property int effectiveWidth: 200
    // property int effectiveHeigth: 200
    property int displayRatio: tetris.getDisplayHeight()/tetris.getDisplayWidth()
    // width: (Math.min(effectiveWidth , effectiveHeigth/displayRatio))
    // height: (Math.min(effectiveWidth * displayRatio , effectiveHeigth))
    border.color: "black"
    border.width: 2
    property alias tetris: tetris
    property alias timer: timeOut

    function moveDown(){
        if(!timeOut.running) return;
        if(!tetris.moveDown()){
            tetris.fixFigure()
            tetris.generateNewFigure(Math.floor(Math.random()*7)+1)
            if(timeOut.running){
            timeOut.restart();
            }
            return true;
        }
        return false;
    }
    function moveLeft() {
        if(!timeOut.running) return;
        tetris.moveLeft()
    }
    function moveRight() {
        if(!timeOut.running) return;
        tetris.moveRight()
    }
    function rotateRight(){
        if(!timeOut.running) return;
        tetris.rotateRight()
    }
    function reset(){
        tetris.reset()
        tetris.generateNewFigure(Math.floor(Math.random()*7)+1)
    }
    TCore{
        id: tetris
        anchors.fill: parent
        anchors.margins: parent.border.width
        Component.onCompleted: {
            tetris.setup(10,25);
            tetris.reset()
            tetris.generateNewFigure(Math.floor(Math.random()*7)+1)
        }
        onTetrisEvent: {
            if(event==TCore.FixedFigure){
                var moreLines = true;
                while(moreLines){
                    moreLines = tetris.removeLine();
                }
            }
        }
    }
    Timer{
        id:timeOut
        interval: 250
        repeat: true
        running: false
        onTriggered:{
            base.moveDown();
        }
    }
}
