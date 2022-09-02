//==============================================================================
///
/// @file outputter.hpp
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
#ifndef GRAPH_LIB_DISPLAY_OUTPUTTER_HPP
#define GRAPH_LIB_DISPLAY_OUTPUTTER_HPP


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <vector>
#include <algorithm>            // std::for_each
#include <sstream>              // std::stringstream

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/display/drawer/positioner.h"    // Positioner
#include "graph-lib/display/drawer/drawer.h"        // Drawer
//#include "graph-lib/graph.hpp"


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
// Forward declarations
//------------------------------------------------------------------------------
// (none)

namespace graph
{
    template<class id_type,
             typename implementation_type>
    class Graph;

} //    namespace graph


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief namespace containing all structures used to display graph.
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    /// @brief Outputter
    ///
    /// Displays graphs.
    //------------------------------------------------------------------------------
    template<class id_type>
    class Outputter
    {

        using graph_type            = graph::Graph<id_type>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor.
        ///
        //------------------------------------------------------------------------------
        Outputter();

        //------------------------------------------------------------------------------
        /// @brief Registers graph instance.
        ///
        /// @param[in] graph Graph to display.
        ///
        /// @return Reference to this object.
        ///
        //------------------------------------------------------------------------------
        Outputter&
        operator<<(graph_type& graph);


    private:

        //------------------------------------------------------------------------------
        /// @brief Fill graph vertices with coordinates.
        ///
        /// @param[in] graph Graph to display.
        ///
        //------------------------------------------------------------------------------
        void
        GetCoordinates(graph_type& graph);

        //------------------------------------------------------------------------------
        /// @brief Draw graph.
        ///
        /// @param[in] graph Graph to display.
        ///
        //------------------------------------------------------------------------------
        void
        DrawInstance(const graph_type& graph);


    private:

        /// @brief Object calculating coordinates.
        Positioner positioner_;

        /// @brief Object drawing graph's components.
        Drawer drawer_;

        /// @brief Window width.
        float width_;

        /// @brief Window height.
        float height_;

        /// @brief Number of window sectors.
        int sectorCount_;
    };

} //    namespace output


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

namespace output
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Outputter<id_type>::Outputter() : width_(1200.f),
                                      height_(800.f),
                                      sectorCount_(1),
                                      positioner_(0, 0.f, 0.f, 1200.f, 800.f),
                                      drawer_(nullptr)
    {   }



    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    Outputter<id_type>&
    Outputter<id_type>::operator<<(typename Outputter<id_type>::graph_type& graph)
    {
        // create SFML window instance for input graph
        sf::RenderWindow window(sf::VideoMode(width_, height_), "Current graph");

        // initialize necessary sub components
        drawer_ = Drawer(&window);
        positioner_ = Positioner(graph.Size(),
                                 0.f,
                                 0.f,
                                 width_,
                                 height_);

        // generate coordinates
        GetCoordinates(graph);

        // draw graph
        DrawInstance(graph);

        return *this;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::GetCoordinates(typename Outputter<id_type>::graph_type& graph)
    {
        auto coordinateContainer = positioner_.ComputeCoordinates();
        auto coordinateIter = coordinateContainer.begin();

        // iterate over <vertex, edge_list> pairs
        std::for_each(graph.begin(), graph.end(), 
            [&coordinateIter, &graph](auto& tuple)
            {
                // add coordinate to current vertex
                graph.UpdateVertex(tuple.first.Id(), coordinateIter->first, coordinateIter->second);
                ++coordinateIter;
            });
    }



    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::DrawInstance(const typename Outputter<id_type>::graph_type& graph)
    {
        //event loop
        while (drawer_.GetWindow().isOpen())
        {
            // add some more sophisticated event handling
            sf::Event event;
            while (drawer_.GetWindow().pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    drawer_.GetWindow().close();
            }

            // clean canvas
            drawer_.GetWindow().clear(drawer_.GetPalette().backgroundColor_);

            // iterate over <vertex, edge_list> pairs
            std::for_each(graph.cbegin(), graph.cend(),
                [this](const auto& tuple)
                {
                    // iterate over edge_list
                    std::for_each(tuple.second.begin(), tuple.second.end(),
                        [this](const auto& edge)
                        {
                            // draw edge
                            drawer_.DrawEdge(edge.GetVertex(0).Coordinate(0),
                                             edge.GetVertex(0).Coordinate(1),
                                             edge.GetVertex(1).Coordinate(0),
                                             edge.GetVertex(1).Coordinate(1),
                                             edge.GetDirection(),
                                             edge.GetWeight());
                        });
                });

            // iterate over <vertex, edge_list> pairs
            std::for_each(graph.cbegin(), graph.cend(),
                [this](const auto& tuple)
                {
                    // convert id_type id to string
                    std::stringstream converter;
                    std::string stringId;
                    converter << tuple.first.Id();
                    converter >> stringId;

                    // drqw vertex
                    drawer_.DrawVertex(tuple.first.Coordinate(0),
                                       tuple.first.Coordinate(1),
                                       stringId);
                });
                
            // display graph 
            drawer_.GetWindow().display();
        }
    }

} //    namespace output



#endif // GRAPH_LIB_DISPLAY_OUTPUTTER_HPP
//==============================================================================
// End of outputter.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
