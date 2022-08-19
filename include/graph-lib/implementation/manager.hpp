//==============================================================================
///
/// @file manager.hpp
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
#ifndef GRAPH_LIB_IMPLEMENTATION_MANAGER_HPP
#define GRAPH_LIB_IMPLEMENTATION_MANAGER_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <initializer_list>
#include <utility>              // std::move
#include <tuple>
#include <algorithm>            // std::find

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/implementation/adjacency-list.hpp>
#include <graph-lib/implementation/incidence-matrix.hpp>

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
/// @brief <Description>
///
/// <Detailed description>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief Implementation related classes and functions.
//------------------------------------------------------------------------------
namespace implementation
{
    //------------------------------------------------------------------------------
    /// @brief Implements graph's functionality.
    ///
    /// Contains vertex and edge container and indices (implementations) over them.
    //------------------------------------------------------------------------------
    class Manager
    {
        //type aliases
        using edge_type                 = component::Edge<int>;
        using edge_container            = std::vector<edge_type>;
        using vertex_init_type          = int;
        using edge_init_type            = std::tuple<int, int, int>;
        using init_list_type            = std::tuple<vertex_init_type, std::vector<edge_init_type>>;
        using base_implementation       = BaseImplementation<int>;
        using implementation_ptr        = std::unique_ptr<base_implementation>;
        using implementation_container  = std::vector<implementation_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor.
        //------------------------------------------------------------------------------
        Manager();

        //------------------------------------------------------------------------------
        /// @brief Initializer list constructor.
        ///
        /// @param[in] initList
        ///
        //------------------------------------------------------------------------------
        Manager(std::initializer_list<init_list_type>&& initList);

        //------------------------------------------------------------------------------
        /// @brief Adds vertex with specefic id to a graph.
        /// 
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        AddVertex(int id);

        /*
        //------------------------------------------------------------------------------
        /// @brief Gets vertex with specific id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @retval True if Vertex exists.
        /// @retval False if Vertex doesn't exist.
        ///
        //------------------------------------------------------------------------------   
        bool
        GetVertex(int id) const;
        */

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from a graph.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveVertex(int id);
        
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
        AddEdge(int id1,
                int id2,
                int direction,
                int weight);

        //------------------------------------------------------------------------------
        /// @brief Confirm edge existence using given vertex ids.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @retval True Edge exists.
        /// @retval False Otherwise.
        ///
        //------------------------------------------------------------------------------
        bool
        Edge(int id1,
             int id2,
             int direction,
             int weight) const;

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
        RemoveEdge(int id1,
                   int id2,
                   int direction,
                   int weight);

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(int id) const;

        /*
        //------------------------------------------------------------------------------
        /// @brief Number of vertices in a graph.
        ///
        /// @return Vertex count.
        ///
        //------------------------------------------------------------------------------
        int
        Size() const;
        */

    private:

        //------------------------------------------------------------------------------
        /// @brief Adds new implementation to a graph.
        ///
        /// @param[in] pImpl Implementation pointer.
        ///
        //------------------------------------------------------------------------------
        void
        AddImplementation(implementation_ptr pImpl);

        //------------------------------------------------------------------------------
        /// @brief Remove implementation with a given index from a graph.
        ///
        /// @param[in] index Implementation storage index.
        ///
        //------------------------------------------------------------------------------
        void
        RemoveImplementation(int index);

        //------------------------------------------------------------------------------
        /// @brief Sets new index of active implementation.
        ///
        /// @param[in] index Implementation storage index.
        ///
        //------------------------------------------------------------------------------  
        void
        ChangeImplementation(int index);


    private:

        /// @brief Index of active implementation.
        int activeIndex_;

        /// @brief Implementation container.
        implementation_container implementations_;
    };

} //    namespace implementation



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



#endif // GRAPH_LIB_IMPLEMENTATION_MANAGER_HPP
//==============================================================================
// End of manager.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
