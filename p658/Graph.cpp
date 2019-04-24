#include <iostream>
#include <algorithm>
#include <unordered_set>

#include "./Graph.h"
#include "./Vertex.h"
#include "./Circle.h"
#include "./Line.h"

// TODO: Move the "current" vertex to point p. You will set
// the current vertex in mouseDown(). If you have source
// and target vertices (as stored in the graph), call the 
// dijkstra() function after moving the vertex to update 
// the shortest path. 
void Graph::mouseMoved(const Point &p)
{
    if (_current) {
        _current->data().location = p;
    }
    
    if (_source && _target) {
        dijkstra(_source);
    }
}

// TODO: Use the distance function to find the vertex closest
// to the mouse click. That vertex will become the new current
// vertex. Update the shortest path if appropriate.
void Graph::mouseDown(const Point &p)
{
    _current = closest(p);
    
    if (_source && _target) {
        dijkstra(_source);
    }
}

// TODO: Use the distance function to find the vertex closest
// to the mouse click. That vertex will become the new source
// vertex. Update the shortest path if appropriate.
void Graph::mouseControlClick(const Point &p)
{
    _source = closest(p);
    
    if (_source && _target) {
        dijkstra(_source);
    }
}

// TODO: Use the distance function to find the vertex closest
// to the mouse click. That vertex will become the new target
// vertex. Update the shortest path if appropriate.
void Graph::mouseShiftClick(const Point &p)
{
    _target = closest(p);
    
    if (_source && _target) {
        dijkstra(_source);
    }
}

void Graph::render(FlatProgram &program, mat4x4 mvp)
{
    using namespace std;
    
    Circle *c = Circle::instance();
    Line *l = Line::instance();
    
    // Renders a line from point p to point q
    glLineWidth(1.0); // Set this to 5.0 to bold the shortest path line.
    
    // render all edges in GRAY, and then rerender edges belonging
    // to the shortest path (if source and target are selected) in RED
    
    // Renders dots at points p and q
    // The source node (if selected) should be RED
    // The target node (if selected) should be BLUE
    // All other nodes should be gray
    
    // TODO: Render edges and vertices using the functions
    // demonstrated above.
    for (Vertex &from : _graph.vertices()) {
        for (auto &edge : from.adj()) {
            Vertex &to = edge.to();
            l->render(program, mvp, from.data().location, to.data().location, Color::GRAY);
        }
    }
    
    glLineWidth(5.0); // Set this to 5.0 to bold the shortest path line.
    if (_target) {
        auto node = &(_target->data());
        auto next = node->pi;
        while (next) {
            l->render(program, mvp, node->location, next->location, Color::RED);
            node = next;
            next = node->pi;
        }
    }
    
    for (Vertex &v : _graph.vertices()) {
        c->render(program, mvp, v.data().location, Color::GRAY, true);
    }
    if (_source) {
        c->render(program, mvp, _source->data().location, Color::RED, true);
    }
    if (_target) {
        c->render(program, mvp, _target->data().location, Color::BLUE, true);
    }
}

// TODO: Implement. Each vertex should have a point location
// associated with it.
Vertex *Graph::addVertex(const std::string &data, const Point &p)
{
    return _graph.addVertex({data, p});
}

// TODO: Implement.
void Graph::addEdge(Vertex *u, Vertex *v, const std::string &data)
{
    _graph.addEdge(u, v, data);
}

void Graph::dijkstra(Vertex *source)
{
    initializeSingleSource(source);
    std::unordered_set<Vertex *> S;
    typedef std::tuple<double, Vertex*, Vertex*> V;
    auto cmp = [](V p1, V p2) { return std::get<0>(p1) > std::get<0>(p2); };
    std::priority_queue<V, std::vector<V>, decltype(cmp)> Q{cmp};
    Q.push({0, source, nullptr});
    
    while (!Q.empty()) {
        double d;
        Vertex *u;
        Vertex *pi;
        std::tie(d, u, pi) = Q.top();
        Q.pop();
        
        if (!S.insert(u).second) continue;
        u->data().pi = &(pi->data());
        u->data().d = d;
        
        for (auto &edge : u->adj()) {
            Vertex *v = &(edge.to());
            Q.push({d + w(u, v), v, u});
        }
    }
}

Vertex *Graph::closest(const Point &p)
{
    auto vertices = _graph.vertices();
    auto min = std::min_element(
        vertices.begin(), vertices.end(), [&](Vertex &v1, Vertex &v2)
        {
            return distance(p, v1.data().location) < distance(p, v2.data().location);
        }
    );
    if (min == vertices.end()) {
        return nullptr;
    }
    return &*min;
}

double Graph::w(Vertex *u, Vertex *v)
{
    if (_graph.hasEdge(u, v)) {
        return distance(u->data().location, v->data().location);
    }
    return std::numeric_limits<double>::infinity();
}

void Graph::initializeSingleSource(Vertex *start)
{
    for (Vertex &v : _graph.vertices()) {
        v.data().d = std::numeric_limits<double>::infinity();
        v.data().pi = nullptr;
    }
    start->data().d = 0;
}

//------------------------------------------------------------
// TODO: This is where the graph is initialized with vertices.
// You can add/take away vertices as you wish.
//------------------------------------------------------------
void initGraph(Graph &g)
{
    // Layout of the vertices:
    //
    //               G
    //         D
    //   A           C
    //
    //         E
    //         F
    
    Vertex *A = g.addVertex("A", Point(-0.5, 0));
    Vertex *C = g.addVertex("C", Point(0.5, 0));
    Vertex *D = g.addVertex("D", Point(0, 0.25));
    Vertex *E = g.addVertex("E", Point(0, -0.3));
    Vertex *F = g.addVertex("F", Point(0, -0.7));
    Vertex *G = g.addVertex("G", Point(0.5, 0.35));
    
    g.addEdge(A, D, "A-D");
    g.addEdge(A, E, "A-E");
    g.addEdge(D, G, "D-G");
    g.addEdge(G, C, "G-C");
    g.addEdge(E, C, "E-C");
    g.addEdge(A, F, "A-F");
    g.addEdge(F, C, "F-C");
}

