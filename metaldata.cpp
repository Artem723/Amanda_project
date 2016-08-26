#include "metaldata.h"

MetalData::MetalData()
{
    this->empty = true;
    this->coord.setLat(0);
    this->coord.setLon(0);
    this->metalDetectorValue = 0;
    this->precision = 0;
    return;
}

//MetalData::MetalData(QString protocolMetalInfo /* Ex. 0.445$5205.7806#02345.3954#2.5 */)
//{
//    QStringList pars, pars_gps;

//    QString metal;
//    QString gps;
//    // QString str_XY;

//    /**/QString str;
//    double lat_d,lon_d;//в градусах
//    QString grad_lat="";
//    QString min_lat="";
//    QString grad_lon="";
//    QString min_lon="";
//    QString latit="";
//    QString lontit="";

//    point p;
//    // int metal_num;
//    //qDebug() << in.readLine();

//    if(str.isEmpty())
//    {
//        p.X=0;
//        p.Y=0;
//        p.metal=0;
//        p.precision=0;
//        p.lat=0;
//        p.lon=0;
//        return p;
//    }
//    pars = str.split('$');
//    metal = pars.first();
//    // metal_num = metal.toDouble();
//    //qDebug()<<metal_num;
//    gps = pars.back();
//    //qDebug()<<gps;
//    pars_gps = gps.split('#');

//    if(pars_gps.at(0).isEmpty() || pars_gps.size()<3)
//    {
//        p.X=0;
//        p.Y=0;
//        p.metal=0;
//        p.precision=0;
//        p.lat=0;
//        p.lon=0;
//        return p;
//    }
//    //////Достаём из протокола координаты северной широты и восточной долготы

//    latit = pars_gps.at(0);
//    lontit = pars_gps.at(1);

//    grad_lat = latit.left(2);
//    min_lat = latit.right(latit.size()-2);

//    lat_d = grad_lat.toDouble() + min_lat.toDouble()/60;


//    grad_lon = lontit.left(3);
//    min_lon = lontit.right(lontit.size()-3);

//    lon_d = grad_lon.toDouble() + min_lon.toDouble()/60;

//    p.lat = lat_d;
//    p.lon = lon_d;
//    qDebug()<<"p.lat="<<p.lat;
//    qDebug()<<"p.lon="<<p.lon;
//    ////////

//    p.X = (pars_gps.takeFirst()).toDouble()*10000;
//    p.Y = (pars_gps.takeFirst()).toDouble()*10000;
//    p.metal = metal.toDouble();
//    if(!pars_gps.isEmpty())
//        p.precision = (pars_gps.takeFirst()).toDouble();
//    else
//        p.precision=1;


//    //            if(p.X==0 && p.Y ==0)
//    //            {
//    //                zero_dots++;
//    //                continue;
//    //            }
//    return p;

//    // qDebug()<<"p.X= "<<p.X;
//    // qDebug()<<"p.Y= "<<p.Y;

//}

MetalData::MetalData(QString protocolMetalInfo /* Ex. 0.445$5205.7806#02345.3954#2.5 */)
{

    QStringList strList = protocolMetalInfo.split(QRegExp("[\$#]"));
    if( strList.length() < 3)
    {
        this->empty = true;
        this->coord.setLat(0);
        this->coord.setLon(0);
        this->metalDetectorValue = 0;
        this->precision = 0;
        return;
    }
    bool metalConverIsOk;
    this->metalDetectorValue = strList.takeFirst().toDouble(&metalConverIsOk);
    this->coord.setLat(strList.takeFirst());
    this->coord.setLon(strList.takeFirst());
    if( !metalConverIsOk)
    {
        this->empty = true;
        this->coord.setLat(0);
        this->coord.setLon(0);
        this->metalDetectorValue = 0;
        this->precision = 0;
        return;
    }
    this->empty = false;

    if(strList.isEmpty())
        this->precision = 1;
    else
        this->precision = strList.takeFirst().toDouble();

}

MetalData::MetalData(Coordinates _coord, double _metalDetectorValue, double _precision)
{
    this->empty = false;
    this->coord = _coord;

    this->metalDetectorValue = _metalDetectorValue;
    this->precision = _precision;

}

void MetalData::setCoord(Coordinates _coord)
{
    this->coord = _coord;
}

void MetalData::setMetalValue(double _metalDetectorValue)
{
    this->metalDetectorValue = _metalDetectorValue;
}

void MetalData::setPrecision(double _precision)
{
    this->precision = _precision;
}

Coordinates MetalData::getCoord()
{
    return coord;
}

double MetalData::getMetalValue()
{
    return metalDetectorValue;
}

double MetalData::getPrecision()
{
    return precision;
}
