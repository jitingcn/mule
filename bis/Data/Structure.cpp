#include "Structure.h"

using namespace mule::Data;
using namespace mule::Data::Basic;

Structure::Structure(std::u16string name) : name(name)
{
}

mule::Data::Structure::~Structure()
{
	for (Field *field : fields)
	{
		delete field;
	}
}

void Structure::AppendField(const std::u16string &name, Type * field)
{
	fields.push_back(new Field(name, field));
}

void Structure::Read(xybase::Stream *stream, DataHandler *dataHandler)
{
	for (Field *field : fields)
	{
		field->Read(stream, dataHandler);
	}
}

void Structure::Write(xybase::Stream *stream, DataHandler *dataHandler)
{
	for (Field *field : fields)
	{
		field->Write(stream, dataHandler);
	}
}

size_t Structure::Size() const
{
	size_t size = 0;
	for (Type *obj : fields)
	{
		size += obj->Size();
	}
	return size;
}

std::u16string mule::Data::Structure::GetName() const
{
	return name;
}

std::u16string mule::Data::Structure::GetDataType() const
{
	return name;
}

bool mule::Data::Structure::IsComposite() const
{
	return true;
}

void mule::Data::Structure::Field::Read(xybase::Stream *stream, DataHandler *dataHandler)
{
	dataHandler->OnRealmEnter(object, name);
	object->Read(stream, dataHandler);
	dataHandler->OnRealmExit(object, name);
}

void mule::Data::Structure::Field::Write(xybase::Stream *stream, DataHandler *dataHandler)
{
	dataHandler->OnRealmEnter(object, name);
	object->Write(stream, dataHandler);
	dataHandler->OnRealmExit(object, name);
}

size_t mule::Data::Structure::Field::Size() const
{
	return object->Size();
}

const std::u16string &mule::Data::Structure::Field::GetName() const
{
	return name;
}

const Type *const mule::Data::Structure::Field::GetObject() const
{
	return object;
}

mule::Data::Structure::Field::Field(std::u16string name, Type *obj)
	: name(name), object(obj)
{
}

std::u16string mule::Data::Structure::Field::GetDataType() const
{
	return u"field[" + object->GetDataType() + u',' + name + u']';
}
