/*
 * SFINAE.h
 *
 *  Created on: Aug. 21, 2019
 *      Author: daniel
 */

#pragma once
#include <map>
#include <set>
#include <type_traits>
#include <vector>

namespace elladan {

template <typename T>
struct is_map
{
   template <typename U>
   static typename std::enable_if<(
         std::is_same<U, std::map< typename U::key_type, typename U::mapped_type, typename U::key_compare, typename U::allocator_type>
   >::value), char>::type
   test(typename U::value_type* x);

   template <typename U>
   static long test(U* x);

   static const bool value = sizeof(test<T>(nullptr)) == 1;
};

template <typename T>
struct is_set
{
   template <typename U>
   static typename std::enable_if<(
         std::is_same<U, std::set< typename U::key_type, typename U::key_compare, typename U::allocator_type>
   >::value), char>::type
   test(typename U::value_type* x);

   template <typename U>
   static long test(U* x);

   static const bool value = sizeof(test<T>(0)) == 1;
};

template <typename T>
struct is_vector
{
   template <typename U>
   static typename std::enable_if<(
         std::is_same<U, std::vector< typename U::value_type, typename U::allocator_type >
   >::value), char>::type
   test(typename U::value_type* x);

   template <typename U>
   static long test(U* x);

   static const bool value = sizeof(test<T>(0)) == 1;
};

}
