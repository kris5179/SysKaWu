import QtQuick
import QtQuick.Controls

ApplicationWindow{
    visible: true
    color: "white"
    width: 500
    height: 500
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
            text: "Zaloguj"
            onClicked: klinika.logIntoApp(poleLogin.text, poleHaslo.text)
        }

        Text {
            id: komunikat
            text: ""
        }

        // ?
        TextField {
            id: poleIdZwierzaka
            placeholderText: "Wpisz id zwierzaka"
            validator: IntValidator { bottom: 1 }
        }

        Button {
            text: "Wyświetl zwierzaka"
            onClicked: listaZwierzat.model = klinika.getAnimals(parseInt(poleIdZwierzaka.text))
        }

        ListView {
            id: listaZwierzat
            width: parent.width
            height: 300
            model: []
            delegate: Row {
                spacing: 10
                Text { text: modelData["name"]}
                Text { text: modelData["species"]}
                Text { text: modelData["breed"]}
            }
        }
    }


    Connections {
        target: klinika
        function onLoginSignal(){
            if (klinika.loginSuccess){
                komunikat.text = "Witaj, " + klinika.user["login"]
            } else {
                komunikat.text = klinika.user["errMsg"] 
            }
        }
    }
}
