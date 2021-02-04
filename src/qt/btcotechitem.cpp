#include "btcotechitem.h"
#include "ui_btcotechitem.h"

btcotechitem::btcotechitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btcotechitem),
    host(""),
    name("")
{
    ui->setupUi(this);
}

void btcotechitem::setHost(QString hostStr)
{
    host = hostStr;
    ui->serverHostLabel->setText(hostStr);
}

void btcotechitem::setName(QString nameStr)
{
    name = nameStr;
    ui->serverNameLabel->setText(nameStr);
}

btcotechitem::~btcotechitem()
{
    delete ui;
}
