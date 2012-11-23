import QtQuick 1.1

Rectangle
{
    id: aboutTab;
    anchors.fill: parent;
    color: "#00000000";

    Flickable
    {
        id: flickArea;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        width: parent.width - verticalScroll.width - 20
        contentWidth: parent.width;
        contentHeight: content.height;
        flickableDirection: Flickable.VerticalFlick;
        clip: true;

        Rectangle
        {
            id: content;
            anchors.top: parent.top;
            height: childrenRect.height;
            anchors.left:parent.left;
            width: flickArea.width;
            color: "#00000000";

            Text
            {
                id: helpText
                anchors.top: parent.top;
                anchors.horizontalCenter: parent.horizontalCenter;
                font.pixelSize: 14;
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                text: qsTr("Mena'an v1.0");
            }

            Separator
            {
                id:centerSeparator;
                anchors.top: helpText.bottom;
                anchors.topMargin: 2;
                anchors.horizontalCenter: parent.horizontalCenter;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }

            Text
            {
                id: authorsText1
                anchors.top: centerSeparator.top;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Mena'an created by Inteima.x2 Team:");
            }

            Text
            {
                id: authorsText2
                anchors.top: authorsText1.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                text: qsTr("Interima. ix2\
                            <br>Interima. Cry\
                            <br>Interima. InMay\
                            <br>Interima. Cemetery\
                            <br>Interima. Tombstone\
                            <br>Interima. BlueIceScream\
                            <br>Interima. The Heavy Rain");

            }

            Text
            {
                id: mailText1
                anchors.top: authorsText2.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("If you have a suggestion send it to e-mail:");
            }

            Text
            {
                id: mailText2
                anchors.top: mailText1.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                text: qsTr("Interima.x2@gmail.com");

            }


            Text
            {
                id: licenseText1
                anchors.top: mailText2.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Mena'an license:");
            }

            Text
            {
                id: licenseText2
                anchors.top: licenseText1.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                text: qsTr("GNU/GPL version 3");

            }

            Separator
            {
                id:bottomSeparator;
                anchors.top: licenseText2.bottom;
                anchors.topMargin: 8;
                anchors.horizontalCenter: parent.horizontalCenter;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: warrantyText
                anchors.top: bottomSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                color: "#FFFFFF";
                text: qsTr("THE SOFTWARE IS PROVIDED 'AS IS',\
WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, \
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. \
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE \
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION \
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF \
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
            }

        }
    }

    VScrollBar
    {
        id: verticalScroll;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        position: flickArea.visibleArea.yPosition;
        pageSize: flickArea.visibleArea.heightRatio;
    }
}
