import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Tetris 1.0

ApplicationWindow {
    id: base
    visible: true
    width: 408
    height: 502
    title: qsTr("Tetris")
    GridLayout{
        id: gameGrid
        columns: 2
        anchors.fill: parent
        TetrisPoints{
            height: base.height/4
            id: p1Points
            Layout.column: 0
            Layout.row: 0
            playerName: "Player 1"
        }
        TetrisScreen{
            id: p1
            Layout.fillWidth: true
            Layout.fillHeight: true

            tetris.onTetrisEvent: {
                console.log("event p1"+ event);
                if(event==TCore.NewLine){
                    p2.tetris.insertLine(p2.tetris.getDisplayHeight()-1,[0,1,0,1,0,1,0,1,0,1]);
                    p1Points.lines++
                }
                if(event === TCore.GameLost){
                    pauseScreen.end(p2Points.playerName + " Wins");
                }
            }
            Layout.column: 0
            Layout.row: 1
        }
        TetrisPoints{
            height: base.height/4
            id: p2Points
            Layout.column: 1
            Layout.row: 0
            playerName: "Player 2"
        }
        TetrisScreen{
            id: p2
            Layout.fillWidth: true
            Layout.fillHeight: true
            tetris.onTetrisEvent: {
                console.log("event p2"+ event);
                if(event==TCore.NewLine){
                    p1.tetris.insertLine(p1.tetris.getDisplayHeight()-1,[0,1,0,1,0,1,0,1,0,1]);
                    p2Points.lines++
                }
                if(event === TCore.GameLost){
                    pauseScreen.end(p1Points.playerName + " Wins");
                }
            }
            Layout.column: 1
            Layout.row: 1
        }

        Keys.onPressed: {
            if(event.isAutoRepeat) return;

            if(event.key === Qt.Key_Left){
                p1.moveLeft()
            }
            if(event.key === Qt.Key_Right){
                p1.moveRight()
            }
            if(event.key === Qt.Key_Down){
                p1.moveDown()
            }
            if(event.key === Qt.Key_Up){
                p1.rotateRight()
            }

            if(event.key === Qt.Key_A){
                p2.moveLeft()
            }
            if(event.key === Qt.Key_S){
                p2.moveDown()
            }
            if(event.key === Qt.Key_D){
                p2.moveRight()
            }
            if(event.key === Qt.Key_W){
                p2.rotateRight()
            }
            if(event.key === Qt.Key_O){
                p1.tetris.insertLine(p1.tetris.getDisplayHeight()-1,[0,1,0,1,0,1,0,1,0,1]);
                p2.tetris.insertLine(p2.tetris.getDisplayHeight()-1,[0,1,0,1,0,1,0,1,0,1]);
            }
            if(event.key === Qt.Key_Escape){
                pauseScreen.pause();
            }
        }
    }


    Rectangle{
        id: pauseScreen
        anchors.fill: parent
        color: "#aa000000"
        function reset(){

            p2.reset()
            p1.reset()
            p1Points.reset()
            p2Points.reset()
            p1.timer.start()
            p2.timer.start()

            continueButton.visible = true;
            pauseScreen.visible = false;

            gameGrid.forceActiveFocus()

        }

        function resume(){
            pauseScreen.visible = false;
            p1.timer.start()
            p2.timer.start()

            gameGrid.forceActiveFocus()
        }

        function pause(){
            pauseScreen.visible = true
            p1.timer.stop()
            p2.timer.stop()
        }

        function end(winer){
            continueButton.visible = false;
            pauseScreen.visible = true
            p1.timer.stop()
            p2.timer.stop()
            winerText.text = winer
        }
        Column{
            anchors.centerIn: parent
            spacing: 5
            Text{
                id: winerText
                text: "play"
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                font.pixelSize: 25
            }
            Button{
                id: resetButton
                text: "Reset"
                onClicked: pauseScreen.reset()
            }

            Button{
                id: continueButton
                text: "Continue"
                visible: false
                onClicked: pauseScreen.resume()
            }
        }
    }


}
