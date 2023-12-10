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




int main(){

    return 0;
}
