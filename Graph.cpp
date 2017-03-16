/**
 * author: Vahid Mavaji
 * year: 2001
 */

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

enum Boolean {
    FALSE, TRUE
};

template<class Type>
class ListNode {
public:
    template<class U> friend
    class List;

    template<class U> friend
    class Graph;

    ListNode() {
        Data = 0;
        Link = 0;
    }

private:
    Type Data;
    ListNode *Link;
};

template<class Type>
class List {
public:
    template<class U> friend
    class Graph;

    List() { Head = 0; }

    void Add(const Type NewData);

    ListNode<Type> *GetHead() { return Head; }

private:
    ListNode<Type> *Head;
};

template<class Type>
void List<Type>::Add(const Type NewData) {
    ListNode<Type> *p1, *NewNode;

    NewNode = new ListNode<Type>;
    NewNode->Data = NewData;
    NewNode->Link = 0;
    if (Head == 0) {
        Head = NewNode;
        Head->Link = 0;
        return;
    }

    p1 = Head;
    while (p1->Link != 0) p1 = p1->Link;
    p1->Link = NewNode;

}

template<class Type>
class Graph {
public:
    Graph(const int vertices = 0) : n(vertices) { HeadNodes = new List<Type>[n]; }

    void MakeAdjacencyList();

    void Traversal(int index);

    void ShortestPath(int index);

    void DFS(const int startVertex);

    void DFSInternal(const int v);

    void BFS();

private:
    List<Type> *HeadNodes;
    Boolean *visited;
    int n;
    int *UnDiMatrix, **DiMatrix;
};

template<class Type>
void Graph<Type>::MakeAdjacencyList() {
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
    UnDiMatrix = (int *) malloc(count * count * sizeof(int));

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
                *(UnDiMatrix + count * i + (j - 1) / 2) = num;
                s[0] = 0;
            } else if (ch == '\n' || feof(fp)) {
                num = atoi(s);
                *(UnDiMatrix + count * i + (count - 1)) = num;
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
            std::cout << (*(UnDiMatrix + i * count + j)) << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    HeadNodes = new List<int>[count];
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++)
            if (*(UnDiMatrix + i * count + j)) HeadNodes[i].Add(j);
    }

    fclose(fp);

    std::cout << "Adjacency List:" << std::endl;
    for (i = 0; i < count; i++) {
        ListNode<Type> *p = HeadNodes[i].Head;
        std::cout << "[" << i << "]";
        while (p != 0) {
            std::cout << " -> " << p->Data;
            p = p->Link;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    n = count;
}

template<class Type>
void Graph<Type>::DFS(const int startVertex) {
    visited = new Boolean[n];
    for (int i = 0; i < n; i++) visited[i] = FALSE;

    std::cout << std::endl << "HEAD";

    DFSInternal(startVertex);

    delete[] visited;
}

template<class Type>
void Graph<Type>::DFSInternal(const int v) {
    visited[v] = TRUE;
    std::cout << " -> " << v;
    ListNode<Type> *p;
    p = HeadNodes[v].GetHead();
    while (p) {
        if (!visited[p->Data]) DFSInternal(p->Data);
        p = p->Link;
    }
}

template<class Type>
void Graph<Type>::BFS() {
}

template<class Type>
void Graph<Type>::Traversal(int index) {
}

template<class Type>
void Graph<Type>::ShortestPath(int index) {
}

int main() {
    Graph<int> Obj;

    Obj.MakeAdjacencyList();

    int startVertex;
    std::cout << "Enter Start Vertex for DFS: ";
    std::cin >> startVertex;

    Obj.DFS(startVertex);

    std::cout << std::endl;

    return 0;
}