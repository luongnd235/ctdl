#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;


string cities[] = {
    "Ha Noi", "Hai Duong", "Hung Yen", "Phu Ly", "Hoa Binh", 
    "Son Tay", "Thai Nguyen", "Bac Ninh", "Bac Giang", "Uong Bi", "Hai Phong"
};
const int V = 11; 

vector<int> adj[V];

void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void BFS(int start) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Thu tu duyet BFS tu dinh Ha noi:\n";

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << cities[u] << " -> ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "END\n";
}

int main() {
    // Them cac canh dua tren so do hinh ve
    addEdge(0, 1);  // Ha Noi - Hai Duong (D1)
    addEdge(1, 2);  // Hai Duong - Hung Yen (D2)
    addEdge(3, 2);  // Phu Ly - Hung Yen (D3)
    addEdge(0, 3);  // Ha Noi - Phu Ly (D4)
    addEdge(0, 4);  // Ha Noi - Hoa Binh (D5)
    addEdge(0, 5);  // Ha Noi - Son Tay (D6)
    addEdge(0, 6);  // Ha Noi - Thai Nguyen (D7)
    addEdge(0, 7);  // Ha Noi - Bac Ninh (D8)
    addEdge(7, 8);  // Bac Ninh - Bac Giang (D9)
    addEdge(8, 9);  // Bac Giang - Uong Bi (D10)
    addEdge(7, 9);  // Bac Ninh - Uong Bi (D11)
    addEdge(9, 10); // Uong Bi - Hai Phong (D12)
    addEdge(1, 10); // Hai Duong - Hai Phong (D13)

    BFS(0);

    return 0;
}
