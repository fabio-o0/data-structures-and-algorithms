#pragma once
#include <vector>
#include <exception>
#include <type_traits>
#include <cstring>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

namespace cop3530 {

//AVL Tree
template<typename Key, typename T>
class bst {
    
    struct node {
        // key
        Key key;
        // value
        T data;
        // left child
        node* left;
        // right child
        node* right;
        int height;

        node() {
            left = nullptr;
            right = nullptr;
            height = 1;
        }
        
        node(Key k, T t) {
            key = k;
            data = t;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
        
        const Key getKey() {
            return key;
        }
    };

    // root of tree
    node* root;
    
    node* curr;
    node* prev;

    public:
        bst();
        ~bst();
        node* recurInsert(node* &root, Key key, T t);
        node* recurErase(node* &root, Key key);
        void insert(const Key &key, const T &t);
        void erase(const Key &key);
        T& at(const Key &key);
        bool contains(const Key &key) const;
        bool empty() const;
        size_t size() const;
        node* getRoot();
        std::vector<std::pair<Key, T>> inorder_contents();
        std::vector<std::pair<Key, T>> preorder_contents();
        node* left_left_rotate(node* &curr_node);
        node* right_right_rotate(node* &curr_node);
        int getHeight(node* &curr_node);
        int getBalance(node* &curr_node);

};

template<typename Key, typename T>
bst<Key, T>::bst() {
    root = nullptr;
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::getRoot() {
    return root;
}

template<typename Key, typename T>
bst<Key, T>::~bst() {
    while (!empty()) {
        erase(root->getKey());
    }
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::recurInsert(node* &root, Key key, T t) {
    if (root == nullptr) { //base case
        root = new node(key, t);
        return root;
    }
    else { //recursive case
        if (key < root->key) {
            root->left = recurInsert(root->left, key, t);
        } else if (key > root->key) {
            root->right = recurInsert(root->right, key, t);
        } else {
            root->data = t;
            return root;
        }
    }
    
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    
    int balance = getBalance(root);
    
    if (std::abs(balance) > 1) {
        if (root->left != nullptr) {
            if (balance > 1 && key < root->left->key) {
                return left_left_rotate(root);
            }
        }
        
        if (root->right != nullptr) {
            if (balance < -1 && key > root->right->key) {
                return right_right_rotate(root);
            }
        }
        
        if (root->left != nullptr) {
            if (balance > 1 && key > root->left->key) {
                root->left = right_right_rotate(root->left);
                return left_left_rotate(root);
            }
        }
        
        if (root->right != nullptr) {
            if (balance < -1 && key < root->right->key) {
                root->right = left_left_rotate(root->right);
                return right_right_rotate(root);
            }
        }
    }
    
    return root;
}

template<typename Key, typename T>
void bst<Key, T>::insert(const Key &key, const T &t) {
    if (root == nullptr) {
        root = new node(key, t);
    } else {
        if (key < root->key) {
            root->left = recurInsert(root->left, key, t);
        } else if (key > root->key) {
            root->right = recurInsert(root->right, key, t);
        } else {
            root->data = t;
        }
    }
    
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    
    int balance = getBalance(root);
    
    if (std::abs(balance) > 1) {
        if (root->left != nullptr) {
            if (balance > 1 && key < root->left->key) {
                root = left_left_rotate(root);
            }
        }
        
        if (root->right != nullptr) {
            if (balance < -1 && key > root->right->key) {
                root = right_right_rotate(root);
            }
        }
        
        if (root->left != nullptr) {
            if (balance > 1 && key > root->left->key) {
                root->left = right_right_rotate(root->left);
                root = left_left_rotate(root);
            }
        }
        
        if (root->right != nullptr) {
            if (balance < -1 && key < root->right->key) {
                root->right = left_left_rotate(root->right);
                root = right_right_rotate(root);
            }
        }
    }
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::recurErase(node* &root, Key key) {
    if (root == nullptr) {
        //
    }
    if (key < root->key && root->left != nullptr) {
        root->left = recurErase(root->left, key);
    } else if (key > root->key && root->right != nullptr) {
        root->right = recurErase(root->right, key);
    } else if (key == root->key) {
        if (root->left != nullptr) {
            curr = root->left;
            node* temp = nullptr;
            while (curr->right != nullptr) {
                temp = curr;
                curr = curr->right;
            }
            if (root->right != nullptr) {
                curr->right = root->right;
            }
            node* toDel = root;
            if (temp != nullptr) {
                if (temp->right->left != nullptr) {
                    temp->right = temp->right->left;
                } else {
                    temp->right = nullptr;
                }
                root = curr;
                root->left = toDel->left;
                delete toDel;
                toDel = nullptr;
            } else {
                root = curr;
                delete toDel;
                toDel = nullptr;
            }
            return root;
        } else if (root->right != nullptr) {
            curr = root;
            root = curr->right;
            delete curr;
            curr = nullptr;
        } else {
            delete root;
            root = nullptr;
        }
    }
    
    if (root != nullptr) {
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        
        if (std::abs(balance) > 1) {
            if (root->left != nullptr) {
                if (balance > 1 && getBalance(root->left) >= 0) {
                    return left_left_rotate(root);
                }
            }
            
            if (root->right != nullptr) {
                if (balance < -1 && getBalance(root->right) <= 0) {
                    return right_right_rotate(root);
                }
            }
            
            if (root->left != nullptr) {
                if (balance > 1 && getBalance(root->left) < 0) {
                    root->left = right_right_rotate(root->left);
                    return left_left_rotate(root);
                }
            }
            
            if (root->right != nullptr) {
                if (balance < -1 && getBalance(root->right) > 0) {
                    root->right = left_left_rotate(root->right);
                    return right_right_rotate(root);
                }
            }
        }
    }
    
    return root;
}

template<typename Key, typename T>
void bst<Key, T>::erase(const Key &key) {
    size_t currSize = size();
    if (root == nullptr) {
        //
    }
    else if (key < root->key && root->left != nullptr) {
        root->left = recurErase(root->left, key);
    } else if (key > root->key && root->right != nullptr) {
        root->right = recurErase(root->right, key);
    } else if (key == root->key) {
        if (root->left != nullptr) {
            curr = root->left;
            node* temp = nullptr;
            while (curr->right != nullptr) {
                temp = curr;
                curr = curr->right;
            }
            if (root->right != nullptr) {
                curr->right = root->right;
            }
            node* toDel = root;
            if (temp != nullptr) {
                if (temp->right->left != nullptr) {
                    temp->right = temp->right->left;
                } else {
                    temp->right = nullptr;
                }
                root = curr;
                root->left = toDel->left;
                delete toDel;
                toDel = nullptr;
            } else {
                root = curr;
                delete toDel;
                toDel = nullptr;
            }
        } else if (root->right != nullptr) {
            curr = root;
            root = root->right;
            delete curr;
            curr = nullptr;
        } else {
            delete root;
            root = nullptr;
        }
    }
    
    if (root != nullptr) {
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        
        if (std::abs(balance) > 1) {
            if (root->left != nullptr) {
                if (balance > 1 && getBalance(root->left) >= 0) {
                    root = left_left_rotate(root);
                }
            }
            
            if (root->right != nullptr) {
                if (balance < -1 && getBalance(root->right) <= 0) {
                    root = right_right_rotate(root);
                }
            }
            
            if (root->left != nullptr) {
                if (balance > 1 && getBalance(root->left) < 0) {
                    root->left = right_right_rotate(root->left);
                    root = left_left_rotate(root);
                }
            }
            
            if (root->right != nullptr) {
                if (balance < -1 && getBalance(root->right) > 0) {
                    root->right = left_left_rotate(root->right);
                    root = right_right_rotate(root);
                }
            }
        }
    }
    
    size_t newSize = size();
    if (currSize == newSize) throw std::out_of_range("Value not found");
}

template<typename Key, typename T>
T& bst<Key, T>::at(const Key &key) {
    curr = root;
    while (curr != nullptr) {
        if (key < curr->key) {
            curr = curr->left;
        } else if (key == curr->key) {
            return curr->data;
        } else {
            curr = curr->right;
        }
    }
    throw std::out_of_range("Value not found");
}

template<typename Key, typename T>
bool bst<Key, T>::contains(const Key &key) const {
    node* temp = root;
    while (temp != nullptr) {
        if (key < temp->key) {
            temp = temp->left;
        } else if (key == temp->key) {
            return true;
        } else {
            temp = temp->right;
        }
    }
    return false;
}

template<typename Key, typename T>
bool bst<Key, T>::empty() const {
    return root == nullptr;
}

template<typename Key, typename T>
size_t bst<Key, T>::size() const {
    size_t size = root != nullptr ? 1 : 0;
    if (size == 0) return 0;

    std::queue<node*> q;
    q.push(root);

    while(!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp != nullptr) {
            if (temp->left != nullptr) {
                size++;
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                size++;
                q.push(temp->right);
            }
        }
    }

    return size;

}

template<typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
    std::vector<std::pair<Key, T>> contents;

    if (root == nullptr) {
        return contents;
    }
    
    std::stack<node*> s;
    curr = root;
    
    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();

        contents.push_back(std::make_pair(curr->key, curr->data));

        curr = curr->right;
    }
    return contents;
}

template<typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
    std::vector<std::pair<Key, T>> contents;
    
    if (root == nullptr) {
        return contents;
    }
    
    std::stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        curr = s.top();
        contents.push_back(std::make_pair(curr->key, curr->data));
        s.pop();

        if (curr->right != nullptr) {
            s.push(curr->right);
        }
        if (curr->left != nullptr) {
            s.push(curr->left);
        }
    }
    return contents;
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::left_left_rotate(node* &curr_node) {
    node* left = curr_node->left;
    node* leftRight = left->right;
    
    left->right = curr_node;
    curr_node->left = leftRight;
    
    curr_node->height = std::max(getHeight(curr_node->left), getHeight(curr_node->right)) + 1;
    left->height = std::max(getHeight(left->left), getHeight(left->right)) + 1;
    
    return left;
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::right_right_rotate(node* &curr_node) {
    node* right = curr_node->right;
    node* rightLeft = right->left;
    
    right->left = curr_node;
    curr_node->right = rightLeft;
    
    curr_node->height = std::max(getHeight(curr_node->left), getHeight(curr_node->right)) + 1;
    right->height = std::max(getHeight(right->left), getHeight(right->right)) + 1;
    
    return right;
}

template<typename Key, typename T>
int bst<Key, T>::getHeight(node* &curr_node) {
    if (curr_node == nullptr) return 0;
    return curr_node->height;
}

template<typename Key, typename T>
int bst<Key, T>::getBalance(node* &curr_node) {
    if (curr_node == nullptr) return 0;
    return getHeight(curr_node->left) - getHeight(curr_node->right);
}

}

