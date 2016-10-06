#ifndef NTL_DEBUG_GLOBAL_H
#define NTL_DEBUG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NTL_DEBUG_LIBRARY)
#  define NTL_DEBUGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NTL_DEBUGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NTL_DEBUG_GLOBAL_H
