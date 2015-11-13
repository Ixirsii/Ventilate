/*! \file
 * \brief Define export and import macro for public classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright BSD 3 Clause
 */

#ifndef LIBVENTILATE_GLOBAL_H
#define LIBVENTILATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBVENTILATE_LIBRARY)
#  define LIBVENTILATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBVENTILATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBVENTILATE_GLOBAL_H
