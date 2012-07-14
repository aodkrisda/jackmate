/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Mon Sep 12 10:57:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jm/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      65,   56,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      87,   11,   11,   11, 0x0a,
     105,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     132,   11,   11,   11, 0x0a,
     151,   11,   11,   11, 0x0a,
     185,  179,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0p_flags\0"
    "newProcessingFlags(ProcessingFlags)\0"
    "taskData\0newTaskData(TaskData)\0"
    "connectToCamera()\0disconnectCamera()\0"
    "about()\0clearImageBuffer()\0"
    "updateMouseCursorPosLabel()\0frame\0"
    "updateFrame(QImage)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newProcessingFlags((*reinterpret_cast< ProcessingFlags(*)>(_a[1]))); break;
        case 1: newTaskData((*reinterpret_cast< TaskData(*)>(_a[1]))); break;
        case 2: connectToCamera(); break;
        case 3: disconnectCamera(); break;
        case 4: about(); break;
        case 5: clearImageBuffer(); break;
        case 6: updateMouseCursorPosLabel(); break;
        case 7: updateFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newProcessingFlags(ProcessingFlags _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::newTaskData(TaskData _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
