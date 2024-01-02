/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *frame_2;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *name;
    QLabel *label_5;
    QLineEdit *mail;
    QLabel *label_6;
    QLineEdit *pass;
    QLabel *label_7;
    QLineEdit *cpass;
    QPushButton *pushButton_back1;
    QPushButton *pushButton_next;

    void setupUi(QDialog *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName("Signup");
        Signup->resize(600, 500);
        Signup->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(Signup);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(Signup);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 600, 500));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/img/_d2c400d3-68a4-4544-bea0-9303c338e05f.jpeg);"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 50, 521, 411));
        label_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,100);\n"
"border-radius:20px;"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(240, 10, 121, 31));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 20pt \"Myriad Pro Cond\";\n"
""));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(200, 110, 231, 271));
        frame_2->setStyleSheet(QString::fromUtf8("border:none;\n"
"background:rgba(0,0,0,0)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame_2);
        formLayout->setObjectName("formLayout");
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 700 13pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        name = new QLineEdit(frame_2);
        name->setObjectName("name");
        name->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,255);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));

        formLayout->setWidget(1, QFormLayout::SpanningRole, name);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 700 13pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        mail = new QLineEdit(frame_2);
        mail->setObjectName("mail");
        mail->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,230);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));

        formLayout->setWidget(3, QFormLayout::SpanningRole, mail);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font: 700 13pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        pass = new QLineEdit(frame_2);
        pass->setObjectName("pass");
        pass->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,255);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        pass->setEchoMode(QLineEdit::Password);
        pass->setClearButtonEnabled(true);

        formLayout->setWidget(5, QFormLayout::SpanningRole, pass);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 700 13pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        cpass = new QLineEdit(frame_2);
        cpass->setObjectName("cpass");
        cpass->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,255);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        cpass->setEchoMode(QLineEdit::Password);
        cpass->setClearButtonEnabled(true);

        formLayout->setWidget(7, QFormLayout::SpanningRole, cpass);

        pushButton_back1 = new QPushButton(frame);
        pushButton_back1->setObjectName("pushButton_back1");
        pushButton_back1->setGeometry(QRect(20, 10, 35, 35));
        pushButton_back1->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_back1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/img/backarrow.jpeg);\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	\n"
"	border-image: url(:/resource/img/jkbjkbe.jpeg);\n"
"}"));
        pushButton_next = new QPushButton(frame);
        pushButton_next->setObjectName("pushButton_next");
        pushButton_next->setGeometry(QRect(360, 400, 80, 24));
        pushButton_next->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_next->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: none;\n"
"color: rgba(255,255,255,255);\n"
"background-color: rgb(5, 77, 101);\n"
"font : 700 12pt \"Myriad Pro Cond\";\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"\n"
"	background-color: rgb(30, 104, 154);\n"
"}\n"
""));

        verticalLayout->addWidget(frame);


        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QDialog *Signup)
    {
        Signup->setWindowTitle(QCoreApplication::translate("Signup", "SignUp Page", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("Signup", "SIGN UP", nullptr));
        label_4->setText(QCoreApplication::translate("Signup", "NAME*", nullptr));
        name->setText(QString());
        name->setPlaceholderText(QCoreApplication::translate("Signup", "FULL NAME", nullptr));
        label_5->setText(QCoreApplication::translate("Signup", "MAIL*", nullptr));
        mail->setPlaceholderText(QCoreApplication::translate("Signup", "myname@gmail.com", nullptr));
        label_6->setText(QCoreApplication::translate("Signup", "PASSWORD*", nullptr));
        pass->setPlaceholderText(QCoreApplication::translate("Signup", "PASSWORD", nullptr));
        label_7->setText(QCoreApplication::translate("Signup", "CONFIRM PASSWORD*", nullptr));
        cpass->setPlaceholderText(QCoreApplication::translate("Signup", "CONFIRM PASSWORD", nullptr));
        pushButton_back1->setText(QString());
        pushButton_next->setText(QCoreApplication::translate("Signup", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
