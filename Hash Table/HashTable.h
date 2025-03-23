#pragma once
#include <iostream>
#include <vector>
#include <fstream>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable
{
private:
    std::vector<std::pair<Key, Value>> table;
    int size;
    int capacity;
    const double load_factor_threshold = 0.7;
    const double contamination_threshold = 0.1;
    Hash h1;

    int next_size(int curr_size) const;

    size_t h2(const Key& key) const;

    void rehashWithDouble();

    void check_load_factor();

    void rehash();

    void check_contamination();

public:
    HashTable();

    ~HashTable();

    void insert(const Key& key, const Value& value);

    bool contains(const Key& key) const;

    void erase(const Key& key);

    Value& operator[](const Key& key);

    class Iterator
    {
    private:
        std::vector<std::pair<Key, Value>>& table;
        int index;

    public:
        Iterator(std::vector<std::pair<Key, Value>>& table, int index) : table(table), index(index) {}

        bool operator!=(const Iterator& other) const
        {
            return index != other.index;
        }

        Iterator& operator++();
 

        std::pair<Key, Value>& operator*() const
        {
            return const_cast<std::pair<Key, Value>&>(table[index]);
        }

        Iterator& operator=(const Iterator& other)
        {
            if (this != &other)
            {
                table = other.table;
                index = other.index;
            }
            return *this;
        }
    };

    Iterator begin()
    {
        int index = 0;
        while (index < capacity && table[index].first == Key{})
        {
            index++;
        }
        return Iterator(table, index);
    }

    Iterator end()
    {
        return Iterator(table, capacity);
    }
};

template<typename Key, typename Value, typename Hash>
int HashTable<Key, Value, Hash>::next_size(int curr_size) const
{
    return curr_size * 2;
}

template<typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::h2(const Key& key) const
{
    return (h1(key) * 2) + 1;
}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::rehashWithDouble()
{
    int new_capacity = next_size(capacity);
    std::vector<std::pair<Key, Value>> new_table(new_capacity);
    for (const auto& pair : table)
    {
        int index = h1(pair.first) % new_capacity;
        int step = h2(pair.first) % new_capacity;
        while (new_table[index].first != Key{})
        {
            index = (index + step) % new_capacity;
        }
        new_table[index] = pair;
    }
    table = new_table;
    capacity = new_capacity;
}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::check_load_factor()
{
    if (static_cast<double>(size) / capacity > load_factor_threshold)
    {
        rehashWithDouble();
    }
}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::rehash()
{
    int new_capacity = capacity;
    std::vector<std::pair<Key, Value>> new_table(new_capacity);
    for (const auto& pair : table)
    {
        int index = h1(pair.first) % new_capacity;
        int step = h2(pair.first) % new_capacity;
        while (new_table[index].first != Key{})
        {
            index = (index + step) % new_capacity;
        }
        new_table[index] = pair;
    }
    table = new_table;
}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::check_contamination()
{
    size_t contamination = 0;
    for (const auto& pair : table)
    {
        if (pair.first != Key{})
            contamination++;
    }
    if (static_cast<double>(contamination) / capacity > contamination_threshold)
    {
        rehash();
    }
}

template<typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::HashTable() : size(0), capacity(8), table(8)
{

}

template<typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::~HashTable()
{

}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::insert(const Key& key, const Value& value)
{
    check_load_factor();
    int index = h1(key) % capacity;
    int step = h2(key) % capacity;
    while (table[index].first != Key{})
    {
        if (table[index].first == key)
        {
            table[index].second = value;
            return;
        }
        index = (index + step) % capacity;
    }
    table[index] = std::make_pair(key, value);
    size++;
    check_contamination();
}

template<typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::contains(const Key& key) const
{
    int index = h1(key) % capacity;
    int step = h2(key) % capacity;
    while (table[index].first != Key{})
    {
        if (table[index].first == key)
        {
            return true;
        }
        index = (index + step) % capacity;
    }
    return false;
}

template<typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::erase(const Key& key)
{
    if (contains(key) == false)
    {
        std::cout << "Nu contine cheia " << key << " pentru a fi stearsa." << std::endl;
        return;
    }
    else
    {
        std::cout << "Element sters." << std::endl;
    }
    int index = h1(key) % capacity;
    int step = h2(key) % capacity;
    while (table[index].first != Key{})
    {
        if (table[index].first == key)
        {
            table[index].first = Key{};
            size--;
            return;
        }
        index = (index + step) % capacity;
    }
}

template<typename Key, typename Value, typename Hash>
Value& HashTable<Key, Value, Hash>::operator[](const Key& key)
{
    check_load_factor();
    int index = h1(key) % capacity;
    int step = h2(key) % capacity;
    while (table[index].first != Key{})
    {
        if (table[index].first == key)
        {
            return table[index].second;
        }
        index = (index + step) % capacity;
    }
    table[index].first = key;
    size++;
    check_contamination();
    return table[index].second;
}

template<typename Key, typename Value, typename Hash>
inline HashTable<Key, Value, Hash>::Iterator& HashTable<Key, Value, Hash>::Iterator::operator++()
{
    do
    {
        index++;
    } while (index < table.size() && table[index].first == Key{});
    return *this;
}
