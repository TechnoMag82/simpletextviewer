#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextDocument>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDir>

#include "appsettingsloader.h"
#include "syntaxconfigloader.h"
#include "commonsyntaxhighlighter.h"
#include "colorthemeloader.h"
#include "codeeditor.h"

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

    private slots:
        void quitApp();

    private:
        QLabel *label;
        QComboBox *searchEdit;
        QCheckBox *checkBox;
        QPushButton *buttonPrevFind;
        QPushButton *buttonNextFind;
        CodeEditor *plainTextEdit = nullptr;
        QString filePath;
        AppSettings appSettings;
        Ui::MainWindow *ui;
        SyntaxConfigLoader *configLoader = nullptr;
        CommonSyntaxHighlighter *syntaxHighlighter = nullptr;
        ColorThemeLoader *colorThemeLoader = nullptr;

        void loadAppSettings();
        void loadFile();
        void initMainMenu();
        void initSearchLayout();
        void configurePlainTextEdit();
};
#endif // MAINWINDOW_H
