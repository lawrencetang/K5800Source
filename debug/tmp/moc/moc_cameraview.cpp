/****************************************************************************
** Meta object code from reading C++ file 'cameraview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CameraView/cameraview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraView_t {
    QByteArrayData data[15];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraView_t qt_meta_stringdata_CameraView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CameraView"
QT_MOC_LITERAL(1, 11, 9), // "autoCheck"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "upDateImage"
QT_MOC_LITERAL(4, 34, 8), // "fileName"
QT_MOC_LITERAL(5, 43, 10), // "openCamera"
QT_MOC_LITERAL(6, 54, 9), // "readFrame"
QT_MOC_LITERAL(7, 64, 10), // "showCamera"
QT_MOC_LITERAL(8, 75, 6), // "remove"
QT_MOC_LITERAL(9, 82, 6), // "saveAs"
QT_MOC_LITERAL(10, 89, 17), // "showSelectedImage"
QT_MOC_LITERAL(11, 107, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(12, 124, 4), // "item"
QT_MOC_LITERAL(13, 129, 15), // "showPageChanged"
QT_MOC_LITERAL(14, 145, 2) // "id"

    },
    "CameraView\0autoCheck\0\0upDateImage\0"
    "fileName\0openCamera\0readFrame\0showCamera\0"
    "remove\0saveAs\0showSelectedImage\0"
    "QListWidgetItem*\0item\0showPageChanged\0"
    "id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    1,   68,    2, 0x08 /* Private */,
      13,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void CameraView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraView *_t = static_cast<CameraView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->autoCheck();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->upDateImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->openCamera(); break;
        case 3: _t->readFrame(); break;
        case 4: _t->showCamera(); break;
        case 5: _t->remove(); break;
        case 6: _t->saveAs(); break;
        case 7: _t->showSelectedImage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->showPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CameraView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CameraView.data,
      qt_meta_data_CameraView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraView.stringdata0))
        return static_cast<void*>(const_cast< CameraView*>(this));
    return QFrame::qt_metacast(_clname);
}

int CameraView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
