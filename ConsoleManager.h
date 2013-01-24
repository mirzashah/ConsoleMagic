/*****************************************************************************/
// Filename: ConsoleManager.h
/*****************************************************************************/
// Description: This class manages all Console instances. This class is hidden
// from the end user.
/*****************************************************************************/

#ifndef CONSOLE_MAGIC_CONSOLE_MANAGER_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_MANAGER_H_DEFINED

#include <ConsoleManagerWindow.h>
#include <vector>
#include <map>
using std::vector;
using std::map;

namespace ConsoleMagic
{

class CConsole;

typedef map<unsigned int, CConsole*> ConsoleMapType;
typedef map<unsigned int, Gtk::Window*> GtkWindowMapType;

class CConsoleManager : public CConsoleManagerWindow
{
    friend class CConsoleMagicApp;

    public:

        virtual ~CConsoleManager();


        static CConsole&                    Console(unsigned int consoleID);
        static CConsoleManager&             Instance();
        void                                SetConsoleLayoutFileName(std::string sFilename) {_sFilename=sFilename;};
        void                                PositionConsolesFromFile();


    private:
        CConsoleManager();
        void                                AddConsole(unsigned int consoleID, CConsole* console);
        void                                AddGtkWindow(unsigned int gtkWindowID, Gtk::Window* gtkWindow);
        ConsoleMapType&                     ConsoleMap();
        GtkWindowMapType&                   GtkWindowMap();
        virtual void                        OnActionSaveLayout();
        virtual void                        OnActionRestoreLayout();
        virtual void                        OnActionHideAllWindows();
        virtual void                        OnActionShowAllWindows();
        void                                OnHideAllWindows();
        void                                OnShowAllWindows();

        void                                PositionConsole(Glib::ustring type, unsigned int consoleID, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        void                                SaveConsolesPositionsToFile();

    private:
        ConsoleMapType                      _consoleMap;
        GtkWindowMapType                    _gtkWindowMap;
        static CConsoleManager*             _instance;

        Glib::ustring                       _sFilename;

};

};

#endif
