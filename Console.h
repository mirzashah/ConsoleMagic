/*****************************************************************************/
// Filename: Console.h
/*****************************************************************************/
// Description: This class represents a Console window derived from Gtk::Window.
// Each object of this class represents a physical console on the screen.
/*****************************************************************************/


#ifndef CONSOLE_MAGIC_CONSOLE_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_H_DEFINED

#include <ConsoleWindow.h>
#include <ostream>
#include <sstream>
using std::ostringstream;

namespace ConsoleMagic
{

class CConsole : public CConsoleWindow
{
    friend class CConsoleManager;

    public:
        CConsole();
        virtual ~CConsole();
        static CConsole*                    Create();
        void                                ClearConsole();
        unsigned int                        GetConsoleID();
        Glib::ustring                       GetConsoleText();
        void                                AdjustScrollBarsToBottomLeft();
        void                                SetTheConsoleTitle(Glib::ustring title);

#ifdef WIN32
        CConsole& operator<<(std::ostream&(*functionPtr)(std::ostream&))
        {
            _mutex.lock();
            if(functionPtr == std::endl)
                (*this)<<'\n';
            _mutex.unlock();
            return(*this);
        }
#endif

        template <typename T> CConsole&  operator<<(const T& val)
        {
            _mutex.lock();
            LimitBufferSize();
            AdjustScrollBarsToBottomLeft();
            ostringstream temp;
            temp<<val;
            ConsoleTextBuffer()->insert_at_cursor(temp.str().c_str());
            ConsoleTextView().set_buffer(ConsoleTextBuffer());
            //ConsoleTextView().get_buffer()->insert_at_cursor(temp.str().c_str());
            _mutex.unlock();
            return(*this);
        }


    private:
        // Private Class Operations
        Glib::ustring                       GetTheConsoleTitle();
        void                                SetConsoleID(unsigned int consoleID);
        void                                UpdateConsoleTitle();
        void                                LimitBufferSize();

        // Private Class Variables
        unsigned int                        _consoleID;
        Glib::ustring                       _consoleTitle;
        Glib::Mutex                         _mutex;



};

};

#endif
