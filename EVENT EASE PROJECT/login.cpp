#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "verify.h"
#include <QPushButton>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>

login::login(QWidget *parent, MainWindow* mainWindow, class verify* verify):
    QDialog(parent),
    ui(new Ui::login),
    mainWindow(mainWindow),
    verify(verify)
{
    ui->setupUi(this);
    connect(ui->pushButton_back, &QPushButton::clicked, this, &login::on_pushButton_back_clicked);


   /*QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName("/home/okeyy/Desktop/try/event_ease/Databse/project");
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
    ui->email->addAction(userIcon, QLineEdit::LeadingPosition);
    ui->email->setClearButtonEnabled(true); // Enable the clear button with the icon

    QIcon passIcon(":/resource/img/lock.png"); // Provide the path to your user icon
    ui->pass->addAction(passIcon, QLineEdit::LeadingPosition);
    ui->pass->setClearButtonEnabled(true); // Enable the clear button with the icon


}
void login::showMessage(const QString &title, const QString &text, QMessageBox::Icon icon, QFlags<QMessageBox::StandardButton> buttons) {
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(text);
    msgBox->setIcon(icon);
    msgBox->setStandardButtons(buttons);
    msgBox->setWindowTitle(title);
    msgBox->setStyleSheet("QLabel{font-size: 18px; color: #000; font-weight: 400; font-family: 'Poppins';} "
                          "QPushButton{color: #fff; font-family: 'Poppins'; background-color: #088F8F;}");

    msgBox->exec();
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
    QString email=ui->email->text();
    QString password=ui->pass->text();

     QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    if(!mydb.open()) {
        qDebug() << "Failed to open the database.";
        return;
    }
    else
    {
        qDebug() << "Successful to open the database.";
    }

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    //query.bindValue(":password", password);
    query.bindValue(":password",hashedPassword);

    if (query.exec() && query.next()) {
        // Login successful
        qDebug() << "Login successful";

        // Redirect to another window (you can replace this part with your own logic)
       // this->hide();


        // Close the login window
        close();
    } else {
        // Login failed, show error message
        qDebug() << "Login failed";
      showMessage("Login Error", "Invalid username or password.", QMessageBox::Critical, QMessageBox::Ok);  //ERROR aayera nagareko..solve and do//
        qDebug()<<"Error:"<<mydb.lastError();
    }

    mydb.close();
}


void login::on_pushButton_clicked()
{
    hide();
    verify = new class verify(this);
    verify->exec();
}

