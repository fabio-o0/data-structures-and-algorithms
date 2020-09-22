#pragma once

#include "frequency_table.h"

class huffman_encoder {
    class node {
    public:
        char data;
        unsigned int frequency;
        
        node* left;
        node* right;
        
        node(char data, unsigned int frequency) {
            this->data = data;
            this->frequency = frequency;
            this->left = this->right = nullptr;
        }
    };
    
    class comparator {
    public:
        bool operator () (node* node1, node* node2) {
            return node1->frequency > node2->frequency;
        }
    };
    
    private:
        node* root;
        std::unordered_map<char, std::string> matchedChars;
    
    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();

        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &string_to_decode) const;
        void encodeChars(node* root, int* arr, int top, std::unordered_map<char, std::string> &encoded) const;
};
