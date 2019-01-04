/*
 * Exception.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: daniel
 */

#include "../src/Exception.h"

namespace elladan{

Exception::Exception(const std::string& err)
    : std::exception(), _err(err)
{
}

const char* Exception::what() const noexcept
{
    return _err.c_str();
}

} // namespace elladan
