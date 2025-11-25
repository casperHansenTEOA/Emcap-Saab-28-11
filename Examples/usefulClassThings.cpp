// ...existing code...

#include <iostream>
#include <memory>
#include <vector>
#include <string>

//
// 1) Basic inheritance & polymorphism
//
// Key differences vs Java:
// - C++ methods are non-virtual by default. Use `virtual` to allow runtime dispatch.
// - Use `override` on overridden methods (helps catch errors).
// - If you delete objects via a base pointer, the base needs a virtual destructor.
//

struct Animal {                // 'struct' defaults to public; 'class' defaults to private
    std::string name;
    Animal(std::string n) : name(std::move(n)) {}
    virtual ~Animal() = default;       // virtual dtor prevents undefined behavior on delete
    virtual void speak() const {       // non-virtual in C++ would be like 'final' in Java
        std::cout << name << " (Animal)\n";
    }
};

struct Dog : Animal {
    Dog(std::string n) : Animal(std::move(n)) {}
    void speak() const override {      // override -> compile-time check
        std::cout << name << " says: woof\n";
    }
};

//
// 2) Polymorphism in action (use smart pointers in modern C++)
//
void demoPolymorphism() {
    std::unique_ptr<Animal> a = std::make_unique<Dog>("Rex");
    a->speak(); // calls Dog::speak because speak() is virtual
}

//
// 3) Object slicing (gotcha for Java devs)
// If you assign a derived object to a base object (not pointer/reference), the derived parts are sliced off.
//
void demoSlicing() {
    Dog d("Buddy");
    Animal a = d;      // slice: a is a plain Animal copy of d
    a.speak();         // calls Animal::speak, not Dog::speak
    // Avoid slicing: use pointers or references.
}

//
// 4) Pure virtual (interface-like) & multiple inheritance
//
// In Java, interfaces exist. In C++ you model them with abstract classes (pure virtual).
//
struct Flyer {
    virtual ~Flyer() = default;
    virtual void fly() const = 0;   // pure virtual
};

struct Swimmer {
    virtual ~Swimmer() = default;
    virtual void swim() const = 0;
};

struct Duck : Animal, Flyer, Swimmer {
    Duck(std::string n) : Animal(std::move(n)) {}
    void speak() const override { std::cout << name << " quacks\n"; }
    void fly() const override { std::cout << name << " flies\n"; }
    void swim() const override { std::cout << name << " swims\n"; }
};

//
// 5) Diamond problem & virtual inheritance
//
// If two base classes share a common ancestor, you can get two copies of the ancestor.
// Use virtual inheritance to ensure a single shared base subobject.
//
struct A { virtual ~A() = default; int value = 42; };
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {
    // D has a single A subobject due to `virtual` inheritance
};

//
// 6) Nested classes (inner classes) differences vs Java
//
// In Java, non-static inner classes implicitly reference the outer instance.
// In C++, nested classes are like Java's static nested classes: they do NOT have an implicit
// pointer to the outer instance. Pass a reference if you need it.
//
struct Outer {
    int outerVal = 7;

    struct Inner {                 // no implicit access to Outer members
        void show(Outer& o) const { // pass outer explicitly
            std::cout << "outerVal = " << o.outerVal << "\n";
        }
    };

    // Friend nested class can access private members:
    struct SecretInner {
        void reveal(const Outer& o) const {
            // if SecretInner is declared friend of Outer, it could access privates.
            std::cout << "secret outerVal = " << o.outerVal << "\n";
        }
    };
};

//
// 7) Usage demo
//
int main() {
    demoPolymorphism();
    demoSlicing();

    Duck duck("Daffy");
    std::vector<Animal*> zoo = { &duck, /* could hold other animals */ };
    for (auto a : zoo) a->speak();

    Outer::Inner in;
    Outer out;
    in.show(out);

    // Demonstrate diamond:
    D d;
    std::cout << "single A::value through D = " << d.value << "\n";

    return 0;
}

// ...existing code...