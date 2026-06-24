#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// So luong tinh thanh (11 tinh)
const int V = 11;

// Mang luu ten cac tinh thanh khong dau de hien thi truc quan
string cities[] = {
    "Ha noi", "Hai duong", "Hung yen", "Phu ly", "Hoa binh", 
    "Son tay", "Thai nguyen", "Bac ninh", "Bac giang", "Uong bi", "Hai phong"
};

// Do thi luu duoi dang danh sach ke
vector<int> adj[V];

// Ham them tuyen duong giua 2 tinh thanh
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // Do thi vo huong
}

// Ham tim va in duong di ngan nhat tu tinh Start den tinh End su dung BFS
void findShortestPathBFS(int start, int end) {
    vector<bool> visited(V, false);
    vector<int> parent(V, -1); // Mang luu vet duong di
    queue<int> q;

    // Khoi tao dinh xuat phat
    visited[start] = true;
    q.push(start);

    // Tien hanh duyet BFS
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == end) break; // Da tim thay dich, dung vong lap

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u; // Luu vet: de den duoc v thi phai di qua u
                q.push(v);
            }
        }
    }

    // Kiem tra xem co duong di toi dich khong
    if (!visited[end]) {
        cout << "Khong co duong di tu " << cities[start] << " den " << cities[end] << endl;
        return;
    }

    // Truy vet nguoc tu dich ve nguon
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end()); // Dao nguoc mang de co thu tu xuoi

    // In lo trinh ngan nhat ra man hinh
    cout << "=> LO TRINH NGAN NHAT (qua it tinh nhat): ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << cities[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n(Tong so chang: " << path.size() - 1 << " tuyen duong)\n";
}

int main() {
    // Thiet lap mang luoi giao thong dua tren so do do thi
    addEdge(0, 1);  // Ha noi - Hai duong (D1)
    addEdge(1, 2);  // Hai duong - Hung yen (D2)
    addEdge(3, 2);  // Phu ly - Hung yen (D3)
    addEdge(0, 3);  // Ha noi - Phu ly (D4)
    addEdge(0, 4);  // Ha noi - Hoa binh (D5)
    addEdge(0, 5);  // Ha noi - Son tay (D6)
    addEdge(0, 6);  // Ha noi - Thai nguyen (D7)
    addEdge(0, 7);  // Ha noi - Bac ninh (D8)
    addEdge(7, 8);  // Bac ninh - Bac giang (D9)
    addEdge(8, 9);  // Bac giang - Uong bi (D10)
    addEdge(7, 9);  // Bac ninh - Uong bi (D11)
    addEdge(9, 10); // Uong bi - Hai phong (D12)
    addEdge(1, 10); // Hai duong - Hai phong (D13)

    cout << "--- HE THONG TIM DUONG DI GIAO THONG ---" << endl;
    
    // Thu nghiem 1: Tim duong di tu Hoa binh (dinh 4) toi Hai phong (dinh 10)
    cout << "\n[Test 1] Tim duong tu Hoa binh den Hai phong:\n";
    findShortestPathBFS(4, 10);

    // Thu nghiem 2: Tim duong di tu Thai nguyen (dinh 6) toi Hung yen (dinh 2)
    cout << "\n[Test 2] Tim duong tu Thai nguyen den Hung yen:\n";
    findShortestPathBFS(6, 2);

    return 0;
}
