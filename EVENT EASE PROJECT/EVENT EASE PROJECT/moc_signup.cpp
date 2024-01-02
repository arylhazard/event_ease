/****************************************************************************
** Meta object code from reading C++ file 'signup.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "signup.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSignupENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSignupENDCLASS = QtMocHelpers::stringData(
    "Signup",
    "returnToMainWindow",
    "",
    "goToQuestions",
    "on_pushButton_back1_clicked",
    "on_pushButton_next_clicked",
    "isValidEmail",
    "email",
    "showMessage",
    "title",
    "text",
    "QMessageBox::Icon",
    "icon",
    "QFlags<QMessageBox::StandardButton>",
    "buttons"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSignupENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[28];
    char stringdata5[27];
    char stringdata6[13];
    char stringdata7[6];
    char stringdata8[12];
    char stringdata9[6];
    char stringdata10[5];
    char stringdata11[18];
    char stringdata12[5];
    char stringdata13[36];
    char stringdata14[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSignupENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSignupENDCLASS_t qt_meta_stringdata_CLASSSignupENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Signup"
        QT_MOC_LITERAL(7, 18),  // "returnToMainWindow"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 13),  // "goToQuestions"
        QT_MOC_LITERAL(41, 27),  // "on_pushButton_back1_clicked"
        QT_MOC_LITERAL(69, 26),  // "on_pushButton_next_clicked"
        QT_MOC_LITERAL(96, 12),  // "isValidEmail"
        QT_MOC_LITERAL(109, 5),  // "email"
        QT_MOC_LITERAL(115, 11),  // "showMessage"
        QT_MOC_LITERAL(127, 5),  // "title"
        QT_MOC_LITERAL(133, 4),  // "text"
        QT_MOC_LITERAL(138, 17),  // "QMessageBox::Icon"
        QT_MOC_LITERAL(156, 4),  // "icon"
        QT_MOC_LITERAL(161, 35),  // "QFlags<QMessageBox::StandardB..."
        QT_MOC_LITERAL(197, 7)   // "buttons"
    },
    "Signup",
    "returnToMainWindow",
    "",
    "goToQuestions",
    "on_pushButton_back1_clicked",
    "on_pushButton_next_clicked",
    "isValidEmail",
    "email",
    "showMessage",
    "title",
    "text",
    "QMessageBox::Icon",
    "icon",
    "QFlags<QMessageBox::StandardButton>",
    "buttons"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSignupENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    0,   63,    2, 0x0a,    2 /* Public */,
       4,    0,   64,    2, 0x0a,    3 /* Public */,
       5,    0,   65,    2, 0x0a,    4 /* Public */,
       6,    1,   66,    2, 0x0a,    5 /* Public */,
       8,    4,   69,    2, 0x0a,    7 /* Public */,
       8,    3,   78,    2, 0x2a,   12 /* Public | MethodCloned */,
       8,    2,   85,    2, 0x2a,   16 /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 11, 0x80000000 | 13,    9,   10,   12,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject Signup::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSSignupENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSignupENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSignupENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Signup, std::true_type>,
        // method 'returnToMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToQuestions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_back1_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_next_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'isValidEmail'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMessageBox::Icon, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFlags<QMessageBox::StandardButton>, std::false_type>,
        // method 'showMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMessageBox::Icon, std::false_type>,
        // method 'showMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void Signup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Signup *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnToMainWindow(); break;
        case 1: _t->goToQuestions(); break;
        case 2: _t->on_pushButton_back1_clicked(); break;
        case 3: _t->on_pushButton_next_clicked(); break;
        case 4: { bool _r = _t->isValidEmail((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->showMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMessageBox::Icon>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QFlags<QMessageBox::StandardButton>>>(_a[4]))); break;
        case 6: _t->showMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMessageBox::Icon>>(_a[3]))); break;
        case 7: _t->showMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *Signup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Signup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSignupENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Signup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
