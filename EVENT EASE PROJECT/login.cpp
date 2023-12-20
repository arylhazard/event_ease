#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include <QCoreApplication>
#include <QDir>
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>


login::login(QWidget *parent, MainWindow* mainWindow) :
    QDialog(parent),
    ui(new Ui::login),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_back, &QPushButton::clicked, this, &login::on_pushButton_back_clicked);


  /*  QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/okeyy/endsem/Databse/project");

    if(mydb.open())
    {
        qDebug()<<"Database is Connected";
    }
    else
    {

        qDebug()<<"Database is Not Connected";
        qDebug()<<"Error:"<<mydb.lastError();
    }*/
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



void login::on_pushButton_done_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::database();
    QString username=ui->user->text();
    QString password=ui->pass->text();

     QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    if(!mydb.open()) {
        qDebug() << "Failed to open the database.";
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE usesrname = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":password",hashedPassword);

    if (query.exec() && query.next()) {
        // Login successful
        qDebug() << "Login successful";

        // Redirect to another window (you can replace this part with your own logic)
      //  this->hide();


        // Close the login window
        close();
    } else {
        // Login failed, show error message
        qDebug() << "Login failed";
       // showMessage("Login Error", "Invalid email or password.", QMessageBox::Critical, QMessageBox::Ok);  //ERROR aayera nagareko..solve and do//
    }

    mydb.close();






}

