import QtQuick 2.0

//ListView {
//    spacing: 10
//    width: 200; height: 250
//    model: postgroup
//    delegate: Rectangle {
//        width: 200
//        height: 50
//        color: "yellow"
//    }
//}


Item {
    id:background
    width: parent.width
    height: parent.height
    Rectangle {
        width: parent.width
        height: 100
        color: "red"
        id:plate_title
        Text{
            objectName: "title"
            anchors.centerIn: parent
            text:plate_c.get_title()
            color:"black"
        }
    }
    ListView {
        model: postgroup
        spacing:10
        height: parent.height
        x:10
        y:110
        delegate: Rectangle{
            id:id
            width: 800
            height: 100
            color: "yellow"
            anchors.verticalCenter: parent
            Text{
                anchors.centerIn: parent
                text:title
            }
        }

    }


}

