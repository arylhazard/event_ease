#include "verify.h"
#include "ui_verify.h"

verify::verify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::verify)
{
    ui->setupUi(this);

    QIcon mailIcon(":/resource/img/mail.png");
    ui->mail->addAction(mailIcon, QLineEdit::LeadingPosition);
    ui->mail->setClearButtonEnabled(true);



    QIcon bookIcon(":/resource/img/book.png");
    ui->book->addAction(bookIcon, QLineEdit::LeadingPosition);
    ui->book->setClearButtonEnabled(true);


    QIcon homeIcon(":/resource/img/home.png");
    ui->home->addAction(homeIcon, QLineEdit::LeadingPosition);
    ui->home->setClearButtonEnabled(true);



}

verify::~verify()
{
    delete ui;
}
