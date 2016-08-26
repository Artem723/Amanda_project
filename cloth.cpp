#include "cloth.h"
#include<QPainter>
#include<QPen>
#include<QFont>
#include<QDebug>
#include<QColor>
#include<cmath>


Cloth::Cloth(QWidget *parent) :
    QWidget(parent)
{
    map_scale = 1;
    max_metal = 0;
    min_metal = 1024;
    dot_size = 5;
    shift_x = 0;
    shift_y = 0;
    zero_dots=0;
    hdop = 10;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    img = new QImage(6000, 4000, QImage::Format_ARGB32);
    img->fill(QColor(255,255,255,255));

    isSaving = false;

}
void Cloth::setHDOP(int _hdop)
{
    if(_hdop>=1 && _hdop<=10)
       { hdop = _hdop;repaint();}

}

void Cloth::addDot(point _dot)
{

     dots.push_back(_dot);
    repaint();
}

void Cloth::clear()
{
    dots.clear();
    zero_dots=0;
    max_metal = 0;
    min_metal = 1024;

    update();


}

void Cloth::setShiftX(int sh)
{
    shift_x=sh;
}

void Cloth::setShiftY(int sh)
{
    shift_y=sh;
}

QColor Cloth::getColor(int _metal)
{
    QColor clr;
    if(_metal > max_metal)max_metal = _metal;
    else if(_metal < min_metal)min_metal = _metal;

    int L = max_metal - min_metal;/*
    qDebug()<<"max_metal "<< max_metal;
    qDebug()<<"min_metal "<< min_metal;*/
    double k;
    if(L==0)k=0;
    else k = (_metal - min_metal)/(double)L;
//    qDebug()<<"L "<< L;
//qDebug()<<"_color "<< _color;
//    qDebug()<<"k "<< k;
    int red = 255*k;
    int blue = 255 - 255*k;
    clr.setRgb(red,0,blue);
    //qDebug()<<"red: "<<red<<"; blue"<<blue;

    return clr;
}

void Cloth::setDotSize(int _dot_size)
{
    dot_size = _dot_size;
}

void Cloth::setMapScale(double _scale)
{
    map_scale = _scale;
}

double Cloth::measure(const point *d1, const point *d2)
{
    const double R = 6378.137; //Радиус земли(км)
    const double PI = 3.14159265359;
    double dLat = (d2->lat - d1->lat)*PI / 180;
    double dLon = (d2->lon - d1->lon)*PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) +
    cos(d1->lat * PI / 180) * cos(d2->lat * PI / 180) *
    sin(dLon/2) * sin(dLon/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R*c;
    return d * 1000;

}
double Cloth::measure2(const point *d1, const point *d2)
{
    const double R = 6378.137; //Радиус земли(км)
    const double PI = 3.14159265359;
    double dLat = (d2->lat - d1->lat)*PI / 180;
    double dLon = (d2->lon - d1->lon)*PI / 180;
    double f1 = d1->lat *PI/180;
    double f2 = d2->lat *PI/180;

//    double a = sin(dLat/2) * sin(dLat/2) +
//    cos(d1->lat * PI / 180) * cos(d2->lat * PI / 180) *
//    sin(dLon/2) * sin(dLon/2);
    double y = sqrt(pow(cos(f2)*sin(dLon),2) + pow(cos(f1)*sin(f2)-sin(f1)*cos(f2)*cos(dLon),2));
    double x = sin(f1)*sin(f2)+cos(f1)*cos(f2)*cos(dLon);
    double c = atan2(y, x);
    double d = R*c;
    return d * 1000;//in metres

}
QVector<point> Cloth::getDots()
{
    return dots;
}

void Cloth::paintEvent(QPaintEvent *) {
    int xM = width();
    int yM = height();

    int img_XM = 6000;
    int img_YM = 4000;

    int startX;
    int startY;
    QPainter p_out(img);//for out image



    if(isSaving)
    {

        p_out.setRenderHint(QPainter::Antialiasing,true);
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);

   // p.setPen(QPen(Qt::red,5,Qt::SolidLine));

    double L=0;//суммарное расстояние
     double L2=0;//расстояние между первой и последней точкой
    if(!dots.isEmpty())
    {

        QPen pen;
       // QColor clr;
        qDebug()<<"paintEvent";
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(dot_size);
        //pen.setColor(Qt::red);
        p.setPen(pen);

        //p.setPen(QPen(Qt::red,5,Qt::SolidLine));
        startX = dots.at(0).X - shift_x;
        startY = dots.at(0).Y - shift_y;
       // qDebug()<<"shift_x "<<shift_x;
        pen.setColor(this->getColor(dots.at(0).metal)) ;


        //pen.setColor(clr);
        p.setPen(pen);
        if(isSaving)p_out.setPen(pen);
        ////!!!p.drawPoint(xM*0.5+shift_x,yM*0.5+shift_y);
       // p.drawPoint(startX,startY);

        int tempX;
        int tempY;

        int img_tempX;
        int img_tempY;
       // int num_zero = 0;
        point dotPrevius, dotCurr;

        dotCurr.lat = dotCurr.lon = 0;
        dotPrevius.lat=dots.at(0).lat;
        dotPrevius.lon=dots.at(0).lon;

        if(dots.size()>1)
            L2 = measure(&dots.at(0),&dots.back());

        p.setPen(QPen(Qt::red,5,Qt::SolidLine));
        if(isSaving)p_out.setPen(QPen(Qt::red,5,Qt::SolidLine));
        for(int i=0;i<dots.size();i++)
        {
                if(dots.at(i).precision > hdop)
                {
                    continue;
                }

                pen.setColor(this->getColor(dots.at(i).metal)) ;


                p.setPen(pen);
                if(isSaving)p_out.setPen(pen);
                tempX = (dots.at(i).X-startX)*map_scale+xM*0.5;
                tempY = (dots.at(i).Y-startY)*map_scale+yM*0.5;

                img_tempX = (dots.at(i).X-startX)*map_scale+img_XM*0.5;
                img_tempY = (dots.at(i).Y-startY)*map_scale+img_YM*0.5;
                // qDebug()<<"tempX: "<<tempX<<"; tempY"<<tempY<<"; (dots.at(i).X-startX)"<<(dots.at(i).X-startX)<<"; xM*0.5"<<(xM*0.5);
                p.drawPoint(tempX,tempY);
                if(isSaving)p_out.drawPoint(img_tempX,img_tempY);
                //подсчёт суммарно пройденного расстояния
                dotCurr.lat=dots.at(i).lat;
                dotCurr.lon=dots.at(i).lon;
                if(i==0)continue;
                L+= this->measure(&dotPrevius,&dotCurr);
                dotPrevius = dotCurr;


        }


    }

    ///

    QFont text;
    QPen pen;
    pen.setColor(Qt::black);
    text.setPixelSize(15);
    text.setFamily(QString("Courier"));
    p.setFont(text);
    if(isSaving)p_out.setFont(text);


    p.setPen(pen);
    p.drawText(0,15,QString("Path length is ") + QString::number(L));
    p.drawText(0,32,QString("Dist. between first & last is ") + QString::number(L2));

    if(isSaving)
    {
        p_out.setPen(pen);
        p_out.drawText(0,15,QString("Path length is ") + QString::number(L));
        p_out.drawText(0,32,QString("Dist. between first & last is ") + QString::number(L2));
    }
    ///

    p.setPen(palette().dark().color());
    p.setBrush(Qt::NoBrush);
    p.drawRect(QRect(0, 0, width() - 1, height() - 1));
    p.drawLine(0,yM*0.5,xM,yM*0.5);
    p.drawLine(xM*0.5,0,xM*0.5,yM);

    if(isSaving)
    {
        p_out.setPen(palette().dark().color());
        p_out.setBrush(Qt::NoBrush);
        p_out.drawRect(QRect(0, 0, img_XM - 1, img_YM - 1));
        p_out.drawLine(0,img_YM*0.5,img_XM,img_YM*0.5);
        p_out.drawLine(img_XM*0.5,0,img_XM*0.5,img_YM);

        isSaving =false;
    }

}

void Cloth::imgClear()
{//чистим изображение заполняя его белым прямоугольником
    QPainter p_img(img);
    p_img.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    p_img.drawRect(0,0,6000,4000);
}

bool Cloth::saveAsImage(QString path)
{
   isSaving = true;
   repaint();
   img->save(path);
   this->imgClear();
   return true;
}
