//==============================================================================
///
/// @file edge.cpp
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
#include "graph-lib/component/edge.hpp"


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

//------------------------------------------------------------------------------
//
//  Integer Edge class implementation
//
//------------------------------------------------------------------------------
namespace component
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Edge<int>::Edge(int index1,
                    int index2,
                    traits::edge_direction direction,
                    int inWeight) : container_({ index1, index2}),
                                    property_(std::make_tuple(direction,
                                                              inWeight))
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Edge<int>::Edge(Edge<int>&& inEdge) : container_(std::move(inEdge.container_)),
                                          property_(std::move(inEdge.property_))
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Edge<int>::~Edge()
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Edge<int>&
    Edge<int>::operator=(Edge<int>&& inEdge)
    {
        container_ = std::move(inEdge.container_),
        property_ = std::move(inEdge.property_);

        return *this;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    int
    Edge<int>::GetVertex(int index) const
    {
        return container_.at(index);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    traits::edge_direction
    Edge<int>::GetDirection() const
    {
        return std::get<0>(property_);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    int
    Edge<int>::GetWeight() const
    {
        return std::get<1>(property_);
    }
    
} //    namespace component



//==============================================================================
// End of edge.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================