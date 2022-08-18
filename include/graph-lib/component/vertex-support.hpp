#ifndef GRAPH_COMPONENT_VERTEX_SUPPORT_HPP
#define GRAPH_COMPONENT_VERTEX_SUPPORT_HPP





//
//
// forward declaration of some specific components
//
namespace implementation
{
	template<   typename id_type>
	class AdjacencyList;

} //	namespace implementation

namespace implementation
{
	template<   typename id_type>
	class IncidenceMatrix;

} //	namespace implementation

namespace component
{
	template< 	typename id_type>
	class Vertex;

	template< 	typename id_type>
	class Edge;

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
		//! vertex_traits<id_type>
		/*!
		 * Base class definition.
		*/
		template<	typename id_type>
		class vertex_traits
		{	};

		//! vertex_traits<int>
		/*!
		 * integer instantiation.
		*/
		template<>
		class vertex_traits<int>
		{
		public:

			//! special Vertex<int> enumerator
			/*!
			 * contains reserved values
			*/
			enum {	children_delimeter	=	-2147483648, 
					layer_delimeter		=	2147483647  };
		};

		//! vertex_traits<char>
		/*!
		 * char instantiation.
		*/
		template<>
		class vertex_traits<char>
		{
		public:

			//! special Vertex<char> enumerator
			/*!
			 * contains reserved values
			*/
			enum {	children_delimeter	=	-128, 
					layer_delimeter		=	127  };
			 
		};		

	} //	namespace vertextraits

} //	namespace component





//! component
/*!
 * A common namespace for graph's components: vertex and edge. 
*/
namespace component
{
	//! support
	/*!
	 * Namespace containing graph components' support structures: hash, comparator, etc.
	*/
	namespace support
	{
		//! vertex_hash
		/*!
		 * Class implementing Vertex hash. Enables Vertex as a key in std::map.
		*/
		template<   typename id_type>
		class vertex_hash
		{

			using vertex_type = component::Vertex<id_type>;

		public:

			//! operator()
			/*!
			 * Computes hash from Vertex id.
			   \param const Vertex& input vertex
			   \return Vertex hash
			*/
			size_t operator()(    const vertex_type& vertex) const
			{
				return std::hash<id_type>()(vertex.Id());
			}
		};

		//! vertex_ptr_hash
		/*!
		 * Class implementing shared_ptr<Vertex> hash. Enables shared_ptr<Vertex> as a key in std::map.
		*/
		template<	typename id_type>
		class vertex_ptr_hash
		{

			using vertex_type 	= component::Vertex<id_type>;
			using vertex_ptr 	= std::shared_ptr<vertex_type>;

		public:
			
			//! operator()
			/*!
			 * Computes hash from Vertex id (default - value + address).
			  \param const shared_ptr<Vertex>& input vertex pointer
			  \return pointer hash
			*/
			size_t operator()(    const vertex_ptr& inPtr) const
			{
				return std::hash<id_type>()(inPtr->Id());
			}
		};

		//! vertex_equal
		/*!
		 * Class implementing Vertex equality comparison.
		*/
		template<   typename id_type>
		class vertex_equal
		{

			using vertex_type = component::Vertex<id_type>;

		public:

			//! operator()
			/*!
			 * Compares vertices by id.
			  \param const Vertex& first vertex
			  \param const Vertex& second vertex
			  \return comparison result
			*/
			bool   operator()(    const vertex_type& lhs,
				                  const vertex_type& rhs) const
			{
				return lhs.Id() == rhs.Id();
			}
		};

		//! vertex_ptr_equal
		/*!
		 * Class implementing shared_ptr<Vertex> equality comparison.
		*/
		template<	typename id_type>
		class VertexPtrEqual
		{

			using vertex_type 	= component::Vertex<id_type>;
			using vertex_ptr 	= std::shared_ptr<vertex_type>;

		public:

			//! operator()
			/*!
			 * Compares Vertex pointers by id.
			  \param const shared_ptr<Vertex>& first pointer
			  \param const shared_ptr<Vertex>& second pointer
			  \return comparison result
			*/
			bool operator()(	const vertex_ptr& lhs,
								const vertex_ptr& rhs) const
			{
				return (lhs->Id() == rhs->Id());
			}

		};

		//! vertex_less
		/*!
		 * Class implementing Vertex order comparison.
		*/
		template<   typename id_type>
		class vertex_less
		{

			using vertex_type = component::Vertex<id_type>;

		public:

			//! operator()
			/*!
			 * Compares Vertex pointers by id.
			  \param const Vertex& first vertex
			  \param const Vertex& second vertex
			  \return comparison result
			*/
			bool   operator()(    const vertex_type& lhs,
				                  const vertex_type& rhs) const
			{
				return lhs.Id() < rhs.Id();
			}
		};


		//! vertex_ptr_less
		/*!
		 * Class implementing shared_ptr<Vertex> order comparison.
		*/
		template<	typename id_type>
		class vertex_ptr_less
		{

			using vertex_type 	= component::Vertex<id_type>;
			using vertex_ptr 	= std::shared_ptr<vertex_type>;

		public:

			//! operator()
			/*!
			 * Compares Vertex pointers by id.
			  \param const shared_ptr<Vertex>& first pointer
			  \param const shared_ptr<Vertex>& second pointer
			  \return comparison result
			*/
			bool operator()(	const vertex_ptr& lhs,
								const vertex_ptr& rhs) const
			{
				return lhs->Id() < rhs->Id();
			}

		};

	} //	namespace support

} //	namespace component





//! component
/*!
 * A common namespace for graph's components: vertex and edge. 
*/
namespace component
{
	//! policies
	/*!
	 * A collection of different policies
	*/
	namespace policies
	{
		//! vertex_allocator<id_type>
		/*!
		 * Base class storage policy used in graph's implementations to appropriately insert vertices depending on their type.
		 */
		template<   typename id_type,
					template<	typename> typename ContainerType> 
		class vertex_allocator
		{   };


		//! vertex_allocator<id_type, AdjacencyList>
		/*!
		 * AdjacencyList instantiation of vertex_allocation storage policy.
		*/
		template<   typename id_type> 
		class vertex_allocator<	id_type,
								implementation::AdjacencyList>
		{
			using vertex_type 		= Vertex<id_type>;
			using vertex_ptr 		= std::shared_ptr<vertex_type>;
			using structure_type 	= implementation::AdjacencyList<id_type>;
		
		public:
			
			//! Value constructor
			/*!
			  \param AdjacencyList&
			*/
			explicit  	vertex_allocator(   structure_type& inStructure) :  owner_(inStructure)
			{   }

			//! Copy constructor
			/*!
			 * Deleted.
			*/
						vertex_allocator( 	const vertex_allocator&) 	= delete;

			//! Allocate
			/*!
			 * Function placing new Vertex in data structure.
			  \param id_type vertex id
			*/
			void 		Allocate(	id_type inId)
			{
				owner_.list_[vertex_ptr(new vertex_type(inId))];
			}

			//! Remove
			/*!
			 * Function removing Vertex from data structure.
			  \param id_type vertex id
			*/
			void 		Remove(		id_type inId)
			{
				owner_.list_.erase(owner_.Vertex(inId));
			}



		private:

			//! Owner
			/*!
			 * Reference to AdjacencyList instance.
			*/
			structure_type& 		owner_;
		};





		//! vertex_allocator<id_type, IncidenceMatrix>
		/*!
		 * IncidenceMatrix instantiation of vertex_allocation storage policy.
		*/
		template<   typename id_type> 
		class vertex_allocator<	id_type,
								implementation::IncidenceMatrix>
		{
			using vertex_type 		= Vertex<id_type>;
			using vertex_ptr 		= std::shared_ptr<vertex_type>;
			using structure_type 	= implementation::IncidenceMatrix<id_type>;
		
		public:
			
			//! Value constructor
			/*!
			  \param IncidenceMatrix&
			*/
			explicit  	vertex_allocator(   structure_type& inStructure) :  owner_(inStructure)
			{   }

			//! Copy constructor
			/*!
			 * Deleted.
			*/
						vertex_allocator( 	const vertex_allocator&) 	= delete;

			//! Allocate
			/*!
			 * Function placing new Vertex in data structure.
			  \param id_type vertex id
			*/
			void 		Allocate(	id_type inId)
			{
				// insert new row + push_back 1 empty element into each previous row
			}

			//! Remove
			/*!
			 * Function removing Vertex from data structure.
			  \param id_type vertex id
			*/
			void 		Remove(		id_type inId)
			{
				// remove entries in other rows corresponding to this vertex
				// remove vertex's row
			}



		private:

			//! Owner
			/*!
			 * Reference to IncidenceMatrix instance.
			*/
			structure_type& 		owner_;
		
		};

	} //	namespace policies

} //	namespace component



#endif //GRAPH_COMPONENT_VERTEX_SUPPORT_HPP