/****************************************************************************
** Meta object code from reading C++ file 'Session.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../project/Session.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Session.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Session_t {
    QByteArrayData data[12];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Session_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Session_t qt_meta_stringdata_Session = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Session"
QT_MOC_LITERAL(1, 8, 12), // "OnServerEcho"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "message"
QT_MOC_LITERAL(4, 30, 14), // "OnServerEcho__"
QT_MOC_LITERAL(5, 45, 13), // "OnServerEcho_"
QT_MOC_LITERAL(6, 59, 1), // "t"
QT_MOC_LITERAL(7, 61, 14), // "OnLoginSuccess"
QT_MOC_LITERAL(8, 76, 13), // "ClientSocket*"
QT_MOC_LITERAL(9, 90, 12), // "clientSocket"
QT_MOC_LITERAL(10, 103, 18), // "OnDownloadFinished"
QT_MOC_LITERAL(11, 122, 14) // "OnUploadFished"

    },
    "Session\0OnServerEcho\0\0message\0"
    "OnServerEcho__\0OnServerEcho_\0t\0"
    "OnLoginSuccess\0ClientSocket*\0clientSocket\0"
    "OnDownloadFinished\0OnUploadFished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Session[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    2,   53,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x26 /* Public | MethodCloned */,
       7,    1,   61,    2, 0x06 /* Public */,
      10,    0,   64,    2, 0x06 /* Public */,
      11,    0,   65,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    6,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Session::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Session *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnServerEcho((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->OnServerEcho__(); break;
        case 2: _t->OnServerEcho_((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->OnServerEcho_((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnLoginSuccess((*reinterpret_cast< ClientSocket*(*)>(_a[1]))); break;
        case 5: _t->OnDownloadFinished(); break;
        case 6: _t->OnUploadFished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Session::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnServerEcho)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnServerEcho__)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Session::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnServerEcho_)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Session::*)(ClientSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnLoginSuccess)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnDownloadFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Session::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Session::OnUploadFished)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Session::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Session.data,
    qt_meta_data_Session,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Session::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Session::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Session.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Session::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Session::OnServerEcho(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Session::OnServerEcho__()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Session::OnServerEcho_(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void Session::OnLoginSuccess(ClientSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Session::OnDownloadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Session::OnUploadFished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
