/****************************************************************************
** Meta object code from reading C++ file 'tempcontrolview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TempControlView/tempcontrolview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tempcontrolview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TempControlView_t {
    QByteArrayData data[9];
    char stringdata[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TempControlView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TempControlView_t qt_meta_stringdata_TempControlView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TempControlView"
QT_MOC_LITERAL(1, 16, 17), // "onStartBtnClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "setTargetValue"
QT_MOC_LITERAL(4, 50, 5), // "value"
QT_MOC_LITERAL(5, 56, 15), // "setCurrentValue"
QT_MOC_LITERAL(6, 72, 15), // "readTemperature"
QT_MOC_LITERAL(7, 88, 9), // "pauseRead"
QT_MOC_LITERAL(8, 98, 2) // "ok"

    },
    "TempControlView\0onStartBtnClicked\0\0"
    "setTargetValue\0value\0setCurrentValue\0"
    "readTemperature\0pauseRead\0ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TempControlView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void TempControlView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TempControlView *_t = static_cast<TempControlView *>(_o);
        switch (_id) {
        case 0: _t->onStartBtnClicked(); break;
        case 1: _t->setTargetValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setCurrentValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->readTemperature(); break;
        case 4: _t->pauseRead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TempControlView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_TempControlView.data,
      qt_meta_data_TempControlView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TempControlView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TempControlView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TempControlView.stringdata))
        return static_cast<void*>(const_cast< TempControlView*>(this));
    return QFrame::qt_metacast(_clname);
}

int TempControlView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
