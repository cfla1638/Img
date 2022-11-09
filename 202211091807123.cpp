#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

void InitializeGraph(Graph &G)
{
    G.volume = 0;
    G.vertexNum = 0;
    for (int i = 0; i < MAX; i++)
    {
        G.adjacentTable[i].edgeList = nullptr;
        G.adjacentTable[i].elem = defaultVal;
        G.adjacentTable[i].existFlag = true;
    }
}

void AddVertex(Graph &G, ElementType elem)
{
    if (FindVertex(G, elem) != NotAVertex)
    {
        cout << "Element Value conflict!" << endl;
        return ;
    }
    //�����������������������
    if (G.vertexNum >= MAX)
    {
        cout << "Out of Space!" << endl;
        return ;
    }
    //�����ʹ�õĽ����������������������ڽӱ�������ǰɾ���Ľ��
    if (G.volume >= MAX && G.vertexNum < MAX)
    {
        Vertex v;
        for (int i = 0; i < G.volume; i++)
            if (!G.adjacentTable[i].existFlag)
                v = i;
        G.adjacentTable[v].elem = elem;
        G.adjacentTable[v].existFlag = true;
        G.adjacentTable[v].edgeList = nullptr;
        G.vertexNum++;
        return ;
    }
    G.adjacentTable[G.volume].elem = elem;
    G.volume++;
    G.vertexNum++;
}

Vertex FindVertex(const Graph &G, ElementType elem)
{
    for (int i = 0; i < G.volume; i++)
    {
        if (G.adjacentTable[i].elem == elem && G.adjacentTable[i].existFlag)
        {
            return i;
        }
    }

    return NotAVertex;
}

void AddEdgeByIndex(Graph &G, int weight, Vertex u, Vertex v)
{
    if (u == v || u < 0 || u >= G.volume || v < 0 || v >= G.volume || !G.adjacentTable[u].existFlag || !G.adjacentTable[v].existFlag)
    {
        cout << "Illegal position of edge of graph!" << endl;
        return ;
    }

    //ȷ����������һ���Ѿ����ڵı�
    EdgeNode temp = G.adjacentTable[u].edgeList;
    while (temp != nullptr)
    {
        if (temp->vertex == v)
        {
            cout << "This edge have already exist!" << endl;
            return ;
        }
        temp = temp->nextPtr;
    }

    EdgeNode ptr = new Edge;
    ptr->weight = weight;
    ptr->vertex = v;
    ptr->nextPtr = G.adjacentTable[u].edgeList;
    G.adjacentTable[u].edgeList = ptr;
}

void AddEdge(Graph &G, int weight, ElementType u, ElementType v)
{
    Vertex U, V;

    U = FindVertex(G, u);
    V = FindVertex(G, v);
    AddEdgeByIndex(G, weight, U, V);
}

void DeleteNode(Graph &G, Vertex v)
{
    G.adjacentTable[v].existFlag = false;
    G.vertexNum--;

    //ɾ������ָ��ý��ı�
    for (int i = 0; i < G.volume; i++)
    {
        if (G.adjacentTable[i].existFlag)
            DeleteEdge(G, i, v);
    }

    //ɾ���ý������б�
    EdgeNode temp = G.adjacentTable[v].edgeList;
    while (G.adjacentTable[v].edgeList != nullptr)
    {
        G.adjacentTable[v].edgeList = temp->nextPtr;
        delete temp;
        temp = G.adjacentTable[v].edgeList;
    }
    
}

void DeleteEdge(Graph &G, Vertex u, Vertex v)       //ɾ��һ����u->v�ı�
{
    EdgeNode temp = G.adjacentTable[u].edgeList;
    EdgeNode preTemp = G.adjacentTable[u].edgeList;       //ǰ���ڵ�

    while (temp != nullptr)
    {
        if (temp->vertex == v)
        {
            if (temp == G.adjacentTable[u].edgeList)
            {
                G.adjacentTable[u].edgeList = temp->nextPtr;
                delete temp;
                return ;        //��ΪAddEdgeByIndex����ȷ������������һģһ���ıߣ����Կ���ֱ��return
            }
            else
            {
                preTemp->nextPtr = temp->nextPtr;
                delete temp;
                return ;
            }
        }
        preTemp = temp;
        temp = temp->nextPtr;
    }
}

int GetIndegree(const Graph &G, Vertex v)
{
    int Indegree = 0;
    EdgeNode temp;

    for (int i = 0; i < G.volume; i++)
    {
        if (G.adjacentTable[i].existFlag)
        {
            temp = G.adjacentTable[i].edgeList;
            while (temp != nullptr)
            {
                if (temp->vertex == v)
                    Indegree++;
                temp = temp->nextPtr;
            }
        }
    }

    return Indegree;
}

void DebugShowAll(const Graph &G)
{
    EdgeNode temp;

    cout << "volume: " << G.volume << endl;
    cout << "VertexNum: " << G.vertexNum << endl << endl;
    for (int i = 0; i < G.volume; i++)
    {
        cout << "elem: "<< G.adjacentTable[i].elem << endl;
        cout << "existFlag: " << G.adjacentTable[i].existFlag << endl;

        temp = G.adjacentTable[i].edgeList;
        while (temp != nullptr)
        {
            cout << "  " << G.adjacentTable[temp->vertex].elem << " " << temp->weight << endl;
            temp = temp->nextPtr;
        }
        cout << endl;
    }
}

/*����һ����׼��ͼ�Ĵ���
    AddVertex(G, "v1");
    AddVertex(G, "v2");
    AddVertex(G, "v3");
    AddVertex(G, "v4");
    AddVertex(G, "v5");
    AddVertex(G, "v6");
    AddVertex(G, "v7");

    AddEdge(G, 0, "v1", "v2");
    AddEdge(G, 0, "v1", "v4");
    AddEdge(G, 0, "v2", "v4");
    AddEdge(G, 0, "v2", "v5");
    AddEdge(G, 0, "v3", "v1");
    AddEdge(G, 0, "v3", "v6");
    AddEdge(G, 0, "v4", "v3");
    AddEdge(G, 0, "v4", "v5");
    AddEdge(G, 0, "v4", "v6");
    AddEdge(G, 0, "v4", "v7");
    AddEdge(G, 0, "v5", "v7");
    AddEdge(G, 0, "v7", "v6");
*/