//==============================================================================
///
/// @file dinic.hpp
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
#ifndef GRAPH_LIB_ALGORITHM_FLOW_DINIC_HPP
#define GRAPH_LIB_ALGORITHM_FLOW_DINIC_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <limits>               // std::numeric_limits

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/vertex.hpp"   // component::Vertex
#include "graph-lib/utility/print.hpp"      // Debug printing

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
    /// @brief Dinic algorithm implementation.
    ///
    //------------------------------------------------------------------------------
    template<class id_type>
    class dinic
    {
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using level_structure       = std::map<vertex_type,
                                               int,
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
        dinic(graph_type * const pGraph);

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
        int
        get() const;

        //------------------------------------------------------------------------------
        ///
        /// @brief Get algorithm's graph.
        ///
        /// @return Reference to graph object.
        ///
        //------------------------------------------------------------------------------
        graph_type * const
        get_graph();


    private:

        //------------------------------------------------------------------------------
        ///
        /// @brief Reset level structure.
        ///
        //------------------------------------------------------------------------------
        void
        flush_structure();

        //------------------------------------------------------------------------------
        ///
        /// @brief Compute level graph.
        ///
        /// @param[in] root Start vertex.
        ///
        //------------------------------------------------------------------------------
        void
        compute_level_structure(const vertex_type& root);

        //------------------------------------------------------------------------------
        ///
        /// @brief Send max possible flow from source to sink on a path.
        ///
        /// @param[in] vertex Current vertex.
        ///
        /// @param[in] sink End vertex.
        ///
        /// @param[in] flow Current flow.
        ///
        /// @return Improving flow.
        ///
        //------------------------------------------------------------------------------
        int
        send_flow(const vertex_type& vertex,
                  const vertex_type& sink,
                  int flow);

        //------------------------------------------------------------------------------
        ///
        /// @brief Dinic algorithm implementation.
        ///
        /// @param[in] source Flow start vertex.
        ///
        /// @param[in] sink Flow end vertex.
        ///
        //------------------------------------------------------------------------------
        void
        dinic_inner(const vertex_type& source,
                    const vertex_type& sink);



    private:

        /// @brief Max flow possible to send over the network.
        int flow_;

        //------------------------------------------------------------------------------
        /// @brief Level graph structure.
        ///
        /// Contains <vertex, <predecessor, vertex_level>> key-value pairs.
        ///
        //------------------------------------------------------------------------------
        level_structure level_;

        /// @brief Graph.
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
    dinic<id_type>::dinic(
            typename dinic<id_type>::graph_type * const pGraph) : pGraph_(pGraph),
                                                                  flow_(0)
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
    dinic<id_type>::run(
            const typename dinic<id_type>::vertex_type& source,
            const typename dinic<id_type>::vertex_type& sink)
    {
        dinic_inner(source, sink);
        //dfs_stack(root);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    int
    dinic<id_type>::get() const
    {
        return flow_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename dinic<id_type>::graph_type * const
    dinic<id_type>::get_graph()
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
    dinic<id_type>::flush_structure()
    {
        // initialize parent structure: insert <vertex, large_const> entries,
        // where vertex - vertex of the graph
        std::for_each(pGraph_->cbegin(), pGraph_->cend(),
            [this](const auto& tuple)
            {
                level_[tuple.first] = std::numeric_limits<int>::max();
            });
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    dinic<id_type>::compute_level_structure(
            const typename dinic<id_type>::vertex_type& root)
    {
        // reset level structure
        flush_structure();

        // run bfs on vertices
        int currentLevel = 0;
        std::queue<typename dinic<id_type>::vertex_type> queue;
        queue.push(root);
        level_[root] = currentLevel;

        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();

            //DEBUG
            std::cout << "Current vertex in level BFS is ";
            print_vertex<id_type>(current);
            std::cout << '\n';
            //DEBUG

            for (auto& neighbourEdge : pGraph_->GetNeighbours(current))
            {
                // check if vertex level can be updated
                if ( (level_.at(current) + 1 < level_.at(neighbourEdge.GetVertex(1))) &&
                     (neighbourEdge.GetCapacity() - neighbourEdge.GetFlow() > 0) )
                {
                    //DEBUG
                    std::cout << "Current valid neighbour connection is ";
                    print_edge<id_type>(neighbourEdge);
                    std::cout << '\n';
                    //DEBUG

                    // update level
                    level_[neighbourEdge.GetVertex(1)] = level_.at(current) + 1;
                    // enqueue
                    queue.push(neighbourEdge.GetVertex(1));
                }
            }
        }

        //DEBUG
        std::cout << "Computed level structure is \n";
        print_level_structure<id_type>(level_);
        //DEBUG
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    int
    dinic<id_type>::send_flow(
            const typename dinic<id_type>::vertex_type& vertex,
            const typename dinic<id_type>::vertex_type& sink,
            int flow)
    {
        // no path exists
        if (flow == 0)
        {
            return 0;
        }
        // reached destination
        if (vertex == sink)
        {
            return flow;
        }

        // proceed with children
        for (auto& neighbourEdge : pGraph_->GetNeighbours(vertex))
        {
            auto& neighbourVertex = neighbourEdge.GetVertex(1);
            int residualCapacity = neighbourEdge.GetCapacity() - neighbourEdge.GetFlow();

            //DEBUG
            std::cout << "Current neighbour is ";
            print_vertex<id_type>(neighbourVertex);
            std::cout << '\n';
            //DEBUG

            // neighbour to skip
            if ( (level_.at(neighbourVertex) != level_.at(vertex) + 1) ||
                 (residualCapacity < 1) )
            {
                //DEBUG
                std::cout << "  Neighbour is not valid\n";
                //DEBUG

                continue;
            }

            // try to send flow to a valid neighbour
            int tempFlow = send_flow(neighbourVertex, sink,
                    std::min(flow, residualCapacity));

            //DEBUG
            std::cout << "  Neighbour flow computed is " << tempFlow << '\n';
            //DEBUG

            // failed
            if (tempFlow == 0)
            {
                continue;
            }

            //DEBUG
            std::cout << "Update edge flow\n";
            //DEBUG

            // update connection edge flow
            neighbourEdge.SetFlow(neighbourEdge.GetFlow() + tempFlow);

            return tempFlow;
        }

        return 0;
    }


    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    dinic<id_type>::dinic_inner(
            const typename dinic<id_type>::vertex_type& source,
            const typename dinic<id_type>::vertex_type& sink)
    {
        int flow = 0;
        int blockingFlow = 0;

        while (true)
        {
            // construct level graph
            compute_level_structure(source);

            // no path to sink exists - exit
            if (level_.at(sink) == std::numeric_limits<int>::max())
            {
                break;
            }

            //DEBUG
            std::cout << "Level Structure computed - Find blocking flow\n";
            //DEBUG

            // find blocking flow f'
            blockingFlow = std::numeric_limits<int>::max();
            while ((blockingFlow = send_flow(source, sink, std::numeric_limits<int>::max())) != 0)
            {
                //DEBUG
                std::cout << "Current found blocking flow is " << blockingFlow << '\n';
                //DEBUG

                // increment total flow f
                flow += blockingFlow;
            }
        }

        flow_ = flow;
    }
} // namespace algorithm



#endif // GRAPH_LIB_ALGORITHM_FLOW_DINIC_HPP
//==============================================================================
// End of dinic.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
