/*****************************************************************************/
// Filename: ConsoleMagic.h
/*****************************************************************************/
// Description: This file is the only include file end-users need to include
// to use ConsoleMagic.
/*****************************************************************************/

#ifndef CONSOLE_MAGIC_CONSOLE_MAGIC_H_DEFINED
#define CONSOLE_MAGIC_CONSOLE_MAGIC_H_DEFINED

#include <Console.h>
#include <ConsoleMagicApp.h>

namespace ConsoleMagic
{

CConsole& Console(unsigned int consoleID);


void         SetConsoleManagerIcon(Glib::ustring filename);
void         SetConsoleManagerTitle(Glib::ustring title);

};

#endif
