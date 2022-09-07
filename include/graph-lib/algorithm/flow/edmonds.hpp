//==============================================================================
///
/// @file edmonds.hpp
///
/// @brief Edmonds-Karp max flow in a graph.
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
#ifndef GRAPH_LIB_ALGORITHM_FLOW_EDMONDS_HPP
#define GRAPH_LIB_ALGORITHM_FLOW_EDMONDS_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <queue>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/algorithm/traversal/bfs.hpp"    // bfs


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
/// @brief Common graph algorithms.
///
//------------------------------------------------------------------------------
namespace algorithm
{
    //------------------------------------------------------------------------------
    /// @brief Edmonds-Karp implementation.
    ///
    //------------------------------------------------------------------------------
    template<class id_type>
    class edmonds_karp
    {
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using parent_structure      = std::map<vertex_type,
                                               vertex_type,
                                               component::support::vertex_less<id_type>>;
        using graph_type            = graph::Graph<id_type>;

    public:

        //------------------------------------------------------------------------------
        ///
        /// @brief Value constructor.
        ///
        /// @param[in] pGraph Input graph pointer.
        ///
        //------------------------------------------------------------------------------
        edmonds_karp(const graph_type* pGraph);

        //------------------------------------------------------------------------------
        ///
        /// @brief Execute Edmonds-Karp algorithm.
        ///
        /// @param[in] source Flow start vertex.
        ///
        /// @param[in] sink Flow end vertex.
        ///
        //------------------------------------------------------------------------------
        void
        run(const vertex_type& source,
            const vertex_type& sink);

        //------------------------------------------------------------------------------
        ///
        /// @brief Get algorithm execution results.
        ///
        /// @return Reference to parent structure defining order.
        ///
        //------------------------------------------------------------------------------
        const parent_structure&
        get();

        //------------------------------------------------------------------------------
        ///
        /// @brief Get algorithm's graph.
        ///
        /// @return Reference to graph object.
        ///
        //------------------------------------------------------------------------------
        const graph_type*
        get_graph();


    private:

        //------------------------------------------------------------------------------
        ///
        /// @brief Edmonds-Karp algorithm implementation.
        ///
        /// @param[in] source Flow start vertex.
        ///
        /// @param[in] sink Flow end vertex.
        ///
        //------------------------------------------------------------------------------
        void
        edmonds_karp_inner(const vertex_type& source,
                           const vertex_type& sink);



    private:

        /// @brief Parent structure.
        parent_structure structure_;

        /// @brief Graph.
        const graph_type* pGraph_;
    };

} // namespace algorithm



//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
///
/// @brief <Description>
///
/// @param[in] <name> <Description>
///
/// @param[in,out] <name> <Description>
///
/// @param[out] <name> <Description>
///
/// @return <Description>
/// @retval <Value i> <Description>
///
//------------------------------------------------------------------------------
<data type> <function name>(...);


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Algorithms namespace
//
//------------------------------------------------------------------------------
namespace algorithm
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    edmonds_karp<id_type>::dfs(
            const typename edmonds_karp<id_type>::graph_type* pGraph) : pGraph_(pGraph)
    {
        flush_structure();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    edmonds_karp<id_type>::run(
            const typename edmonds_karp<id_type>::vertex_type& source,
            const typename edmonds_karp<id_type>::vertex_type& sink)
    {
        edmonds_karp_inner(source, sink);
        //dfs_stack(root);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename edmonds_karp<id_type>::parent_structure&
    edmonds_karp<id_type>::get()
    {
        return structure_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename edmonds_karp<id_type>::graph_type*
    edmonds_karp<id_type>::get_graph()
    {
        return pGraph_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    edmonds_karp<id_type>::flush_structure()
    {
        // initialize parent structure: insert <vertex, invalid_vertex> entries,
        // where vertex - vertex of the graph
        std::for_each(pGraph_->cbegin(), pGraph_->cend(),
            [this](const auto& tuple)
            {
                structure_[tuple.first] = 
                    component::Vertex<id_type>::invalidInstance_;
            });
    }





    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    bool
    edmonds_karp<id_type>::is_discovered(const typename edmonds_karp<id_type>::vertex_type& vertex)
    {
        // Discovered: parent structure contains valid entry for the second endpoint
        return (structure_.at(vertex) != 
                component::Vertex<id_type>::invalidInstance_);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    edmonds_karp<id_type>::edmonds_karp_inner(
            const typename edmonds_karp<id_type>::vertex_type& source,
            const typename edmonds_karp<id_type>::vertex_type& sink)
    {
        int flow = 0;

        while (true)
        {
            // run BFS
            bfs<id_type> bfsObj(pGraph_);
            bfsObj.run(source);

            // augmenting path found
            if (bfsObj.get().at(sink) != NULL)
            {
                int possibleFlow = INT_MAX;
                // determine max flow possible to send
                for (auto edge : predecessor sink)
                {
                    if (edge != NULL)
                }
                // "send" this flow
                for (;;)
                {

                }
                // update
                flow += possibleFlow;
            }
            else
            {
                // algorithm finish
                break;
            }
        }
        
    }
}



#endif // GRAPH_LIB_ALGORITHM_FLOW_EDMONDS_HPP
//==============================================================================
// End of edmonds.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
