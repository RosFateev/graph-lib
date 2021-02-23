#ifndef GRAPH_COMPONENT_EDGE_SUPPORT_HPP
#define GRAPH_COMPONENT_EDGE_SUPPORT_HPP



//related
//c
//std
#include <algorithm>
#include <type_traits>
#include <iostream>
//lib
//user 





//
// forward declaration of some specific components
//
namespace adjlist
{
	template<   typename Data,
                template<   typename> typename EdgeType>
	class AdjacencyList;

} //	namespace adjlis





//
// Edge traits are Vertex supposed to help in some algorithms (i.e some specific reserved values etc). - currently unused
// 
// Edge policies are used in adjecency list component (underlying graph implementation). - currently used for:
//	- appropriately storing the value (storage_policy class)
//
namespace component
{
	namespace edgetraits
	{
		template<   class Data>
		class edge_traits
		{	};

	} //	namespace edgetraits
	




	namespace func
	{
		template<   typename Data,
		            template<   typename> typename EdgeType>
		static EdgeType<Data> Reverse(const EdgeType<Data>& inEdge)
		{
			return EdgeType<Data>(inEdge.Second(), inEdge.First(), -inEdge.Weight());
		}
	} //	namespace misc





	namespace edgepolicies
	{
		//base template edge storage policy
		template<   typename Data,
		            template<   typename> typename EdgeType>
		class storage_policy
		{   };





		template<   typename Data>
		class storage_policy<   Data,
		                        UndirectedEdge>
		{
		public:
			explicit  	storage_policy(   adjlist::AdjacencyList<Data, UndirectedEdge>& inList) :   owner_(inList),
																									valid_(true)
			{   }
						storage_policy() 							= delete;

						storage_policy( 	const storage_policy&) 	= delete;


			//adding an edge - two entries to a map structure: edge and its reverse
			void AllocateEdge(   const UndirectedEdge<Data>& inEdge)
			{
				//Doesn't work
				owner_.list_.at(inEdge.First()).push_back(inEdge);
				owner_.list_.at(inEdge.Second()).emplace_back(inEdge.Second(), inEdge.First(), -inEdge.Weight());
			}

			void AllocateEdge(   const Vertex<Data>& inVertex1, const Vertex<Data>& inVertex2, int inWeight = 0)
			{
				owner_.list_.at(inVertex1).emplace_back(inVertex1, inVertex2, inWeight);
				owner_.list_.at(inVertex2).emplace_back(inVertex2, inVertex1, -inWeight);
			}



			//Debug
			bool IsValid(){ return valid_;}



		private:
			adjlist::AdjacencyList<Data, UndirectedEdge>& 	owner_;
			bool 											valid_;
		};





		template<   typename Data>
		class storage_policy<   Data,
		                        DirectedEdge>
		{
		public:
			explicit  	storage_policy(   adjlist::AdjacencyList<Data, DirectedEdge>& inList) :   	owner_(inList),
																									valid_(true)
			{   }
						storage_policy() 							= delete;

						storage_policy( 	const storage_policy&) 	= delete;



			//adding an edge - single entry to a map structure
			void AllocateEdge(   const DirectedEdge<Data>& inEdge)
			{
				owner_.list_.at(inEdge.First()).push_back(inEdge);
			}

			void AllocateEdge(   const Vertex<Data>& inVertex1, const Vertex<Data>& inVertex2, int inWeight)
			{
				owner_.list_.at(inVertex1).emplace_back(inVertex1, inVertex2, inWeight);
			}



			//Debug
			bool IsValid(){ return valid_;}

		private:
			adjlist::AdjacencyList<Data, DirectedEdge>& 	owner_;
			bool 											valid_;
		};

	} //	namespace edgepolicies



	namespace edgepolicies
	{

	} //	namespace edgepolicies


} //	namespace component



#endif // GRAPH_COMPONENT_EDGE_SUPPORT_HPP