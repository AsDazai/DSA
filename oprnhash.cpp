#include <iostream>
#include <string>
#include <list>

using namespace std;

// Node for linked list
template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K, V>* next;

    Node(K key, V value) : key(key), value(value), next(nullptr) {}
};

// Hash Table using Open Addressing with Linked Lists
template<typename K, typename V, typename Hash = hash<K>>
class HashTable {
private:
    int size;
    list<Node<K, V>>* table;
    Hash hashFunction;

    // Hash function
    size_t hash(K key) {
        return hashFunction(key) % size;
    }

public:
    HashTable(int size) : size(size) {
        table = new list<Node<K, V>>[size];
    }

    // Insert key-value pair
    void insert(K key, V value) {
        size_t index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                // Update value if key already exists
                node.value = value;
                return;
            }
        }
        table[index].push_back(Node<K, V>(key, value));
    }

    // Find value by key
    V find(K key) {
        size_t index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                return node.value;
            }
        }
        throw out_of_range("Key not found");
    }

    // Delete key-value pair
    void remove(K key) {
        size_t index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                return;
            }
        }
        throw out_of_range("Key not found");
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }
};

int main() {
    HashTable<string, int> dictionary(10);

    // Insert key-value pairs
    dictionary.insert("apple", 10);
    dictionary.insert("banana", 20);
    dictionary.insert("orange", 30);

    // Find values
    try {
        cout << "Value of apple: " << dictionary.find("apple") << endl;
        cout << "Value of banana: " << dictionary.find("banana") << endl;
        cout << "Value of orange: " << dictionary.find("orange") << endl;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }

    // Delete a key-value pair
    try {
        dictionary.remove("banana");
        cout << "Value of banana after deletion: " << dictionary.find("banana") << endl;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
