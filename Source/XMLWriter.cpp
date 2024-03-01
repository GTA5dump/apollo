#include "XMLWriter.h"
#include "stdafx.h"

std::vector <std::string> XMLWriter::nodes;
int XMLWriter::depth;
std::ofstream XMLWriter::file;

void XMLWriter::open(const std::string& file)
{
	if (XMLWriter::file.is_open())
		XMLWriter::close();
	XMLWriter::file.open(file);
}

void XMLWriter::close()
{
	XMLWriter::file.close();
	XMLWriter::depth = 0;
	XMLWriter::nodes.clear();
}

void XMLWriter::createNode(const std::string& label)
{
	addTabs();
	file << "<" << label << ">" << std::endl;
	depth++;
	nodes.push_back(label);
}

void XMLWriter::closeNode()
{
	depth--;
	addTabs();
	file << "</" << nodes[nodes.size() - 1] << ">" << std::endl;
	nodes.erase(nodes.begin() + nodes.size() - 1);
}

void XMLWriter::addTabs()
{
	for (int i = depth; i--;)
	{
		file << "  ";
	}
}

void XMLWriter::createInlineValue(const std::string& label)
{
	addTabs();
	file << "<" + label;
}

void XMLWriter::endInlineValue()
{
	file << " />" << std::endl;
}