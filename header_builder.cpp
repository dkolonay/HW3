#include "header_builder.h"
#include <vector>
#include <string>

std::string HeaderBuilder::createHeaderInputElement(std::string filename){
    return "\\input{" + filename + "}\n";
}

HeaderBuilder::HeaderBuilder(std::string tHead, std::string cHead){
    texHeader = createHeaderInputElement(tHead);
    contentHeader = createHeaderInputElement(cHead);
}

void HeaderBuilder::addHeaderElement(std::string elementName, std::string elementContent){
    headerElements.push_back("\\newcommand{\\" + elementName + "}{" + elementContent + "}\n");
}

void HeaderBuilder::addHeaderElement(std::string elementName, int elementContent){
    headerElements.push_back("\\newcommand{\\" + elementName + "}{" + std::to_string(elementContent) + "}\n");
}

std::string HeaderBuilder::build(){
    std::string header = "";
    header = header + texHeader;

    for (std::string element : headerElements)
    {
        header = header + element;
    }
    header = header + contentHeader;

    return header;
}
