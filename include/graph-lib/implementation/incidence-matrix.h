//==============================================================================
///
/// @file incidence-matrix.h
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
#ifndef GRAPH_LIB_IMPLEMENTATION_INCIDENCE_MATRIX_H
#define GRAPH_LIB_IMPLEMENTATION_INCIDENCE_MATRIX_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <initializer_list>
#include <vector>
#include <map>
#include <utility>                          //std::hash, std::forward
#include <memory>                           //shared_ptr, unique_ptr

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/component/edge.hpp>
#include <graph-lib/implementation/implementation.hpp>


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
/// @brief Implementation related classes and functions.
//------------------------------------------------------------------------------
namespace implementation
{
    //------------------------------------------------------------------------------
    /// @brief An implementation of incidence matrix structure.
    //------------------------------------------------------------------------------
    class IncidenceMatrix : public BaseImplementation
    {
        using edge_type             = component::Edge<int>;
        using edge_ptr              = std::shared_ptr<edge_type>;
        using edge_container        = std::vector<bool>;
        using data_structure        = std::map<vertex_ptr, edge_container, component::support::VertexPtrLess<id_type>>;
        using vertex_init_container = std::vector<vertex_ptr>;
        using edge_init_container   = std::vector<edge_ptr>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor
        //------------------------------------------------------------------------------
        IncidenceMatrix();
        
        //------------------------------------------------------------------------------
        /// @brief Value constructor
        ///
        /// @param[in]
        ///
        /// @param[in]
        ///
        //------------------------------------------------------------------------------
        IncidenceMatrix(const vertex_init_container&, 
                        const edge_init_container&);

        //------------------------------------------------------------------------------
        /// @brief Virtual destructor.
        //------------------------------------------------------------------------------
        virtual ~IncidenceMatrix();

        //------------------------------------------------------------------------------
        /// @brief Add vertex to incidence matrix.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddVertex(int id) override;

        //------------------------------------------------------------------------------
        /// @brief Confirms if vertex exists.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @retval True if Vertex exists.
        /// @retval False if Vertex doesn't exist.
        ///
        //------------------------------------------------------------------------------
        virtual bool
        GetVertex(int id) const override;

        //------------------------------------------------------------------------------
        /// @brief Removes vertex with id from implementation.
        ///
        /// @param[in] id Vertex id.
        ///
        //------------------------------------------------------------------------------
        virtual void
        RemoveVertex(int id) override;

        //------------------------------------------------------------------------------
        /// @brief Add edge pointer to incidence matrix.
        ///
        /// @param[in] pEdge Pointer to edge.
        ///
        //------------------------------------------------------------------------------
        virtual void
        AddEdge(const edge_ptr& pEdge) override;
        
        //------------------------------------------------------------------------------
        /// @brief Get edge pointer for given vertex ids.
        ///
        /// @param[in] id1 First vertex id.
        ///
        /// @param[in] id2 Second vertex id.
        ///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @return Pointer to desired edge.
        ///
        //------------------------------------------------------------------------------
        virtual const edge_ptr&
        GetEdge(int id1,
                int id2,
                int direction,
                int weight) const override;

        //------------------------------------------------------------------------------
        /// @brief Removes edge pointer with given vertex ids.
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
                   int weight) override;

        //------------------------------------------------------------------------------
        /// @brief Get neighbours of the vertex with given id.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @return Edges to neighbours.
        ///
        //------------------------------------------------------------------------------
        const edge_container&
        GetNeighbours(int id) const override;


    private:
        
        /// @brief Indicates if IncidenceMatrix object needs to be updated.
        bool isValid_;

        /// @brief Incidence matrix container.
        data_structure matrix_;

    };

} // namespace implementation



#endif // GRAPH_LIB_IMPLEMENTATION_INCIDENCE_MATRIX_H
//==============================================================================
// End of incidence-matrix.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
