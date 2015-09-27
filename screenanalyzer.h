#ifndef SCREENANALYZER_H
#define SCREENANALYZER_H

#include <QThread>
#include <QColor>

class ScreenAnalyzerPrivate;

class ScreenAnalyzer : public QThread
{
    Q_OBJECT
public:
    ScreenAnalyzer();

protected:
    void run();

signals:
    void color(QColor);

public slots:
    void stop();

private:
    ScreenAnalyzerPrivate *d_ptr;
};

#endif // SCREENANALYZER_H
