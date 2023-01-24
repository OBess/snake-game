import QtQuick 2.15

Item {
    id: root

    Palette { id: palette }

    property color backgroud: palette.background
    property font font: Qt.font({
        family: "Arial",
        pointSize: 20,
        bold: true
    })

    property int bestScore: 0
    property int currentScore: 0

    height: 60

    Rectangle {
        id: backgroundItem

        anchors.fill: parent

        color: backgroud

        Row {
            anchors.fill: parent
            spacing: 2
            leftPadding: 10

            Image {
                anchors.verticalCenter: parent.verticalCenter
                width: 50
                height: 50

                source: "qrc:/resources/images/cup.png"
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                font: root.font
                color: palette.cup

                text: root.bestScore
            }

            Item {
                width: 30
                height: 30
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                width: 50
                height: 50

                source: "qrc:/resources/images/goal.png"
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                font: root.font
                color: "white"

                text: root.currentScore
            }
        }
    }
}
