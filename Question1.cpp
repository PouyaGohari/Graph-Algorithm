#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
class graph{
    public:
    int V;
    vector<vector<int>> adjacency;
    graph(int number_of_nodes, vector<vector<int>> adj);
    pair<vector<vector<int>>, vector<vector<int>>> floyd_warshall();
};

graph :: graph(int number_of_nodes, vector<vector<int>> adj){
    this -> V = number_of_nodes;
    this -> adjacency = adj;
}

pair<vector<vector<int>>, vector<vector<int>>> graph :: floyd_warshall(){
    int n = this->V;
    vector<vector<int>> A(n, vector<int> (n));
    vector<vector<int>> T(n, vector<int> (n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = this->adjacency[i][j];
            if(this->adjacency[i][j] > 0){
                T[i][j] = 1;
            }
            else{
                T[i][j] = 0;
            }
        }
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(A[i][j] > A[i][k] + A[k][j]){
                    A[i][j] = A[i][k] + A[k][j];
                    T[i][j] = T[i][k] + T[k][j];
                }
            }
        }
    }
    return make_pair(A, T);   
}


struct inputs{
    vector<graph*> graphs;
    vector<pair<int, int>> trips;
    vector<int> k_times; 
}typedef inputs;

inputs getting_input(){
    int number_of_nodes;
    int number_of_graphs;
    int number_of_trips;
    cin >> number_of_nodes;
    cin >> number_of_graphs;
    cin >> number_of_trips;
    vector<graph*> my_graphs(number_of_graphs);
    for(int m = 0; m < number_of_graphs; m++){
        vector<vector<int>> adj(number_of_nodes, vector<int> (number_of_nodes));
        for(int i = 0; i < number_of_nodes; i++){
            for(int j = 0; j < number_of_nodes; j++){
                cin >> adj[i][j];
            }
        }
    my_graphs[m] = new graph(number_of_nodes, adj);
    }   
    vector<pair<int, int>> trips(number_of_trips);
    vector<int> k_times(number_of_trips);
    for(int r = 0; r < number_of_trips; r++){
        cin >> trips[r].first;
        cin >> trips[r].second;
        cin >> k_times[r];
    }
    return {my_graphs, trips, k_times};
} 

int main(){
    inputs my_inputs = getting_input();
    return 0;
}
