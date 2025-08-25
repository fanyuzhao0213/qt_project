/****************************************************************************
** Meta object code from reading C++ file 'serialmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../fyz_smart_home/serialmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serialmanager_t {
    QByteArrayData data[15];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serialmanager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serialmanager_t qt_meta_stringdata_serialmanager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "serialmanager"
QT_MOC_LITERAL(1, 14, 12), // "dataReceived"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "data"
QT_MOC_LITERAL(4, 33, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 47, 8), // "errorMsg"
QT_MOC_LITERAL(6, 56, 12), // "serialOpened"
QT_MOC_LITERAL(7, 69, 12), // "serialClosed"
QT_MOC_LITERAL(8, 82, 15), // "portListUpdated"
QT_MOC_LITERAL(9, 98, 5), // "ports"
QT_MOC_LITERAL(10, 104, 9), // "scanPorts"
QT_MOC_LITERAL(11, 114, 14), // "readSerialData"
QT_MOC_LITERAL(12, 129, 11), // "handleError"
QT_MOC_LITERAL(13, 141, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(14, 170, 5) // "error"

    },
    "serialmanager\0dataReceived\0\0data\0"
    "errorOccurred\0errorMsg\0serialOpened\0"
    "serialClosed\0portListUpdated\0ports\0"
    "scanPorts\0readSerialData\0handleError\0"
    "QSerialPort::SerialPortError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serialmanager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,
       7,    0,   61,    2, 0x06 /* Public */,
       8,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   65,    2, 0x0a /* Public */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void serialmanager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serialmanager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->serialOpened(); break;
        case 3: _t->serialClosed(); break;
        case 4: _t->portListUpdated((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 5: _t->scanPorts(); break;
        case 6: _t->readSerialData(); break;
        case 7: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (serialmanager::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialmanager::dataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (serialmanager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialmanager::errorOccurred)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (serialmanager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialmanager::serialOpened)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (serialmanager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialmanager::serialClosed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (serialmanager::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialmanager::portListUpdated)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serialmanager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_serialmanager.data,
    qt_meta_data_serialmanager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serialmanager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serialmanager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serialmanager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int serialmanager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void serialmanager::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void serialmanager::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void serialmanager::serialOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void serialmanager::serialClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void serialmanager::portListUpdated(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
