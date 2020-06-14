/*
 * fstring.h
 *
 *  Created on: Jun 6, 2020
 *      Author: mad
 */

#ifndef LIBSTX_INCLUDE_STX_FSTRING_H_
#define LIBSTX_INCLUDE_STX_FSTRING_H_

#include <string>
#include <cstring>
#include <algorithm>


namespace stx {

template<size_t N>
class fstring {
public:
	fstring() = default;
	
	fstring(const fstring& other) = default;
	
	fstring(const std::string& other) {
		*this = other;
	}
	
	~fstring() {
		data[0] = 0;
	}
	
	fstring& operator=(const std::string& other) {
		const auto len = std::min(other.size(), N - 1);
		::memcpy(data, other.c_str(), len);
		data[len] = 0;
		return *this;
	}
	
	bool operator==(const fstring& other) const {
		return ::strcmp(data, other.data) == 0;
	}
	
	bool operator!=(const fstring& other) const {
		return ::strcmp(data, other.data) != 0;
	}
	
	bool operator==(const std::string& other) const {
		return ::strcmp(data, other.c_str()) == 0;
	}
	
	bool operator!=(const std::string& other) const {
		return ::strcmp(data, other.c_str()) != 0;
	}
	
	bool operator<(const fstring& other) const {
		return ::strcmp(data, other.data) < 0;
	}
	
	bool operator>(const fstring& other) const {
		return ::strcmp(data, other.data) > 0;
	}
	
	bool operator<(const std::string& other) const {
		return ::strcmp(data, other.c_str()) < 0;
	}
	
	bool operator>(const std::string& other) const {
		return ::strcmp(data, other.c_str()) > 0;
	}
	
	friend bool operator==(const std::string& A, const fstring& B) {
		return ::strcmp(A.c_str(), B.data) == 0;
	}
	
	friend bool operator!=(const std::string& A, const fstring& B) {
		return ::strcmp(A.c_str(), B.data) != 0;
	}
	
	friend bool operator<(const std::string& A, const fstring& B) {
		return ::strcmp(A.c_str(), B.data) < 0;
	}
	
	friend bool operator>(const std::string& A, const fstring& B) {
		return ::strcmp(A.c_str(), B.data) > 0;
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
		data[0] = 0;
	}
	
	size_t hash() const {
		size_t hash = 0;
		const auto* s = data;
		while(*s) {
			hash = hash * size_t(101) + size_t(*s++);
		}
		return hash;
	}
	
private:
	char data[N] = {};
	
};


} // stx

#endif /* LIBSTX_INCLUDE_STX_FSTRING_H_ */
