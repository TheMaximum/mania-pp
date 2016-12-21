#ifndef LOGGING_H_
#define LOGGING_H_

#include <cmath>
#include "../GbxRemote/GbxStructs.h"

//* Logging
/**
 * \brief Utility to print information to the console.
 */
class Logging
{
public:
    /*!
     * \brief Prints error to console.
     *
     * \param error        Error structure.
     */
    static void PrintError(GbxError* error)
    {
        std::stringstream numberString;
        numberString << error->number;
        const char* errorNumber = numberString.str().c_str();
        int errorNumberLength = strlen(errorNumber);
        int spaces = (9 - errorNumberLength);

        if(spaces > 1)
        {
            double halfSpaces = (spaces / 2);

            std::stringstream output;
            output << "[\033[0;31m";
            for(int i = 0; i < ceil(halfSpaces); i++)
            {
                output << " ";
            }
            output << error->number;
            for(int i = 0; i < floor(halfSpaces); i++)
            {
                output << " ";
            }

            output << "\033[0;0m] ERROR: " + error->message;

            std::cout << output.str() << std::endl;
        }
        else
        {
            std::cout << "[\033[0;31m" << errorNumber << "\033[0;0m] ERROR: " << error->message << std::endl;
        }
    }

    /*!
     * \brief Prints OK. in [         ]-spaces in console.
     */
    static void PrintOKFlush()
    {
        std::cout << "[   \033[0;32mOK.\033[0;0m" << std::endl;
    }

    /*!
     * \brief Prints Failed! in [         ]-spaces in console.
     */
    static void PrintFailedFlush()
    {
        std::cout << "[ \033[0;31mFAILED!\033[0;0m" << std::endl;
    }
};

#endif // LOGGING_H_