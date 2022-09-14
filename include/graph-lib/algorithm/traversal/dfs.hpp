//==============================================================================
///
/// @file dfs.hpp
///
/// @brief Depth First Search algorithm
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
#include "graph-lib/component/vertex.hpp"	// component::Vertex
#include "graph-lib/utility/print.hpp" 		// Debug printing


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
		/// @param[in] pGraph Input graph pointer.
		///
		//------------------------------------------------------------------------------
		dfs(const graph_type* pGraph);

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
		get() const;

		//------------------------------------------------------------------------------
		///
		/// @brief Get algorithm's graph.
		///
		/// @return Reference to graph object.
		///
		//------------------------------------------------------------------------------
		const graph_type*
		get_graph() const;


	private:

		//------------------------------------------------------------------------------
		///
		/// @brief Check if second enpoint was visited by DFS algorithm.
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
		/// @param[in] parent Parent vertex.
		///
		/// @param[in] vertex Current vertex.
		///
		//------------------------------------------------------------------------------
		void
		dfs_recursive(const vertex_type& parent,
					  const vertex_type& vertex);

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
		const graph_type* pGraph_;

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
	dfs<id_type>::dfs(const typename dfs<id_type>::graph_type* pGraph) : pGraph_(pGraph)
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
		dfs_recursive(root, root);
		//dfs_stack(root);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename dfs<id_type>::parent_structure&
	dfs<id_type>::get() const
	{
		return structure_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename dfs<id_type>::graph_type*
	dfs<id_type>::get_graph() const
	{
		return pGraph_;
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
		// Discovered: parent structure contains valid entry for the second endpoint
		return (structure_.at(vertex) != 
				component::Vertex<id_type>::invalidInstance_);
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
		std::for_each(pGraph_->cbegin(), pGraph_->cend(),
			[this](const auto& tuple)
			{
				structure_[tuple.first] = 
					component::Vertex<id_type>::invalidInstance_;
			});
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	void
	dfs<id_type>::dfs_recursive(
			const typename dfs<id_type>::vertex_type& parent,
			const typename dfs<id_type>::vertex_type& vertex)
	{
		//DEBUG
		std::cout << "	DFS: Current connection<";
		print_vertex<id_type>(parent);
		std::cout << ", ";
		print_vertex<id_type>(vertex);
		std::cout << " >\n"; 
		//DEBUG

		// mark node as discovered
		structure_[vertex] = parent;

		// proceed with vertex children
		for (auto& neighbour : pGraph_->GetNeighbours(vertex))
		{
			if (!is_discovered(neighbour.GetVertex(1)))
			{
				//DEBUG
				std::cout << "		DFS:Proceed with ";
				print_vertex<id_type>(neighbour.GetVertex(1));
				std::cout << '\n';
				//DEBUG

				dfs_recursive(vertex, neighbour.GetVertex(1));
			}
		}
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
		// initialize connection stack
		std::stack<std::pair<typename dfs<id_type>::vertex_type, 
							 typename dfs<id_type>::vertex_type>> stack;
		// artificial algorithm initializer edge
		auto rootConnection = std::make_pair(root,root);
		stack.push(rootConnection);

		while (!stack.empty())
		{
			// pop current top connection
			auto neighbourConnection = stack.top();
			stack.pop();

			//DEBUG
			std::cout << "	DFS-stack: Current connection: < ";
			print_vertex<id_type>(neighbourConnection.first);
			std::cout << ", ";
			print_vertex<id_type>(neighbourConnection.second);
			std::cout <<  " >\n"; 
			//DEBUG

			// if not discovered
			if (!is_discovered(neighbourConnection.second))
			{
				//DEBUG
				std::cout << "		Label current connection as discovered\n";
				//DEBUG

				// label as discovered
				structure_.at(neighbourConnection.second) = neighbourConnection.first;

				// proceed with children
				for (auto& neighbourEdge : pGraph_->GetNeighbours(neighbourConnection.second))
				{
					//DEBUG
					std::cout << "		DFS-stack: Add to stack < ";
					print_vertex<id_type>(neighbourEdge.GetVertex(0));
					std::cout << ", ";
					print_vertex<id_type>(neighbourEdge.GetVertex(1));
					std::cout << " >\n";
					//DEBUG

					auto tmpPair = std::make_pair(neighbourEdge.GetVertex(0), neighbourEdge.GetVertex(1));

					stack.push(tmpPair);
				}

			}
		}
	}
}



#endif // GRAPH_LIB_ALGORITHM_TRAVERSAL_DFS_HPP
//==============================================================================
// End of dfs.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
