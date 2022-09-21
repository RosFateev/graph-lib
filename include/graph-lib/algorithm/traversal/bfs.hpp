//==============================================================================
///
/// @file bfs.hpp
///
/// @brief Breadth First Search algorithm implementation.
///
/// Breadth First Search is one of the most basic and core graph traversal
/// algorithms encapsulated inside an object. Algorithm class is parametrized by
/// graph's vertex id type. Single algorithm object works with single graph object.
/// Contains queue implementation and flow variation, the latter being used in
/// Edmonds-Karp flow algorithm to produce traversal tree depending on flow.
/// Both BFS produce a parent structure, which is a dictionary containing
/// child-parent pairs, where child - graph's vertex, parent - it's predecessor
/// in a traversal order.
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
#include <string>
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
		run(const vertex_type& root,
			std::string mode = "");

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
		/// @brief Check if vertex can be used by BFS algorithm.
		///
		/// @param[in] vertex Input vertex.
		///
		/// @retval True If vertex is available.
		/// @retval False otherwise.
		///
		//------------------------------------------------------------------------------
		bool
		is_available(const vertex_type& vertex);

		//------------------------------------------------------------------------------
		///
		/// @brief Check if edge can be used by BFS_flow algorithm.
		///
		/// @param[in] edge Input edge.
		///
		/// @retval True If it can.
		/// @retval False otherwise.
		///
		//------------------------------------------------------------------------------
		bool
		is_flow_available(const edge_type& edge);

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

		//------------------------------------------------------------------------------
		///
		/// @brief Queue BFS implementation for network flow.
		///
		/// @param[in] root Starting vertex.
		///
		//------------------------------------------------------------------------------
		void
		bfs_queue_flow(const vertex_type& root);

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
	bfs<id_type>::run(const typename bfs<id_type>::vertex_type& root,
					  std::string mode)
	{
		if (mode == "flow")
		{
			bfs_queue_flow(root);
		}
		else
		{
			bfs_queue(root);
		}
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	const typename bfs<id_type>::parent_structure&
	bfs<id_type>::get() const
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
	bfs<id_type>::get_graph() const
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
	bfs<id_type>::is_available(const typename bfs<id_type>::vertex_type& vertex)
	{
		// Not Discovered: parent structure contains invalid entry for the second endpoint
		return (structure_.at(vertex) == 
				component::Vertex<id_type>::invalidInstance_);
	}

	//------------------------------------------------------------------------------
	//
	//  <Design related information>
	//
	//------------------------------------------------------------------------------
	template<class id_type>
	bool
	bfs<id_type>::is_flow_available(const typename bfs<id_type>::edge_type& edge)
	{
		// Discovered: is_available(second_vert) returns true and capacity can accomodate more flow
		return (is_available(edge.GetVertex(1)) && (edge.GetCapacity() > edge.GetFlow()) );
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
			std::cout << "	BFS-queue: Current connection: < ";
			print_vertex<id_type>(neighbourConnection.first);
			std::cout << ", ";
			print_vertex<id_type>(neighbourConnection.second);
			std::cout <<  " >\n"; 
			//DEBUG

			// if not discovered
			if (is_available(neighbourConnection.second))
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
					std::cout << "		BFS-queue: Add to queue < ";
					print_vertex<id_type>(neighbourEdge.GetVertex(0));
					std::cout << ", ";
					print_vertex<id_type>(neighbourEdge.GetVertex(1));
					std::cout << " >\n";
					//DEBUG

					auto tmpPair = std::make_pair(neighbourEdge.GetVertex(0), neighbourEdge.GetVertex(1));

					queue.push(tmpPair);
				}

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
	bfs<id_type>::bfs_queue_flow(
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
			std::cout << "	BFS-flow: Current connection: < ";
			print_vertex<id_type>(neighbourConnection.first);
			std::cout << ", ";
			print_vertex<id_type>(neighbourConnection.second);
			std::cout <<  " >\n"; 
			//DEBUG

			// proceed with children
			for (auto& neighbourEdge : pGraph_->GetNeighbours(neighbourConnection.second))
			{
				// if neighbour vertex was not discovered
				if (is_flow_available(neighbourEdge))
				{
					//DEBUG
					std::cout << "		Label current connection as discovered\n";
					//DEBUG

					// label as discovered
					structure_.at(neighbourEdge.GetVertex(1)) = neighbourEdge.GetVertex(0);

					//DEBUG
					std::cout << "		BFS-flow: Add to queue < ";
					print_vertex<id_type>(neighbourEdge.GetVertex(0));
					std::cout << ", ";
					print_vertex<id_type>(neighbourEdge.GetVertex(1));
					std::cout << " >\n";
					//DEBUG

					auto tmpPair = std::make_pair(neighbourEdge.GetVertex(0), neighbourEdge.GetVertex(1));

					queue.push(tmpPair);
				}
			}
		}
	}

} // namespace algorithm



#endif // GRAPH_LIB_ALGORITHM_TRAVERSAL_BFS_HPP
//==============================================================================
// End of bfs.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
