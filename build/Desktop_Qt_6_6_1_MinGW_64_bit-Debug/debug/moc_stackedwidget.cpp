/****************************************************************************
** Meta object code from reading C++ file 'stackedwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stackedwidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stackedwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSStackedWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSStackedWidgetENDCLASS = QtMocHelpers::stringData(
    "StackedWidget",
    "createFolderSignal",
    "",
    "createFileSignal",
    "pasteSignal",
    "propertiesSignal",
    "copySignal",
    "cutSignal",
    "deleteSignal"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSStackedWidgetENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[14];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[12];
    char stringdata5[17];
    char stringdata6[11];
    char stringdata7[10];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSStackedWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSStackedWidgetENDCLASS_t qt_meta_stringdata_CLASSStackedWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "StackedWidget"
        QT_MOC_LITERAL(14, 18),  // "createFolderSignal"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 16),  // "createFileSignal"
        QT_MOC_LITERAL(51, 11),  // "pasteSignal"
        QT_MOC_LITERAL(63, 16),  // "propertiesSignal"
        QT_MOC_LITERAL(80, 10),  // "copySignal"
        QT_MOC_LITERAL(91, 9),  // "cutSignal"
        QT_MOC_LITERAL(101, 12)   // "deleteSignal"
    },
    "StackedWidget",
    "createFolderSignal",
    "",
    "createFileSignal",
    "pasteSignal",
    "propertiesSignal",
    "copySignal",
    "cutSignal",
    "deleteSignal"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStackedWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    0,   58,    2, 0x06,    3 /* Public */,
       5,    0,   59,    2, 0x06,    4 /* Public */,
       6,    0,   60,    2, 0x06,    5 /* Public */,
       7,    0,   61,    2, 0x06,    6 /* Public */,
       8,    0,   62,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject StackedWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QStackedWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSStackedWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStackedWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStackedWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StackedWidget, std::true_type>,
        // method 'createFolderSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createFileSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pasteSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'propertiesSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'copySignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cutSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void StackedWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StackedWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createFolderSignal(); break;
        case 1: _t->createFileSignal(); break;
        case 2: _t->pasteSignal(); break;
        case 3: _t->propertiesSignal(); break;
        case 4: _t->copySignal(); break;
        case 5: _t->cutSignal(); break;
        case 6: _t->deleteSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::createFolderSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::createFileSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::pasteSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::propertiesSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::copySignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::cutSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StackedWidget::*)();
            if (_t _q_method = &StackedWidget::deleteSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *StackedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StackedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStackedWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QStackedWidget::qt_metacast(_clname);
}

int StackedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void StackedWidget::createFolderSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StackedWidget::createFileSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StackedWidget::pasteSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StackedWidget::propertiesSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void StackedWidget::copySignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void StackedWidget::cutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void StackedWidget::deleteSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
