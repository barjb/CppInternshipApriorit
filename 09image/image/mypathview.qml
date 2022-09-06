import QtQuick 2.15
import Qt.labs.folderlistmodel 2.3

PathView{
    id: imagesPathView
    anchors.fill: parent
    model: FolderListModel{
        id: folderModel
        folder: fdiag.folder
        showDirs: false
        nameFilters: ["*.png","*.jpg"]
    }
    delegate: pathdelegate
    path: Path{
        startX: 120; startY:140
        PathQuad{ x:520; y:140; controlX: 320; controlY: 280}
    }
    Component{
        id: pathdelegate
        Column{
            id: wrapper
            opacity: PathView.isCurrentItem ? 1: 0.5
            Image{
                id: image
                width: 128
                height:  128
                source: fdiag.folder + '/' + fileName
                MouseArea{
                    anchors.fill: parent
                    onClicked: ()=>{
                                   image.width = (image.width === 120 ? imagesPathView.width : 120);
                                   image.height = (image.height === 120 ? imagesPathView.height : 120);
                               }
                }
            }
        }
    }
}
