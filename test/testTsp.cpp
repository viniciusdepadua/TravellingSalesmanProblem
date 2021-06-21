#include <gtest/gtest.h>
#include <TspReader.h>
#include <TspSolver.h>

// test fixture: create data and open file before each test
class TspTest : public ::testing::Test {
 protected:
  void SetUp() override {
    
    
  }
  
  
};//class  Setup



void printPercourse(std::vector<int> &v) {
std::cout << std::endl << "[ ";
for (int i : v)
    std::cout << i << " ";
std::cout << " ]" << std::endl;
    
}
  
  
// test if vector is sorted and report errors
::testing::AssertionResult isPermutation(std::vector<int> &v) {
    std::vector<char> aux(v.size()+1,0); // aux has one element more, position aux[0] is always false.
    
    int found_repeated_element = 0;
    int found_value_out_of_range = 0;
    for (int val : v) {
        if ((val < 1) || (val > v.size())) { // val must be in 1,2,3,...,n
            found_value_out_of_range = val;
            break;
        }
        if (aux[val]) { // if value was already present in v before
            found_repeated_element = val;
            break;
        }
        aux[val] = 1;
    }
    if (found_value_out_of_range) {
        std::stringstream ss;
        ss << "vector is NOT a permutation: value out of range " << found_value_out_of_range << std::endl;
        return ::testing::AssertionFailure() << ss.str();
    }//if
    if (found_repeated_element) {
        std::stringstream ss;
        ss << "vector is NOT a permutation: repeated element " << found_repeated_element << std::endl;
        return ::testing::AssertionFailure() << ss.str();
    }//if
    
    int found_missing_value = 0;
    for( int i = 1; i <= v.size() ; i++ ) {
        // all integers between 1 and n MUST be in the vector
        if (!aux[i]) {
            found_missing_value = i;
            break;
        }
    }//for
    if (found_missing_value) {
        std::stringstream ss;
        ss << "vector is NOT a permutation: missing value " << found_missing_value << std::endl;
        return ::testing::AssertionFailure() << ss.str();
    }//if
    
    // if no check failed, we are happy and the vector is a permutation
    return ::testing::AssertionSuccess();
}//IsPermutation

  
typedef TspTest AuxLibTests;
typedef TspTest TspEXACT;

TEST_F(AuxLibTests, ReadTspFile) {
    TspReader tr;
    ASSERT_EQ(tr.read("../data/wi29.tsp"),29); /// check if exacltly 29 cities were read from file
    ASSERT_EQ(tr.getNumCities(),29); /// check if exacltly 29 cities were stored
    
    /*
    ///UNCOMMENT IF YOU WANT TO RUN THE TWO WAYS TO PRINT THE DATA
    tr.printCities(); // print
    
    City c;
    std::cout << "\n\n accessing cities and  printing "; 
    while (tr.getCities(c)) {
        std::cout << c; 
    }
    */
}//ReadTspFile

void testTspFile(std::string filename, int TspSize, long TspCost) {
    TspReader tr;
    ASSERT_EQ(tr.read(filename),TspSize); /// check how many cities were read from file
    ASSERT_EQ(tr.getNumCities(),TspSize); /// check how many cities were stored in tr
    std::vector<int> percourse;
    TspSolver *ts = new TspSolver();
    ts->solve(tr,percourse);   
    //printPercourse(percourse);
    ASSERT_EQ(percourse.size(),TspSize); /// check how many cities are in the TSP solution
    ASSERT_TRUE(isPermutation(percourse));
    long your_perccost = tr.percourseCost(percourse);
    std::cout << "\n FILE: "<<  filename << "   cost: " << your_perccost << "\n"; 
    ASSERT_LE(your_perccost,2*TspCost);
    delete ts;
}//testTspFile

void testTspExact(std::string filename, int TspSize, long TspCost) {
    TspReader tr;
    ASSERT_EQ(tr.read(filename),TspSize); /// check how many cities were read from file
    ASSERT_EQ(tr.getNumCities(),TspSize); /// check how many cities were stored in tr
    std::vector<int> percourse;
    TspSolver *ts = new TspSolver();
    ts->solve(tr,percourse);   
    //printPercourse(percourse);
    ASSERT_EQ(percourse.size(),TspSize); /// check how many cities are in the TSP solution
    ASSERT_TRUE(isPermutation(percourse));
    long your_perccost = tr.percourseCost(percourse);
    std::cout << "\n FILE: "<<  filename << "   cost: " << your_perccost << "\n"; 
    ASSERT_EQ(your_perccost,TspCost);
    delete ts;
}//testTspFile

TEST_F(TspTest, WesternSahara29Tsp) {
    int TspSize = 29; 
    TspReader tr;
    ASSERT_EQ(tr.read("../data/wi29.tsp"),TspSize); /// check how many cities were read from file
    ASSERT_EQ(tr.getNumCities(),TspSize); /// check how many cities were stored in tr
    std::vector<int> percourse;
    TspSolver *ts = new TspSolver();
    ts->solve(tr,percourse);   
    //printPercourse(percourse);
    ASSERT_EQ(percourse.size(),TspSize); /// check how many cities are in the TSP solution
    ASSERT_TRUE(isPermutation(percourse));
    long perccost = tr.percourseCost(percourse);
    //std::cout << "\n\n cost: " << perccost; 
    ASSERT_LE(perccost,2*27603);
    delete ts;
  }//// WesternSaharaTsp 
  
/// convention exactness test  
TEST_F(TspEXACT, Quatar194EXACT) {
    testTspExact("../data/qa194.tsp",194,12181);
}

TEST_F(TspEXACT, Djbuti38EXACT) {
    testTspExact("../data/dj38.tsp",38,8716);
}

TEST_F(TspEXACT, Luxemburg980EXACT) {
    testTspExact("../data/lu980.tsp",980,15343);
}

TEST_F(TspEXACT, Uruguay734EXACT) {
    testTspExact("../data/uy734.tsp",734,108088);
}
TEST_F(TspEXACT, Zimbabue929EXACT) {
    testTspExact("../data/zi929.tsp",929,130442);
}
TEST_F(TspEXACT, CircuitXQF131EXACT) {
    testTspExact("../data/xqf131.tsp",131,742);
}
TEST_F(TspEXACT, CircuitXQG237EXACT) {
    testTspExact("../data/xqg237.tsp",237,1366);
}
TEST_F(TspEXACT, CircuitBCL380EXACT) {
    testTspExact("../data/bcl380.tsp",380,2141);
}
TEST_F(TspEXACT, CircuitXQL662EXACT) {
    testTspExact("../data/xql662.tsp",662,3494);
}

/// corectness test  
TEST_F(TspTest, Quatar194Tsp) {
    testTspFile("../data/qa194.tsp",194,9352);
}

TEST_F(TspTest, Djbuti38Tsp) {
    testTspFile("../data/dj38.tsp",38,6656);
}

TEST_F(TspTest, Luxemburg980Tsp) {
    testTspFile("../data/lu980.tsp",980,11340);
}

TEST_F(TspTest, Uruguay734Tsp) {
    testTspFile("../data/uy734.tsp",734,79114);
}
TEST_F(TspTest, Zimbabue929Tsp) {
    testTspFile("../data/zi929.tsp",929,95345);
}
TEST_F(TspTest, CircuitXQF131Tsp) {
    testTspFile("../data/xqf131.tsp",131,564);
}
TEST_F(TspTest, CircuitXQG237Tsp) {
    testTspFile("../data/xqg237.tsp",237,1019);
}
TEST_F(TspTest, CircuitBCL380Tsp) {
    testTspFile("../data/bcl380.tsp",380,1621);
}
TEST_F(TspTest, CircuitXQL662Tsp) {
    testTspFile("../data/xql662.tsp",662,2513);
}

TEST_F(TspTest, mytest) {
    testTspFile("../data/teste.tsp",8,11);
}
