/****************************************************************************
** Meta object code from reading C++ file 'ProcessingThread.h'
**
** Created: Mon Sep 12 10:57:51 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jm/ProcessingThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProcessingThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessingThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,
      41,   17,   17,   17, 0x05,
      61,   56,   17,   17, 0x05,
      81,   17,   17,   17, 0x05,
      98,   56,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,   17,   17,   17, 0x0a,
     138,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProcessingThread[] = {
    "ProcessingThread\0\0frame\0newFrame(QImage)\0"
    "clearMsgText()\0text\0newTextMsg(QString)\0"
    "clearHistBoard()\0updateHistBoard(QString)\0"
    "deckShuffled()\0setBlack()\0"
};

const QMetaObject ProcessingThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ProcessingThread,
      qt_meta_data_ProcessingThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessingThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessingThread))
        return static_cast<void*>(const_cast< ProcessingThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ProcessingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: clearMsgText(); break;
        case 2: newTextMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: clearHistBoard(); break;
        case 4: updateHistBoard((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: deckShuffled(); break;
        case 6: setBlack(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ProcessingThread::newFrame(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProcessingThread::clearMsgText()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ProcessingThread::newTextMsg(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProcessingThread::clearHistBoard()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ProcessingThread::updateHistBoard(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
