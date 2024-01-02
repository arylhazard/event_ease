#ifndef VERIFY_H
#define VERIFY_H

#include <QDialog>
#include "change.h"

namespace Ui {
class verify;
}

class verify : public QDialog
{
    Q_OBJECT

public:
    explicit verify(QWidget *parent = nullptr, change* change = nullptr);
    ~verify();

private slots:
    void on_pushButton_done_2_clicked();

private:
    Ui::verify *ui;
    change* change;
};

#endif // VERIFY_H
