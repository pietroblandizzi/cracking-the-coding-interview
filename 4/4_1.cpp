/*****************************************************************************
Copyright (c) [2017] [Blandizzi Pietro]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************************************************************************/

#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;



class Node
{
public:
    int data;
    bool visited;
    std::vector<Node*> adj;
};

typedef vector<Node*>::size_type v_size;

class Graph
{
   std::vector<Node*> g;

public:
    Graph () {}

    void addNode (int d);
    void addEdge (Node* s, Node* d);
    bool is_there_a_path (Node* s, Node* d);
    void print ();
    Node* getNodePointer (int d);
    void printNeighbours (int d);
};

void Graph::addNode (int d) {

 Node* n = new Node;
 n->data = d;
 n->visited = false;

 g.push_back(n);

}
void Graph::addEdge (Node* s, Node* d)
{
    //direct graph
    for (v_size i = 0; i < g.size(); i++) {
        if (g[i] == s) {
            g[i]->adj.push_back(d);
        }
    }
}

bool Graph::is_there_a_path (Node* s, Node* d)
{
    if (s == nullptr || d == nullptr)
        return false;

    if (s == d)
        return true;

    //unmark all
    for (v_size i = 0; i < g.size(); i++) {
        g[i]->visited = false;
    }

    queue<Node*> q;
    s->visited = true;
    q.push(s);

    while (!q.empty()) {

        Node* n = q.front();
        q.pop();
        n->visited = true;
        for (v_size i = 0;i <n->adj.size(); i++) {
            if (n->adj[i] == d)
                return true;

            if (n->adj[i]->visited == false)
                q.push(n->adj[i]);
        }
    }
    return false;
}

void Graph::print ()
{
    for (v_size i = 0; i < g.size(); i++) {
        std::cout << g[i]->data << std::endl;
    }
    std::cout <<  std::endl;
}

Node* Graph::getNodePointer (int d)
{
    for (v_size i = 0; i < g.size(); i++) {
        if (g[i]->data == d)
            return g[i];
    }
    return nullptr;
}

void Graph::printNeighbours (int d)
{
    Node* t = getNodePointer(d);
    if (t == nullptr || t->adj.size() == 0)
        return;

    for (v_size i = 0;i < t->adj.size(); i++) {
        std::cout << t->adj[i]->data << std::endl;
    }
    std::cout <<  std::endl;

}

int main()
{
    Graph g;

    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addNode(6);
    g.addNode(7);

    g.print();
//create the edges

    Node* s = g.getNodePointer(1);
    Node* d = g.getNodePointer(2);
    g.addEdge(s,d);

    s = g.getNodePointer(2);
    d = g.getNodePointer(3);
    g.addEdge(s,d);

    s = g.getNodePointer(2);
    d = g.getNodePointer(4);
    g.addEdge(s,d);

    s = g.getNodePointer(3);
    d = g.getNodePointer(4);
    g.addEdge(s,d);

    s = g.getNodePointer(4);
    d = g.getNodePointer(5);
    g.addEdge(s,d);

    s = g.getNodePointer(5);
    d = g.getNodePointer(6);
    g.addEdge(s,d);

    s = g.getNodePointer(6);
    d = g.getNodePointer(4);
    g.addEdge(s,d);

    s = g.getNodePointer(7);
    d = g.getNodePointer(3);
    g.addEdge(s,d);


    g.printNeighbours(2);

    s = g.getNodePointer(3);
    d = g.getNodePointer(6);

    if (g.is_there_a_path(s,d))
        std::cout << "yes!" << std::endl;
    else
        std::cout << "no!" << std::endl;
    return 0;
}
