/*
 * cstring.h
 *
 *  Created on: Jun 6, 2020
 *      Author: mad
 */

#ifndef LIBSTX_INCLUDE_STX_CSTRING_H_
#define LIBSTX_INCLUDE_STX_CSTRING_H_

#include <string>
#include <cstring>


namespace stx {

class cstring {
public:
	cstring() = default;
	
	cstring(const cstring& other) {
		*this = other;
	}
	
	cstring(const std::string& other) {
		*this = other;
	}
	
	cstring(cstring&& other) {
		data = other.data;
		other.data = &zero;
	}
	
	~cstring() {
		if(data != &zero) {
			delete [] data;
		}
		data = 0;
	}
	
	cstring& operator=(const cstring& other) {
		const auto len = other.size();
		resize(len);
		::memcpy(data, other.data, len);
		return *this;
	}
	
	cstring& operator=(const std::string& other) {
		resize(other.size());
		::memcpy(data, other.c_str(), other.size());
		return *this;
	}
	
	bool operator==(const cstring& other) const {
		return ::strcmp(data, other.data) == 0;
	}
	
	bool operator!=(const cstring& other) const {
		return ::strcmp(data, other.data) != 0;
	}
	
	bool operator==(const std::string& other) const {
		return ::strcmp(data, other.c_str()) == 0;
	}
	
	bool operator!=(const std::string& other) const {
		return ::strcmp(data, other.c_str()) != 0;
	}
	
	bool operator<(const cstring& other) const {
		return ::strcmp(data, other.data) < 0;
	}
	
	bool operator>(const cstring& other) const {
		return ::strcmp(data, other.data) > 0;
	}
	
	std::string str() const {
		return std::string(data, size());
	}
	
	const char* c_str() const {
		return data;
	}
	
	size_t size() const {
		return ::strlen(data);
	}
	
	void clear() {
		if(data != &zero) {
			delete [] data;
			data = &zero;
		}
	}
	
	size_t hash() const {
		size_t hash = 0;
		const auto* s = data;
		while(*s) {
			hash = hash * size_t(101) + size_t(*s++);
		}
		return hash;
	}
	
protected:
	void resize(size_t new_size) {
		if(data != &zero) {
			delete [] data;
		}
		if(new_size) {
			data = new char[new_size + 1];
		} else {
			data = &zero;
		}
		data[new_size] = 0;
	}
	
private:
	static char zero;
	char* data = &zero;
	
};

#if __cplusplus >= 201703L
inline char cstring::zero = 0;
#endif


} // stx

namespace std {
	template<> struct hash<stx::cstring> {
		size_t operator()(const stx::cstring& x) const {
			return x.hash();
		}
	};
} // std

#endif /* LIBSTX_INCLUDE_STX_CSTRING_H_ */
