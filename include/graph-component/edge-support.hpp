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





//forward declaration
namespace adjlist
{
	template<   typename Data,
                template<   typename> typename EdgeType>
	class AdjacencyList;

} //	namespace adjlis





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
			explicit  storage_policy(   adjlist::AdjacencyList<Data, UndirectedEdge>& inList) :   owner_(inList)
			{   }

			void AllocateEdge(   const UndirectedEdge<Data>& inEdge)
			{
				//Doesn't work
				//owner_.list_.at(inEdge.First()).push_back(inEdge);
				//AllocateEdge( inEdge.First(), inEdge.Second(), inEdge.Weight());
			}

			void AllocateEdge(   const Vertex<Data>& inVertex1, const Vertex<Data>& inVertex2, int inWeight = 0)
			{
				owner_.list_.at(inVertex1).emplace_back(inVertex1, inVertex2, inWeight);
				owner_.list_.at(inVertex2).emplace_back(inVertex2, inVertex1, -inWeight);
			}


		private:
			adjlist::AdjacencyList<Data, UndirectedEdge>& owner_;
		};


		template<   typename Data>
		class storage_policy<   Data,
		                        DirectedEdge>
		{
		public:
			explicit  storage_policy(   adjlist::AdjacencyList<Data, DirectedEdge>& inList) :   owner_(inList)
			{   }

			//adding an edge - single entry to a map structure
			void AllocateEdge(   const DirectedEdge<Data>& inEdge)
			{
				owner_.list_.at(inEdge.First()).push_back(inEdge);
			}

			void AllocateEdge(   const Vertex<Data>& inVertex1, const Vertex<Data>& inVertex2, int inWeight)
			{
				owner_.list_.at(inVertex1).emplace_back(inVertex1, inVertex2, inWeight);
			}

		private:
			adjlist::AdjacencyList<Data, DirectedEdge>& owner_;
		};

	} //	namespace edgepolicies



	namespace edgepolicies
	{

	} //	namespace edgepolicies


} //	namespace component



#endif // GRAPH_COMPONENT_EDGE_SUPPORT_HPP