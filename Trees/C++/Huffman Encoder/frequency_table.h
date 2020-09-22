#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>

class frequency_table {
    public:
        // Something to store the frequency of each character
        std::unordered_map<char, int> frequencies; //hash table

    
        frequency_table(const std::string &file_name);
        ~frequency_table();

        int get_frequency(char c) const;
};
