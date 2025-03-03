#pragma once

#ifndef XY_RUNTIME_EXCEPTION_H__
#define XY_RUNTIME_EXCEPTION_H__

#include <exception>
#include <string>

namespace xybase
{
	const int RUNTIME_EXCEPTION_LEAD = 0x0100'0000;

	class RuntimeException : public std::exception
	{
	public:
		RuntimeException(const std::wstring &message, int err);

		virtual ~RuntimeException();

		virtual const char *what() const noexcept override;

		virtual const std::wstring &GetMessage() const;

		virtual int GetErrorCode() const;

	protected:
		std::wstring message;
		int err;
		char *buf;
	};
}

#endif
