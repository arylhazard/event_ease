#include "change.h"
#include "ui_change.h"
#include "login.h"
change::change(QWidget *parent, class login* login) :
    QDialog(parent),
    ui(new Ui::change),
    login(login)
{
    ui->setupUi(this);

    QIcon cpassIcon(":/resource/img/password.png");
    ui->cpass->addAction(cpassIcon, QLineEdit::LeadingPosition);
    ui->cpass->setClearButtonEnabled(true);

    QIcon passIcon(":/resource/img/lock.png");
    ui->pass->addAction(passIcon, QLineEdit::LeadingPosition);
    ui->pass->setClearButtonEnabled(true);

}

change::~change()
{
    delete ui;
}

void change::on_pushButton_done_2_clicked()
{
    hide();
    login = new class login(this);
    login->exec();
}

