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

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/implementation/implementation-support.hpp>



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
    template<   class int>
    class Vertex;

    template<   class int>
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

        using vertex_type           = component::Vertex<int>;
        using vertex_ptr            = std::shared_ptr<vertex_type>;
        using edge_type             = component::Edge<int>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        using edge_container        = std::list<edge_ptr>;
        using vertex_init_container = std::vector<vertex_ptr>;
        using edge_init_container   = std::vector<edge_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor
        //------------------------------------------------------------------------------
        BaseImplementation()
        {}
        
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

        //------------------------------------------------------------------------------
        /// @brief Virtual destructor.
        //------------------------------------------------------------------------------
        virtual ~BaseImplementation() {};

        //------------------------------------------------------------------------------
        /// @brief Add vertex to implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddVertex(int id) = 0;

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
        GetVertex(int id) const = 0;

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        RemoveVertex(int id) = 0;

        //------------------------------------------------------------------------------
        /// @brief Add edge pointer to implementation.
        ///
        /// @param[in] pEdge Pointer to edge.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddEdge(const edge_ptr& pEdge) = 0;
        
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
        virtual const edge_ptr&
        GetEdge(int id1,
                int id2,
                int direction,
                int weight) const = 0;

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
        void
        RemoveEdge(int id1,
                   int id2,
                   int direction,
                   int weight); = 0;

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(int id) const = 0;

    };

} // namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_IMPLEMENTATION_H
//==============================================================================
// End of implementation.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
