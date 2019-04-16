#include "./bacon.h"

#include "./util.h"

using namespace std;

Graph buildBaconGraph(const string &filename)
{
    Graph G;
    // The Movie struct can be found in util.h
    vector<Movie> movies = readMovieFile(filename);

//   fill the graph G such that one vertex exists for each
//   actor, and an edge exists between two actors' vertices if they
//   have appeared in a film together. The edge should be annotated
//   with the name of the film.
//
//   It is recommended (but not required) that you output a
//   progress indicator because this function could take a
//   little bit of time for some input files. You would do
//   this as follows:
    for (Movie &movie : movies) {
        for (size_t i = 0; i < movie.actors.size(); i++) {
            for (size_t j = 0; j < movie.actors.size(); j++) {
                G.addEdge(
                    G.ensureVertex(movie.actors[i]),
                    G.ensureVertex(movie.actors[j]),
                    movie.name
                );
            }
        }
    }
    
    return G;
}

void play(const string &filename)
{
    // implement the Six Degrees of Kevin Bacon game here.
    Graph g = buildBaconGraph(filename);
    Vertex *kb = g.getVertex("Bacon, Kevin (I)");
    g.bfs(kb);
    
    while (true) {
        std::cout << "Please enter an actor's name (press Enter to quit): ";
        std::string name;
        if (!std::getline(std::cin, name)) return;
        if (name.empty()) return;
        Vertex *v = g.getVertex(name);
        if (!v) {
            std::cout << name << " isn't in our database. Please try someone else.\n" << std::endl;
            continue;
        }
        std::cout << name << " has a Bacon number of " << v->d() << "\n";
        while (v->pi() != nullptr) {
            std::cout << v->data() << " was in " << g.getEdgeData(v, v->pi()) << " with " << v->pi()->data() << "\n";
            v = v->pi();
        }
        std::cout << std::endl;
    }
    
    
    // // This code should help when you need to get input from the
    // // user.
    // cout << "Please enter an actor's name (press Enter to quit): ";
    // string name;
    // getline(cin, name);
}
