/****************************************************************************
** Meta object code from reading C++ file 'checkview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CheckView/checkview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CheckView_t {
    QByteArrayData data[16];
    char stringdata[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CheckView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CheckView_t qt_meta_stringdata_CheckView = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CheckView"
QT_MOC_LITERAL(1, 10, 8), // "checking"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 2), // "ok"
QT_MOC_LITERAL(4, 23, 9), // "clearPlot"
QT_MOC_LITERAL(5, 33, 12), // "deviceEnable"
QT_MOC_LITERAL(6, 46, 9), // "saveImage"
QT_MOC_LITERAL(7, 56, 16), // "controllerOption"
QT_MOC_LITERAL(8, 73, 11), // "excuteCheck"
QT_MOC_LITERAL(9, 85, 14), // "checkMainboard"
QT_MOC_LITERAL(10, 100, 15), // "checkMicroscale"
QT_MOC_LITERAL(11, 116, 11), // "checkCuttve"
QT_MOC_LITERAL(12, 128, 16), // "checkTemperature"
QT_MOC_LITERAL(13, 145, 14), // "autoCheckError"
QT_MOC_LITERAL(14, 160, 14), // "autoConnection"
QT_MOC_LITERAL(15, 175, 11) // "changeModel"

    },
    "CheckView\0checking\0\0ok\0clearPlot\0"
    "deviceEnable\0saveImage\0controllerOption\0"
    "excuteCheck\0checkMainboard\0checkMicroscale\0"
    "checkCuttve\0checkTemperature\0"
    "autoCheckError\0autoConnection\0changeModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CheckView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    0,   82,    2, 0x06 /* Public */,
       5,    1,   83,    2, 0x06 /* Public */,
       6,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   87,    2, 0x0a /* Public */,
       8,    0,   88,    2, 0x0a /* Public */,
       9,    0,   89,    2, 0x0a /* Public */,
      10,    0,   90,    2, 0x0a /* Public */,
      11,    0,   91,    2, 0x0a /* Public */,
      12,    0,   92,    2, 0x0a /* Public */,
      13,    0,   93,    2, 0x0a /* Public */,
      14,    0,   94,    2, 0x0a /* Public */,
      15,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void CheckView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CheckView *_t = static_cast<CheckView *>(_o);
        switch (_id) {
        case 0: _t->checking((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->clearPlot(); break;
        case 2: _t->deviceEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->saveImage(); break;
        case 4: _t->controllerOption(); break;
        case 5: _t->excuteCheck(); break;
        case 6: _t->checkMainboard(); break;
        case 7: _t->checkMicroscale(); break;
        case 8: _t->checkCuttve(); break;
        case 9: _t->checkTemperature(); break;
        case 10: _t->autoCheckError(); break;
        case 11: _t->autoConnection(); break;
        case 12: _t->changeModel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CheckView::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckView::checking)) {
                *result = 0;
            }
        }
        {
            typedef void (CheckView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckView::clearPlot)) {
                *result = 1;
            }
        }
        {
            typedef void (CheckView::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckView::deviceEnable)) {
                *result = 2;
            }
        }
        {
            typedef void (CheckView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckView::saveImage)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject CheckView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CheckView.data,
      qt_meta_data_CheckView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CheckView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CheckView.stringdata))
        return static_cast<void*>(const_cast< CheckView*>(this));
    return QFrame::qt_metacast(_clname);
}

int CheckView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CheckView::checking(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CheckView::clearPlot()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CheckView::deviceEnable(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CheckView::saveImage()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
