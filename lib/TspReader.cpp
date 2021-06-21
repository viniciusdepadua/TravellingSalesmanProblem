#include <TspReader.h>


void TspReader::printCities() {
    std::cout << " TSP file: " << filename << std::endl;
    for (City c : cities) {
        std::cout << c;
    }
}

 /*
  * usage
  * while(myreader.getCities(c)) 
  *     do something with c
  */
bool TspReader::getCities(City &c) {
    bool notfinished = true;
    if (city_count < cities.size() ) {
        c.copy(cities[city_count]);
        city_count++;
    } else {
        city_count = 0;
        notfinished = false;
    }//if
    
    return notfinished;
}

// you can copy the whole vector.
void TspReader::copyCitiesVector(std::vector<City> &vc) {
    vc = cities;//copy assignment
}


// add a new city given its data
int TspReader::add(float x, float y, int id) {
    City c(x,y,id);
    
    cities.push_back(c);
    return cities.size();
}

// add a text line
int TspReader::add(std::string line) {
    std::istringstream ss(line);
    int id; float x; float y;
    
    if (ss >> id >> x >> y)  {
    
        add(x,y,cities.size()+1); // ignore the id from the file, use sequential numbers
        return cities.size();
    } else {
        return 0;
    }
}

// read archive line by line
int TspReader::read(std::string filename_) {
    filename = filename_;//copy to atribute
    std::ifstream infile(filename);
    
    int readlines = 0;
    std::string line;
    while (std::getline(infile, line)) {
        if (isdigit(line[0])) {//ignore lines with no digit as 1st char
            add(line);
            readlines++;
        }//if
    }//while
    infile.close();
    return readlines;
}

// allows the student to check percourse length, the same code is used in tests.
long TspReader::percourseCost(std::vector<int> &p)  {
    long dist = 0;
    int last_city = 0;
    int first_city = 0;
    for (int i : p) 
        if (!last_city) { first_city = last_city = i; }
        else {
            //std::cout << "\n { "<<i<<" "<<last_city<<" } " << cities[i-1].disti(cities[last_city-1]) << " +" << dist;
            // -1 in dists: we know that the city with id x is in position x-1
            dist += cities[i-1].disti(cities[last_city-1]);
            last_city = i;
        }
    //std::cout << "\n { "<<first_city<<" "<<last_city<<" } " << cities[first_city-1].disti(cities[last_city-1]) << " +" << dist;
    dist += cities[first_city-1].disti(cities[last_city-1]);
    return dist;
}// percourseCost


// operator to << print for City objects
std::ostream& operator<<(std::ostream& stream, const City& c) {
    stream << c.getId()  << " [ " << c.getx() << ", " << c.gety() << " ]" << std::endl;
    return stream;
 }

