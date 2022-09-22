//==============================================================================
///
/// @file template.h
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
#ifndef TEMPLATE_H
#define TEMPLATE_H


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <string>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "fetcher.h"            // Fetcher


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
/// @brief Object accepting commands as input and executing them.
///
//------------------------------------------------------------------------------
class Runner
{
public:

    //------------------------------------------------------------------------------
    ///
    /// @brief Default constructor.
    ///
    //------------------------------------------------------------------------------
    Runner();

    //------------------------------------------------------------------------------
    ///
    /// @brief Starts a loop processing input commands.
    ///
    /// Available commands (each on a separate line, arguments delimeted by space):
    /// - Graph traversal:
    ///     - dfs [graph file] [root vertex]
    ///     - bfs [graph file] [root vertex]
    /// - Graph flow:
    ///     - edmonds [graph file] [source vertex] [sink vertex]
    ///     - dinic [graph file] [source vertex] [sink vertex]
    /// - Control:
    ///     - quit
    ///
    //------------------------------------------------------------------------------
    void
    execute();


private:

    //------------------------------------------------------------------------------
    ///
    /// @brief Parse individual input command.
    ///
    /// @param[in] input Input command string.
    ///
    /// @retval True If command didn't fail.
    /// @retval False Otherwise.
    ///
    //------------------------------------------------------------------------------
    bool
    parse_command(std::string input);

    //------------------------------------------------------------------------------
    ///
    /// @brief Execute graph traversal input command.
    ///
    /// @param[in] command Either "quit" command or graph algorithm.
    ///
    /// @param[in] graphFile Input graph file.
    ///
    /// @param[in] arg1 First algorithm argument.
    ///
    /// @param[in] arg2 Second algorithm argument.
    ///
    /// @retval True If command didn't fail.
    /// @retval False Otherwise.
    ///
    //------------------------------------------------------------------------------
    bool
    execute_command(std::string command,
                    std::string graphFile,
                    std::string arg1,
                    std::string arg2);


private:

    /// @brief Fetcher object constructing graph.
    Fetcher fetcher_;
};


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------



//
#endif // TEMPLATE_H
//==============================================================================
// End of template.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
