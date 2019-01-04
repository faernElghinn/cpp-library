/*
 * VMap.h
 *
 *  Created on: Jul 20, 2018
 *      Author: daniel
 */

#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

namespace elladan {

template <typename K, typename V>
class VMap
{
public:
   typedef K key_type;
   typedef V value_type;

   typedef typename std::pair<K,V> pair;
   typedef typename std::vector<pair>::iterator iterator;
   typedef typename std::vector<pair>::const_iterator const_iterator;
   typedef typename std::vector<pair>::reverse_iterator reverse_iterator;

   VMap() = default;
   VMap(const VMap&) = default;
   VMap(VMap&&) = default;
   VMap(std::initializer_list<std::pair<K,V>> l) {
      for (auto& ite : l) 
         _vector.push_back(ite);
   }
   ~VMap() = default;

   iterator find(K key) {
      for (auto ite = _vector.begin(); ite != _vector.end(); ++ite)
         if (ite->first == key)
            return ite;
      return _vector.end();
   }

   const_iterator find(K key) const {
      for (auto ite = _vector.begin(); ite != _vector.end(); ++ite)
         if (ite->first == key)
            return ite;
      return _vector.end();
   }

   bool insert(const K& key, const V& ele) {
      if (find(key) != _vector.end())
         return false;

      _vector.push_back(std::make_pair(key,ele));
      return true;
   }
   bool emplace(const K& key, V&& ele) {
      if (find(key) != _vector.end())
         return false;

      _vector.emplace_back(std::move(std::make_pair(key,std::move(ele))));
      return true;
   }

   bool erase(iterator ite) {
      if (ite == _vector.end())
         return false;
      _vector.erase(ite);
      return true;
   }

   bool erase(K key) {
      return erase(find(key));
   }

   V& operator[] (K key) {
      auto ite = find(key);
      if (ite == _vector.end()) {
         _vector.emplace_back(std::make_pair(key,V()));
         ite =  --_vector.end();
      }
      return ite->second;
   }

   const V& at(const K& key) const {
      auto ite = find(key);
      assert(ite != _vector.end());
      return ite->second;
   }

   V& at(const K& key) {
      auto ite = find(key);
      assert(ite != _vector.end());
      return ite->second;
   }

   V&& take(const K& key) {
      auto ite = find(key);
      assert(ite != _vector.end());
      V retVal = std::move(ite->second);
      erase(ite);
      return retVal;
   }

   void clear() { _vector.clear(); }
   int count (K key) const { return find(key) != _vector.end(); }
   int size () const { return _vector.size(); }
   int reserve (size_t size) const { return _vector.reserve(size); }
   iterator begin() { return  _vector.begin(); }
   iterator end() { return  _vector.end(); }
   const_iterator begin() const { return  _vector.begin(); }
   const_iterator end() const { return  _vector.end(); }
   reverse_iterator rbegin() const { return  _vector.rbegin(); }
   reverse_iterator rend() const { return  _vector.rend(); }

   void sort() {
      std::stable_sort(_vector.begin(), _vector.end(), [](const pair& lhs, const pair& rhs){ return lhs.first < rhs.first; });
   }
   void sort(std::function<bool(const pair& lhs, const pair& rhs)> sortFnc) {
      std::stable_sort(_vector.begin(), _vector.end(), sortFnc);
   }

#define CMP(OP, eqRes)\
   bool operator OP (const VMap<K,V>& rhs) const {\
      const size_t siz = size();\
      if (siz != rhs.size()) return siz OP rhs.size();\
      for (int i = 0; i < siz; i++) {\
         if (_vector.at(i).first != rhs._vector.at(i).first) return _vector.at(i).first OP rhs._vector.at(i).first;\
         if (_vector.at(i).second != rhs._vector.at(i).second) return _vector.at(i).second OP rhs._vector.at(i).second;\
      }\
      return eqRes;\
   }

   CMP(< , false)
   CMP(<=, true)
   CMP(>=, true)
   CMP(> , false)
#undef CMP

   bool operator == (const VMap<K,V>& rhs) const {
      if ((size() - rhs.size()) != 0) return false;
      for (int i = 0; i < size(); i++) {
         if (_vector.at(i).first != rhs._vector.at(i).first) return false;
         if (_vector.at(i).second != rhs._vector.at(i).second) return false;
      }
      return true;
   }
   bool operator != (const VMap<K,V>& rhs) const {
      if ((size() - rhs.size()) != 0) return true;
      for (int i = 0; i < size(); i++) {
         if (_vector.at(i).first != rhs._vector.at(i).first) return true;
         if (_vector.at(i).second != rhs._vector.at(i).second) return true;
      }
      return false;
   }

protected:
   std::vector<pair> _vector;
   int cmp(const VMap<K,V>& rhs) const {
      return size() - rhs.size();
   }
};

}  // namespace elladan
