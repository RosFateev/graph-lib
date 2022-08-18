#ifndef GRAPH_DISPLAY_MANAGER_DRAWER
#define GRAPH_DISPLAY_MANAGER_DRAWER





//related
//c
//std 
#include <vector>
#include <string>
#include <sstream>
#include <memory>
//lib
#include <SFML/Graphics.hpp>        // graphics library





namespace graph
{
    template< typename id_type>
    class Graph;
}

namespace output
{
    template< typename id_type>
    class OutputInstance;
}










//
// Draws different GraphEntries
// - determines draw routines
// - produces a final 
//
namespace output
{
    template< typename id_type>
    class Drawer
    {
        using coordinate_type   = Coordinate;
        using out_instance_type = OutputInstance<id_type>;

    public:

        // construction
                            Drawer(sf::RenderWindow*);
                            
                            Drawer(Drawer&&);
        
        void                operator=(Drawer&&);



        // interface
        // prepares graph to be displayed
        void                DrawInstance(const out_instance_type&);

        

        // access window component 
        sf::RenderWindow&   Window();



    private:

        // prepare individual components to be displayed
        void                DrawVertex(float, float, const std::string&);

        void                DrawEdge(float, float, float, float);



    private:

        // state
        sf::RenderWindow*   window_;

        // cosmetics
        sf::Font            font_;
        float               vertex_size_;
        float               edge_thickness_;
        sf::Color           color_;

    };

} //    namespace output










//
// Drawer's implementation
//
namespace output
{
    // construction
    template< typename id_type>
    Drawer<id_type>::Drawer( sf::RenderWindow* inWindow) :  window_(inWindow),
                                                            vertex_size_(20.f),
                                                            edge_thickness_(2),
                                                            color_(0,0,0)
    {
        if (!font_.loadFromFile("include/graph-display/Calibri-Regular.ttf"))
        {
            std::cout << "font wasn't loaded" << std::endl;
        }
    }

    template< typename id_type>
    Drawer<id_type>::Drawer(Drawer&& inDrawer) :    window_(inDrawer.window_),
                                                    vertex_size_(inDrawer.vertex_size_),
                                                    edge_thickness_(2),
                                                    color_(inDrawer.color_),
                                                    font_(inDrawer.font_)
    {

    }

    template< typename id_type>
    void Drawer<id_type>::operator=(Drawer&& inDrawer)
    {
        window_ = inDrawer.window_;
        vertex_size_ = inDrawer.vertex_size_;
        color_ = inDrawer.color_;
        font_ = inDrawer.font_;

    }



    // Draw components
    // vertex
    template< typename id_type>
    void Drawer<id_type>::DrawVertex(   float x, float y, 
                                        const std::string& inId)
    {   
        // prepare vertex shape
        sf::CircleShape circle(vertex_size_);
        circle.setOutlineThickness(vertex_size_ / 4.f);
        circle.setOutlineColor(color_);
        circle.setPosition(x, y);

        // prepare index
        sf::Text text;
        text.setFont(font_);
        text.setString(inId);
        text.setFillColor(color_);
        text.setCharacterSize(int(vertex_size_) + 10);
        text.setPosition(x + 12.f, y);
        
        // draw
        window_->draw(circle);
        window_->draw(text);
    }

    // edge
    template< typename id_type>
    void Drawer<id_type>::DrawEdge( float x1, float y1,
                                    float x2, float y2)
    {   
        sf::Vertex edge[] =
        {
            sf::Vertex(sf::Vector2f(x1 + vertex_size_, y1 + vertex_size_), color_),
            sf::Vertex(sf::Vector2f(x2 + vertex_size_, y2 + vertex_size_), color_)
        };

        window_->draw(edge, 2, sf::Lines);  // edge
    }



    // Draw graph
    template< typename id_type>
    void    Drawer<id_type>::DrawInstance(const typename Drawer<id_type>::out_instance_type& instance)
    {
        //event loop
        while (window_->isOpen())
        {
            // add some more sophisticated event handling
            sf::Event event;
            while (window_->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window_->close();
            }

            // clean canvas
            this->Window().clear(sf::Color::White);

            // display components        
            for (auto edge_iterator = instance.Graph().e_begin(); edge_iterator != instance.Graph().e_end(); ++edge_iterator)
            {

                DrawEdge(   (*edge_iterator)->GetVertex(0).Coordinate(0), (*edge_iterator)->GetVertex(0).Coordinate(1),
                            (*edge_iterator)->GetVertex(1).Coordinate(0), (*edge_iterator)->GetVertex(1).Coordinate(1));
            }

            for (auto vertex_iterator = instance.Graph().v_begin(); vertex_iterator != instance.Graph().v_end(); ++vertex_iterator)
            {
                std::stringstream converter;
                std::string id_holder;
                
                // convert id_type to string
                converter << (*vertex_iterator)->Id();
                converter >> id_holder;

                std::cout << "id_holder" << id_holder << '\n';

                DrawVertex((*vertex_iterator)->Coordinate(0), (*vertex_iterator)->Coordinate(1), id_holder);
            }
                
            // display graph 
            this->Window().display();
        }
    }

        


    // return managed SFML window
    template< typename id_type>
    sf::RenderWindow& Drawer<id_type>::Window()
    {
        return *window_;
    }

} //    namespace output



#endif // GRAPH_DISPLAY_MANAGER_DRAWER