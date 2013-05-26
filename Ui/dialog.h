#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QThread>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class Dialog;
}

class Dialog;

class Worker : public QThread
{
    Q_OBJECT

protected:
    virtual void run();

signals:
    void doorOpened();
};

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void doorIsOpen();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
