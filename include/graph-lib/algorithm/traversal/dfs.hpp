//==============================================================================
///
/// @file dfs.hpp
///
/// @brief Depth First Search algorithm
///
/// This is an implementation of Depth-First Search algorithm. DFS class is
/// parametrized by the type of edges and the internal id type of the vertices.
/// It uses std::deque as a stack and std::unordered_set to mark discovered
/// vertices. The result tree is stored in a std::deque subobject.
///
/// The documentation is available on the following website:
/// <website>
///
/// Support email: <email>
///
//==============================================================================

//==============================================================================
// Include only once
//
#ifndef GRAPH_LIB_ALGORITHM_TRAVERSAL_DFS_HPP
#define GRAPH_LIB_ALGORITHM_TRAVERSAL_DFS_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <vector>
#include <stack>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <graph-lib/component/vertex.hpp>


//------------------------------------------------------------------------------
// Global references
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
namespace graph
{
	template<    class id_type,
	             template<typename> typename EdgeType>
	class Graph;
}


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief <Description>
///
/// <Detailed description>
//------------------------------------------------------------------------------
class Object
{
    /// @brief <Member description>
    <data type> <name>;
};


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
///
/// @brief <Description>
///
/// @param[in] <name> <Description>
///
/// @param[in,out] <name> <Description>
///
/// @param[out] <name> <Description>
///
/// @return <Description>
/// @retval <Value i> <Description>
///
//------------------------------------------------------------------------------
<data type> <function name>(...);

//------------------------------------------------------------------------------
///
/// @brief DFS
///
/// Depth-First Search implementation
/// Input: Graph G
/// Output: for every vertex v parent[v]
///
/// @param[in] graph Input graph.
///
/// @return <Description>
/// @retval <Value i> <Description>
///
//------------------------------------------------------------------------------
template<id_type, EdgeType>
std::vector<id_type>
dfs(const graph::Graph<id_type, EdgeType>& graph,
	const component::Vertex<id_type>& root);


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
<data type> <function name>(...)
{

}


//------------------------------------------------------------------------------
//
// Algorithms namespace
//
//------------------------------------------------------------------------------
namespace algorithm
{
	//------------------------------------------------------------------------------
	//
	// Algorithms namespace
	//
	//------------------------------------------------------------------------------
	template<id_type, EdgeType>
	std::vector<id_type>
	dfs(const graph::Graph<id_type, EdgeType>& graph,
		const component::Vertex<id_type>& root)
	{
		// output structure containing 
		std::vector<id_type>
		// label vertex as discovered
		std::stack<component::Vertex<id_type>*> vStack;


		// proceed
		while (!vStack.empty())
		{

		}

	}

}


//------------------------------------------------------------------------------
///
/// @brief <Description>
///
/// @param[in] <name> <Description>
///
/// @param[in,out] <name> <Description>
///
/// @param[out] <name> <Description>
///
/// @return <Description>
/// @retval <Value i> <Description>
///
//------------------------------------------------------------------------------
static <data type> <function name>(...)
{

}



#endif // GRAPH_LIB_ALGORITHM_TRAVERSAL_DFS_HPP
//==============================================================================
// End of dfs.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================


// forward declaration of a Graph class (graph.hpp) to avoid circular inclusion







namespace pathsearch
{

	// DFS class declaration. It is required to be initialized with a graph. It is copy-constructible,
	// but not movable.

	template<   typename                    id_type,
                template<typename> typename EdgeType>
	class DFS
	{
	public:
		// type aliases for internal use
		using v_traits    = component::vertextraits::vertex_traits<id_type>;
		using vertex_type = component::Vertex<id_type>;
		using edge_type   = EdgeType<id_type>;
		using graph_type  = graph::Graph<id_type, EdgeType>;
		// specific for std::unordered_set
		using vertex_hash = component::support::VertexHash<id_type>; 
		using vertex_eq   = component::support::VertexEqual<id_type>;





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
	template<   typename                    id_type,
                template<typename> typename EdgeType>
	DFS<id_type, EdgeType>::DFS(   const graph_type&             inGraph) :         graph_(inGraph)
	{   }



	//
	template<   typename                    id_type,
                template<typename> typename EdgeType>
	DFS<id_type, EdgeType>::DFS(	  const DFS<id_type,EdgeType>&   inAlgorithm) :     graph_( inAlgorithm.graph_),
	                                                                               result_(inAlgorithm.result_)
	{   }



	//
	template<   typename                    id_type,
                template<typename> typename EdgeType>
	const DFS<id_type, EdgeType>&     DFS<id_type, EdgeType>::operator=(   const DFS<id_type, EdgeType>& inAlgorithm)
	{
		graph_  = inAlgorithm.graph_;
		result_ = inAlgorithm.result_;

		return *this;
	}



	// 
	template<   typename                    id_type,
                template<typename> typename EdgeType>
	const std::deque<component::Vertex<id_type>>&   DFS<id_type, EdgeType>::Result() const
	{ 
		return result_;
	}
	


	// Execute method
	template<   typename                    id_type,
                template<typename> typename EdgeType>
	void                             DFS<id_type, EdgeType>::Execute(   const component::Vertex<id_type>& inRoot)
	{
		std::deque<component::Vertex<id_type>>                                   stack;
		std::unordered_set<component::Vertex<id_type>, vertex_hash, vertex_eq>   discovered;

		// add root to a stack and mark it discovered
		stack.push_front( inRoot);
		discovered.insert(inRoot);
 
		while(!stack.empty())
		{
			// pop the top element from a stack, add it to the resulting path
			component::Vertex<id_type> currentVrtx(*stack.begin());
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