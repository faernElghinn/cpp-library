/*
 * String.cpp
 *
 *  Created on: May 9, 2017
 *      Author: daniel
 */

#include "Stringify.h"

#include <stddef.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <functional>
#include <iterator>

#include "Exception.h"

namespace std {
std::string to_string(std::string val) { return val; }
std::string to_string(bool val) { return val ? "true" : "false"; }
}  // namespace std


template<> std::string fromString<std::string> (const std::string& str){ return str; }
template<> int8_t      fromString<int8_t     > (const std::string& str){ int8_t val;   if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to int8_t  "); return val; }
template<> uint8_t     fromString<uint8_t    > (const std::string& str){ uint8_t val;  if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to uint8_t "); return val; }
template<> int16_t     fromString<int16_t    > (const std::string& str){ int16_t val;  if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to int16_t "); return val; }
template<> uint16_t    fromString<uint16_t   > (const std::string& str){ uint16_t val; if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to uint16_t"); return val; }
template<> int32_t     fromString<int32_t    > (const std::string& str){ int32_t val;  if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to int32_t "); return val; }
template<> int64_t     fromString<int64_t    > (const std::string& str){ int64_t val;  if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to int64_t "); return val; }
template<> uint32_t    fromString<uint32_t   > (const std::string& str){ uint32_t val; if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to uint32_t"); return val; }
template<> uint64_t    fromString<uint64_t   > (const std::string& str){ uint64_t val; if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to uint64_t"); return val; }
template<> float       fromString<float      > (const std::string& str){ float val;    if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to float   "); return val; }
template<> double      fromString<double     > (const std::string& str){ double val;   if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to double  "); return val; }
template<> bool        fromString<bool       > (const std::string& str){ bool val;     if(!elladan::parseString(str, val)   ) throw elladan::Exception("Could not parsestrint to bool    "); return val; }

namespace elladan {

int isBool(const std::string& str) {
   bool bidon;
   return parseString(str, bidon);
}
int isInt(const std::string& str) {
   size_t pos;
   std::stoi(str, &pos, 0);
   return pos;
}
int isDouble(const std::string& str) {
   size_t pos;
   std::stod(str, &pos);
   return pos;
}

// Try to parse the value. Return the number of consumed byte.
int getVal(char c, int base){
   c = tolower(c);
   int val;
   if ((c >= '0') & (c <= '9'))
      val = c - '0';
   else
      val = c - 'a' + 10;
   if (val >= base) return -1;
   return val;
}
int parseStringeg(std::string::iterator& ite, std::string::iterator end, uint64_t& val, int *obase = nullptr)  {
   size_t pos;
   uint64_t acc = 0;
   std::string::iterator start = ite;
   int base = 10;
   bool valid = false;

   if (ite != end && *ite == '0') {
      ++ite;
      valid = true;
      base = 8;
      if (ite != end) {
         if (*ite == 'x') {
            base=16;
            ++ite;
         }
      }
   }

   for (; ite != end; ite++) {
      int loc = getVal(*ite, base);
      if (loc < 0) break;
      acc = acc * base + loc;
      valid = true;
   }

   if (valid) {
      val = acc;
      if (acc == 0) base = 10;
      if (obase) *obase = base;
      return std::distance(start, ite);
   }
   return 0;
}
int parseFract(std::string::iterator& ite, std::string::iterator end, int base, double& val)  {
   size_t pos;
   std::string::iterator start = ite;
   double fraction = 1./(double)base;

   val = 0;
   for (; ite != end; ite++){
      int loc = getVal(*ite, base);
      if (loc < 0) break;
      val += (double)loc * fraction;
      fraction /= base;
   }

   return std::distance(start, ite);
}

template <typename T, bool sign>
int parseStringImpl(std::string str, T& val){
   trim(str);

   bool neg = false;
   std::string::iterator ite = str.begin();

   if (sign && *ite == '-') {
      ++ite;
      neg = true;
   }

   uint64_t acc;
   int pos = parseStringeg(ite, str.end(), acc);

   if (ite != str.end())
      return 0;

   if (sign) {
      int64_t t = acc;
      val = (neg ? -((T)t) : t);
   }
   else
      val = acc;

   return std::distance(str.begin(), ite);
}

#define DecParseString(Format) \
      int parseString(const std::string& str, Format& val) {return parseStringImpl<Format, true>(str, val); } \
      int parseString(const std::string& str, u##Format& val) {return parseStringImpl<u##Format, false>(str, val); } \

DecParseString(int8_t)
DecParseString(int16_t)
DecParseString(int32_t)
DecParseString(int64_t)

#undef DecParseString

template <typename T>
int parseStringImpl(std::string str, T& val){
   trim(str);
   int base;
   uint64_t integ = 0, expo = 0;
   double fract = 0.;

   bool integNeg = false, expNeg = false;
   std::string::iterator ite = str.begin();
   if (*ite == '-') {
      ++ite;
      integNeg = true;
   }
   parseStringeg(ite, str.end(), integ, &base);
   if (ite != str.end() && (*ite == '.' || *ite == ',') )
      parseFract(++ite, str.end(), base, fract);
   if (ite != str.end() && tolower(*ite) == 'e'){
      if (*++ite == '-'){
         ++ite;
         expNeg = true;
      }
      parseStringeg(ite, str.end(), expo);
   }

   if (ite != str.end())
      return 0;

   val = integ;
   val += fract;
   if(integNeg) val = -val;
   double fact = expo;
   if (expNeg) fact = -fact;
   val *= exp10(fact);

   return std::distance(str.begin(), ite);
}
int parseString(const std::string& str, float& val) { return parseStringImpl(str, val);}
int parseString(const std::string& str, double& val){ return parseStringImpl(str, val);}


int parseString(const std::string& str, bool& val) {
   size_t pos = 0;
   std::string bo = toLower(str);

   // Eat up whitespace.
   while (pos < bo.size() && std::isspace(bo[pos]))
      pos++;

   if (pos > bo.size())
      return 0;

   if (bo[pos] == 't') {
      val = true;
      return (bo.substr(pos, 4) == "true") ? 4 : 1;
   }
   if (bo[pos] == '1') {
      val = true;
      return 1;
   }
   if (bo[pos] == 'f') {
      val = false;
      return (bo.substr(pos, 5) == "false") ? 5 : 1;
   }
   if (bo[pos] == '0') {
      val = false;
      return 1;
   }

   return 0;
}

int parseString(const std::string& str, std::string& val){ val = str; return str.size(); }

// Trim whitespace from both ends
std::string& trim(std::string& s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// Split the string at the sep.
std::vector<std::string> tokenize(const std::string& txt, std::string sep) {
   std::vector<std::string> token;

   size_t startPos = 0;
   size_t endPos = txt.find(sep, startPos);

   while (endPos != std::string::npos) {
      std::string part = txt.substr(startPos, endPos - startPos);
      token.push_back(part);

      startPos = endPos + 1;
      endPos = txt.find(sep, startPos);
   }

   if (startPos != txt.length()) {
      std::string part = txt.substr(startPos);
      token.push_back(part);
   } else {
      token.push_back("");
   }

   return token;
}

// Check if the passed str start with the pattern. Case sensitive.
bool startWith(const std::string& str, const std::string& pattern, bool ignoreCase){
   if (str.size() < pattern.size()) return false;

   if (ignoreCase) {
      std::string strl = toLower(str);
      std::string patternl = toLower(pattern);

      return !strl.compare(0, patternl.size(), patternl);
   }
   else {
      return !str.compare(0, pattern.size(), pattern);
   }
}

std::string& toUpper(std::string& s) {
   std::transform (s.begin (), s.end (), s.begin (), std::ptr_fun<int, int> (toupper));
   return s;
}

std::string& toLower(std::string& s) {
   std::transform (s.begin (), s.end (), s.begin (), std::ptr_fun<int, int> (tolower));
   return s;
}

std::string toUpper(const std::string& str) {
   std::string s = str;
   std::transform (s.begin (), s.end (), s.begin (), std::ptr_fun<int, int> (toupper));
   return s;
}
std::string toLower(const std::string& str) {
   std::string s = str;
   std::transform (s.begin (), s.end (), s.begin (), std::ptr_fun<int, int> (tolower));
   return s;
}

uint8_t charToHex(char c, uint8_t max){
   if (max <= 36) c = std::toupper(c);
   if (c >= '0' && c <= '9') return std::min((uint8_t)(c - '0'), max);
   if (c >= 'A' && c <= 'Z') return std::min((uint8_t)(c - 'A'  + 10), max);
   if (c >= 'a' && c <= 'z') return std::min((uint8_t)(c - 'a'  + 36), max);
   return 0;
}

std::string hexToChar(uint8_t c){
   std::string retVal;
   retVal.push_back((c>>4) > 9 ? ((c>>4) -10 + 'A') : (c>>4) + '0');
   retVal.push_back((c&15) > 9 ? ((c&15) -10 + 'A') : (c&15) + '0');
   return retVal;
}


} /* namespace elladan */
