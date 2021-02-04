#ifndef BTCOTECHINIT_H
#define BTCOTECHINIT_H

#include <QDialog>

namespace Ui {
class BtcoTechInit;
}

class BtcoTechInit : public QDialog
{
    Q_OBJECT

public:
    explicit BtcoTechInit(QWidget *parent = 0);
    ~BtcoTechInit();
    QString GetServers();
    void ShowBtcotechIntro(bool exitAfter = true);

private:
    Ui::BtcoTechInit *ui;
};

#endif // BTCOTECHINIT_H
