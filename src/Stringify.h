/*
 * String.h
 *
 *  Created on: May 9, 2017
 *      Author: daniel
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>


// Convert many value to string. Very usefull for templates.
namespace std {
std::string to_string (const std::string val);
std::string to_string (bool val);
}  // namespace std

template <typename T>
T fromString (const std::string& val);

template<> std::string fromString<std::string > (const std::string& str);
template<> int8_t      fromString<int8_t      > (const std::string& str);
template<> uint8_t     fromString<uint8_t     > (const std::string& str);
template<> int16_t     fromString<int16_t     > (const std::string& str);
template<> uint16_t    fromString<uint16_t    > (const std::string& str);
template<> int32_t     fromString<int32_t     > (const std::string& str);
template<> int64_t     fromString<int64_t     > (const std::string& str);
template<> uint32_t    fromString<uint32_t    > (const std::string& str);
template<> uint64_t    fromString<uint64_t    > (const std::string& str);
template<> float       fromString<float       > (const std::string& str);
template<> double      fromString<double      > (const std::string& str);
template<> bool        fromString<bool        > (const std::string& str);

namespace elladan {

int isBool(const std::string& str);
int isInt(const std::string& str);
int isDouble(const std::string& str);

// Try to parse the value. return true if it succeeded.
int parseString(const std::string& str, int8_t& val);
int parseString(const std::string& str, uint8_t& val);
int parseString(const std::string& str, int16_t& val);
int parseString(const std::string& str, uint16_t& val);
int parseString(const std::string& str, int32_t& val);
int parseString(const std::string& str, uint32_t& val);
int parseString(const std::string& str, int64_t& val);
int parseString(const std::string& str, uint64_t& val);
int parseString(const std::string& str, float& val);
int parseString(const std::string& str, double& val);
int parseString(const std::string& str, bool& val);
int parseString(const std::string& str, std::string& val);

// Trim whitespace from both ends
std::string& trim(std::string& s);

// Split the string at the sep.
std::vector<std::string> tokenize(const std::string& txt, std::string sep);

// Check if the passed str start with the pattern. Case sensitive.
bool startWith(const std::string& str, const std::string& pattern, bool ignoreCase = false);

std::string& toUpper(std::string& str);
std::string& toLower(std::string& str);

std::string toUpper(const std::string& str);
std::string toLower(const std::string& str);

uint8_t charToHex(char c, uint8_t max = 16);
std::string  hexToChar(uint8_t c);

} // namespace elladan
