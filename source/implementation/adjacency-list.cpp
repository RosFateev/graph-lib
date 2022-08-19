//==============================================================================
///
/// @file adjacency-list.cpp
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
#include <graph-lib/implementation/adjacency-list.h>


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
    AdjacencyList::AdjacencyList() : isValid_(true),
                                     list_()
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    AdjacencyList::AdjacencyList(
        const typename AdjacencyList::vertex_init_container& vertices, 
        const typename AdjacencyList::edge_init_container& edges) : is_valid_(true)
    {
        // push vertices
        for (auto vertex_iter = vertices.begin(); vertex_iter != vertices.end(); ++vertex_iter)
        {
            list_[(*vertex_iter)->Id()] = typename AdjacencyList::edge_container();
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
    AdjacencyList::~AdjacencyList()
    {   }

    //------------------------------------------------------------------------------
    //
    //  Push empty edge container.
    //  
    //------------------------------------------------------------------------------
    void
    AdjacencyList::AddVertex(int id)
    {
        list_.push_back(typename AdjacencyList::edge_container());
    }

    /*
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    const bool
    AdjacencyList::GetVertex(int id) const
    {
        return list_.at(inId).front()->GetPointer(0);
    }
    */

    // currently finds a SINGLE occurence in neighbours list - improve find_if()
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    AdjacencyList::RemoveVertex(int id)
    {
        // overwrite with empty container
        list_[id] = typename AdjacencyList::edge_container();

        // erase all edges in other vertices lists
        std::for_each(list_.begin(), list_.end(),
            [&id](auto& edgeContainerIter)
            {
                edgeContainerIter->erase(
                    std::find_if(edgeContainer.begin(), edgeContainer.end(),
                    [&id](auto& edge)
                    {
                        return edge->GetVertex(1).Id() == id;
                    }));

            });
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    AdjacencyList::AddEdge(int id1,
                           int id2,
                           int direction,
                           int weight) 
    {
        list_.at(id1).push_back(typename AdjacencyList::edge_type(id1, id2,
                                                                  direction, weight));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    const bool
    AdjacencyList::Edge(int id1,
                        int id2,
                        int direction,
                        int weight) const
    {
        if (std::find_if(list_.at(id1).begin(), list_.at(id1).end(),
            [&id2, &direction, &weight](auto pEdge)
            {
                return ((pEdge->GetVertex(1).Id() == inId2) &&
                        (pEdge->Direction() == direction) &&
                        (pEdge->Weight() == weight));
            }) != list_.at(inId1).end())
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //  
    //------------------------------------------------------------------------------
    void
    AdjacencyList::RemoveEdge(int id1,
                              int id2,
                              int direction,
                              int weight)
    {
        list_.at(id1).erase(
            std::find_if(list_.at(id1).begin(), list_.at(id1).end(),
            [&inId2, &direction, &weight]( auto& pEdge)
            { 
                return ((pEdge->GetVertex(1).Id() == inId2) &&
                        (pEdge->Direction() == direction) &&
                        (pEdge->Weight() == weight));
            }));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    const typename AdjacencyList::edge_container&
    AdjacencyList::GetNeighbours(int id) const
    {
        return list_.at(id);
    }

} //    namespace implementation



//==============================================================================
// End of adjacency-list.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
