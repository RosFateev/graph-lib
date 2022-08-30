#ifndef GRAPH_IMPLEMENTATION_IMPLEMENTATION_SUPPORT_H
#define GRAPH_IMPLEMENTATION_IMPLEMENTATION_SUPPORT_H





//user 
#include "graph-lib/component/vertex-support.hpp"
#include "graph-lib/component/edge-support.hpp"





/*
//
// forward declaration of some specific components
//
namespace implementation
{
	template<   typename id_type,
                template<   typename> typename EdgeType>
	class AdjacencyList;

} //	namespace implementation

namespace implementation
{
	template<   class id_type,
                template<  typename> typename EdgeType>
	class IncidenceMatrix;
} //	namespace implementation










//
// Policies
//
namespace implementation
{
	namespace policies
	{
		//
		// Base storage policy template
		//
		template<   typename id_type,
		            template<   typename> typename EdgeType,
					template<	typename, template<typename> typename> typename ContainerType>
		class storage_policy
		{
			using vertex_type 		= component::Vertex<id_type>;
			using vertex_ptr 		= std::shared_ptr<vertex_type>;
			using edge_type 		= EdgeType<id_type>;
			using structure_type 	= ContainerType<id_type, edge_type>;
			using vertex_policy 	= component::policies::vertex_storage_policy<id_type, edge_type, structure_type>;
			using edge_policy 		= component::policies::edge_storage_policy<id_type, edge_type, structure_type>;


		public:

			explicit  	storage_policy(   structure_type& inList) : owner_(inList),
																	vertexAllocator_(inList),
																	edgeAllocator_(inList)
			{   }
						storage_policy() 							= delete;

						storage_policy( 	const storage_policy&) 	= delete;



			// allocators
			void 	AllocateVertex(	id_type inId)
			{
				vertexAllocator_.Allocate(inId);
			}
			
			void 	AllocateEdge(	const vertex_ptr 	inVertexPtr1,
									const vertex_ptr 	inVertexPtr2,
									int 				type,
									int 				inWeight)
			{
				edgeAllocator_.Allocate(inVertexPtr1, inVertexPtr2, type, inWeight);
			}

			void 	AllocateEdge(	id_type 	inId1,
									id_type 	inId2,
									int 		type,
									int 		inWeight)
			{
				edgeAllocator_.Allocate(inId1, inId2, type, inWeight);
			}


			// deallocators
			void 	RemoveVertex(	id_type 	inId)
			{
				vertexAllocator_.Remove(inId);
			}

			void 	RemoveEdge(		const vertex_ptr 	inVertexPtr1,
									const vertex_ptr 	inVertexPtr2)
			{
				edgeAllocator_.Remove(inVertexPtr1, inVertexPtr2);
			}



		private:

			// state
			structure_type& 		owner_;
			vertex_policy 			vertexAllocator_;
			edge_policy 			edgeAllocator_;

		};
		

	}
	

} //	namespace implementation
*/

#endif //	GRAPH_IMPLEMENTATION_IMPLEMENTATION_SUPPORT_H