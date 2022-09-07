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
#include <utility> 					// std::pair

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

	public:

		//------------------------------------------------------------------------------
		/// @brief Default constructor.
		///
		//------------------------------------------------------------------------------
		Edge();

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
		/// @brief Copy constructor.
		///
		/// @param[in] edge Edge to copy.
		///
		//------------------------------------------------------------------------------
		Edge(const Edge& edge);

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

		//------------------------------------------------------------------------------
		/// @brief Set edge weight.
		///
		/// @param[in] weight New weight.
		///
		//------------------------------------------------------------------------------
		virtual void
		SetWeight(int weight);

		//------------------------------------------------------------------------------
		/// @brief Get edge capacity.
		///
		/// @return Edge capacity.
		///
		//------------------------------------------------------------------------------
		virtual int
		GetCapacity() const;

		//------------------------------------------------------------------------------
		/// @brief Set edge capacity.
		///
		/// @param[in] capacity New capacity.
		///
		//------------------------------------------------------------------------------
		virtual void
		SetCapacity(int capacity);

		//------------------------------------------------------------------------------
		/// @brief Get edge flow.
		///
		/// @return Edge flow.
		///
		//------------------------------------------------------------------------------
		virtual int
		GetFlow() const;

		//------------------------------------------------------------------------------
		/// @brief Set edge flow.
		///
		/// @param[in] flow New flow.
		///
		//------------------------------------------------------------------------------
		virtual void
		SetFlow(int flow);


	public:

		/// @brief Invalid vertex constant.
        static const Edge<id_type> invalidInstance_;


	private:

		/// @brief First endpoit vertex.
		const vertex_type& first_;

		/// @brief Second endpoit vertex.
		const vertex_type& second_;

		/// @brief Edge direction.
		traits::edge_direction direction_;

		/// @brief Edge weight.
		int weight_;

		/// @brief Edge capacity used in flow network algorithms.
		int capacity_;

		/// @brief Edge flow used in flow network algorithms.
		int flow_;
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
	Edge<id_type>::Edge() :	first_(Vertex<id_type>::invalidInstance_),
							second_(Vertex<id_type>::invalidInstance_),
							direction_(traits::edge_direction::none),
							weight_(0),
							capacity_(0)
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>::Edge(const typename Edge<id_type>::vertex_type& vertex1,
						const typename Edge<id_type>::vertex_type& vertex2,
						traits::edge_direction direction,
						int weight) : 
								first_(vertex1),
								second_(vertex2),
								direction_(direction),
								weight_(weight),
								capacity_(0)
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	Edge<id_type>::Edge(const Edge<id_type>& edge) : first_(edge.first_),
													 second_(edge.second_),
													 direction_(edge.direction_),
													 weight_(edge.weight_),
													 capacity_(edge.capacity_)
	{	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename Edge<id_type>::vertex_type&
	Edge<id_type>::GetVertex(int index) const
	{
		return (index == 0 ? first_ : second_);
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
		return direction_;
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
		return weight_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	Edge<id_type>::SetWeight(int weight)
	{
		weight_ = weight;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	int
	Edge<id_type>::GetCapacity() const
	{
		return capacity_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	Edge<id_type>::SetCapacity(int capacity)
	{
		capacity_ = capacity;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	int
	Edge<id_type>::GetFlow() const
	{
		return flow_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	Edge<id_type>::SetFlow(int flow)
	{
		flow_ = flow;
	}

} //	namespace component



#endif // GRAPH_LIB_COMPONENT_EDGE_HPP
//==============================================================================
// End of edge.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
