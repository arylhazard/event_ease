#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>

namespace Ui {
class question;
}

class question : public QDialog
{
    Q_OBJECT

public:
    explicit question(QWidget *parent = nullptr);
    ~question();

private:
    Ui::question *ui;
};

#endif // QUESTION_H
