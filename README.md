# 🔢 Hash Table Implementation in C++

## 📌 Overview  
This **C++ Hash Table Implementation** provides an efficient **key-value storage solution** using **open addressing with double hashing** to handle collisions. The implementation dynamically resizes and redistributes elements when needed to maintain optimal performance.

## 🛠️ Features  
### **🔹 Core Functionalities**  
- **Efficient Insertion, Lookup, and Deletion** operations.
- **Open Addressing with Double Hashing** to resolve collisions.
- **Automatic Resizing & Rehashing** when the load factor exceeds `0.7`.
- **Contamination Handling**: If contamination exceeds `10%`, the table is rehashed.

### **🔹 Additional Operations**  
- **Operator Overloading (`[]`)** for easy access and modification of values.
- **Custom Iterators** to enable traversal through the hash table.
- **Interactive CLI Menu** for user interaction and testing.
- **Reading Input from File** (`file.in`) for bulk data insertion.

## 🚀 How It Works  
1. **Users add key-value pairs** via the interactive menu or file input.  
2. **Collisions are handled using double hashing** (primary and secondary hash functions).  
3. **If the load factor or contamination threshold is exceeded**, the table is resized and rehashed.  
4. **Users can search, modify, or delete elements** dynamically.  

## 🔧 Technologies Used  
- **C++** for implementation.
