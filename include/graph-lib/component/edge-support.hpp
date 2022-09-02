//==============================================================================
///
/// @file edge-support.hpp
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
#ifndef GRAPH_LIB_COMPONENT_EDGE_SUPPORT_HPP
#define GRAPH_LIB_COMPONENT_EDGE_SUPPORT_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t


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
namespace component
{
	template< 	typename 	id_type>
	class Vertex;

	template< 	typename 	id_type>
	class Edge;

} // namespace component

namespace implementation
{
	template<class id_type>
	class AdjacencyList;

} // namespace implementation


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
	/// @brief graph components' traits.
	//------------------------------------------------------------------------------
	namespace traits
	{
		//------------------------------------------------------------------------------
		/// @brief Encapsulates types of edges direction.
		//------------------------------------------------------------------------------
		enum class edge_direction
		{
			/// @brief Undirected edge: v1 ----- v2.
			none,
			/// @brief Directed edge: v1 ----> v2.
			one_two
		};
	
	} // namespace traits

} // namespace component


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief Contains Vertex and Edge.
///
/// A common namespace for graph's basic components.
//------------------------------------------------------------------------------
namespace component
{
	//------------------------------------------------------------------------------
	//
	//  Edge == operator.
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator==(const Edge<id_type>& lhs,
			   const Edge<id_type>& rhs)
	{
		return ( (lhs.GetVertex(0).Id() == rhs.GetVertex(0).Id()) &&
				 (lhs.GetVertex(1).Id() == rhs.GetVertex(1).Id()) &&
				 (lhs.Direction() == rhs.Direction()) &&
				 (lhs.Weight() == rhs.Weight()) );
	}

	//------------------------------------------------------------------------------
	//
	//  Edge != operator.
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator!=(const Edge<id_type>& lhs,
			   const Edge<id_type>& rhs)
	{
		return ( (lhs.GetVertex(0).Id() != rhs.GetVertex(0).Id()) ||
				 (lhs.GetVertex(1).Id() != rhs.GetVertex(1).Id()) ||
				 (lhs.Direction() != rhs.Direction()) ||
				 (lhs.Weight() != rhs.Weight()) );
	}

	//------------------------------------------------------------------------------
	//
	//  Edge < operator
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator<(const Edge<id_type>& lhs,
			  const Edge<id_type>& rhs)
	{
		return lhs.Weight() < rhs.Weight();
	}

	//------------------------------------------------------------------------------
	//
	//  Edge < operator
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator<=(const Edge<id_type>& lhs,
			   const Edge<id_type>& rhs)
	{
		return lhs.Weight() <= rhs.Weight();
	}

}  // namespace component



#endif // GRAPH_LIB_COMPONENT_EDGE_SUPPORT_HPP
//==============================================================================
// End of edge-support.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
