#pragma once
#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class XMLWriter
{
public:
	static void open(const std::string& file);
	static void close();
	static void createNode(const std::string& label);
	static void closeNode();
	static void addTabs();
	static void createInlineValue(const std::string& label);
	template <typename T>
	static void addValueToInlineValue(const std::string& label, T value)
	{
		file << " " << label << "=\"" << std::to_string(value) << "\"";
	}
	template <typename T>
	static void addStringToInlineValue(const std::string& label, T value)
	{
		file << " " << label << "=\"" << value << "\"";
	}
	static void endInlineValue();
	template <typename T>
	static void writeValue(const std::string& label, T value)
	{
		addTabs();
		file << "<" << label << ">" << std::to_string(value) << "</" << label << ">" << std::endl;
	}
	template <typename T>
	static void writeString(const std::string& label, T value)
	{
		addTabs();
		file << "<" << label << ">" << value << "</" << label << ">" << std::endl;
	}
private:
	static std::vector <std::string> nodes;
	static int depth;
	static std::ofstream file;
};