#ifndef BTCOTECHITEM_H
#define BTCOTECHITEM_H

#include <QWidget>

namespace Ui {
class btcotechitem;
}

class btcotechitem : public QWidget
{
    Q_OBJECT

public:
    explicit btcotechitem(QWidget *parent = 0);
    ~btcotechitem();
    void setHost(QString hostStr);
    void setName(QString nameStr);

private:
    Ui::btcotechitem *ui;
    QString host;
    QString name;
};

#endif // BTCOTECHITEM_H
