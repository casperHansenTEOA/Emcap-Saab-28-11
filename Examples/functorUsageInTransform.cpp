//inclue stl algorith
#include <algorithm>
//inclue stl vector
#include <vector>
//inclue stl iostream
#include <iostream>

using namespace std;
class Dynamic_inc {
    private:
        int increment;

    public:

        Dynamic_inc(int increment):
        increment(increment) {

        }

        void operator()(int& value) {
            value += increment;
        }

        ~Dynamic_inc() {
            cout << "Dynamic_inc destructor" << endl;
        }
};

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    int toAdd = 10;
    transform(v.begin(), v.end(), v.begin(), Dynamic_inc(toAdd));

}