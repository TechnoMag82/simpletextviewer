#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("SimpleTextViewer");
    QApplication::setApplicationVersion("1.0.3");
    MainWindow *w;
    if (argc >= 1) {
        w = new MainWindow(0, argv[1]);
    } else {
        w = new MainWindow();
    }
    w->showMaximized();
    return a.exec();
}
