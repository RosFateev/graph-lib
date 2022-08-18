//==============================================================================
///
/// @file template.cpp
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


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "template.h"


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
// Local data types
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward function declarations
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
    IncidenceMatrix::IncidenceMatrix() : isValid_(true),
                                         list_()
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    IncidenceMatrix::IncidenceMatrix(
        const typename IncidenceMatrix::vertex_init_container& vertices, 
        const typename IncidenceMatrix::edge_init_container& edges) : is_valid_(true)
    {
        // push vertices
        for (auto vertex_iter = vertices.begin(); vertex_iter != vertices.end(); ++vertex_iter)
        {
            list_[(*vertex_iter)->Id()] = typename IncidenceMatrix::edge_container();
        }

        // push edges
        for (auto edge_iter = edges.begin(); edge_iter != edges.end(); ++edge_iter)
        {
            list_.at((*edge_iter)->GetVertex(0).Id()).push_back(*edge_iter);
        }
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    IncidenceMatrix::~IncidenceMatrix()
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    IncidenceMatrix::AddVertex(int id)
    {
        list_[vertexPtr->Id()] = typename IncidenceMatrix::edge_container();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    const bool
    IncidenceMatrix::GetVertex(int id) const
    {
        return list_.at(inId).front()->GetPointer(0);
    }

    // currently finds a SINGLE occurence in neighbours list - improve find_if()
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    IncidenceMatrix::RemoveVertex(int id)
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

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    IncidenceMatrix::AddEdge(const edge_ptr& edge) 
    {
        list_.at(edge->GetVertex(0).Id()).push_back(edge);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    const typename IncidenceMatrix::edge_ptr&
    IncidenceMatrix::GetEdge(int id1,
                           int id2,
                           int direction,
                           int weight) const
    {
        return *std::find_if(list_.at(inId1).begin(), list_.at(inId1).end(), 
            [inId2, direction, weight]( auto& edgePtr) { 
                                return ((edgePtr->GetVertex(1).Id() == inId2) &&
                                        (edgePtr->Direction() == direction) &&
                                        (edgePtr->Weight() == weight));} );
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    IncidenceMatrix::RemoveEdge(int id1,
                              int id2,
                              int direction,
                              int weight)
    {
        list_.at(inId1).erase( std::find_if( list_.at(inId1).begin(), list_.at(inId1).end(),
            [inId2, direction, weight]( auto& edgePtr){ 
                                                        return ((edgePtr->GetVertex(1).Id() == inId2) &&
                                                                (edgePtr->Direction() == direction) &&
                                                                (edgePtr->Weight() == weight));}) );
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    const typename IncidenceMatrix::edge_container&
    IncidenceMatrix::GetNeighbours(int id) const
    {
        return list_.at(Vertex(inId));
    }

    /*
    // DONE
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void IncidenceMatrix::print()
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



//==============================================================================
// End of template.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
