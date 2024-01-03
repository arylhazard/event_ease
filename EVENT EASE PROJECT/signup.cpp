#include "signup.h"
#include "ui_signup.h"
#include <QPushButton>
#include "mainwindow.h"
#include "login.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>
Signup::Signup(QWidget *parent, MainWindow* mainWindow,class login *login) :
    QDialog(parent),
    ui(new Ui::Signup),
    mainWindow(mainWindow),
    login(login)
{
    ui->setupUi(this);
    connect(ui->pushButton_back1, &QPushButton::clicked, this, &Signup::on_pushButton_back1_clicked);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../database/project");

    if(mydb.open())
    {
        qDebug()<<"Database is Connected";
    }
    else
    {

        qDebug()<<"Database is Not Connected";
        qDebug()<<"Error:"<<mydb.lastError();
    }
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
void Signup::goToLogin()
{
    hide();
    login =new class login(this);
    login->exec();
}

void Signup::on_pushButton_back1_clicked()
{
    returnToMainWindow();
}
bool Signup::isValidEmail(const QString &email) {
    // Regular expression for a simple email validation
    QRegularExpression regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    return regex.match(email).hasMatch();
}
void Signup::showMessage(const QString &title, const QString &text, QMessageBox::Icon icon, QFlags<QMessageBox::StandardButton> buttons) {
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(text);
    msgBox->setIcon(icon);
    msgBox->setStandardButtons(buttons);
    msgBox->setWindowTitle(title);
    msgBox->setStyleSheet("QLabel{font-size: 18px; color: #000; font-weight: 400; font-family: 'Poppins';} "
                          "QPushButton{color: #fff; font-family: 'Poppins'; background-color: #088F8F;}");

    msgBox->exec();
}
Signup::~Signup()
{
    delete ui;
}




void Signup::on_pushButton_next_clicked()
{
   QSqlDatabase mydb = QSqlDatabase::database(); // Get the existing database     connection
    QString username = ui->name->text();
    QString email= ui->mail->text();
    QString password = ui->pass->text();
    QString cpassword = ui->cpass->text();

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    if(!mydb.open()) {
        qDebug() << "Failed to open the database.";
        return;
    }
    if (isValidEmail(email)) {
       qDebug() << "Email is valid!";

        if(password==cpassword && password.length()>=6){
     QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE email=:email OR username=:username");
     query.bindValue(":email",email);
      query.bindValue(":username",username);
     if (query.exec() && query.next()) {
         // Email is already used, show error message
         qDebug() << "Email or username is already in use";
       showMessage("Registration Error", "This email addess is already in use. Please use another or simply login.",
                     QMessageBox::Critical, QMessageBox::Ok);
     }
     else{
         query.prepare("Insert INTO users(username,email,password) VALUES (:username,:email,:password)");
         query.bindValue(":username",username);
         query.bindValue(":email",email);
         query.bindValue(":password",hashedPassword);
         if(query.exec()){
             qDebug()<<"Data Inserted Successfully";
             showMessage("Registration Successful", "You can now log in.", QMessageBox::Information, QMessageBox::Ok);
                //returnToMainWindow();
             goToLogin();
             this->hide();
         }
         else {
             qDebug() << "Error: " << query.lastError().text();
         }
         }
        }
    else{
        //password wrong error thrown//
        showMessage("Registration Error","Password and Confirm Password didnt match and password must be at least 6 characters long,",QMessageBox::Warning,QMessageBox::Ok);

     }
         //Tyo is Valid username ko lagi//

    }
     else{
         qDebug()<<"Invalid email";
         showMessage("Registration Error","The email address is not valid.Please enter valid email.",QMessageBox::Critical,QMessageBox::Ok);
     }
     mydb.close();
     }






















