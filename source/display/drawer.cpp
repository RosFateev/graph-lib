//==============================================================================
///
/// @file drawer.cpp
///
/// @brief <description>
///
/// <Detailed description>
///
/// The documentation is available on the following website:
/// <website>
///
/// Support email: <email>
///
//==============================================================================


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <vector>
#include <string>
#include <sstream>
#include <memory>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include <SFML/Graphics.hpp>                    // sf::RenderWindow, sf::Color, ...
#include "graph-lib/display/drawer/drawer.h"


//------------------------------------------------------------------------------
// Global references
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Local data types
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward function declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
<data type> <function name>(...)
{

}

//------------------------------------------------------------------------------
//
//  Palette class definition.
//
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Palette::Palette() : primaryColor_(0,0,0),
                         secondaryColor_(),
                         backgroundColor_()
    {    }

} // namespace output



//------------------------------------------------------------------------------
//
//  Drawer class definition.
//
//------------------------------------------------------------------------------
namespace output
{
            /// @brief SFML window object.
        sf::RenderWindow* pWindow_;

        /// @brief Font to display strings.
        sf::Font font_;

        /// @brief Vertex size.
        float vertexSize_;

        /// @brief Edge thickness.

        float edgeThickness_;

        /// @brief Color palette.
        Palette palette_;

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Drawer::Drawer(sf::RenderWindow* pWindow) : pWindow_(pWindow),
                                                vertexSize_(20.f),
                                                edgeThickness_(2),
                                                palette_()
    {
        if (!font_.loadFromFile("include/graph-display/Calibri-Regular.ttf"))
        {
            std::cout << "font wasn't loaded" << std::endl;
        }
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Drawer::Drawer(const Drawer& drawer) : pWindow_(drawer.pWindow_),
                                           vertexSize_(drawer.vertexSize_),
                                           edgeThickness_(2),
                                           palette_(drawer.palette_),
                                           font_(drawer.font_)
    {   }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    const Drawer&
    Drawer::operator=(const Drawer& drawer)
    {
        pWindow_ = drawer.pWindow_;
        vertexSize_ = drawer.vertexSize_;
        edgeThickness_ = drawer.edgeThickness_,
        palette_ = drawer.palette_;
        font_ = drawer.font_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    // access window component 
    sf::RenderWindow&
    Drawer::Window()
    {
        return *pWindow_;
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Palette&
    Drawer::Palette()
    {
        return palette_;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    // prepare individual components to be displayed
    void
    Drawer::DrawVertex(float x,
                       float y,
                       const std::string& id)
    {
        // prepare vertex shape
        sf::CircleShape circle(vertexSize_);
        circle.setOutlineThickness(vertexSize_ / 4.f);
        circle.setOutlineColor(palette_.primaryColor_);
        circle.setPosition(x, y);

        // prepare index
        sf::Text text;
        text.setFont(font_);
        text.setString(id);
        text.setFillColor(palette_.primaryColor_);
        text.setCharacterSize(int(vertexSize_) + 10);
        text.setPosition(x + 12.f, y);
        
        // draw
        pWindow_->draw(circle);
        pWindow_->draw(text);
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void
    Drawer::DrawEdge(float x1,
                     float y1,
                     float x2,
                     float y2,
                     component::traits::edge_direction direction,
                     const std::string& weight)
    {
        // create edge
        sf::Vertex edge[] =
        {
            sf::Vertex(sf::Vector2f(x1 + vertexSize_, y1 + vertexSize_), palette_.primaryColor_),
            sf::Vertex(sf::Vector2f(x2 + vertexSize_, y2 + vertexSize_), palette_.primaryColor_)
        };

        // draw
        pWindow_->draw(edge, 2, sf::Lines);  // edge
    }


//
// MOVE TO OUTPUTTER
//
    // Draw graph
    template< typename id_type>
    void    Drawer<id_type>::DrawInstance(const typename Drawer<id_type>::out_instance_type& instance)
    {
        //event loop
        while (pWindow_->isOpen())
        {
            // add some more sophisticated event handling
            sf::Event event;
            while (pWindow_->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    pWindow_->close();
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
//
// MOVE TO OUTPUTTER
//

} // namespace output



//==============================================================================
// End of drawer.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
