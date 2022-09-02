// Header description: 
//
// This is an implementation of Breadth-First Search algorithm. BFS class is parametrized by the type
// of edges and the internal id type of the vertices. It uses std::deque as a queue and 
// std::unordered_set to mark discovered vertices. The result tree is stored in a std::deque subobject.
//
//
// Author: Rostislav Fateev

#ifndef GRAPH_ALGORITHM_BFS_HPP
#define GRAPH_ALGORITHM_BFS_HPP





// related
// c
// std 
#include <deque>
#include <unordered_set>
#include <memory>
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










// 
// BFS declaration
//
namespace pathsearch
{
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	class BFS
	{		
		using vertex_type 		= component::Vertex<IdType>;
		using vertex_ptr 		= std::shared_ptr<vertex_type>;
		using edge_type 		= EdgeType<IdType>;
		using edge_container 	= std::vector<EdgeType<IdType>>;
		using graph_type 		= graph::Graph<IdType, EdgeType>;
		using vertex_traits     = component::traits::vertex_traits<IdType>;
		using edge_traits       = component::traits::edge_traits<IdType>;
		// specific for std::unordered_set
		using vertex_hash 		= component::support::VertexPtrHash<IdType>; 
		using vertex_eq   		= component::support::VertexPtrEqual<IdType>;
		using deque_type 		= std::deque<vertex_ptr>;
		using set_type 			= std::unordered_set<vertex_ptr, vertex_hash, vertex_eq>;

	public:
		// methods
		BFS(   const graph_type&);
		BFS(   const BFS&);
		BFS(   BFS&&) = delete;

		//
		const BFS& 	operator=(   const BFS&);


		
		// main path computing method 
		void                            Execute(  const vertex_ptr&);

		// return result
		const deque_type&  				Result() const;
		deque_type&   					Result();





	private:

		//
		// state
		//
		const graph_type& 	graph_;
		deque_type 			result_;
	};

} //	namespace pathsearch





namespace pathsearch
{

	// BFS class definition
	//
	// constructor
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	BFS<IdType, EdgeType>::BFS(   const graph_type&             inGraph) :         graph_(inGraph)
	{   }



	//
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	BFS<IdType, EdgeType>::BFS(	  const BFS<IdType,EdgeType>&   inAlgorithm) :     graph_( inAlgorithm.graph_),
	                                                                               result_(inAlgorithm.result_)
	{   }



	//
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	const BFS<IdType, EdgeType>&     BFS<IdType, EdgeType>::operator=(   const BFS<IdType, EdgeType>& inAlgorithm)
	{
		graph_  = inAlgorithm.graph_;
		result_ = inAlgorithm.result_;

		return *this;
	}



	// 
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	const typename BFS<IdType, EdgeType>::deque_type&   BFS<IdType, EdgeType>::Result() const
	{ 
		return result_;
	}

	template<   typename                    IdType,
                template<typename> typename EdgeType>
	typename BFS<IdType, EdgeType>::deque_type&   BFS<IdType, EdgeType>::Result()
	{ 
		return result_;
	}
	


	// Execute method
	template<   typename                    IdType,
                template<typename> typename EdgeType>
	void                        BFS<IdType, EdgeType>::Execute(   const typename BFS<IdType, EdgeType>::vertex_ptr& inRoot)
	{
		typename BFS<IdType, EdgeType>::deque_type 		queue;
		typename BFS<IdType, EdgeType>::set_type   		discovered;

		// add root to a queue and mark it discovered
		queue.push_back( inRoot);
		discovered.insert(inRoot);
 
		while(!queue.empty())
		{
			// pop the top element from a queue, add it to the resulting path
			typename BFS<IdType, EdgeType>::vertex_ptr currentVrtx(*queue.begin());
			queue.pop_front();
			result_.push_back(currentVrtx);

			// if neighbour vertex is discovered, add it to queue and mark discovered
			for(auto iter = graph_.Neighbours(currentVrtx).begin(); iter != graph_.Neighbours(currentVrtx).end(); ++iter)	
			{
				if (discovered.find(iter->Second()) == discovered.end())
				{	
					discovered.insert(iter->Second());
					queue.push_back(iter->Second());
				}
			}
		}

	}

} //namespace pathsearch

/*
1	 procedure BFS(G, root) is
2      let Q be a queue
3      label root as discovered
4      Q.enqueue(root)
5      while Q is not empty do
6          v := Q.dequeue()
7          if v is the goal then
8              return v
9          for all edges from v to w in G.adjacentEdges(v) do
10             if w is not labeled as discovered then
11                 label w as discovered
12                 w.parent := v
13                 Q.enqueue(w)
*/

#endif //GRAPH_ALGORITHM_BFS_HPP