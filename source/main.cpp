#include <iostream>
#include <algorithm>
#include "graph-lib/graph.hpp"



// Create string representation of edge direction type
std::string direction_to_string(component::traits::edge_direction direction)
{
    return direction == component::traits::edge_direction::none ? "---" : "-->";
}


// print graph to stdout
template<class id_type>
void print_graph(const graph::Graph<id_type>& graph)
{
    // iterate over map structure
    std::for_each(graph.cbegin(), graph.cend(),
        [&graph](const auto& mapTuple)
        {
            // print vertex
            std::cout << "[ " << mapTuple.first.Id() << " ] :";
            // print edges
            auto edges = graph.GetNeighbours(mapTuple.first);

            std::for_each(edges.begin(), edges.end(),
                [&mapTuple](const auto& edge)
                {
                    std::cout << " < " 
                              << mapTuple.first.Id()
                              << ", " 
                              << edge.GetVertex(1).Id()
                              << ", "
                              << direction_to_string(edge.GetDirection())
                              << ", "
                              << edge.GetWeight()
                              << ">";
                });
            std::cout << std::endl;
        });
}


// create graph instance
template<class id_type>
graph::Graph<id_type> create_test_graph()
{
    // create graph object
    graph::Graph<char> testGraph;
    
    //        3
    // ('a') --> ('b')
    //  | \        |
    //  |  --      |
    // 7|    \0    |5
    //  |     --   |
    //  |       \  V
    // ('d') <-- ('c')
    //        1
    // fill with vertices
    testGraph.AddVertex('a');
    testGraph.AddVertex('b');
    testGraph.AddVertex('c');
    testGraph.AddVertex('d');
    
    // fill graph with edges
    testGraph.AddEdge( 'a', 'b', component::traits::edge_direction::one_two, 3);
    testGraph.AddEdge( 'a', 'c', component::traits::edge_direction::none);
    testGraph.AddEdge( 'a', 'd', component::traits::edge_direction::none, 7);
    testGraph.AddEdge( 'b', 'c', component::traits::edge_direction::one_two, 5);
    testGraph.AddEdge( 'c', 'd', component::traits::edge_direction::one_two, 1);

    std::cout << "Graph object was created" << std::endl;

    return testGraph;
}



int main()
{
    auto testGraph = create_test_graph<char>();

    // print graph
    print_graph<char>(testGraph);

    return 0;
}