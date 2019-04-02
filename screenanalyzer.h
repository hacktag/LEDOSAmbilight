#ifndef SCREENANALYZER_H
#define SCREENANALYZER_H

#include <QThread>

class ScreenAnalyzer : public QThread
{
    Q_OBJECT
public:
    ScreenAnalyzer();

protected:
    void run();
};

#endif // SCREENANALYZER_H
