#pragma once

#include "string"

namespace elladan{

class LCString : public std::string {
public:

#define FOR(Type)\
   int compare (const Type rhs) const noexcept;\
   inline bool operator< (const Type rhs) const noexcept { return compare(rhs) <  0; }\
   inline bool operator<=(const Type rhs) const noexcept { return compare(rhs) <= 0; }\
   inline bool operator==(const Type rhs) const noexcept { return compare(rhs) == 0; }\
   inline bool operator!=(const Type rhs) const noexcept { return compare(rhs) != 0; }\
   inline bool operator>=(const Type rhs) const noexcept { return compare(rhs) >= 0; }\
   inline bool operator> (const Type rhs) const noexcept { return compare(rhs) >  0; }

   LCString () = default;
   LCString (LCString&& str) = default;
   LCString (const LCString& str) = default;
   LCString& operator=(const LCString&);
   LCString& operator=(LCString&&);
   FOR(LCString&)

   LCString (std::string&& str);
   LCString (const std::string& str);
   LCString& operator=(const std::string&);
   LCString& operator=(std::string&&);
   FOR(std::string&)

   LCString (const char* str);
   LCString& operator=(const char* str);
   FOR(char *)

   inline const std::string& getLower() const { return lowerCase; }

protected:
   mutable std::string lowerCase;
};

} // namespace elladan