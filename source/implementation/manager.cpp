//==============================================================================
///
/// @file manager.cpp
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
#include <graph-lib/implementation/manager.h>


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
    Manager::Manager()
    {   }

    //------------------------------------------------------------------------------
    //
    //  Due to edge being dependent on his endpoint vertices it is necessary to
    //  iterate over initializer list twice.
    //
    //------------------------------------------------------------------------------
    Manager::Manager(   std::initializer_list< typename Manager::init_list_type>&&     inList) : implementations_()
    {
        // push vertices into container
        for (auto vertex_iter = inList.begin(); vertex_iter != inList.end(); ++vertex_iter)
        {
            vertices_.emplace_back( new typename Manager::vertex_type(std::get<0>(*vertex_iter)) );
        }

        // std::tuple<int, int, int>;
        
        // push edges into container
        auto vertex_init_iter = inList.begin();
        auto vertex_iter = vertices_.begin();

        for (; vertex_init_iter != inList.end(); ++vertex_init_iter, ++vertex_iter)
        {
            for (auto edge_iter = std::get<1>(*vertex_init_iter).begin(); edge_iter != std::get<1>(*vertex_init_iter).end(); ++edge_iter)
            {
                auto& vertex2 = *std::find_if( vertices_.begin(), vertices_.end(), 
                    [edge_iter](typename Manager::vertex_ptr& vertexPtr){ return vertexPtr->Id() == std::get<0>(*edge_iter);}  );
                
                edges_.emplace_back( new typename Manager::edge_type( *vertex_iter, vertex2, std::get<1>(*edge_iter),std::get<2>(*edge_iter) )  );
            }
        }

        // initialize implementations - currently Adjacency List
        implementations_.emplace_back( new AdjacencyList(vertices_, edges_));
    }

    //------------------------------------------------------------------------------
    //
    //  Call implementations methods.
    //
    //------------------------------------------------------------------------------
    void
    Manager::AddVertex(int id)
    {
        // add vertex pointer to implementation structures
        std::for_each(implementations_.begin(), implementations_.end(),
            [&id](auto& pImplementation)
            { pImplementation->AddVertex(id); });
    }
    
    //------------------------------------------------------------------------------
    //
    //  Call implementations methods.
    //
    //------------------------------------------------------------------------------
    void
    Manager::RemoveVertex(int id)
    {
        // remove vertex from each implementation structure
        std::for_each(implementations_.begin(), implementations_.end(), 
            [&id](auto& pImplementation)
            { pImplementation->RemoveVertex(id); });
        // remove from data holder
    }

    //------------------------------------------------------------------------------
    //
    //  Call implementations methods.
    //
    //------------------------------------------------------------------------------
    void
    Manager::AddEdge(int id1,
                     int id2,
                     int direction,
                     int weight)
    {
        // remove vertex from each implementation structure
        std::for_each(implementations_.begin(), implementations_.end(), 
            [&id1, &id2, direction, weight](auto& pImplementation)
            { pImplementation->AddEdge(id1, id2, direction, weight); });
    }

    //------------------------------------------------------------------------------
    //
    //  Confirm edge existence.
    //
    //------------------------------------------------------------------------------
    bool
    Manager::Edge(int id1,
                  int id2,
                  int direction,
                  int weight) const
    {
        if (implementations_[activeIndex_]->Edge(id1, id2, direction, weight))
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
    Manager::RemoveEdge(int id1,
                        int id2,
                        int direction,
                        int weight)
    {
        // remove vertex from each implementation
        std::for_each(implementations_.begin(), implementations_.end(), 
            [&id1, &id2, &direction, &weight](auto& implementation)
            { implementation->RemoveEdge(id1, id2, direction, weight); } );
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    typename Manager::const edge_container&
    Manager::GetNeighbours(int id)
    { 
        return implementations_[activeIndex_]->GetNeighbours(id);
    }

    /*
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    int
    Manager::Size() const
    {
        return vertices_.size();
    }
    */

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void
    Manager::AddImplementation(  typename Manager::implementation_ptr implementation)
    {
        implementations_.push_back(implementation);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void
    Manager::RemoveImplementation(int index)
    {
        implementations_.erase(index);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void
    Manager::ChangeImplementation(int index)
    {
        activeIndex_ = index;
    }

} //    namespace implementation



//==============================================================================
// End of manager.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
