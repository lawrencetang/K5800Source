/****************************************************************************
** Meta object code from reading C++ file 'fittingview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../FittingView/fittingview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fittingview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FittingView_t {
    QByteArrayData data[29];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FittingView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FittingView_t qt_meta_stringdata_FittingView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FittingView"
QT_MOC_LITERAL(1, 12, 13), // "readySaveFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "filename"
QT_MOC_LITERAL(4, 36, 4), // "data"
QT_MOC_LITERAL(5, 41, 6), // "insert"
QT_MOC_LITERAL(6, 48, 2), // "id"
QT_MOC_LITERAL(7, 51, 17), // "SettingDataModel*"
QT_MOC_LITERAL(8, 69, 6), // "sModel"
QT_MOC_LITERAL(9, 76, 6), // "import"
QT_MOC_LITERAL(10, 83, 9), // "headerStr"
QT_MOC_LITERAL(11, 93, 9), // "recordStr"
QT_MOC_LITERAL(12, 103, 15), // "QVector<double>"
QT_MOC_LITERAL(13, 119, 1), // "x"
QT_MOC_LITERAL(14, 121, 1), // "y"
QT_MOC_LITERAL(15, 123, 12), // "QVector<int>"
QT_MOC_LITERAL(16, 136, 1), // "c"
QT_MOC_LITERAL(17, 138, 16), // "QVector<QString>"
QT_MOC_LITERAL(18, 155, 1), // "f"
QT_MOC_LITERAL(19, 157, 7), // "restart"
QT_MOC_LITERAL(20, 165, 5), // "clear"
QT_MOC_LITERAL(21, 171, 12), // "itemSelected"
QT_MOC_LITERAL(22, 184, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(23, 202, 4), // "item"
QT_MOC_LITERAL(24, 207, 11), // "updateByRow"
QT_MOC_LITERAL(25, 219, 3), // "fit"
QT_MOC_LITERAL(26, 223, 6), // "remove"
QT_MOC_LITERAL(27, 230, 10), // "updateUnit"
QT_MOC_LITERAL(28, 241, 4) // "unit"

    },
    "FittingView\0readySaveFile\0\0filename\0"
    "data\0insert\0id\0SettingDataModel*\0"
    "sModel\0import\0headerStr\0recordStr\0"
    "QVector<double>\0x\0y\0QVector<int>\0c\0"
    "QVector<QString>\0f\0restart\0clear\0"
    "itemSelected\0QTableWidgetItem*\0item\0"
    "updateByRow\0fit\0remove\0updateUnit\0"
    "unit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FittingView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   69,    2, 0x0a /* Public */,
       9,    6,   74,    2, 0x0a /* Public */,
      19,    0,   87,    2, 0x0a /* Public */,
      20,    0,   88,    2, 0x0a /* Public */,
      21,    1,   89,    2, 0x08 /* Private */,
      24,    1,   92,    2, 0x08 /* Private */,
      25,    0,   95,    2, 0x08 /* Private */,
      26,    0,   96,    2, 0x08 /* Private */,
      27,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 12, 0x80000000 | 12, 0x80000000 | 15, 0x80000000 | 17,   10,   11,   13,   14,   16,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

void FittingView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FittingView *_t = static_cast<FittingView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readySaveFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 1: _t->insert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< SettingDataModel*(*)>(_a[2]))); break;
        case 2: { QString _r = _t->import((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QVector<double>(*)>(_a[3])),(*reinterpret_cast< QVector<double>(*)>(_a[4])),(*reinterpret_cast< QVector<int>(*)>(_a[5])),(*reinterpret_cast< QVector<QString>(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->restart(); break;
        case 4: _t->clear(); break;
        case 5: _t->itemSelected((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->updateByRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->fit(); break;
        case 8: _t->remove(); break;
        case 9: _t->updateUnit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 5:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            case 3:
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FittingView::*_t)(QString , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FittingView::readySaveFile)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FittingView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_FittingView.data,
      qt_meta_data_FittingView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FittingView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FittingView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FittingView.stringdata0))
        return static_cast<void*>(const_cast< FittingView*>(this));
    return QFrame::qt_metacast(_clname);
}

int FittingView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FittingView::readySaveFile(QString _t1, QStringList _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
