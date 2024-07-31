#include <iostream>
#include <vector>
#include <climits>

using namespace std;
class super_graph{
    public:
    int V;
    int M;
    vector<vector<int>> init_dp;
    super_graph(int nodes, int graphs, vector<vector<int>> dp_zero);
    vector<vector<vector<int>>> floyd_warshall();
};

super_graph :: super_graph(int nodes, int graphs, vector<vector<int>> dp_zero){
    this -> V = nodes;
    this -> M = graphs;
    this -> init_dp = dp_zero;
}

vector<vector<vector<int>>>  super_graph :: floyd_warshall(){
    vector<vector<vector<int>>> dp(1001, vector<vector<int>>(V, vector<int> (V, INT_MAX)));
    dp[0] = this->init_dp;
    for(int cond = 1; cond <= 1000; cond++){
        for(int k = 0; k < V; k++){
            for(int i = 0; i < V; i++){
                for(int j = 0; j < V; j++){
                    dp[cond][i][j] = min(dp[cond][i][j], dp[0][i][k] + dp[cond-1][k][j]);
                }
            }
        }
    }
    return dp;
}

int main(){
    int nodes;
    int graphs;
    int trips;
    cin >> nodes;
    cin >> graphs;
    cin >> trips;
    vector<vector<int>> adj(nodes, vector<int>(nodes));
    vector<int> originis(trips);
    vector<int> dests(trips);
    vector<int> conditions(trips);
    vector<vector<int>> dp_zero(nodes, vector<int> (nodes, INT_MAX));
    for(int m = 0; m < graphs; m++){
        for(int i = 0; i < nodes; i++){
            for(int j = 0; j < nodes; j++){
                cin >> adj[i][j];
            }
        }
        for(int k = 0; k < nodes; k++){
            for(int i = 0; i < nodes; i++){
                for(int j = 0; j < nodes; j++){
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
                    dp_zero[i][j] = min(dp_zero[i][j], adj[i][j]);
                }
            }
        }
    }
    super_graph* my_graph = new super_graph(nodes, graphs, dp_zero);
    vector<vector<vector<int>>> x = my_graph->floyd_warshall();
    for(int r = 0; r < trips; r++){
        cin >> originis[r]>> dests[r]>> conditions[r];
    }
    for(int r = 0; r < trips; r++){
        cout << x[conditions[r]][originis[r]-1][dests[r]-1] << endl;
    }
    delete my_graph;
    return 0;
}