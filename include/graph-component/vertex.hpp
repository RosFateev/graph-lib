// Header description: 
//
// This is an implementation of Vertex class
//
//
// Author: Rostislav Fateev

#ifndef GRAPH_COMPONENT_VERTEX_HPP
#define GRAPH_COMPONENT_VERTEX_HPP



// related
// c
// std 
#include <utility>
// lib
// user 





// A common namespace for graph's components: vertex and edge. It also contains their support
// classes (traits, policies etc.) in nested namespaces. 
namespace component
{

	// Vertex class declaration.
	
	template<   class IdType>
	class Vertex
	{
	public:

		// constructors
		explicit    Vertex(	IdType&&);

		            Vertex( const Vertex&);

		           ~Vertex() {}

		// operators
		const Vertex&   operator=(   const Vertex&);
		


		// accessors
		const IdType&     Id() const { return id_; }

		void              Id(IdType&& inId) { id_ = std::forward<IdType>(inId); }
	
	private:
		
		// state
		IdType id_;
	};

} //	namespace component





namespace component
{
	// Vertex definition
	// Constructors
	template <   class IdType>
	Vertex<IdType>::Vertex(   IdType&&              inId) :       id_(std::forward<IdType>(inId))
	{	}



	//
	template <   class IdType>
	Vertex<IdType>::Vertex(   const Vertex<IdType>& inVertex) :   id_(inVertex.id_)
	{	}



	//
	template <   class IdType>
	const Vertex<IdType>& Vertex<IdType>::operator=(   const Vertex<IdType>& inVertex)
	{
		id_ = inVertex.id_;

		return *this;
	}

} //	namespace component



#endif //GRAPH_COMPONENT_VERTEX_HPP