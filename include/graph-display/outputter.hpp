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
// Outputter component:
//
namespace outputter
{
	class Outputter
	{
		//template<	class 						IdType,
		//			template<typename> typename EdgeType>
		//using graph_ptr = graph::Graph<IdType, EdgeType>;
	public:

		// initialized an openGL frame
		static void Initialize();

		// register objects, that need to be drawn
		static void Register();

		// exact code to draw the component
		static void Draw();

		// draw objects on frame
		static void Display();



		// main method 
		static void Show();




		
		// state
		static std::queue<GraphDummy> 	log_;
	};

	// initialize log container
	std::queue<GraphDummy> Outputter::log_;

} //	namespace outputter










//
//
//
namespace outputter
{
	//
	void 			Outputter::Initialize()
	{
		// dummy values thar glutInit requires
		int argc{0};
		char** argv = nullptr;

		// Use a single buffered window in RGB mode (as opposed to a double-buffered
		// window or color-index mode).
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

		// Position window at (80,80)-(680,480) and give it a title.
		glutInitWindowPosition(80, 80);
		glutInitWindowSize(600, 400);
		glutCreateWindow("Outputter");

		// Tell GLUT that whenever the main window needs to be repainted that it
		// should call the function display().
		glutDisplayFunc(outputter::Outputter::Display);
	}



	//
	void 			Outputter::Register()
	{
		//log_.push(graph_ptr);
	}



	//
	void 			Outputter::Draw()
	{
		/* Vertex
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(inVertex.X() + 0.01f, inVertex.Y() + 0.01f);
				glVertex2f(inVertex.X() + 0.01f, inVertex.Y() - 0.01f);
				glVertex2f(inVertex.X() - 0.01f, inVertex.Y() + 0.01f);
				glVertex2f(inVertex.X() - 0.01f, inVertex.Y() - 0.01f);
			glEnd();
		*/
		/* Edge
			glBegin(GL_LINES);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(inEdge.First().X(), inEdge.First().Y());
				glVertex2f(inEdge.Second().X(), inEdge.Second().Y());
			glEnd();
		*/
	}



	//  Draw graph's components (call display functions of corresponding outputter types)
	void 			Outputter::Display()
	{
		// Set every pixel in the frame buffer to the current clear color.
		glClear(GL_COLOR_BUFFER_BIT);

		// Drawing is done by specifying a sequence of vertices.  The way these
		// vertices are connected (or not connected) depends on the argument to
		// glBegin.  GL_POLYGON constructs a filled polygon.
		for(auto iter = log_.begin(); iter != log_.end(); ++iter)
		{ 
			Draw(*iter);
		}

		// Flush drawing command buffer to make drawing happen as soon as possible.
		glFlush();
	}
	}


	void 			Outputter::Show()
	{
		Initialize();

		// background color (white)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Tell GLUT to start reading and processing events.  This function
		// never returns; the program only exits when the user closes the main
		// window or kills the process.
		glutMainLoop();
	}
	

} //	namespace outputter
//



#endif //GRAPH_DISPLAY_OUTPUTTER