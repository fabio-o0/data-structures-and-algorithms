#include <queue>
#include <vector>
#include "huffman_encoder.h"

huffman_encoder::huffman_encoder(const frequency_table &table){
    std::priority_queue<node*, std::vector<node*>, comparator> pq;
    auto it = table.frequencies.begin();
 
    while (it != table.frequencies.end()) {
        pq.push(new node(it->first, it->second));
        it++;
    }
    
    bool done = false;
    int i = 0;
    while (pq.size() != 0 && !done) {
        node* left = pq.top();
        pq.pop();
        
        node* right;
        if (pq.size() != 0) {
            right = pq.top();
            pq.pop();
            
            node* val = new node('#', left->frequency + right->frequency);
            
            val->left = left;
            val->right = right;
            
            pq.push(val);
        } else {
            pq.push(left);
            if (i > 0) {
                done = true;
            } else {
                node* val = new node('#', left->frequency);
                val->left = left;
                val->right = nullptr;
                pq.push(val);
            }
            right = nullptr;
        }
        i++;
    }
    
    this->root = pq.top();
    
    int arr[100], top = 0;
    encodeChars(this->root, arr, top, this->matchedChars);
}

huffman_encoder::~huffman_encoder(){

}

std::string huffman_encoder::get_character_code(char character) const {
    auto c = this->matchedChars.find(character);
    if (c != this->matchedChars.end()) {
        return c->second;
    }
    return "";
}

std::string huffman_encoder::encode(const std::string &file_name) const {
    std::string result = "";
    
    std::ifstream file(file_name);
    if (file.is_open()) {
        char c;
        while (file.get(c)) {
            auto ch = this->matchedChars.find(c);
            if (ch == this->matchedChars.end()) {
                return "";
            } else {
                result += ch->second;
            }
        }
    } else {
        throw std::runtime_error("The file could not be opened.");
    }
    file.close();
    
    return result;
}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    std::string result = "";
    
    auto curr = this->root;
    for (char c : string_to_decode) {
        if (c == '0') {
            curr = curr->left;
        } else if (c == '1') {
            curr = curr->right;
        } else {
            return "";
        }
        
        if (curr->left == nullptr && curr->right == nullptr) {
            result += curr->data;
            curr = this->root;
        }
    }
    
    return result;
}

void huffman_encoder::encodeChars(node* root, int* arr, int top, std::unordered_map<char, std::string> &encoded) const {
    if (root->left) {
        arr[top] = 0;
        encodeChars(root->left, arr, top + 1, encoded);
    }
    
    if (root->right) {
        arr[top] = 1;
        encodeChars(root->right, arr, top + 1, encoded);
    }
    
    if (!root->left && !root->right) {
        std::string temp = "";
        for (int i = 0; i < top; i++) {
            temp += std::to_string(arr[i]);
        }
        encoded.insert(std::make_pair(root->data, temp));
    }
}
