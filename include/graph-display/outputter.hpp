#ifndef GRAPH_DISPLAY_OUTPUTTER
#define GRAPH_DISPLAY_OUTPUTTER



//related
//c
//std 
#include <memory>
#include <utility>
//lib
//user 



namespace outputter
{

	template<   class Data,
	            template<typename> typename EdgeType>
	class Outputter
	{
	public:
		//constructors
		Outputter(Graph<Data, EdgeType>*);

		//visualizes graph object
		void Display();

	private:
		Graph<Data, EdgeType>* graphObj_;


	}

} //	namespace outputter



#endif //GRAPH_DISPLAY_OUTPUTTER