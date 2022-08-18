#ifndef GRAPH_DISPLAY_MANAGER_OUTPUTTER_MANAGER
#define GRAPH_DISPLAY_MANAGER_OUTPUTTER_MANAGER





// std
#include <vector>
// related
#include "graph-display/manager/output-instance.hpp"
#include "graph-display/manager/drawer/positioner.hpp"
#include "graph-display/manager/drawer/drawer.hpp"





// forward declaration
namespace graph
{
    template<   typename    id_type>
    class Graph;
}





//! output
/*!
 * Namespace containing all structures used to display graph.
 */
namespace output
{
    //! OutputterManager
    /*!
     * Class which manages graph display process. It contains:
     *  - all graphs OutputInstances to be shown on screen
     *  - drawer to display instances on the screen
     *  - positioner, which manages instance coordinates
     */
    template< typename id_type>
    class OutputterManager
    {
        using graph_type            = graph::Graph<id_type>;
        using instance_container    = std::vector<OutputInstance<id_type>>;
        using positioner_type       = Positioner;
        using drawer_type           = Drawer<id_type>;
        
    public:

        //! Value constructor
        /*!
         * Constructs an instance having window of input dimensions.
            \param int
            \param int
         */
                                    OutputterManager(   int width = 1000, 
                                                        int height = 600);

        //! Register
        /*!
         * Stores graph's OutputInstance into the container.
            \param const graph_type&
         */
        void                        Register(   const graph_type&);

        //! Instances
        /*!
         * OutputInstance container getter.
            \return const instance_container&
         */
        const instance_container&   Instances() const;

        //! Display
        /*!
         * Displays all OutputInstances.
         */
        void                        Display();
    


    private:

        //! width
        /*!
         * Display window width.
         */
        int                 width_; 
        
        //! height
        /*!
         * Display window height.
         */
        int                 height_;

        //! instances
        /*!
         * Graph OutputInstances container.
         */
        instance_container  instances_;

        //! window
        /*!
         * SFML window.
         */
        sf::RenderWindow    window_;

        //! positioner
        /*!
         * Component calculating coordinates for stored OutputInstance objects.
         */
        positioner_type     positioner_;

        //! drawer
        /*!
         * Drawer object used to display registered OutputInstance objects.
         */
        drawer_type         drawer_;
        
    };

} //    namespace output










//
//  Definition
//
namespace output
{
    // Construction
    template< typename id_type>
    OutputterManager<id_type>::OutputterManager(    int width, 
                                                    int height) :   
                                                                    width_(width), 
                                                                    height_(height),
                                                                    window_(sf::VideoMode(width_, height_), "Outputter"),
                                                                    drawer_(),
                                                                    positioner_(width_, height_),
                                                                    instances_()
    {   }



    // Register an instance
    template<   typename    id_type>
    void    OutputterManager<id_type>::Register(    const typename OutputterManager<id_type>::graph_type&   inGraph)
    {
        instances_.emplace_back( &window_, inGraph, width_, height_);
    }



    // Provide access to instance container
    template<   typename    id_type>
    const typename OutputterManager<id_type>::instance_container&   OutputterManager<id_type>::Instances() const
    {
        return instances_;
    }



    // Display instances
    template< typename id_type>
    void            OutputterManager<id_type>::Display()
    {
        // draw all graphs
        for(auto iter = instances_.begin(); iter != instances_.end(); ++iter)
        {
            // update coordinates for instance's graph
            iter->UpdateCoordinates( positioner_.Compute(iter->Graph().Size()));

            drawer_.DrawInstance(*iter);
        }
        
    }

} //    namespace output



#endif //GRAPH_DISPLAY_OUTPUTTER_MANAGER