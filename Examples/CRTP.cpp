#include <iostream>

template <typename T>
class ShapeCRTP {
private:

    // default implementation (can be overridden)  
    void drawImpl(){
        std::cout << "Base: Default draw implementation." << std::endl;
    }
public:
    void draw() {
        std::cout << "Base: preparing to draw..." << std::endl;
        // Call derived implementation
        static_cast<T*>(this)->drawImpl();
    }

};

class Square : public ShapeCRTP<Square> {
public:
    // derived implements drawImpl (not draw) so base can call it
    void drawImpl() {
        std::cout << "Derived: Drawing a square." << std::endl;
    }
};

int main() {
    ShapeCRTP<Square>* shape = new Square();
    shape->draw();
    delete shape;

    return 0;
}

