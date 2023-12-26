#include "question.h"
#include "ui_question.h"

question::question(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::question)
{
    ui->setupUi(this);


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
