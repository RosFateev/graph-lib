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
        using vertex_type           = component::Vertex<id_type>;
        using edge_type             = component::Edge<id_type>;
        using graph_type            = graph::Graph<id_type>;
        using algorithm_result_type = std::map<vertex_type,
                                               vertex_type,
                                               component::support::vertex_less<id_type>>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Default constructor.
        ///
        //------------------------------------------------------------------------------
        Outputter();

        //------------------------------------------------------------------------------
        /// @brief Display object.
        ///
        /// @param[in] graph Graph to display.
        ///
        /// @param[in] pAlgResult Pointer to algorithm results to display with graph.
        ///
        //------------------------------------------------------------------------------
        void
        Display(graph_type& graph,
                const algorithm_result_type* pAlgResult = nullptr);


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
        /// @brief Draw graph and associated algorithm.
        ///
        /// @param[in] graph Graph to draw.
        ///
        /// @param[in] pAlgResult Pointer to algorithm results to draw with graph.
        ///
        //------------------------------------------------------------------------------
        void
        Draw(const graph_type& graph,
             const algorithm_result_type* pAlgResult);


        //------------------------------------------------------------------------------
        /// @brief Draw graph's edges.
        ///
        /// @param[in] graph Graph, which edges to draw.
        ///
        //------------------------------------------------------------------------------
        void DrawEdges(const graph_type& graph);


        //------------------------------------------------------------------------------
        /// @brief Draw graph's edges affected by algorithm.
        ///
        /// @param[in] graph Graph, which edges to draw.
        ///
        /// @param[in] pAlgResult Pointer to algorithm highlighted edges of a graph.
        ///
        //------------------------------------------------------------------------------
        void DrawEdges(const graph_type& graph,
                       const algorithm_result_type* pAlgResult);

        //------------------------------------------------------------------------------
        /// @brief Draw graph's vertices.
        ///
        /// @param[in] graph Graph, which vertices to draw.
        ///
        //------------------------------------------------------------------------------
        void DrawVertices(const graph_type& graph);

        


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
    Outputter<id_type>::Outputter() : width_(800.f),
                                      height_(600.f),
                                      sectorCount_(1),
                                      positioner_(0, 0.f, 0.f, 800.f, 600.f),
                                      drawer_(nullptr)
    {   }



    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::Display(
            typename Outputter<id_type>::graph_type& graph,
            const typename Outputter<id_type>::algorithm_result_type* pAlgResult)
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

        // Printing is not interactive - try to print stuff once
        // clean canvas
        drawer_.GetWindow().clear(drawer_.GetPalette().backgroundColor_);
        // draw graph
        Draw(graph, pAlgResult);
        // display window 
        drawer_.GetWindow().display();

        // display graph event loop
        while (drawer_.GetWindow().isOpen())
        {
            // add some more sophisticated event handling
            sf::Event event;
            while (drawer_.GetWindow().pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    drawer_.GetWindow().close();
            }
        }

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
    Outputter<id_type>::Draw(
            const typename Outputter<id_type>::graph_type& graph,
            const typename Outputter<id_type>::algorithm_result_type* pAlgResult)
    {
        // draw graph edges
        if (pAlgResult == nullptr)
        {
            // no algorithm provided
            DrawEdges(graph);
        }
        else
        {
            DrawEdges(graph, pAlgResult);
        }
        

        // draw graph vertices
        DrawVertices(graph);
    }


    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::DrawEdges(
            const typename Outputter<id_type>::graph_type& graph)
    {
        //DEBUG
        std::cout << "DrawEdges()\n";
        //DEBUG

        std::for_each(graph.cbegin(), graph.cend(),
            [this](const auto& tuple)
            {
                // iterate over edge_list
                std::for_each(tuple.second.begin(), tuple.second.end(),
                    [this](const auto& edge)
                    {
                        //DEBUG
                        std::cout << "Drawing < ["
                            << edge.GetVertex(0).Id() << "] ["
                            << edge.GetVertex(1).Id() << ", "
                            << (edge.GetDirection() == component::traits::edge_direction::none ? "---" : "-->")
                            << ", " << edge.GetWeight() << "> with primary color\n";
                        //DEBUG

                        // draw edge
                        drawer_.DrawEdge(edge.GetVertex(0).Coordinate(0),
                                         edge.GetVertex(0).Coordinate(1),
                                         edge.GetVertex(1).Coordinate(0),
                                         edge.GetVertex(1).Coordinate(1),
                                         edge.GetDirection(),
                                         edge.GetWeight(),
                                         drawer_.GetPalette().primaryColor_);
                    });
            });
    }


    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::DrawEdges(
            const typename Outputter<id_type>::graph_type& graph,
            const typename Outputter<id_type>::algorithm_result_type* pAlgResult)
    {
        //DEBUG
        std::cout << "DrawEdges(...,algorithm)\n";
        //DEBUG

        // variables used
        sf::Color edgeColor;

        std::for_each(graph.cbegin(), graph.cend(),
            [this, &pAlgResult, &edgeColor](const auto& tuple)
            {
                std::for_each(tuple.second.begin(), tuple.second.end(),
                    [this, &pAlgResult, &edgeColor](const auto& edge)
                    {
                        if ( (pAlgResult->at(edge.GetVertex(1)) == edge.GetVertex(0)) ||
                             (pAlgResult->at(edge.GetVertex(0)) == edge.GetVertex(1)))
                        {
                            edgeColor = drawer_.GetPalette().secondaryColor_;
                        }
                        else
                        {
                            edgeColor = drawer_.GetPalette().primaryColor_;
                        }

                        //DEBUG
                        std::cout << "Drawing < ["
                            << edge.GetVertex(0).Id() << "] ["
                            << edge.GetVertex(1).Id() << ", "
                            << (edge.GetDirection() == component::traits::edge_direction::none ? "---, " : "-->, ")
                            << edge.GetWeight()
                            << "> with "
                            << (edgeColor == drawer_.GetPalette().primaryColor_ ? "primary" : "secondary")
                            << " color\n";
                        //DEBUG

                        // draw edge
                        drawer_.DrawEdge(edge.GetVertex(0).Coordinate(0),
                                         edge.GetVertex(0).Coordinate(1),
                                         edge.GetVertex(1).Coordinate(0),
                                         edge.GetVertex(1).Coordinate(1),
                                         edge.GetDirection(),
                                         edge.GetWeight(),
                                         edgeColor);
                    });
            });
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    template<class id_type>
    void
    Outputter<id_type>::DrawVertices(
            const typename Outputter<id_type>::graph_type& graph)
    {
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
                                   stringId,
                                   drawer_.GetPalette().primaryColor_);
            });
    }

} //    namespace output



#endif // GRAPH_LIB_DISPLAY_OUTPUTTER_HPP
//==============================================================================
// End of outputter.hpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
