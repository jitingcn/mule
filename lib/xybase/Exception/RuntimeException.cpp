#include "RuntimeException.h"
#include <cstring>
#include "../xyutils.h"

xybase::RuntimeException::RuntimeException(const std::wstring &message, int err)
	: message(message), err(RUNTIME_EXCEPTION_LEAD | err)
{
	auto ret = xybase::string::to_utf8(message);
	buf = new char[ret.size()];
	memcpy(buf, ret.c_str(), ret.size());
}

xybase::RuntimeException::~RuntimeException()
{
	delete[] buf;
}

const char *xybase::RuntimeException::what() const noexcept
{
	return buf;
}

const std::wstring &xybase::RuntimeException::GetMessage() const
{
	return message;
}

int xybase::RuntimeException::GetErrorCode() const
{
	return err;
}
