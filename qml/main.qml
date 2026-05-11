import QtQuick
import QtQuick.Controls

ApplicationWindow{
    visible: true
    color: "white"
    width: 100
    height: 100
    title: "SysKaWu"

    Text {
        id: tekst1
        anchors.centerIn: parent
        text: "Hello, World"
    }

    Button {
        text: "Klik"
        onClicked:{
            klinika.logIntoApp()
        }
    }
}
