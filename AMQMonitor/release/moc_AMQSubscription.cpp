/****************************************************************************
** Meta object code from reading C++ file 'AMQSubscription.h'
**
** Created: Sat Mar 21 13:23:35 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AMQSubscription.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AMQSubscription.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AMQSubscription[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      62,   16,   16,   16, 0x08,
      96,   16,   16,   16, 0x08,
     137,   16,   16,   16, 0x08,
     178,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AMQSubscription[] = {
    "AMQSubscription\0\0"
    "stateChanged(AMQConnection::ConnectionState)\0"
    "receivedFrame(AMQConnectionFrame)\0"
    "receivedReceiptFrame(AMQConnectionFrame)\0"
    "receivedMessageFrame(AMQConnectionFrame)\0"
    "sentFrame(AMQConnectionFrame)\0"
};

const QMetaObject AMQSubscription::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AMQSubscription,
      qt_meta_data_AMQSubscription, 0 }
};

const QMetaObject *AMQSubscription::metaObject() const
{
    return &staticMetaObject;
}

void *AMQSubscription::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AMQSubscription))
        return static_cast<void*>(const_cast< AMQSubscription*>(this));
    return QObject::qt_metacast(_clname);
}

int AMQSubscription::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< AMQConnection::ConnectionState(*)>(_a[1]))); break;
        case 1: receivedFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 2: receivedReceiptFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 3: receivedMessageFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 4: sentFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
