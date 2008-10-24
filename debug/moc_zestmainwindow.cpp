/****************************************************************************
** Meta object code from reading C++ file 'zestmainwindow.h'
**
** Created: Fri Oct 24 21:21:12 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/widgets/zestmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zestmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ZestMainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      45,   15,   15,   15, 0x08,
      68,   15,   15,   15, 0x08,
      92,   15,   15,   15, 0x08,
     117,   15,   15,   15, 0x08,
     143,   15,   15,   15, 0x08,
     169,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ZestMainWindow[] = {
    "ZestMainWindow\0\0on_tempoEdit_returnPressed()\0"
    "on_tapButton_pressed()\0on_plainRadio_clicked()\0"
    "on_dottedRadio_clicked()\0"
    "on_tripletRadio_clicked()\0"
    "on_actionQuit_triggered()\0"
    "on_actionAbout_triggered()\0"
};

const QMetaObject ZestMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ZestMainWindow,
      qt_meta_data_ZestMainWindow, 0 }
};

const QMetaObject *ZestMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *ZestMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZestMainWindow))
	return static_cast<void*>(const_cast< ZestMainWindow*>(this));
    if (!strcmp(_clname, "Observer"))
	return static_cast< Observer*>(const_cast< ZestMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ZestMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_tempoEdit_returnPressed(); break;
        case 1: on_tapButton_pressed(); break;
        case 2: on_plainRadio_clicked(); break;
        case 3: on_dottedRadio_clicked(); break;
        case 4: on_tripletRadio_clicked(); break;
        case 5: on_actionQuit_triggered(); break;
        case 6: on_actionAbout_triggered(); break;
        }
        _id -= 7;
    }
    return _id;
}
