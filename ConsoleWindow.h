/*****************************************************************************/
// Filename: ConsoleWindow.h
/*****************************************************************************/
// Console Window Base Class for widgets
/*****************************************************************************/

#ifndef CONSOLE_MAGIC_CONSOLE_WINDOW_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_WINDOW_H_DEFINED

#include <gtkmm.h>

namespace ConsoleMagic
{

class CConsoleWindow : public Gtk::Window
{
    public:
        CConsoleWindow();
        virtual ~CConsoleWindow();

        void                                SetConsoleIcon(Glib::ustring filename);

    private:
        // Private Class Operations
        void                                AddMenuToUIManager();
        void                                AddWidgetsToWindow();
        void                                CreateActionsAndSignalHandlers();
        void                                CreateUIManager();
        void                                DefineXMLMenuToolBarContent();
        void                                InitializeWidgetsProperties();
        void                                InitializeWindowProperties();
        void                                InstantiateMenuBar();
        void                                OnActionClear();
        void                                OnActionToggleTextWrap();
        void                                OnActionToggleScrollBars();

    protected:
        // ConsoleWindow Widgets Accessors
        Gtk::ScrolledWindow&                ConsoleScrolledWindow()     {return _scrolledWindow;};
        Glib::RefPtr<Gtk::TextBuffer>       ConsoleTextBuffer()         {return _textBuffer;};
        Gtk::TextView&                      ConsoleTextView()           {return _textView;};
        Gtk::VBox&                          ConsoleVBox()               {return _vBox;};

        Glib::RefPtr<Gtk::ActionGroup>&     ConsoleActionGroup()        {return _actionGroup;};
        Gtk::Widget&                        ConsoleMenuBar()            {return *_menuBar;};
        Glib::RefPtr<Gtk::UIManager>&       ConsoleUIManager()          {return _uiManager;};
        Glib::ustring&                      ConsoleUIXMLInfo()          {return _uiXMLInfo;};

    private:
        // ConsoleWindow Widgets Variables
        Gtk::ScrolledWindow                 _scrolledWindow;
        Gtk::TextView                       _textView;
        Glib::RefPtr<Gtk::TextBuffer>       _textBuffer;
        Gtk::VBox                           _vBox;

        Glib::RefPtr<Gtk::ActionGroup>      _actionGroup;
        Gtk::Widget*                        _menuBar;
        Glib::RefPtr<Gtk::UIManager>        _uiManager;
        Glib::ustring                       _uiXMLInfo;
};

};

#endif
