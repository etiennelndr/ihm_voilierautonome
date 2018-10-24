import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0

ApplicationWindow{
    visible : true
    title: "voilier"
    width : 500
    height : 600

    header :ToolBar{
        RowLayout{
            anchors.fill : parent
            ToolButton {
                text : "Open"
                onClicked : fileDialog.open()
            }
        }
     }

     FileDialog {
        id : fileDialog
        title:"Please choose a file"
        folder : shortcuts.home
     }

     TextArea {
         id : TextEdit
         anchors.fill:
     }
 }



/*
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Voilier Autonome")
}

*/

/*
Rectangle {
    id: simpleButton
    color: "grey"
    width: 150; height: 75

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: "button label"
    }
}

*/




/*

NOVA VERSAO


/*

/*
// MAPPING - qml file - fichier test

Item {
    PositionSource {
        active : true
        onPositionChanged : {
           // map.center = position.coordinate ;
        }
    }

    Map {
           id : map
           anchors.fill : parent
           plugin : Plugin {name : "osm"}
           center : QtPositioning.coordinates (59.930243, 10.714635)
           zoomLevel : 15

           MapQuickItem{
               color : "green"
               center : QtPositioning.coordinates (59.930243, 10.714635)
               radius : 1000

           MapQuickItem{
                   id : marker
                   coordinate: QtPositioning.coordinates (59.930243, 10.714635)
                   /*sourceItem : Image {
                   id : image
                       // source : "file:marker.png"
                    }*/
                   anchorPoint.x = image.width/2
                   anchorPoint.x = image.height
            }
         MapItemView {
            model : routeModel
            delegate : Component {
                               MapRoute {
                                    route : routeData
                                    line.color : "blue"
                        line.widht : 4
                                }
                         }
             }

        }

         GeocodeModel {
            plugin : map.plugin
            query : "Sandakervein 116, Oslo"
                onLocationsChanged : {
                    if(count)
                        marker.coordinate = get(0).coordinate;
                }
                Component.onCompleted : update()
         }

          RouteModel {
             id : routeModel
             plugin : map.plugin
             query : RouteQuery { id: RouteQuery}
             Component.onCompleted: {
                        routeQuery.addWaypoint(QtPositioning.coordinates(52.520663, 13,416552));
                        routeQuery.addWayPoint(QtPositioning.coordinates(52.430663, 13,416552));
                        update();

                    }
          }

 /* set one INITIAL MAP AREA
  *
 import QtQuick 2.6
 import Esri.ArcGISRuntime 100.4

 Rectangle {
     width: 800
     height: 600

     // Create MapView that contains a Map with the Imagery Basemap
     MapView {
         id: mapView
         anchors.fill: parent
         Map {
             BasemapImagery {}
             initialViewpoint: viewpoint
         }
     }

     // Create the intial Viewpoint
     ViewpointExtent {
         id: viewpoint
         extent: Envelope {
             xMin: -12211308.778729
             yMin: 4645116.003309
             xMax: -12208257.879667
             yMax: 4650542.535773
             spatialReference: SpatialReference { wkid: 102100 }
         }
     }
 }

  */


/*
 *
 * import QtQuick 2.6
import Esri.ArcGISRuntime 100.4
import Esri.ArcGISExtras 1.1

Rectangle {
    width: 800
    height: 600

    property real scaleFactor: System.displayScaleFactor
    property string statusText

    // Create MapView that contains a Map
    MapView {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: statusBar.top
        }

        Map {
            // Set the initial basemap to Streets
            BasemapStreets {}

            // Set up signal handler to determine load status
            // Load status should be loaded once the basemap successfully loads
            onLoadStatusChanged: {
                switch (loadStatus) {
                case Enums.LoadStatusFailedToLoad:
                    statusText = "Failed to Load";
                    break;
                case Enums.LoadStatusLoaded:
                    statusText = "Loaded";
                    break;
                case Enums.LoadStatusLoading:
                    statusText = "Loading...";
                    break;
                case Enums.LoadStatusNotLoaded:
                    statusText = "Not Loaded";
                    break;
                case Enums.LoadStatusUnknown:
                    statusText = "Unknown";
                    break;
                default:
                    statusText = "Unknown";
                    break;
                }
            }
        }
    }

    Rectangle {
        id: statusBar
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 30 * scaleFactor
        color: "lightgrey"
        border {
            width: 0.5 * scaleFactor
            color: "black"
        }

        Text {
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 10 * scaleFactor
            }
            text: "Map Load Status: %1".arg(statusText)
            font.pixelSize: 14 * scaleFactor
        }
    }
}
*/


/* SET MAP INITIAL  REFERENCE
 *
 * import QtQuick 2.6
 import Esri.ArcGISRuntime 100.4

 Rectangle {
     width: 800
     height: 600

     MapView {
         anchors.fill: parent
         wrapAroundMode: Enums.WrapAroundModeDisabled

         Map {
             id: map
             // Specify the SpatialReference
             spatialReference: SpatialReference { wkid:54024 }
         }
     }

     Basemap {
         id: basemap
         ArcGISMapImageLayer {
             url: "https://sampleserver6.arcgisonline.com/arcgis/rest/services/SampleWorldCities/MapServer"
         }
     }

     Component.onCompleted: {
         map.basemap = basemap;
     }
 }
*/
