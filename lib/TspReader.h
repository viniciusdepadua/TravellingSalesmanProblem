#ifndef TSP_READER
#define TSP_READER


#include <fstream> // reading files
#include <sstream>
#include <string>
#include <cctype> // isdigit
#include <vector>
#include <cmath> // round
#include <iostream> // cout

class City {
public:
    City() : x(0),y(0),id(0) { };
    City(int x_, float y_, float id_) : x(x_),y(y_),id(id_) { };
    
    
    int disti(City &c) {
        return (int)round( dist(c) );
    }
    
    float dist(City &c) {
        return ( sqrt( (x-c.x)*(x-c.x) + (y-c.y)*(y-c.y) ) );
    }
    
    float getx() const { return x; }
    float gety() const { return y; }
    int getId() const { return id; }
    
    void copy(City &c) {
        x = c.getx();
        y = c.gety();
        id = c.getId();
    }
  
private:
    
float x;
float y;
int id;



};


std::ostream& operator<<(std::ostream& stream, const City& c);


class TspReader {
public:
    
    TspReader() : city_count(0), filename("undefined") { };
    
    TspReader(std::string fname): city_count(0)  { read(fname); };
    
void printCities() ;

bool getCities(City &c);
void copyCitiesVector(std::vector<City> &vc);

int add(float x, float y, int id);

int add(std::string line) ;

int read(std::string filename_) ;

int getNumCities() { return cities.size(); }

long percourseCost(std::vector<int> &p);
    
private:
    std::vector<City> cities;
    std::string filename;
    
    int city_count; // used to mark the last city output.
}; //class


#endif
