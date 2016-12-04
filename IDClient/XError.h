#pragma once
#include <sstream>
#include <ostream>
#include <string>
#include "ThickWrapper.h"
#include <iomanip>

class XError
{
public:
	using id_type = decltype(GetLastError());
	using file_type = char const *;
	using string_type = std::string;
private:
	id_type code_;
	int line_;
	file_type file_;
public:
	XError(int line, file_type file) :code_(GetLastError()), line_(line), file_(file) {}
	~XError();

	auto code() const -> id_type { return code_; }
	auto file() const -> file_type { return file_; }
	int line() const { return line_; }

	string_type msg();

	std::string ErrorDescription(DWORD str);

#define THROW_CONSOLE_ERROR() throw XError(__LINE__,__FILE__)
#define THROW_IF_CONSOLE_ERROR(res) if(!res) throw XError(__LINE__,__FILE__)
};

