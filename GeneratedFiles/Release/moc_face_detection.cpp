/****************************************************************************
** Meta object code from reading C++ file 'face_detection.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../face_detection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'face_detection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Face_detection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      42,   15,   15,   15, 0x08,
      75,   15,   15,   15, 0x08,
      89,   15,   15,   15, 0x08,
     104,   15,   15,   15, 0x08,
     116,   15,   15,   15, 0x08,
     136,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Face_detection[] = {
    "Face_detection\0\0on_actionCapture_opencv()\0"
    "on_actionCapture_opencv_camera()\0"
    "knopka_play()\0knopka_obzor()\0fps_count()\0"
    "radio_button_fail()\0radio_button_camera()\0"
};

void Face_detection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Face_detection *_t = static_cast<Face_detection *>(_o);
        switch (_id) {
        case 0: _t->on_actionCapture_opencv(); break;
        case 1: _t->on_actionCapture_opencv_camera(); break;
        case 2: _t->knopka_play(); break;
        case 3: _t->knopka_obzor(); break;
        case 4: _t->fps_count(); break;
        case 5: _t->radio_button_fail(); break;
        case 6: _t->radio_button_camera(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Face_detection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Face_detection::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Face_detection,
      qt_meta_data_Face_detection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Face_detection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Face_detection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Face_detection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Face_detection))
        return static_cast<void*>(const_cast< Face_detection*>(this));
    return QWidget::qt_metacast(_clname);
}

int Face_detection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
