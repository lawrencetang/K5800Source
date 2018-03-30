/****************************************************************************
** Meta object code from reading C++ file 'datalayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Controller/datalayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datalayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataLayer_t {
    QByteArrayData data[9];
    char stringdata[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataLayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataLayer_t qt_meta_stringdata_DataLayer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DataLayer"
QT_MOC_LITERAL(1, 10, 11), // "vesselClose"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 2), // "ok"
QT_MOC_LITERAL(4, 26, 16), // "temperatureValue"
QT_MOC_LITERAL(5, 43, 11), // "temperature"
QT_MOC_LITERAL(6, 55, 12), // "currentAngle"
QT_MOC_LITERAL(7, 68, 5), // "angle"
QT_MOC_LITERAL(8, 74, 18) // "readFromSerialPort"

    },
    "DataLayer\0vesselClose\0\0ok\0temperatureValue\0"
    "temperature\0currentAngle\0angle\0"
    "readFromSerialPort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataLayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DataLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataLayer *_t = static_cast<DataLayer *>(_o);
        switch (_id) {
        case 0: _t->vesselClose((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->temperatureValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->currentAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->readFromSerialPort(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataLayer::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataLayer::vesselClose)) {
                *result = 0;
            }
        }
        {
            typedef void (DataLayer::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataLayer::temperatureValue)) {
                *result = 1;
            }
        }
        {
            typedef void (DataLayer::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataLayer::currentAngle)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject DataLayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataLayer.data,
      qt_meta_data_DataLayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataLayer.stringdata))
        return static_cast<void*>(const_cast< DataLayer*>(this));
    return QObject::qt_metacast(_clname);
}

int DataLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DataLayer::vesselClose(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataLayer::temperatureValue(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataLayer::currentAngle(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
