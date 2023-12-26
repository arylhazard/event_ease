#include "change.h"
#include "ui_change.h"

change::change(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change)
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
