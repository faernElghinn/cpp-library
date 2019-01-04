/*
 * Random.h
 *
 *  Created on: Aug 31, 2016
 *      Author: daniel
 */

#pragma once

#include <string>

#include <random>

namespace elladan {

class Random
{
public:
  static unsigned int get(int max);
  static ::std::string generateString(int length = 32);
private:
  static ::std::random_device _src;
};


} // namespace elladan

