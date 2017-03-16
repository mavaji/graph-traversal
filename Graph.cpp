/**
 * author: Vahid Mavaji
 * year: 2001
 */

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

template<class T>
class ListNode {
public:
    template<class U> friend
    class List;

    template<class U> friend
    class Graph;

    ListNode() {
        data = 0;
        next = 0;
    }

private:
    T data;
    ListNode *next;
};

template<class T>
class List {
public:
    template<class U> friend
    class Graph;

    List() { head = 0; }

    void add(const T newData);

    ListNode<T> *getHead() { return head; }

private:
    ListNode<T> *head;
};

template<class T>
void List<T>::add(const T newData) {
    ListNode<T> *p, *newNode;

    newNode = new ListNode<T>;
    newNode->data = newData;
    newNode->next = 0;
    if (head == 0) {
        head = newNode;
        head->next = 0;
        return;
    }

    p = head;
    while (p->next != 0) p = p->next;
    p->next = newNode;

}

template<class T>
class Graph {
public:
    Graph(const int vertices = 0) : n(vertices) { headNodes = new List<T>[n]; }

    void makeAdjacencyList();

    void traversal(int index);

    void shortestPath(int index);

    void dfs(const int startVertex);

    void dfsInternal(const int v);

    void bfs();

private:
    List<T> *headNodes;
    int *visited;
    int n;
    int *unDiMatrix, **diMatrix;
};

template<class T>
void Graph<T>::makeAdjacencyList() {
    int count = 0;
    FILE *fp;

    fp = fopen("matrix.txt", "rt");

    if (fp == 0) {
        std::cout << "Can't open file";
        exit(1);
    }

    rewind(fp);
    char c = 0;
    while (c != 10 /*'\n'*/) {
        c = (char) fgetc(fp);
        count++;
    }

    count = (count + 1) / 2;
    unDiMatrix = (int *) malloc(count * count * sizeof(int));

    rewind(fp);
    char ch;
    char *s;
    s[0] = '\0';
    int len, i, j, num;
    for (i = 0; i < count; i++)
        for (j = 0; j < 2 * count; j++) {
            ch = (char) fgetc(fp);

            if (ch == ' ') {
                num = atoi(s);
                *(unDiMatrix + count * i + (j - 1) / 2) = num;
                s[0] = 0;
            } else if (ch == '\n' || feof(fp)) {
                num = atoi(s);
                *(unDiMatrix + count * i + (count - 1)) = num;
                s[0] = 0;
            } else {
                len = (int) strlen(s);
                s[len] = ch;
                s[len + 1] = 0;
            }
        }

    std::cout << "Adjacency Matrix:" << std::endl;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++)
            std::cout << (*(unDiMatrix + i * count + j)) << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    headNodes = new List<int>[count];
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++)
            if (*(unDiMatrix + i * count + j)) headNodes[i].add(j);
    }

    fclose(fp);

    std::cout << "Adjacency List:" << std::endl;
    for (i = 0; i < count; i++) {
        ListNode<T> *p = headNodes[i].head;
        std::cout << "[" << i << "]";
        while (p != 0) {
            std::cout << " -> " << p->data;
            p = p->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    n = count;
}

template<class Type>
void Graph<Type>::dfs(const int startVertex) {
    visited = new int[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    std::cout << std::endl << "HEAD";

    dfsInternal(startVertex);

    delete[] visited;
}

template<class Type>
void Graph<Type>::dfsInternal(const int v) {
    visited[v] = 1;
    std::cout << " -> " << v;
    ListNode<Type> *p;
    p = headNodes[v].getHead();
    while (p) {
        if (!visited[p->data]) dfsInternal(p->data);
        p = p->next;
    }
}

template<class Type>
void Graph<Type>::bfs() {
}

template<class Type>
void Graph<Type>::traversal(int index) {
}

template<class Type>
void Graph<Type>::shortestPath(int index) {
}

int main() {
    Graph<int> graph;

    graph.makeAdjacencyList();

    int startVertex;
    std::cout << "Enter Start Vertex for DFS: ";
    std::cin >> startVertex;

    graph.dfs(startVertex);

    std::cout << std::endl;

    return 0;
}