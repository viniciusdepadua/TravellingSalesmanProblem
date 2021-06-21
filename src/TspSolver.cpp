#include <TspSolver.h>
// used my own tuple structure for the problem. Thought it was gonna be easier using the overloaded operator.
struct my_tuple{
    int distance;
    int parent_id;
    int id;
    my_tuple(int n1, int n2, int n3) : distance(n1), parent_id(n2), id(n3)
    {
    }
    // operator so that stl's priority_queue can compare correctly
    bool operator<(const struct my_tuple& other) const
    {
        if(distance == other.distance && parent_id == other.parent_id){
            return id > other.id;
        }
        else if(distance == other.distance){
            return parent_id > other.parent_id;
        }
        return distance > other.distance;
    } // priority used as the convention says
};

void TspSolver::get_percourse(std::vector<int> *MST, std::vector<int> &percourse, int v, int &index) {
    percourse[index++] = v+1;
    for(int & i : MST[v])
        get_percourse(MST, percourse, i, index);
} //pre_order percourse

void TspSolver::solve(TspReader &tr,std::vector<int> &percourse) {

    int numCities = tr.getNumCities();
    std::vector<City> cities;
    tr.copyCitiesVector(cities);
    std::vector<int> graph[numCities];
    std::priority_queue<my_tuple> distances;
    percourse.resize(numCities);

    // initializing min heap and graph
    for (int i = 0; i < numCities; i++) {
        graph[i].resize(numCities);
        for (int j = 0; j < numCities; j++){
            graph[i][j] = cities[i].disti(cities[j]);
            if(!i)
                if(j)
                    distances.push(my_tuple(graph[i][j], i, j));
        }
    }

    std::vector<bool> marked (numCities, false);
    std::vector<int> MST[numCities];
    marked[0] = true;

    // Prim
    for(int i  = 1; i < numCities; i++){
        int v = distances.top().id;
        int p = distances.top().parent_id;
        while(marked[v]) {
            distances.pop();
            v = distances.top().id;
            p = distances.top().parent_id;
        }
        marked[v] = true;
        // representing MST with adjacency list
        MST[p].push_back(v);
        distances.pop();
        // add distances to v on the distances heap
        for(int j = 0; j < numCities; j++)
            if(!marked[j])
                distances.push(my_tuple(graph[v][j], v, j));
    }
    int index = 0;
    get_percourse(MST, percourse, 0, index);

}//solve