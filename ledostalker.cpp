#include "ledostalker.h"

#include <QThread>
#include <QDebug>

class LEDOSTalkerPrivate {
public:
    LEDOSTalkerPrivate() {
        serial = NULL;
    }

    ~LEDOSTalkerPrivate() {
        if( serial != NULL && serial->isOpen() )
            serial->close();
    }

    QSerialPort *serial;
};


LEDOSTalker::LEDOSTalker(QObject *parent) : d_ptr(new LEDOSTalkerPrivate)
{
}

void LEDOSTalker::serial(QString portName)
{
    if( d_ptr->serial != NULL && d_ptr->serial->portName() != portName && d_ptr->serial->isOpen() )
        d_ptr->serial->close();

    d_ptr->serial = new QSerialPort(portName);
    d_ptr->serial->setBaudRate(115200);
    d_ptr->serial->open(QSerialPort::WriteOnly);
    QThread::msleep(1000);
    d_ptr->serial->write("effect color\n");
    d_ptr->serial->flush();
}

void LEDOSTalker::color(QColor color)
{
    QString command = QString("b%1%2%3\n");
    command = command.arg(color.red(), 2, 16, QChar('0'));
    command = command.arg(color.green(), 2, 16, QChar('0'));
    command = command.arg(color.blue(), 2, 16, QChar('0'));
//    qDebug() << command;
    d_ptr->serial->write( command.toStdString().c_str() );
    d_ptr->serial->flush();
}

