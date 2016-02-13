#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QWidget>

#include <QDialog>


QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class connectDialog :   public QDialog
{
    Q_OBJECT
public:
    explicit connectDialog(QWidget *parent = 0);
    QString getHost();

signals:

public slots:
    void ok();
    void cancel();
private:
    QLabel *labelHOST;
    QLineEdit *lineEditHOST;

    QLabel *labelPORT;
    QLineEdit *lineEditPORT;

    QPushButton *OK_button;
    QPushButton *cancel_button;

    QDialogButtonBox *buttonBox;

    QString host_name;
    QString port_num;

};

#endif // CONNECTDIALOG_H
