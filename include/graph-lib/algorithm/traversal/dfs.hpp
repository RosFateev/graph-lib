// Header description: 
//
// This is an implementation of Depth-First Search algorithm. DFS class is parametrized by the type
// of edges and the internal id type of the vertices. It uses std::deque as a stack and 
// std::unordered_set to mark discovered vertices. The result tree is stored in a std::deque subobject.
//
//
// Author: Rostislav Fateev

#ifndef GRAPH_ALGORITHM_DFS_HPP
#define GRAPH_ALGORITHM_DFS_HPP





// related
// c
// std 
#include <deque>
#include <unordered_set>
// lib
// user
#include "graph-component/vertex.hpp"





// forward declaration of a Graph class (graph.hpp) to avoid circular inclusion
namespace graph
{
	template<    class IdType,
	             template<typename> typename EdgeType>
	class Graph;
}





// a common namespace for path search algorithms
namespace pathsearch
{

	// DFS class declaration. It is required to be initialized with a graph. It is copy-constructible,
	// but not movable.

	template<   typename                    IdType,
                template<typename> typename EdgeType>
	class DFS
	{
	public:
		// type aliases for internal use
		using v_traits    = component::vertextraits::vertex_traits<IdType>;
		using vertex_type = component::Vertex<IdType>;
		using edge_type   = EdgeType<IdType>;
		using graph_type  = graph::Graph<IdType, EdgeType>;
		// specific for std::unordered_set
		using vertex_hash = component::support::VertexHash<IdType>; 
		using vertex_eq   = component::support::VertexEqual<IdType>;





	public:
		// methods
		DFS(   const graph_type&);
		DFS(   const DFS&);
		//
		DFS(   DFS&&) = delete;
		//
		const DFS&                       operator=(   const DFS&);


		
		// main path computing method 
		void                             Execute(  const vertex_type&);

		// return result
		const std::deque<vertex_type>&   Result() const;





	private:
		// state

		const graph_type&       graph_;

		std::deque<vertex_type> result_;
	};

} //	namespace pathsearch





namespace pathsearch
{

	// DFS class definition
	//
	// constructor
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	DFS<IdType, EdgeType>::DFS(   const graph_type&             inGraph) :         graph_(inGraph)
	{   }



	//
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	DFS<IdType, EdgeType>::DFS(	  const DFS<IdType,EdgeType>&   inAlgorithm) :     graph_( inAlgorithm.graph_),
	                                                                               result_(inAlgorithm.result_)
	{   }



	//
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	const DFS<IdType, EdgeType>&     DFS<IdType, EdgeType>::operator=(   const DFS<IdType, EdgeType>& inAlgorithm)
	{
		graph_  = inAlgorithm.graph_;
		result_ = inAlgorithm.result_;

		return *this;
	}



	// 
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	const std::deque<component::Vertex<IdType>>&   DFS<IdType, EdgeType>::Result() const
	{ 
		return result_;
	}
	


	// Execute method
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	void                             DFS<IdType, EdgeType>::Execute(   const component::Vertex<IdType>& inRoot)
	{
		std::deque<component::Vertex<IdType>>                                   stack;
		std::unordered_set<component::Vertex<IdType>, vertex_hash, vertex_eq>   discovered;

		// add root to a stack and mark it discovered
		stack.push_front( inRoot);
		discovered.insert(inRoot);
 
		while(!stack.empty())
		{
			// pop the top element from a stack, add it to the resulting path
			component::Vertex<IdType> currentVrtx(*stack.begin());
			stack.pop_front();
			result_.push_back(currentVrtx);

			// get neighbours of the chosen vertex
			auto currentNeighbours(graph_.GetNeighbours(currentVrtx));

			// if neighbour vertex is discovered, add it to stack and mark discovered 
			for(auto iter = currentNeighbours.begin(); iter != currentNeighbours.end(); ++iter)	
			{
				if (discovered.find(iter->Second()) == discovered.end())
				{	
					discovered.insert(iter->Second());
					stack.push_front(iter->Second());
				}
			}
		}

	}

} //namespace pathsearch

/*
	1	procedure DFS_iterative(G, v) is
    2	let S be a stack
    3	S.push(v)
    4	while S is not empty do
    5	   v = S.pop()
    6	   if v is not labeled as discovered then
    7	       label v as discovered
    8	       for all edges from v to w in G.adjacentEdges(v) do 
    9	           S.push(w)
*/



#endif //GRAPH_ALGORITHM_DFS_HPP