/****************************************************************************
** Meta object code from reading C++ file 'lsy_qrs.h'
**
** Created: Wed Apr 23 13:45:25 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lsy_qrs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lsy_qrs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LSY_QRS[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,    8,    8,    8, 0x08,
      60,    8,    8,    8, 0x08,
      74,    8,    8,    8, 0x08,
      88,    8,    8,    8, 0x08,
     106,    8,    8,    8, 0x08,
     122,    8,    8,    8, 0x08,
     137,    8,    8,    8, 0x08,
     152,    8,    8,    8, 0x08,
     167,    8,    8,    8, 0x08,
     182,    8,    8,    8, 0x08,
     199,    8,    8,    8, 0x08,
     222,    8,    8,    8, 0x08,
     243,    8,    8,    8, 0x08,
     259,    9,    8,    8, 0x08,
     289,    8,    8,    8, 0x08,
     305,    8,    8,    8, 0x08,
     322,    8,    8,    8, 0x08,
     344,    8,    8,    8, 0x08,
     377,  365,    8,    8, 0x08,
     415,  365,    8,    8, 0x08,
     454,  365,    8,    8, 0x08,
     493,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LSY_QRS[] = {
    "LSY_QRS\0\0moduleTree\0ContextMenuShow(QTreeWidget*)\0"
    "LayView()\0ObjMeanView()\0FeatureView()\0"
    "ClassResultView()\0ObjBorderView()\0"
    "MultiSegment()\0SelectObjLay()\0"
    "DelectObjLay()\0ClassSegment()\0"
    "Classification()\0DeleteClassification()\0"
    "EditClassification()\0EditClassifie()\0"
    "InsertClassifie(QTreeWidget*)\0"
    "CopyClassifie()\0DeletClassifie()\0"
    "OutputClassifieRule()\0InputClassifieRule()\0"
    "item,column\0SelectXingZheng(QTreeWidgetItem*,int)\0"
    "SelectXingZheng1(QTreeWidgetItem*,int)\0"
    "SelectXingZheng2(QTreeWidgetItem*,int)\0"
    "GetRasterImgArry()\0"
};

void LSY_QRS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LSY_QRS *_t = static_cast<LSY_QRS *>(_o);
        switch (_id) {
        case 0: _t->ContextMenuShow((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 1: _t->LayView(); break;
        case 2: _t->ObjMeanView(); break;
        case 3: _t->FeatureView(); break;
        case 4: _t->ClassResultView(); break;
        case 5: _t->ObjBorderView(); break;
        case 6: _t->MultiSegment(); break;
        case 7: _t->SelectObjLay(); break;
        case 8: _t->DelectObjLay(); break;
        case 9: _t->ClassSegment(); break;
        case 10: _t->Classification(); break;
        case 11: _t->DeleteClassification(); break;
        case 12: _t->EditClassification(); break;
        case 13: _t->EditClassifie(); break;
        case 14: _t->InsertClassifie((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 15: _t->CopyClassifie(); break;
        case 16: _t->DeletClassifie(); break;
        case 17: _t->OutputClassifieRule(); break;
        case 18: _t->InputClassifieRule(); break;
        case 19: _t->SelectXingZheng((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: _t->SelectXingZheng1((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: _t->SelectXingZheng2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->GetRasterImgArry(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LSY_QRS::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LSY_QRS::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LSY_QRS,
      qt_meta_data_LSY_QRS, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LSY_QRS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LSY_QRS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LSY_QRS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LSY_QRS))
        return static_cast<void*>(const_cast< LSY_QRS*>(this));
    if (!strcmp(_clname, "QgisPlugin"))
        return static_cast< QgisPlugin*>(const_cast< LSY_QRS*>(this));
    return QObject::qt_metacast(_clname);
}

int LSY_QRS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void LSY_QRS::ContextMenuShow(QTreeWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
