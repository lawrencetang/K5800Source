/****************************************************************************
** Meta object code from reading C++ file 'spectrograph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Spectrograph/spectrograph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spectrograph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Spectrograph_t {
    QByteArrayData data[14];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Spectrograph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Spectrograph_t qt_meta_stringdata_Spectrograph = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Spectrograph"
QT_MOC_LITERAL(1, 13, 5), // "error"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "code"
QT_MOC_LITERAL(4, 25, 7), // "message"
QT_MOC_LITERAL(5, 33, 4), // "open"
QT_MOC_LITERAL(6, 38, 5), // "close"
QT_MOC_LITERAL(7, 44, 7), // "measure"
QT_MOC_LITERAL(8, 52, 13), // "QVector<int>&"
QT_MOC_LITERAL(9, 66, 10), // "waveLength"
QT_MOC_LITERAL(10, 77, 16), // "QVector<double>&"
QT_MOC_LITERAL(11, 94, 8), // "spectrum"
QT_MOC_LITERAL(12, 103, 5), // "count"
QT_MOC_LITERAL(13, 109, 12) // "serialNumber"

    },
    "Spectrograph\0error\0\0code\0message\0open\0"
    "close\0measure\0QVector<int>&\0waveLength\0"
    "QVector<double>&\0spectrum\0count\0"
    "serialNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Spectrograph[] = {

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
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    3,   51,    2, 0x0a /* Public */,
       7,    2,   58,    2, 0x2a /* Public | MethodCloned */,
      13,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 8, 0x80000000 | 10, QMetaType::Int,    9,   11,   12,
    QMetaType::Int, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::QString,

       0        // eod
};

void Spectrograph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Spectrograph *_t = static_cast<Spectrograph *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: { bool _r = _t->open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->close(); break;
        case 3: { int _r = _t->measure((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->measure((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->serialNumber();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Spectrograph::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Spectrograph::error)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Spectrograph::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Spectrograph.data,
      qt_meta_data_Spectrograph,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Spectrograph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Spectrograph::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Spectrograph.stringdata0))
        return static_cast<void*>(const_cast< Spectrograph*>(this));
    return QObject::qt_metacast(_clname);
}

int Spectrograph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Spectrograph::error(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
