/*****************************************************************************/
// Filename: ConsoleManagerWindow.h
/*****************************************************************************/
// Description: Console Manager Window Base Class for widgets
/*****************************************************************************/

#ifndef CONSOLE_MAGIC_CONSOLE_MANAGER_WINDOW_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_MANAGER_WINDOW_H_DEFINED

#include <vector>
#include <map>
#include <gtkmm.h>
using std::vector;
using std::map;

namespace ConsoleMagic
{

class CConsoleManagerWindow : public Gtk::Window
{
    public:
        CConsoleManagerWindow();
        virtual ~CConsoleManagerWindow();


        bool                                IsConsolePauseButtonPressed() {return _consolePauseButtonPressedFlag;};
        void                                SetConsoleManagerTitle(Glib::ustring title);
        void                                SetConsoleManagerIcon(std::string filename);

    protected:
        void                                OnActionPause();
        void                                OnActionQuit();
        virtual void                        OnActionSaveLayout();
        virtual void                        OnActionRestoreLayout();
        virtual void                        OnActionHideAllWindows();
        virtual void                        OnActionShowAllWindows();

    private:
        void                                AddWidgetsToWindow();
        void                                AddMenuToUIManager();
        void                                CreateUIManager();
        void                                CreateActionsAndSignalHandlers();
        void                                DefineXMLMenuToolBarContent();
        void                                InitializeWidgetsProperties();
        void                                InitializeWindowProperties();
        void                                InstantiateMenuAndToolBar();
        void                                SetConsolePauseButtonPressedFlag(bool consolePauseButtonPressedFlag);

    private:
        // Console Widgets Accessors
        Glib::RefPtr<Gtk::ActionGroup>&     ConsoleActionGroup()        {return _actionGroup;};
        Gtk::Widget&                        ConsoleMenuBar()            {return *_menuBar;};
        Gtk::Widget&                        ConsoleToolBar()            {return *_toolBar;};
        Glib::RefPtr<Gtk::UIManager>&       ConsoleUIManager()          {return _uiManager;};
        Glib::ustring&                      ConsoleUIXMLInfo()          {return _uiXMLInfo;};
        Gtk::VBox&                          ConsoleVBox()               {return _vBox;};

        // Console Widgets Variables
        Glib::RefPtr<Gtk::ActionGroup>      _actionGroup;
        Gtk::Widget*                        _menuBar;
        Gtk::Widget*                        _toolBar;
        Glib::RefPtr<Gtk::UIManager>        _uiManager;
        Glib::ustring                       _uiXMLInfo;
        Gtk::VBox                           _vBox;
        bool                                _consolePauseButtonPressedFlag;
};

};

#endif
