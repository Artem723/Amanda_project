#include "coordinates.h"


Coordinates::Coordinates()
{
    latitude = 0.0;
    longitude = 0.0;
}

Coordinates::Coordinates(double lat,double lon)
{
    if(lat<=0 || lat>90){qDebug() << "Error: Invalid input in \'Coordinates\' constructor: argument must be in the range from 0 to 90.\nInput number is "<< lat <<";";exit(1);}
    this->latitude = lat;

    if(lon<=0 || lon>180){qDebug() << "Error: Invalid input in \'Coordinates\' constructor: argument must be in the range from 0 to 180.\nInput number is "<< lon <<";";exit(1);}
    this->longitude = lon;
}

double Coordinates::getLat()
{
    return this->latitude;
}

double Coordinates::getLon()
{
    return this->longitude;
}

void Coordinates::setLat(double lat)
{
    if(lat<=0 || lat>90){qDebug() << "Error: Invalid input in \'setLat\' function: argument must be in the range from 0 to 90.\nInput number is "<< lat <<";";exit(1);}
    this->latitude = lat;
}

void Coordinates::setLon(double lon)
{
    if(lon<=0 || lon>180){qDebug() << "Error: Invalid input in \'setLon\' function: argument must be in the range from 0 to 180.\nInput number is "<< lon <<";";exit(1);}
    this->longitude = lon;
}

void Coordinates::setLat(QString latStr)
{
    bool gradLatConvIsOk, minLatConvIsOk;
    double grad_lat = latStr.left(2).toDouble(&gradLatConvIsOk);
    double min_lat = latStr.right(latStr.size()-2).toDouble(&minLatConvIsOk);

    grad_lat += min_lat/60;
    if(grad_lat<=0 || grad_lat>90 || !gradLatConvIsOk || !minLatConvIsOk)
    {
        qDebug() << "Error: Invalid input in \'setLat(QString)\' function: input string is not correct!!! ";exit(1);
    }
    this->latitude = grad_lat;
}

void Coordinates::setLon(QString lonStr)
{
  bool gradLonConvIsOk, minLonConvIsOk;
  double grad_lon = lonStr.left(3).toDouble(&gradLonConvIsOk);
  double min_lon = lonStr.right(lonStr.size()-3).toDouble(&minLonConvIsOk);

  grad_lon += min_lon/60;

  if(grad_lon<=0 || grad_lon>180 || !gradLonConvIsOk || !minLonConvIsOk)
  {
      qDebug() << "Error: Invalid input in \'setLon(QString)\' function: input string is not correct!!! ";exit(1);
  }
  this->longitude = grad_lon;

}

double Coordinates::distance(Coordinates c)
{
    const double R = 6378.137; //Радиус земли(км)
    const double PI = 3.14159265359;

    double dLat = (c.latitude - this->latitude)*PI / 180;
    double dLon = (c.longitude - this->longitude)*PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) +
    cos(this->latitude * PI / 180) * cos(c.latitude * PI / 180) *
    sin(dLon/2) * sin(dLon/2);

    double C = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R*C;
    return d * 1000;//in metres

}


