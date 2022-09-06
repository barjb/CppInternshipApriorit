import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import Qt.labs.folderlistmodel 2.2

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Images Browser")
    RowLayout{
        id: topBar
        width: parent.width
        height: 100
        Button{
            text: "Open images folder"
            onClicked: fdiag.open()
        }
        FolderDialog{
            id: fdiag
            acceptLabel: "Open"

        }
        ComboBox{
            width: 200
            model: ListModel{
                ListElement{ text: "list"}
                ListElement{ text: "table"}
                ListElement{ text: "pathview"}
            }
            onCurrentIndexChanged: () => {
                                       if(model.get(currentIndex).text === "list")
                                       myLoader.source = "mylist.qml";
                                       else if(model.get(currentIndex).text === "table")
                                       myLoader.source = "mygrid.qml"
                                       else
                                       myLoader.source = "mypathview.qml"
                                   }
        }
        z: 1
    }
    Loader{
        id: myLoader
        width: mainWindow.width
        height: mainWindow.height-topBar.height
        anchors.top: topBar.bottom
        source: ""
    }
}
