#include <type_traits>
#include <utility>
#include <iostream>

// CRTP-bas som gör compile-time kontroller av Derived::evaluate() -> double
template <typename Derived>
struct EvaluateCRTP
{
    // Kontrollera att Derived har evaluate() som returnerar exakt double

    double call_evaluate()
    {
        static_assert(std::is_same<decltype(std::declval<Derived>().evaluate()), double>::value,
                      "Derived must implement evaluate() returning double");
        return static_cast<Derived &>(*this).evaluate();
    }
};

// Exempelklass som använder CRTP
class Good : public EvaluateCRTP<Good>
{
    public:
        double evaluate()
        {
            return 42.0;
        }
};

class Bad : public EvaluateCRTP<Bad>
{
public:
    int evaluate() // fel returtyp -> kommer ge compile-time fel med vårt static_assert
    {
        return 0;
    }
};

int main()
{
    Good g;
    std::cout << "Good.evaluate() -> " << g.call_evaluate() << "\n";
    Bad b;
    std::cout << "Bad.evaluate() -> " << b.call_evaluate() << "\n";
    return 0;
}
