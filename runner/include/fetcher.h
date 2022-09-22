//==============================================================================
///
/// @file fetcher.h
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
#ifndef FETCHER_H
#define FETCHER_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <string>               // std::getline

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/graph.hpp"      // graph::Graph

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

//------------------------------------------------------------------------------
/// @brief Processes input file to construct a graph.
///
//------------------------------------------------------------------------------
class Fetcher
{
    using vertex_init_type      = std::string;
    using edge_init_type        = std::tuple<vertex_init_type,
                                             vertex_init_type,
                                             component::traits::edge_direction,
                                             int,
                                             int,
                                             int>;
    using vertex_init_container = std::vector<vertex_init_type>;
    using edge_init_container   = std::vector<edge_init_type>;

public:

    //------------------------------------------------------------------------------
    ///
    /// @brief Default constructor
    ///
    //------------------------------------------------------------------------------
    Fetcher();

    //------------------------------------------------------------------------------
    ///
    /// @brief Construct graph from file.
    ///
    /// @param[in] filePath Path to file containing graph data.
    ///
    /// @return Graph object.
    ///
    //------------------------------------------------------------------------------
    graph::Graph<std::string>
    get_graph(const std::string& filePath);

private:

    //------------------------------------------------------------------------------
    ///
    /// @brief Read vertices from file.
    ///
    /// @param[in] stream File input stream object.
    ///
    /// @param[out] vertices Vertex initialization container to fill.
    ///
    /// @return Container with vertex initialization values.
    ///
    //------------------------------------------------------------------------------
    void
    read_vertices(std::fstream& stream,
                  vertex_init_container& vertices);

    //------------------------------------------------------------------------------
    ///
    /// @brief Read edges from file.
    ///
    /// @param[in] stream File input stream object.
    ///
    /// @param[out] edges Edge initialization container to fill.
    ///
    /// @return Container with edge initialization values.
    ///
    //------------------------------------------------------------------------------
    void
    read_edges(std::fstream& stream,
               edge_init_container& edges);

    //------------------------------------------------------------------------------
    ///
    /// @brief Parse string to produce edge initialization value.
    ///
    /// @param[in] input String containing edge data.
    ///
    /// @return Edge initialization value.
    ///
    //------------------------------------------------------------------------------
    edge_init_type
    parse_edge(std::string input);
};


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------
// (none)



//
#endif // FETCHER_H
//==============================================================================
// End of fetcher.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
