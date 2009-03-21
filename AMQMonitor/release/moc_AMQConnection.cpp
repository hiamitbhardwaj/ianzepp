/****************************************************************************
** Meta object code from reading C++ file 'AMQConnection.h'
**
** Created: Sat Mar 21 13:23:36 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AMQConnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AMQConnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AMQConnection[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      45,   14,   14,   14, 0x05,
      79,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     109,   14,   14,   14, 0x0a,
     125,   14,   14,   14, 0x0a,
     155,   14,   14,   14, 0x0a,
     181,   14,   14,   14, 0x0a,
     214,   14,   14,   14, 0x08,
     232,   14,   14,   14, 0x08,
     253,   14,   14,   14, 0x08,
     290,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AMQConnection[] = {
    "AMQConnection\0\0stateChanged(ConnectionState)\0"
    "receivedFrame(AMQConnectionFrame)\0"
    "sentFrame(AMQConnectionFrame)\0"
    "connectToHost()\0sendFrame(AMQConnectionFrame)\0"
    "sendFrameData(QByteArray)\0"
    "receiveFrame(AMQConnectionFrame)\0"
    "socketConnected()\0socketDisconnected()\0"
    "socketError(QTcpSocket::SocketError)\0"
    "socketProcessBuffer()\0"
};

const QMetaObject AMQConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AMQConnection,
      qt_meta_data_AMQConnection, 0 }
};

const QMetaObject *AMQConnection::metaObject() const
{
    return &staticMetaObject;
}

void *AMQConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AMQConnection))
        return static_cast<void*>(const_cast< AMQConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int AMQConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< ConnectionState(*)>(_a[1]))); break;
        case 1: receivedFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 2: sentFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 3: connectToHost(); break;
        case 4: sendFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 5: sendFrameData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: receiveFrame((*reinterpret_cast< AMQConnectionFrame(*)>(_a[1]))); break;
        case 7: socketConnected(); break;
        case 8: socketDisconnected(); break;
        case 9: socketError((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 10: socketProcessBuffer(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AMQConnection::stateChanged(ConnectionState _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AMQConnection::receivedFrame(AMQConnectionFrame _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AMQConnection::sentFrame(AMQConnectionFrame _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
