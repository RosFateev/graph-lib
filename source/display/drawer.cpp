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
#include <iostream>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
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
    Palette::Palette() : primaryColor_(sf::Color::Black),
                         secondaryColor_(sf::Color::Red),
                         backgroundColor_(sf::Color::White)
    {    }

} // namespace output



//------------------------------------------------------------------------------
//
//  Drawer class definition.
//
//------------------------------------------------------------------------------
namespace output
{
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
        if (!font_.loadFromFile("resources/Calibri-Regular.ttf"))
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

        return *this;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    // access window component 
    sf::RenderWindow&
    Drawer::GetWindow()
    {
        return *pWindow_;
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Palette&
    Drawer::GetPalette()
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
                     int weight)
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

} // namespace output



//==============================================================================
// End of drawer.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
