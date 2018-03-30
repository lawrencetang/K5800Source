/****************************************************************************
** Meta object code from reading C++ file 'dydialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingsView/dydialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DyDialog_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DyDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DyDialog_t qt_meta_stringdata_DyDialog = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DyDialog"
QT_MOC_LITERAL(1, 9, 12), // "okBtnClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "showDialog"
QT_MOC_LITERAL(4, 34, 8), // "paramStr"
QT_MOC_LITERAL(5, 43, 8), // "watchStr"
QT_MOC_LITERAL(6, 52, 10), // "hideDialog"
QT_MOC_LITERAL(7, 63, 15), // "wathLabelEnable"
QT_MOC_LITERAL(8, 79, 2) // "ok"

    },
    "DyDialog\0okBtnClicked\0\0showDialog\0"
    "paramStr\0watchStr\0hideDialog\0"
    "wathLabelEnable\0ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DyDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   45,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x2a /* Public | MethodCloned */,
       3,    0,   53,    2, 0x2a /* Public | MethodCloned */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void DyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DyDialog *_t = static_cast<DyDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->okBtnClicked(); break;
        case 1: _t->showDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->showDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->showDialog(); break;
        case 4: _t->hideDialog(); break;
        case 5: _t->wathLabelEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DyDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DyDialog::okBtnClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DyDialog.data,
      qt_meta_data_DyDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DyDialog.stringdata0))
        return static_cast<void*>(const_cast< DyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DyDialog::okBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
