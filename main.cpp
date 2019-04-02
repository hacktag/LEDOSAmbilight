#include "screenanalyzer.h"
#include <QApplication>
#include <QThread>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // The Screen Analyzer class outputs a single color based on the image displayed on the screen
    ScreenAnalyzer analyzer;
//    QThread::sleep(10);
    execv( "/usr/bin/mpv", argv );
    return 0;;
}
