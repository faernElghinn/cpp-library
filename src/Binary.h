/*
 * Binary.h
 *
 *  Created on: Oct 31, 2017
 *      Author: daniel
 */

#ifndef SRC_BINARY_H_
#define SRC_BINARY_H_

#include <stddef.h>
#include <string>
#include <memory>
#include <vector>

namespace elladan {

class Binary
{
public:
    Binary() = default;
    Binary(const Binary&) = delete;
    Binary(Binary&&) = default;
    Binary& operator= (const Binary&) = delete;
    Binary& operator= (Binary&&) = default;

    Binary(size_t size);
    Binary(void* data, size_t size);
    Binary(const std::string& str);
    ~Binary() = default;

    Binary copy() const;

    int cmp(const Binary& rhs) const;
    bool operator ==(const Binary& rhs) const;
    bool operator !=(const Binary& rhs) const;
    bool operator  <(const Binary& rhs) const;
    bool operator <=(const Binary& rhs) const;
    bool operator  >(const Binary& rhs) const;
    bool operator >=(const Binary& rhs) const;
    
    std::string toHex() const;
    inline size_t size() const { return data.size(); }

    std::vector<char> data;
};

}  // namespace elladan

namespace std {
std::string to_string(const elladan::Binary* binary);
}  // namespace std

#endif /* SRC_BINARY_H_ */
