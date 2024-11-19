#include <array>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

class Dish {
private:
    string description;

public:
    Dish(string description) {
        this->description = description;
    }

    string get_description() {
        return this->description;
    }
};

template <typename T>
class Stack {
private:
    static const int MAX_SIZE = 100;
   array<T*, MAX_SIZE> items;
    int top;

public:
    Stack() : top(-1) {
        items.fill(nullptr);
    }

    ~Stack() {
        while (top >= 0) {
            delete items[top];
            top--;
        }
    }

    void push(T* item) {
        if (top >= MAX_SIZE - 1) {
            cout << "Stack is full! Cannot add more items." << endl;
            return;
        }
        items[++top] = item;
    }

    T* pop() {
        if (top < 0) {
            throw runtime_error("Stack is empty!");
        }
        return items[top--];
    }

    T* peek() {
        if (top < 0) {
            throw runtime_error("Stack is empty!");
        }
        return items[top];
    }

    int size() {
        return top + 1;
    }

    bool isEmpty() {
        return top < 0;
    }

    void clear() {
        while (top >= 0) {
            delete items[top];
            items[top] = nullptr;
            top--;
        }
    }
};

int main() {
    Stack<Dish> dishStack;
    Stack<int> intStack;
    
    string filename = "data.txt";  
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 5) == "dish,") {
            string description = line.substr(5);
            dishStack.push(new Dish(description));
        }
        else if (line.substr(0, 4) == "int,") {
            int value = stoi(line.substr(4));
            intStack.push(new int(value));
        }
    }
    
    file.close();
    
    cout << "Dish stack size: " << dishStack.size() << endl;
    if (!dishStack.isEmpty()) {
        cout << "Top dish: " << dishStack.peek()->get_description() << endl;
    }
    
    cout << "\nInteger stack size: " << intStack.size() << endl;
    if (!intStack.isEmpty()) {
        cout << "Top number: " << *intStack.peek() << endl;
    }
    
    dishStack.clear();
    intStack.clear();
    
    return 0;
}
