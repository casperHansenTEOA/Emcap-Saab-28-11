class FunctorOP {

    private:
        int constructingValue;

    public:
        FunctorOP(int constructingValue):
        constructingValue(constructingValue) {
    
        }

        void operator()(int otherValue) {
            // some operation between the two values
        }
            
};