import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import App 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: "Touchstone Visualizer"

    GraphController {
        id: graphController
    }

    FileDialog {
        id: fileDialog
        title: "Select Touchstone file"
        onAccepted: {
            graphController.loadFile(fileDialog.fileUrl)
        }
    }

    Button {
        text: "Open File"
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: fileDialog.open()
    }

    CustomGraph {
        id: graph
        anchors.fill: parent
        anchors.margins: 40
    }

    MessageDialog {
        id: errorDialog
        title: "Error"
    }

    Connections {
        target: graphController

        function onErrorOccurred(message) {
            errorDialog.text = message
            errorDialog.open()
        }

        function onDataUpdated(points) {
            graph.points = points
        }
    }
}
