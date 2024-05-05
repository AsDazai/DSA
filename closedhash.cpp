#include <iostream>
#include <list>
#include <utility>
using namespace std;

struct KeyValuePair {
    string key;
    string value;
    KeyValuePair(const string& k, const string& v) : key(k), value(v) {}
};

class Dictionary {
public:
    static const int TABLE_SIZE = 10; // Size of the hash table
    list<KeyValuePair> table[TABLE_SIZE]; // Array of linked lists for separate chaining

    int hashFunction(const string& key) {
        int hash = 0;
       for (int i = 0; i < key.size(); ++i) {
            char c = key[i];
            hash += c;
       }
        return hash % TABLE_SIZE;
    }

public:
    void Insert(const string& key, const string& value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }
        table[index].push_back(KeyValuePair(key, value));
    }

    string Find(const string& key) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        return "Key not found";
    }

    
};

int main() {
    Dictionary dict;

    dict.Insert("apple", "A fruit");
    dict.Insert("banana", "A fruit");
    dict.Insert("cat", "A domestic animal");
    dict.Insert("dog", "A domestic animal");

    cout<<" apple, A fruit\n banana ,A fruit\n cat , A domestic animal\n dog , A domestic animal\n ";

    cout<<"enter the key which vallue u wanna find : ";
    string ff;
    cin>>ff;

    cout << "\nValue for key "<< ff <<" "<< dict.Find(ff) << endl;
    return 0;
}
