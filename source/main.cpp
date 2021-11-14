﻿
#include <iostream>
#include <string>
#include "Repl.h"
#include "LanguageServer.h"

#include "Windows.h"
#include "debugapi.h"

struct
{
    bool help;
    bool debug;
} options = {};

void printHelp()
{
    std::cout << 
        "usage: kuku [mode] [options]\n"
        "\n"

        "modes:\n"
        "  repl        : run read-eval-print loop\n"
        "  lang-server : run language server\n"
        "\n"

        "options:\n"
        "  -h | --help  : print help message\n"
        "  -d | --debug : wait debugger attach before start\n"
        "\n";
}

#include "json.h"

#include "Position.h"
#include "Range.h"

int main(int argc, const char* argv[])
{
    std::string mode{ "repl" }; // default mode

    for (int i = 1; i < argc; i++)
    {
        std::string arg{ argv[i] };
        if (arg[0] == '-') // option
        {
            if (arg == "-h" || arg == "--help")
                options.help = true;

            if (arg == "-d" || arg == "--debug")
                options.debug = true;
        }
        else // mode
        {
            mode = arg;
        }
    }

    if (options.debug)
    {
        while (!IsDebuggerPresent()) Sleep(100);
    }

    if (options.help)
    {
        printHelp();
    }

    std::string command{ argc > 1 ? argv[1] : "repl" };

    if (mode == "repl")
    {
        Repl();
    }
    else if (mode == "lang-server")
    {
        language_server{};
    }
    else
    {
        std::cout << "unknown mode: " << mode << std::endl;
        if (!options.help)
        {
            printHelp();
        }
    }

    return 0;
}
