//==============================================================================
///
/// @file implementation.h
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
#ifndef GRAPH_LIB_IMPLEMENTATION_IMPLEMENTATION_H
#define GRAPH_LIB_IMPLEMENTATION_IMPLEMENTATION_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <list>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/edge.hpp"
#include "graph-lib/implementation/implementation-support.hpp"



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
namespace component
{
    template<   class id_type>
    class Vertex;

    template<   class id_type>
    class Edge;
}


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief <Description>
///
/// <Detailed description>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief Implementation related classes and functions.
//------------------------------------------------------------------------------
namespace implementation
{
    //------------------------------------------------------------------------------
    /// @brief Base abstract implementation class. 
    //------------------------------------------------------------------------------
    class BaseImplementation
    {
        using edge_type             = component::Edge<int>;
        using edge_container        = std::list<edge_type>;
        //using vertex_init_container = std::vector<vertex_ptr>;
        //using edge_init_container   = std::vector<edge_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor
        //------------------------------------------------------------------------------
        BaseImplementation();
        
        /*
        //------------------------------------------------------------------------------
        /// @brief Value constructor
        ///
        /// @param[in]
        ///
        /// @param[in]
        ///
        //------------------------------------------------------------------------------
        BaseImplementation(const vertex_init_container&, 
                           const edge_init_container&) {}
        */

        //------------------------------------------------------------------------------
        /// @brief Virtual destructor.
        //------------------------------------------------------------------------------
        virtual ~BaseImplementation();

        //------------------------------------------------------------------------------
        /// @brief Add vertex to implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddVertex(int id);

        /*
        //------------------------------------------------------------------------------
        /// @brief Confirms if vertex exists.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @retval True if Vertex exists.
        /// @retval False if Vertex doesn't exist.
        ///
        //------------------------------------------------------------------------------
        virtual bool
        GetVertex(int id) const;
        */

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        RemoveVertex(int id);

        //------------------------------------------------------------------------------
        /// @brief Add edge to implementation.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddEdge(int id1,
                int id2,
                component::traits::edge_direction direction,
                int weight);
        
        //------------------------------------------------------------------------------
        /// @brief Get edge pointer for given vertex ids.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @return Pointer to desired edge.
        ///
        //------------------------------------------------------------------------------
        virtual bool
        Edge(int id1,
             int id2,
             component::traits::edge_direction direction,
             int weight) const;

        //------------------------------------------------------------------------------
        /// @brief Removes edge pointer with given vertex ids.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        //------------------------------------------------------------------------------
        virtual void
        RemoveEdge(int id1,
                   int id2,
                   component::traits::edge_direction direction,
                   int weight);

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        virtual const edge_container&
        GetNeighbours(int id) const;

    };

} // namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_IMPLEMENTATION_H
//==============================================================================
// End of implementation.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
