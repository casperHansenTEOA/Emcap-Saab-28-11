#ifndef LOCATION
#define LOCATION
// no reason for this to be a class, should be a struct
class Location {
public:
    double x; ///< The x-coordinate of the location.
    double y; ///< The y-coordinate of the location.
    /**
     * @brief Adds two locations together.
     * 
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The sum of the two locations.
     */
    Location * add(const Location& loc1, const Location& loc2){
        // this is a bad idea might cause memory leak if overwriting locations
        return new Location (loc1.x + loc2.x, loc1.y + loc2.y);
    };

    Location(double x, double y) : x(x), y(y) {}

   


};

#endif // LOCATION