#include <utility>

#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <forward_list>
#include <limits>

#include "linmath.h"

#include "./programs.h"
#include "./util.h"

template<typename F>
class derefFirst
{
public:
    template<typename ...T>
    typename std::result_of<F(T...)>::type operator()(T *...ptr) const { return f(*ptr...); }

private:
    F f;
};

template<typename Iter>
class iter_pair
{
public:
    iter_pair(Iter begin, Iter end) : _begin(std::move(begin)), _end(std::move(end)) { }
    
    const Iter &begin() const { return _begin; }
    
    const Iter &end() const { return _end; }

private:
    Iter _begin;
    Iter _end;
};

template<typename V, typename E>
class graph_impl
{
public:
    graph_impl() = default;
    
    // Don't allow copying without remaking pointers.
    graph_impl(const graph_impl &) = delete;
    
    graph_impl &operator=(const graph_impl &) = delete;
    
    graph_impl(graph_impl &&) noexcept = default;
    
    graph_impl &operator=(graph_impl &&) noexcept = default;
    
    ~graph_impl() = default;
    
    
    class edge;
    class vertex
    {
    public:
        const V &data() const { return _data; }
        
        V &data() { return _data; }
        
        iter_pair<typename std::forward_list<edge>::iterator> adj() { return {_adj.begin(), _adj.end()}; }
    
    private:
        vertex(V data, std::forward_list<edge> &adj) : _data(std::move(data)), _adj(adj) { }
        
        V _data;
        std::forward_list<edge> &_adj;
        
        friend class graph_impl;
    };
    
    class edge
    {
    public:
        vertex &to() const { return _to; }
        E &data() const { return _data; }

    private:
        edge(vertex &to, E &data) : _to(to), _data(data) { }
        
        vertex &_to;
        E &_data;
        friend class graph_impl;
    };
    
    vertex *addVertex(V data);
    
    size_t numVertices() const { return _numVertices; }
    
    const vertex *getVertex(const V &data) const;
    
    vertex *getVertex(const V &data);
    
    vertex *ensureVertex(const V &data);
    
    void addEdge(vertex *from, vertex *to, E data);
    
    bool hasEdge(const vertex *from, const vertex *to) const;
    
    const E &getEdgeData(const vertex *from, const vertex *to) const;
    
    E &getEdgeData(const vertex *from, const vertex *to);
    
    iter_pair<typename std::forward_list<vertex>::iterator> vertices();

private:
    size_t _numVertices = 0;
    std::forward_list<vertex> _vertices;
    
    std::unordered_map<
        const V *,
        vertex *,
        derefFirst<std::hash<V>>,
        derefFirst<std::equal_to<V>>
    > _key2Vertex;
    
    std::forward_list<std::forward_list<edge>> _adjacencyLists;
    std::forward_list<E> _edgeData;
};

template<typename V, typename E>
typename graph_impl<V, E>::vertex *graph_impl<V, E>::addVertex(V data)
{
    _adjacencyLists.emplace_front();
    _vertices.push_front({std::move(data), *_adjacencyLists.begin()});
    vertex *ptr = &*_vertices.begin();
    _key2Vertex[&(ptr->_data)] = ptr;
    _numVertices++;
    return ptr;
}

template<typename V, typename E>
typename graph_impl<V, E>::vertex *graph_impl<V, E>::getVertex(const V &data)
{
    auto iter = _key2Vertex.find(&data);
    if (iter == _key2Vertex.end()) {
        return nullptr;
    }
    return iter->second;
}

template<typename V, typename E>
const typename graph_impl<V, E>::vertex *graph_impl<V, E>::getVertex(const V &data) const
{
    auto iter = _key2Vertex.find(&data);
    if (iter == _key2Vertex.end()) {
        return nullptr;
    }
    return iter->second;
}

template<typename V, typename E>
typename graph_impl<V, E>::vertex *graph_impl<V, E>::ensureVertex(const V &data)
{
    auto iter = _key2Vertex.find(&data);
    if (iter == _key2Vertex.end()) {
        return addVertex(data);
    }
    return iter->second;
}

template<typename V, typename E>
void graph_impl<V, E>::addEdge(vertex *from, vertex *to, E data)
{
    _edgeData.push_front(std::move(data));
    auto &data_ref = *_edgeData.begin();
    from->_adj.push_front({*to, data_ref});
    to->_adj.push_front({*from, data_ref});
}

template<typename V, typename E>
bool graph_impl<V, E>::hasEdge(const vertex *from, const vertex *to) const
{
    for (const edge &edge : from->_adj) {
        if (&edge._to == to) return true;
    }
    return false;
}

template<typename V, typename E>
const E &graph_impl<V, E>::getEdgeData(const graph_impl::vertex *from, const graph_impl::vertex *to) const
{
    for (const edge &edge : from->_adj) {
        if (edge._to == to) return edge._data;
    }
    throw std::runtime_error("Doesn't contain edge");
}

template<typename V, typename E>
E &graph_impl<V, E>::getEdgeData(const graph_impl::vertex *from, const graph_impl::vertex *to)
{
    for (const edge &edge : from->_adj) {
        if (&edge._to == to) return edge._data;
    }
    throw std::runtime_error("Doesn't contain edge");
}

template<typename V, typename E>
iter_pair<typename std::forward_list<typename graph_impl<V, E>::vertex>::iterator>
graph_impl<V, E>::vertices()
{
    return {_vertices.begin(), _vertices.end()};
}

struct vertex_info
{
    vertex_info(std::string data, Point location) : data(std::move(data)), location(location) { }
    
    std::string data;
    Point location;
    double d = 0;
    vertex_info *pi = nullptr;
    
    bool operator==(const vertex_info &rhs) const { return data == rhs.data; }
};

template<>
class std::hash<vertex_info>
{
public:
    size_t operator()(const vertex_info &v) const
    {
        return _hasher(v.data);
    }

private:
    std::hash<std::string> _hasher;
};

typedef graph_impl<vertex_info, std::string>::vertex Vertex;


// For the purposes of implementing dijkstra's algorithm,
// You will want to store references to the source, target,
// as well as current vertices (the current vertex points to
// the vertex being moved, when applicable). These references
// are updated in the mouseControlClick, mouseShiftClick, and
// mouseDown/mouseMoved functions respectively (in Graph.cpp).
class Graph
{
public:
    
    void render(FlatProgram &program, mat4x4 mvp);
    
    void mouseDown(const Point &p);
    
    void mouseShiftClick(const Point &p);
    
    void mouseControlClick(const Point &p);
    
    void mouseMoved(const Point &p);
    
    Vertex *addVertex(const std::string &data, const Point &p);
    
    void addEdge(Vertex *u, Vertex *v, const std::string &data);
    
    void dijkstra(Vertex *source);
    
    // Note on implementing dijkstra(): for the priority queue,
    // consider using the following:
    //    auto cmp = [](Vertex* u, Vertex* v) { return u->d() > v->d(); };
    //    priority_queue<Vertex*, vector<Vertex*>, decltype(cmp)> Q(cmp);
    // This uses lambda expressions to supply the "less than"
    // function to the priority queue.
private:
    graph_impl<vertex_info, std::string> _graph;
    Vertex *_source = nullptr;
    Vertex *_target = nullptr;
    Vertex *_current = nullptr;
    
    Vertex *closest(const Point &p);
    
    double w(Vertex *u, Vertex *v);
    void initializeSingleSource(Vertex *start);
};

//------------------------------------------------------------
// TODO: This is where the graph is initialized with vertices.
// You can add/take away vertices as you wish. This function
// is implemented in Graph.cpp.
//------------------------------------------------------------
void initGraph(Graph &g);