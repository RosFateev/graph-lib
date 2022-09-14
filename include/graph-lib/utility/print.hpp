//==============================================================================
///
/// @file print.hpp
///
/// @brief <description>
///
/// <Detailed description>
///
/// The documentation is available on the following website:
/// <website>
///
/// Support email: <email>
///
//==============================================================================

//==============================================================================
// Include only once
//
#ifndef GRAPH_LIB_UTILITY_PRINT_HPP
#define GRAPH_LIB_UTILITY_PRINT_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <string>
#include <iostream>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/edge-support.hpp"


//------------------------------------------------------------------------------
// Global references
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

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
        << vertex.Coordinate(0) <<','
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
    std::cout << ", "
              << direction_to_string(edge.GetDirection())
              << ", "
              << edge.GetWeight()
              << ", "
              << edge.GetFlow()
              << '/'
              << edge.GetCapacity()
              << " >";
}

// print traversal algorithm results to stdout
template<class id_type>
void
print_traversal_result(
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
            std::cout << '\n';
        });
}

// print Dinic algorithm level structure to stdout
template<class id_type>
void
print_level_structure(
        const std::map<component::Vertex<id_type>,
                       int,
                       component::support::vertex_less<id_type>>& container)
{
    std::cout << "Algorithm structure:\n";

    std::for_each(container.cbegin(),container.cend(),
        [](const auto& tuple)
        {
            std::cout << "Key: ";
            print_vertex<id_type>(tuple.first);
            std::cout << ", Value: " << tuple.second << '\n';
        });
}

// print graph
template<class id_type>
void
print_graph(const graph::Graph<id_type>& graph)
{
    std::cout << "Graph:\n";

    std::for_each(graph.cbegin(), graph.cend(),
        [](const auto& tuple)
        {
            print_vertex<id_type>(tuple.first);
            std::cout << "  : ";
            std::for_each(tuple.second.begin(), tuple.second.end(),
                [](const auto& edge)
                {
                    print_edge<id_type>(edge);
                    std::cout << " | ";
                });
            std::cout << '\n';
        });
}



#endif // GRAPH_LIB_UTILITY_PRINT_HPP
//==============================================================================
// End of print.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
