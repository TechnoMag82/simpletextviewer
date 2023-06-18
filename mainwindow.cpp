#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString filePath)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainMenu();

    plainTextEdit = new CodeEditor(ui->centralwidget);
    ui->verticalLayout->addWidget(plainTextEdit);

    initSearchLayout();

    this->filePath = filePath;
    configurePlainTextEdit();
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

void MainWindow::quitApp()
{
    close();
}

void MainWindow::loadAppSettings()
{
    AppSettingsLoader *appSettingsLoader = new AppSettingsLoader();
    appSettings = appSettingsLoader->loadSettings();
    delete appSettingsLoader;
}

void MainWindow::loadFile()
{
    qDebug() << "Load file: " << filePath;
    QFile textFile(filePath);
    textFile.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream inText(&textFile);
    if (configLoader != nullptr && colorThemeLoader != nullptr) {
        configLoader->loadConfig(filePath);
        syntaxHighlighter->assignSyntaxConfig(configLoader);
        syntaxHighlighter->assignColorTheme(colorThemeLoader);
    }
    plainTextEdit->setPlainText(inText.readAll());
    textFile.close();
}

void MainWindow::initMainMenu()
{
    ui->actionExit->setShortcut(QKeySequence("Esc"));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quitApp()));
}

void MainWindow::initSearchLayout()
{
    QBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(4, -1, 4, -1);
    label = new QLabel(ui->centralwidget);
    label->setText(tr("Find: "));
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);

    searchEdit = new QComboBox(ui->centralwidget);
    searchEdit->setObjectName(QString::fromUtf8("lineEdit"));
    searchEdit->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
    searchEdit->setEditable(true);

    horizontalLayout->addWidget(searchEdit);

    buttonPrevFind = new QPushButton(ui->centralwidget);
    buttonPrevFind->setObjectName(QString::fromUtf8("buttonPrevFind"));
    buttonPrevFind->setText(tr("<< Prev (F6)"));

    horizontalLayout->addWidget(buttonPrevFind);

    buttonNextFind = new QPushButton(ui->centralwidget);
    buttonNextFind->setObjectName(QString::fromUtf8("buttonNextFind"));
    buttonNextFind->setText(tr("Next (F7) >>"));

    horizontalLayout->addWidget(buttonNextFind);

    checkBox = new QCheckBox(ui->centralwidget);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setText(tr("Match case"));

    horizontalLayout->addWidget(checkBox);

    ui->verticalLayout->addLayout(horizontalLayout);
}

void MainWindow::configurePlainTextEdit()
{
    loadAppSettings();
    configLoader = new SyntaxConfigLoader();
    colorThemeLoader = new ColorThemeLoader();
    colorThemeLoader->loadTheme(appSettings.colorThemeName);

    plainTextEdit->setCurrentLineColor(colorThemeLoader->getCurrentLineColor());
    plainTextEdit->setTextColor(colorThemeLoader->getBaseTextColor());
    plainTextEdit->setBackgroundColor(colorThemeLoader->getBackgroundColor());
    plainTextEdit->setLineNumberColor(colorThemeLoader->getLineNumberColor());
    plainTextEdit->applyColorTheme();

    syntaxHighlighter = new CommonSyntaxHighlighter(plainTextEdit->document());
}

