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

    QIcon nameIcon(":/resource/img/id-card.png"); // Provide the path to your user icon
    ui->name->addAction(nameIcon, QLineEdit::LeadingPosition);
    ui->name->setClearButtonEnabled(true); // Enable the clear button with the icon

    QIcon passIcon(":/resource/img/lock.png"); // Provide the path to your user icon
    ui->pass->addAction(passIcon, QLineEdit::LeadingPosition);
    ui->pass->setClearButtonEnabled(true); // Enable the clear button with the icon

    QIcon mailIcon(":/resource/img/mail.png"); // Provide the path to your user icon
    ui->mail->addAction(mailIcon, QLineEdit::LeadingPosition);
    ui->mail->setClearButtonEnabled(true); // Enable the clear button with the icon

    QIcon cpassIcon(":/resource/img/password.png"); // Provide the path to your user icon
    ui->cpass->addAction(cpassIcon, QLineEdit::LeadingPosition);
    ui->cpass->setClearButtonEnabled(true); // Enable the clear button with the icon



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
