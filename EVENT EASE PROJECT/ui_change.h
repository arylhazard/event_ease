/********************************************************************************
** Form generated from reading UI file 'change.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_H
#define UI_CHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_change
{
public:
    QFrame *frame;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QFrame *frame_2;
    QLabel *labelMessage;
    QLabel *label_6;
    QLineEdit *cpass;
    QLineEdit *pass;
    QLabel *label_7;
    QPushButton *pushButton_done_2;

    void setupUi(QDialog *change)
    {
        if (change->objectName().isEmpty())
            change->setObjectName("change");
        change->resize(600, 500);
        frame = new QFrame(change);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 600, 500));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 60, 481, 401));
        label_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,100);\n"
"border-radius:20px;"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, -1, 600, 500));
        label->setMinimumSize(QSize(400, 0));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/img/_d2c400d3-68a4-4544-bea0-9303c338e05f.jpeg);"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 10, 291, 31));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 25pt \"Myriad Pro Cond\";\n"
""));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(130, 80, 351, 341));
        frame_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0);\n"
"border:none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        labelMessage = new QLabel(frame_2);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(40, 269, 171, 21));
        labelMessage->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 76, 151, 23));
        label_6->setStyleSheet(QString::fromUtf8("font: 700 15pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));
        cpass = new QLineEdit(frame_2);
        cpass->setObjectName("cpass");
        cpass->setGeometry(QRect(40, 210, 251, 41));
        cpass->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,255);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 13pt \"Myriad Pro Cond\";\n"
""));
        cpass->setEchoMode(QLineEdit::Password);
        cpass->setClearButtonEnabled(true);
        pass = new QLineEdit(frame_2);
        pass->setObjectName("pass");
        pass->setGeometry(QRect(40, 105, 251, 41));
        pass->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,255);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,255);\n"
"font: 700 13pt \"Myriad Pro Cond\";\n"
""));
        pass->setEchoMode(QLineEdit::Password);
        pass->setClearButtonEnabled(true);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 180, 231, 24));
        label_7->setStyleSheet(QString::fromUtf8("font: 700 15pt \"Myriad Pro Cond\";\n"
"color:rgba(255,255,255,255)"));
        pushButton_done_2 = new QPushButton(frame_2);
        pushButton_done_2->setObjectName("pushButton_done_2");
        pushButton_done_2->setGeometry(QRect(250, 300, 71, 31));
        pushButton_done_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_done_2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: none;\n"
"border-radius:15px;\n"
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
        label->raise();
        label_2->raise();
        frame_2->raise();
        label_4->raise();

        retranslateUi(change);

        QMetaObject::connectSlotsByName(change);
    } // setupUi

    void retranslateUi(QDialog *change)
    {
        change->setWindowTitle(QCoreApplication::translate("change", "Change Password", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        label_4->setText(QCoreApplication::translate("change", "CHANGE PASSWORD", nullptr));
        labelMessage->setText(QString());
        label_6->setText(QCoreApplication::translate("change", "NEW PASSWORD", nullptr));
        cpass->setPlaceholderText(QCoreApplication::translate("change", "CONFIRM PASSWORD", nullptr));
        pass->setPlaceholderText(QCoreApplication::translate("change", "PASSWORD", nullptr));
        label_7->setText(QCoreApplication::translate("change", "CONFIRM NEW PASSWORD", nullptr));
        pushButton_done_2->setText(QCoreApplication::translate("change", "DONE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class change: public Ui_change {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_H
