/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_pushButton_ajouter_clicked",
    "",
    "on_supprimer_Clicked",
    "on_modifier_Clicked",
    "afficherLivraisons",
    "on_rechercher_clicked",
    "exporterEnCSV",
    "on_sendMailButton_clicked",
    "sendEmail",
    "to",
    "subject",
    "body",
    "onDateClicked",
    "date",
    "updateCalendar",
    "on_openDoorButton_clicked",
    "on_closeDoorButton_clicked",
    "readFromArduino"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[11];
    char stringdata1[30];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[20];
    char stringdata5[19];
    char stringdata6[22];
    char stringdata7[14];
    char stringdata8[26];
    char stringdata9[10];
    char stringdata10[3];
    char stringdata11[8];
    char stringdata12[5];
    char stringdata13[14];
    char stringdata14[5];
    char stringdata15[15];
    char stringdata16[26];
    char stringdata17[27];
    char stringdata18[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 29),  // "on_pushButton_ajouter_clicked"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 20),  // "on_supprimer_Clicked"
        QT_MOC_LITERAL(63, 19),  // "on_modifier_Clicked"
        QT_MOC_LITERAL(83, 18),  // "afficherLivraisons"
        QT_MOC_LITERAL(102, 21),  // "on_rechercher_clicked"
        QT_MOC_LITERAL(124, 13),  // "exporterEnCSV"
        QT_MOC_LITERAL(138, 25),  // "on_sendMailButton_clicked"
        QT_MOC_LITERAL(164, 9),  // "sendEmail"
        QT_MOC_LITERAL(174, 2),  // "to"
        QT_MOC_LITERAL(177, 7),  // "subject"
        QT_MOC_LITERAL(185, 4),  // "body"
        QT_MOC_LITERAL(190, 13),  // "onDateClicked"
        QT_MOC_LITERAL(204, 4),  // "date"
        QT_MOC_LITERAL(209, 14),  // "updateCalendar"
        QT_MOC_LITERAL(224, 25),  // "on_openDoorButton_clicked"
        QT_MOC_LITERAL(250, 26),  // "on_closeDoorButton_clicked"
        QT_MOC_LITERAL(277, 15)   // "readFromArduino"
    },
    "MainWindow",
    "on_pushButton_ajouter_clicked",
    "",
    "on_supprimer_Clicked",
    "on_modifier_Clicked",
    "afficherLivraisons",
    "on_rechercher_clicked",
    "exporterEnCSV",
    "on_sendMailButton_clicked",
    "sendEmail",
    "to",
    "subject",
    "body",
    "onDateClicked",
    "date",
    "updateCalendar",
    "on_openDoorButton_clicked",
    "on_closeDoorButton_clicked",
    "readFromArduino"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    0,   98,    2, 0x08,    7 /* Private */,
       9,    3,   99,    2, 0x08,    8 /* Private */,
      13,    1,  106,    2, 0x08,   12 /* Private */,
      15,    0,  109,    2, 0x08,   14 /* Private */,
      16,    0,  110,    2, 0x08,   15 /* Private */,
      17,    0,  111,    2, 0x08,   16 /* Private */,
      18,    0,  112,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::QDate,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_pushButton_ajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_supprimer_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_modifier_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherLivraisons'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rechercher_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exporterEnCSV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sendMailButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendEmail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onDateClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'updateCalendar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_openDoorButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_closeDoorButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readFromArduino'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_ajouter_clicked(); break;
        case 1: _t->on_supprimer_Clicked(); break;
        case 2: _t->on_modifier_Clicked(); break;
        case 3: _t->afficherLivraisons(); break;
        case 4: _t->on_rechercher_clicked(); break;
        case 5: _t->exporterEnCSV(); break;
        case 6: _t->on_sendMailButton_clicked(); break;
        case 7: _t->sendEmail((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->onDateClicked((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 9: _t->updateCalendar(); break;
        case 10: _t->on_openDoorButton_clicked(); break;
        case 11: _t->on_closeDoorButton_clicked(); break;
        case 12: _t->readFromArduino(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
