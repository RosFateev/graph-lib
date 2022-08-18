#ifndef GRAPH_IMPLEMENTATION_MANAGER_HPP
#define GRAPH_IMPLEMENTATION_MANAGER_HPP





//std
#include <initializer_list>
#include <utility>              // std::move
#include <tuple>
#include <algorithm>            // std::find
//lib
//user
#include "graph-implementation/adjacency-list.hpp"
//#include "graph-implementation/incidence-matrix.hpp"










//! implementation
/*!
 * This namespace contains all classes responsible for graph functionality: storing components, 
 * managing internal structures, etc.
*/
namespace implementation
{
    //! Manager
    /*!
     * Contains vertex and edge container and indices (implementations) over them.
    */
    template<   class id_type>
    class Manager
    {
        //type aliases
        using vertex_type               = component::Vertex<id_type>;
        using vertex_ptr                = std::shared_ptr<vertex_type>;
        using edge_type                 = component::Edge<id_type>;
        using edge_ptr                  = std::shared_ptr<edge_type>;
        using vertex_container          = std::vector<vertex_ptr>;
        using edge_container            = std::vector<edge_ptr>;
        using vertex_init_type          = id_type;
        using edge_init_type            = std::tuple<id_type, int, int>;
        using init_list_type            = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        using base_implementation       = BaseImplementation<id_type>;
        using implementation_ptr        = std::unique_ptr<base_implementation>;
        using implementation_container  = std::vector<implementation_ptr>;
        using const_vertex_iterator     = typename vertex_container::const_iterator;
        using const_edge_iterator       = typename edge_container::const_iterator;

    public:

        //! Default constructor
        /*!
         * Creates an empty manager instance.
        */
                                    Manager();

        //! Initializer list constructor
        /*!
         * Stores components and builds structures from a given init list (the same as in Graph 
         * init list constructor).
            \param initializer_list&&
        */
                                    Manager(    std::initializer_list<init_list_type>&&);

        //! AddVertex
        /*!
         * Stores vertex.
            \param id_type
         */
        void                        AddVertex(  id_type);

        //! AddVertex
        /*!
         * Copies and stores vertex.
            \param const vertex_type&
         */
        void                        AddVertex(  const vertex_type&);

        //! GetVertex
        /*!
         * Returns vertex for given index.
            \param id_type
            \return const vertex_type&
         */
        const vertex_type&          GetVertex(  id_type) const;

        //! RemoveVertex
        /*!
         * Removes vertex with given index.
            \param id_type
         */
        void                        RemoveVertex(   id_type);
        
        //! AddEdge
        /*!
         * Stores edge.
            \param id_type
            \param id_type
            \param int
            \param int
         */
        void                        AddEdge(    id_type,
                                                id_type,
                                                int,
                                                int);

        //! AddEdge
        /*!
         * Stores edge.
            \param const vertex_type&
            \param const vertex_type&
            \param int
            \param int
         */
        void                        AddEdge(    const vertex_type&,
                                                const vertex_type&,
                                                int,
                                                int);
        
        //! GetEdge
        /*!
         * Returns edge for given vertex ids.
            \param id_type
            \param id_type
            \param int
            \param int
            \return const edge_type&
         */
        const edge_type&            GetEdge(    id_type,
                                                id_type,
                                                int,
                                                int) const;

        //! GetEdge
        /*!
         * Returns edge for given vertices-endpoints.
            \param const vertex_type&
            \param const vertex_type&
            \param int
            \param int
            \return const edge_type&
         */
        const edge_type&            GetEdge(    const vertex_type&,
                                                const vertex_type&,
                                                int,
                                                int) const;

        //! RemoveEdge
        /*!
         * Removes edge for given vertex ids.
            \param id_type
            \param id_type
            \param int
            \param int
         */
        void                        RemoveEdge( id_type,
                                                id_type,
                                                int,
                                                int);

        //! RemoveEdge
        /*!
         * Removes edge for given vertices-endpoints.
            \param const vertex_type&
            \param const vertex_type&
            \param int
            \param int
         */
        void                        RemoveEdge( const vertex_type&,
                                                const vertex_type&,
                                                int,
                                                int);
        /*
        // neighbours
        template<   class ArgT>
        edge_container&             Neighbours(   ArgT&&);

        template<   class ArgT>
        const edge_container&       Neighbours(   ArgT&&) const;
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

        //! AddImplementation
        /*!
         * Adds new implementation to a graph.
            \param implementation_ptr
         */
        void                        AddImplementation(  implementation_ptr);

        //! RemoveImplementation
        /*!
         * Remove implementation with a given index from a graph.
            \param int
         */
        void                        RemoveImplementation( int);

        //! ChangeImplementation
        /*!
         * Sets new index of active implementation.
            \param int
         */
        void                        ChangeImplementation( int);

        //! GetActiveImplementation
        /*!
         * Returns a reference to active implementation.
            \return implementation_ptr&
         */
        implementation_ptr&         GetActiveImplementation();
        


        //! GetVertexPtr
        /*!
         * For a given id, returns vertex pointer.
            \param int
            \return const vertex_ptr&
         */
        const vertex_ptr&           GetVertexPtr(  id_type) const;

        //! GetEdgePtr
        /*!
         * For a given ids, direction and weight, returns edge pointer.
            \param id_type
            \param id_type
            \param int
            \param int
            \return const edge_ptr&
         */
        const edge_ptr&             GetEdgePtr( id_type,
                                                id_type,
                                                int,
                                                int) const;
        


    private:

        //! vertices
        /*!
         * Vertex container.
         */
        vertex_container            vertices_;
        
        //! edges
        /*!
         * Edge container.
         */
        edge_container              edges_;
        
        //! activeIndex
        /*!
         * Index of active implementation in implementation container.
         */
        int                         activeIndex_;
        
        //! implementations
        /*!
         * Implementation container.
         */
        implementation_container    implementations_;
    };

} //    namespace implementation










//
// Implementation
//
namespace implementation
{
    // constructors
    template<   class id_type>
    Manager<id_type>::Manager()
    {   }

    // Due to edge being dependent on his endpoint vertices it is necessary to iterate over initializer list twice
    template<   class id_type>
    Manager<id_type>::Manager(   std::initializer_list< typename Manager<id_type>::init_list_type>&&     inList) : implementations_()
    {
        // push vertices into container
        for (auto vertex_iter = inList.begin(); vertex_iter != inList.end(); ++vertex_iter)
        {
            vertices_.emplace_back( new typename Manager<id_type>::vertex_type(std::get<0>(*vertex_iter)) );
        }

        // std::tuple<id_type, int, int>;
        
        // push edges into container
        auto vertex_init_iter = inList.begin();
        auto vertex_iter = vertices_.begin();

        for (; vertex_init_iter != inList.end(); ++vertex_init_iter, ++vertex_iter)
        {
            for (auto edge_iter = std::get<1>(*vertex_init_iter).begin(); edge_iter != std::get<1>(*vertex_init_iter).end(); ++edge_iter)
            {
                auto& vertex2 = *std::find_if( vertices_.begin(), vertices_.end(), 
                    [edge_iter](typename Manager<id_type>::vertex_ptr& vertexPtr){ return vertexPtr->Id() == std::get<0>(*edge_iter);}  );
                
                edges_.emplace_back( new typename Manager<id_type>::edge_type( *vertex_iter, vertex2, std::get<1>(*edge_iter),std::get<2>(*edge_iter) )  );
            }
        }

        // initialize implementations - currently Adjacency List
        implementations_.emplace_back( new AdjacencyList(vertices_, edges_));
    }



    //
    // Graph interface
    //
    // vertex
    template<   class id_type>
    void        Manager<id_type>::AddVertex(  id_type     id)
    {
        vertices_.emplace_back( new typename Manager<id_type>::vertex_type(id));

        // add vertex pointer to implementation structures
        for (auto iter = implementations_.begin(); iter != implementations_.end(); ++iter)
        {
            (*iter)->AddVertex(vertices_.back());
        }
    }
    
    template<   class id_type>
    void        Manager<id_type>::AddVertex(  const typename Manager<id_type>::vertex_type& vertex)
    {
        AddVertex(vertex.Id());
    }

    template<   class id_type>
    const typename Manager<id_type>::vertex_type&   Manager<id_type>::GetVertex(  id_type     id) const
    {
        return *GetVertexPtr(id);
    }
    
    template<   class id_type>
    void    Manager<id_type>::RemoveVertex(   id_type     id)
    {
        // remove vertex from each implementation
        std::for_each(implementations_.begin(), implementations_.end(), 
            [id](auto& implementation) { implementation->RemoveVertex(id); });
        // remove from data holder
    }

    

    // Edge
    template<   class id_type>
    void    Manager<id_type>::AddEdge(  id_type     id1,
                                        id_type     id2,
                                        int         direction,
                                        int         weight)
    {
        edges_.emplace_back(new typename Manager<id_type>::edge_type(GetVertexPtr(id1), GetVertexPtr(id1), direction, weight));

        // add vertex pointer to implementation structures
        for (auto iter = implementations_.begin(); iter != implementations_.end(); ++iter)
        {
            (*iter)->AddEdge(edges_.back());
        }
    }

    template<   class id_type>
    void    Manager<id_type>::AddEdge(  const typename Manager<id_type>::vertex_type&  vertex1,
                                        const typename Manager<id_type>::vertex_type&  vertex2,
                                        int                                            direction,
                                        int                                            weight)
    {
        AddEdge(vertex1.Id(), vertex2.Id(), direction, weight);
    }

    template<   class id_type>
    const typename Manager<id_type>::edge_type&    Manager<id_type>::GetEdge(   id_type     id1,
                                                                                id_type     id2,
                                                                                int         direction,
                                                                                int         weight) const
    {
        return *GetEdgePtr(id1, id2, direction, weight);
    }

    template<   class id_type>
    const typename Manager<id_type>::edge_type&    Manager<id_type>::GetEdge(   const typename Manager<id_type>::vertex_type&  vertex1,
                                                                                const typename Manager<id_type>::vertex_type&  vertex2,
                                                                                int                                            direction,
                                                                                int                                            weight) const
    {
        return GetEdge(vertex1.Id(), vertex2.Id(), direction, weight);
    }

    template<   class id_type>
    void    Manager<id_type>::RemoveEdge(   id_type     id1,
                                            id_type     id2,
                                            int         direction,
                                            int         weight)
    {
        // remove vertex from each implementation
        std::for_each(implementations_.begin(), implementations_.end(), 
            [id1, id2, direction, weight](auto& implementation) { implementation->RemoveEdge(id1, id2, direction, weight); } );
        /*
        for (auto iter = implementations_.begin(); iter != implementations_.end(); ++iter)
        {
            (*iter)->RemoveEdge(id1,id2);
        }
        */
        // remove from data holder
    }

    template<   class id_type>
    void    Manager<id_type>::RemoveEdge(   const typename Manager<id_type>::vertex_type&  vertex1,
                                            const typename Manager<id_type>::vertex_type&  vertex2,
                                            int                                            direction,
                                            int                                            weight)
    {
        RemoveEdge(vertex1.Id(), vertex2.Id(), direction, weight);
    }
    


    // neighbours
    /*
    template<   class id_type>
    std::vecto<id_type>>&         Manager<id_type>::Neighbours(   ArgT&& inArg)
    { 
        return list_.Neighbours(std::forward<ArgT>(inArg));
    }

    template<   class id_type>
    const std::vecto<id_type>>&   Manager<id_type>::Neighbours(   ArgT&& inArg) const
    { 
        return list_.Neighbours(std::forward<ArgT>(inArg));
    }
    */

    template<   class id_type>
    typename Manager<id_type>::const_vertex_iterator      Manager<id_type>::v_begin() const
    {
        return vertices_.begin();
    }
    
    template<   class id_type>
    typename Manager<id_type>::const_vertex_iterator      Manager<id_type>::v_end() const
    {
        return vertices_.end();
    }
    
    template<   class id_type>
    typename Manager<id_type>::const_edge_iterator      Manager<id_type>::e_begin() const
    {
        return edges_.begin();
    }
    
    template<   class id_type>
    typename Manager<id_type>::const_edge_iterator      Manager<id_type>::e_end() const
    {
        return edges_.end();
    }





    // helper functions
    // graph's size
    template<   class id_type>
    int     Manager<id_type>::Size() const
    {
        return vertices_.size();
    }



    // Implementation methods
    template<   class id_type>
    void    Manager<id_type>::AddImplementation(  typename Manager<id_type>::implementation_ptr implementation)
    {
        implementations_.push_back(implementation);
    }

    template<   class id_type>
    void    Manager<id_type>::RemoveImplementation( int index)
    {
        implementations_.erase(index);
    }

    template<   class id_type>
    void    Manager<id_type>::ChangeImplementation( int index)
    {
        activeIndex_ = index;
    }

    template<   class id_type>
    typename Manager<id_type>::implementation_ptr&    Manager<id_type>::GetActiveImplementation()
    {
        return implementations_[activeIndex_];
    }





    template<   class id_type>
    const typename Manager<id_type>::vertex_ptr&          Manager<id_type>::GetVertexPtr(  id_type id) const
    {
        return implementations_[activeIndex_]->GetVertex(id);
    }

    template<   class id_type>
    const typename Manager<id_type>::edge_ptr&            Manager<id_type>::GetEdgePtr( id_type id1,
                                                                                        id_type id2,
                                                                                        int     direction,
                                                                                        int     weight) const
    {
        return implementations_[activeIndex_]->GetEdge(id1, id2, direction, weight);
    }
    


} //    namespace implementation



#endif //GRAPH_IMPLEMENTATION_MANAGER_HPP