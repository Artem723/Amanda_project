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
#include "cloth.h"
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
    QDialogButtonBox *buttonBox;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;


    QByteArray imgData;


public:
    explicit Map(QWidget *parent = 0);
    void drawMetalPoint(point);




signals:

public slots:
    void ok();
    void cancel();

    void startRequest(QUrl);
    void httpFinished();
    void httpReadyRead();


};

#endif // MAP_H
