#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString filePath)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QApplication::applicationName());

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
    delete actFindNext;
    delete actFindPrev;
    delete actFocusSearch;
    delete configLoader;
    delete syntaxHighlighter;
    delete colorThemeLoader;
    delete ui;
}

void MainWindow::quitApp()
{
    close();
}

void MainWindow::showDialogAbout()
{
    DialogAbout *aboutDialog = new DialogAbout(this);
    aboutDialog->exec();
    delete aboutDialog;
}

void MainWindow::findNext()
{
   if (searchEdit->currentText().isEmpty())
       return;
   if (!isHistoryContains(searchEdit->currentText())) {
       searchEdit->addItem(searchEdit->currentText());
   }
   QTextCursor cursor = plainTextEdit->textCursor();
   QTextDocument::FindFlags flag;
   if (checkBox->isChecked())
       flag |= QTextDocument::FindCaseSensitively;
   if (!plainTextEdit->find(searchEdit->currentText(), flag)) {
        cursor.movePosition(QTextCursor::Start);
        plainTextEdit->setTextCursor(cursor);
   }
}

void MainWindow::findPrev()
{
    if (searchEdit->currentText().isEmpty())
        return;
    if (!isHistoryContains(searchEdit->currentText())) {
        searchEdit->addItem(searchEdit->currentText());
    }
    QTextCursor cursor = plainTextEdit->textCursor();
    QTextDocument::FindFlags flag;
    flag |= QTextDocument::FindBackward;
    if (checkBox->isChecked())
        flag |= QTextDocument::FindCaseSensitively;
    if (!plainTextEdit->find(searchEdit->currentText(), flag)) {
         cursor.movePosition(QTextCursor::End);
         plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::focusSearch()
{
    searchEdit->setFocus();
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
    if (textFile.open(QIODevice::ReadOnly| QIODevice::Text)) {
        QTextStream inText(&textFile);
        if (configLoader != nullptr && colorThemeLoader != nullptr) {
            if (configLoader->loadConfig(filePath)) {
                syntaxHighlighter->assignSyntaxConfig(configLoader);
                syntaxHighlighter->assignColorTheme(colorThemeLoader);
            } else {
                syntaxHighlighter->assignSyntaxConfig(nullptr);
                syntaxHighlighter->assignColorTheme(nullptr);
            }
        }
        plainTextEdit->setPlainText(inText.readAll());
        textFile.close();
        setWindowTitle(QApplication::applicationName() + " - " + this->filePath);
    }
}

void MainWindow::initMainMenu()
{
    ui->actionExit->setShortcut(QKeySequence("Esc"));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quitApp()));

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showDialogAbout()));
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

    actFocusSearch = new QAction(searchEdit);
    actFocusSearch->setShortcut(QKeySequence("Ctrl+F"));
    searchEdit->addAction(actFocusSearch);
    connect(actFocusSearch, SIGNAL(triggered()), this, SLOT(focusSearch()));

    horizontalLayout->addWidget(searchEdit);

    buttonPrevFind = new QPushButton(ui->centralwidget);
    buttonPrevFind->setObjectName(QString::fromUtf8("buttonPrevFind"));
    buttonPrevFind->setText(tr("<< Prev (Shift+F3)"));

    actFindPrev = new QAction(buttonPrevFind);
    actFindPrev->setShortcut(QKeySequence("Shift+F3"));
    buttonPrevFind->addAction(actFindPrev);
    connect(actFindPrev, SIGNAL(triggered()), this, SLOT(findPrev()));
    connect(buttonPrevFind, SIGNAL(clicked()), this, SLOT(findPrev()));

    horizontalLayout->addWidget(buttonPrevFind);

    buttonNextFind = new QPushButton(ui->centralwidget);
    buttonNextFind->setObjectName(QString::fromUtf8("buttonNextFind"));
    buttonNextFind->setText(tr("Next (F3) >>"));

    actFindNext = new QAction(buttonNextFind);
    actFindNext->setShortcut(QKeySequence("F3"));
    buttonNextFind->addAction(actFindNext);
    connect(actFindNext, SIGNAL(triggered()), this, SLOT(findNext()));
    connect(buttonNextFind, SIGNAL(clicked()), this, SLOT(findNext()));

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

bool MainWindow::isHistoryContains(QString item)
{
    int count = searchEdit->count();
    for (int index = 0; index < count; index++) {
        if (searchEdit->itemText(index).compare(item) == 0)
            return true;
    }
    return false;
}

