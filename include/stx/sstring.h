/*
 * sstring.h
 *
 *  Created on: Jun 6, 2020
 *      Author: mad
 */

#ifndef LIBSTX_INCLUDE_STX_SSTRING_H_
#define LIBSTX_INCLUDE_STX_SSTRING_H_

#include <string>
#include <cstring>


namespace stx {

class sstring {
public:
	sstring() = default;
	
	sstring(const sstring& other) {
		*this = other;
	}
	
	sstring(const std::string& other) {
		*this = other;
	}
	
	sstring(sstring&& other) {
		if(other.data == other.small) {
			::memcpy(data, other.data, sizeof(small));
		} else {
			data = other.data;
		}
		other.data = other.small;
		other.small[0] = 0;
	}
	
	~sstring() {
		if(data != small) {
			delete [] data;
		}
		data = 0;
	}
	
	sstring& operator=(const sstring& other) {
		const auto len = other.size();
		resize(len);
		::memcpy(data, other.data, len);
		return *this;
	}
	
	sstring& operator=(const std::string& other) {
		resize(other.size());
		::memcpy(data, other.c_str(), other.size());
		return *this;
	}
	
	bool operator==(const sstring& other) const {
		return ::strcmp(data, other.data) == 0;
	}
	
	bool operator!=(const sstring& other) const {
		return ::strcmp(data, other.data) != 0;
	}
	
	bool operator==(const std::string& other) const {
		return ::strcmp(data, other.c_str()) == 0;
	}
	
	bool operator!=(const std::string& other) const {
		return ::strcmp(data, other.c_str()) != 0;
	}
	
	bool operator<(const sstring& other) const {
		return ::strcmp(data, other.data) < 0;
	}
	
	bool operator>(const sstring& other) const {
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
		if(data != small) {
			delete [] data;
			data = small;
		}
		small[0] = 0;
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
		if(data != small) {
			delete [] data;
		}
		if(new_size >= sizeof(small)) {
			data = new char[new_size + 1];
		} else {
			data = small;
		}
		data[new_size] = 0;
	}
	
private:
	char small[16] = {};
	char* data = small;
	
};


} // stx

namespace std {
	template<> struct hash<stx::sstring> {
		size_t operator()(const stx::sstring& x) const {
			return x.hash();
		}
	};
} // std

#endif /* LIBSTX_INCLUDE_STX_SSTRING_H_ */
