#include <ConsolePositioner.h>
#include <ConsoleMagic.h>
#include <fstream>
using std::ifstream;

/************************************************/
CConsolePositioner::CConsolePositioner()
/************************************************/
{
}

/************************************************/
CConsolePositioner::~CConsolePositioner()
/************************************************/
{
}

/************************************************/
void CConsolePositioner::PositionConsole(unsigned int consoleID, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
/************************************************/
{
    ConsoleMagic::Console(consoleID).move(x,y);
    ConsoleMagic::Console(consoleID).resize(width, height);
}

/************************************************/
void CConsolePositioner::PositionConsolesFromFile(string filename)
/************************************************/
{
    ifstream consolePositionFile;
    consolePositionFile.open(filename.c_str());
    if(consolePositionFile)
    {
        string garbage;
        consolePositionFile>>garbage>>garbage>>garbage>>garbage>>garbage;
        while(consolePositionFile)
        {
            unsigned int consoleID, x, y, width, height;
            consolePositionFile>>consoleID>>x>>y>>width>>height;
            PositionConsole(consoleID, x, y, width, height);
        }
    }
}
