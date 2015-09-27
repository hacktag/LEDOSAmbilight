#ifndef LEDOSTALKER_H
#define LEDOSTALKER_H

#include <QSerialPort>
#include <QColor>

class LEDOSTalkerPrivate;

class LEDOSTalker : public QObject
{
    Q_OBJECT
public:
    explicit LEDOSTalker(QObject *parent = 0);

public slots:
    void serial(QString);
    void color(QColor);

private:
    LEDOSTalkerPrivate *d_ptr;
};

#endif // LEDOSTALKER_H
