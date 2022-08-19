//==============================================================================
///
/// @file manager.h
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
#ifndef GRAPH_LIB_IMPLEMENTATION_MANAGER_H
#define GRAPH_LIB_IMPLEMENTATION_MANAGER_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <initializer_list>
#include <utility>              // std::move
#include <tuple>
#include <algorithm>            // std::find

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/implementation/adjacency-list.hpp>
#include <graph-lib/implementation/incidence-matrix.hpp>

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
    /// @brief Implements graph's functionality.
    ///
    /// Contains vertex and edge container and indices (implementations) over them.
    //------------------------------------------------------------------------------
    class Manager
    {
        //type aliases
        using edge_type                 = component::Edge<int>;
        using edge_container            = std::vector<edge_type>;
        using vertex_init_type          = int;
        using edge_init_type            = std::tuple<int, int, int>;
        using init_list_type            = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        using base_implementation       = BaseImplementation<int>;
        using implementation_ptr        = std::unique_ptr<base_implementation>;
        using implementation_container  = std::vector<implementation_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor.
        //------------------------------------------------------------------------------
        Manager();

        //------------------------------------------------------------------------------
        /// @brief Initializer list constructor.
        ///
        /// @param[in] initList
        ///
        //------------------------------------------------------------------------------
        Manager(std::initializer_list<init_list_type>&& initList);

        //------------------------------------------------------------------------------
        /// @brief Adds vertex with specefic id to a graph.
        /// 
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        AddVertex(int id);

        /*
        //------------------------------------------------------------------------------
        /// @brief Gets vertex with specific id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @retval True if Vertex exists.
        /// @retval False if Vertex doesn't exist.
        ///
        //------------------------------------------------------------------------------   
        bool
        GetVertex(int id) const;
        */

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from a graph.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveVertex(int id);
        
        //------------------------------------------------------------------------------
        /// @brief Adds edge connecting two vertices with specific ids to a graph.
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
        AddEdge(int id1,
                int id2,
                int direction,
                int weight);

        //------------------------------------------------------------------------------
        /// @brief Confirm edge existence using given vertex ids.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @retval True Edge exists.
        /// @retval False Otherwise.
        ///
        //------------------------------------------------------------------------------
        bool
        Edge(int id1,
             int id2,
             int direction,
             int weight) const;

        //------------------------------------------------------------------------------
        /// @brief Removes edge from a graph using input vertex ids.
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
                   int weight);

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(int id) const;

        /*
        //------------------------------------------------------------------------------
        /// @brief Number of vertices in a graph.
        ///
        /// @return Vertex count.
        ///
        //------------------------------------------------------------------------------
        int
        Size() const;
        */

    private:

        //------------------------------------------------------------------------------
        /// @brief Adds new implementation to a graph.
        ///
        /// @param[in] pImpl Implementation pointer.
        ///
        //------------------------------------------------------------------------------
        void
        AddImplementation(implementation_ptr pImpl);

        //------------------------------------------------------------------------------
        /// @brief Remove implementation with a given index from a graph.
        ///
        /// @param[in] index Implementation storage index.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveImplementation(int index);

        //------------------------------------------------------------------------------
        /// @brief Sets new index of active implementation.
        ///
        /// @param[in] index Implementation storage index.
        ///
        //------------------------------------------------------------------------------  
        void
        ChangeImplementation(int index);


    private:

        /// @brief Index of active implementation.
        int activeIndex_;

        /// @brief Implementation container.
        implementation_container implementations_;
    };

} //    namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_MANAGER_H
//==============================================================================
// End of manager.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
