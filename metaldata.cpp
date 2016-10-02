#include "metaldata.h"

MetalData::MetalData()
{
    //this->empty = true;
    this->coord.setLat(0);
    this->coord.setLon(0);
    this->metalDetectorValue = 0;
    this->precision = 0;
    return;
}

MetalData::MetalData(QString protocolMetalInfo /* Ex. 0.445$5205.7806#02345.3954#2.5 */)
{

    QStringList strList = protocolMetalInfo.split(QRegExp("[\$#]"));
    if( strList.length() < 3)
    {
        //this->empty = true;
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
        //this->empty = true;
        this->coord.setLat(0);
        this->coord.setLon(0);
        this->metalDetectorValue = 0;
        this->precision = 0;
        return;
    }
    //this->empty = false;

    if(strList.isEmpty())
        this->precision = 1;
    else
        this->precision = strList.takeFirst().toDouble();

}

MetalData::MetalData(Coordinates _coord, double _metalDetectorValue, double _precision)
{
    //this->empty = false;
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

bool MetalData::isEmpty()
{
    if((this->coord.getLat() == 0) && (this->coord.getLon() == 0))
        return true;
    else return false;
}
