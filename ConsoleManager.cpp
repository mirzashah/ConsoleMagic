#include <ConsoleManager.h>
#include <Console.h>
#include <sstream>
using std::ostringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

namespace ConsoleMagic
{

/*************************************************/
CConsoleManager* CConsoleManager::_instance = NULL;
/*************************************************/


/********************************/
CConsoleManager::CConsoleManager()
/********************************/
{
    _sFilename = "ConsoleMagicLayout.txt";
}

/*********************************/
CConsoleManager::~CConsoleManager()
/*********************************/
{
    ConsoleMapType::iterator itr;
    for(itr = ConsoleMap().begin(); itr != ConsoleMap().end(); itr++)
        delete itr->second;

    GtkWindowMapType::iterator itr2;
    for(itr2 = GtkWindowMap().begin(); itr2 != GtkWindowMap().end(); itr2++)
        delete itr2->second;
}

/*************************************************************************/
void CConsoleManager::AddConsole(unsigned int consoleID, CConsole* console)
/*************************************************************************/
{
    if(ConsoleMap()[consoleID] != NULL)
        delete(ConsoleMap()[consoleID]);

    ConsoleMap()[consoleID] = console;
}

/**********************************************************************************/
void CConsoleManager::AddGtkWindow(unsigned int gtkWindowID, Gtk::Window* gtkWindow)
/**********************************************************************************/
{
    if(GtkWindowMap()[gtkWindowID] != NULL)
        delete(GtkWindowMap()[gtkWindowID]);

    GtkWindowMap()[gtkWindowID] = gtkWindow;
}

/********************************************************/
CConsole& CConsoleManager::Console(unsigned int consoleID)
/********************************************************/
{
    if(Instance().ConsoleMap()[consoleID] == NULL)
    {
        CConsole* newConsole = CConsole::Create();
        newConsole->SetConsoleID(consoleID);
        Instance().AddConsole(consoleID, newConsole);
    }
    CConsole& toReturn = (*(Instance().ConsoleMap()[consoleID]));
    toReturn.show(); //Note: Even if the window was closed, accessing it again will automatically pop it up again.
    return(toReturn);
}

/*******************************************/
ConsoleMapType& CConsoleManager::ConsoleMap()
/*******************************************/
{
    return(_consoleMap);
}

/***********************************************/
GtkWindowMapType& CConsoleManager::GtkWindowMap()
/***********************************************/
{
    return(_gtkWindowMap);
}

/******************************************/
CConsoleManager& CConsoleManager::Instance()
/******************************************/
{
    if(_instance==NULL)
    {
        _instance = new CConsoleManager();
        _instance->show();
    }
    return(*_instance);
}

/****************************************/
void CConsoleManager::OnActionSaveLayout()
/****************************************/
{
    SaveConsolesPositionsToFile();
}

/*******************************************/
void CConsoleManager::OnActionRestoreLayout()
/*******************************************/
{
    PositionConsolesFromFile();
}

/**************************************/
void CConsoleManager::OnHideAllWindows()
/**************************************/
{
    for(ConsoleMapType::iterator itr = ConsoleMap().begin(); itr != ConsoleMap().end(); itr++)
        itr->second->iconify();
    for (GtkWindowMapType::iterator itr = GtkWindowMap().begin(); itr != GtkWindowMap().end(); itr++)
    {
        if(itr->second != NULL)
            itr->second->iconify();
    }
}

/**************************************/
void CConsoleManager::OnShowAllWindows()
/**************************************/
{
    for(ConsoleMapType::iterator itr = ConsoleMap().begin(); itr != ConsoleMap().end(); itr++)
    {
        if (itr->second->is_visible())
            itr->second->present();
    }
    for (GtkWindowMapType::iterator itr = GtkWindowMap().begin(); itr != GtkWindowMap().end(); itr++)
    {
        if (itr->second != NULL)
        {
            if (itr->second->is_visible())
                itr->second->present();
        }
    }
}

/********************************************/
void CConsoleManager::OnActionHideAllWindows()
/********************************************/
{
    OnHideAllWindows();
}

/********************************************/
void CConsoleManager::OnActionShowAllWindows()
/********************************************/
{
    OnShowAllWindows();
}

/************************************************************************************************************************************/
void CConsoleManager::PositionConsole(Glib::ustring type, unsigned int consoleID, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
/************************************************************************************************************************************/
{
    if (type == "Console")
    {
        Console(consoleID).resize(width, height);
        Console(consoleID).move(x,y);
    }
    else if (type == "GtkWindow" && GtkWindowMap()[consoleID]!=NULL)
    {
        GtkWindowMap()[consoleID]->move(x,y);
        GtkWindowMap()[consoleID]->resize(width, height);
    }
}

/**********************************************/
void CConsoleManager::PositionConsolesFromFile()
/**********************************************/
{
    ifstream consolePositionFile;
    consolePositionFile.open(_sFilename.c_str());
    if(consolePositionFile)
    {
        // Get Column Headers and Get Console Manager Info
        Glib::ustring garbage;
        unsigned int x, y, width, height;
        consolePositionFile>>garbage>>garbage>>garbage>>garbage>>garbage>>garbage;
        consolePositionFile>>garbage>>garbage>>x>>y>>width>>height;
        move(x,y);
        resize(width,height);

        while(consolePositionFile)
        {
            Glib::ustring type;
            unsigned int consoleID, x, y, width, height;
            consolePositionFile>>type>>consoleID>>x>>y>>width>>height;
            PositionConsole(type,consoleID, x, y, width, height);
        }
    }
    consolePositionFile.close();
}

/*************************************************/
void CConsoleManager::SaveConsolesPositionsToFile()
/*************************************************/
{
    ofstream consolePositionFile;
    consolePositionFile.open(_sFilename.c_str());

    if(consolePositionFile)
    {
        // Set Column Headers and set Console Manager Info
        int consoleID, x, y, width, height;
        get_position(x,y);
        get_size(width, height);
        consolePositionFile<<"Type" << " " <<"consoleID "<<"x  "<<"y  "<<"width  "<<"height"<<endl;
        consolePositionFile<<"Main" <<" "<<"Main " <<" "<<x<<" "<<y<<" "<<width<<" "<<height<<endl;


        for (GtkWindowMapType::iterator iter = GtkWindowMap().begin(); iter != GtkWindowMap().end(); iter++)
        {
            // Make sure the window isn't minimized
            if (iter->second != NULL)
            {
                if (iter->second->is_visible())
                {
                    iter->second->present();
                    int consoleID, x, y, width, height;
                    consoleID = iter->first;
                    iter->second->get_position(x,y);
                    iter->second->get_size(width, height);
                    consolePositionFile<<"GtkWindow" << " "<<consoleID <<" "<<x<<" "<<y<<" "<<width<<" "<<height<<endl;
                }
            }
        }

        for (ConsoleMapType::iterator iter = ConsoleMap().begin(); iter != ConsoleMap().end(); iter++)
        {
            // Make sure the window isn't minimized
            if (iter->second->is_visible())
            {
                iter->second->present();
                int consoleID, x, y, width, height;
                consoleID = iter->first;
                iter->second->get_position(x,y);
                iter->second->get_size(width, height);
                consolePositionFile<<"Console" << " "<<consoleID <<" "<<x<<" "<<y<<" "<<width<<" "<<height<<endl;
            }
        }
    }
    consolePositionFile.close();
}

}; // End Namespace
