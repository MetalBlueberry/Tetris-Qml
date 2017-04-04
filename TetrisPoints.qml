import QtQuick 2.7

Item {
    id: base
    property int lines: 0
    property alias playerName: player.text;

    function reset(){
        base.lines = 0
    }
Column{
    Text {
        id: player

        fontSizeMode: Text.Fit
        font.pixelSize: 30
    }
    Text {
        id: lines
        text: qsTr("Lines") + " " + base.lines.toString();
        fontSizeMode: Text.Fit
        font.pixelSize: 30
    }
}
}
