//==============================================================================
///
/// @file drawer.h
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

//==============================================================================
// Include only once
//
#ifndef GRAPH_LIB_DISPLAY_DRAWER_DRAWER_H
#define GRAPH_LIB_DISPLAY_DRAWER_DRAWER_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/component/edge-support.hpp"
#include <SFML/Graphics.hpp>                    // sf::RenderWindow, sf::Color, ...


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief namespace containing all structures used to display graph.
///
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    /// @brief Encapsulates colors used by a drawer object.
    ///
    //------------------------------------------------------------------------------
    class Palette
    {
    public:

        //------------------------------------------------------------------------------
        ///
        /// @brief Default constructor.
        ///
        //------------------------------------------------------------------------------
        Palette();

        //
        // State
        //
        /// @brief Primary drawing color.
        sf::Color primaryColor_;
        /// @brief Secondary drawing color.
        sf::Color secondaryColor_;
        /// @brief Window background color.
        sf::Color backgroundColor_;
    };

} // namespace output


//------------------------------------------------------------------------------
/// @brief namespace containing all structures used to display graph.
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    /// @brief Draws graphs.
    ///
    /// Manages window object and contains interface used to draw various objects.
    //------------------------------------------------------------------------------
    class Drawer
    {

    public:

        //------------------------------------------------------------------------------
        ///
        /// @brief Value constructor.
        ///
        /// @param[in] pWindow Pointer to sf::RenderWindow object.
        ///
        //------------------------------------------------------------------------------
        Drawer(sf::RenderWindow* pWindow);

        //------------------------------------------------------------------------------
        ///
        /// @brief Copy constructor.
        ///
        /// @param[in] drawer Drawer object to copy.
        ///
        //------------------------------------------------------------------------------
        Drawer(const Drawer& drawer);

        //------------------------------------------------------------------------------
        ///
        /// @brief Copy-assignment operator.
        ///
        /// @param[in] drawer Drawer object to copy.
        ///
        /// @return Reference to itself.
        ///
        //------------------------------------------------------------------------------
        const Drawer&
        operator=(const Drawer& drawer);

        //------------------------------------------------------------------------------
        ///
        /// @brief Window object getter.
        ///
        /// @return Reference to window object.
        ///
        //------------------------------------------------------------------------------
        // access window component 
        sf::RenderWindow&
        GetWindow();

        //------------------------------------------------------------------------------
        ///
        /// @brief Palette object getter.
        ///
        /// @return Reference to palette object.
        ///
        //------------------------------------------------------------------------------
        // access window component 
        Palette&
        GetPalette();

        //------------------------------------------------------------------------------
        ///
        /// @brief Draws graph's vertex.
        ///
        /// @param[in] x Vertex x-coordinate.
        ///
        /// @param[in] y Vertex y-coordinate.
        ///
        /// @param[in] id Vertex id.
        ///
        /// @param[in] color Vertex color.
        ///
        //------------------------------------------------------------------------------
        void
        DrawVertex(float x,
                   float y,
                   const std::string& id,
                   sf::Color color);

        //------------------------------------------------------------------------------
        ///
        /// @brief Draws graph's edge.
        ///
        /// @param[in] x1 Vertex1 x-coordinate.
        ///
        /// @param[in] y1 Vertex1 y-coordinate.
        ///
        /// @param[in] x2 Vertex2 x-coordinate.
        ///
        /// @param[in] y2 Vertex2 y-coordinate.
        ///
        /// @param[in] direction Edge direction type.
        ///
        /// @param[in] weight Edge weight.
        ///
        /// @param[in] color Edge color.
        ///
        //------------------------------------------------------------------------------
        void
        DrawEdge(float x1,
                 float y1,
                 float x2,
                 float y2,
                 component::traits::edge_direction direction,
                 int weight,
                 sf::Color color);

        //------------------------------------------------------------------------------
        ///
        /// @brief Draws text.
        ///
        /// @param[in] x Text x-coordinate.
        ///
        /// @param[in] y Text y-coordinate.
        ///
        /// @param[in] data Text to draw.
        ///
        /// @param[in] color Text color.
        ///
        //------------------------------------------------------------------------------
        void
        DrawText(float x,
                 float y,
                 const std::string& data,
                 sf::Color color);


    private:

        /// @brief SFML window object pointer.
        sf::RenderWindow* pWindow_;

        /// @brief Font to display strings.
        sf::Font font_;

        /// @brief Vertex size.
        float vertexRadius_;

        /// @brief Edge thickness.

        float edgeThickness_;

        /// @brief Color palette.
        Palette palette_;

    };

} //    namespace output



//
#endif // GRAPH_LIB_DISPLAY_DRAWER_DRAWER_H
//==============================================================================
// End of drawer.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
