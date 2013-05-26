#include "dialog.h"
#include "ui_dialog.h"

#include <stdio.h>
#include <algorithm>

#include <QThread>
#include <QMessageBox>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Worker *worker = new Worker();
    connect(worker, SIGNAL(doorOpened()), this, SLOT(doorIsOpen()), Qt::QueuedConnection);

    worker->start();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::doorIsOpen()
{
    show();
}

void Worker::run()
{
    QTcpSocket socket(this);
    socket.connectToHost("10.0.10.100", 23);
    socket.waitForConnected();
    // Write some data to start the stream
    socket.write("\n");

    const int doorDist = 343;
    const int margin = 20;
    const size_t samplesCount = 10;

    char msg[100];
    list<int> samples;
    while(socket.isValid())
    {
        if (socket.waitForReadyRead() && socket.readLine(msg, 100) > 0)
        {
            int sample;
            sscanf(msg, "%d\n", &sample);
            samples.push_back(sample);
            while (samples.size() > samplesCount)
                samples.pop_front();

            float sum = 0;
            for (auto& it: samples)
            {
                sum += it;
            }
            int avg = sum / samples.size();

            if (abs(avg-doorDist) > margin)
            {
                emit(doorOpened());
            }
        }
        else
        {
            QThread::usleep(5000);
        }
    }
}
