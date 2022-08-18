#ifndef GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H
#define GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H





//std
#include <initializer_list>
#include <list>
#include <map>
#include <utility>                      // std::hash, std::forward
#include <iostream>
#include <algorithm>                    // std::find
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
    //! AdjacencyList
    /*!
     * An implementation of adjacency list structure using map<index, edge_pointer container>. 
     * Child class of BaseImplementation. 
    */
    template<   typename    id_type>
    class AdjacencyList : public BaseImplementation<id_type>
    {
        using vertex_type           = component::Vertex<id_type>;
        using vertex_ptr            = std::shared_ptr<vertex_type>;
        using edge_type             = component::Edge<id_type>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        using edge_container        = std::list<edge_ptr>;
        using data_structure        = std::map<id_type, edge_container>;
        using vertex_init_container = std::vector<vertex_ptr>;
        using edge_init_container   = std::vector<edge_ptr>;

    public:
        
        //! Default constructor
        /*!
         * Constructs empty AdjacencyList object.
        */
                                            AdjacencyList();
        
        //! Value constructor
        /*!
         * Constructs AdjacencyList object using vertex and edge initializer lists.
        */
                                            AdjacencyList(  const vertex_init_container&, 
                                                            const edge_init_container&);

        //! Destructor
        /*!
         * Virtual destructor.
        */
        virtual                             ~AdjacencyList();

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
        
        // 
        /*
        virtual edge_container&             Neighbours(    id_type inId) override;

        virtual const edge_container&       Neighbours(    id_type inId) const override;

        virtual edge_container&             Neighbours(    const vertex_ptr& inVertex) override;

        virtual const edge_container&       Neighbours(    const vertex_ptr& inVertex) const override;
        */



    private:
        
        //! is_valid
        /*!
         * Indicates if AdjacencyList object needs to be updated.
         */
        bool                    is_valid_;

        //! list
        /*!
         * Adjacency list container.
         */
        data_structure          list_;
    };

} //    namespace implementation










//
// Adjacency list definition
//
namespace implementation
{
    //Adjacency list implementation
    //constructors

    // DONE
    template<   typename    id_type>
    AdjacencyList<id_type>::AdjacencyList() :   is_valid_(true),
                                                list_()
    {   }

    template<   typename    id_type>
    AdjacencyList<id_type>::AdjacencyList(  const typename AdjacencyList<id_type>::vertex_init_container&   vertices, 
                                            const typename AdjacencyList<id_type>::edge_init_container&    edges) :    is_valid_(true)
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

    template<   typename    id_type>
    AdjacencyList<id_type>::~AdjacencyList()
    {   }



    // vertex
    template<   typename    id_type>
    void        AdjacencyList<id_type>::AddVertex(   const    vertex_ptr&         vertexPtr)
    {
        list_[vertexPtr->Id()] = typename AdjacencyList<id_type>::edge_container();
    }

    template<   typename    id_type>
    const typename AdjacencyList<id_type>::vertex_ptr&    AdjacencyList<id_type>::GetVertex(    id_type     inId) const
    {
        return list_.at(inId).front()->GetPointer(0);
    }

    // currently finds a SINGLE occurence in neighbours list - improve find_if()
    template<   typename    id_type>
    void              AdjacencyList<id_type>::RemoveVertex( id_type   inId)
    {
        // erase vertex
        list_.erase(list_.find(inId));

        // erase all edges in other vertices lists
        for (auto key_iterator = list_.begin(); key_iterator != list_.end(); ++key_iterator)
        {
            (key_iterator->second).erase( 
                    std::find_if((key_iterator->second).begin(), (key_iterator->second).end(), 
                        [inId]( auto& edgePtr){ return edgePtr->GetVertex(1).Id() == inId; }) );
        } 
    }



    // edge
    template<   typename    id_type>
    void    AdjacencyList<id_type>::AddEdge(  const edge_ptr& edge) 
    {
        list_.at(edge->GetVertex(0).Id()).push_back(edge);
    }

    template<   typename    id_type>
    const typename AdjacencyList<id_type>::edge_ptr&      AdjacencyList<id_type>::GetEdge(  id_type     inId1,
                                                                                            id_type     inId2,
                                                                                            int         direction,
                                                                                            int         weight) const
    {
        return *std::find_if(list_.at(inId1).begin(), list_.at(inId1).end(), 
            [inId2, direction, weight]( auto& edgePtr) { 
                                return ((edgePtr->GetVertex(1).Id() == inId2) &&
                                        (edgePtr->Direction() == direction) &&
                                        (edgePtr->Weight() == weight));} );
    }



    //
    template<   typename    id_type>
    void              AdjacencyList<id_type>::RemoveEdge(   id_type     inId1,
                                                            id_type     inId2,
                                                            int         direction,
                                                            int         weight)
    {
        list_.at(inId1).erase( std::find_if( list_.at(inId1).begin(), list_.at(inId1).end(),
            [inId2, direction, weight]( auto& edgePtr){ 
                                                        return ((edgePtr->GetVertex(1).Id() == inId2) &&
                                                                (edgePtr->Direction() == direction) &&
                                                                (edgePtr->Weight() == weight));}) );
    }

    template<   typename    id_type>
    void              AdjacencyList<id_type>::RemoveEdge(   const vertex_ptr&   vertexPtr1,
                                                            const vertex_ptr&   vertexPtr2,
                                                            int                 direction,
                                                            int                 weight)
    {
        RemoveEdge(vertexPtr1->Id(), vertexPtr2->Id(), direction, weight);
    }





    //
    // Get neighbors are used for algorithms
    //
    /*
    // DONE
    template<   typename    id_type>
    std::lis<id_type>>&          AdjacencyList<id_type>::Neighbours(            id_type             inId)
    {
        return list_.at(Vertex(inId));
    }

    template<   typename    id_type>
    const std::lis<id_type>>&    AdjacencyList<id_type>::Neighbours(            id_type             inId)       const
    {
        return list_.at(Vertex(inId));
    }

    template<   typename    id_type>
    std::lis<id_type>>&          AdjacencyList<id_type>::Neighbours(    const   vertex_ptr&     inVertexPtr)
    {
        return list_.at(inVertexPtr);
    }

    template<   typename    id_type>
    const std::lis<id_type>>&    AdjacencyList<id_type>::Neighbours(    const   vertex_ptr&     inVertexPtr)    const
    {
        return list_.at(inVertexPtr);
    }
    */



    //
    //  print method used for debugging
    //
    //  REMOVE LATER
    //
    /*
    // DONE
    template<   typename id_type>
    void AdjacencyList<id_type>::print()
    {
        std::cout << "Printing a graph:" << std::endl;
        //std::map<vertex_type, std::lis<id_type>>>;

        //output vertexes 
        typename data_structure::const_iterator mapIter(list_.begin());

        for(; mapIter != list_.end(); ++mapIter)
        {
            //output vertex

            std::cout << "[ " << mapIter->first->Id() << " ] :";
            //output edges
            typename edge_container::const_iterator vectIter(mapIter->second.begin());

            for(; vectIter != mapIter->second.end(); ++vectIter)
            {
                std::cout << "  ( " << vectIter->First()->Id() << ", " << vectIter->Second()->Id() << ")";
            }
            std::cout << std::endl;
        }
    }
    */

} //    namespace implementation


#endif //GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H