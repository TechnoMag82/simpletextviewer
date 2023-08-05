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
#include <QShortcut>
#include <QMimeDatabase>

#include "appsettingsloader.h"
#include "syntaxconfigloader.h"
#include "commonsyntaxhighlighter.h"
#include "colorthemeloader.h"
#include "codeeditor.h"
#include "dialogabout.h"

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
        void showDialogAbout();
        void findNext();
        void findPrev();
        void focusSearch();

    private:
        QLabel *label;
        QAction *actFindNext;
        QAction *actFindPrev;
        QAction *actFocusSearch;
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
        bool isHistoryContains(QString item);
};
#endif // MAINWINDOW_H
