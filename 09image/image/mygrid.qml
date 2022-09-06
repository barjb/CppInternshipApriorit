import QtQuick 2.15
import QtQml
import Qt.labs.folderlistmodel 2.3

GridView{
    id: imagesGrid
    anchors.fill: parent
    cellHeight: 200
    cellWidth: 200
    model: FolderListModel{
        id: folderModel
        folder: fdiag.folder
        showDirs: false
        nameFilters: ["*.png","*.jpg"]
    }
    delegate: imageDelegator
    Component {
        id: imageDelegator
        Image{
            id: image
            fillMode: Image.PreserveAspectFit
            width: 120
            height: 120
            source: fdiag.folder + '/' + fileName
            MouseArea{
                anchors.fill: parent
                onClicked: ()=>{
                               image.width = (image.width === 120 ? imagesGrid.width : 120);
                               image.height = (image.height === 120 ? imagesGrid.height : 120);
                           }
            }
        }
    }
}
