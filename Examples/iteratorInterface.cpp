

#include <vector>

// Forward-declare SkipList and its nested types so SkipList::Iterator can be defined out-of-line.
class SkipList : public std::vector<int> {
    public: 
        class Iterator{
            public:
                Iterator(int* ptr) : current(ptr) {}
    
                int operator*() const {
                    return *current;
                }
    
                Iterator& operator++() {
                    ++current;
                    return *this;
                }
    
                bool operator!=(const Iterator& other) const {
                    return current != other.current;
                }
    
            private:
                int* current;
        };
};
