#include <Console.h>
#include <gtkmm.h>
#include <sstream>
using std::ostringstream;

namespace ConsoleMagic
{

/*************************************************************************************************************************/
    CConsole::CConsole() : _consoleID(0), _consoleTitle("")
/*************************************************************************************************************************/
{
}

/*******************/
CConsole::~CConsole()
/*******************/
{
}

/**************************/
CConsole* CConsole::Create()
/**************************/
{
    CConsole* consoleWindow = new CConsole();
    return(consoleWindow);
}

/***************************/
void CConsole::ClearConsole()
/***************************/
{
    ConsoleTextBuffer()->set_text("");
}

/***********************************/
unsigned int CConsole::GetConsoleID()
/***********************************/
{
    return(_consoleID);
}

/**************************************/
Glib::ustring CConsole::GetConsoleText()
/**************************************/
{
    return(ConsoleTextBuffer()->get_text());
}

/******************************************/
Glib::ustring CConsole::GetTheConsoleTitle()
/******************************************/
{
    return(_consoleTitle);
}

/*******************************************/
void CConsole::AdjustScrollBarsToBottomLeft()
/*******************************************/
{
    Glib::RefPtr<Gtk::TextBuffer::Mark> mark = ConsoleTextBuffer()->create_mark(ConsoleTextBuffer()->get_iter_at_line(ConsoleTextBuffer()->get_line_count()));
    ConsoleTextView().scroll_to_mark(mark,0);
    ConsoleTextBuffer()->delete_mark(mark);
}

/*************************************************/
void CConsole::SetConsoleID(unsigned int consoleID)
/*************************************************/
{
    _consoleID = consoleID;
    UpdateConsoleTitle();
}

/***********************************************/
void CConsole::SetTheConsoleTitle(Glib::ustring title)
/***********************************************/
{
    _consoleTitle = title;
    UpdateConsoleTitle();
}

/*********************************/
void CConsole::UpdateConsoleTitle()
/*********************************/
{
    ostringstream finalTitle;
    finalTitle << "Console " << GetConsoleID() << ": "<<GetTheConsoleTitle();
    set_title(finalTitle.str());
}

/**********************************/
void CConsole::LimitBufferSize()
/***********************************/
{
    if (ConsoleTextBuffer()->get_line_count() > (300))   // need to make this a pass in
    {
        Gtk::TextBuffer::iterator itrAtLineCount = ConsoleTextBuffer()->get_iter_at_line(ConsoleTextBuffer()->get_line_count()-300);
        Gtk::TextBuffer::iterator itrAtBegin;
        Gtk::TextBuffer::iterator itrAtEnd;
        ConsoleTextBuffer()->get_bounds(itrAtBegin, itrAtEnd);
        ConsoleTextBuffer()->erase(itrAtBegin,itrAtLineCount);
    }
}

};
