/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#include "userdatabase.h"

UserDatabase::UserDatabase()
    : MiniDBInterface(USER_TABLE)
{
}

UserDatabase::~UserDatabase()
{
}
