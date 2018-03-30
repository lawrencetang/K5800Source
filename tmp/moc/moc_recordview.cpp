/****************************************************************************
** Meta object code from reading C++ file 'recordview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RecordView/recordview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recordview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RecordView_t {
    QByteArrayData data[17];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordView_t qt_meta_stringdata_RecordView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RecordView"
QT_MOC_LITERAL(1, 11, 8), // "moveCoef"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "coef"
QT_MOC_LITERAL(4, 26, 7), // "clearid"
QT_MOC_LITERAL(5, 34, 14), // "sampleLEchange"
QT_MOC_LITERAL(6, 49, 4), // "text"
QT_MOC_LITERAL(7, 54, 13), // "sendConcValue"
QT_MOC_LITERAL(8, 68, 12), // "setRecordDir"
QT_MOC_LITERAL(9, 81, 3), // "dir"
QT_MOC_LITERAL(10, 85, 12), // "insertRecord"
QT_MOC_LITERAL(11, 98, 9), // "recordStr"
QT_MOC_LITERAL(12, 108, 4), // "save"
QT_MOC_LITERAL(13, 113, 4), // "move"
QT_MOC_LITERAL(14, 118, 7), // "hideRow"
QT_MOC_LITERAL(15, 126, 10), // "hideColumn"
QT_MOC_LITERAL(16, 137, 5) // "clear"

    },
    "RecordView\0moveCoef\0\0coef\0clearid\0"
    "sampleLEchange\0text\0sendConcValue\0"
    "setRecordDir\0dir\0insertRecord\0recordStr\0"
    "save\0move\0hideRow\0hideColumn\0clear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x0a /* Public */,
      16,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecordView *_t = static_cast<RecordView *>(_o);
        switch (_id) {
        case 0: _t->moveCoef((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->clearid(); break;
        case 2: _t->sampleLEchange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendConcValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setRecordDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->insertRecord((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->save(); break;
        case 7: _t->move(); break;
        case 8: _t->hideRow(); break;
        case 9: _t->hideColumn(); break;
        case 10: _t->clear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RecordView::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecordView::moveCoef)) {
                *result = 0;
            }
        }
        {
            typedef void (RecordView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecordView::clearid)) {
                *result = 1;
            }
        }
        {
            typedef void (RecordView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecordView::sampleLEchange)) {
                *result = 2;
            }
        }
        {
            typedef void (RecordView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecordView::sendConcValue)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject RecordView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_RecordView.data,
      qt_meta_data_RecordView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RecordView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RecordView.stringdata))
        return static_cast<void*>(const_cast< RecordView*>(this));
    return QFrame::qt_metacast(_clname);
}

int RecordView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void RecordView::moveCoef(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RecordView::clearid()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void RecordView::sampleLEchange(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RecordView::sendConcValue(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
