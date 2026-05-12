import QtQuick
import QtQuick.Controls

ApplicationWindow{
    visible: true
    color: "white"
    width: 100
    height: 100
    title: "SysKaWu"

    Column {
        anchors.centerIn: parent

        TextField {
            id: poleLogin
            placeholderText: "Wpisz login"
        }

        TextField {
            id: poleHaslo
            placeholderText: "Wpisz haslo"
            echoMode: TextInput.Password
        }

        Button {
            text: "Klik"
            onClicked: klinika.logIntoApp(poleLogin.text, poleHaslo.text)
        }

        Text {
            id: komunikat
            text: ""
        }
    }

    Connections {
        target: klinika
        function onLoginSignal(){
            if (klinika.loginSuccess){
                komunikat.text = "Witaj, " + klinika.user["login"]
            } else {
                komunikat.text = "Wprowadzone hasło lub login są nieprawidłowe"
            }
        }
    }
}
