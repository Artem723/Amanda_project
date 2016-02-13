#include "connectdialog.h"
#include <QtWidgets>


connectDialog::connectDialog(QWidget *parent) :
     QDialog(parent)
{
    host_name = "";
    port_num = "";

    labelHOST = new QLabel(tr("&Host addres:"));
    lineEditHOST = new QLineEdit;
    labelHOST->setBuddy(lineEditHOST);

//    labelPORT = new QLabel(tr("&Port number:"));
//    lineEditPORT = new QLineEdit;
//    labelPORT->setBuddy(lineEditPORT);

    lineEditHOST->setInputMask("000.000.000.000;");
    lineEditHOST->setText("192.168.43.55");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(labelHOST);
    topLayout->addWidget(lineEditHOST);

//    QHBoxLayout *bottomLayout = new QHBoxLayout;
//    bottomLayout->addWidget(labelPORT);
//    bottomLayout->addWidget(lineEditPORT);

    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addLayout(topLayout);
//    Layout->addLayout(bottomLayout);

    OK_button = new QPushButton(tr("&OK"));
    OK_button->setDefault(true);

    cancel_button = new QPushButton(tr("&Cancel"));
    cancel_button->setAutoDefault(false);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(OK_button, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancel_button, QDialogButtonBox::ActionRole);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(Layout, 0, 0);
    mainLayout->addWidget(buttonBox, 1, 0);

    setLayout(mainLayout);

    setWindowTitle(tr("Connect to sever"));


     connect(OK_button, SIGNAL(clicked()), this, SLOT(ok()));
     connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel()));


}

void connectDialog::ok()
{
    QMessageBox ms;
    host_name = lineEditHOST->text();
    //port_num = lineEditPORT->text();
    //qDebug()<<host_name;
    if(host_name!="...")
    {

        this->close();
    }
    else
    {
        ms.setText("Field empty");
        ms.exec();
    }

}
void connectDialog::cancel()
{
    host_name="";
    this->close();

}

QString connectDialog::getHost()
{
    return host_name;
}

