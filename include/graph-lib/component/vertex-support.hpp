//==============================================================================
///
/// @file vertex-support.hpp
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
#ifndef GRAPH_LIB_COMPONENT_VERTEX_SUPPORT_HPP
#define GRAPH_LIB_COMPONENT_VERTEX_SUPPORT_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <cstddef> 				// size_t
#include <functional> 			// std::hash


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
	template<class id_type>
	class Vertex;

	template<class id_type>
	class Edge;

} // 	namespace component

namespace implementation
{
	template<class id_type>
	class AdjacencyList;

} //	namespace implementation


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
		/// @brief Vertex traits define usefull constants etc.
		//------------------------------------------------------------------------------
		template<class id_type>
		class vertex_traits
		{
		public:
			
			static const id_type invalid_;
		};

		/*
		//------------------------------------------------------------------------------
		/// @brief Vertex traits integer specification.
		//------------------------------------------------------------------------------
		template<>
		class vertex_traits<int>
		{
		public:

			//------------------------------------------------------------------------------
			/// @brief Vertex<int> invalid value.
			//------------------------------------------------------------------------------
			static const int invalid_;
		};

		//------------------------------------------------------------------------------
		/// @brief Vertex traits float specification.
		//------------------------------------------------------------------------------
		template<>
		class vertex_traits<float>
		{
		public:

			//------------------------------------------------------------------------------
			/// @brief Vertex<int> invalid value.
			//------------------------------------------------------------------------------
			static const float invalid_;
		};

		

		//------------------------------------------------------------------------------
		/// @brief Vertex traits string specification.
		//------------------------------------------------------------------------------
		template<>
		class vertex_traits<std::string>
		{
		public:

			//------------------------------------------------------------------------------
			/// @brief Vertex<int> invalid value.
			//------------------------------------------------------------------------------
			static const std::string invalid_;
		};
		*/

	} // namespace traits

} // namespace component


//------------------------------------------------------------------------------
/// @brief Contains Vertex and Edge.
///
/// A common namespace for graph's basic components.
//------------------------------------------------------------------------------
namespace component
{
	//------------------------------------------------------------------------------
	/// @brief graph components' support functionality: hash, comparator, etc.
	//------------------------------------------------------------------------------
	namespace support
	{
		//------------------------------------------------------------------------------
		/// @brief Vertex hash.
		///
		/// Enables Vertex as a key in std::map.
		//------------------------------------------------------------------------------
		template<class id_type>
		class vertex_hash
		{
			using vertex_type = component::Vertex<id_type>;

		public:

			//------------------------------------------------------------------------------
			/// @brief Computes hash from Vertex id.
			///
			/// @param[in] vertex Input vertex.
			///
			/// @return Vertex hash.
			///
			//------------------------------------------------------------------------------
			size_t
			operator()(const vertex_type& vertex) const
			{
				return std::hash<id_type>()(vertex.Id());
			}
		};

		//------------------------------------------------------------------------------
		/// @brief Vertex equality comparison.
		//------------------------------------------------------------------------------
		template<class id_type>
		class vertex_equal
		{
			using vertex_type = component::Vertex<id_type>;

		public:

			//------------------------------------------------------------------------------
			/// @brief Compares vertices by id.
			///
			/// @param[in] lhs First vertex.
			///
			/// @param[in] rhs Second vertex.
			///
			/// @retval True If lhs == rhs.
			/// @retval False Otherwise.
			///
			//------------------------------------------------------------------------------
			bool
			operator()(const vertex_type& lhs,
	                   const vertex_type& rhs) const
			{
				return lhs.Id() == rhs.Id();
			}
		};

		//------------------------------------------------------------------------------
		/// @brief Vertex order comparison.
		//------------------------------------------------------------------------------
		template<class id_type>
		class vertex_less
		{
			using vertex_type = component::Vertex<id_type>;

		public:

			//------------------------------------------------------------------------------
			/// @brief Compares vertices by id.
			///
			/// @param[in] lhs First vertex.
			///
			/// @param[in] rhs Second vertex.
			///
			/// @retval True If lhs < rhs.
			/// @retval False Otherwise.
			///
			//------------------------------------------------------------------------------
			bool
			operator()(const vertex_type& lhs,
	                   const vertex_type& rhs) const
			{
				return lhs.Id() < rhs.Id();
			}

		};

	} // namespace support

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
	//  Vertex == operator.
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator==(const Vertex<id_type>& lhs,
			   const Vertex<id_type>& rhs)
	{
		return lhs.Id() == rhs.Id();
	}

	//------------------------------------------------------------------------------
	//
	//  Vertex < operator
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	operator<(const Vertex<id_type>& lhs,
			  const Vertex<id_type>& rhs)
	{
		return lhs.Id() < rhs.Id();
	}

}  // namespace component



#endif // GRAPH_LIB_COMPONENT_VERTEX_SUPPORT_HPP
//==============================================================================
// End of vertex-support.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
