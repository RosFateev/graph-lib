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
#include <utility>              // std::move
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>            // std::for_each

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
        using vertex_structure      = std::map<vertex_type,
                                               int,
                                               component::support::vertex_hash<id_type>
                                               component::support::vertex_equal<id_type>>;
        using edge_type             = component::Edge<id_type>;
        using edge_container        = std::vector<edge_type>;
        using manager_type          = implementation::Manager;
        using vertex_init_type      = id_type;
        using edge_init_type        = std::tuple<id_type, int, int>;
        using init_list_type        = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        //using const_vertex_iterator = typename std::vector<vertex_ptr>::const_iterator;
        //using const_edge_iterator   = typename std::vector<edge_ptr>::const_iterator;

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
        edge_container
        GetNeighbours(id_type id) const;

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex.
        ///
        /// @param[in] vertex Input vertex.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------        
        edge_container
        GetNeighbours(const vertex_type& vertex) const;

        //------------------------------------------------------------------------------
        /// @brief Number of vertices in a graph.
        ///
        /// @return Vertex count.
        ///
        //------------------------------------------------------------------------------
        int
        Size() const;


    private:
        
        /// @brief Mapping user preferred vertices to internal indexes.
        vertex_structure vertexMap_;

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
    //  Go through initializer list filling vertexMap_ structure.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Graph<id_type>::Graph(
        std::initializer_list<typename Graph<id_type>::init_list_type>&& initList) : 
                manager_()
    {
        int index = 0;
        std::for_each(initList.begin(), initList.end(),
            [&vertexMap_, &index](const auto& initVertEdgeTuple)
            {
                vertexMap_.[
                    typename Graph<id_type>::vertex_type(
                        std::get<0>(initVertEdgeTuple) )] = index++;

                manager_.AddEdge()
            });
    }

    //------------------------------------------------------------------------------
    //
    //  Add vertex creates a new entry in map structure and implementation(s).
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddVertex(id_type id)
    {
        int index = vertexMap_.size();
        // add vertex to structure
        vertexMap_[typename Graph<id_type>::vertex_type(id)] = index;

        // add vertex to implementation
        manager_.AddVertex(index);
    }
    
    //------------------------------------------------------------------------------
    //
    //  Call AddVertex(id_type) method.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddVertex(const typename Graph<id_type>::vertex_type& vertex)
    {
        // call default method
        AddVertex(vertex.Id());
    }

    //------------------------------------------------------------------------------
    //
    //  Returns vertex from map structure if present.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::vertex_type&
    Graph<id_type>::GetVertex(id_type id) const
    {
        auto tpl = vertexMap_.find(typename Graph<id_type>::vertex_type(id));
        
        if ( (tpl != vertexMap_.end()) &&
             (tpl->second != -1) )
        {
            return tpl->first;
        }

        return component::traits::invalid;
    }

    //------------------------------------------------------------------------------
    //
    //  Mark as invalid in map structure and remove from implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveVertex(id_type id) 
    {
        // assign invalid value to structure
        vertexMap_.at(typename Graph<id_type>::vertex_type(id)) = -1;

        // remove from implementation
        manager_.RemoveVertex(id); 
    }

    //------------------------------------------------------------------------------
    //
    //  Look for proper indecies in structure and insert into implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddEdge(id_type id1,
                            id_type id2,
                            int direction,
                            int weight)
    {
        AddEdge(typename Graph<id_type>::vertex_type(id),
                typename Graph<id_type>::vertex_type(id),
                direction,
                weight);
    }

    //------------------------------------------------------------------------------
    //
    //  Look for proper indecies in structure and insert into implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::AddEdge(const typename Graph<id_type>::vertex_type& vertex1,
                            const typename Graph<id_type>::vertex_type& vertex2,
                            int direction,
                            int weight)
    {
        manager_.AddEdge(vertexMap_.at(vertex1),
                         vertexMap_.at(vertex2), direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  If edge exist in implementation - construct and return Edge object
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::edge_type&
    Graph<id_type>::GetEdge(id_type id1,
                            id_type id2,
                            int direction,
                            int weight) const
    {
        return GetEdge(typename Graph<id_type>::vertex_type(id1),
                       typename Graph<id_type>::vertex_type(id2),
                       direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  If edge exist in implementation - construct and return Edge object
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename Graph<id_type>::edge_type&
    Graph<id_type>::GetEdge(const typename Graph<id_type>::vertex_type&  vertex1,
                            const typename Graph<id_type>::vertex_type&  vertex2,
                            int direction,
                            int weight) const
    {
        // look for endpoints
        auto tpl1 = vertexMap_.find(vertex1);
        auto tpl2 = vertexMap_.find(vertex2);

        // if edge exists
        if (manager_.Edge(tpl1->second,
                          tpl2->second, direction, weight))
        {
            return typename Graph<id_type>::edge_type(tpl1->first,
                                                      tpl2->first,
                                                      direction, weight);
        }
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveEdge(id_type id1,
                               id_type id2,
                               int direction,
                               int weight)
    {
        RemoveEdge(typename Graph<id_type>::vertex_type(id1),
                   typename Graph<id_type>::vertex_type(id2),
                   direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Graph<id_type>::RemoveEdge(const typename Graph<id_type>::vertex_type& vertex1,
                               const typename Graph<id_type>::vertex_type& vertex2,
                               int direction,
                               int weight)
    {
        manager_.RemoveEdge(vertexMap_.at(vertex1),
                            vertexMap_.at(vertex2),
                            direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::edge_container
    Graph<id_type>::GetNeighbours(id_type id)
    { 
        return GetNeighbours(typename Graph<id_type>::vertex_type(id));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename Graph<id_type>::edge_container
    Graph<id_type>::GetNeighbours(const typename Graph<id_type>::vertex_type& vertex) const
    {
        // resulting container
        typename Graph<id_type>::edge_container neighbours;
        // fetch from implementation
        auto mNeighbours = manager_.GetNeighbours(vertexMap_.at(vertex));

        std::for_each(mNeighbours.begin(), mNeighbours.end(),
            [&neighbours](const auto& intEdge)
            {
                neighbours.push_back(
                    typename Graph<id_type>::edge_type(
                        vertex,
                        typename Graph<id_type>::vertex_type(intEdge.GetVertex(1)),
                        intEdge.GetDirection(),
                        intEdge.GetWeight())
                    );
            });
        
        return neighbours;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    int
    Graph<id_type>::Size() const
    {
        int length = 0;

        // if value is -1 => vertex is invalid
        std::for_each(vertexMap_.begin(), vertexMap_.end(),
            [&length](const auto& kvPair)
            { kvPair->second != -1 ? ++length : length; });

        return length;
    }


} //    namespace graph



#endif // GRAPH_LIB_GRAPH_HPP
//==============================================================================
// End of graph.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
