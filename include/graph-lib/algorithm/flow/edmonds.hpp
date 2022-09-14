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
#include <limits>               // std::numeric_limits

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/algorithm/traversal/bfs.hpp"    // algorithm::bfs
#include "graph-lib/utility/print.hpp"              // Debug printing


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
    /// @brief Edmonds-Karp algorithm implementation.
    ///
    //------------------------------------------------------------------------------
    template<class id_type>
    class edmonds_karp
    {
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using graph_type            = graph::Graph<id_type>;

    public:

        //------------------------------------------------------------------------------
        ///
        /// @brief Value constructor.
        ///
        /// @param[in] pGraph Input graph pointer.
        ///
        //------------------------------------------------------------------------------
        edmonds_karp(graph_type * const pGraph);

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
        /// @return Flow value.
        ///
        //------------------------------------------------------------------------------
        int
        get() const;

        //------------------------------------------------------------------------------
        ///
        /// @brief Get algorithm's graph.
        ///
        /// @return Reference to graph object.
        ///
        //------------------------------------------------------------------------------
        const graph_type*
        get_graph() const;


    private:

        //------------------------------------------------------------------------------
        ///
        /// @brief Reset parent structure.
        ///
        //------------------------------------------------------------------------------
        void
        flush_structure();

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

        /// @brief Max flow possible to send over the network.
        int flow_;

        /// @brief Graph pointer.
        graph_type * const pGraph_;
    };

} // namespace algorithm



//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------


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
    edmonds_karp<id_type>::edmonds_karp(
            typename edmonds_karp<id_type>::graph_type * const pGraph) : pGraph_(pGraph),
                                                                         flow_(0)
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
    int
    edmonds_karp<id_type>::get() const
    {
        return flow_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename edmonds_karp<id_type>::graph_type*
    edmonds_karp<id_type>::get_graph() const
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
        // initialize edge flow
        std::for_each(pGraph_->begin(), pGraph_->end(),
            [](auto& tuple)
            {
                std::for_each(tuple.second.begin(), tuple.second.end(),
                    [](auto& edge)
                    {
                        edge.SetFlow(0);
                    });
            });
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
        int incrementingFlow = 0;

        while (true)
        {
            //DEBUG
            std::cout << "Run BFS\n";
            //DEBUG

            // run bfs_flow()
            bfs<id_type> bfsObj(pGraph_);
            bfsObj.run(source, "flow");

            //DEBUG
            print_traversal_result<id_type>(bfsObj.get());
            //DEBUG

            // augmenting path found
            if (bfsObj.get().at(sink) != component::Vertex<id_type>::invalidInstance_)
            {
                //DEBUG
                std::cout << "Compute network flow increase\n";
                //DEBUG

                incrementingFlow = std::numeric_limits<int>::max();
                // determine max possible increase to send via augmenting path edges found by BFS
                auto current = sink;
                while (current != source)
                {
                    // fetch connection edge
                    auto& edge = pGraph_->GetEdge(
                        bfsObj.get().at(current), current);

                    // check if incrementing flow can be updated
                    incrementingFlow = std::min(
                                incrementingFlow,
                                edge.GetCapacity() - edge.GetFlow());

                    // update current
                    current = edge.GetVertex(0);
                }

                //DEBUG
                std::cout << "Improving flow has value: " << incrementingFlow << '\n';
                //DEBUG

                // increment flow in all edges of augmenting path found by BFS
                current = sink;
                while (current != source)
                {
                    auto& edge = pGraph_->GetEdge(bfsObj.get().at(current), current);
                    // increment flow
                    edge.SetFlow(edge.GetFlow() + incrementingFlow);

                    // update current
                    current = edge.GetVertex(0);
                }

                // update
                flow += incrementingFlow;

                //DEBUG
                print_graph<id_type>(*pGraph_);
                //DEBUG
            }
            else
            {
                // algorithm finish
                break;
            }
        }

        flow_ = flow;
    }
} // namespace algorithm



#endif // GRAPH_LIB_ALGORITHM_FLOW_EDMONDS_HPP
//==============================================================================
// End of edmonds.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
