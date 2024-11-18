#include <stdexcept>
#include <memory>


class MyClass {
public:
    MyClass() { data = new int[100]; }
    // Uncomment this line to fix the memory leak
    // ~MyClass() { delete[] data; } 
private:
    int* data;
};
bool some_condition = true;

void foo() {
    int* ptr = new int[100];
    if (some_condition) {
        throw std::runtime_error("Error");
    }
    // doesnt get deleted if exception is thrown
    delete[] ptr;  
}


std::shared_ptr<int> ptr1 = std::make_shared<int>(10);

std::unique_ptr<int> ptr2 = std::make_unique<int>(20);

// ptr3 = ptr2; // will not work because unique_ptr is not copyable
std::unique_ptr<int> ptr3 = std::move(ptr2);

// ptr4 = ptr1; // will  work because shared_ptr is copyable
std::shared_ptr<int> ptr4 = ptr1;

std::weak_ptr<int> ptr5 = ptr4; // weak_ptr is a weak reference to a shared_ptr
