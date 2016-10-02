
#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFile>
#include "cameraview.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>
#include <QMessageBox>
#include <QByteArray>
#include <QUrlQuery>
#include <QColor>

#include "metaldata.h"
class QNetworkReply;


class Map : public QDialog
{
    Q_OBJECT
private:
    CameraView* mapSurface;
    QLabel* labelLat,*labelLon;
    QLineEdit *lineEditLat;
    QLineEdit *lineEditLon;
    QPushButton *OK_button;
    QPushButton *cancel_button;
    QPushButton *removePointsButton;
    QPushButton *saveButton;
    QDialogButtonBox *buttonBox;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;


    QByteArray imgData;

    static const double diffLat = 0.000774;
    static const double diffLon = 0.001531;

    Coordinates currentCoordinates;

//    double minMetalValue;
//    double maxMetalValue;

    Coordinates topLeft;

    double distWidth;
    double distHeight;

    bool hasRequestSended;

    //QColor getColorByMetal(double metal);


public:
    explicit Map(QWidget *parent = 0);
    void drawMetalPoint(MetalData md);




signals:

public slots:
    void ok();
    void cancel();

    void startRequest(QUrl);
    void httpFinished();
    void httpReadyRead();

    void removeAllPoints();
    void networkError();


};

#endif // MAP_H
