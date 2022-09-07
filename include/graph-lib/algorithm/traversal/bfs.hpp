//==============================================================================
///
/// @file bfs.hpp
///
/// @brief Breadth First Search algorithm
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
#ifndef GRAPH_LIB_ALGORITHM_TRAVERSAL_BFS_HPP
#define GRAPH_LIB_ALGORITHM_TRAVERSAL_BFS_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <map>
#include <queue>
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
	/// @brief BFS implementation.
	///
	//------------------------------------------------------------------------------
	template<class id_type>
	class bfs
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
		bfs(const graph_type* pGraph);

		//------------------------------------------------------------------------------
		///
		/// @brief Execute BFS algorithm.
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

		//------------------------------------------------------------------------------
		///
		/// @brief Get algorithm's graph.
		///
		/// @return Reference to graph object.
		///
		//------------------------------------------------------------------------------
		const graph_type*
		get_graph();


	private:

		//------------------------------------------------------------------------------
		///
		/// @brief Check if second enpoint was visited by BFS algorithm.
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
		/// @brief Queue BFS implementation.
		///
		/// @param[in] root Starting vertex.
		///
		//------------------------------------------------------------------------------
		void
		bfs_queue(const vertex_type& root);

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
	bfs<id_type>::bfs(const typename bfs<id_type>::graph_type* pGraph) : pGraph_(pGraph)
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
	bfs<id_type>::run(const typename bfs<id_type>::vertex_type& root)
	{
		bfs_queue(root);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename bfs<id_type>::parent_structure&
	bfs<id_type>::get()
	{
		return structure_;
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename bfs<id_type>::graph_type*
	bfs<id_type>::get_graph()
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
	bfs<id_type>::is_discovered(const typename bfs<id_type>::vertex_type& vertex)
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
	bfs<id_type>::flush_structure()
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
	bfs<id_type>::bfs_queue(
			const typename bfs<id_type>::vertex_type& root)
	{
		// initialize connection queue
		std::queue<std::pair<typename bfs<id_type>::vertex_type, 
							 typename bfs<id_type>::vertex_type>> queue;
		// artificial algorithm initializer edge
		auto rootConnection = std::make_pair(root,root);
		queue.push(rootConnection);

		while (!queue.empty())
		{
			// pop current top vertex
			auto neighbourConnection = queue.front();
			queue.pop();
			//DEBUG
			std::cout << "		- < [" << neighbourConnection.first.Id() << "], ["
			<< neighbourConnection.second.Id() << "], ...> removed from queue\n"; 
			//DEBUG

			// if not discovered
			if (!is_discovered(neighbourConnection.second))
			{
				//DEBUG
				std::cout << "	Label current < [" 
				<< neighbourConnection.first.Id() << "], ["
				<< neighbourConnection.second.Id() << "] > as discovered\n";
				//DEBUG

				// label as discovered
				structure_.at(neighbourConnection.second) = neighbourConnection.first;

				// proceed with children
				for (auto& neighbourEdge : pGraph_->GetNeighbours(neighbourConnection.second))
				{
					//DEBUG
					std::cout << "		+ < [" << neighbourEdge.GetVertex(0).Id() << "], ["
					<< neighbourEdge.GetVertex(1).Id() << "] > added to queue\n"; 
					//DEBUG
					auto tmpPair = std::make_pair(neighbourEdge.GetVertex(0), neighbourEdge.GetVertex(1));

					queue.push(tmpPair);
				}

			}
		}
	}

}



#endif // GRAPH_LIB_ALGORITHM_TRAVERSAL_BFS_HPP
//==============================================================================
// End of bfs.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
