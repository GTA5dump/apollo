#pragma once
#pragma once
#include "pugixml.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class XML
{
public:
	static void open(const std::string& file);
	static void openNode(const char* node);
	static void closeNode();
	static int getInt(const char* label);
	static float getFloat(const char* label);
	static char* getChar(const char* label);
	static std::string getString(const char* label);
	static bool getBool(const char* label);
	static void openInlineValue(const char* label);
	static int getInlineInt(const char* label);
	static float getInlineFloat(const char* label);
	static char* getInlineChar(const char* label);
	static std::string getInlineString(const char* label);
	static bool getInlineBool(const char* label);
	static int getCurrentNodeId();
	static pugi::xml_node getCurrentNode();
	static void addNodeToStack(pugi::xml_node node);
private:
	static std::vector <pugi::xml_node> nodes;
	static pugi::xml_document doc;
	static pugi::xml_node attribute;
};