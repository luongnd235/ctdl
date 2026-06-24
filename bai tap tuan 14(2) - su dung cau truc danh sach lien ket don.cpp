#include <iostream>
#include <queue>
#include <string>

using namespace std;

string cities[] = {
    "Ha Noi", "Hai Duong", "Hung Yen", "Phu Ly", "Hoa Binh", 
    "Son Tay", "Thai Nguyen", "Bac Ninh", "Bac Giang", "Uong Bi", "Hai Phong"
};
const int V = 11;

struct Node {
    int dest;
    Node* next;
};

struct AdjList {
    Node* head;
};

struct Graph {
    AdjList array[V];
};

Node* createNode(int dest) {
    Node* newNode = new Node;
    newNode->dest = dest;
    newNode->next = nullptr;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {

    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void BFS(Graph* graph, int start) {
    bool visited[V] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Thu tu duyet BFS tu dinh Ha noi (Dùng Danh sach lien ket):\n";

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << cities[u] << " -> ";


        Node* temp = graph->array[u].head;
        while (temp != nullptr) {
            int v = temp->dest;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
            temp = temp->next;
        }
    }
    cout << "END\n";
}

int main() {
    Graph* graph = new Graph;
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = nullptr;
    }

    // Noi cac tuyen duong giao thong
    addEdge(graph, 0, 1);  // Ha Noi - Hai Duong
    addEdge(graph, 1, 2);  // Hai Duong - Hung Yen
    addEdge(graph, 3, 2);  // Phu Ly - Hung Yen
    addEdge(graph, 0, 3);  // Ha Noi - Phu Ly
    addEdge(graph, 0, 4);  // Ha Noi - Hoa Binh
    addEdge(graph, 0, 5);  // Ha Noi - Son Tay
    addEdge(graph, 0, 6);  // Ha Noi - Thai Nguyen
    addEdge(graph, 0, 7);  // Ha Noi - Bac Ninh
    addEdge(graph, 7, 8);  // Bac Ninh - Bac Giang
    addEdge(graph, 8, 9);  // Bac Giang - Uong Bi
    addEdge(graph, 7, 9);  // Bac Ninh - Uong Bi
    addEdge(graph, 9, 10); // Uong Bi - Hai Phong
    addEdge(graph, 1, 10); // Hai Duong - Hai Phong

    BFS(graph, 0);

    for (int i = 0; i < V; ++i) {
        Node* current = graph->array[i].head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete graph;

    return 0;
}
