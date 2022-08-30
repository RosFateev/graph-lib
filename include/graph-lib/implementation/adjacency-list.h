//==============================================================================
///
/// @file adjacency-list.h
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
#ifndef GRAPH_LIB_IMPLEMENTATION_ADJACENCY_LIST_H
#define GRAPH_LIB_IMPLEMENTATION_ADJACENCY_LIST_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <initializer_list>
#include <vector>
#include <list>
#include <algorithm>                // std::for_each, std::find

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/edge.hpp"
#include "graph-lib/implementation/implementation.h"


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
/// @brief Implementation related classes and functions.
//------------------------------------------------------------------------------
namespace implementation
{
    //------------------------------------------------------------------------------
    /// @brief An implementation of adjacency list structure.
    //------------------------------------------------------------------------------
    class AdjacencyList : public BaseImplementation
    {
        using edge_type             = component::Edge<int>;
        using edge_container        = std::list<edge_type>;
        using data_structure        = std::vector<edge_container>;
        //using vertex_init_container = std::vector<int>;
        //using edge_init_container   = std::vector<edge_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor
        //------------------------------------------------------------------------------
        AdjacencyList();
        
        /*
        //------------------------------------------------------------------------------
        /// @brief Value constructor
        ///
        /// @param[in]
        ///
        /// @param[in]
        ///
        //------------------------------------------------------------------------------
        AdjacencyList(const vertex_init_container&, 
                      const edge_init_container&);
        */

        //------------------------------------------------------------------------------
        /// @brief Virtual destructor.
        //------------------------------------------------------------------------------
        virtual ~AdjacencyList();

        //------------------------------------------------------------------------------
        /// @brief Add vertex to adjacency list.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddVertex(int id) override;

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
        GetVertex(int id) const override;
        */

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        RemoveVertex(int id) override;

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
                int weight) override;
        
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
             int weight) const override;

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
                   component::traits::edge_direction direction,
                   int weight) override;

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(int id) const override;


    private:
        
        /// @brief Indicates if AdjacencyList object needs to be updated.
        bool isValid_;

        /// @brief Adjacency list container.
        data_structure list_;

    };

} // namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_ADJACENCY_LIST_H
//==============================================================================
// End of adjacency-list.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
