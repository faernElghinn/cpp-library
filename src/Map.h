/*
 * Set.h
 *
 *  Created on: May 26, 2017
 *      Author: daniel
 */

#pragma once

#include <map>
#include <functional>

namespace elladan {

template < typename K, typename T, typename KC, typename A>
void keep_intersect_key(std::map<K,T,KC,A>& edited, const std::map<K,T,KC,A>& must_include) {
   auto ite = edited.begin();
   auto ote = must_include.cbegin();

   KC cmp;
   while (ite != edited.end() && ote != must_include.cend()){
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;
            break;

         // Is the same. Keep it.
         case 0:
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Remove it.
         case 1:
            ite = edited.erase(ite);
            break;
      }
   }

   // Remove trailing unmatched values.
   while (ite != edited.end()) 
      ite = edited.erase(ite);
}

template < typename K, typename T, typename KC, typename A>
void keep_difference_key(std::map<K,T,KC,A>& edited, const std::map<K,T,KC,A>& must_not_include) {
   auto ite = edited.begin();
   auto ote = must_not_include.cbegin();
   KC cmp;

   while (ite != edited.end() && ote != must_not_include.cend()){
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      
      switch (rel) {
         // This value arrives before the next value... Keep it.
         case -1:
            ++ite;;
            break;

         // Is the same.. Remove it.
         case 0:
            ite = edited.erase(ite);
            ++ote;
            break;

         // This value arrives before the next value... Keep searching.
         case 1:
            ++ote;
            break;
      }
   }
}

template < typename K, typename T, typename KC, typename A>
std::map<K,T,KC,A> intersect_key(const std::map<K,T,KC,A>& base, const std::map<K,T,KC,A>& other) {
   std::map<K,T,KC,A> copy;
   auto ite = base.cbegin();
   auto ote = other.cbegin();
   KC cmp;
   while (ite != base.cend() && ote != other.cend()) {
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;;
            break;

         // Is the same.. Remove it.
         case 0:
            copy.insert(copy.end(), ite->first);
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Skip it.
         case 1:
            ++ite;
            break;
      }
   }
   return copy;
}

template < typename K, typename T, typename KC, typename A>
std::map<K,T,KC,A> difference_key(const std::map<K,T,KC,A>& base, const std::map<K,T,KC,A>& other) {
   std::map<K,T,KC,A> copy;
   auto ite = base.cbegin();
   auto ote = other.cbegin();
   KC cmp;
   while (ite != base.cend() && ote != other.cend()) {
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;;
            break;

         // Is the same... Skip it.
         case 0:
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Add it.
         case 1:
         copy.insert(copy.end(), ite->first);
            ++ite;
            break;
      }
   }
   return copy;
}

template < typename K, typename T, typename KC, typename A>
void keep_intersect_full(std::map<K,T,KC,A>& edited, const std::map<K,T,KC,A>& must_include, std::function<int(const T& lhs, const T& rhs)> value_cmp) {
   auto ite = edited.begin();
   auto ote = must_include.cbegin();

   KC cmp;
   while (ite != edited.end() && ote != must_include.cend()){
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      if (rel == 0) rel = value_cmp(ite->second, ote->second);
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;
            break;

         // Is the same. Keep it.
         case 0: 
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Remove it.
         case 1:
            ite = edited.erase(ite);
            break;
      }
   }

   // Remove trailing unmatched values.
   while (ite != edited.end()) 
      ite = edited.erase(ite);
}

template < typename K, typename T, typename KC, typename A>
void keep_difference_full(std::map<K,T,KC,A>& edited, const std::map<K,T,KC,A>& must_not_include, std::function<int(const T& lhs, const T& rhs)> value_cmp) {
   auto ite = edited.begin();
   auto ote = must_not_include.cbegin();
   KC cmp;

   while (ite != edited.end() && ote != must_not_include.cend()){
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      if (rel == 0) rel = value_cmp(ite->second, ote->second);

      switch (rel) {
         // This value arrives before the next value... Keep it.
         case -1:
            ++ite;;
            break;

         // Is the same.. Remove it.
         case 0:
            ite = edited.erase(ite);
            ++ote;
            break;

         // This value arrives before the next value... Keep searching.
         case 1:
            ++ote;
            break;
      }
   }
}

template < typename K, typename T, typename KC, typename A>
std::map<K,T,KC,A> intersect_full(const std::map<K,T,KC,A>& base, const std::map<K,T,KC,A>& other, std::function<int(const T& lhs, const T& rhs)> value_cmp) {
   std::map<K,T,KC,A> copy;
   auto ite = base.cbegin();
   auto ote = other.cbegin();
   KC cmp;
   while (ite != base.cend() && ote != other.cend()) {
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      if (rel == 0) rel = value_cmp(ite->second, ote->second);
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;;
            break;

         // Is the same.. Remove it.
         case 0:
            copy.insert(copy.end(), ite->first);
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Skip it.
         case 1:
            ++ite;
            break;
      }
   }
   return copy;
}

template < typename K, typename T, typename KC, typename A>
std::map<K,T,KC,A> difference_full(const std::map<K,T,KC,A>& base, const std::map<K,T,KC,A>& other, std::function<int(const T& lhs, const T& rhs)> value_cmp) {
   std::map<K,T,KC,A> copy;
   auto ite = base.cbegin();
   auto ote = other.cbegin();
   KC cmp;
   while (ite != base.cend() && ote != other.cend()) {
      int rel = ((int)cmp(ite->first, ote->first)) - ((int)cmp(ote->first, ite->first));
      if (rel == 0) rel = value_cmp(ite->second, ote->second);
      
      switch (rel) {
         // This arrive after the next value... Keep searching.
         case -1:
            ++ote;;
            break;

         // Is the same... Skip it.
         case 0:
            ++ite;
            ++ote;
            break;

         // This value arrives before the next value... Add it.
         case 1:
         copy.insert(copy.end(), ite->first);
            ++ite;
            break;
      }
   }
   return copy;
}

} // namespace elladan
