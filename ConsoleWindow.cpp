#include <ConsoleWindow.h>
#include <iostream>

namespace ConsoleMagic
{
/**************************************************/
    CConsoleWindow::CConsoleWindow(): _menuBar(NULL)
/**************************************************/
{
    _textBuffer = Gtk::TextBuffer::create();
    InitializeWindowProperties();
    CreateActionsAndSignalHandlers();
    CreateUIManager();
    DefineXMLMenuToolBarContent();
    AddMenuToUIManager();
    InstantiateMenuBar();

    AddWidgetsToWindow();
    InitializeWidgetsProperties();
    show_all_children();
}

/*******************************/
CConsoleWindow::~CConsoleWindow()
/*******************************/
{
    delete _menuBar;
}

/***************************************/
void CConsoleWindow::AddMenuToUIManager()
/***************************************/
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

/***************************************/
void CConsoleWindow::AddWidgetsToWindow()
/***************************************/
{
    add(ConsoleVBox());
    ConsoleVBox().pack_start(ConsoleMenuBar(), Gtk::PACK_SHRINK);

    //Add the TextView, inside a ScrolledWindow, with the button underneath:
    ConsoleScrolledWindow().add(_textView);
    //Pack scrolled window into first vertical box space
    ConsoleVBox().pack_start(_scrolledWindow, Gtk::PACK_EXPAND_WIDGET);
}

/***************************************************/
void CConsoleWindow::CreateActionsAndSignalHandlers()
/***************************************************/
{
    // Creat action group
    ConsoleActionGroup() = Gtk::ActionGroup::create();

    // Create and add Actions to group for Menus, Submenus, and Toolbars
    ConsoleActionGroup()->add(Gtk::Action::create("MenuActions", "Actions"));
    ConsoleActionGroup()->add( Gtk::Action::create("Clear", Gtk::Stock::CLEAR),
        sigc::mem_fun(*this, &CConsoleWindow::OnActionClear) );
    ConsoleActionGroup()->add(Gtk::Action::create("MenuOptions", "Options"));
    ConsoleActionGroup()->add( Gtk::ToggleAction::create("ToggleTextWrap", "Wrap Text"),
        sigc::mem_fun(*this, &CConsoleWindow::OnActionToggleTextWrap) );
   // ConsoleActionGroup()->add( Gtk::ToggleAction::create("ToggleScrollBars", "Scroll Bars"),
    //    sigc::mem_fun(*this, &CConsoleWindow::OnActionToggleScrollBars) );
}

/************************************/
void CConsoleWindow::CreateUIManager()
/************************************/
{
    // Create UIManager and add action group
    ConsoleUIManager() = Gtk::UIManager::create();
    ConsoleUIManager()->insert_action_group(ConsoleActionGroup());

    // Enable response to specified keyboard shortcuts
    add_accel_group(ConsoleUIManager()->get_accel_group());
}

/************************************************/
void CConsoleWindow::DefineXMLMenuToolBarContent()
/************************************************/
{
    // Define Visible Menu and Tool Bar Layout
    ConsoleUIXMLInfo() =
        "<ui>"
        "   <menubar name='MenuBar'>"
        "       <menu action='MenuActions'>"
        "           <menuitem action='Clear'/>"
        "       </menu>"
        "       <menu action='MenuOptions'>"
        "           <menuitem action='ToggleTextWrap'/>"
       // "           <menuitem action='ToggleScrollBars'/>"
        "       </menu>"
        "   </menubar>"
        "</ui>";
}

/************************************************/
void CConsoleWindow::InitializeWidgetsProperties()
/************************************************/
{
    // Set Vertical Box Spacing
    ConsoleVBox().set_spacing(4);

    ConsoleScrolledWindow().set_shadow_type(Gtk::SHADOW_ETCHED_IN);
    // ConsoleWindow text view properties
    ConsoleTextView().set_editable(false);
    ConsoleTextView().set_cursor_visible(true);

    ConsoleScrolledWindow().set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);


   // Gtk::CheckMenuItem& toggleScrollMenuItemHandle = *dynamic_cast<Gtk::CheckMenuItem*>(ConsoleUIManager()->get_widget("/MenuBar/MenuOptions/ToggleScrollBars"));
   // toggleScrollMenuItemHandle.set_active(true);

    Gtk::CheckMenuItem& toggleTextWrapMenuItemHandle = *dynamic_cast<Gtk::CheckMenuItem*>(ConsoleUIManager()->get_widget("/MenuBar/MenuOptions/ToggleTextWrap"));
    toggleTextWrapMenuItemHandle.set_active(true);

}

/***********************************************/
void CConsoleWindow::InitializeWindowProperties()
/***********************************************/
{
    set_border_width(1);
    set_default_size(400, 300);
}

/***************************************/
void CConsoleWindow::InstantiateMenuBar()
/***************************************/
{
   _menuBar = ConsoleUIManager()->get_widget("/MenuBar");
}

/**********************************/
void CConsoleWindow::OnActionClear()
/**********************************/
{
    ConsoleTextBuffer()->set_text("");
}

/*********************************************/
void CConsoleWindow::OnActionToggleScrollBars()
/*********************************************/
{
    Gtk::CheckMenuItem& toggleScrollMenuItemHandle = *dynamic_cast<Gtk::CheckMenuItem*>(ConsoleUIManager()->get_widget("/MenuBar/MenuOptions/ToggleScrollBars"));

  //  if (toggleScrollMenuItemHandle.get_active())

   // else


}

/*******************************************/
void CConsoleWindow::OnActionToggleTextWrap()
/*******************************************/
{
    Gtk::CheckMenuItem& toggleTextWrapMenuItemHandle = *dynamic_cast<Gtk::CheckMenuItem*>(ConsoleUIManager()->get_widget("/MenuBar/MenuOptions/ToggleTextWrap"));
    if (toggleTextWrapMenuItemHandle.get_active())
        ConsoleTextView().set_wrap_mode(Gtk::WRAP_WORD);
    else
        ConsoleTextView().set_wrap_mode(Gtk::WRAP_NONE);
}

/*******************************************************/
void CConsoleWindow::SetConsoleIcon(Glib::ustring filename)
/*******************************************************/
{
    set_icon_from_file(filename);
}



};
