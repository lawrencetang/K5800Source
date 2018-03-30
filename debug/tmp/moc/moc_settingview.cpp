/****************************************************************************
** Meta object code from reading C++ file 'settingview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingsView/settingview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SettingView_t {
    QByteArrayData data[20];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingView_t qt_meta_stringdata_SettingView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SettingView"
QT_MOC_LITERAL(1, 12, 8), // "hideView"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "status"
QT_MOC_LITERAL(4, 29, 11), // "changeTitle"
QT_MOC_LITERAL(5, 41, 5), // "title"
QT_MOC_LITERAL(6, 47, 13), // "subDirChanged"
QT_MOC_LITERAL(7, 61, 6), // "subDir"
QT_MOC_LITERAL(8, 68, 17), // "changeAutoMeasure"
QT_MOC_LITERAL(9, 86, 8), // "changeId"
QT_MOC_LITERAL(10, 95, 15), // "recordSendvalue"
QT_MOC_LITERAL(11, 111, 3), // "add"
QT_MOC_LITERAL(12, 115, 4), // "edit"
QT_MOC_LITERAL(13, 120, 6), // "remove"
QT_MOC_LITERAL(14, 127, 2), // "ok"
QT_MOC_LITERAL(15, 130, 6), // "modify"
QT_MOC_LITERAL(16, 137, 8), // "updateOp"
QT_MOC_LITERAL(17, 146, 16), // "changeMeasureWay"
QT_MOC_LITERAL(18, 163, 18), // "displaySettingInfo"
QT_MOC_LITERAL(19, 182, 7) // "clearid"

    },
    "SettingView\0hideView\0\0status\0changeTitle\0"
    "title\0subDirChanged\0subDir\0changeAutoMeasure\0"
    "changeId\0recordSendvalue\0add\0edit\0"
    "remove\0ok\0modify\0updateOp\0changeMeasureWay\0"
    "displaySettingInfo\0clearid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   90,    2, 0x0a /* Public */,
       8,    0,   93,    2, 0x0a /* Public */,
       9,    1,   94,    2, 0x0a /* Public */,
      11,    0,   97,    2, 0x08 /* Private */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,
      16,    1,  102,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingView *_t = static_cast<SettingView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->subDirChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changeAutoMeasure(); break;
        case 4: _t->changeId((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->add(); break;
        case 6: _t->edit(); break;
        case 7: _t->remove(); break;
        case 8: _t->ok(); break;
        case 9: _t->modify(); break;
        case 10: _t->updateOp((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->changeMeasureWay(); break;
        case 12: _t->displaySettingInfo(); break;
        case 13: _t->clearid(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingView::hideView)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SettingView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingView::changeTitle)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SettingView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SettingView.data,
      qt_meta_data_SettingView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingView.stringdata0))
        return static_cast<void*>(const_cast< SettingView*>(this));
    return QFrame::qt_metacast(_clname);
}

int SettingView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SettingView::hideView(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingView::changeTitle(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
