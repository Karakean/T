#include "MyTXT.h"
MyTXT::MyTXT(std::string filename) {
	this->filename = filename;
}
void MyTXT::convert() {
    std::ifstream input(filename + ".txt");
    std::ofstream output;
    output.open(filename + ".xml");

    std::string line;
    while (getline(input, line)) {
        output << "<row>\n";

        std::size_t space_position;
        while ((space_position = line.find(" ")) != std::string::npos) {
            if ((line.find("<") != std::string::npos ||
                line.find(">") != std::string::npos))
                throw "Error. Text file cannot contain \"<\" nor \">\"";

            if (!(line.substr(0, space_position).empty()))
                output << "<col>" << line.substr(0, space_position) << "</col>\n";

            line.erase(0, space_position + 1);
        }
        if (!line.empty())
            output << "<col>" << line << "</col>\n";

        output << "</row>\n";
    }

    output.close();
    return;
}