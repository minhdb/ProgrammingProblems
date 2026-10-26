/**
 * EPI Chapter 19 Graphs
 *
 * 19.9 Compute a shortest path with fewest edges.
 *
 * In the usual formulatino of the shortest path problem, the number of edges
 * in the path is not a consideration. For example, considering the shortest
 * path problem from a to h on Page 345, the sum of the edge costs on the path
 * <a, c, e, d, h> is 22, which is the same as for path
 * <a, b, k, i, j, f, g, h>. Both are shortest paths, but the latter has 3 more
 * edges.
 *
 * Heuristically, if we did want to avoid paths with a large number of edges, we
 * can add the small amount to the cost of each edge. However, depending on the
 * structure of the graph and the edge costs, this may not result in the
 * shortest path.
 *
 * Design an algorithm which takes as input a graph G = (V, E), directed or
 * undirected, a nonnegative cost function on E, and vertices s and t; your
 * algorithm should output a path with the fewest edges amongst all shortest
 * paths from s to t.
 *
 * Hint: Change the edge cost and cast it as an instance of the standard
 * shortest path problem.
 */

#include <vector>
#include <set>
#include <limits>
#include <iostream>

using std::vector;
using std::set;
using std::cout;
using std::numeric_limits;



/**
 * Idea:
 *
 * Time complexity: O((|E| + |V|) log|V|)
 * Space complexity:
 */
struct GraphVertex
{
    struct DistanceWithFewestEdges
    {
        int distance, min_num_edges;
    };

    DistanceWithFewestEdges distance_with_fewest_edges =
        DistanceWithFewestEdges{numeric_limits<int>::max(), 0};

    struct VertexWithDistance
    {
        GraphVertex& vertex;
        int distance;
    };

    vector<VertexWithDistance> edges;

    // The id of this vertex.
    int id;

    // The predecessor in the shortest path.
    const GraphVertex* pred = nullptr;
};

struct Comp
{
    bool operator()(const GraphVertex* lhs, const GraphVertex* rhs) const
    {
        return lhs->distance_with_fewest_edges.distance < 
            rhs->distance_with_fewest_edges.distance ||
            (lhs->distance_with_fewest_edges.distance ==
             rhs->distance_with_fewest_edges.distance &&
             lhs->distance_with_fewest_edges.min_num_edges <
             rhs->distance_with_fewest_edges.min_num_edges);
    }
};


void OutputShortestPath(const GraphVertex* v)
{
    if (v) {
        OutputShortestPath(v->pred);
        std::cout << v->id << " ";
    }
}

void DijkstraShortestPath(GraphVertex* s, const GraphVertex* t)
{
    // Initialization of the distance of starting point.
    s->distance_with_fewest_edges = {0, 0};
    set<GraphVertex*, Comp> node_set;
    node_set.emplace(s);

    while(!node_set.empty()) {
        // Extracts the minimum distance vertex from heap.
        GraphVertex* u = *node_set.cbegin();
        if (u->id == t->id) break;

        node_set.erase(node_set.cbegin());

        // Relax neighboring vertices of u.
        for (const GraphVertex::VertexWithDistance& v : u->edges) {
            int v_dist = u->distance_with_fewest_edges.distance + v.distance;
            int v_num_edges = u->distance_with_fewest_edges.min_num_edges + 1;
            if (v.vertex.distance_with_fewest_edges.distance > v_dist ||
                    (v.vertex.distance_with_fewest_edges.distance == v_dist &&
                     v.vertex.distance_with_fewest_edges.min_num_edges > v_num_edges)) {
                node_set.erase(&v.vertex);
                v.vertex.pred = u;
                v.vertex.distance_with_fewest_edges = {v_dist, v_num_edges};
                node_set.emplace(&v.vertex);
            }
        }
    }
    // Outputs the shortest path with fewest edges.
    OutputShortestPath(t);
};

int main()
{
    return 0;
}
