#ifndef VERIFY_H
#define VERIFY_H

#include <QDialog>

namespace Ui {
class verify;
}

class verify : public QDialog
{
    Q_OBJECT

public:
    explicit verify(QWidget *parent = nullptr);
    ~verify();

private:
    Ui::verify *ui;
};

#endif // VERIFY_H
