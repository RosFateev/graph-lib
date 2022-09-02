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
#include <vector>
#include <tuple>
#include <algorithm>            // std::for_each
#include <stdexcept>            // std::out_of_range

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/implementation/adjacency-list.hpp"


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
    /// A wrapper over structured collection of vertices and edges.
    /// Exact functionality depends on implementation_type component.
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type = implementation::AdjacencyList<id_type>>
    class Graph
    {
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using edge_container        = typename implementation_type::edge_container;
        // init list related
        using vertex_init_type      = id_type;
        using edge_init_type        = std::tuple<id_type, int, int>;
        using init_list_type        = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        // allows iterator access
        using iterator              = typename implementation_type::iterator;
        using const_iterator        = typename implementation_type::const_iterator;

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
        /// @brief Update vertex coordinates.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @param[in] x Vertex x-coordinate.
        ///
        /// @param[in] y Vertex y-coordinate.
        ///
        /// @return Vertex.
        ///
        //------------------------------------------------------------------------------
        void
        UpdateVertex(id_type id,
                     float x,
                     float y);

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
                component::traits::edge_direction direction = component::traits::edge_direction::none,
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
                component::traits::edge_direction direction = component::traits::edge_direction::none,
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
                component::traits::edge_direction direction = component::traits::edge_direction::none,
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
                component::traits::edge_direction direction = component::traits::edge_direction::none,
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
                   component::traits::edge_direction direction = component::traits::edge_direction::none,
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
                   component::traits::edge_direction direction = component::traits::edge_direction::none,
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

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the beginning of vertex map structure.
        ///
        /// @return implementation begin() iterator.
        ///
        //------------------------------------------------------------------------------        
        iterator
        begin();

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the beginning of vertex map structure.
        ///
        /// @return implementation cbegin() iterator.
        ///
        //------------------------------------------------------------------------------        
        const_iterator
        cbegin() const;

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the end of vertex map structure.
        ///
        /// @return implementation end() iterator.
        ///
        //------------------------------------------------------------------------------        
        iterator
        end();

        //------------------------------------------------------------------------------
        /// @brief Get iterator to the end of vertex map structure.
        ///
        /// @return implementation cend() iterator.
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

        //------------------------------------------------------------------------------
        /// @brief Determine if vertex is valid and present in a graph.
        ///
        /// @param[in] vertex Input vertex.
        ///
        /// @retval True if vertex id != invalid value.
        /// @retval False otherwise.
        ///
        //------------------------------------------------------------------------------
        bool
        IsValidVertex(const vertex_type& vertex) const;

        //------------------------------------------------------------------------------
        /// @brief Determine if edge is valid and present in a graph.
        ///
        /// @param[in] edge Input edge.
        ///
        /// @retval True if edge id != invalid value.
        /// @retval False otherwise.
        ///
        //------------------------------------------------------------------------------
        bool
        IsValidEdge(const edge_type& edge) const;


    public:

        /*
        /// @brief invalid vertex constant.
        static const vertex_type& invalidVertex_;

        /// @brief invalid edge constant.
        static const edge_type& invalidEdge_;
        */

    private:

        /// @brief Internal graph implementation.
        implementation_type implementation_;
    };

    /*
    // initialize graph invalid vertex
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::vertex_type&
    Graph<id_type, implementation_type>::invalidVertex_ = implementation_type::invalidVertex_;

    // initialize graph invalid vertex
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::edge_type&
    Graph<id_type, implementation_type>::invalidEdge_ = implementation_type::invalidEdge_;
    */

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
    template<class id_type,
             typename implementation_type>
    Graph<id_type, implementation_type>::Graph()
    {   }

    /*
    //------------------------------------------------------------------------------
    //
    //  Go through initializer list filling vertexMap_ structure.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    Graph<id_type, implementation_type>::Graph(
        std::initializer_list<typename Graph<id_type, implementation_type>::init_list_type>&& initList) : 
                implementation_()
    {
        int index = 0;
        std::for_each(initList.begin(), initList.end(),
            [&vertexMap_, &index](const auto& initVertEdgeTuple)
            {
                vertexMap_.[
                    typename Graph<id_type, implementation_type>::vertex_type(
                        std::get<0>(initVertEdgeTuple) )] = index++;

                implementation_.AddEdge()
            });
    }
    */

    //------------------------------------------------------------------------------
    //
    //  Add vertex creates a new entry in map structure and implementation(s).
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::AddVertex(id_type id)
    {
        AddVertex(typename Graph<id_type, implementation_type>::vertex_type(id));
    }
    
    //------------------------------------------------------------------------------
    //
    //  Call AddVertex(id_type) method.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::AddVertex(const typename Graph<id_type, implementation_type>::vertex_type& vertex)
    {
        // call default method
        implementation_.AddVertex(vertex);
    }

    //------------------------------------------------------------------------------
    //
    //  Returns vertex from map structure if present.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::vertex_type&
    Graph<id_type, implementation_type>::GetVertex(id_type id) const
    {
        return implementation_.GetVertex(id);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::UpdateVertex(id_type id,
                                                      float x,
                                                      float y)
    {
        implementation_.UpdateVertex(id, x, y);
    }

    //------------------------------------------------------------------------------
    //
    //  Mark as invalid in map structure and remove from implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::RemoveVertex(id_type id) 
    {
        implementation_.RemoveVertex(typename Graph<id_type, implementation_type>::vertex_type(id));
    }

    //------------------------------------------------------------------------------
    //
    //  Look for proper indecies in structure and insert into implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::AddEdge(id_type id1,
                                                 id_type id2,
                                                 component::traits::edge_direction direction,
                                                 int weight)
    {
        AddEdge(GetVertex(id1),
                GetVertex(id2),
                direction,
                weight);
    }

    //------------------------------------------------------------------------------
    //
    //  Look for proper indecies in structure and insert into implementation.
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::AddEdge(
            const typename Graph<id_type, implementation_type>::vertex_type& vertex1,
            const typename Graph<id_type, implementation_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight)
    {
        implementation_.AddEdge(vertex1, vertex2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  If edge exist in implementation - construct and return Edge object
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::edge_type&
    Graph<id_type, implementation_type>::GetEdge(id_type id1,
                                                 id_type id2,
                                                 component::traits::edge_direction direction,
                                                 int weight) const
    {
        return GetEdge(typename Graph<id_type, implementation_type>::vertex_type(id1),
                       typename Graph<id_type, implementation_type>::vertex_type(id2),
                       direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  If edge exist in implementation - construct and return Edge object
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::edge_type&
    Graph<id_type, implementation_type>::GetEdge(
            const typename Graph<id_type, implementation_type>::vertex_type& vertex1,
            const typename Graph<id_type, implementation_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight) const
    {
        return implementation_.GetEdge(vertex1, vertex2, direction, weight);
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::RemoveEdge(id_type id1,
                                                    id_type id2,
                                                    component::traits::edge_direction direction,
                                                    int weight)
    {
        RemoveEdge(typename Graph<id_type, implementation_type>::vertex_type(id1),
                   typename Graph<id_type, implementation_type>::vertex_type(id2),
                   direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    void
    Graph<id_type, implementation_type>::RemoveEdge(
            const typename Graph<id_type, implementation_type>::vertex_type& vertex1,
            const typename Graph<id_type, implementation_type>::vertex_type& vertex2,
            component::traits::edge_direction direction,
            int weight)
    {
        implementation_.RemoveEdge(vertex1, vertex2, direction, weight);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::edge_container&
    Graph<id_type, implementation_type>::GetNeighbours(id_type id) const
    {
        return GetNeighbours(typename Graph<id_type, implementation_type>::vertex_type(id));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    const typename Graph<id_type, implementation_type>::edge_container&
    Graph<id_type, implementation_type>::GetNeighbours(
            const typename Graph<id_type, implementation_type>::vertex_type& vertex) const
    {
        return implementation_.GetNeighbours(vertex);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    typename Graph<id_type, implementation_type>::iterator
    Graph<id_type, implementation_type>::begin()
    {
        return implementation_.begin();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------    
    template<class id_type,
             typename implementation_type>
    typename Graph<id_type, implementation_type>::const_iterator
    Graph<id_type, implementation_type>::cbegin() const
    {
        return implementation_.cbegin();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------      
    template<class id_type,
             typename implementation_type>
    typename Graph<id_type, implementation_type>::iterator
    Graph<id_type, implementation_type>::end()
    {
        return implementation_.end();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------      
    template<class id_type,
             typename implementation_type>
    typename Graph<id_type, implementation_type>::const_iterator
    Graph<id_type, implementation_type>::cend() const
    {
        return implementation_.cend();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    int
    Graph<id_type, implementation_type>::Size() const
    {
        return implementation_.Size();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    bool
    Graph<id_type, implementation_type>::IsValidVertex(
            const typename Graph<id_type, implementation_type>::vertex_type& vertex) const
    {
        return (vertex.Id() == component::traits::vertex_traits<id_type>::invalid_ ? false : true);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type,
             typename implementation_type>
    bool
    Graph<id_type, implementation_type>::IsValidEdge(
            const typename Graph<id_type, implementation_type>::edge_type& edge) const
    {
        return IsValidVertex(edge.GetVertex(0));
    }


} //    namespace graph



#endif // GRAPH_LIB_GRAPH_HPP
//==============================================================================
// End of graph.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
