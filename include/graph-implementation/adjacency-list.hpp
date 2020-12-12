#ifndef GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H
#define GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H



//related
//c
//std
#include <initializer_list>
#include <vector>
#include <unordered_map>
#include <utility>							//std::hash, std::forward
#include <iostream>
//lib
//user
#include "graph-component/vertex.hpp"
#include "graph-component/vertex-support.hpp"
#include "graph-component/edge.hpp"
#include "graph-component/edge-support.hpp"



namespace adjlist
{
	template<   typename Data,   template<typename> typename EdgeType>
	class AdjacencyList
	{
	private:
		//type aliases
		using vertex_type         = component::Vertex<Data>;
		using v_traits            = component::vertextraits::vertex_traits<Data>;
		using e_traits            = component::edgetraits::edge_traits<Data>;
		using neighbours          = std::vector<EdgeType<Data>>;
		using map_structure       = std::unordered_map<vertex_type, neighbours, component::support::VertexHash<Data>, component::support::VertexEqual<Data>>;
		using init_list_type      = std::pair<const vertex_type, std::vector<EdgeType<Data>>>; 
		using storage_policy_type = component::edgepolicies::storage_policy<Data, EdgeType>;

	public:
		
		//construcors
		AdjacencyList() :   valid_(false),
		                    list_(),
		                    edgeAllocator_(*this)
		{   }

		AdjacencyList(    std::initializer_list<init_list_type>&&);


		//component manipulators
		void           AddVertex(  Data&& inData);
		
		void           AddVertex(  const vertex_type&); 

		const vertex_type&   GetVertex(  Data&& inId);

		void           RemoveVertex();

		
		void              AddEdge(    const vertex_type&, 
		                              const vertex_type&,
		                              int                inWeight = 0);
		
		void              AddEdge(    const EdgeType<Data>&);
		
		EdgeType<Data>&   GetEdge(    Data&&,
			                          Data&&); 
		
		EdgeType<Data>&   GetEdge(    const vertex_type&,
		                              const vertex_type&); //unsure

		void              RemoveEdge( const vertex_type&,
			                          const vertex_type&);

		void              RemoveEdge( Data&&,
			                          Data&&);

		std::vector<EdgeType<Data>>&          GetNeighbours(    Data&& inId);

		const std::vector<EdgeType<Data>>&    GetNeighbours(    Data&& inId) const;

		std::vector<EdgeType<Data>>&          GetNeighbours(    const vertex_type& inVertex);

		const std::vector<EdgeType<Data>>&    GetNeighbours(    const vertex_type& inVertex) const;

		//method to remove

		void print();

	private:
		//data
		bool                valid_;
		map_structure       list_;
		storage_policy_type edgeAllocator_;


		//friendships
		friend storage_policy_type;
	};

} //	namespace adjlist





namespace adjlist
{
	//Adjacency list implementation
	//constructors
	template<   typename Data,
	            template<typename> typename EdgeType>
	AdjacencyList<Data, EdgeType>::AdjacencyList(    std::initializer_list<init_list_type>&& inList) : 
	                              valid_(false),
	                              list_(std::forward<std::initializer_list<init_list_type>>(inList)),
	                              edgeAllocator_(*this)
	{   }

	//accessors
	template<   typename Data,
	            template<typename> typename EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddVertex(   Data&& inData) 
	{
		list_[vertex_type(std::forward<Data>(inData))];
	}
	
	template<   typename Data,
	            template<typename> typename EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddVertex(   const vertex_type& inVertex) //unsure
	{
		list_[inVertex];
	}

	
	template<   typename Data,
	            template<typename> typename EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddEdge(     const vertex_type& inVertex1,
		                                                const vertex_type& inVertex2,
		                                                int                inWeight) 
	{ 
		edgeAllocator_.AllocateEdge(inVertex1, inVertex2, inWeight);
	} 
	

	template<   typename Data,
	            template<typename> typename EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddEdge(     const EdgeType<Data>& inEdge)
	{
		edgeAllocator_.AllocateEdge(inEdge);
	}


	template<   typename Data,
	            template<typename> typename EdgeType>
	const component::Vertex<Data>&    AdjacencyList<Data, EdgeType>::GetVertex(   Data&& inId)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if(vrtxIter->first.Id() == inId)
				return vrtxIter->first; 
				
		return list_.end()->first;
	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	EdgeType<Data>&      AdjacencyList<Data, EdgeType>::GetEdge(     Data&& inId1,
		                                                             Data&& inId2)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if( vrtxIter->first.Id() == inId1)
				for(auto edgeIter = vrtxIter->second.begin(); edgeIter != vrtxIter->second.end(); ++edgeIter)
					if( edgeIter->Second().Id() == inId2)
						return *edgeIter;

	} 
		
	template<   typename Data,
	            template<typename> typename EdgeType>
	EdgeType<Data>&      AdjacencyList<Data, EdgeType>::GetEdge(     const vertex_type& inVertex1,
		                                                             const vertex_type& inVertex2)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if( vrtxIter->first == inVertex1)
				for(auto edgeIter = vrtxIter->second.begin(); edgeIter != vrtxIter->second.end(); ++edgeIter)
					if( edgeIter->Second() == inVertex2)
						return *edgeIter;
	} 

	template<   typename Data,
	            template<typename> typename EdgeType>
	void              AdjacencyList<Data, EdgeType>::RemoveEdge( const vertex_type& inVertex1,
			                                                     const vertex_type& inVertex2)
	{

	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	void              AdjacencyList<Data, EdgeType>::RemoveEdge( Data&& inId1,
			                                                     Data&& inId2)
	{

	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	std::vector<EdgeType<Data>>&          AdjacencyList<Data, EdgeType>::GetNeighbours(    Data&& inId)
	{
		return list_.at(vertex_type(std::forward<Data>(inId)));
	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	const std::vector<EdgeType<Data>>&    AdjacencyList<Data, EdgeType>::GetNeighbours(    Data&& inId) const
	{
		return list_.at(vertex_type(std::forward<Data>(inId)));
	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	std::vector<EdgeType<Data>>&          AdjacencyList<Data, EdgeType>::GetNeighbours(    const vertex_type& inVertex)
	{
		return list_.at(inVertex);
	}

	template<   typename Data,
	            template<typename> typename EdgeType>
	const std::vector<EdgeType<Data>>&    AdjacencyList<Data, EdgeType>::GetNeighbours(    const vertex_type& inVertex) const
	{
		return list_.at(inVertex);
	}


	//method to remove

	template<   typename Data,
	            template<typename> typename EdgeType>
	void AdjacencyList<Data, EdgeType>::print()
	{
		std::cout << "Printing a graph:" << std::endl;
		//std::unordered_map<vertex_type, std::vector<EdgeType<Data>>>;

		//output vertexes 
		typename map_structure::const_iterator mapIter(list_.begin());

		for(; mapIter != list_.end(); ++mapIter)
		{
			//output vertex

			std::cout << "[ " << mapIter->first.Id() << " ] :";
			//output edges
			typename neighbours::const_iterator vectIter(mapIter->second.begin());

			for(; vectIter != mapIter->second.end(); ++vectIter)
			{
				std::cout << "	( " << vectIter->First().Id() << ", " << vectIter->Second().Id() << ")";
			}
			std::cout << std::endl;
		}
	}

} //	namespace adjlist


#endif //GRAPH_IMPLEMENTATION_ADJACENCY_LIST_H