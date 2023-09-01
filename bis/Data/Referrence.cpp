#include "Referrence.h"

using namespace mule::Data::Basic;

void mule::Data::Referrence::Read(xybase::Stream *stream, DataHandler *dataHandler)
{
	int ptr = stream->ReadInt32();

	if (ptr == 0)
	{
		dataHandler->OnDataRead(MultiValue::MV_NULL);
		return;
	}

	size_t loc = stream->Tell();
	stream->Seek(ptr, 0);
	referent->Read(stream, dataHandler);
	stream->Seek(loc, 0);
}

void mule::Data::Referrence::Write(xybase::Stream *stream, DataHandler *dataHandler)
{
	int ptr = stream->ReadInt32();

	if (ptr == 0)
	{
		return;
	}

	size_t loc = stream->Tell();
	stream->Seek(ptr, 0);
	referent->Write(stream, dataHandler);
	stream->Seek(loc, 0);
}

size_t mule::Data::Referrence::Size() const
{
	return size_t(sizeof(int32_t));
}

std::u16string mule::Data::Referrence::GetTypeName() const
{
	return referent->GetTypeName() + u'*';
}

bool mule::Data::Referrence::IsComposite() const
{
	return referent->IsComposite();
}

mule::Data::Referrence::Referrence(Type *referent)
{
	this->referent = referent;
}

Type *mule::Data::Referrence::ReferrenceCreator::DoCreateObject(std::u16string info)
{
	if (!info.ends_with(u"*"))
	{
		return nullptr;
	}

	Basic::Type *innerType = TypeManager::GetInstance().GetOrCreateType(info.substr(0, info.size() - 1));
	if (innerType == nullptr) return nullptr;

	Referrence *referrer = new Referrence(innerType);
	return referrer;
}
