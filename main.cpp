#include "settingswindow.h"
#include "screenanalyzer.h"
#include "ledostalker.h"
#include <QApplication>
#include <QColor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // This is a hack to prevent some OS to pause executing the program when the window is not visible
    a.setQuitOnLastWindowClosed(false);

    // The settings window allows the user to control the program
    SettingsWindow window;
    window.show();

    // The Screen Analyzer class outputs a single color based on the image displayed on the screen
    ScreenAnalyzer analyzer;

    // LEDOS Talker communicates color from the Screen Analyzer to LEDOS
    LEDOSTalker talker;

    // Whenever the user "starts" the program, start the analysis thread
    QObject::connect( &window, SIGNAL(start()), &analyzer, SLOT(start()) );

    // And stop it when the user doesn't need it anymore
    QObject::connect( &window, SIGNAL(stop()), &analyzer, SLOT(stop()) );

    // Close the program when the window is closed
    QObject::connect( &window, SIGNAL(quit()), &a, SLOT(quit()) );

    // When a serial port is selected, update it in the LEDOS Talker instance
    QObject::connect( &window, SIGNAL(serial(QString)), &talker, SLOT(serial(QString)) );

    // Every time a color is ready to be sent pass it to the LEDOS Talker
    QObject::connect( &analyzer, SIGNAL(color(QColor)), &talker, SLOT(color(QColor)) );

    return a.exec();
}
