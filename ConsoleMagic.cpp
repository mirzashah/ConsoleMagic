#include <ConsoleMagic.h>
#include <ConsoleManager.h>

namespace ConsoleMagic
{

/***************************************/
CConsole& Console(unsigned int consoleID)
/***************************************/
{
    return(CConsoleManager::Console(consoleID));
}

/**********************************************/
void SetConsoleManagerTitle(Glib::ustring title)
/**********************************************/
{
    CConsoleManager::Instance().SetConsoleManagerTitle(title);
}

/**********************************************/
void SetConsoleManagerIcon(Glib::ustring filename)
/**********************************************/
{
    CConsoleManager::Instance().SetConsoleManagerIcon(filename);
}

};
