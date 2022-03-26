#include "MyTXT.h"
MyTXT::MyTXT(std::string filename, std::string in_dir, std::string out_dir) {
    this->filename = filename;
    this->in_dir = in_dir;
    this->out_dir = out_dir;
}
void MyTXT::convert() {
    std::ifstream input(in_dir + filename + ".txt");
    std::ofstream output;
    output.open(out_dir + filename + ".xml");

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