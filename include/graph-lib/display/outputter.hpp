#ifndef GRAPH_DISPLAY_OUTPUTTER
#define GRAPH_DISPLAY_OUTPUTTER





// related
#include "graph-display/manager/outputter-manager.hpp"      // outputter implementation





// Forward declarations
namespace graph
{
    template<   typename    id_type>
    class Graph;
} //    namespace graph






//! output
/*!
 * Namespace containing all structures used to display graph.
 */
namespace output
{
    //! Outputter
    /*!
     * Displays graphs.
     */
    template< typename id_type>
    class Outputter
    {

        using graph_type    = graph::Graph<id_type>;
        using manager_type  = OutputterManager<id_type>;

    public:

        //! Default constructor
        /*!
         * Construct an empty Outputter instance.
         */
                        Outputter();

        //! operator <<
        /*!
         * Registers graph instance, so that it can be drawn on screen.
            \param const graph_type&
            \return Outputter&
         */
        Outputter&      operator<<(const graph_type&);

        //! operator <<
        /*!
         * Displays on screen all registered graph instances.
         */
        void            Show();



    private:

        //! manager
        /*!
         * Component implementing Outputters functionality.
         */
        manager_type   manager_;
    };

} //    namespace output










//
// Definition
//
namespace output
{
    //
    template< typename id_type>
    Outputter<id_type>::Outputter() : manager_()
    {   }



    //
    template<   typename    id_type>
    Outputter<id_type>&      Outputter<id_type>::operator<<(const typename Outputter<id_type>::graph_type& inGraph)
    {
        manager_.Register(inGraph);

        return *this;
    }



    //
    template< typename id_type>
    void    Outputter<id_type>::Show()
    {
        manager_.Display();
    }

} //    namespace output



#endif //GRAPH_DISPLAY_OUTPUTTER