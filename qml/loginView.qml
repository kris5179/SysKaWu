import QtQuick
import QtQuick.Controls

Item {
    id: root
    Component.onCompleted: console.log("loginView załadowany")
    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {id: poleLogin; placeholderText: "Login" }
        TextField {id: poleHaslo; placeholderText: "Hasło"; echoMode: TextInput.Password }
        Button {
            text: "Zaloguj"
            onClicked: klinika.logIntoApp(poleLogin.text, poleHaslo.text)
        }
        Text { id: komunikat }
    }
    Connections {
        target: klinika
        function onLoginSignal() {
            if (klinika.loginSuccess && klinika.user.id > 0) {
                if (klinika.user["privilege"] == 0) {
                    root.StackView.view.push(Qt.resolvedUrl("adminView.qml"))
                } else if (klinika.user["privilege"] == 1) {
                    root.StackView.view.push(Qt.resolvedUrl("vetView.qml"))
                } else if (klinika.user["privilege"] == 2) {
                    root.StackView.view.push(Qt.resolvedUrl("nurseView.qml"))
                } else{
                    komunikat.text = klinika.user["errMsg"]
                }
            }
        }
    }
}
