#include <iostream>             // std::cout
#include <algorithm>            // std::for_each
#include "graph-lib/graph.hpp"                      // graph::Graph
#include "graph-lib/display/outputter.hpp"          // output::Outputter
#include "graph-lib/algorithm/traversal/dfs.hpp"    // algorithm::dfs
#include "graph-lib/algorithm/traversal/bfs.hpp"    // algorithm::bfs





// Create string representation of edge direction type
std::string
direction_to_string(component::traits::edge_direction direction)
{
    return direction == component::traits::edge_direction::none ? "---" : "-->";
}

// print vertex to stdout
template<class id_type>
void
print_vertex(const component::Vertex<id_type>& vertex)
{
    std::cout << "[ "
        << vertex.Id() << " - ("
        << vertex.Coordinate(0) << ","
        << vertex.Coordinate(1) << ") ]";
}

// print edge to stdout
template<class id_type>
void
print_edge(const component::Edge<id_type>& edge)
{
    std::cout << "< ";
    print_vertex<id_type>(edge.GetVertex(0));
    std::cout << ", ";
    print_vertex<id_type>(edge.GetVertex(1));
    std::cout << ", ";
    std::cout << direction_to_string(edge.GetDirection());
    std::cout << ", ";
    std::cout << edge.GetWeight() << " >";
}

// print algorithm results to stdout
template<class id_type>
void
print_algorithm_result(
        const std::map<component::Vertex<id_type>,
                       component::Vertex<id_type>,
                       component::support::vertex_less<id_type>>& container)
{
    std::cout << "Algorithm structure:\n";

    std::for_each(container.cbegin(),container.cend(),
        [](const auto& tuple)
        {
            std::cout << "Key: ";
            print_vertex<id_type>(tuple.first);
            std::cout << ", Value: ";
            print_vertex<id_type>(tuple.second);
            std::cout << "\n";
        });
}





template<class id_type>
void
initialize_graph(graph::Graph<id_type>& testGraph)
{
    // fill with vertices
    testGraph.AddVertex('a');
    testGraph.AddVertex('b');
    testGraph.AddVertex('c');
    testGraph.AddVertex('d');
    testGraph.AddVertex('e');
    testGraph.AddVertex('f');
    

    // fill graph with edges
    // a edges
    testGraph.AddEdge( 'a', 'b', component::traits::edge_direction::one_two, 3);
    testGraph.AddEdge( 'a', 'd', component::traits::edge_direction::none, 7);
    testGraph.AddEdge( 'a', 'e', component::traits::edge_direction::none);
    // b edges
    testGraph.AddEdge( 'b', 'e', component::traits::edge_direction::one_two, 5);
    // c edges
    testGraph.AddEdge( 'c', 'b', component::traits::edge_direction::one_two, 10);
    // e edges
    testGraph.AddEdge( 'e', 'c', component::traits::edge_direction::one_two, 4);
    testGraph.AddEdge( 'e', 'd', component::traits::edge_direction::one_two, 1);
    testGraph.AddEdge( 'e', 'f', component::traits::edge_direction::one_two, 15);
    // f edges
    testGraph.AddEdge( 'f', 'c', component::traits::edge_direction::none, 1);

    std::cout << "Graph object was created" << std::endl;
}





template<class id_type>
void
traversal_demo(graph::Graph<id_type>& testGraph)
{
    // draw graph
    output::Outputter<char> graphout;
    graphout.Display(testGraph);


    // run dfs
    algorithm::dfs<char> dfsObj(&testGraph);
    dfsObj.run(testGraph.GetVertex('a'));
    // print algorithm result
    print_algorithm_result<char>(dfsObj.get());
    // draw algorithm result
    graphout.Display(testGraph, &dfsObj.get());


    // run bfs
    algorithm::bfs<char> bfsObj(&testGraph);
    bfsObj.run(testGraph.GetVertex('a'));
    // print algorithm result
    print_algorithm_result<char>(bfsObj.get());
    // draw algorithm result
    graphout.Display(testGraph, &bfsObj.get());
}





int main()
{
    // create test graph
    //        3         10
    // ('a') --> ('b') <-- ('c')
    //  | \        |       > |
    //  |  --      |    4 /  |
    // 7|    \0    |5   --   | 1
    //  |     --   |   /     |
    //  |       \  V  /      |
    // ('d') <-- ('e') --> ('f')
    //        1         15
    graph::Graph<char> testGraph;
    
    initialize_graph<char>(testGraph);


    // run dfs and bfs algorithms
    traversal_demo<char>(testGraph);
    

    return 0;
}