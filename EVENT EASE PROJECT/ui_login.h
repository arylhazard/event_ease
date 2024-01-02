/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QFrame *frame;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QFrame *frame_2;
    QPushButton *pushButton_done;
    QLabel *label_3;
    QLineEdit *user;
    QLineEdit *pass;
    QLabel *labelMessage;
    QPushButton *pushButton_back;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(600, 500);
        login->setCursor(QCursor(Qt::ArrowCursor));
        login->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame = new QFrame(login);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 600, 500));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 50, 521, 411));
        label_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,100);\n"
"border-radius:20px;"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 601, 501));
        label->setMinimumSize(QSize(550, 0));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/img/_d2c400d3-68a4-4544-bea0-9303c338e05f.jpeg);"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(260, 10, 121, 31));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 20pt \"Myriad Pro Cond\";\n"
""));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(170, 90, 281, 351));
        frame_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0);\n"
"border:none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton_done = new QPushButton(frame_2);
        pushButton_done->setObjectName("pushButton_done");
        pushButton_done->setGeometry(QRect(200, 290, 61, 24));
        pushButton_done->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_done->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 10, 120, 120));
        label_3->setMinimumSize(QSize(120, 120));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/img/user.jpeg);\n"
"border-radius:60px;"));
        user = new QLineEdit(frame_2);
        user->setObjectName("user");
        user->setGeometry(QRect(40, 170, 171, 29));
        user->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,230);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,210);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        user->setClearButtonEnabled(true);
        pass = new QLineEdit(frame_2);
        pass->setObjectName("pass");
        pass->setGeometry(QRect(40, 220, 171, 29));
        pass->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,230);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,210);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        pass->setEchoMode(QLineEdit::Password);
        pass->setClearButtonEnabled(true);
        labelMessage = new QLabel(frame_2);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(40, 269, 171, 21));
        labelMessage->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_3->raise();
        user->raise();
        pass->raise();
        pushButton_done->raise();
        labelMessage->raise();
        pushButton_back = new QPushButton(frame);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 10, 35, 35));
        pushButton_back->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_back->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/img/backarrow.jpeg);\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	\n"
"	border-image: url(:/resource/img/jkbjkbe.jpeg);\n"
"}"));
        label->raise();
        label_2->raise();
        frame_2->raise();
        label_4->raise();
        pushButton_back->raise();

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Login Page", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        label_4->setText(QCoreApplication::translate("login", "LOGIN", nullptr));
        pushButton_done->setText(QCoreApplication::translate("login", "DONE", nullptr));
        label_3->setText(QString());
        user->setPlaceholderText(QCoreApplication::translate("login", "email", nullptr));
        pass->setPlaceholderText(QCoreApplication::translate("login", "Password", nullptr));
        labelMessage->setText(QString());
        pushButton_back->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
