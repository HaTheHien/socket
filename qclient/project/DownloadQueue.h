#ifndef DOWNLOADQUEUE_H
#define DOWNLOADQUEUE_H
#include <QTabWidget>

namespace Ui {
class MainView;
}

class DownloadQueue
{
private:
    QWidget* ui_downloadTab;

public:
    DownloadQueue();
    DownloadQueue(QWidget* ui);
};

#endif // DOWNLOADQUEUE_H
