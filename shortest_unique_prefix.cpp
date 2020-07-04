#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NUM_OF_ALPHA 26
#define CHAR_TO_INT(x) ((int)x - 'a')

struct TrieNode {
    struct TrieNode* children[NUM_OF_ALPHA];
    int freq;
};

struct TrieNode* getNode(void)
{
    struct TrieNode* newNode = new TrieNode;
    for (int i = 0; i < NUM_OF_ALPHA; i++)
        newNode->children[i] = NULL;
    newNode->freq = 1;
    return newNode;
}

void insert(struct TrieNode* root, string words)
{
    TrieNode* p = root;
    for (int i = 0; i < words.size(); i++) {
        int index = CHAR_TO_INT(words[i]);
        if (!p->children[index])
            p->children[index] = getNode();
        else
            p->children[index]->freq += 1;
        p = p->children[index];
    }
}

vector<string> shortest_unique_prefix(vector<string> words)
{
    TrieNode* root = getNode();
    TrieNode* p;
    vector<string> res;

    for (auto word: words)
        insert(root, word);
    
    for (auto word: words) {
        p = root;
        for (int i = 0; i < word.size(); i++) {
            int index = CHAR_TO_INT(word[i]);
            p = p->children[index];
            if (p->freq == 1) {
                res.push_back(word.substr(0, i+1));
                break;
            }
        }
    }
    return res;
}

int main()
{
    vector<string> words = {"zebra", "dog", "duck", "dove"};
    vector<string> res = shortest_unique_prefix(words);
    for (auto word: res)
        cout << word << " ";
    cout << endl;
}
