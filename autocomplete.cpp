#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define ALPHABET_SIZE 26
#define CHAR_TO_INT(c) ((int)c - 'a')

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isWordEnd;
};

struct TrieNode* getNode(void)
{
    TrieNode* newNode = new TrieNode();
    for (int i=0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->isWordEnd = false;
    return newNode;
}

void insert(struct TrieNode* root, const string word)
{
    struct TrieNode* p = root;
    for (int i = 0; i < word.size(); i++) {
        int index = CHAR_TO_INT(word[i]);
        if (!p->children[index])
            p->children[index] = getNode();
        p = p->children[index];
    }
    p->isWordEnd = true;
}

bool isLastNode(struct TrieNode* root)
{
    for (int i=0; i<ALPHABET_SIZE; i++) {
        if (root->children[i])
            return false;
    }
    return true;
}

void suggestions(struct TrieNode* root, string prefix)
{
    if (!root) return;
    if (root->isWordEnd) {
        cout << prefix << endl;
    }
    for (int i=0; i<ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            prefix.push_back(97 + i);
            suggestions(root->children[i], prefix);
            prefix.pop_back();
        }
    }
}

int printAutoSuggestions(struct TrieNode* root, string query)
{
    struct TrieNode* p = root;
    for (int i=0; i<query.size(); i++) {
        int index = CHAR_TO_INT(query[i]);
        if (!p->children[index])
            return -1;
        p = p->children[index];
    }
    if (isLastNode(p) && p->isWordEnd) {
        cout << query << endl;
        return 1;
    }
    if (!isLastNode(p)) {
        suggestions(p, query);
    }
    return 0;
}

int main() {
    struct TrieNode* root = getNode();
    insert(root, "dog");
    insert(root, "dark");
    insert(root, "cat");
    insert(root, "door");
    insert(root, "dodge");
    printAutoSuggestions(root, "do");
    return 0;
}