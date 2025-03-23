#include "HashTable.h"

int main()
{
    HashTable<int, std::string> hash_table;
    std::ifstream file("file.in");
    int number;
    file >> number;
    for (int i = 0; i < number; i++)
    {
        std::pair<int, std::string> element;
        file >> element.first >> element.second;
        hash_table.insert(element.first, element.second);
    }

    int choice;
    do
    {
        std::cout << "1. Cautarea unei chei" << std::endl;
        std::cout << "2. Adaugarea unei perechi" << std::endl;
        std::cout << "3. Stergerea unei chei" << std::endl;
        std::cout << "4. Iesire" << std::endl << std::endl;
        std::cout << "Introduceti optiunea: ";
        std::cin >> choice;
        switch (choice) 
        {
        case 1: 
        {
            int key;
            std::cout << "Introduceti cheia pentru cautare: ";
            std::cin >> key;
            if (hash_table.contains(key)) 
            {
                std::cout << "Elementul cu cheia " << key << " exista in tabel si are valoarea " << hash_table[key] << "." << std::endl;
            }
            else 
            {
                std::cout << "Elementul cu cheia " << key << " nu exista in tabel." << std::endl;
            }
            std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
            break;
        }
        case 2:
        {
            int key;
            std::string value;
            std::cout << "Introduceti cheia si valoarea pentru adaugare: ";
            std::cin >> key >> value;
            hash_table.insert(key, value);
            std::cout << "Element adaugat." << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
            break;
        }
        case 3:
        {
            int key;
            std::cout << "Introduceti cheia pentru stergere: ";
            std::cin >> key;
            hash_table.erase(key);
            std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
            break;
        }
        case 4:
            std::cout << "Iesire din program." << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
            break;
        default:
            std::cout << "Optiune invalida." << std::endl << "Introduceti o optiune valida." << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl << std::endl;
        }
    } while (choice != 4);

    return 0;
}
