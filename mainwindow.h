#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsEffect>

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void shootScreen();

private:
    void updateScreenshotLabel();
    QPixmap originalPixmap;
    QLabel *screenshotLabel;
    QVBoxLayout *mainLayout;
    QTimer *frameCapture;
    QGraphicsOpacityEffect * effect;
};

#endif // MAINWINDOW_H
