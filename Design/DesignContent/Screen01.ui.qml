

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import Design

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        id: label
        text: qsTr("Hello Design")
        font.family: Constants.font.family
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: Constants.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: Constants.backgroundColor
                from: "#2294c6"
            }
        }
    }

    Image {
        id: bg
        x: -128
        y: -8
        width: 2100
        height: 1124
        source: "images/bg.png"
        fillMode: Image.PreserveAspectFit

        Image {
            id: logo
            x: 163
            y: 48
            source: "images/logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: acc
            x: 372
            y: -324
            width: 1734
            height: 1844
            source: "images/acc.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: abri1
        x: -16
        y: 324
        width: 70
        height: 100
        source: "images/abri (1).png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "clicked"

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}
