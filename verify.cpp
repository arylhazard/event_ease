#include "verify.h"
#include "ui_verify.h"
#include"change.h"

verify::verify(QWidget *parent, class change* change) :
    QDialog(parent),
    ui(new Ui::verify),
    change(change)
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

void verify::on_pushButton_done_2_clicked()
{
    hide();
    change = new class change(this);
    change->exec();
}
