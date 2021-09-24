// main.cpp
#include <QtCore>
#include <QDebug>
#include "bledevicefinder.hpp"
#include "bledevice.hpp"
#include "bleserviceinfo.hpp"
#include "uartservice.hpp"

class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {
        this->devFinder = new BLEDeviceFinder();
        this->dev = nullptr;
    }

public slots:
    void startScan()
    {
        // Do processing here
        QObject::connect(this->devFinder, SIGNAL(stateChanged()), this, SLOT(stateChangedFinder()));
        QTimer::singleShot(0, this->devFinder, SLOT(startScan()));

    }

    void stateChangedFinder()
    {
        qDebug() << this->devFinder->state();

        if (this->devFinder->state() == (BLEDeviceFinder::ScanSucceeded)){
            qDebug() << "Get Device ";
     this->dev = qobject_cast<BLEDevice *>(this->devFinder->findByName("IMU_"));

//            this->dev = qobject_cast<BLEDevice *>(this->devFinder->findbyAdress("D1:4E:6E:E7:0F:DE"));

            qDebug() << "Device found " << this->dev->name() << " " << this->dev->address();
            if (this->dev != nullptr){
                BLEServiceInfo info;
                info.loadDefinitions(":/bleservices.json");
                this->nus = new UARTService(info);
                this->nus->setDevice(this->dev);

                QTimer::singleShot(0, this->dev, SLOT(establishConnection()));
            }
        }
    }



signals:
    void finished();

private :
    BLEDeviceFinder* devFinder;
    BLEDevice* dev;
    UARTService* nus;
};


#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(startScan()));

    return a.exec();
}
