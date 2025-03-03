#include "CsvHandler.h"

#include <xystring.h>

using namespace mule::Data::Basic;

void mule::Csv::CsvHandler::OnSheetReadStart()
{
	if (status != CHS_IDLE)
		throw xybase::InvalidOperationException(L"This handler is not idle for read.", 10000);
	status = CHS_READ;
}

void mule::Csv::CsvHandler::OnSheetReadEnd()
{
	if (status != CHS_READ)
		throw xybase::InvalidOperationException(L"This handler is not reading.", 10000);
	status = CHS_IDLE;
}

void mule::Csv::CsvHandler::OnSheetWriteStart()
{
	if (status != CHS_IDLE)
		throw xybase::InvalidOperationException(L"This handler is not idle for write.", 10000);
	status = CHS_WRITE;
}

void mule::Csv::CsvHandler::OnSheetWriteEnd()
{
	if (status != CHS_WRITE)
		throw xybase::InvalidOperationException(L"This handler is not writing.", 10000);
	status = CHS_IDLE;
}

void mule::Csv::CsvHandler::OnRealmEnter(Type *realm, const std::u16string &name)
{
	if (realm->IsComposite())
	{
		++layer;
	}
}

void mule::Csv::CsvHandler::OnRealmExit(Type *realm, const std::u16string &name)
{
	if (realm->IsComposite())
	{
		--layer;
		if (layer == 1 || layer == 0)
		{
			if (status == CHS_READ || status == CHS_READ_TRAILCELL)
			{
				status = CHS_READ;
				stream->Write("\n");
			}
		}
	}
}

void mule::Csv::CsvHandler::OnRealmEnter(Type *realm, int idx)
{
	if (realm->IsComposite())
	{
		++layer;
	}
}

void mule::Csv::CsvHandler::OnRealmExit(Type *realm, int idx)
{
	if (realm->IsComposite())
	{
		--layer;
		if (layer == 1)
		{
			if (status == CHS_READ || status == CHS_READ_TRAILCELL)
			{
				status = CHS_READ;
				stream->Write("\n");
			}
		}
	}
}

void mule::Csv::CsvHandler::OnDataRead(const MultiValue &value)
{
	if (status == CHS_READ)
		status = CHS_READ_TRAILCELL;
	else if (status == CHS_READ_TRAILCELL)
	{
		stream->Write(",");
	}
	stream->Write(reinterpret_cast<const char *>(xybase::string::to_utf8(value.Stringfy()).c_str()));
}

MultiValue mule::Csv::CsvHandler::OnDataWrite()
{
	return MultiValue();
}

void mule::Csv::CsvHandler::SetStream(xybase::Stream *stream)
{
	this->stream = stream;
}
