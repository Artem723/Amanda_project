#include "cameraview.h"

CameraView::CameraView(QWidget *parent) :
    QWidget(parent)
{

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

void CameraView::paintEvent(QPaintEvent *)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    QRect rect(0,0,this->width(),this->height());
    p.drawImage(rect,image);
    MapPoint point;
    foreach (point, points)
    {
        pen.setColor(point.color);
        pen.setWidth(point.size);
        p.setPen(pen);
        p.drawPoint(point.x,point.y);


    }

}
