import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 600
    height: 500
    title: "SysKaWu"
    Component.onCompleted: console.log("ApplicationWindow załadowany")

    StackView {
        id: stos
        anchors.fill: parent
        initialItem: "loginView.qml"
        Component.onCompleted: console.log("Stack view załadowany, initial item: ", initialItem)
    }
}
