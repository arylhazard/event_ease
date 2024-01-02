#include "question.h"
#include "ui_question.h"
#include"login.h"
question::question(QWidget *parent, class login* login) :
    QDialog(parent),
    ui(new Ui::question),
    login(login)
{
    ui->setupUi(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/okeyy/Desktop/try/event_ease/Databse/project");

    if(mydb.open())
    {
        qDebug()<<"Database is Connected";
    }
    else
    {

        qDebug()<<"Database is Not Connected";
        qDebug()<<"Error:"<<mydb.lastError();
    }
    QIcon homeIcon(":/resource/img/home.png");
    ui->home->addAction(homeIcon, QLineEdit::LeadingPosition);
    ui->home->setClearButtonEnabled(true);


    QIcon bookIcon(":/resource/img/book.png");
    ui->book->addAction(bookIcon, QLineEdit::LeadingPosition);
    ui->book->setClearButtonEnabled(true);
}

question::~question()
{
    delete ui;
}

void question::on_pushButton_done_clicked()
{
    hide();
    login = new class login(this);
    login->exec();
}

