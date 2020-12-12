#ifndef GRAPH_IMPLEMENTATION_MANAGER_HPP
#define GRAPH_IMPLEMENTATION_MANAGER_HPP



//related
//c
//std
#include <initializer_list>
#include <utility>                    //std::forward
//lib
//user
#include "graph-implementation/adjacency-list.hpp"
#include "graph-implementation/incidence-matrix.hpp"



//forward declarations
namespace component
{
	template<   class Data>
	class Vertex;

}





namespace graphimp
{
	template<   class Data,
	            template<typename> typename EdgeType>
	class Manager
	{
	private:
		//type aliases
		using vertex_type      = component::Vertex<Data>;
		using adj_list_type    = adjlist::AdjacencyList<Data, EdgeType>;
		using inc_matrix_type  = incmatrix::IncidenceMatrix<Data, EdgeType>;
		using init_list_type   = std::pair<const vertex_type, std::vector<EdgeType<Data>>>; 

	public:
		//constructors
		Manager();														//default
		Manager(    const Manager&);									//copy

		Manager(    std::initializer_list<init_list_type>&&);		//initializer list

		template<   class InputIterator>
		Manager(    InputIterator,
		            InputIterator);										//input iterator
		

		//operators
		Manager&   operator=(   const Manager&);						//copy-assignment


		//component manipulators
		void    Default(   bool value);
		
		bool    Default() const;

		template<   class ArgT>
		void           AddVertex(   ArgT&& inArg);

		const vertex_type&   GetVertex(	Data&& inId);

		void           RemoveVertex(Data&& inId);

		template<   class ...Args>
		void              AddEdge(    Args&&... args);

		template<   class ArgT>
		EdgeType<Data>&   GetEdge(    ArgT&& inArg1,
			                          ArgT&& inArg2);

		template<   class ArgT>
		void              RemoveEdge( ArgT&& inArg1,
			                          ArgT&& inArg2);

		template<   class ArgT>
		std::vector<EdgeType<Data>>&   GetNeighbours(   ArgT&& inArg);

		template<   class ArgT>
		const std::vector<EdgeType<Data>>&   GetNeighbours(   ArgT&& inArg) const;
		//method to remove

		void print();

	private:
		//state
		bool             default_;
		adj_list_type    list_;
		inc_matrix_type  matrix_;

		//methods
	};

} //	namespace graphimp





namespace graphimp
{
	//Manager implementation
	//constructors
	template<   class Data,
	            template<typename> typename EdgeType>
	Manager<Data, EdgeType>::Manager() :  default_(true)
	{   }

	template<   class Data,
	            template<typename> typename EdgeType>
	Manager<Data, EdgeType>::Manager(   const Manager<Data, EdgeType>& inManager) : default_(inManager.default_),
	                                                                                list_(inManager.list_),
	                                                                                matrix_(inManager.matrix_)
	{   }

	template<   class Data,
	            template<typename> typename EdgeType>
	Manager<Data, EdgeType>::Manager(   std::initializer_list<init_list_type>&& inList) : default_(true),
	                                                                                      list_(std::forward<std::initializer_list<init_list_type>>(inList)),
	                                                                                      matrix_()
	{   }
	
	
	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class InputIterator>
	Manager<Data, EdgeType>::Manager(   InputIterator first,
	                                    InputIterator last) :   list_(first, last)
	{   }
    

	template<   class Data,
	            template<typename> typename EdgeType>
	Manager<Data, EdgeType>& Manager<Data, EdgeType>::operator=(   const Manager<Data, EdgeType>&)
	{	}




	//component manipulators
	template<   class Data,
	            template<typename> typename EdgeType>
	void    Manager<Data, EdgeType>::Default(   bool value) 
	{ 
		default_ = value;
	}
	
	template<   class Data,
	            template<typename> typename EdgeType>
	bool    Manager<Data, EdgeType>::Default() const
	 { 
	 	return default_;
	 }
    
    template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	void           Manager<Data, EdgeType>::AddVertex(   ArgT&& inArg)
	{
		list_.AddVertex(std::forward<ArgT>(inArg));
	}
    
    template<   class Data,
	            template<typename> typename EdgeType>
	const component::Vertex<Data>&   Manager<Data, EdgeType>::GetVertex(	 Data&& inId)
	{ 
		return list_.GetVertex(std::forward<Data>(inId));
	}

	template<   class Data,
	            template<typename> typename EdgeType>
	void           Manager<Data, EdgeType>::RemoveVertex(Data&& inId)
	{
		list_.RemoveVertex(std::forward<Data>(inId));
	}

    
    //Edge
    template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ...Args>
	void              Manager<Data, EdgeType>::AddEdge(    Args&&... args)
	{
		list_.AddEdge(std::forward<Args>(args)...);
	}

    template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	EdgeType<Data>&   Manager<Data, EdgeType>::GetEdge(    ArgT&& inArg1,
		                                                   ArgT&& inArg2)
	{
		return list_.GetEdge(std::forward<ArgT>(inArg1), std::forward<ArgT>(inArg2));
	}
    
    template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	void              Manager<Data, EdgeType>::RemoveEdge( ArgT&& inArg1,
		                                                   ArgT&& inArg2)
	{
		list_.RemoveEdge(std::forward<ArgT>(inArg1), std::forward<ArgT>(inArg2));
	}

    
    template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	std::vector<EdgeType<Data>>&         Manager<Data, EdgeType>::GetNeighbours(   ArgT&& inArg)
	{ 
		return list_.GetNeighbours(std::forward<ArgT>(inArg));
	}

	template<   class Data,
	            template<typename> typename EdgeType>
	template<   class ArgT>
	const std::vector<EdgeType<Data>>&   Manager<Data, EdgeType>::GetNeighbours(   ArgT&& inArg) const
	{ 
		return list_.GetNeighbours(std::forward<ArgT>(inArg));
	}


	//methods to remove
	template<   class Data,
	            template<typename> typename EdgeType>
	void Manager<Data, EdgeType>::print()
	{
		list_.print();
	}

} //	namespace graphimp



#endif //GRAPH_IMPLEMENTATION_MANAGER_HPP