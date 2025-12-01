#ifndef HEADER_BUILDER_H
#define HEADER_BUILDER_H

#include "string"
#include "vector"

class HeaderBuilder
{
private:
    std::string texHeader;
    std::string contentHeader;
    std::vector<std::string> headerElements;

    std::string createHeaderInputElement(std::string filename);

public:
    HeaderBuilder(std::string tHead, std::string cHead);
    void addHeaderElement(std::string elementName, std::string elementContent);
    void addHeaderElement(std::string elementName, int elementContent);
    std::string build();
};

#endif