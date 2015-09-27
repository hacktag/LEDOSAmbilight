#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    screenshotLabel = new QLabel;
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    screenshotLabel->setMinimumSize(240, 160);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(screenshotLabel);
    setLayout(mainLayout);

    frameCapture = new QTimer(this);
    connect(frameCapture, SIGNAL(timeout()), this, SLOT(shootScreen()));
    frameCapture->setInterval(5);
    frameCapture->start();

    effect = new QGraphicsOpacityEffect(this->screenshotLabel);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent * /* event */)
{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
}

void MainWindow::shootScreen()
{
    originalPixmap = QPixmap(); // clear image for low memory situations
                                // on embedded devices.
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
        originalPixmap = screen->grabWindow(0);
    updateScreenshotLabel();
}



void MainWindow::updateScreenshotLabel()
{
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));
}
