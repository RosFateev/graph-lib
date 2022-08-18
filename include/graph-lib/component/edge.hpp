#ifndef GRAPH_COMPONENT_EDGE_HPP
#define GRAPH_COMPONENT_EDGE_HPP





//std
#include <memory>								// shared_ptr
#include <array>
//related
#include "graph-component/vertex.hpp"
#include "graph-component/edge-support.hpp"





//! component
/*!
 * A common namespace for graph's components: vertex and edge. 
*/
namespace component
{
	//! Edge
	/*!
	 * Edge represents a connection between 2 instances of Vertex.
	 * It contains pointers to vertices, direction and weight.
	 */
	template< class id_type>
	class Edge
	{		
		using vertex_type 			= Vertex<id_type>;
		using vertex_ptr 			= std::shared_ptr<vertex_type>;
		using vertex_container 		= std::array<const vertex_ptr, 2>;
		// < direction, weight >
		using connection_property	= std::tuple<int, int>;

	public:

		//! Value constructor
		/*!
			\param const vertex_ptr pointer1
			\param const vertex_ptr pointer2
			\param int direction
			\param int weight
		 */
								Edge( 	const vertex_ptr, 
										const vertex_ptr, 
										int 				direction = traits::edge_direction::none, 
										int 				weight = 0);

		//! Move constructor
		/*!
			\param Edge&&
		 */
								Edge( Edge&&);

		//! Virtual destructor
		/*!
		 * So that Edge can be extended to Multi- or HyperEdge
		 */
		virtual 				~Edge();



		//! Move assignment operator
		/*!
			\param Edge&&
			\return reference to itself
		*/
		Edge&	    			operator=(	Edge&&);

		//! GetVertex
		/*!
		 * Accesses Edge's endpoint.
			\param int index
			\return endpoint
		*/
		const vertex_type& 		GetVertex(int)  const;

		//! GetPointer
		/*!
		 * Accesses Edge's endpoint pointer.
			\param int index
			\return endpoint pointer
		*/
		const vertex_ptr& 		GetPointer(int) const;

		//! Direction
		/*! 
		 * It's virtual to allow extension
			\return direction type
		*/
		virtual int 			Direction() const; /*!< Get edge direction */
		
		//! Weight
		/*! 
		 * It's virtual to allow extension
			\return weight
		*/
		virtual int				Weight() const; /*!< Get edge weight */



	private:

		//! Container
		/*!
		 * Contains vertices.
		 */
		vertex_container 		container_;
		
		//! Property
		/*!
		 * (direction, weight) tuple describing connection between endpoints
		 */
		connection_property		property_;
	};
	
} //	namespace component










//
// Edge class definition
//
namespace component
{

	//
	// Constructors
	//
	template<   class 	id_type>
	Edge<id_type>::Edge(	  const typename Edge<id_type>::vertex_ptr 		inVertex1, 
						      const typename Edge<id_type>::vertex_ptr 		inVertex2,
						      int 											direction,
						      int 											inWeight) :	container_({ inVertex1, inVertex2}),
						      															property_(std::make_tuple(	direction,
						      																						inWeight))
	{	}
	


	//
	template<   class 	id_type>
	Edge<id_type>::Edge(   		Edge<id_type>&&	inEdge) :  	container_(std::move(inEdge.container_)),
	                                                        property_(std::move(inEdge.property_))
	{	}



	template<   class 	id_type>
	Edge<id_type>::~Edge()
	{	}





	//
	// Operators
	//
	template<   class 	id_type>
	Edge<id_type>&  	Edge<id_type>::operator=( Edge<id_type>&& 	inEdge)
	{
		container_ 	= std::move(inEdge.container_),
		property_ 	= std::move(inEdge.property_);

		return *this;
	}


	


	//
	// Accessors
	//
	template<   class 	id_type>
	const typename Edge<id_type>::vertex_type&	    Edge<id_type>::GetVertex(int index) 	const
	{
		return *GetPointer(index);
	}

	template<   class 	id_type>
	const typename Edge<id_type>::vertex_ptr&	    Edge<id_type>::GetPointer(int index) 	const
	{
		return container_[index];
	}



	//
	template<   class 	id_type>
	int 					Edge<id_type>::Direction() const
	{
		return std::get<0>(property_);
	}



	//
	template<   class 	id_type>
	int     				Edge<id_type>::Weight() const
	{
		return std::get<1>(property_);
	}
	
} //	namespace component



#endif //GRAPH_COMPONENT_EDGE_HPP