import QtQuick
import QtQuick.Controls

Item {
    id: root
    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Witaj na panelu administratora - Magazyn Leków"
            font.pixelSize: 16
            font.bold: true
        }
        Row {
            spacing: 5
            TextField { id: inputName; placeholderText: "Nazwa leku"; width: 120 }
            TextField { id: inputStock; placeholderText: "Ilość"; width: 60; validator: IntValidator{bottom: 0} }
            TextField { id: inputUnit; placeholderText: "Jedn. (np. ml)"; width: 80 }
            TextField { id: inputBatch; placeholderText: "Partia"; width: 80 }

            Button {
                text: "Dodaj"
                onClicked: {

                    klinika.addMedicine(inputName.text, parseInt(inputStock.text), inputBatch.text, inputUnit.text)
                    inputName.text = ""; inputStock.text = ""; inputUnit.text = ""; inputBatch.text = "";
                    listaLekow.model = klinika.getMedicines()
                }
            }
        }
        Button {
            text: "Pobierz listę leków"
            onClicked: listaLekow.model = klinika.getMedicines()
        }

        ListView {
            id: listaLekow
            width: 550
            height: 200
            clip: true
            model: []

            delegate: Row {
                spacing: 15
                Text { text: "Lek: " + modelData["name"] }
                Text { text: "Stan: " + modelData["stock"] + " " + modelData["unit"] }

                Button {
                    text:"Usuń"
                    onClicked:{
                        klinika.deleteMedicine(modelData["id"])
                        listaLekow.model=klinika.getMedicines()
                    }
                }
            }
        }

        Button {
            text: "Wyloguj"
            onClicked: root.StackView.view.pop()
        }
    }
}
