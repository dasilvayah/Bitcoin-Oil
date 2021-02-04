#ifndef BTCOTECHSETUP_H
#define BTCOTECHSETUP_H

#include "wallet/btcotech.h"

#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class btcotechsetup;
}

class btcotechsetup : public QDialog
{
    Q_OBJECT

public:
    explicit btcotechsetup(QWidget *parent = 0);
    ~btcotechsetup();

private:
    Ui::btcotechsetup *ui;

public Q_SLOTS:
    void reloadBtcotechServers();
    void addBtcotechServer();
    void removeBtcotechServer();
    void getinfoBtcotechServer();
    void showButtons(bool show=true);
    void showBtcotechIntro();

};

#endif // BTCOTECHSETUP_H
