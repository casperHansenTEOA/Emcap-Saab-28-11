
#include <iostream>
template<typename T, int value> class MyTemplateClass {
    private:
        T data;
    public:
        MyTemplateClass(T data) {
            this->data = data;  
        }
        void display() {
            std::cout << "Template parameter value: " << value << std::endl;
            std::cout << "Data: " << data << std::endl;
        }
};


int main() {
    MyTemplateClass<int, 42> myObject = MyTemplateClass<int, 42>(100);
    myObject.display();
    return 0;
}

