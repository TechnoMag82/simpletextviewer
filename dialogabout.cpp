#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->label->setText(QApplication::applicationName());
    ui->label_2->setText(QApplication::applicationVersion());
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
