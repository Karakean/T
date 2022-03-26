#include "MyXML.h"
MyXML::MyXML(std::string filename, std::string in_dir, std::string out_dir) {
	this->filename = filename;
    this->in_dir = in_dir;
    this->out_dir = out_dir;
}
void MyXML::convert() {
    std::ifstream input(in_dir + filename + ".xml");
    std::vector<char> buf((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    rapidxml::xml_document<> xml_doc;
    xml_doc.parse<0>(&buf[0]);

    std::ofstream output;
    output.open(out_dir + filename + ".txt");

    for (rapidxml::xml_node<>* row_node = xml_doc.first_node("row"); row_node; row_node = row_node->next_sibling()) {
        if (strcmp(row_node->name(), "row"))
            throw "Invalid XML file.\n";
        for (rapidxml::xml_node<>* column_node = row_node->first_node("col"); column_node; column_node = column_node->next_sibling())
        {
            if (strcmp(column_node->name(), "col"))
                throw "Invalid XML file.\n";
            output << column_node->value() << " ";
        }
        output << "\n";
    }

    output.close();
    return;
}