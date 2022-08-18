#ifndef GRAPH_COMPONENT_EDGE_SUPPORT_HPP
#define GRAPH_COMPONENT_EDGE_SUPPORT_HPP





//std
#include <algorithm>





// forward declarations
namespace implementation
{
	template<   typename 	id_type>
	class AdjacencyList;

}

namespace implementation
{
	template<   typename 	id_type>
	class IncidenceMatrix;
}

namespace component
{
	template< 	typename 	id_type>
	class Vertex;

	template< 	typename 	id_type>
	class Edge;
}





//! component
/*!
 * A common namespace for graph's components: vertex and edge. 
*/
namespace component
{

	//! traits
	/*!
	 * Namespace containing graph components' traits.
	*/
	namespace traits
	{
		//! edge_direction
		/*!
		 * Encapsulates types of edges direction
		 */
		enum edge_direction
		{
			//! none
			/*!
			 * undirected edge: v1 ----- v2
			 */
			none,
			//! one_two
			/*!
			 * directed edge: v1 ----> v2
			 */
			one_two
		};
	
	} //	namespace traits
} // 	namespace component





//! component
/*!
 * A common namespace for graph's components: vertex and edge. 
*/
namespace component
{
	//! traits
	/*!
	 * Namespace containing graph components' traits.
	*/
	namespace traits
	{
		//! edge_traits
		/*!
		 * Edge traits provide additional information that may be used in algorithms(i.e some specific reserved values etc)
		 * Base class.
		*/
		template<   typename 	id_type>
		class edge_traits
		{	};

	} //	namespace edgetraits
	



	//! policies
	/*!
	 * Namespace containing graph components' policies.
	*/
	namespace policies
	{
		//! edge_allocator
		/*!
		 * Storage policy base class used in graph's implementations to appropriately place edges depending on their type.
		 */
		template<   typename id_type,
					template<	typename> typename container_type> 
		class edge_allocator
		{   };





		//! edge_allocator<AdjacencyList>
		/*!
		 * Storage policy instantiation for AdjacencyList structure.
		*/
		template<   typename id_type>
		class edge_allocator<  id_type,
		                       implementation::AdjacencyList>
		{

			using vertex_type 		= Vertex<id_type>;
			using vertex_ptr 		= std::shared_ptr<vertex_type>;
			using edge_type 		= Edge<id_type>;
			using edge_ptr 			= std::shared_ptr<edge_type>;
			using structure_type 	= implementation::AdjacencyList<id_type>;
		
		public:

			//! Value constructor
			/*!
				\param AdjacencyList&
			 */
			explicit  	edge_allocator(   structure_type& inList) : 	owner_(inList)
			{   }

			//! Copy constructor
			/*!
			 * Deleted.
			*/
						edge_allocator( 	const edge_allocator&) 	= delete;

			//! Allocate
			/*!
			 * Places an edge into data structure.
				\param const vertex_ptr pointer1
				\param const vertex_ptr pointer2
				\param int direction
				\param int weight
			 */
			void 		Allocate(   const vertex_ptr 	inVertexPtr1,
									const vertex_ptr 	inVertexPtr2,
									int 				type, 
									int 				weight)
			{
				if (type == traits::edge_direction::one_two)
				{
					// directed edge

					AllocateOneTwo(inVertexPtr1, inVertexPtr2, type, weight);
				}
				else
				{
					// undirected edge == two directed

					AllocateOneTwo(inVertexPtr1, inVertexPtr2, traits::edge_direction::one_two, weight);
					AllocateOneTwo(inVertexPtr2, inVertexPtr1, traits::edge_direction::one_two, weight);
				}
			}

			//! Remove
			/*!
			 * Removes an edge from data structure.
				\param const vertex_ptr pointer1
				\param const vertex_ptr pointer2
				\param int direction
			 */
			void 		Remove(   	const vertex_ptr& 	inVertexPtr1,
									const vertex_ptr& 	inVertexPtr2,
									int 				type)
			{
				if (type == traits::edge_direction::one_two)
				{
					RemoveOneTwo(inVertexPtr1, inVertexPtr2);
				}
				else
				{
					RemoveOneTwo(inVertexPtr1, inVertexPtr2);
					RemoveOneTwo(inVertexPtr2, inVertexPtr1);
				}
			}


		private:

			//! AllocateOneTwo
			/*!
			 * Place directed v1 ----> v2 edge. Used as an internal routine in Allocate.
			 */
			void AllocateOneTwo(	const vertex_ptr 	inVertexPtr1,
									const vertex_ptr 	inVertexPtr2,
									int 				type, 
									int 				weight)
			{
				owner_.list_.at(inVertexPtr1).emplace_back(inVertexPtr1, inVertexPtr2, type, weight);
			}

			//! RemoveOneTwo
			/*!
			 * Removes a directed edge from data structure. Used as an internal routine in Remove.
				\param const vertex_ptr pointer1
				\param const vertex_ptr pointer2
			 */
			void RemoveOneTwo( 	const vertex_ptr& 	inVertexPtr1,
								const vertex_ptr& 	inVertexPtr2)
			{
				owner_.list_.erase(owner_.Edge(inVertexPtr1, inVertexPtr2));
			}



		private:

			//! Owner
			/*!
			 * Reference to AdjacencyList instance.
			 */
			structure_type& 		owner_;

		};

	} //	namespace policies





	//! policies
	/*!
	 * Namespace containing graph components' policies.
	*/
	namespace policies
	{
		//! edge_allocator<IncidenceMatrix>
		/*!
		 * Storage policy instantiation for IncidenceMatrix structure.
		*/
		template<   typename id_type>
		class edge_allocator< 	id_type,
		                        implementation::IncidenceMatrix>
		{

			using vertex_type 		= Vertex<id_type>;
			using vertex_ptr 		= std::shared_ptr<vertex_type>;
			using edge_type 		= Edge<id_type>;
			using structure_type 	= implementation::IncidenceMatrix<id_type>;
		
		public:
			
			//! Value constructor
			/*!
				\param IncidenceMatrixt&
			 */
			explicit  	edge_allocator(   structure_type& inList) :   	owner_(inList)
			{   }

			//! Copy constructor
			/*!
			 * Deleted.
			*/
						edge_allocator( 	const edge_allocator&) 	= delete;

			//! Allocate
			/*!
			 * Places an edge into data structure.
				\param const vertex_ptr pointer1
				\param const vertex_ptr pointer2
				\param int direction
				\param int weight
			 */
			void 		Allocate(   const vertex_ptr& 	inVertexPtr1,
									const vertex_ptr& 	inVertexPtr2,
									int 				type,
									int 				weight)
			{
				owner_.matrix_[owner_.map_.at(inVertexPtr1)][owner_.map_.at(inVertexPtr2)] = weight;
				owner_.matrix_[owner_.map_.at(inVertexPtr2)][owner_.map_.at(inVertexPtr1)] = weight;
			}

			//! Remove
			/*!
			 * Removes an edge from data structure.
				\param const vertex_ptr pointer1
				\param const vertex_ptr pointer2
				\param int direction
			 */
			void 		Remove( 	const vertex_ptr& 	inVertexPtr1,
									const vertex_ptr& 	inVertexPtr2,
									int 				type)
			{
				// currently unimplemented
			}



		private:

			//! Owner
			/*!
			 * Reference to AdjacencyList instance.
			 */
			structure_type& 		owner_;

		};
		
	} //	namespace policies

} //	namespace component



#endif // GRAPH_COMPONENT_EDGE_SUPPORT_HPP