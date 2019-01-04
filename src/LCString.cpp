#include "LCString.h"

#include "Stringify.h"


namespace elladan{

LCString& LCString::operator=(LCString&& rhs) {
   *this = LCString(std::move(rhs));
   return *this;
}

LCString& LCString::operator=(const LCString& rhs) {
   *this = LCString(rhs);
   return *this;
}

int LCString::compare (const LCString& rhs) const noexcept {
   return lowerCase.compare(rhs.lowerCase);
}


LCString::LCString (std::string&& str) 
: std::string(std::move(str))
, lowerCase(toLower((const std::string&)*this)) 
{}

LCString::LCString (const std::string& str) 
: std::string(str)
, lowerCase(toLower(str)) 
{}

LCString& LCString::operator=(std::string&& rhs) {
   *this = LCString(std::move(rhs));
   return *this;
}

LCString& LCString::operator=(const std::string& rhs) {
   *this = LCString(rhs);
   return *this;
}

int LCString::compare (const std::string& str) const noexcept {
   return lowerCase.compare(toLower(str));
}

LCString::LCString (const char* str) 
: std::string(str)
, lowerCase(toLower(str)) 
{}

LCString& LCString::operator=(const char* rhs) {
   *this = LCString(rhs);
   return *this;
}

int LCString::compare (const char* str) const noexcept {
   return lowerCase.compare(toLower(str));
}

} // namespace elladan