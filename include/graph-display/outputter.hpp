#ifndef GRAPH_DISPLAY_OUTPUTTER
#define GRAPH_DISPLAY_OUTPUTTER



//related
#include <GL/glut.h>		//openGl
//c
//std 
#include <queue>			//
#include <memory>			//unique pointer
//lib
//user 










//
// Forward declarations
//
namespace component
{
	template<	class 	IdType>
	class Vertex;

	template<	class 	IdType,
				bool	eFlag>
	class Edge;
} //	namespace component



namespace graph
{
	template<	class 						IdType,
				template<typename> typename EdgeType>
	class Graph;
} //	namespace graph










//
//	OutObject registers a specific
//
namespace outputter
{
	class OutObject
	{
	public:
		virtual 			~OutObject(){}

		virtual 	void 	Draw() = 0;
	};





	template<	class 	IdType>
	class VertexOutObject : public OutObject
	{
		using vertex_type = component::Vertex<IdType>;

	public:
		// construction
		virtual 						~VertexOutObject(){}
							
										VertexOutObject(const vertex_type& inVertex) : object_(inVertex) {	}



		// accessors
				const 	vertex_type& 	Get() { return object_;}



		// drawing
		virtual 		void			Draw();

	private:
		const vertex_type& 	object_;
	};





	template<	class 	IdType,
				bool 	eFlag>
	class EdgeOutObject : public OutObject
	{
		using edge_type = component::Edge<IdType, eFlag>;

	public:
		// construction
		virtual 					~EdgeOutObject(){}
							
									EdgeOutObject(const edge_type& inEdge) : object_(inEdge) {	}



		// accessor
				const 	edge_type& 	Get() { return object_; }
		


		// drawing
		virtual 			void	Draw();

	private:
		const edge_type& 	object_;
	};





	template<	class 							IdType,
				template< typename > typename 	EdgeType>
	class GraphOutObject : public OutObject
	{
		using graph_type = graph::Graph<IdType, EdgeType>;

	public:
		// construction
		virtual 						~GraphOutObject(){}
							
										GraphOutObject(const graph_type& inGraph) : object_(inGraph) {	}

		

		// accessors
				const 	graph_type& 	Get() { return object_; }
		


		// drawing
		virtual 		void			Draw();

	private:
		const graph_type& 	object_;
	};

} //	namespace outputter










//
// Outputter component:
// - is a singleton
// - drawing frame owner
// - uses an overloaded << operator to output different graph lib components
//
namespace outputter
{
	class Outputter
	{
	private:
		// construction:
		// - copy construction methods are declared and deleted (in public section) - disallow
		// move construction and make copy construction inaccessible
	
						Outputter(const Outputter&);
		void 			operator=(const Outputter&);

		// helper methods
		// initializes an output frame
		void 			Initialize();


	public:
		// construction
						Outputter(const Outputter&) = delete;
		void 			operator=(const Outputter&) = delete;
						
		//
						Outputter() {}



		// core functionality
		template<	class 						IdType>
		Outputter& 		operator<<(const component::Vertex<IdType>&);
		
		template<	class 						IdType,
					bool						eFlag>
		Outputter& 		operator<<(const component::Edge<IdType, eFlag>&);

		template<	class 						IdType,
					template<typename> typename EdgeType>
		Outputter& 		operator<<(const graph::Graph<IdType, EdgeType>&);



		// method which glut calls to draw components
		void 			Display();

		void			Execute();

	private:
		
		//additional state
		std::queue<std::unique_ptr<OutObject>> 	log_;
	};

} //	namespace outputter










//
// Definition of helper components
//
namespace outputter
{
	//
	// Base outputter definition
	//
	template<	class 	IdType>
	void VertexOutObject::Draw()
	{

	}


	template<	class 	IdType,
				bool 	eFlag>
	void EdgeOutObject::Draw()
	{

	}



	template<	class 							IdType,
				template< typename > typename 	EdgeType>
	void GraphOutObject::Draw()
	{

	}
} //










//
//
//
namespace outputter
{
	template<	class 						IdType>
	Outputter& 						Outputter::operator<<(const 	component::Vertex<IdType>& 			inVertex)
	{
		// register an object 
		log_.push(std::unique_ptr<OutObject>(new VertexOutObject<IdType>(inVertex)));

		return *this;
	}
	
	template<	class 						IdType,
				bool						eFlag>
	Outputter& 						Outputter::operator<<(const 	component::Edge<IdType,eFlag>& 		inEdge)
	{
		// register an object 
		log_.push(std::unique_ptr<OutObject>(new EdgeOutObject<IdType, eFlag>(inEdge)));

		return *this;
	}

	template<	class 						IdType,
				template<typename> typename EdgeType>
	Outputter& 						Outputter::operator<<(const 	graph::Graph<IdType, EdgeType>& 	inGraph)
	{
		// register an object 
		log_.push(std::unique_ptr<OutObject>(new GraphOutObject<IdType, EdgeType>(inGraph)));

		return *this;
	}





	//
	void 			Outputter::Initialize()
	{
		// Use a single buffered window in RGB mode (as opposed to a double-buffered
  		// window or color-index mode).
  		glutInit(&argc, argv);
  		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		

		// Position window at (100,100)-(700,500) and give it a title.
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(600, 400);
		glutCreateWindow("Graph");

		// Tell GLUT that whenever the main window needs to be repainted that it
		// should call the function display().
		glutDisplayFunc(this->Display);
	}



	//  Draw graph's components (call display functions of corresponding outputter types)
	void 			Outputter::Display()
	{
		// clear the frame
		glClear(GL_COLOR_BUFFER_BIT);


		// draw code
		for(auto object : log_)
		{
			object->Draw();
		}

		// Flush drawing command buffer to make drawing happen as soon as possible.
		glFlush();
	}


	void 			Outputter::Execute()
	{
		this->Initialize();
		// Tell GLUT to start reading and processing events.  This function
		// never returns; the program only exits when the user closes the main
		// window or kills the process.
		glutMainLoop();
	}
	

} //	namespace outputter
//



#endif //GRAPH_DISPLAY_OUTPUTTER