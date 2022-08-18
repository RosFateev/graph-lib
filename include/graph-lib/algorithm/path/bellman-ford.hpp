// Header description:
//
// Author: Rostislav Fateev

#ifndef GRAPH_ALGORITHM_BELLMAN_FORD_HPP
#define GRAPH_ALGORITHM_BELLMAN_FORD_HPP





//includes
//related
//c
//std 
//lib
//user 





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

	// Bellman-Ford algorithm class declaration

	template<   typename                    IdType,
                template<typename> typename EdgeType>
	class BellmanFord
	{
		// type aliases for internal use
		using v_traits    = component::vertextraits::vertex_traits<IdType>;
		using vertex_type = component::Vertex<IdType>;
		using edge_type   = EdgeType<IdType>;
		using graph_type  = graph::Graph<IdType, EdgeType>;





	public:
	private:

	};

} // namespace pathsearch


#endif //GRAPH_ALGORITHM_BELLMAN_FORD_HPP