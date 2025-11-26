#include <iostream>

template<typename Derived>
struct EvaluatorBase {
    void evaluate_safely() {
        if (auto* derived = static_cast<Derived*>(this)) {
            derived->evaluate();
        } else {
            std::cerr << "Error: Unable to cast to derived class.\n";
        }
    }
};

class MyEvaluator : public EvaluatorBase<MyEvaluator> {
public:
    void evaluate() { 
        std::cout << "Evaluating...\n"; 
    }
};