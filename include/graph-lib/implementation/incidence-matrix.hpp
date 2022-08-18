#ifndef GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H
#define GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H





//std
#include <initializer_list>
#include <vector>
#include <map>
#include <utility>                          //std::hash, std::forward
#include <memory>                           //shared_ptr, unique_ptr
//user
#include "graph-component/vertex.hpp"
#include "graph-component/edge.hpp"
#include "graph-implementation/implementation.hpp"





//! implementation
/*!
 * This namespace contains all classes responsible for graph functionality: storing components, 
 * managing internal structures, etc.
*/
namespace implementation
{
    //! IncidenceMatrix
    /*!
     * An implementation of incidence matrix structure using map<vertex_ptr, table index> and vector<int, int>. 
     * Child class of BaseImplementation. 
    */
    template<   typename    id_type>
    class IncidenceMatrix : public BaseImplementation<id_type>
    {
    private:

        //type aliases
        using vertex_type           = component::Vertex<id_type>;
        using vertex_ptr            = std::shared_ptr<vertex_type>;
        using edge_type             = component::Edge<id_type>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        using edge_container        = std::vector<bool>;
        using data_structure        = std::map<vertex_ptr, edge_container, component::support::VertexPtrLess<id_type>>;
        using vertex_init_container = std::vector<vertex_ptr>;
        using edge_init_container   = std::vector<edge_ptr>;

    public:
        
        //! Default constructor
        /*!
         * Constructs empty IncidenceMatrix object.
        */
                                            IncidenceMatrix();
        
        //! Value constructor
        /*!
         * Constructs IncidenceMatrix object using vertex and edge initializer lists.
        */
                                            IncidenceMatrix(    const vertex_init_container&, 
                                                                const edge_init_container&);

        //! Destructor
        /*!
         * Virtual destructor.
        */
        virtual                             ~IncidenceMatrix();

        //! AddVertex
        /*!
         * Stores vertex pointer.
            \param id_type
         */
        virtual void                        AddVertex(  const vertex_ptr&) override;

        //! GetVertex
        /*!
         * Returns vertex pointer for given index.
            \param id_type
            \return const vertex_ptr&
         */
        virtual const vertex_ptr&           GetVertex(  id_type) const override;

        //! RemoveVertex
        /*!
         * Removes vertex pointer with given index.
            \param id_type
         */
        virtual void                        RemoveVertex( id_type) override;

        //! AddEdge
        /*!
         * Stores edge pointer.
            \param const edge_ptr&
         */
        virtual void                        AddEdge(    const edge_ptr&) override;
        
        //! GetEdge
        /*!
         * Returns edge pointer for given vertex ids.
            \param id_type
            \param id_type
            \param int
            \param int
            \return const edge_ptr&
         */
        virtual const edge_ptr&             GetEdge(    id_type,
                                                        id_type,
                                                        int,
                                                        int) const override;
        
        //! RemoveEdge
        /*!
         * Removes edge pointer for given vertex pointers.
            \param const vertex_ptr&
            \param const vertex_ptr&
            \param int
            \param int
         */
        virtual void                        RemoveEdge( const vertex_ptr&,
                                                        const vertex_ptr&,
                                                        int,
                                                        int) override;

        //! RemoveEdge
        /*!
         * Removes edge pointer for given vertex ids.
            \param id_type
            \param id_type
            \param int
            \param int
         */
        virtual void                        RemoveEdge( id_type,
                                                        id_type,
                                                        int,
                                                        int) override;

        /*
        virtual edge_container&          GetNeighbours(    id_type inId) override;
        virtual const edge_container&    GetNeighbours(    id_type inId) const override;
        virtual edge_container&          GetNeighbours(    const vertex_type& inVertex) override;
        virtual const edge_container&    GetNeighbours(    const vertex_type& inVertex) const override;
        */





    private:
        
        //
        // state
        //
        bool                    valid_;
        data_structure          map_;
        edge_container          matrix_;



        //friendships
        friend storage_policy_type;
    };

} //    namespace implementation










//
// Incidence Matrix definition
//
namespace implementation
{
    /*
    //
    // Constructors
    //
    template<   typename    id_type>
    IncidenceMatrix<id_type>::IncidenceMatrix() : valid_(false),
                                                            map_(),
                                                            matrix_(),
                                                            componentAllocator_(*this)
    {   }



    //
    // Component manipulators
    //
    template<   typename    id_type>
    void IncidenceMatrix<id_type>::AddVertex(  id_type)
    {

    }
        

    template<   typename    id_type>
    void IncidenceMatrix<id_type>::AddVertex(  const vertex_type&)
    {

    } 
    

    template<   typename    id_type>
    const component::Vertex<id_type>& IncidenceMatrix<id_type>::GetVertex(  id_type)
    {

    }


    template<   typename    id_type>
    void IncidenceMatrix<id_type>::RemoveVertex( id_type&&)
    {

    }

    
    template<   typename    id_type>
    void IncidenceMatrix<id_type>::AddEdge(    const vertex_type&, 
                                                    const vertex_type&,
                                            int                     inWeight = 0)
    {

    }
        
        
    template<   typename    id_type>
    EdgeType<id_type>& IncidenceMatrix<id_type>::GetEdge(    id_type,
                                            id_type)
    {

    } 
    

    template<   typename    id_type>
    EdgeType<id_type>& IncidenceMatrix<id_type>::GetEdge(    const vertex_type&,
                                            const vertex_type&)
    {

    }


    template<   typename    id_type>
    void IncidenceMatrix<id_type>::RemoveEdge( const vertex_type&,
                                            const vertex_type&)
    {

    }


    template<   typename    id_type>
    void IncidenceMatrix<id_type>::RemoveEdge( id_type&&,
                                            id_type&&)
    {

    }


    template<   typename    id_type>
    edge_container& IncidenceMatrix<id_type>::GetNeighbours(    id_type inId)
    {

    }


    template<   typename    id_type>
    const edge_container& IncidenceMatrix<id_type>::GetNeighbours(    id_type inId) const
    {

    }

    
    template<   typename    id_type>
    edge_container& IncidenceMatrix<id_type>::GetNeighbours(    const vertex_type& inVertex)
    {

    }


    template<   typename    id_type>
    const edge_container& IncidenceMatrix<id_type>::GetNeighbours(    const vertex_type& inVertex) const
    {

    }
    */

} //    namespace implementation



#endif //GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H