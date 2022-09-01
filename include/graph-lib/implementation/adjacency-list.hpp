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
#include <list>
#include <map>
#include <algorithm>                // std::for_each, std::find

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
    template<class id_type>
    class AdjacencyList
    {
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
    
    public:

        using edge_container        = std::list<edge_type>;


    private:

        using map_type              = std::map<vertex_type,
                                               edge_container,
                                               component::support::vertex_less<id_type>>;
        //using vertex_init_container = std::vector<int>;
        //using edge_init_container   = std::vector<edge_ptr>;

    public:

        using const_iterator        = typename map_type::const_iterator;

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
        /// @brief Add vertex to adjacency list.
        ///
        /// @param[in] vertex Vertex.
        ///
        //------------------------------------------------------------------------------
        void
        AddVertex(const vertex_type& vertex);

        //------------------------------------------------------------------------------
        /// @brief Get vertex from adjacency list.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Vertex.
        ///
        //------------------------------------------------------------------------------
        const vertex_type&
        GetVertex(id_type id) const;

        //------------------------------------------------------------------------------
        /// @brief Removes vertex from adjacency list.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveVertex(const vertex_type& id);

        //------------------------------------------------------------------------------
        /// @brief Add edge to adjacency list.
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
                component::traits::edge_direction direction,
                int weight);
        
        //------------------------------------------------------------------------------
        /// @brief Get edge pointer for given vertices.
        ///
        /// @param[in] vertex1 First vertex.
        ///
        /// @param[in] vertex2 Second vertex.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @return Pointer to desired edge.
        ///
        //------------------------------------------------------------------------------
        const edge_type&
        GetEdge(const vertex_type& vertex1,
                const vertex_type& vertex2,
                component::traits::edge_direction direction,
                int weight) const;

        //------------------------------------------------------------------------------
        /// @brief Removes edge pointer with given vertices.
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
                   component::traits::edge_direction direction,
                   int weight);

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the given vertex.
        ///
        /// @param[in] vertex Vertex.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(const vertex_type& vertex) const;

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the beginning of vertex map structure.
        ///
        /// @return map_type cbegin() iterator.
        ///
        //------------------------------------------------------------------------------        
        const_iterator
        cbegin() const;

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the end of vertex map structure.
        ///
        /// @return map_type cend() iterator.
        ///
        //------------------------------------------------------------------------------        
        const_iterator
        cend() const;

        //------------------------------------------------------------------------------
        /// @brief Number of vertices in a graph.
        ///
        /// @return Vertex count.
        ///
        //------------------------------------------------------------------------------
        int
        Size() const;


    private:

        /// @brief Adjacency list container.
        map_type list_;

    };

} // namespace implementation



//------------------------------------------------------------------------------
// Global references
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------
namespace implementation
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    AdjacencyList<id_type>::AdjacencyList() : list_()
    {   }

    /*
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    AdjacencyList<id_type>::AdjacencyList(
        const typename AdjacencyList<id_type>::vertex_init_container& vertices, 
        const typename AdjacencyList<id_type>::edge_init_container& edges) : is_valid_(true)
    {
        // push vertices
        for (auto vertex_iter = vertices.begin(); vertex_iter != vertices.end(); ++vertex_iter)
        {
            list_[(*vertex_iter)->Id()] = typename AdjacencyList<id_type>::edge_container();
        }

        // push edges
        for (auto edge_iter = edges.begin(); edge_iter != edges.end(); ++edge_iter)
        {
            list_.at((*edge_iter)->GetVertex(0).Id()).push_back(*edge_iter);
        }
    }
    */


    //------------------------------------------------------------------------------
    //
    //  Push empty edge container.
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    AdjacencyList<id_type>::AddVertex(
            const typename AdjacencyList<id_type>::vertex_type& vertex)
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::AddVertex(vertex_type):" << '\n';
        std::cout << "Adding vertex with index - " << vertex.Id() << std::endl;
        //DEBUG

        list_[vertex] = typename AdjacencyList<id_type>::edge_container();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename AdjacencyList<id_type>::vertex_type&
    AdjacencyList<id_type>::GetVertex(id_type id) const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::GetVertex(id_type):" << '\n';
        //DEBUG

        return list_.find(
            typename AdjacencyList<id_type>::vertex_type(id))->first;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    AdjacencyList<id_type>::RemoveVertex(
        const typename AdjacencyList<id_type>::vertex_type& vertex)
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::RemoveVertex(id_type):" << '\n';
        std::cout << "Removing vertex with id - " << vertex.Id() << '\n';
        //DEBUG

        list_.erase(list_.find(vertex));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    AdjacencyList<id_type>::AddEdge(
            const typename AdjacencyList<id_type>::vertex_type& vertex1,
            const typename AdjacencyList<id_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight)
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::AddEdge(vertex_type,...):" << '\n';
        //DEBUG

        list_.at(vertex1).push_back(
            typename AdjacencyList<id_type>::edge_type(vertex1, vertex2,
                                                       direction, weight));

        // undirected case: push reversed
        if (direction == component::traits::edge_direction::none)
        {
            //DEBUG
            std::cout << "  Undirected edge case" << '\n';
            //DEBUG
            
            list_.at(vertex2).push_back(
                typename AdjacencyList<id_type>::edge_type(vertex2, vertex1,
                                                           direction, weight));
        }
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename AdjacencyList<id_type>::edge_type&
    AdjacencyList<id_type>::GetEdge(
            const typename AdjacencyList<id_type>::vertex_type& vertex1,
            const typename AdjacencyList<id_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight) const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::GetEdge(vertex_type,...):" << '\n';
        //DEBUG

        return std::find_if(list_.at(vertex1).begin(), list_.at(vertex1).end(),
            [&vertex2, &direction, &weight](const auto& edge)
            {
                return ((edge.GetVertex(1) == vertex2) &&
                        (edge.GetDirection() == direction) &&
                        (edge.GetWeight() == weight));
            });
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    AdjacencyList<id_type>::RemoveEdge(
            const typename AdjacencyList<id_type>::vertex_type& vertex1,
            const typename AdjacencyList<id_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight)
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::RemoveEdge(vertex_type, ...):" << '\n';
        //DEBUG

        list_.at(vertex1).erase(
            std::find_if(list_.at(vertex1).begin(), list_.at(vertex1).end(),
            [&vertex2, &direction, &weight](const auto& edge)
            {
                return ((edge.GetVertex(1) == vertex2) &&
                        (edge.GetDirection() == direction) &&
                        (edge.GetWeight() == weight));
            }));

        // undirected case: erase reversed
        if (direction == component::traits::edge_direction::none)
        {
            //DEBUG
            std::cout << "  Undirected edge case" << '\n';
            //DEBUG

            list_.at(vertex2).erase(
                std::find_if(list_.at(vertex2).begin(), list_.at(vertex2).end(),
                [&vertex1, &direction, &weight](const auto& edge)
                {
                    return ((edge.GetVertex(1) == vertex1) &&
                            (edge.GetDirection() == direction) &&
                            (edge.GetWeight() == weight));
                }));
        }
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const typename AdjacencyList<id_type>::edge_container&
    AdjacencyList<id_type>::GetNeighbours(
            const typename AdjacencyList<id_type>::vertex_type& vertex) const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::GetNeighbours(vertex_type):" << '\n';
        //DEBUG

        return list_.at(vertex);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename AdjacencyList<id_type>::const_iterator
    AdjacencyList<id_type>::cbegin() const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::cbegin():" << '\n';
        //DEBUG

        return list_.cbegin();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    typename AdjacencyList<id_type>::const_iterator
    AdjacencyList<id_type>::cend() const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::cend():" << '\n';
        //DEBUG

        return list_.cend();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    int
    AdjacencyList<id_type>::Size() const
    {
        //DEBUG
        std::cout << "AdjacencyList<id_type>::Size():" << '\n';
        //DEBUG

        return list_.size();
    }

} //    namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_ADJACENCY_LIST_H
//==============================================================================
// End of adjacency-list.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
