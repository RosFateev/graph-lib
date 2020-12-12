#ifndef GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H
#define GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H



//related
//c
//std 
#include <vector>
//lib
//user
#include "graph-component/vertex.hpp"



namespace incmatrix
{
	template<   class Data,
                template<  typename> typename EdgeType>
	class IncidenceMatrix
	{
	public:
		IncidenceMatrix() {}

		void AddVertex(const component::Vertex<Data>&);
		void AddEdge(const component::Vertex<Data>&, const component::Vertex<Data>&);

	private:
		std::vector<std::vector<bool>> matrix_;
		std::vector<component::Vertex<Data>> helpStructure_;
	};

} //	namespace incmatrix



#endif //GRAPH_IMPLEMENTATION_INCIDENCE_MATRIX_H