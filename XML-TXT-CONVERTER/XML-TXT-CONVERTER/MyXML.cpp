#include "MyXML.h"
MyXML::MyXML(std::string filename) {
	this->filename = filename;
}
void MyXML::convert() {
    std::ifstream input(filename + ".xml");
    std::vector<char> buf((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    rapidxml::xml_document<> xml_doc;
    xml_doc.parse<0>(&buf[0]);

    std::ofstream output;
    output.open(filename + ".txt");

    for (rapidxml::xml_node<>* row_node = xml_doc.first_node("row"); row_node; row_node = row_node->next_sibling()) {
        for (rapidxml::xml_node<>* column_node = row_node->first_node("col"); column_node; column_node = column_node->next_sibling())
        {
            output << column_node->value() << " ";
        }
        output << "\n";
    }

    output.close();
    return;
}