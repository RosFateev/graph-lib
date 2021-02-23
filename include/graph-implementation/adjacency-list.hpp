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





//
//	Underlying graph implementation
//
namespace adjlist
{
	template<   typename 						Data,   
				template<typename> typename 	EdgeType>
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
		
		//
		// Methods
		//
		// construcors
		AdjacencyList() :   valid_(false),
		                    list_(),
		                    edgeAllocator_(*this)
		{   }

		AdjacencyList(    std::initializer_list<init_list_type>&&);


		// component manipulators
		void           			AddVertex(  Data);
		
		void           			AddVertex(  const vertex_type&); 

		const vertex_type&   	GetVertex(  Data);

		void           			RemoveVertex( Data&&);

		
		void              		AddEdge(    const vertex_type&, 
		                              		const vertex_type&,
		                              		int                		inWeight = 0);
		
		
		
		EdgeType<Data>&   		GetEdge(    Data,
			                          		Data); 
		
		EdgeType<Data>&   		GetEdge(    const vertex_type&,
		                              		const vertex_type&); //unsure

		void              		RemoveEdge( const vertex_type&,
			                          		const vertex_type&);

		void              		RemoveEdge( Data&&,
			                          		Data&&);

		std::vector<EdgeType<Data>>&          GetNeighbours(    Data inId);

		const std::vector<EdgeType<Data>>&    GetNeighbours(    Data inId) const;

		std::vector<EdgeType<Data>>&          GetNeighbours(    const vertex_type& inVertex);

		const std::vector<EdgeType<Data>>&    GetNeighbours(    const vertex_type& inVertex) const;



		//method to remove

		void print();
		size_t size() { return list_.size();}

		//Debug
		bool 					IsValid() 	{ return valid_;}
		bool 					IsEmpty() 	{ return list_.size() == 0 ? true : false; }
		storage_policy_type& 	GetPolicy() { return edgeAllocator_;}



	

		// helper functions
		bool 	ContainsVertex(	Data) 	const;
		bool 	ContainsEdge(	Data,
								Data) 	const;
		private:
		//Edge is tightly bound to its endpoint vertices - copy construction should be restricted
		void              		AddEdge(    const EdgeType<Data>&);



	private:
		
		//
		// state
		//
		bool                	valid_;
		map_structure       	list_;
		storage_policy_type 	edgeAllocator_;



		//friendships
		friend storage_policy_type;
	};

} //	namespace adjlist





namespace adjlist
{
	//Adjacency list implementation
	//constructors
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	AdjacencyList<Data, EdgeType>::AdjacencyList(    	std::initializer_list<init_list_type>&& inList) : 
	                              																			valid_(false),
	                              																			list_(std::forward<std::initializer_list<init_list_type>>(inList)),
	                              																			edgeAllocator_(*this)
	{   }





	//
	// Add component: vertex and edge 
	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddVertex(   		Data 				inData) 
	{
		list_[vertex_type(inData)];
	}
	
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddVertex(   const 	vertex_type& 		inVertex) //unsure
	{
		list_[inVertex];
	}



	//	
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddEdge(     const 	vertex_type& 		inVertex1,
		                                                const 	vertex_type& 		inVertex2,
		                                                		int             	inWeight) 
	{ 
		edgeAllocator_.AllocateEdge(inVertex1, inVertex2, inWeight);
	} 
	

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void    AdjacencyList<Data, EdgeType>::AddEdge(     const 	EdgeType<Data>& 	inEdge)
	{
		edgeAllocator_.AllocateEdge(inEdge);
	}





	//
	// Get component: vertex and edge getters
	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	const component::Vertex<Data>&    AdjacencyList<Data, EdgeType>::GetVertex(   Data 	inId)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if(vrtxIter->first.Id() == inId)
				return vrtxIter->first; 
				
		return list_.end()->first;
	}



	// 
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	EdgeType<Data>&      AdjacencyList<Data, EdgeType>::GetEdge(     		Data 			inId1,
		                                                            		Data 			inId2)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if( vrtxIter->first.Id() == inId1)
				for(auto edgeIter = vrtxIter->second.begin(); edgeIter != vrtxIter->second.end(); ++edgeIter)
					if( edgeIter->Second().Id() == inId2)
						return *edgeIter;
	} 
		
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	EdgeType<Data>&      AdjacencyList<Data, EdgeType>::GetEdge(     const 	vertex_type& 	inVertex1,
		                                                             const 	vertex_type& 	inVertex2)
	{
		for(auto vrtxIter = list_.begin(); vrtxIter != list_.end(); ++vrtxIter)
			if( vrtxIter->first == inVertex1)
				for(auto edgeIter = vrtxIter->second.begin(); edgeIter != vrtxIter->second.end(); ++edgeIter)
					if( edgeIter->Second() == inVertex2)
						return *edgeIter;
	} 



	//
	// Remove component: vertex and edge - currently not working
	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void              AdjacencyList<Data, EdgeType>::RemoveVertex( 		Data&& 			inId)
	{	}



	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void              AdjacencyList<Data, EdgeType>::RemoveEdge( const 	vertex_type& 	inVertex1,
			                                                     const 	vertex_type& 	inVertex2)
	{	}

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	void              AdjacencyList<Data, EdgeType>::RemoveEdge( 		Data&& 			inId1,
			                                                     		Data&& 			inId2)
	{	}





	//
	// Get neighbors are used for algorithms
	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	std::vector<EdgeType<Data>>&          AdjacencyList<Data, EdgeType>::GetNeighbours(    			Data 			inId)
	{
		return list_.at(vertex_type(inId));
	}

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	const std::vector<EdgeType<Data>>&    AdjacencyList<Data, EdgeType>::GetNeighbours(    			Data 			inId) 		const
	{
		return list_.at(vertex_type(inId));
	}

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	std::vector<EdgeType<Data>>&          AdjacencyList<Data, EdgeType>::GetNeighbours(    const 	vertex_type& 	inVertex)
	{
		return list_.at(inVertex);
	}

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	const std::vector<EdgeType<Data>>&    AdjacencyList<Data, EdgeType>::GetNeighbours(    const 	vertex_type& 	inVertex) 	const
	{
		return list_.at(inVertex);
	}





	//
	// Helper functions
	//
	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	bool 	AdjacencyList<Data, EdgeType>::ContainsVertex(	Data inId) 		const
	{
		if(list_.find(vertex_type(inId)) != list_.end())
			return true;

		return false;
	}

	template<   typename 						Data,
	            template<typename> typename 	EdgeType>
	bool 	AdjacencyList<Data, EdgeType>::ContainsEdge(	Data inId1,
															Data inId2) 	const
	{
		if(ContainsVertex(inId1))
		{
			for(const auto& edge : GetNeighbours(inId1))
			{
				if(edge.Second().Id() == inId2)
					return true;
			}
			return false;
		}
		else
			return false;
	}

	//
	//	print method used for debugging
	//
	//	REMOVE LATER
	//
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