// a good example of RAII using a dynamic array

#include <iostream>
#include <memory>

class GoodRaii {
    private:
        int size;
        int* data;

    public:
        GoodRaii(int size) : 
        size(size),
        data(new int[size]) { //<-- här allokeras minnet
            try {
                for (int i = 0; i < size; i++) {
                    data[i] = i;
                }
            } catch (...) { //<-- om det blir fel så ska minnet deallokeras
                delete[] data;
                throw;
            } 
        }

        ~GoodRaii() {
            delete[] data; //<-- här dealokeras minnet vid destruction
        }

        void print() {
            for (int i = 0; i < size; i++) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
};