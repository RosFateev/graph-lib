#include <iostream>
#include <algorithm>                                // std::for_each
#include "graph-lib/graph.hpp"                      // graph::Graph
#include "graph-lib/display/outputter.hpp"          // output::Outputter
#include "graph-lib/algorithm/traversal/dfs.hpp"    // algorithm::dfs



// Create string representation of edge direction type
std::string direction_to_string(component::traits::edge_direction direction)
{
    return direction == component::traits::edge_direction::none ? "---" : "-->";
}


// print vertex to stdout
template<class id_type>
void print_vertex(const component::Vertex<id_type>& vertex)
{
    // [ id, (x,y) ]
    std::cout << "[ " << vertex.Id()
          << ", (" << vertex.Coordinate(0)
          << "," << vertex.Coordinate(1)
          << ") ]";
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
            print_vertex<id_type>(mapTuple.first);
            std::cout << " :";

            // print edges
            auto edges = graph.GetNeighbours(mapTuple.first);

            std::for_each(edges.begin(), edges.end(),
                [&mapTuple](const auto& edge)
                {
                    std::cout << " < ";
                    print_vertex<id_type>(edge.GetVertex(0));
                    std::cout << ", ";
                    print_vertex<id_type>(edge.GetVertex(1));
                    std::cout << ", "
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

    // draw graph
    output::Outputter<char> graphout;
    graphout << testGraph;

    // print graph after drawer component done stuff
    print_graph<char>(testGraph);


    // run dfs
    algorithm::dfs<char> dfsObj(testGraph);
    dfsObj.run(testGraph.GetVertex('a'));

    // print result
    std::for_each(dfsObj.get().begin(), dfsObj.get().end(),
        [](const auto& tuple)
        {
            print_vertex<char>(tuple.first);
            std::cout << " : ";
            print_vertex<char>(tuple.second);
            std::cout << '\n';
        });

    /*
    // remove components:
    //        3
    // ('a') --> ('b')                ('b')
    //  | \        |                    |
    //  |  --      |                    |
    // 7|    \0    |5      ~            |5
    //  |     --   |                    |
    //  |       \  V                    V
    // ('d') <-- ('c')       ('d')    ('c')
    //        1
    testGraph.RemoveVertex('a');
    testGraph.RemoveEdge('c','d', component::traits::edge_direction::one_two, 1);

    // print graph
    print_graph<char>(testGraph);

    // display graph
    graphout << testGraph;

    // try to remove/access nonexisting values
    try
    {
        testGraph.GetVertex('e');
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        testGraph.GetEdge('b', 'c', component::traits::edge_direction::none, 5);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        testGraph.RemoveEdge('b', 'a', component::traits::edge_direction::none, 5);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        testGraph.RemoveVertex('a');
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    // print graph
    print_graph<char>(testGraph);
    */
    return 0;
}