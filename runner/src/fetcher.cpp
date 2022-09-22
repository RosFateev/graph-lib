//==============================================================================
///
/// @file fetcher.cpp
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


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <fstream>          // std::fstream
#include <sstream>          // std::stringstream

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "fetcher.h"


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
// Local data types
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward function declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
Fetcher::Fetcher()
{   }

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
graph::Graph<std::string>
Fetcher::get_graph(const std::string& filePath)
{
    // open file for reading
    std::fstream stream(filePath, std::ios::in);

    if (stream.is_open())
    {
        // read vertices
        typename Fetcher::vertex_init_container vertices;
        read_vertices(stream, vertices);

        // read edges
        typename Fetcher::edge_init_container edges;
        read_edges(stream, edges);

        // construct graph object
        graph::Graph<std::string> graph(vertices, edges);

        return graph;
    }
    
    std::cout << "File " << filePath << " does not exist\n";
    throw;
}

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
void
Fetcher::read_vertices(
        std::fstream& stream,
        typename Fetcher::vertex_init_container& vertices)
{
    for (std::string token; std::getline(stream, token);)
    {
        if (token == "---")
        {
            break;
        }

        vertices.push_back(token);
    }
}

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
void
Fetcher::read_edges(
        std::fstream& stream,
        typename Fetcher::edge_init_container& edges)
{
    for (std::string token; std::getline(stream, token);)
    {
        edges.push_back(parse_edge(token));
    }
}

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
typename Fetcher::edge_init_type
Fetcher::parse_edge(std::string input)
{
    // edge consists of:
    // vertex1, vertex2, direction, weight, capacity, flow
    // string,  string,     int,     int,     int,     int
    //  need     need     optional  optional optional  optional
    std::string vertex1("");
    std::string vertex2("");
    std::string direction("");
    std::string weight("");
    std::string capacity("");
    std::string flow("");

    std::stringstream converter(input);
    converter >> vertex1;
    converter >> vertex2;
    converter >> direction;
    converter >> weight;
    converter >> capacity;
    converter >> flow;

    return std::make_tuple(
        vertex1,
        vertex2,
        (direction == "-->" ? component::traits::edge_direction::one_two :
                              component::traits::edge_direction::none),
        (weight == "" ? 0 : std::stoi(weight)),
        (capacity == "" ? 0 : std::stoi(capacity)),
        (flow == "" ? 0 : std::stoi(flow)));
}



//==============================================================================
// End of fetcher.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
