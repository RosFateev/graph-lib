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
#include <string>

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

namespace component
{
    // instantiate invalid vertices for various classes
    // char
    template<>
    const Edge<char> 
    Edge<char>::invalidInstance_ = Edge<char>(
            Vertex<char>::invalidInstance_,
            Vertex<char>::invalidInstance_);

    // int
    template<>
    const Edge<int> 
    Edge<int>::invalidInstance_ = Edge<int>(
            Vertex<int>::invalidInstance_,
            Vertex<int>::invalidInstance_);

    // float
    template<>
    const Edge<float> 
    Edge<float>::invalidInstance_ = Edge<float>(
            Vertex<float>::invalidInstance_,
            Vertex<float>::invalidInstance_);

    // string
    template<>
    const Edge<std::string> 
    Edge<std::string>::invalidInstance_ = Edge<std::string>(
            Vertex<std::string>::invalidInstance_,
            Vertex<std::string>::invalidInstance_);
}

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



//==============================================================================
// End of edge.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
