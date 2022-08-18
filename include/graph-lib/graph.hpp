#ifndef GRAPH_HPP
#define GRAPH_HPP





//std
#include <initializer_list>
#include <utility>                      // std::move
//user
#include "graph-implementation/manager.hpp"





//! graph
/*!
 * namespace containing graph's definition. 
*/
namespace graph
{
    //! Graph
    /*! 
     * A collection of vertices and edges.
    */
    template<    class id_type>
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

        //! Default constructor
        /*!
         * Creates an empty graph instance.
         */
                                    Graph();
        
        //! Initializer list constructor
        /*!
         * Creates a graph instance from initializer list of type: 
         * {
            * { vertex_id, { 
            *       { neighbour1_id, direction, weight},
            *       ...
            *       { neighbourM_id, direction, weight} } 
            * },
            * { vertex2_id, {...} },
            * ...
            * { vertexR_id, {...} } 
            }
         */
                                    Graph(  std::initializer_list<init_list_type>&&);

        //! AddVertex
        /*!
         * Adds vertex to a graph.
            \param id_type id
         */
        void                        AddVertex(  id_type);

        //! AddVertex
        /*!
         * Adds vertex to a graph.
            \param const Vertex& vertex
         */
        void                        AddVertex(  const vertex_type&);
        
        //! GetVertex
        /*!
         * Finds vertex in a graph and returns it.
            \param id_type id
            \return constant reference to vertex
         */
        const vertex_type&          GetVertex(  id_type) const;

        //! RemoveVertex
        /*!
         * Removes vertex from a graph.
            \param id_type id
         */
        void                        RemoveVertex(   id_type);
        
        //! AddEdge
        /*!
         * Adds edge to a graph.
            \param id_type id1
            \param id_type id2
            \param int direction
            \param int weight
         */
        void                        AddEdge(    id_type,
                                                id_type,
                                                int     direction = component::traits::edge_direction::none,
                                                int     weight = 0);

        //! AddEdge
        /*!
         * Adds edge to a graph.
            \param const Vertex& vertex1
            \param const Vertex& vertex2
            \param int direction
            \param int weight
         */
        void                        AddEdge(    const vertex_type&,
                                                const vertex_type&,
                                                int                 direction = component::traits::edge_direction::none,
                                                int                 weight = 0);
        
        //! GetEdge
        /*!
         * Finds edge in a graph and returns it.
            \param id_type id1
            \param id_type id2
            \param int direction
            \param int weight
            \return constant reference to edge
         */
        const edge_type&            GetEdge(    id_type,
                                                id_type,
                                                int      direction = component::traits::edge_direction::none,
                                                int      weight = 0) const;

        //! GetEdge
        /*!
         * Finds edge in a graph and returns it.
            \param const Vertex& vertex1
            \param const Vertex& vertex2
            \param int direction
            \param int weight
            \return constant reference to edge
         */
        const edge_type&            GetEdge(    const vertex_type&,
                                                const vertex_type&,
                                                int                 direction = component::traits::edge_direction::none,
                                                int                 weight = 0) const;

        //! RemoveEdge
        /*!
         * Removes edge from a graph.
            \param id_type id1
            \param id_type id2
            \param int direction
            \param int weight
         */
        void                        RemoveEdge( id_type,
                                                id_type,
                                                int      direction = component::traits::edge_direction::none,
                                                int      weight = 0);

        //! RemoveEdge
        /*!
         * Removes edge from a graph.
            \param const Vertex& vertex1
            \param const Vertex& vertex2
            \param int direction
            \param int weight
         */
        void                        RemoveEdge( const vertex_type&,
                                                const vertex_type&,
                                                int                 direction = component::traits::edge_direction::none,
                                                int                 weight = 0);



        // all edges for a particular vertex
        /*
        const edge_container&       Neighbours(   id_type) const;
        
        const edge_container&       Neighbours(   const vertex_type&) const;
        */


        //! v_begin
        /*!
         * Returns iterator to the beginning of vertex container to enable iteration (like container.begin()).
            \return constant vertex container iterator to the beginning
         */
        const_vertex_iterator       v_begin() const;

        //! v_end
        /*!
         * Returns iterator to the end of vertex container to enable iteration (like container.end()).
            \return constant vertex container iterator to the end
         */
        const_vertex_iterator       v_end() const;

        //! e_begin
        /*!
         * Returns iterator to the beginning of edge container to enable iteration (like container.begin()).
            \return constant edge container iterator to the beginning
         */
        const_edge_iterator         e_begin() const;

        //! e_end
        /*!
         * Returns iterator to the end of edge container to enable iteration (like container.end()).
            \return constant edge container iterator to the end
         */
        const_edge_iterator         e_end() const;

        //! Size
        /*!
         * Returns number of vertices in a graph.
            \return vertex count
         */
        int                         Size() const;


        


    private:
        
        //! Manager
        /*!
         * Manager structure which implements graph functionality.
         */
        manager_type    manager_;
    };

} //    namespace graph 










//
// Graph implementation
//
namespace graph
{
    // constructors
    template<   class id_type>
    Graph<id_type>::Graph()
    {   }

    template<   class id_type>
    Graph<id_type>::Graph(   std::initializer_list<typename Graph<id_type>::init_list_type>&& inList) : manager_(std::move(inList))
    {   }   





    // component manipulator    
    // Vertex
    template<   class id_type>
    void        Graph<id_type>::AddVertex(  id_type   id)
    {
        manager_.AddVertex(id);
    }
    
    template<   class id_type>
    void        Graph<id_type>::AddVertex(  const typename Graph<id_type>::vertex_type&     vertex)
    {
        manager_.AddVertex(vertex);
    }
    /*
    template<   class id_type>  
    void        Graph<id_type>::AddVertex(  typename Graph<id_type>::vertex_type&&      vertex)
    {
        manager_.AddVertex(std::forward(vertex));
    }
    */
    template<   class id_type>
    const typename Graph<id_type>::vertex_type&       Graph<id_type>::GetVertex(  id_type  id) const
    {
        return manager_.GetVertex(id);
    }

    template<   class id_type>
    void           Graph<id_type>::RemoveVertex(  id_type     id) 
    { 
        manager_.RemoveVertex(id); 
    }



    // Edge
    template<   class id_type>
    void        Graph<id_type>::AddEdge(    id_type     id1,
                                            id_type     id2,
                                            int         direction,
                                            int         weight)
    {
        manager_.AddEdge(id1, id2, direction, weight);
    }

    template<   class id_type>
    void        Graph<id_type>::AddEdge(    const typename Graph<id_type>::vertex_type&  vertex1,
                                            const typename Graph<id_type>::vertex_type&  vertex2,
                                            int                                          direction,
                                            int                                          weight)
    {
        manager_.AddEdge(vertex1, vertex2, direction, weight);
    }

    template<   class id_type>
    const typename Graph<id_type>::edge_type&        Graph<id_type>::GetEdge(   id_type     id1,
                                                                                id_type     id2,
                                                                                int         direction,
                                                                                int         weight) const
    {
        return manager_.GetEdge(id1, id2, direction, weight);
    }

    template<   class id_type>
    const typename Graph<id_type>::edge_type&        Graph<id_type>::GetEdge(   const typename Graph<id_type>::vertex_type&  vertex1,
                                                                                const typename Graph<id_type>::vertex_type&  vertex2,
                                                                                int                                          direction,
                                                                                int                                          weight) const
    {
        return manager_.GetEdge(vertex1, vertex2, direction, weight);
    }
    
    template<   class id_type>
    void        Graph<id_type>::RemoveEdge( id_type     id1,
                                            id_type     id2,
                                            int         direction,
                                            int         weight)
    {
        manager_.RemoveEdge(id1, id2, direction, weight);
    }

    template<   class id_type>
    void        Graph<id_type>::RemoveEdge(     const typename Graph<id_type>::vertex_type&  vertex1,
                                                const typename Graph<id_type>::vertex_type&  vertex2,
                                                int                                          direction,
                                                int                                          weight)
    {
        manager_.RemoveEdge(vertex1, vertex2, direction, weight);
    }



    // neighbours
    /*
    template<   class id_type>
    typename Graph<id_type>::edge_container&    Graph<id_type>::Neighbours(   ArgT&& inArg)
    { 
        return manager_.Neighbours(std::forward<ArgT>(inArg));
    }

    template<   class id_type>
    typename Graph<id_type>::edge_container&    Graph<id_type>::Neighbours(   ArgT&& inArg) const
    { 
        return manager_.Neighbours(std::forward<ArgT>(inArg));
    }
    */


    template<   class id_type>
    typename Graph<id_type>::const_vertex_iterator      Graph<id_type>::v_begin() const
    {
        return manager_.v_begin();
    }
    
    template<   class id_type>
    typename Graph<id_type>::const_vertex_iterator      Graph<id_type>::v_end() const
    {
        return manager_.v_end();
    }
    
    template<   class id_type>
    typename Graph<id_type>::const_edge_iterator      Graph<id_type>::e_begin() const
    {
        return manager_.e_begin();
    }
    
    template<   class id_type>
    typename Graph<id_type>::const_edge_iterator      Graph<id_type>::e_end() const
    {
        return manager_.e_end();
    }



    // helper functions
    // Size
    template<   class id_type>
    int     Graph<id_type>::Size() const
    {
        return manager_.Size();
    }



} //    namespace graph




#endif //GRAPH_HPP