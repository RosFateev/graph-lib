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
#include <cmath>                // asin, sqrt, pow

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
                                                vertexRadius_(20.f),
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
                                           vertexRadius_(drawer.vertexRadius_),
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
        vertexRadius_ = drawer.vertexRadius_;
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
                       const std::string& id,
                       sf::Color color)
    {
        // draw vertex shape
        sf::CircleShape circle(vertexRadius_);
        circle.setOutlineThickness(vertexRadius_ / 4.f);
        circle.setOutlineColor(color);
        circle.setPosition(x, y);
        
        pWindow_->draw(circle);

        // draw vertex id
        DrawText(x, y, id, color);
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
                     int weight,
                     sf::Color color)
    {
        // draw edge core
        sf::Vertex edge[] =
        {
            sf::Vertex(sf::Vector2f(x1 + vertexRadius_, y1 + vertexRadius_), color),
            sf::Vertex(sf::Vector2f(x2 + vertexRadius_, y2 + vertexRadius_), color)
        };

        pWindow_->draw(edge, 2, sf::Lines);  // edge

        // display weight
        DrawText( (x1 + (x2 - x1)/2) - vertexRadius_, 
                  (y1 + (y2 - y1)/2) - vertexRadius_,
                  std::to_string(weight),
                  color);


        // directed edge
        if (direction == component::traits::edge_direction::one_two)
        {
            sf::CircleShape indicator(vertexRadius_ / 2);
            indicator.setFillColor(palette_.primaryColor_);

            // consider 3 points for 2 vectors with a common point
            float initial_x = x2;
            float initial_y = y2;
            
            // to avoid float comparison
            int x1Int = int(x1);
            int y1Int = int(y1);
            int x2Int = int(x2);
            int y2Int = int(y2);
            if (x2Int > x1Int)
            {
                if (y2Int > y1Int)
                {
                    initial_x -= vertexRadius_;
                    initial_y -= vertexRadius_;
                }
                else if (y2Int == y1Int)
                {
                    initial_x -= vertexRadius_;
                }
                else
                {   // y2Int < y1Int
                    initial_x -= vertexRadius_;
                    initial_y += vertexRadius_;
                }
            }
            else if (x2Int == x1Int)
            {
                if (y2Int > y1Int)
                {
                    initial_y -= vertexRadius_;
                }
                else
                {   // y2Int < y1Int
                    initial_y += vertexRadius_;
                }

            }
            else
            {   // (x2Int < x1Int)
                if (y2Int > y1Int)
                {
                    initial_x += vertexRadius_;
                    initial_y -= vertexRadius_;
                }
                else if (y2Int == y1Int)
                {
                    initial_x += vertexRadius_;
                }
                else
                {   // y2Int < y1Int
                    initial_x += vertexRadius_;
                    initial_y += vertexRadius_;
                }

            }

            // set indicator position
            indicator.setPosition(initial_x, initial_y);

            pWindow_->draw(indicator);
        }
    }


    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    void
    Drawer::DrawText(float x,
                     float y,
                     const std::string& data,
                     sf::Color color)
    {
        // prepare index
        sf::Text text;
        text.setFont(font_);
        text.setString(data);
        text.setFillColor(color);
        text.setCharacterSize(int(vertexRadius_) + 10);
        text.setPosition(x + 12.f, y);

        pWindow_->draw(text);
    }

} // namespace output



//==============================================================================
// End of drawer.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
