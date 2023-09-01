#include "String.h"

#include <xystring.h>

using namespace mule::Data::Basic;

size_t String::Size() const
{
	return size_t(-1);
}

std::u16string mule::Data::Basic::String::GetTypeName() const
{
	return u"string";
}

size_t mule::Data::Basic::String::GetLastSize() const
{
	return lastSize;
}

size_t mule::Data::Basic::String::EvalSize(const MultiValue &obj) const
{
	if (obj.type != MultiValue::MVT_STRING)
		return 0;

	return obj.value.stringValue->size() + 1;
}

MultiValue mule::Data::Basic::String::DoRead(xybase::Stream *stream)
{
	MultiValue tmp(xybase::string::to_utf16(stream->ReadString()));
	lastSize = tmp.value.stringValue->length();
	tmp.metadata[u"size"] = lastSize;
	return tmp;
}

void mule::Data::Basic::String::DoWrite(xybase::Stream *stream, const MultiValue &value)
{
	if (!value.IsType(MultiValue::MVT_STRING)) throw xybase::InvalidParameterException(u"value", u"Type mismatch!", 19004);

	auto data = xybase::string::to_string(*(value.value.stringValue));

	auto &&itr = value.metadata.find(u"size");
	if (itr != value.metadata.end())
	{
		if (data.size() > itr->second.value.unsignedValue) throw xybase::InvalidParameterException(u"value", u"Too large for this string space.", 19010);
	}

	stream->Write(data);
}
