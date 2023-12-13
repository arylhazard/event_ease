#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include "mainwindow.h"

login::login(QWidget *parent, MainWindow* mainWindow) :
    QDialog(parent),
    ui(new Ui::login),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_back, &QPushButton::clicked, this, &login::on_pushButton_back_clicked);
    QIcon userIcon(":/resource/img/user.png"); // Provide the path to your user icon
    ui->user->addAction(userIcon, QLineEdit::LeadingPosition);
    ui->user->setClearButtonEnabled(true); // Enable the clear button with the icon

    QIcon passIcon(":/resource/img/lock.png"); // Provide the path to your user icon
    ui->pass->addAction(passIcon, QLineEdit::LeadingPosition);
    ui->pass->setClearButtonEnabled(true); // Enable the clear button with the icon


}


void login::returnToMainWindow()
{
    accept(); // Return QDialog::Accepted result
    if (mainWindow) {
        mainWindow->show(); // Show the main window
    }
}

void login::on_pushButton_back_clicked()
{
    returnToMainWindow(); // Call the returnToMainWindow function
}


login::~login()
{
    delete ui;
}

void login::on_pass_returnPressed()
{
    ui->labelMessage->setText("Login Successful");
}

