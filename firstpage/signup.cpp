#include "signup.h"
#include "ui_signup.h"
#include <QPushButton>
#include "mainwindow.h"

Signup::Signup(QWidget *parent, MainWindow* mainWindow) :
    QDialog(parent),
    ui(new Ui::Signup),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_back1, &QPushButton::clicked, this, &::Signup::on_pushButton_back1_clicked);
}


void Signup::returnToMainWindow()
{
    accept(); // Return QDialog::Accepted result
    if (mainWindow) {
        mainWindow->show(); // Show the main window
    }
}

void Signup::on_pushButton_back1_clicked()
{
    returnToMainWindow(); // Call the returnToMainWindow function
}


Signup::~Signup()
{
    delete ui;
}
