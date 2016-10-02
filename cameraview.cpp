#include "cameraview.h"

CameraView::CameraView(QWidget *parent) :
    QWidget(parent)
{
    minValue = INT_MAX;
    maxValue = 0;
}
void CameraView::drowImage(QImage &_image)
{
    this->image = _image;
    this->update();

}

void CameraView::addPoint(int x, int y, QColor color, int size)
{
    MapPoint pnt;
    pnt.x = x;
    pnt.y = y;
    pnt.color = color;
    pnt.size = size;
    points.push_back(pnt);
    this->update();

}

void CameraView::addPoint2(int x, int y, double value, int size)
{
    MapPoint2 pnt;
    pnt.x = x;
    pnt.y = y;
    pnt.value = value;
    pnt.size = size;
    points2.push_back(pnt);
    this->repaint();

}

void CameraView::removeAllPoints()
{
    points.resize(0);
    points2.resize(0);

    maxValue = 0;
    minValue = INT_MAX;

    this->update();
}

QColor CameraView::getColorByValue(double value)
{
    if(value < minValue) minValue = value;
    if(value > maxValue) maxValue = value;

//    minValue = 0;
//    maxValue = 1024;
    double L = maxValue - minValue;

    double k;
    if(L == 0) k = 0;
    else k = (value - minValue)/L;

    int red;
    int blue;

    int val = k * 510;
    if(val <= 255)
    {
        blue = val;
        red = 0;

    }
    else
    {
        val -= 255;
        red = val;
        blue = 255 - val;
    }
    return QColor(red, 0, blue);


}

void CameraView::paintEvent(QPaintEvent *)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    QRect rect(0,0,this->width(),this->height());
    p.drawImage(rect,image);
    MapPoint point;
    MapPoint2 point2;
    foreach (point, points)
    {
        pen.setColor(point.color);
        pen.setWidth(point.size);
        p.setPen(pen);
        p.drawPoint(point.x,point.y);


    }

    foreach (point2, points2)
    {
        pen.setColor(getColorByValue(point2.value));
        pen.setWidth(point2.size);
        p.setPen(pen);
        p.drawPoint(point2.x,point2.y);


    }

}



