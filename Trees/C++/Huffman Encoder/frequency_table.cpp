#include "frequency_table.h"

frequency_table::frequency_table(const std::string &file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        char c;
        while (file.get(c)) {
            std::unordered_map<char, int>::iterator it = this->frequencies.find(c);
            if (it != this->frequencies.end()) {
                it->second++;
            } else {
                this->frequencies.insert(std::make_pair(c, 1));
            }
        }
    } else {
        throw std::runtime_error("The file could not be opened.");
    }
    file.close();
}

frequency_table::~frequency_table() {

}

int frequency_table::get_frequency(char c) const {
    return this->frequencies.find(c) != this->frequencies.end() ? this->frequencies.find(c)->second : 0;
}
