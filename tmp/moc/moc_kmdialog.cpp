/****************************************************************************
** Meta object code from reading C++ file 'kmdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SettingsView/kmdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kmdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KmDialog_t {
    QByteArrayData data[8];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KmDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KmDialog_t qt_meta_stringdata_KmDialog = {
    {
QT_MOC_LITERAL(0, 0, 8), // "KmDialog"
QT_MOC_LITERAL(1, 9, 12), // "okBtnClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "showDialog"
QT_MOC_LITERAL(4, 34, 8), // "paramStr"
QT_MOC_LITERAL(5, 43, 10), // "hideDialog"
QT_MOC_LITERAL(6, 54, 11), // "typeChanged"
QT_MOC_LITERAL(7, 66, 2) // "id"

    },
    "KmDialog\0okBtnClicked\0\0showDialog\0"
    "paramStr\0hideDialog\0typeChanged\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KmDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x0a /* Public */,
       3,    0,   43,    2, 0x2a /* Public | MethodCloned */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void KmDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KmDialog *_t = static_cast<KmDialog *>(_o);
        switch (_id) {
        case 0: _t->okBtnClicked(); break;
        case 1: _t->showDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->showDialog(); break;
        case 3: _t->hideDialog(); break;
        case 4: _t->typeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KmDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KmDialog::okBtnClicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KmDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KmDialog.data,
      qt_meta_data_KmDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KmDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KmDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KmDialog.stringdata))
        return static_cast<void*>(const_cast< KmDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int KmDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void KmDialog::okBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE