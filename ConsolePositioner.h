#ifndef CONSOLE_POSITIONER_H_DEFIEND
#define CONSOLE_POSITIONER_H_DEFIEND

#include <string>
using std::string;

class CConsolePositioner
{
    public:
        CConsolePositioner();
        virtual ~CConsolePositioner();

        void     PositionConsolesFromFile(string filename);

    private:
        void     PositionConsole(unsigned int consoleID, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

};

#endif
