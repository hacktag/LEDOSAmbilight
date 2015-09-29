#include "settingswindow.h"

#include <QLabel>
#include <QThread>
#include <QMenuBar>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSerialPortInfo>

class SettingsWindowPrivate {
public:
    SettingsWindowPrivate() {
        running = false;
    }

    QWidget *mainWidget;
    QMenu *windowsMenu;
    QMenuBar *menuBar;
    QVBoxLayout *layout;
    QHBoxLayout *hlayout;
    QLabel *serialLabel;
    QComboBox *serialDropdown;
    QPushButton *toggleButton;
    QPushButton *refreshButton;
    QList<QSerialPortInfo> serialPorts;
    bool running;
};

SettingsWindow::SettingsWindow(QMainWindow *parent) : QMainWindow(parent), d_ptr(new SettingsWindowPrivate)
{
    // Intialize a vertical layout
    d_ptr->layout = new QVBoxLayout();

    // Select Serial Connection Label
    d_ptr->serialLabel = new QLabel();
    d_ptr->serialLabel->setText("Select Serial Connection:");
    d_ptr->layout->addWidget(d_ptr->serialLabel);

    // Initialize the horizontal layout
    d_ptr->hlayout = new QHBoxLayout();

    // Serial connection Dropdown
    d_ptr->serialDropdown = new QComboBox();
    connect( d_ptr->serialDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedSerial(int)) );
    populatePorts();
    d_ptr->hlayout->addWidget(d_ptr->serialDropdown);

    // Refresh Serial Ports button
    d_ptr->refreshButton = new QPushButton();
    d_ptr->refreshButton->setText("Refresh");
    connect( d_ptr->refreshButton, SIGNAL(released()), this, SLOT(populatePorts()) );
    d_ptr->hlayout->addWidget(d_ptr->refreshButton);

    // Add the Horizontal Layout to the vertical main Layout
    d_ptr->layout->addLayout(d_ptr->hlayout);

    // Start button
    d_ptr->toggleButton = new QPushButton();
    d_ptr->toggleButton->setText("Start");
    connect( d_ptr->toggleButton, SIGNAL(released()), this, SLOT(modeToggle()) );
    d_ptr->layout->addWidget(d_ptr->toggleButton);

    // Initialize main Widget
    d_ptr->mainWidget = new QWidget();
    d_ptr->mainWidget->setLayout(d_ptr->layout);

    setCentralWidget(d_ptr->mainWidget);

    // Menu Bar
    d_ptr->menuBar = new QMenuBar();
    d_ptr->windowsMenu = new QMenu();
    d_ptr->menuBar->addMenu(d_ptr->windowsMenu);
    d_ptr->windowsMenu->setTitle("Windows");
    d_ptr->windowsMenu->addAction("Settings", d_ptr->mainWidget, SLOT(show()));

    setMenuBar(d_ptr->menuBar);
}

void SettingsWindow::closeEvent(QCloseEvent *)
{
    // Make sure the connection is stopped
    emit stop();
    QThread::msleep(50);

    // Emit the quit signal to kill the program
    emit quit();
}

void SettingsWindow::selectedSerial(int index)
{
    if( index != 0)
        emit serial( d_ptr->serialPorts[index - 1].portName() );
}

void SettingsWindow::populatePorts()
{
    disconnect( d_ptr->serialDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedSerial(int)) );
    d_ptr->serialPorts = QSerialPortInfo::availablePorts();
    d_ptr->serialDropdown->clear();
    d_ptr->serialDropdown->insertItem(0, QIcon(), "Select Port");
    for( int i = 0; i < d_ptr->serialPorts.size(); ++i )
    {
        QString name = d_ptr->serialPorts[i].portName();
        d_ptr->serialDropdown->insertItem(i + 1, QIcon(), name);
    }
    connect( d_ptr->serialDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedSerial(int)) );
}

void SettingsWindow::modeToggle()
{
    if( d_ptr->serialDropdown->currentIndex() == 0 ) return;
    d_ptr->running = ! d_ptr->running;
    d_ptr->toggleButton->setText( d_ptr->running? "Stop" : "Start" );
    d_ptr->toggleButton->setDown( d_ptr->running );

    if( d_ptr->running ) {
        emit start();
    } else {
        emit stop();
    }
}
