/*! \file
 * \brief Helper class that interfaces with the moderator <-> chat room database.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef MODDATABASE_H
#define MODDATABASE_H

#include "minidbinterface.h"

class ModDatabase : public MiniDBInterface
{
public:
    explicit ModDatabase();
    virtual ~ModDatabase();
};

#endif // MODDATABASE_H
