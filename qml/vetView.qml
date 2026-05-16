import QtQuick
import QtQuick.Controls

Item {
    id: root
    Column {
        anchors.centerIn: parent
        Text {
            text: "Witaj na panelu weterynarza"
        }

        Button {
            text: "Wyloguj"
            onClicked: root.StackView.view.pop()
        }
    }
}
