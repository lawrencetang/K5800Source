/****************************************************************************
** Meta object code from reading C++ file 'dataview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DataView/dataview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataView_t {
    QByteArrayData data[18];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataView_t qt_meta_stringdata_DataView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataView"
QT_MOC_LITERAL(1, 9, 10), // "dirChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "name"
QT_MOC_LITERAL(4, 26, 13), // "fileReadReady"
QT_MOC_LITERAL(5, 40, 4), // "type"
QT_MOC_LITERAL(6, 45, 8), // "filename"
QT_MOC_LITERAL(7, 54, 13), // "setCurrentDir"
QT_MOC_LITERAL(8, 68, 12), // "showDataFile"
QT_MOC_LITERAL(9, 81, 7), // "dirname"
QT_MOC_LITERAL(10, 89, 10), // "updateView"
QT_MOC_LITERAL(11, 100, 12), // "itemSelected"
QT_MOC_LITERAL(12, 113, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 130, 4), // "item"
QT_MOC_LITERAL(14, 135, 12), // "saveDataFile"
QT_MOC_LITERAL(15, 148, 4), // "data"
QT_MOC_LITERAL(16, 153, 6), // "remove"
QT_MOC_LITERAL(17, 160, 6) // "moveTo"

    },
    "DataView\0dirChanged\0\0name\0fileReadReady\0"
    "type\0filename\0setCurrentDir\0showDataFile\0"
    "dirname\0updateView\0itemSelected\0"
    "QListWidgetItem*\0item\0saveDataFile\0"
    "data\0remove\0moveTo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    2,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   72,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
      10,    1,   78,    2, 0x0a /* Public */,
      11,    1,   81,    2, 0x0a /* Public */,
      14,    1,   84,    2, 0x0a /* Public */,
      14,    2,   87,    2, 0x0a /* Public */,
      16,    0,   92,    2, 0x0a /* Public */,
      17,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QStringList,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    6,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DataView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataView *_t = static_cast<DataView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dirChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->fileReadReady((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->setCurrentDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->showDataFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->updateView((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->itemSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->saveDataFile((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->saveDataFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 8: _t->remove(); break;
        case 9: _t->moveTo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataView::dirChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DataView::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataView::fileReadReady)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DataView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_DataView.data,
      qt_meta_data_DataView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataView.stringdata0))
        return static_cast<void*>(const_cast< DataView*>(this));
    return QFrame::qt_metacast(_clname);
}

int DataView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DataView::dirChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataView::fileReadReady(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
