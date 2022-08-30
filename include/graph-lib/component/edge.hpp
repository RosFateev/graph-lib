//==============================================================================
///
/// @file edge.hpp
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
#ifndef GRAPH_LIB_COMPONENT_EDGE_HPP
#define GRAPH_LIB_COMPONENT_EDGE_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <memory>					// shared_ptr
#include <array>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/vertex.hpp"
#include "graph-lib/component/edge-support.hpp"

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
/// @brief Contains Vertex and Edge.
///
/// A common namespace for graph's basic components.
//------------------------------------------------------------------------------
namespace component
{
	//------------------------------------------------------------------------------
	/// @brief Edge class declaration.
	///
	/// Edge represents a connection between 2 instances of Vertex.
	/// It contains pointers to vertices, direction and weight.
	///
	//------------------------------------------------------------------------------
	template< class id_type>
	class Edge
	{		
		using vertex_type 			= Vertex<id_type>;
		using vertex_container 		= std::array<const vertex_type, 2>;
		using connection_property	= std::tuple<traits::edge_direction, int>;

	public:

		//------------------------------------------------------------------------------
		/// @brief Value constructor.
		///
		/// @param[in] vertex1 First vertex.
		///
		/// @param[in] vertex2 Second vertex.
		///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
		//------------------------------------------------------------------------------
		Edge(const vertex_type& vertex1, 
			 const vertex_type& vertex2,
			 traits::edge_direction direction = traits::edge_direction::none, 
			 int weight = 0);

		//------------------------------------------------------------------------------
		/// @brief Move constructor.
		///
		/// @param[in] edge Edge to move to.
		//------------------------------------------------------------------------------
		Edge(Edge&& edge);

		//------------------------------------------------------------------------------
		/// @brief Virtual destructor.
		//------------------------------------------------------------------------------
		virtual ~Edge();

		//------------------------------------------------------------------------------
		/// @brief Move assignment operator.
		///
		/// @param[in] edge Edge to move to.
		///
		/// @return Reference to itself.
		///
		//------------------------------------------------------------------------------
		Edge&
		operator=(Edge&& edge);

		//------------------------------------------------------------------------------
		/// @brief Get edge's vertex with specific index.
		///
		/// @param[in] index Vertex position.
		///
		/// @return Desired vertex.
		///
		//------------------------------------------------------------------------------
		const vertex_type&
		GetVertex(int index) const;

		//------------------------------------------------------------------------------
		/// @brief Get edge direction.
		///
		/// @return Direction type.
		///
		//------------------------------------------------------------------------------
		virtual traits::edge_direction
		GetDirection() const;

		//------------------------------------------------------------------------------
		/// @brief Get edge weight.
		///
		/// @return Edge weight.
		///
		//------------------------------------------------------------------------------
		virtual int
		GetWeight() const;


	private:

		//------------------------------------------------------------------------------
		/// @brief Vertex container.
		//------------------------------------------------------------------------------
		vertex_container container_;
		
		//------------------------------------------------------------------------------
		/// @brief Connection property.
		///
		/// (direction, weight) tuple describing connection between endpoints
		//------------------------------------------------------------------------------
		connection_property	property_;
	};
	
} //	namespace component


//------------------------------------------------------------------------------
/// @brief Contains Vertex and Edge.
///
/// A common namespace for graph's basic components.
//------------------------------------------------------------------------------
namespace component
{
	//------------------------------------------------------------------------------
	/// @brief Edge int type specification.
	///
	/// Edge<int> is a simplified edge type used in graph implementations.
	/// References to vertices replaced by int indexes.
	///
	//------------------------------------------------------------------------------
	template<>
	class Edge<int>
	{
		using vertex_container 		= std::array<int, 2>;
		using connection_property	= std::tuple<traits::edge_direction, int>;

	public:

		//------------------------------------------------------------------------------
		/// @brief Value constructor.
		///
		/// @param[in] index1 Index of first vertex in implementation structure.
		///
		/// @param[in] index2 Index of second vertex in implementation structure.
		///
        /// @param[in] direction How vertices are connected.
        ///
        /// @param[in] weight Edge weight.
		//------------------------------------------------------------------------------
		Edge(int index1, 
			 int index2,
			 traits::edge_direction direction = traits::edge_direction::none, 
			 int weight = 0);

		//------------------------------------------------------------------------------
		/// @brief Move constructor.
		///
		/// @param[in] edge Edge to move to.
		//------------------------------------------------------------------------------
		Edge(Edge&& edge);

		//------------------------------------------------------------------------------
		/// @brief Virtual destructor.
		//------------------------------------------------------------------------------
		virtual ~Edge();

		//------------------------------------------------------------------------------
		/// @brief Move assignment operator.
		///
		/// @param[in] edge Edge to move to.
		///
		/// @return Reference to itself.
		///
		//------------------------------------------------------------------------------
		Edge&
		operator=(Edge&& edge);

		//------------------------------------------------------------------------------
		/// @brief Get edge's vertex with specific index.
		///
		/// @param[in] index Vertex position.
		///
		/// @return Desired vertex index.
		///
		//------------------------------------------------------------------------------
		int
		GetVertex(int index) const;

		//------------------------------------------------------------------------------
		/// @brief Get edge direction.
		///
		/// @return Direction type.
		///
		//------------------------------------------------------------------------------
		virtual traits::edge_direction
		GetDirection() const;

		//------------------------------------------------------------------------------
		/// @brief Get edge weight.
		///
		/// @return Edge weight.
		///
		//------------------------------------------------------------------------------
		virtual int
		GetWeight() const;


	private:

		//------------------------------------------------------------------------------
		/// @brief Vertex container.
		//------------------------------------------------------------------------------
		vertex_container container_;
		
		//------------------------------------------------------------------------------
		/// @brief Connection property.
		///
		/// (direction, weight) tuple describing connection between endpoints
		//------------------------------------------------------------------------------
		connection_property	property_;
	};
	
} //	namespace component


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  General Edge class implementation
//
//------------------------------------------------------------------------------
namespace component
{
	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>::Edge(const typename Edge<id_type>::vertex_type& vertex1,
						const typename Edge<id_type>::vertex_type& vertex2,
						traits::edge_direction direction,
						int inWeight) :	container_({ vertex1, vertex2}),
										property_(std::make_tuple(direction,
																  inWeight))
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>::Edge(Edge<id_type>&& edge) : container_(std::move(edge.container_)),
	                                              property_(std::move(edge.property_))
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>::~Edge()
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>&
	Edge<id_type>::operator=(Edge<id_type>&& edge)
	{
		container_ 	= std::move(edge.container_),
		property_ 	= std::move(edge.property_);

		return *this;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename Edge<id_type>::vertex_type&
	Edge<id_type>::GetVertex(int index) const
	{
		return container_.at(index);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	traits::edge_direction
	Edge<id_type>::GetDirection() const
	{
		return std::get<0>(property_);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	int
	Edge<id_type>::GetWeight() const
	{
		return std::get<1>(property_);
	}
	
} //	namespace component



#endif // GRAPH_LIB_COMPONENT_EDGE_HPP
//==============================================================================
// End of edge.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
