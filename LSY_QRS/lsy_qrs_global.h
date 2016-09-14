#ifndef LSY_QRS_GLOBAL_H
#define LSY_QRS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LSY_QRS_LIB
# define LSY_QRS_EXPORT Q_DECL_EXPORT
#else
# define LSY_QRS_EXPORT Q_DECL_IMPORT
#endif

#endif // LSY_QRS_GLOBAL_H
