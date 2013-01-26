import QtQuick 1.1

Rectangle
{
    id: frame;

    radius: 4;
    smooth: true;
    border.color: "#838EA8";

    gradient: Gradient
              {
                  GradientStop { position: 0.0; color: "#87BBC6E0" }
                  GradientStop { position: 1.0; color: "#00BBC6E0" }
              }
}

