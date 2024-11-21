


#include <iostream>
#include <stdexcept>

void throwError() {
    throw std::runtime_error("An error has occurred!");
}

void catchError() {
    try {
        throwError();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an error: " << e.what() << std::endl;
    }
}

int main() {
    catchError();
    return 0;
}




