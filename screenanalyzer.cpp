#include "screenanalyzer.h"

#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QDebug>
#include <QImage>
#include <QTime>

class ScreenAnalyzerPrivate {
public:
    QTime timer;
};

ScreenAnalyzer::ScreenAnalyzer() : QThread(), d_ptr(new ScreenAnalyzerPrivate)
{

}

void ScreenAnalyzer::run()
{
    setPriority(QThread::HighestPriority);
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        d_ptr->timer.start();
        forever {
            if( QThread::currentThread()->isInterruptionRequested() ) return;

            d_ptr->timer.restart();

            QImage image = screen->grabWindow(0).toImage();

            int width = screen->geometry().width();
            int height = screen->geometry().height();

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

            emit color( QColor(red, green, blue, 255) );

            msleep( qMax(20 - d_ptr->timer.elapsed(), 0) );
        }
    }
}

void ScreenAnalyzer::stop()
{
    requestInterruption();
}
