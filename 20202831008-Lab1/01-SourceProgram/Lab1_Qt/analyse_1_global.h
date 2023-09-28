#ifndef ANALYSE_1_GLOBAL_H
#define ANALYSE_1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ANALYSE_1_LIBRARY)
#  define ANALYSE_1_EXPORT Q_DECL_EXPORT
#else
#  define ANALYSE_1_EXPORT Q_DECL_IMPORT
#endif

#endif // ANALYSE_1_GLOBAL_H
