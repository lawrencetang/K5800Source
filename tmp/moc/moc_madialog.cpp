/****************************************************************************
** Meta object code from reading C++ file 'madialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SettingsView/madialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'madialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MaDialog_t {
    QByteArrayData data[11];
    char stringdata[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaDialog_t qt_meta_stringdata_MaDialog = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MaDialog"
QT_MOC_LITERAL(1, 9, 12), // "okBtnClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "showDialog"
QT_MOC_LITERAL(4, 34, 8), // "paramStr"
QT_MOC_LITERAL(5, 43, 8), // "watchStr"
QT_MOC_LITERAL(6, 52, 10), // "hideDialog"
QT_MOC_LITERAL(7, 63, 10), // "addDyeData"
QT_MOC_LITERAL(8, 74, 11), // "typeChanged"
QT_MOC_LITERAL(9, 86, 2), // "id"
QT_MOC_LITERAL(10, 89, 14) // "measureChanged"

    },
    "MaDialog\0okBtnClicked\0\0showDialog\0"
    "paramStr\0watchStr\0hideDialog\0addDyeData\0"
    "typeChanged\0id\0measureChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   55,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x2a /* Public | MethodCloned */,
       3,    0,   63,    2, 0x2a /* Public | MethodCloned */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    1,   66,    2, 0x08 /* Private */,
      10,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void MaDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaDialog *_t = static_cast<MaDialog *>(_o);
        switch (_id) {
        case 0: _t->okBtnClicked(); break;
        case 1: _t->showDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->showDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->showDialog(); break;
        case 4: _t->hideDialog(); break;
        case 5: _t->addDyeData(); break;
        case 6: _t->typeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->measureChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MaDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaDialog::okBtnClicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MaDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MaDialog.data,
      qt_meta_data_MaDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaDialog.stringdata))
        return static_cast<void*>(const_cast< MaDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MaDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MaDialog::okBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
