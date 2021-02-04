#include "btcotechinit.h"
#include "ui_btcotechinit.h"
#include "net.h"
#include "util.h"
#include "skinize.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QUrl>

BtcoTechInit::BtcoTechInit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BtcoTechInit)
{
    ui->setupUi(this);
}

BtcoTechInit::~BtcoTechInit()
{
    delete ui;
}

void BtcoTechInit::ShowBtcotechIntro(bool exitAfter)
{
    BtcoTechInit btcotechinit;
    btcotechinit.setStyleSheet(Skinize());

    if(!btcotechinit.exec())
    {
        if(exitAfter)
            exit(0);
        else
            return;
    }

    QString ServersToAdd = btcotechinit.GetServers();
    QStringList ss = ServersToAdd.split('\n');

    for (int i = 0; i < ss.size(); ++i){
        QString Server = ss.at(i);
        QString strippedServer = Server.remove(' ');
        if(strippedServer != "")
        {
            WriteConfigFile("addanonserver",strippedServer.toStdString());
        }
    }
}

QString BtcoTechInit::GetServers()
{
    return ui->plainTextEdit->toPlainText();
}
