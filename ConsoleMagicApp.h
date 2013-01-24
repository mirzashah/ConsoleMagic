/*****************************************************************************/
// Filename: ConsoleMagicApp.h
/*****************************************************************************/
// Description: This class is the base class for any app that wants to use
// Console Magic. The end user must subclass this class, create an instance
// of it in their int main() function, and invoke the event loop via
// the Run() method.
/*****************************************************************************/

#ifndef CONSOLE_MAGIC_CONSOLE_MAGIC_APP_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_MAGIC_APP_H_DEFINED

#include <vector>
#include <string>

namespace Gtk
{
    class Main; //Forward declaration
    class Window;
};

namespace ConsoleMagic
{

class CConsoleMagicApp
{
    public:
        CConsoleMagicApp(Gtk::Main& kit, unsigned int timerElapseInMilliseconds);
        virtual ~CConsoleMagicApp();



        /**
        * Called right before the main Gtk event-loop is started. Gives an opportunity
        * to initialize things.
        */
        virtual void OnStartup();

        /**
        * Called every "timerElapseInMilliseconds" seconds. Value is set in constructor.
        */
        virtual void OnTimer() = 0;

        /**
        * Begins the main event loop. The method will never return, until the main app window is closed.
        */
        void         Run(std::string consoleLayoutFilename="ConsoleMagicLayout.txt");
        void         Run(std::vector<Gtk::Window*> gtkwindows, std::string consoleLayoutFilename="ConsoleMagicLayout.txt");




    private:
        void         InstallTimer();
        bool         IsConsolePauseButtonPressed();
        Gtk::Main&   Kit();
        bool         OnTimerInternal(int timer_number);
        unsigned int TimerElapseInMilliseconds();

    private:
        bool         _isFirstIteration;
        Gtk::Main&   _kit;
        unsigned int _timerElapseInMilliseconds;
};

};

#endif
