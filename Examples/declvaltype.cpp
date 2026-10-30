#include <utility>

struct MyClass {
    MyClass(int) {} // No default constructor
    double foo() const { return 3.14; }
};

// Deduces the return type of MyClass::foo()
using FooReturnType = decltype(std::declval<MyClass>().foo()); 
// FooReturnType is double

