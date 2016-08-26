#include "map.h"
#include <QLayout>
#include <QPushButton>

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



    lineEditLat->setText("52.096330");
    lineEditLon->setText("+23.756541");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(mapSurface);

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

    mapSurface->addPoint(20,20,QColor(255,0,0),5);
    mapSurface->addPoint(40,40,QColor(255,0,0),5);
    mapSurface->addPoint(60,60,QColor(255,0,0),5);
    mapSurface->addPoint(80,80,QColor(255,0,0),5);

}

void Map::ok()
{
    //read labels
    QString lat = lineEditLat->text();
    QString lon = lineEditLon->text();
    //QString
    url = "http://maps.googleapis.com/maps/api/staticmap?language=english&zoom=18&scale=2&size=640x480&maptype=hybrid&format=png&visual_refresh=true";
    QString queryStr = url.query();
    queryStr += QString("&center=") + lat + QString(",") + lon;
    url.setQuery(queryStr);

    imgData.clear();
    this->startRequest(url);
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

    reply->deleteLater();
}
void Map::httpReadyRead()
{
    imgData.append(reply->readAll());
}

void Map::drawMetalPoint(point pnt)
{

}

