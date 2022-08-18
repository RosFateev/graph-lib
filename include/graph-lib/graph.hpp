//==============================================================================
///
/// @file graph.hpp
///
/// @brief Graph implementation.
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
#ifndef GRAPH_LIB_GRAPH_HPP
#define GRAPH_LIB_GRAPH_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <initializer_list>
#include <utility>                      // std::move

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/implementation/manager.hpp>


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
/// @brief Graph related classes.
//------------------------------------------------------------------------------
namespace graph
{
    //------------------------------------------------------------------------------
    /// @brief Graph class.
    ///
    /// A structured collection of vertices and edges.
    //------------------------------------------------------------------------------
    template<class id_type>
    class Graph
    {
        using vertex_type           = component::Vertex<id_type>;
        using vertex_ptr            = std::shared_ptr<vertex_type>;
        using edge_type             = component::Edge<id_type>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        //using edge_container        = std::vector<edge_type>;
        using manager_type          = implementation::Manager<id_type>;
        using vertex_init_type      = id_type;
        using edge_init_type        = std::tuple<id_type, int, int>;
        using init_list_type        = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        using const_vertex_iterator = typename std::vector<vertex_ptr>::const_iterator;
        using const_edge_iterator   = typename std::vector<edge_ptr>::const_iterator;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor.
        ///
        /// Creates an empty graph instance.
        //------------------------------------------------------------------------------
        Graph();
        
        //------------------------------------------------------------------------------
        /// @brief Initializer list constructor.
        ///
        /// Creates a graph instance from initializer list of type: 
        /// {
        ///     { vertex_id, { 
        ///           { neighbour1_id, direction, weight},
        ///           ...
        ///           { neighbourM_id, direction, weight} } 
        ///     },
        ///     { vertex2_id, {...} },
        ///     ...
        ///     { vertexR_id, {...} }
        /// }
        ///
        /// @param[in] initList Initializer list.
        ///
        //------------------------------------------------------------------------------
        Graph(std::initializer_list<init_list_type>&& initList);

        //------------------------------------------------------------------------------
        /// @brief Adds vertex with specefic id to a graph.
        /// 
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        AddVertex(id_type id);

        //------------------------------------------------------------------------------
        /// @brief Adds a copy of vertex to a graph.
        ///
        /// @param[in] vertex Vertex to copy.
        ///
        //------------------------------------------------------------------------------
        void
        AddVertex(const vertex_type& vertex);
        
        //------------------------------------------------------------------------------
        /// @brief Gets vertex with specific id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Vertex with given id.
        ///
        //------------------------------------------------------------------------------
        const vertex_type&
        GetVertex(id_type id) const;

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from a graph.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveVertex(id_type id);
        
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
        AddEdge(id_type id1,
                id_type id2,
                int direction = component::traits::edge_direction::none,
                int weight = 0);

        //------------------------------------------------------------------------------
        /// @brief Adds edge connecting two given vertices to a graph.
        ///
        /// @param[in] vertex1 First vertex.
        ///
        /// @param[in] vertex2 Second vertex.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        //------------------------------------------------------------------------------
        void
        AddEdge(const vertex_type& vertex1,
                const vertex_type& vertex2,
                int direction = component::traits::edge_direction::none,
                int weight = 0);

        //------------------------------------------------------------------------------
        /// @brief Finds edge in a graph using given vertex ids and returns it.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @return Desired edge.
        ///
        //------------------------------------------------------------------------------
        const edge_type&
        GetEdge(id_type id1,
                id_type id2,
                int direction = component::traits::edge_direction::none,
                int weight = 0) const;

        //------------------------------------------------------------------------------
        /// @brief Finds edge in a graph using input vertices and returns it.
        ///
        /// @param[in] vertex1 First vertex.
        ///
        /// @param[in] vertex2 Second vertex.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @return Desired edge.
        ///
        //------------------------------------------------------------------------------
        const edge_type&
        GetEdge(const vertex_type& vertex1,
                const vertex_type& vertex2,
                int direction = component::traits::edge_direction::none,
                int weight = 0) const;

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
        RemoveEdge(id_type id1,
                   id_type id2,
                   int direction = component::traits::edge_direction::none,
                   int weight = 0);

        //------------------------------------------------------------------------------
        /// @brief Removes edge from a graph using input vertices.
        ///
        /// @param[in] vertex1 First vertex.
        ///
        /// @param[in] vertex2 Second vertex.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveEdge(const vertex_type& vertex1,
                   const vertex_type& vertex2,
                   int direction = component::traits::edge_direction::none,
                   int weight = 0);

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(id_type id) const;

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex.
        ///
        /// @param[in] vertex Input vertex.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------        
        const edge_container&
        GetNeighbours(const vertex_type& vertex) const;


        /*
        //------------------------------------------------------------------------------
        /// @brief v_begin.
        ///
        /// Returns iterator to the beginning of vertex container to enable iteration (like container.begin()).
        /// @return constant vertex container iterator to the beginning
        //------------------------------------------------------------------------------
        const_vertex_iterator       v_begin() const;

        //------------------------------------------------------------------------------
        /// @brief v_end.
        ///
        /// Returns iterator to the end of vertex container to enable iteration (like container.end()).
        /// @return constant vertex container iterator to the end
        //------------------------------------------------------------------------------
        const_vertex_iterator       v_end() const;

        //------------------------------------------------------------------------------
        /// @brief e_begin.
        ///
        /// Returns iterator to the beginning of edge container to enable iteration (like container.begin()).
        /// @return constant edge container iterator to the beginning
        //------------------------------------------------------------------------------
        const_edge_iterator         e_begin() const;

        //------------------------------------------------------------------------------
        /// @brief e_end.
        ///
        /// Returns iterator to the end of edge container to enable iteration (like container.end()).
        /// @return constant edge container iterator to the end
        //------------------------------------------------------------------------------
        const_edge_iterator         e_end() const;
        */

        //------------------------------------------------------------------------------
        /// @brief Number of vertices in a graph.
        ///
        /// @return Vertex count.
        ///
        //------------------------------------------------------------------------------
        int
        Size() const;


    private:
        
        /// @brief Internal structures manager.
        manager_type    manager_;
    };

} // namespace graph


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------
namespace graph
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Graph<id_type>::Graph()
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Graph<id_type>::Graph(   std::initializer_list<typename Graph<id_type>::init_list_type>&& inList) : manager_(std::move(inList))
    {   }   

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddVertex(id_type   id)
    {
        manager_.AddVertex(id);
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddVertex(const typename Graph<id_type>::vertex_type&     vertex)
    {
        manager_.AddVertex(vertex);
    }
    /*
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>  
    void        Graph<id_type>::AddVertex(  typename Graph<id_type>::vertex_type&&      vertex)
    {
        manager_.AddVertex(std::forward(vertex));
    }
    */

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::vertex_type&
    Graph<id_type>::GetVertex(  id_type  id) const
    {
        return manager_.GetVertex(id);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveVertex(  id_type     id) 
    { 
        manager_.RemoveVertex(id); 
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddEdge(id_type     id1,
                            id_type     id2,
                            int         direction,
                            int         weight)
    {
        manager_.AddEdge(id1, id2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddEdge(const typename Graph<id_type>::vertex_type&  vertex1,
                            const typename Graph<id_type>::vertex_type&  vertex2,
                            int                                          direction,
                            int                                          weight)
    {
        manager_.AddEdge(vertex1, vertex2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::edge_type&
    Graph<id_type>::GetEdge(id_type     id1,
                            id_type     id2,
                            int         direction,
                            int         weight) const
    {
        return manager_.GetEdge(id1, id2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::edge_type&
    Graph<id_type>::GetEdge(const typename Graph<id_type>::vertex_type&  vertex1,
                            const typename Graph<id_type>::vertex_type&  vertex2,
                            int                                          direction,
                            int                                          weight) const
    {
        return manager_.GetEdge(vertex1, vertex2, direction, weight);
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveEdge( id_type     id1,
                                            id_type     id2,
                                            int         direction,
                                            int         weight)
    {
        manager_.RemoveEdge(id1, id2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveEdge(     const typename Graph<id_type>::vertex_type&  vertex1,
                                                const typename Graph<id_type>::vertex_type&  vertex2,
                                                int                                          direction,
                                                int                                          weight)
    {
        manager_.RemoveEdge(vertex1, vertex2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::edge_container&    Graph<id_type>::GetNeighbours(   ArgT&& inArg)
    { 
        return manager_.Neighbours(std::forward<ArgT>(inArg));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::edge_container&    Graph<id_type>::GetNeighbours(   ArgT&& inArg) const
    { 
        return manager_.Neighbours(std::forward<ArgT>(inArg));
    }

    /*
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::const_vertex_iterator      Graph<id_type>::v_begin() const
    {
        return manager_.v_begin();
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::const_vertex_iterator      Graph<id_type>::v_end() const
    {
        return manager_.v_end();
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::const_edge_iterator      Graph<id_type>::e_begin() const
    {
        return manager_.e_begin();
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::const_edge_iterator      Graph<id_type>::e_end() const
    {
        return manager_.e_end();
    }
    */

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    int
    Graph<id_type>::Size() const
    {
        return manager_.Size();
    }



} //    namespace graph



#endif // GRAPH_LIB_GRAPH_HPP
//==============================================================================
// End of graph.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
