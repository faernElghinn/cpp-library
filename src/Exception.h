/*
 * Exception.h
 *
 *  Created on: Apr 17, 2017
 *      Author: daniel
 */

#pragma once

#include <exception>
#include <string>

namespace elladan {

class Exception: public std::exception
{
public:
    Exception(const std::string& err);

    virtual const char* what() const noexcept;

private:
    std::string _err;
};

}  // namespace elladan

