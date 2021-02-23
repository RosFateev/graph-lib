#ifndef GRAPH_COMPONENT_EDGE_HPP
#define GRAPH_COMPONENT_EDGE_HPP



//related
//c
//std
#include <memory>
//lib
//user



namespace component
{
	//forward declarations
	template<   class Data>
	class Vertex;





	template<   class Data,
	            bool  Type>
	class Edge
	{
	public:
		//constructors
		explicit    Edge(   const 	Vertex<Data>&, 
			                const 	Vertex<Data>&, 
			                int  	inWght 			= 0);
		
                    Edge(	const Edge&);

                    Edge(	Edge&&);


		//operators
		const Edge&	    operator=(   const Edge&);
		
		
		//element accessors
		const Vertex<Data>&	    First() const { return first_; }

		const Vertex<Data>&     Second() const { return second_; }

		int     Weight() const { return weight_; }

		void    Weight(int inWght) { weight_ = inWght; }
		
	private:
		//data
		const Vertex<Data>&   first_,
		                      second_;
		int   weight_;

	};



	template<   class Data>
	using UndirectedEdge = Edge<Data, false>;
	template<   class Data>
	using DirectedEdge   = Edge<Data, true>;

} //	namespace component





namespace component
{
	//Edge implementation
	//constructors
	template<   class Data,
	            bool  Type>
	Edge<Data, Type>::Edge(	  const Vertex<Data>& 		inVertex1, 
						      const Vertex<Data>& 		inVertex2,
						      int                 		inWght		) :   	first_(inVertex1), 
	                                                          				second_(inVertex2),
	                                                          				weight_(inWght)
	{	}
	


	//
	template<   class Data,
	            bool  Type>
	Edge<Data, Type>::Edge(   const Edge<Data, Type>& 	inEdge) :  	first_(inEdge.first_),
	                                                          	   	second_(inEdge.second_),
	                                                         		weight_(inEdge.weight_)
	{	}



	//
	template<   class Data,
	            bool  Type>
	Edge<Data, Type>::Edge(   Edge<Data, Type>&& 		inEdge) :  	first_(std::move(inEdge.first_)),
	                                                    	        second_(std::move(inEdge.second_)),
	                                                        	    weight_(std::move(inEdge.weight_))
	{	}



	//
	template<   class Data,
	            bool  Type>
	const Edge<Data, Type>& Edge<Data, Type>::operator=(   const Edge<Data, Type>& inEdge)
	{
		first_ = inEdge.first_;
		second_ = inEdge.second_;
		weight_ = inEdge.weight_;
	}
	
} //	namespace component



#endif //GRAPH_COMPONENT_EDGE_HPP