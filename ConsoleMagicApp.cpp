#include <ConsoleMagicApp.h>
#include <ConsoleManager.h>

namespace ConsoleMagic
{

/*************************************************/
const unsigned int DEFAULT_TIMER_NUMBER = 0;
/*************************************************/

/*************************************************/
CConsoleMagicApp::CConsoleMagicApp(Gtk::Main& kit, unsigned int timerElapseInMilliseconds) :
_kit(kit),
_timerElapseInMilliseconds(timerElapseInMilliseconds)
/*************************************************/
{
    if(!Glib::thread_supported())
        Glib::thread_init();
}

/*************************************************/
CConsoleMagicApp::~CConsoleMagicApp()
/*************************************************/
{
}

/*************************************************/
bool CConsoleMagicApp::IsConsolePauseButtonPressed()
/*************************************************/
{
    return CConsoleManager::Instance().IsConsolePauseButtonPressed();
}

/*************************************************/
void CConsoleMagicApp::InstallTimer()
/*************************************************/
{
  sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &CConsoleMagicApp::OnTimerInternal), DEFAULT_TIMER_NUMBER);

  // This is where we connect the slot to the Glib::signal_timeout()
  sigc::connection conn = Glib::signal_timeout().connect(my_slot, TimerElapseInMilliseconds());
}

/*************************************************/
Gtk::Main& CConsoleMagicApp::Kit()
/*************************************************/
{
    return(_kit);
}

/*************************************************/
void CConsoleMagicApp::OnStartup()
/*************************************************/
{
    //No-op
}

/******************************************************/
bool CConsoleMagicApp::OnTimerInternal(int timer_number)
/******************************************************/
{
    if (!IsConsolePauseButtonPressed())
        OnTimer();
    return(true);
}

/**************************/
void CConsoleMagicApp::Run(std::string consoleLayoutFilename)
/**************************/
{
    CConsoleManager::Instance().SetConsoleLayoutFileName(consoleLayoutFilename);
    CConsoleManager::Instance().PositionConsolesFromFile();
    OnStartup();
    InstallTimer();
    Kit().run(CConsoleManager::Instance());
}

/**************************************************************/
void CConsoleMagicApp::Run(std::vector<Gtk::Window*> gtkWindows, std::string consoleLayoutFilename)
/**************************************************************/
{
    CConsoleManager::Instance().GtkWindowMap().clear();
    for(unsigned int c=0; c<gtkWindows.size(); c++)
        CConsoleManager::Instance().AddGtkWindow(c, gtkWindows[c]);
    CConsoleManager::Instance().PositionConsolesFromFile();
    Run(consoleLayoutFilename);
}

/********************************************************/
unsigned int CConsoleMagicApp::TimerElapseInMilliseconds()
/********************************************************/
{
    return(_timerElapseInMilliseconds);
}



};
