#ifndef TSP_SOLVER
#define TSP_SOLVER


#include <TspReader.h>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

class TspSolver {
public:
    // you should fill percourse with a permutation that represents the TSP solution

    void solve(TspReader &tr,std::vector<int> &percourse);

private:
    void get_percourse(std::vector<int> MST[], std::vector<int> &percourse, int v, int &index);

}; 

#endif
