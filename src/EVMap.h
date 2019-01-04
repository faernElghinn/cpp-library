// /*
//  * VMap.h
//  *
//  *  Created on: Jul 20, 2018
//  *      Author: daniel
//  */

// #pragma once

// #include "VMap.h"

// #include <vector>

// namespace elladan {

// template <typename K, typename V>
// class SortedVmap : public VMap<K,V>
// {
// public:

//    SortedVmap() = default;
//    SortedVmap(const SortedVmap&) = default;
//    SortedVmap(SortedVmap&&) = default;
//    SortedVmap(const VMap& oth) {
//       _vector = oth;
//       sort();
//    }
//    SortedVmap(VMap&& oth) {
//       std::move(oth._vector);
//       sort();
//    };
//    SortedVmap(std::initializer_list<std::pair<K,V>> l) {
//       for (auto& ite : l) 
//          _vector.push_back(ite);
//       sort();
//    }
//    ~SortedVmap() = default;

//    bool insert(const K& key, const V& ele) {
//       if (find(key) != _vector.end())
//          return false;

//       _vector.push_back(std::make_pair(key,ele));
//       return true;
//    }
//    bool emplace(const K& key, V&& ele) {
//       if (find(key) != _vector.end())
//          return false;

//       _vector.emplace_back(std::move(std::make_pair(key,std::move(ele))));
//       return true;
//    }

//    bool erase(iterator ite) {
//       if (ite == _vector.end())
//          return false;
//       _vector.erase(ite);
//       return true;
//    }

//    bool erase(K key) {
//       return erase(find(key));
//    }

//    V& operator[] (K key) {
//       auto ite = find(key);
//       if (ite == _vector.end()) {
//          _vector.emplace_back(std::make_pair(key,V()));
//          ite =  --_vector.end();
//       }
//       return ite->second;
//    }

//    const V& at(const K& key) const {
//       auto ite = find(key);
//       assert(ite != _vector.end());
//       return ite->second;
//    }

//    V& at(const K& key) {
//       auto ite = find(key);
//       assert(ite != _vector.end());
//       return ite->second;
//    }

//    V&& take(const K& key) {
//       auto ite = find(key);
//       assert(ite != _vector.end());
//       V retVal = std::move(ite->second);
//       erase(ite);
//       return retVal;
//    }

//    void clear() { _vector.clear(); }
//    int count (K key) const { return find(key) != _vector.end(); }
//    int size () const { return _vector.size(); }
//    int reserve (size_t size) const { return _vector.reserve(size); }
//    iterator begin() { return  _vector.begin(); }
//    iterator end() { return  _vector.end(); }
//    const_iterator begin() const { return  _vector.begin(); }
//    const_iterator end() const { return  _vector.end(); }
//    reverse_iterator rbegin() const { return  _vector.rbegin(); }
//    reverse_iterator rend() const { return  _vector.rend(); }

//    void sort() {
//       std::stable_sort(_vector.begin(), _vector.end(), [](const pair& lhs, const pair& rhs){ return lhs.first < rhs.first; });
//    }
//    void sort(std::function<bool(const pair& lhs, const pair& rhs)> sortFnc) {
//       std::stable_sort(_vector.begin(), _vector.end(), sortFnc);
//    }

// #define CMP(OP, eqVal)\
//    bool operator OP (const VMap<K,V>& rhs) const {\
//       int ret = size() - rhs.size();\
//       if (!ret) return ret OP 0;\
//       for (int i = 0; i < size(); i++) {\
//          if (!(_vector.at(i).first OP rhs._vector.at(i).first)) return false;\
//          if (!(_vector.at(i).second OP rhs._vector.at(i).second)) return false;\
//       }\
//       return eqVal;\
//    }

//    CMP(< , false)
//    CMP(<=, true)
//    CMP(>=, true)
//    CMP(> , false)
// #undef CMP

//    bool operator == (const SortedVmap<K,V>& rhs) const {
//       if ((size() - rhs.size()) != 0) return false;
//       for (int i = 0; i < size(); i++) {
//          if (_vector.at(i).first != rhs._vector.at(i).first) return false;
//          if (_vector.at(i).second != rhs._vector.at(i).second) return false;
//       }
//       return true;
//    }
//    bool operator != (const SortedVmap<K,V>& rhs) const {
//       if ((size() - rhs.size()) != 0) return true;
//       for (int i = 0; i < size(); i++) {
//          if (_vector.at(i).first != rhs._vector.at(i).first) return true;
//          if (_vector.at(i).second != rhs._vector.at(i).second) return true;
//       }
//       return false;
//    }

// protected:
//    std::vector<pair> _vector;
//    int cmp(const VMap<K,V>& rhs) const {
//       return size() - rhs.size();
//    }
// };

// }  // namespace elladan
