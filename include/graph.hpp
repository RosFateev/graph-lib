#ifndef GRAPH_HPP
#define GRAPH_HPP



//std
#include <initializer_list>
#include <utility>                    //std::forward
//user
#include "graph-implementation/manager.hpp"



//forward declarations
namespace component
{
	template<   class Data>
	class Vertex;

} //	namespace component





namespace graph
{
	template<    class Data,
	             template<typename> typename EdgeType>
	class Graph
	{
		//type aliases
		using vertex_type    = component::Vertex<Data>;
		using manager_type   = graphimp::Manager<Data, EdgeType>;
		using init_list_type = std::pair<const vertex_type, std::vector<EdgeType<Data>>>; 

	public:
		//constructors
		Graph();													//default
		Graph(const Graph&);										//copy
		
		Graph(std::initializer_list<init_list_type>&&);		//initializer list
		
		template<	class InputIterator>			
		Graph(	InputIterator, 
				InputIterator);										//input iterator
		

		//operators
		const Graph&	operator=(const Graph&);					//copy-assignment


		//component manipulators
		//Vertex
		template<   class ArgT>
		void           AddVertex(   ArgT&& inArg);

		const vertex_type&   GetVertex(	Data&& inId);

		void           RemoveVertex(Data&& inId);
		
		//Edge
		template<   class ...Args>
		void              AddEdge(    Args&&... args);

		
		template<   class ArgT>
		EdgeType<Data>&   GetEdge(    ArgT&& inArg1,
			                          ArgT&& inArg2);

		template<   class ArgT>
		void              RemoveEdge( ArgT&&,
			                          ArgT&&);

		template<   class ArgT>
		std::vector<EdgeType<Data>>&         GetNeighbours(   ArgT&& inArg);
		
		template<   class ArgT>
		const std::vector<EdgeType<Data>>&   GetNeighbours(   ArgT&& inArg) const;

		//method to remove

		void print();
	private:
		manager_type manager_;
		// methods
	};

} //	namespace graph	





namespace graph
{
	//Graph implementation
	//constructors
	template<   class Data,
	            template<typename> typename EdgeType>
	Graph<Data, EdgeType>::Graph()
	{   }
		
	template<   class Data,
	            template<typename> typename EdgeType>
	Graph<Data, EdgeType>::Graph(   const Graph<Data, EdgeType>& inGraph) : manager_(inGraph.manager_)
	{   }

	template<   class Data,
	            template<typename> typename EdgeType>
	Graph<Data, EdgeType>::Graph(	std::initializer_list<init_list_type>&& inList) : manager_(std::forward<std::initializer_list<init_list_type>>(inList))
	{   }	

	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class InputIterator>
	Graph<Data, EdgeType>::Graph(   InputIterator first,
		                            InputIterator last) :  manager_(first,last)
	{   }

	template<   class Data,
	            template<typename> typename EdgeType>
	const Graph<Data, EdgeType>& Graph<Data, EdgeType>::operator=(   const Graph<Data, EdgeType>& inGraph)
	{	
		manager_ = inGraph.manager_;
	}



	//component manipulators
	//Vertex
	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	void           Graph<Data, EdgeType>::AddVertex(   ArgT&& inArg) 
	{ 
		manager_.AddVertex(std::forward<ArgT>(inArg)); 
	}
	
	template<   class Data,
	            template<typename> typename EdgeType>
	const component::Vertex<Data>&   Graph<Data, EdgeType>::GetVertex(	Data&& inId) 
	{ 
		return manager_.GetVertex(std::forward<Data>(inId)); 
	}

	template<   class Data,
	            template<typename> typename EdgeType>
	void           Graph<Data, EdgeType>::RemoveVertex(Data&& inId) 
	{ 
		manager_.RemoveVertex(std::forward<Data>(inId)); 
	}
		
	//Edge
	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ...Args>
	void              Graph<Data, EdgeType>::AddEdge(    Args&&... args)
	{
		manager_.AddEdge(std::forward<Args>(args)...);
	}
	
	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	EdgeType<Data>&   Graph<Data, EdgeType>::GetEdge(    ArgT&& inArg1,
			                                             ArgT&& inArg2) 
	{ 
		return manager_.GetEdge(std::forward<ArgT>(inArg1), std::forward<ArgT>(inArg2));
	}
	
	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	void              Graph<Data, EdgeType>::RemoveEdge( ArgT&& inArg1,
			                                             ArgT&& inArg2)
	{
		return manager_.RemoveEdge(std::forward<ArgT>(inArg1), std::forward<ArgT>(inArg2));	
	}

	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	std::vector<EdgeType<Data>>&         Graph<Data, EdgeType>::GetNeighbours(   ArgT&& inArg)
	{ 
		return manager_.GetNeighbours(std::forward<ArgT>(inArg));
	}

	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	const std::vector<EdgeType<Data>>&   Graph<Data, EdgeType>::GetNeighbours(   ArgT&& inArg) const
	{ 
		return manager_.GetNeighbours(std::forward<ArgT>(inArg));
	}

	//methods to remove
	template<   class Data,
	            template<typename> typename EdgeType>
	void Graph<Data, EdgeType>::print()
	{
		manager_.print();
	}
	
} //	namespace graph



#endif //GRAPH_HPP