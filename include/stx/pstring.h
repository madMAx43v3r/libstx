/*
 * pstring.h
 *
 *  Created on: Jun 14, 2020
 *      Author: mad
 */

#ifndef INCLUDE_STX_PSTRING_H_
#define INCLUDE_STX_PSTRING_H_

#include <stx/cstring.h>

#include <atomic>


namespace stx {

class pstring {
public:
	pstring() = default;
	
	pstring(const pstring& other) {
		*this = other;
	}
	
	pstring(const cstring& other) {
		*this = other;
	}
	
	pstring(const std::string& other) {
		*this = other;
	}
	
	pstring(pstring&& other) {
		data = other.data;
		other.data = &zero;
	}
	
	~pstring() {
		release();
		data = 0;
	}
	
	pstring& operator=(const pstring& other) {
		assign(other.data);
		return *this;
	}
	
	pstring& operator=(const cstring& other) {
		create();
		data->string = other;
		return *this;
	}
	
	pstring& operator=(const std::string& other) {
		create();
		data->string = other;
		return *this;
	}
	
	bool operator==(const pstring& other) const {
		return data->string == other.data->string;
	}
	
	bool operator!=(const pstring& other) const {
		return data->string != other.data->string;
	}
	
	bool operator==(const cstring& other) const {
		return data->string == other;
	}
	
	bool operator!=(const cstring& other) const {
		return data->string != other;
	}
	
	bool operator==(const std::string& other) const {
		return ::strcmp(c_str(), other.c_str()) == 0;
	}
	
	bool operator!=(const std::string& other) const {
		return ::strcmp(c_str(), other.c_str()) != 0;
	}
	
	bool operator<(const pstring& other) const {
		return data->string < other.data->string;
	}
	
	bool operator>(const pstring& other) const {
		return data->string > other.data->string;
	}
	
	bool operator<(const cstring& other) const {
		return data->string < other;
	}
	
	bool operator>(const cstring& other) const {
		return data->string > other;
	}
	
	bool operator<(const std::string& other) const {
		return ::strcmp(c_str(), other.c_str()) < 0;
	}
	
	bool operator>(const std::string& other) const {
		return ::strcmp(c_str(), other.c_str()) > 0;
	}
	
	friend bool operator==(const cstring& A, const pstring& B) {
		return A == B.data->string;
	}
	
	friend bool operator!=(const cstring& A, const pstring& B) {
		return A != B.data->string;
	}
	
	friend bool operator<(const cstring& A, const pstring& B) {
		return A < B.data->string;
	}
	
	friend bool operator>(const cstring& A, const pstring& B) {
		return A > B.data->string;
	}
	
	friend bool operator==(const std::string& A, const pstring& B) {
		return ::strcmp(A.c_str(), B.c_str()) == 0;
	}
	
	friend bool operator!=(const std::string& A, const pstring& B) {
		return ::strcmp(A.c_str(), B.c_str()) != 0;
	}
	
	friend bool operator<(const std::string& A, const pstring& B) {
		return ::strcmp(A.c_str(), B.c_str()) < 0;
	}
	
	friend bool operator>(const std::string& A, const pstring& B) {
		return ::strcmp(A.c_str(), B.c_str()) > 0;
	}
	
	std::string str() const {
		return data->string.str();
	}
	
	const char* c_str() const {
		return data->string.c_str();
	}
	
	size_t size() const {
		return data->string.size();
	}
	
	void clear() {
		release();
	}
	
	size_t hash() const {
		return data->string.hash();
	}
	
private:
	struct data_t {
		std::atomic<size_t> ref_count {0};
		stx::cstring string;
	};
	
	void create() {
		assign(new data_t());
	}
	
	void assign(data_t* data_) {
		release();
		if(data_ != &zero) {
			data_->ref_count++;
		}
		data = data_;
	}
	
	void release() {
		if(data != &zero) {
			if(--(data->ref_count) == 0) {
				delete data;
			}
			data = &zero;
		}
	}
	
private:
	data_t* data = &zero;
	static data_t zero;
	
};

#if __cplusplus >= 201703L
inline pstring::data_t pstring::zero;
#endif


} // stx

#endif /* INCLUDE_STX_PSTRING_H_ */
