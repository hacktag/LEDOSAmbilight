#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

class SettingsWindowPrivate;

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QMainWindow *parent = 0);

signals:
    void start();
    void stop();
    void serial(QString);

private slots:
    void selectedSerial(int);
    void populatePorts();
    void modeToggle();

private:
    SettingsWindowPrivate *d_ptr;
};

#endif // SETTINGSWINDOW_H
