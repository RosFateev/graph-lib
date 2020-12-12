#ifndef GRAPH_COMPONENT_VERTEX_SUPPORT_HPP
#define GRAPH_COMPONENT_VERTEX_SUPPORT_HPP



//related
//c
//std 
//lib
//user 



namespace component
{
	namespace vertextraits
	{
		template<	class Data>
		class vertex_traits
		{	};

		template<>
		class vertex_traits<int>
		{
		public:
			enum {	children_delimeter	=	-2147483648, 
					layer_delimeter		=	2147483647  };
		};

		template<>
		class vertex_traits<char>
		{
		public:
			enum {	children_delimeter	=	-128, 
					layer_delimeter		=	127  };
			 
		};		

	} //	namespace vertextraits





	//support for data structures: unordered map and set
	namespace support
	{
		//needed for unordered_map to work with Vertex<Data> Key
		template<   class Data>
		class VertexHash
		{
		private:
			//type alias
			using vertex_type = component::Vertex<Data>;

		public:
			
			size_t operator()(    const vertex_type& inVertex) const
			{
				return std::hash<Data>()(inVertex.Id());
			}
		};

		template<   class Data>
		class VertexEqual
		{
		private:
			//type alias
			using vertex_type = component::Vertex<Data>;

		public:
			bool   operator()(    const vertex_type& lhs,
				                  const vertex_type& rhs) const
			{
				return lhs.Id() == rhs.Id();
			}
		};

	} //	namespace support

} //	namespace component



#endif //GRAPH_COMPONENT_VERTEX_SUPPORT_HPP