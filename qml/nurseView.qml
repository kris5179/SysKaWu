import QtQuick
import QtQuick.Controls

Item {
    id: root
    Column {
        anchors.centerIn: parent
        Text {
            text: "Witaj na panelu pielęgniarki"
        }

        Button {
            text: "Wyloguj"
            onClicked: root.StackView.view.pop()
        }
    }
}
