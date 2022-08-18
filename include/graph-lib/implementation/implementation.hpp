#ifndef GRAPH_IMPLEMENTATION_IMPLEMENTATION_HPP
#define GRAPH_IMPLEMENTATION_IMPLEMENTATION_HPP





#include "graph-implementation/implementation-support.hpp"





// forward declarations
namespace component
{
    template<   class id_type>
    class Vertex;

    template<   class id_type>
    class Edge;
}




//! implementation
/*!
 * This namespace contains all classes responsible for graph functionality: storing components, 
 * managing internal structures, etc.
*/
namespace implementation
{
    //! BaseImplementation
    /*!
     * Base abstract implementation class. 
    */
    template<   class   id_type>
    class BaseImplementation
    {

        using vertex_type           = component::Vertex<id_type>;
        using vertex_ptr            = std::shared_ptr<vertex_type>;
        using edge_type             = component::Edge<id_type>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        using edge_container        = std::list<edge_ptr>;
        using vertex_init_container = std::vector<vertex_ptr>;
        using edge_init_container   = std::vector<edge_ptr>;

    public:

        //! Default constructor
        /*!
         * Allows construction of empty BaseImplementation subobject inside children classes.
        */
                                            BaseImplementation() {}
        
        //! Value constructor
        /*!
         * Allows construction of child class' objects using vertex and edge initializer lists through upcasting.
        */
                                            BaseImplementation( const vertex_init_container&, 
                                                                const edge_init_container&) {}

        //! Destructor
        /*!
         * Virtual destructor.
        */
        virtual                             ~BaseImplementation() {};

        //! AddVertex
        /*!
         * Stores vertex pointer. Part of virtual interface.
            \param id_type
         */
        virtual void                        AddVertex(  const vertex_ptr&) = 0;

        //! GetVertex
        /*!
         * Returns vertex pointer for given index. Part of virtual interface.
            \param id_type
            \return const vertex_ptr&
         */
        virtual const vertex_ptr&           GetVertex(  id_type) const = 0;

        //! RemoveVertex
        /*!
         * Removes vertex pointer with given index. Part of virtual interface.
            \param id_type
         */
        virtual void                        RemoveVertex( id_type) = 0;

        //! AddEdge
        /*!
         * Stores edge pointer. Part of virtual interface.
            \param const edge_ptr&
         */
        virtual void                        AddEdge(    const edge_ptr&) = 0;
        
        //! GetEdge
        /*!
         * Returns edge pointer for given vertex ids. Part of virtual interface.
            \param id_type
            \param id_type
            \param int
            \param int
            \return const edge_ptr&
         */
        virtual const edge_ptr&             GetEdge(    id_type,
                                                        id_type,
                                                        int,
                                                        int) const = 0;
        
        //! RemoveEdge
        /*!
         * Removes edge pointer for given vertex pointers. Part of virtual interface.
            \param const vertex_ptr&
            \param const vertex_ptr&
            \param int
            \param int
         */
        virtual void                        RemoveEdge( const vertex_ptr&,
                                                        const vertex_ptr&,
                                                        int,
                                                        int) = 0;

        //! RemoveEdge
        /*!
         * Removes edge pointer for given vertex ids. Part of virtual interface.
            \param id_type
            \param id_type
            \param int
            \param int
         */
        virtual void                        RemoveEdge( id_type,
                                                        id_type,
                                                        int,
                                                        int) = 0;



        // 
        /*
        virtual edge_container&             Neighbours(    id_type inId) = 0;

        virtual const edge_container&       Neighbours(    id_type inId) const = 0;

        virtual edge_container&             Neighbours(    const vertex_ptr& inVertex) = 0;

        virtual const edge_container&       Neighbours(    const vertex_ptr& inVertex) const = 0;
        */



    };

} //    namespace implementation





#endif // GRAPH_IMPLEMENTATION_IMPLEMENTATION_HPP