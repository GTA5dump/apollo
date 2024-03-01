#include "XMLWrapper.h"
#include <iostream>
#include "stdafx.h"

void XML::open(const std::string& file)
{
	nodes.clear();
	doc.load_file(file.c_str());
}

void XML::openNode(const char* node)
{
	if (nodes.size() == 0)
	{
		pugi::xml_node tmp = doc.child(node);
		nodes.push_back(tmp);
	}
	else
	{
		pugi::xml_node tmp = nodes[nodes.size() - 1].child(node);
		tmp = tmp.next_sibling(node);
		nodes.push_back(nodes[nodes.size() - 1].child(node));
	}
}

void XML::closeNode()
{
	nodes.erase(nodes.begin() + nodes.size() - 1);
}

int XML::getInt(const char* label)
{
	std::string result;
	if (nodes.size() == 0)
		result = doc.child_value(label);
	else
		result = nodes[nodes.size() - 1].child_value(label);
	try {
		stoi(result);
	}
	catch (...) {
		Log::Msg(std::string(result + "    " + std::string(label)).c_str());
	}

	return stoi(result);
}

float XML::getFloat(const char* label)
{
	std::string result;
	if (nodes.size() == 0)
		result = doc.child_value(label);
	else
		result = nodes[nodes.size() - 1].child_value(label);
	return stof(result);
}

bool XML::getBool(const char* label)
{
	std::string result;
	if (nodes.size() == 0)
		result = doc.child_value(label);
	else
		result = nodes[nodes.size() - 1].child_value(label);
	return stoi(result) == 1;
}

char* XML::getChar(const char* label)
{
	std::string result;
	if (nodes.size() == 0)
		result = doc.child_value(label);
	else
		result = nodes[nodes.size() - 1].child_value(label);
	return _strdup(result.c_str());
}

std::string XML::getString(const char* label)
{
	if (nodes.size() == 0)
		return doc.child_value(label);
	else
		return nodes[nodes.size() - 1].child_value(label);
}

void XML::openInlineValue(const char* label)
{
	if (nodes.size() == 0)
		attribute = doc.child(label);
	else
		attribute = nodes[nodes.size() - 1].child(label);
}

int XML::getInlineInt(const char* label)
{
	return attribute.attribute(label).as_int();
}

float XML::getInlineFloat(const char* label)
{
	return attribute.attribute(label).as_float();
}

char* XML::getInlineChar(const char* label)
{
	std::string tmp = attribute.attribute(label).as_string();
	return _strdup(tmp.c_str());
}

std::string XML::getInlineString(const char* label)
{
	return attribute.attribute(label).as_string();
}

bool XML::getInlineBool(const char* label)
{
	return attribute.attribute(label).as_bool();
}

int XML::getCurrentNodeId()
{
	return nodes.size() - 1;
}

pugi::xml_node XML::getCurrentNode()
{
	return nodes[nodes.size() - 1];
}

void XML::addNodeToStack(pugi::xml_node node)
{
	nodes.push_back(node);
}

std::vector <pugi::xml_node> XML::nodes;
pugi::xml_document XML::doc;
pugi::xml_node XML::attribute;