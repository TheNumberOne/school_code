#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#include "./programs.h"
#include "./util.h"

class Vertex {
};

// For the purposes of implementing dijkstra's algorithm,
// You will want to store references to the source, target,
// as well as current vertices (the current vertex points to
// the vertex being moved, when applicable). These references
// are updated in the mouseControlClick, mouseShiftClick, and
// mouseDown/mouseMoved functions respectively (in Graph.cpp).
class Graph {
 public:

  void render(FlatProgram& program, mat4x4 mvp);

  void mouseDown(const Point& p);
  void mouseShiftClick(const Point& p);
  void mouseControlClick(const Point& p);
  void mouseMoved(const Point& p);

  Vertex* addVertex(const std::string& data, const Point& p);
  void addEdge(Vertex* u, Vertex* v, const std::string& data);

  // Note on implementing dijkstra(): for the priority queue,
  // consider using the following:
  //    auto cmp = [](Vertex* u, Vertex* v) { return u->d() > v->d(); };
  //    priority_queue<Vertex*, vector<Vertex*>, decltype(cmp)> Q(cmp);
  // This uses lambda expressions to supply the "less than"
  // function to the priority queue.
};

//------------------------------------------------------------
// TODO: This is where the graph is initialized with vertices.
// You can add/take away vertices as you wish. This function
// is implemented in Graph.cpp.
//------------------------------------------------------------
void initGraph(Graph& g);
