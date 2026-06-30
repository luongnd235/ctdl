#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int V = 11;
const int INF = 1e9;

// Ten cac tinh thanh tuong ung voi chi so 0 den 10
string cities[] = {
    "Ha noi", "Hai duong", "Hung yen", "Phu ly", "Hoa binh", 
    "Son tay", "Thai nguyen", "Bac ninh", "Bac giang", "Uong bi", "Hai phong"
};

// Ma tran trong so goc cua do thi giao thong (i = Di)
int graph[V][V];

// Cau truc de phuc vu cho thuat toan Kruskal
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Cac ham khoi tao va thiet lap do thi
void initGraph() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void addEdge(int u, int v, int w) {
    graph[u][v] = w;
    graph[v][u] = w;
}

// Ham hien thi Ma tran dinh ke cua Cay khung
void printMSTMatrix(int mstEdges[V][V]) {
    cout << "\nMA TRAN DINH KE CUA CAY KHUNG NHO NHAT:\n\n";
    cout << "\t";
    for (int i = 0; i < V; i++) cout << i << "\t";
    cout << "\n-----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < V; i++) {
        cout << cities[i] << " (" << i << ")\t| ";
        for (int j = 0; j < V; j++) {
            if (mstEdges[i][j] == INF) cout << "INF\t";
            else cout << mstEdges[i][j] << "\t";
        }
        cout << "\n";
    }
}

// 1. THUAT TOAN DIJKSTRA (Tim duong tu Hoa Binh den Uong Bi)
void dijkstra(int start, int end) {
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min_dist = INF;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1 || u == end) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF && graph[u][v] != 0) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // In lo trinh nguoc tu uong bi ve hoa binh
    cout << "--- KET QUA DIJKSTRA FROM " << cities[start] << " TO " << cities[end] << " ---\n";
    cout << "Do dai duong di ngan nhat: " << dist[end] << "\n";
    cout << "Lo trinh di: ";
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        cout << cities[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n\n";
}

// 2. THUAT TOAN PRIM (Bat dau tu Hoa Binh)
void primMST(int start) {
    int mstMatrix[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) mstMatrix[i][j] = (i == j) ? 0 : INF;

    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    key[start] = 0;

    for (int count = 0; count < V; count++) {
        int u = -1, min_key = INF;
        for (int i = 0; i < V; i++) {
            if (!inMST[i] && key[i] < min_key) {
                min_key = key[i];
                u = i;
            }
        }

        if (u == -1) break;
        inMST[u] = true;

        if (parent[u] != -1) {
            mstMatrix[parent[u]][u] = graph[parent[u]][u];
            mstMatrix[u][parent[u]] = graph[parent[u]][u];
        }

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "--- KET QUA CAY KHUNG PRIM (BAT DAU TU " << cities[start] << ") ---";
    printMSTMatrix(mstMatrix);
    cout << "\n";
}

// 3. THUAT TOAN KRUSKAL
int findParent(int i, vector<int>& parentArr) {
    if (parentArr[i] == -1) return i;
    return findParent(parentArr[i], parentArr);
}

void unionSets(int u, int v, vector<int>& parentArr) {
    int root_u = findParent(u, parentArr);
    int root_v = findParent(v, parentArr);
    if (root_u != root_v) {
        parentArr[root_u] = root_v;
    }
}

void kruskalMST() {
    int mstMatrix[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) mstMatrix[i][j] = (i == j) ? 0 : INF;

    vector<Edge> edges;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != INF && graph[i][j] != 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parentArr(V, -1);
    int edgeCount = 0;

    for (const auto& edge : edges) {
        int root_u = findParent(edge.u, parentArr);
        int root_v = findParent(edge.v, parentArr);

        if (root_u != root_v) {
            mstMatrix[edge.u][edge.v] = edge.weight;
            mstMatrix[edge.v][edge.u] = edge.weight;
            unionSets(root_u, root_v, parentArr);
            edgeCount++;
            if (edgeCount == V - 1) break;
        }
    }

    cout << "--- KET QUA CAY KHUNG KRUSKAL ---";
    printMSTMatrix(mstMatrix);
}

int main() {
    initGraph();

    // Map dinh dung ten goc: 
    // HN=0, HD=1, HY=2, PL=3, HB=4, ST=5, TN=6, BN=7, BG=8, UB=9, HP=10
    addEdge(0, 1, 1);   // Ha noi - Hai duong (D1)
    addEdge(1, 2, 2);   // Hai duong - Hung yen (D2)
    addEdge(3, 2, 3);   // Phu ly - Hung yen (D3)
    addEdge(0, 3, 4);   // Ha noi - Phu ly (D4)
    addEdge(0, 4, 5);   // Ha noi - Hoa binh (D5)
    addEdge(0, 5, 6);   // Ha noi - Son tay (D6)
    addEdge(0, 6, 7);   // Ha noi - Thai nguyen (D7)
    addEdge(0, 7, 8);   // Ha noi - Bac ninh (D8)
    addEdge(7, 8, 9);   // Bac ninh - Bac giang (D9)
    addEdge(8, 9, 10);  // Bac giang - Uong bi (D10)
    addEdge(7, 9, 11);  // Bac ninh - Uong bi (D11)
    addEdge(9, 10, 12); // Uong bi - Hai phong (D12)
    addEdge(1, 10, 13); // Hai duong - Hai phong (D13)

    // 1. Chay Dijkstra tu Hoa Binh (4) den Uong Bi (9)
    dijkstra(4, 9);

    cout << "=========================================================================================\n\n";

    // 2. Chay va in ma tran Cay khung PRIM bat dau tu Hoa Binh (4)
    primMST(4);

    cout << "=========================================================================================\n\n";

    // 3. Chay va in ma tran Cay khung KRUSKAL
    kruskalMST();

    return 0;
}
