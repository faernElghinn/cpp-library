/*
 * Set.h
 *
 *  Created on: May 26, 2017
 *      Author: daniel
 */


#pragma once


/*
 * Deprecated, replaced by
 * - std::set_symetric_difference, // Element is in the resulting set if exactly one of the source set.
 * - std::set_difference  // Element is keep if not in the second set.
 * - std::set_intersection, // Element is keep if in bith set.
 * - std::set_union // Element is keep if in any set.
 * See the standard for the nuts and bolts!
 *
 * Template are added for convenience.
 */

#include <cassert>
#include <algorithm>

#include "SFINAE.h"

namespace elladan {



template<typename T>
inline void moveIfDiff(T& target, T& source) {
   if (target != source) *target = std::move(*source);
   ++target;
   ++source;
}


template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
T set_intersect(const T& set1, const T& set2) {
   assert(std::is_sorted(set1.begin(), set1.end()));
   assert(std::is_sorted(set2.begin(), set2.end()));

   T set3;
   std::set_intersection(set1.begin(), set1.end(),
                         set2.begin(), set2.end(),
                         std::back_inserter(set3));
   return set3;
}
template <typename T, std::enable_if_t<is_set<T>::value>* = nullptr>
T set_intersect(const T& set1, const T& set2) {
   T set3;

   auto read1 = set1.begin();
   auto read2 = set2.begin();

   while (read1 != set1.end()) {
      if (read2 == set2.end())
         break;

      if (*read1 < *read2)
         ++read1;
      else if (*read2 < *read1)
         ++read2;
      else {
         ++read2;
         set3.insert(*read1++);
      }
   }

   return set3;
}

template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
T set_remove(const T& list, const T& toRemove) {
   assert(std::is_sorted(list.begin(), list.end()));
   assert(std::is_sorted(toRemove.begin(), toRemove.end()));

   T set3;
   std::set_difference(list.begin(), list.end(),
                       toRemove.begin(), toRemove.end(),
                       std::back_inserter(set3));
   return set3;
}
template <typename T, std::enable_if_t<is_set<T>::value> = 0>
T set_remove(const T& list, const T& toRemove) {
   T set3;
   auto read1 = list.begin();
   auto read2 = toRemove.begin();

   while (read1 != list.end()) {
      if (read2 == toRemove.end())
         return;

      if (*read1 < *read2)
         set3.insert(*read1++);
      else if (*read2 < *read1)
         ++read2;
      else {
         ++read2;
         ++read1;
      }
   }
   return set3;
}

template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
T set_difference_full(const T& set1, const T& set2) {
   assert(std::is_sorted(set1.begin(), set1.end()));
   assert(std::is_sorted(set2.begin(), set2.end()));

   T set3;
   std::set_symmetric_difference(set1.begin(), set1.end(),
                                 set2.begin(), set2.end(),
                                 std::back_inserter(set3));
   return set3;
}
template <typename T, std::enable_if_t<is_set<T>::value> = 0>
T set_difference_full(const T& set1, const T& set2) {
   T set3;
   auto read1 = set1.begin();
   auto read2 = set2.begin();

   while (read1 != set1.end()) {
      if (read2 == set2.end())
         return;

      if (*read1 < *read2)
         set3.insert(*read1++);
      else if (*read2 < *read1)
         set3.insert(*read2++);
      else {
         ++read2;
         ++read1;
      }
   }
   return set3;
}

template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
T set_union(const T& set1, const T& set2) {
   assert(std::is_sorted(set1.begin(), set1.end()));
   assert(std::is_sorted(set2.begin(), set2.end()));

   T set3;
   std::set_union(set1.begin(), set1.end(),
                  set2.begin(), set2.end(),
                  std::back_inserter(set3));
   return set3;
}
template <typename T, std::enable_if_t<is_set<T>::value> = 0>
T set_union(const T& set1, const T& set2) {
   T set3;
   auto read1 = set1.begin();
   auto read2 = set2.begin();

   while (read1 != set1.end()) {
      if (read2 == set2.end())
         return;

      if (*read1 < *read2)
         set3.insert(*read1++);
      else if (*read2 < *read1)
         set3.insert(*read2++);
      else {
         ++read2;
         set3.insert(*read1++);
      }
   }
   return set3;
}

template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
void set_intersect_in_place(T& set1, const T& set2) {
   assert(std::is_sorted(set1.begin(), set1.end()));
   assert(std::is_sorted(set2.begin(), set2.end()));
   assert(&set1 != &set2);

   auto writeLoc = set1.begin();
   auto read1 = set1.begin();
   auto read2 = set2.begin();

   while (read1 != set1.end()) {
      if (read2 == set2.end()) {
         set1.erase(read1, set1.end());
         break;
      }

      if (*read1 < *read2)
         ++read1;
      else if (*read2 < *read1)
         ++read2;
      else {
         ++read2;
         moveIfDiff(writeLoc, read1);
      }
   }
   set1.erase(writeLoc, set1.end());
}

template <typename T, std::enable_if_t<is_vector<T>::value>* = nullptr>
void set_remove_in_place(T& list, const T& toRemove) {
   assert(std::is_sorted(list.begin(), list.end()));
   assert(std::is_sorted(toRemove.begin(), toRemove.end()));
   assert(&list != &toRemove);

   auto writeLoc = list.begin();
   auto read1 = list.begin();
   auto read2 = toRemove.begin();

   while (read1 != list.end()) {
      if (read2 == toRemove.end())
         moveIfDiff(writeLoc, read1);
      else if (*read1 < *read2)
         moveIfDiff(writeLoc, read1);
      else if (*read2 < *read1)
         ++read2;
      else {
         ++read2;
         ++read1;
      }
   }
   list.erase(writeLoc, list.end());
}
template <typename T, std::enable_if_t<is_set<T>::value>* = nullptr>
void set_remove_in_place(T& list, const T& toRemove) {
   assert(&list != &toRemove);

   auto read1 = list.begin();
   auto read2 = toRemove.begin();

   while (read1 != list.end()) {
      if (read2 == toRemove.end())
         return;

      if (*read1 < *read2)
         ++read1;
      else if (*read2 < *read1)
         ++read2;
      else {
         ++read2;
         read1 = list.erase(read1);
      }
   }
}

} // namespace elladan
