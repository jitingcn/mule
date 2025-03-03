#include "XmlNode.h"

using namespace mule::Xml;

const XmlNode XmlNode::ERROR = XmlNode();

bool mule::Xml::XmlNode::IsTextNode() const
{
	return text.size();
}

void mule::Xml::XmlNode::AddChild(XmlNode node)
{
	children.push_back(node);
}

std::list<XmlNode> mule::Xml::XmlNode::GetChildren() const
{
	return children;
}

void mule::Xml::XmlNode::AddText(std::u16string str)
{
	XmlNode tmp;
	tmp.text = str;
	AddChild(tmp);
}

std::u16string mule::Xml::XmlNode::GetText() const
{
	return text;
}

void mule::Xml::XmlNode::SetName(std::u16string name)
{
	this->name = name;
}

std::u16string mule::Xml::XmlNode::GetName() const
{
	return name;
}

void mule::Xml::XmlNode::AddAttribute(std::u16string name, std::u16string data)
{
	attributes[name] = data;
}

std::map<std::u16string, std::u16string> mule::Xml::XmlNode::GetAttributes() const
{
	return attributes;
}

std::u16string mule::Xml::XmlNode::GetAttribute(std::u16string name) const
{
	auto &&itr = attributes.find(name);
	if (itr == attributes.end()) return u"";
	else return itr->second;
}

bool mule::Xml::XmlNode::operator==(const XmlNode &rvalue) const
{
	return name == rvalue.name && attributes == rvalue.attributes;
}

XmlNode &mule::Xml::XmlNode::operator[](std::u16string name)
{
	for (auto &&child : children)
	{
		if (child.name == name)
		{
			return child;
		}
	}
	
	XmlNode tmp;
	tmp.name = name;
	children.push_back(tmp);
	auto &&itr = children.end();
	--itr;
	return *itr;
}
