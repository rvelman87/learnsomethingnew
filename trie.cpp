/*
 * Goal: Be able to insert and search words in a tree structure.
 *       Each letter represents a node in the data structure.
 *
 * Example:
 *
 * insert("CAT");
 *
 *         () - C - A - T       // "CAT"
 *
 * insert("CALL");
 *
 *         () - C - A - T       // "CAT"
 *                   \ 
 *                    - L - L   // "CALL"
 *
 * Step 1: Design and explain the data structure
 *
 * Step 2: Code and test the insert function
 *         void insert(const std::string& iWord);
 *
 * Step 3: Code and test the search function
 *         bool search(const std::string& iWord);
 */

#include <iostream>
using namespace std;
#define DEBUG 0
#define TRIE_CHARS_A_Z 26


class Node {

    /*Moved all elements to public, because i can access anywhere*/
    /*Also moved the 26 to Define, removing magic number*/
    /*As we know we are working with values A-Z, 26 characters,*/
    /*we will keep indexing based on index of alphabets*/
    /*An extra character to hold character at the node is not required*/
    /*track the end of word with isLeaf*/
    
    
public:
    bool isLeaf;
    Node *ptr[TRIE_CHARS_A_Z]; /*Node pointer to next 26 combo*/
    Node() {
        isLeaf =false;
        for (int i=0; i<TRIE_CHARS_A_Z; i++) {
            this->ptr[i] = NULL;
        }
    }

    void insert( Node *root, const string &iword);

    bool search(Node *root, const string &iword);


    
};


void Node:: insert( Node * root, const string &iword) {
    if(iword.length() == 0) { //boundary check
        return;
    }

    /*If the character already exists, then skip.
     * continue until, the next node is not the character.
     * break at this condition.
     * create a new node and add to the ptr of the current node.
     * if iword length is traversed, retrun
     * else, create new nodes for all remainig iword one by one, add to pointer
    */
    Node *curr = root;

    for (int i =0; i<iword.length(); i++) {
        int index = iword[i] - 'A';
        #if DEBUG
            cout<<" i = " <<i<<endl;
            cout<<"curr[i]->" << curr->ptr[i] << "Isleaf  "<<(curr->isLeaf)  << "index " <<index <<endl;
        #endif

        if (curr->ptr[index] == nullptr) {
        #if DEBUG
                cout<<"Char is not exists " << iword[i] <<endl;
        #endif
                /*Create a node here*/
                curr->ptr[index] = new Node();

        }
        #if DEBUG
        else {

                cout<<"This index exists " <<iword[i] <<endl;
        }
        #endif
        curr = curr->ptr[index];
    }

    curr->isLeaf = true;
}


bool Node:: search(Node *root, const string &iword) {
    if (iword.length() == 0) {
        return false;
    } 
    /*Look for character at the index derived.
        if the node is present, look for next index,
        if found, continue else retrun false*/

    Node *curr = root;
    for (int i=0; i<iword.length(); i++) {

        int index = iword[i] - 'A';
        #if DEBUG
            cout<<"Index " << index << "iword " << iword[i] <<endl;
        #endif
        curr = curr->ptr[index];
        if(curr == nullptr) {
            return false;
        }
    }

    return curr->isLeaf;
}


int main() {

    Node *root = new Node(); //create the empty node
    cout<< "Insert CAT " << endl;
    root->insert(root, "CAT");
    cout << "Search for string  CE, Is CE present ?" << root->search(root, "CE")<<endl;
    cout << "Search for string CAT, Is CAT present ?" << root->search(root, "CAT")<<endl;
    cout<< "Insert CALL " << endl;
    root->insert(root, "CALL");
#if 1
    cout<< "Search for string AT, Is AT present " << root->search(root, "AT") <<endl;
    cout<< "Search for string CAT Is CAT present " << root->search(root, "CAT") <<endl;
    cout<< "Search for string CALL Is CALL present " << root->search(root, "CALL") <<endl;
#endif
}

