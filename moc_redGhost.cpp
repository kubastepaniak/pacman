/****************************************************************************
** Meta object code from reading C++ file 'redGhost.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "redGhost.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'redGhost.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RedGhost_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RedGhost_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RedGhost_t qt_meta_stringdata_RedGhost = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RedGhost"
QT_MOC_LITERAL(1, 9, 2), // "go"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 11), // "changeState"
QT_MOC_LITERAL(4, 25, 14) // "updatePosition"

    },
    "RedGhost\0go\0\0changeState\0updatePosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RedGhost[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RedGhost::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RedGhost *_t = static_cast<RedGhost *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->go(); break;
        case 1: _t->changeState(); break;
        case 2: _t->updatePosition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RedGhost::staticMetaObject = {
    { &Ghost::staticMetaObject, qt_meta_stringdata_RedGhost.data,
      qt_meta_data_RedGhost,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RedGhost::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RedGhost::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RedGhost.stringdata0))
        return static_cast<void*>(const_cast< RedGhost*>(this));
    return Ghost::qt_metacast(_clname);
}

int RedGhost::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Ghost::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
