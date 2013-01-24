#include <ConsoleManagerWindow.h>
#include <ConsolePositioner.h>
#include <sstream>
using std::ostringstream;
#include <iostream>

namespace ConsoleMagic
{

/******************************************************************************************************************/
CConsoleManagerWindow::CConsoleManagerWindow():_menuBar(NULL), _toolBar(NULL), _consolePauseButtonPressedFlag(false)
/******************************************************************************************************************/
{
    InitializeWindowProperties();
    CreateActionsAndSignalHandlers();
    CreateUIManager();
    DefineXMLMenuToolBarContent();
    AddMenuToUIManager();
    InstantiateMenuAndToolBar();
    AddWidgetsToWindow();
    InitializeWidgetsProperties();
    show_all_children();
}

/*********************************************/
CConsoleManagerWindow::~CConsoleManagerWindow()
/*********************************************/
{
    delete _menuBar;
    delete _toolBar;
}

/**********************************************/
void CConsoleManagerWindow::AddMenuToUIManager()
/**********************************************/
{
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
        try
        {
            ConsoleUIManager()->add_ui_from_string(ConsoleUIXMLInfo());
        }
        catch(const Glib::Error& ex)
        {
            std::cerr << "building menus failed: " << ex.what();
        }
    #else
        std::auto_ptr<Glib::Error> ex;
         ConsoleUIManager()->add_ui_from_string(ConsoleUIXMLInfo(), ex);
        if(ex.get())
        {
            std::cerr << "building menus failed: " << ex->what();
        }
    #endif //GLIBMM_EXCEPTIONS_ENABLED
}

/**********************************************/
void CConsoleManagerWindow::AddWidgetsToWindow()
/**********************************************/
{
    add(ConsoleVBox());
    //ConsoleVBox().pack_start(ConsoleMenuBar(), Gtk::PACK_SHRINK);
    ConsoleVBox().pack_start(ConsoleToolBar(), Gtk::PACK_SHRINK);
}

/*****************************************************/
void CConsoleManagerWindow::InstantiateMenuAndToolBar()
/*****************************************************/
{
   _menuBar = ConsoleUIManager()->get_widget("/MenuBar");
   _toolBar = ConsoleUIManager()->get_widget("/ToolBar");
}

/**********************************************************/
void CConsoleManagerWindow::CreateActionsAndSignalHandlers()
/**********************************************************/
{
    // Creat action group
    ConsoleActionGroup() = Gtk::ActionGroup::create();

    // Create and add Actions to group for Menus, Submenus, and Toolbars
    ConsoleActionGroup()->add(Gtk::Action::create("MenuFile", "_File"));
    ConsoleActionGroup()->add( Gtk::Action::create("SaveLayout", Gtk::Stock::SAVE_AS),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionSaveLayout) );
    ConsoleActionGroup()->add( Gtk::Action::create("RestoreLayout", Gtk::Stock::SAVE),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionRestoreLayout) );
    ConsoleActionGroup()->add( Gtk::Action::create("ShowAllWindows", Gtk::Stock::FULLSCREEN),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionShowAllWindows) );
    ConsoleActionGroup()->add( Gtk::Action::create("HideAllWindows", Gtk::Stock::CLOSE),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionHideAllWindows) );
    ConsoleActionGroup()->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionQuit) );
    ConsoleActionGroup()->add( Gtk::ToggleAction::create("Pause", Gtk::Stock::MEDIA_PAUSE),
        sigc::mem_fun(*this, &CConsoleManagerWindow::OnActionPause) );

    //this->signal_drag_begin().connect(sigc::mem_fun(*this, &CConsoleManagerWindow::OnDragBegin));
}

/*******************************************/
void CConsoleManagerWindow::CreateUIManager()
/*******************************************/
{
    // Create UIManager and add action group
    ConsoleUIManager() = Gtk::UIManager::create();
    ConsoleUIManager()->insert_action_group(ConsoleActionGroup());

    // Enable response to specified keyboard shortcuts
    add_accel_group(ConsoleUIManager()->get_accel_group());
}

/*******************************************************/
void CConsoleManagerWindow::DefineXMLMenuToolBarContent()
/*******************************************************/
{
    // Define Visible Menu and Tool Bar Layout
    ConsoleUIXMLInfo() =
        "<ui>"
        "   <menubar name='MenuBar'>"
        "       <menu action='MenuFile'>"
        "           <menuitem action='SaveLayout'/>"
        "           <menuitem action='Quit'/>"
        "       </menu>"
        "   </menubar>"
        "   <toolbar name='ToolBar'>"
        "       <toolitem action='SaveLayout'/>"
        "       <toolitem action='RestoreLayout'/>"
        "       <toolitem action='ShowAllWindows'/>"
        "       <toolitem action='HideAllWindows'/>"
        "       <toolitem action='Pause'/>"
        "       <toolitem action='Quit'/>"
        "   </toolbar>"
        "</ui>";
}

/*******************************************************/
void CConsoleManagerWindow::InitializeWidgetsProperties()
/*******************************************************/
{
    Gtk::ToolButton& saveLayoutButtonHandle = *dynamic_cast<Gtk::ToolButton*>(ConsoleUIManager()->get_widget("/ToolBar/SaveLayout"));
    saveLayoutButtonHandle.set_label("Save");
    Gtk::ToolButton& restoreLayoutButtonHandle = *dynamic_cast<Gtk::ToolButton*>(ConsoleUIManager()->get_widget("/ToolBar/RestoreLayout"));
    restoreLayoutButtonHandle.set_label("Restore");
    Gtk::ToolButton& showAllWindowsButtonHandle = *dynamic_cast<Gtk::ToolButton*>(ConsoleUIManager()->get_widget("/ToolBar/ShowAllWindows"));
    showAllWindowsButtonHandle.set_label("Show All");
    Gtk::ToolButton& hideAllWindowsButtonHandle = *dynamic_cast<Gtk::ToolButton*>(ConsoleUIManager()->get_widget("/ToolBar/HideAllWindows"));
    hideAllWindowsButtonHandle.set_label("Hide All");
}

/******************************************************/
void CConsoleManagerWindow::InitializeWindowProperties()
/******************************************************/
{
    set_title("Console Manager");
    set_border_width(0);
    set_default_size(382,48);
    //set_size_request(322, 45);
}

/*****************************************/
void CConsoleManagerWindow::OnActionPause()
/*****************************************/
{
    Gtk::ToolButton& toolButtonHandle = *dynamic_cast<Gtk::ToolButton*>(ConsoleUIManager()->get_widget("/ToolBar/Pause"));

    if (toolButtonHandle.get_stock_id() == Gtk::Stock::MEDIA_PLAY.id)
    {
        toolButtonHandle.set_stock_id(Gtk::Stock::MEDIA_PAUSE);
        toolButtonHandle.set_label("Pause");
        SetConsolePauseButtonPressedFlag(false);
    }
    else
    {
        toolButtonHandle.set_stock_id(Gtk::Stock::MEDIA_PLAY);
        toolButtonHandle.set_label("Play");
        SetConsolePauseButtonPressedFlag(true);
    }
}
/****************************************/
void CConsoleManagerWindow::OnActionQuit()
/****************************************/
{
    Gtk::Main::quit();
}

/**********************************************/
void CConsoleManagerWindow::OnActionSaveLayout()
/**********************************************/
{
}

/*************************************************/
void CConsoleManagerWindow::OnActionRestoreLayout()
/*************************************************/
{
}

/**************************************************/
void CConsoleManagerWindow::OnActionHideAllWindows()
/**************************************************/
{
}

/**************************************************/
void CConsoleManagerWindow::OnActionShowAllWindows()
/**************************************************/
{
}

/**********************************************************************************************/
void CConsoleManagerWindow::SetConsolePauseButtonPressedFlag(bool consolePauseButtonPressedFlag)
/**********************************************************************************************/
{
    _consolePauseButtonPressedFlag = consolePauseButtonPressedFlag;
}

/*********************************************************************/
void CConsoleManagerWindow::SetConsoleManagerTitle(Glib::ustring title)
/*********************************************************************/
{
    set_title(title);
}

/*********************************************************************/
void CConsoleManagerWindow::SetConsoleManagerIcon(std::string filename)
/**********************************************************************/
{
    set_icon_from_file(filename);
}


};
