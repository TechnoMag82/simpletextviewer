#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextDocument>

#include "syntaxconfigloader.h"
#include "commonsyntaxhighlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr, QString filePath = "");
        void setFilePathForOpen(QString filePath);
        ~MainWindow();

    private:
        QString filePath;
        Ui::MainWindow *ui;
        SyntaxConfigLoader *configLoader = nullptr;
        CommonSyntaxHighlighter *syntaxHighlighter = nullptr;

        void loadConfig();
        void loadFile();
};
#endif // MAINWINDOW_H
