//==============================================================================
///
/// @file vertex.hpp
///
/// @brief Graph vertex implementation.
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
#ifndef GRAPH_LIB_COMPONENT_VERTEX_HPP
#define GRAPH_LIB_COMPONENT_VERTEX_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <utility>                  // std::move

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-component/vertex-support.hpp"       // 


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
/// @brief Contains Vertex and Edge.
///
/// A common namespace for graph's basic components.
//------------------------------------------------------------------------------
namespace component
{

    //------------------------------------------------------------------------------
    /// @brief Basic graph component.
    ///
    /// One of the most basic graph components representing a point on a plane.
    //------------------------------------------------------------------------------
    template<class id_type>
    class Vertex
    {
    public:

        //------------------------------------------------------------------------------
        ///
        /// @brief Value constructor.
        ///
        /// @param[in] id Input vertex id.
        ///
        //------------------------------------------------------------------------------
        explicit Vertex(id_type id);

        //------------------------------------------------------------------------------
        ///
        /// @brief Copy constructor.
        ///
        /// @param[in] vertex Input prototype vertex.
        ///
        //------------------------------------------------------------------------------
        Vertex(const Vertex& vertex);

        //------------------------------------------------------------------------------
        ///
        /// @brief Move constructor.
        ///
        /// @param[in] vertex Input prototype vertex.
        ///
        //------------------------------------------------------------------------------
        Vertex(Vertex&& vertex);

        //------------------------------------------------------------------------------
        ///
        /// @brief Copy assignment operator.
        ///
        /// @param[in] vertex Input prototype vertex.
        ///
        /// @return Reference to itself.
        ///
        //------------------------------------------------------------------------------
        const Vertex&
        operator=(const Vertex& vertex);

        //------------------------------------------------------------------------------
        ///
        /// @brief Move assignment operator.
        ///
        /// @param[in] vertex Input prototype vertex.
        ///
        /// @return Reference to itself.
        ///
        //------------------------------------------------------------------------------
        Vertex&
        operator=(Vertex&& vertex);

        //------------------------------------------------------------------------------
        ///
        /// @brief Id getter.
        ///
        /// @return Reference to vertex id.
        ///
        //------------------------------------------------------------------------------
        const id_type&
        Id() const;

        //------------------------------------------------------------------------------
        ///
        /// @brief Individual coordinate setter.
        ///
        /// @param[in] index Determines coordinate to set.
        ///
        /// @param[in] value Intended coordinate value.
        ///
        //------------------------------------------------------------------------------
        void
        Coordinate(int index,
                   float value);

        //------------------------------------------------------------------------------
        ///
        /// @brief Full coordinate setter.
        ///
        /// @param[in] xValue Intended x coordinate value.
        ///
        /// @param[in] yValue Intended y coordinate value.
        ///
        //------------------------------------------------------------------------------
        void
        Coordinate(float xValue,
                   float yValue);

        //------------------------------------------------------------------------------
        ///
        /// @brief Individual coordinate getter.
        ///
        /// @param[in] index Determines coordinate to get.
        ///
        /// @return Coordinate value.
        ///
        //------------------------------------------------------------------------------
        float
        Coordinate(int) const;


    private:
        
        /// @brief Vertex id.
        id_type id_;

        /// @brief Vertex coordinate.
        float x_;
        float y_;
    };

} //    namespace component



//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------
namespace component
{
    //------------------------------------------------------------------------------
    //
    //  Value constructor
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Vertex<id_type>::Vertex(id_type id) : id_(id),
                                          x_(0.f),
                                          y_(0.f)
    {   }

    //------------------------------------------------------------------------------
    //
    //  Copy constructor
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Vertex<id_type>::Vertex(const Vertex<id_type>& vertex) : id_(vertex.id_),
                                                             x_(vertex.x_),
                                                             y_(vertex.y_)
    {   }

    //------------------------------------------------------------------------------
    //
    //  Move constructor
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Vertex<id_type>::Vertex(Vertex<id_type>&& vertex) : id_(std::move(vertex.id_)),
                                                        x_(vertex.x_),
                                                        y_(vertex.y_)
    {   }

    //------------------------------------------------------------------------------
    //
    //  Copy assignment operator
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const Vertex<id_type>&
    Vertex<id_type>::operator=(const Vertex<id_type>& vertex)
    {
        id_ = vertex.id_;
        x_ = vertex.x_;
        y_ = vertex.y_;

        return *this;
    }

    //------------------------------------------------------------------------------
    //
    //  Move assignment operator
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Vertex<id_type>&
    Vertex<id_type>::operator=(Vertex<id_type>&& vertex)
    {
        id_ = std::move(vertex.id_);

        return *this;
    }

    //------------------------------------------------------------------------------
    //
    //  Id getter
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    const id_type& 
    Vertex<id_type>::Id() const
    { 
        return id_;
    }

    //------------------------------------------------------------------------------
    //
    //  Individual coordinate setter
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Vertex<id_type>::Coordinate(int index, 
                                float value)
    {
        (index == 0) ? x_ = value : y_ = value;
    }

    //------------------------------------------------------------------------------
    //
    //  Full coordinate setter
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Vertex<id_type>::Coordinate(float xValue,
                                float yValue)
    {
        x_ = xValue;
        y_ = yValue;
    }

    //------------------------------------------------------------------------------
    //
    //  Individual coordinate getter
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    float
    Vertex<id_type>::Coordinate(int index) const
    {
        return (index == 0) ? x_ : y_;
    }

} //    namespace component


//
#endif // TEMPLATE_H
//==============================================================================
// End of template.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
