#include "screenanalyzer.h"

#include <QApplication>
#include <QWebSocket>
#include <QEventLoop>
#include <QScreen>
#include <QPixmap>
#include <QDebug>
#include <QImage>
#include <QTime>


ScreenAnalyzer::ScreenAnalyzer()
    : QThread()
{
    start();
}

void ScreenAnalyzer::run()
{
    setPriority(QThread::HighestPriority);

//    QEventLoop loop;
    QTime timer;

    QWebSocket *socket = new QWebSocket();
//    loop.exec();
//    qRegisterMetaType<QAbstractSocket::SocketState>();
    socket->open( QUrl( "ws://ledespino.local/ws" ) );

//    socket->

//    QString command = QString("{\"q\":0}");
//    socket->sendTextMessage( command.toStdString().c_str() );

    QScreen *screen = QApplication::primaryScreen();

    if (screen) {
        timer.start();
        forever {
            if( QThread::currentThread()->isInterruptionRequested() ) return;
            timer.restart();

            QImage image = screen->grabWindow(0).toImage();

            int width = image.width();
            int height = image.height();


            int red = 0, green = 0, blue = 0, sample_count = 0;

            // Sum all the colors in the given range
            for ( int x = 0; x < width; ++x ) {
                for ( int y = 0; y < height; ++y) {

                    QColor color( image.pixel(x, y) );
                    red += color.red();
                    green += color.green();
                    blue += color.blue();
                    ++sample_count;

                }
            }

            // Get he avarage by dividen all the sums by the sample count
            red /= sample_count;
            green /= sample_count;
            blue /= sample_count;
//            qDebug() << red << green << blue;

            QString command = QString("{\"p\":\"%1%2%3\"}");
            command = command.arg( red, 2, 16, QChar('0'));
            command = command.arg( green, 2, 16, QChar('0'));
            command = command.arg( blue, 2, 16, QChar('0'));
            qDebug() << command;
            socket->sendTextMessage( command.toStdString().c_str() );
            socket->flush();

            msleep( qMax(20 - timer.elapsed(), 0) );
        }
    }
}
