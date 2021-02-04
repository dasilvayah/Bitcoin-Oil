#include "btcotechsetup.h"
#include "btcotechitem.h"
#include "ui_btcotechsetup.h"
#include "net.h"
#include "skinize.h"
#include "util.h"

#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <QtNetwork>
#include <QWidget>

btcotechsetup::btcotechsetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::btcotechsetup)
{
    ui->setupUi(this);
    ui->getInfoButton->setVisible(false);
    ui->removeButton->setVisible(false);

    ui->saveButton->setVisible(false);

    this->setWindowTitle("Btcotech");

    connect(ui->addNewButton,SIGNAL(clicked()),this,SLOT(addBtcotechServer()));
    connect(ui->getInfoButton,SIGNAL(clicked()),this,SLOT(getinfoBtcotechServer()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeBtcotechServer()));
    connect(ui->serversListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showButtons()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(close()));

    reloadBtcotechServers();
}

btcotechsetup::~btcotechsetup()
{
    delete ui;
}

void btcotechsetup::addBtcotechServer()
{
    QString serverToAdd = ui->addServerText->text();

    if(serverToAdd == "")
        return;

    serverToAdd = serverToAdd.remove(' ').remove('\n').remove('\r').remove('\t');

    LOCK(cs_vAddedAnonServers);
    std::vector<std::string>::iterator it = vAddedAnonServers.begin();
    for(; it != vAddedAnonServers.end(); it++)
        if (serverToAdd.toStdString() == *it)
            break;

    WriteConfigFile("addanonserver", serverToAdd.toStdString());
    if (it == vAddedAnonServers.end())
        vAddedAnonServers.push_back(serverToAdd.toStdString());

    ui->addServerText->clear();

    reloadBtcotechServers();
}

void btcotechsetup::reloadBtcotechServers()
{
    ui->serversListWidget->clear();

    const std::vector<std::string>& confAnonServers = mapMultiArgs["-addanonserver"];

    BOOST_FOREACH(std::string confAnonServer, confAnonServers) {
        ui->serversListWidget->addItem(QString::fromStdString(confAnonServer));
    }

    BOOST_FOREACH(std::string vAddedAnonServer, vAddedAnonServers) {
        ui->serversListWidget->addItem(QString::fromStdString(vAddedAnonServer));
    }
}

void btcotechsetup::showBtcotechIntro()
{
    setWindowIcon(QIcon(":icons/bitcoinoil"));
    setStyleSheet(Skinize());

    ui->saveButton->setVisible(true);

    exec();
}

void btcotechsetup::removeBtcotechServer()
{
    QString serverToRemove = ui->serversListWidget->currentItem()->text();

    if(serverToRemove == "")
        return;

    QMessageBox::StandardButton btnRetVal = QMessageBox::question(this, tr("Remove Btcotech server"),
        tr("You are about to remove the following Btcotech server: ") + "<br><br>" + serverToRemove + "<br><br>" + tr("Are you sure?"),
        QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);

    if(btnRetVal == QMessageBox::Cancel)
        return;

    LOCK(cs_vAddedAnonServers);
    std::vector<std::string>::iterator it = vAddedAnonServers.begin();

    RemoveConfigFile("addanonserver", serverToRemove.toStdString());
    for(; it != vAddedAnonServers.end(); it++)
        if (serverToRemove == QString::fromStdString(*it))
            break;

    if (it != vAddedAnonServers.end())
    {
      vAddedAnonServers.erase(it);
      QMessageBox::critical(this, windowTitle(),
          tr("Removed."),
          QMessageBox::Ok, QMessageBox::Ok);
    }

    showButtons(false);
    reloadBtcotechServers();
}

void btcotechsetup::showButtons(bool show)
{
    ui->getInfoButton->setVisible(show);
    ui->removeButton->setVisible(show);
}

void btcotechsetup::getinfoBtcotechServer()
{
    QString serverToCheck = ui->serversListWidget->currentItem()->text();

    if(serverToCheck == "")
        return;

    QStringList server = serverToCheck.split(':');

    if(server.length() != 2)
        return;

    try {
        Btcotech *btcotech = new Btcotech();
        UniValue data = btcotech->GetServerInfo(serverToCheck.toStdString());

        QMessageBox::information(this, windowTitle(),
            tr("Btcotech server") + "<br><br>" +  tr("Address: ") + serverToCheck + "<br>" + tr("Min amount: ") + QString::number(data["min_amount"].get_real()) + " <br>" + tr("Max amount: ") + QString::number(data["max_amount"].get_real()) + "<br>" + tr("Tx fee: ") + QString::number(data["transaction_fee"].get_real()) + "%",
            QMessageBox::Ok, QMessageBox::Ok);
    }
    catch(const std::runtime_error &e)
    {
        QMessageBox::warning(this, tr("Btcotech server"),
                             "<qt>Could not get info:<br/><br/>" +
                             tr(e.what())+"</qt>");
    }
}
