#include "map.h"
#include <QLayout>
#include <QPushButton>


///---testing
#include<QFile>

Map::Map(QWidget *parent) :
    QDialog(parent)
{
    labelLat = new QLabel(tr("&Latitude:"));
    labelLon = new QLabel(tr("&Lontitude:"));
    lineEditLat = new QLineEdit;
    lineEditLon = new QLineEdit;
    labelLat->setBuddy(lineEditLat);
    labelLon->setBuddy(lineEditLon);

    mapSurface = new CameraView(this);
    mapSurface->setMaximumSize(640,480);
    mapSurface->setMinimumSize(640,480);

    removePointsButton = new QPushButton(tr("Remove points"));
    saveButton = new QPushButton(tr("Save"));


    lineEditLat->setText("52.096330");
    lineEditLon->setText("+23.756541");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(mapSurface);

    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(removePointsButton, Qt::AlignTop);
    topLeftLayout->addWidget(saveButton, Qt::AlignTop);

    topLayout->addLayout(topLeftLayout);

    QHBoxLayout *latLayout = new QHBoxLayout;
    latLayout->addWidget(labelLat);
    latLayout->addWidget(lineEditLat);

    QHBoxLayout *lonLayout = new QHBoxLayout;
    lonLayout->addWidget(labelLon);
    lonLayout->addWidget(lineEditLon);



    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addLayout(latLayout);
    inputLayout->addLayout(lonLayout);

    OK_button = new QPushButton(tr("&OK"));
    OK_button->setDefault(true);

    cancel_button = new QPushButton(tr("&Cancel"));
    cancel_button->setAutoDefault(false);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(OK_button, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancel_button, QDialogButtonBox::ActionRole);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addLayout(inputLayout);
    bottomLayout->addWidget(buttonBox);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(topLayout, 0, 0);
    mainLayout->addLayout(bottomLayout, 1, 0);

    this->setLayout(mainLayout);

    this->setWindowTitle(tr("Map"));

    connect(OK_button, SIGNAL(clicked()), this, SLOT(ok()));
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(removePointsButton, SIGNAL(clicked()),this,SLOT(removeAllPoints()));

    hasRequestSended = false;

//    mapSurface->addPoint(20,20,QColor(255,0,0),5);
//    mapSurface->addPoint(40,40,QColor(255,0,0),5);
//    mapSurface->addPoint(60,60,QColor(255,0,0),5);
//    mapSurface->addPoint(80,80,QColor(255,0,0),5);

//    maxMetalValue = 0;
//    minMetalValue = INT_MAX;

}

void Map::ok()
{
    //read labels
    QString lat = lineEditLat->text();
    QString lon = lineEditLon->text();

    if(lat.isEmpty() && lon.isEmpty())
    {
      QMessageBox ms;
      ms.setText("Nothing to show. Input is empty");
      ms.exec();
      return;
    }


    bool okLat, okLon;
    double numLat = lat.toDouble(&okLat);
    double numLon = lon.toDouble(&okLon);
    if(!okLat || !okLon)
    {
      QMessageBox ms(QMessageBox::Critical,QString("Input Error"), QString("Input is not correct!"));

      ms.exec();
      return;
    }
    this->currentCoordinates.setLat(numLat);
    this->currentCoordinates.setLon(numLon);

    //--
    double centrLat = this->currentCoordinates.getLat();
    double centrLon = this->currentCoordinates.getLon();

    topLeft.setLat(centrLat + this->diffLat);
    topLeft.setLon(centrLon - this->diffLon);

    Coordinates topSideCenter, leftSideCenter;
    topSideCenter.setLat(topLeft.getLat());
    topSideCenter.setLon(centrLon);

    leftSideCenter.setLat(centrLat);
    leftSideCenter.setLon(topLeft.getLon());


    this->distWidth = 2 * topLeft.distance(topSideCenter);
    this->distHeight = 2 * topLeft.distance(leftSideCenter);
    //--

    //QString
    url = "http://maps.googleapis.com/maps/api/staticmap?language=english&zoom=18&scale=2&size=640x480&maptype=hybrid&format=png&visual_refresh=true";
    QString queryStr = url.query();
    queryStr += QString("&center=") + lat + QString(",") + lon;
    url.setQuery(queryStr);

    imgData.clear();
    this->startRequest(url);
    OK_button->setEnabled(false);

    hasRequestSended = true;

}

void Map::cancel()
{
    this->close();
}

void Map::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(error()),this,SLOT(networkError()));

//    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
//            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void Map::httpFinished()
{
    QImage img;
    if(!img.loadFromData(imgData))
    {
        QMessageBox::information(this, "Error", "can't load image.");
    }
    mapSurface->drowImage(img);
    OK_button->setEnabled(true);


//    MetalData md1, md2,md3;
//    md1.setCoord(Coordinates(52.096421, 23.757203));
//    md1.setMetalValue(0);
//    md2.setCoord(Coordinates(52.096307, 23.756884));
//    md2.setMetalValue(10);
//    md3.setCoord(Coordinates(52.096167, 23.756566));
//    md3.setMetalValue(20);

//    drawMetalPoint(md1);
//    drawMetalPoint(md2);
//    drawMetalPoint(md3);

    reply->deleteLater();
    /*-----------------------------------
    QFile file("c:/Amanda data/data_line_2");
    if(!file.exists())
    {
        qDebug()<<"File does not exist;";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open file';";
        return;
    }

       QTextStream in(&file);
       while (!in.atEnd()) {
           QString line = in.readLine();
           this->drawMetalPoint(MetalData(line));

       }
 ----------------------------------------------*/

}
void Map::httpReadyRead()
{
    imgData.append(reply->readAll());
}

void Map::drawMetalPoint(MetalData md)
{
//    double distHoriz;
//    double distVert;
//    double centrLat = this->currentCoordinates.getLat();
//    double centrLon = this->currentCoordinates.getLon();
//    Coordinates topLeft;
//    topLeft.setLat(centrLat + this->diffLat);
//    topLeft.setLon(centrLon - this->diffLon);

//    Coordinates topSideCenter, leftSideCenter;
//    topSideCenter.setLat(topLeft.getLat());
//    topSideCenter.setLon(centrLon);

//    leftSideCenter.setLat(centrLat);
//    leftSideCenter.setLon(topLeft.getLon());


//    distHoriz = 2 * topLeft.distance(topSideCenter);
//    distVert = 2 * topLeft.distance(leftSideCenter);
    if(!hasRequestSended)return;//выходим, если запрос на получения изображения не отправлен

    //Coordinates coordOfPoint = md.getCoord();

    double lat = md.getCoord().getLat();
    double lon = md.getCoord().getLon();

    double distHoriz;
    double distVert;

    Coordinates topSide, leftSide;
    topSide.setLat(topLeft.getLat());
    topSide.setLon(lon);

    leftSide.setLat(lat);
    leftSide.setLon(topLeft.getLon());

    distHoriz = topLeft.distance(topSide);
    distVert = topLeft.distance(leftSide);

    double X = 640 * (distHoriz / this->distWidth);
    double Y = 480 * (distVert / this->distHeight);

    //QColor color = getColorByMetal( md.getMetalValue() );

    //mapSurface->addPoint(X,Y,QColor(255,0,0),5);
    mapSurface->addPoint2(X,Y,md.getMetalValue(),5);

}

void Map::removeAllPoints()
{
    mapSurface->removeAllPoints();
    //maxMetalValue = 0;
    //minMetalValue = INT_MAX;
}

void Map::networkError()
{
    QMessageBox::critical(this,QString("Error"),reply->errorString());
    OK_button->setEnabled(true);
}

//QColor Map::getColorByMetal(double metal)
//{
////    if(metal < minMetalValue) minMetalValue = metal;
////    if(metal > maxMetalValue) maxMetalValue = metal;

//    minMetalValue = 0;
//    maxMetalValue = 1024;
//    double L = maxMetalValue - minMetalValue;

//    double k;
//    if(L == 0) k = 0;
//    else k = (metal - minMetalValue)/L;

//    int red;
//    int blue;

//    int val = k * 510;
//    if(val <= 255)
//    {
//        blue = val;
//        red = 0;

//    }
//    else
//    {
//        val -= 255;
//        red = val;
//        blue = 255 - val;
//    }
//    return QColor(red, 0, blue);


//}

