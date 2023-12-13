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
    connect(ui->pushButton_back1, &QPushButton::clicked, this, &Signup::on_pushButton_back1_clicked);

    QIcon nameIcon(":/resource/img/id-card.png");
    ui->name->addAction(nameIcon, QLineEdit::LeadingPosition);
    ui->name->setClearButtonEnabled(true);

    QIcon passIcon(":/resource/img/lock.png");
    ui->pass->addAction(passIcon, QLineEdit::LeadingPosition);
    ui->pass->setClearButtonEnabled(true);

    QIcon mailIcon(":/resource/img/mail.png");
    ui->mail->addAction(mailIcon, QLineEdit::LeadingPosition);
    ui->mail->setClearButtonEnabled(true);

    QIcon cpassIcon(":/resource/img/password.png");
    ui->cpass->addAction(cpassIcon, QLineEdit::LeadingPosition);
    ui->cpass->setClearButtonEnabled(true);

   }

void Signup::returnToMainWindow()
{
    accept();
    if (mainWindow) {
        mainWindow->show();
    }
}

void Signup::on_pushButton_back1_clicked()
{
    returnToMainWindow();
}


Signup::~Signup()
{
    delete ui;
}



