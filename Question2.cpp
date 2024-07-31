#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct edges{
    long long start_node;
    long long end_node;
    long long maximum;
    long long minimum;
}typedef edges;

class Tree{
    public:
    long long V;
    long long total;
    vector<long long> a;
    vector<edges> my_edges;
    vector<long long> parent;
    vector<long long> height;
    vector<long long> number_of_nodes_in_sets;
    Tree(long long nodes, vector<long long> a, vector<edges> ed);
    void find_max_path();
    void find_min_path();
    private:
    int DSU_find(long long u);
    void DSU_unoion(long long a, long long b, long long weight);
};

Tree :: Tree(long long nodes, vector<long long> a, vector<edges> ed){
    this -> total = 0;
    this -> V = nodes;
    this -> a = a;
    this -> my_edges = ed;
    this -> parent.assign(V, 0);
    this -> number_of_nodes_in_sets.assign(V, 1);
    this -> height.assign(V, 0);
    for(long long i = 0; i < V; i++){
        this -> parent[i]=i;
    }
    sort(my_edges.begin(), my_edges.end(), [](edges e1, edges e2){
        return e1.maximum < e2.maximum;
    });
    this -> find_max_path();
    long long maximum_path = total;
    sort(my_edges.begin(), my_edges.end(), [](edges e1, edges e2){
        return e1.minimum > e2.minimum;
    });
    this -> total = 0;
    for(long long i = 0; i < V; i++){
        this -> parent[i]=i;
        this -> number_of_nodes_in_sets[i] = 1;
        this -> height[i] = 0;
    }
    this -> find_min_path();
    long long minimum_path = total;
    cout << maximum_path - minimum_path << endl;
}

int Tree ::  DSU_find(long long u){
    while(u != parent[u]){
        u = parent[u];
    }
    return u;
}

void Tree :: DSU_unoion(long long a, long long b, long long weight){
    total += number_of_nodes_in_sets[a]*number_of_nodes_in_sets[b]*weight;
    number_of_nodes_in_sets[a] += number_of_nodes_in_sets[b];
    parent[b] = parent[a];
    // if(height[a] > height[b]){
    //     parent[b] = a;
    //     number_of_nodes_in_sets[a] += number_of_nodes_in_sets[b];
    // }
    // else if(height[a] < height[b]){
    //     parent[a] = b;
    //     height[a] = height[b] + 1;
    //     number_of_nodes_in_sets[b] += number_of_nodes_in_sets[a];
    // }
    // else{
    //     parent[a] = b;
    //     number_of_nodes_in_sets[b] += number_of_nodes_in_sets[a];
    // }
    /*
    this commented was supposed to be faster because it would help our algorithm to be faster and find would be in o(logn) but
    I dont know why the above is faster and it can be larger than o(nlogn) and it maybe be O(n^2)
    it should be cuase to sorted edges and random selection between them.
    */
}

void Tree :: find_min_path(){
    int r1, r2;
    for(auto edge : this -> my_edges){
        r1 = DSU_find(edge.start_node);
        r2 = DSU_find(edge.end_node);
        if(r1 != r2){
            DSU_unoion(r1, r2, edge.minimum);
        }
    }
}

void Tree :: find_max_path(){
    int r1, r2;
    for(auto edge : this -> my_edges){
        r1 = DSU_find(edge.start_node);
        r2 = DSU_find(edge.end_node);
        if(r1 != r2){
            DSU_unoion(r1, r2, edge.maximum);
        }
    }
}

Tree* getting_input(){
    long long nodes;
    cin >> nodes;
    vector<long long> a(nodes, 0);
    for(long long i = 0; i < nodes; i++){
        cin >> a[i];
    }
    vector<edges> my_edges(nodes-1);
    long long x, y; 
    for(long long i = 0; i < nodes-1; i++){
        cin >> x >> y;
        my_edges[i].start_node = x - 1;
        my_edges[i].end_node = y -1;
        my_edges[i].maximum = max(a[my_edges[i].start_node], a[my_edges[i].end_node]);
        my_edges[i].minimum = min(a[my_edges[i].start_node], a[my_edges[i].end_node]);
    }
    Tree* my_tree = new Tree(nodes, a, my_edges);
    return my_tree;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    Tree* my_tree = getting_input();
    delete my_tree;
    return 0;
}