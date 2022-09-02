//==============================================================================
///
/// @file vertex.cpp
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
#include "graph-lib/component/vertex.hpp"   // Vertex


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
    const Vertex<char> 
    Vertex<char>::invalidInstance_ = Vertex<char>(traits::vertex_traits<char>::invalid_);

    // int
    template<>
    const Vertex<int> 
    Vertex<int>::invalidInstance_ = Vertex<int>(traits::vertex_traits<int>::invalid_);

    // float
    template<>
    const Vertex<float> 
    Vertex<float>::invalidInstance_ = Vertex<float>(traits::vertex_traits<float>::invalid_);

    // string
    template<>
    const Vertex<std::string> 
    Vertex<std::string>::invalidInstance_ = Vertex<std::string>(traits::vertex_traits<std::string>::invalid_);
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
// End of vertex.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
