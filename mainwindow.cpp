#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString filePath)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->filePath = filePath;
    configLoader = new SyntaxConfigLoader();
    colorThemeLoader = new ColorThemeLoader();
    colorThemeLoader->loadTheme("obsidian");

    QPalette p = ui->plainTextEdit->palette();
    p.setColor(QPalette::Base, colorThemeLoader->getBackgroundColor());
    p.setColor(QPalette::Text, colorThemeLoader->getBaseTextColor());
    ui->plainTextEdit->setPalette(p);
    ui->plainTextEdit->setWordWrapMode(QTextOption::NoWrap);

    syntaxHighlighter = new CommonSyntaxHighlighter(ui->plainTextEdit->document());

    loadFile();
}

void MainWindow::setFilePathForOpen(QString filePath)
{
    this->filePath = filePath;
}

MainWindow::~MainWindow()
{
    delete configLoader;
    delete syntaxHighlighter;
    delete colorThemeLoader;
    delete ui;
}

void MainWindow::loadFile()
{
    qDebug() << filePath;
    QFile textFile(filePath);
    textFile.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream inText(&textFile);
    if (configLoader != nullptr && colorThemeLoader != nullptr) {
        configLoader->loadConfig(filePath);
        syntaxHighlighter->assignSyntaxConfig(configLoader);
        syntaxHighlighter->assignColorTheme(colorThemeLoader);
    }
    ui->plainTextEdit->setPlainText(inText.readAll());
    textFile.close();
}

