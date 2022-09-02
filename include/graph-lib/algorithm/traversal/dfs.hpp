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
#include <map>
#include <stack>
#include <algorithm> 			// std::for_each
#include <iostream>

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
	template<class id_type,
	         typename implementation_type>
	class Graph;
}


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief Common graph algorithms.
///
//------------------------------------------------------------------------------
namespace algorithm
{
	//------------------------------------------------------------------------------
	/// @brief DFS implementation.
	///
	//------------------------------------------------------------------------------
	template<class id_type>
	class dfs
	{
		using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using parent_structure      = std::map<vertex_type,
        									   vertex_type,
        									   component::support::vertex_less<id_type>>;
        using graph_type 			= graph::Graph<id_type>;

	public:

		//------------------------------------------------------------------------------
		///
		/// @brief Value constructor.
		///
		/// @param[in] graph Input graph.
		///
		//------------------------------------------------------------------------------
		dfs(const graph_type& graph);

		//------------------------------------------------------------------------------
		///
		/// @brief Execute DFS algorithm.
		///
		/// @param[in] root Starting vertex.
		///
		//------------------------------------------------------------------------------
		void
		run(const vertex_type& root);

		//------------------------------------------------------------------------------
		///
		/// @brief Get algorithm execution results.
		///
		/// @return Reference to parent structure defining order.
		///
		//------------------------------------------------------------------------------
		const parent_structure&
		get();


	private:

		//------------------------------------------------------------------------------
		///
		/// @brief Check if vertex was visited by DFS algorithm.
		///
		/// @param[in] vertex Input vertex.
		///
		/// @retval True If vertex was visited.
		/// @retval False otherwise.
		///
		//------------------------------------------------------------------------------
		bool
		is_discovered(const vertex_type& vertex);

		//------------------------------------------------------------------------------
		///
		/// @brief Reset parent structure.
		///
		//------------------------------------------------------------------------------
		void
		flush_structure();

		//------------------------------------------------------------------------------
		///
		/// @brief Recursive DFS implementation.
		///
		/// @param[in] root Starting vertex.
		///
		//------------------------------------------------------------------------------
		void
		dfs_recursive(const vertex_type& root);

		//------------------------------------------------------------------------------
		///
		/// @brief Stack DFS implementation.
		///
		/// @param[in] root Starting vertex.
		///
		//------------------------------------------------------------------------------
		void
		dfs_stack(const vertex_type& root);

	private:

		/// @brief Parent structure.
		parent_structure structure_;

		/// @brief Graph.
		const graph_type& graph_;

	};
} // namespace algorithm


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Algorithms namespace
//
//------------------------------------------------------------------------------
namespace algorithm
{
	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	dfs<id_type>::dfs(const typename dfs<id_type>::graph_type& graph) : graph_(graph)
	{
		flush_structure();
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	dfs<id_type>::run(const typename dfs<id_type>::vertex_type& root)
	{
		//dfs_recursive(root);
		dfs_stack(root);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename dfs<id_type>::parent_structure&
	dfs<id_type>::get()
	{
		return structure_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	dfs<id_type>::is_discovered(const typename dfs<id_type>::vertex_type& vertex)
	{
		// Discovered : structure[vertex] != invalid_vertex
		return (structure_.at(vertex) != component::Vertex<id_type>::invalidInstance_);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	dfs<id_type>::flush_structure()
	{
		// initialize parent structure: insert <vertex, invalid_vertex> entries,
		// where vertex - vertex of the graph
		std::for_each(graph_.cbegin(), graph_.cend(),
			[this](const auto& tuple)
			{
				structure_[tuple.first] = component::Vertex<id_type>::invalidInstance_;
			});
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	dfs<id_type>::dfs_recursive(const typename dfs<id_type>::vertex_type& root)
	{

	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	dfs<id_type>::dfs_stack(
			const typename dfs<id_type>::vertex_type& root)
	{
		// initialize stack
		std::stack<typename dfs<id_type>::vertex_type> stack;
		stack.push(root);
		// initialize parent
		typename dfs<id_type>::vertex_type parent = root;

		while (!stack.empty())
		{
			// pop current top vertex
			auto currentVertex = stack.top();
			stack.pop();

			//DEBUG
			std::cout << "Current vertex is [ " << currentVertex.Id() << " ]\n";
			//DEBUG

			// if not discovered
			if (!is_discovered(currentVertex))
			{
				//DEBUG
				std::cout << "	Label vertex [ " << currentVertex.Id()
						<< " ] as discovered with its parent: ["
						<< parent.Id()
						<< "]\n";
				//DEBUG

				// discover
				structure_[currentVertex] = parent;

				// proceed with children
				for (auto& neighbour : graph_.GetNeighbours(currentVertex))
				{
					stack.push(neighbour.GetVertex(1));
				}
			}

			// update parent
			parent = currentVertex;
		}
	}
}



#endif // GRAPH_LIB_ALGORITHM_TRAVERSAL_DFS_HPP
//==============================================================================
// End of dfs.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
