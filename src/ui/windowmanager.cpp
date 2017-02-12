#include <stddef.h> //for NULL
#include <impl/curses/CursesWindow.h>
#include <impl/curses/curseslib.h>
#include "windowmanager.h"

const char* WIN_TITLE_CHOICES  = "Choices";
const char* WIN_TITLE_MESSAGES = "Messages";

WindowManager* WindowManager::instance = NULL; //singleton instance static initialization

WindowManager* WindowManager::getInstance()
{
	//postcondition: allocates a new WindowManager instance if one doesn't exist,
	//and sets it as the singleton instance. If we've already instantiated one,
	//that instance is returned;

	if(instance == NULL)
	{
		instance = new WindowManager();
	}

	return instance;
}

WindowManager::WindowManager()
	: mainWin(NULL),
	  choiceWin(NULL),
	  msgWin(NULL),
	  cursesActive(false)
{

}

WindowManager::~WindowManager()
{
	//postcondition: all Windows are de-allocated, and curses has been stopped
	//NOTE: shutdown() should be explicitly called on the window manager, so
	//this destructor should basically do nothing.

	destroyWindows();
	shutdownCurses();
}

bool WindowManager::init()
{
	//postcondition: initialize curses subsystem, and create the Window objects
	//that will represent the 3 main UI windows in Errantry.

	initCurses();

	createMainWin();
	createChoiceWin();
	createMessageWin();

	//Now that curses is running and our windows have been made, draw them to the screen
	doupdate();

	//If for some reason the 1 or more of the windows couldn't be inited, return false
	if(mainWin == NULL || choiceWin == NULL || msgWin == NULL || !cursesActive) {
		return false;
	}

	return true;
}

bool WindowManager::shutdown()
{
	//postcondition: all Windows are de-allocated, and curses has been stopped.
	//This method should be explicitly called before the program exits to ensure
	//the console has been reset to its former state.

	destroyWindows();
	shutdownCurses();
	return true;
}

Window* WindowManager::getMainWin()
{
	return mainWin;
}

Window* WindowManager::getChoiceWin()
{
	return choiceWin;
}

Window* WindowManager::getMessageWin()
{
	return msgWin;
}

void WindowManager::initCurses()
{
	//postcondition: curses subsystem is started with default input options
	//enabled: Enter doesn't need pressed after input, arrow and F keys on, no
	//input echo.
	//If curses has already been initialized, it won't be initialized again.

	if(!cursesActive)
	{
		initscr();				//Start curses mode
		cbreak();				//Line buffering disabled - don't need to press enter after pressing key to submit input
		keypad(stdscr, TRUE);	//Enable arrow and function keys
		noecho();				//Don't echo keypresses to console
	}

	cursesActive = true;
}

void WindowManager::shutdownCurses()
{
	//postcondition: free all resources allocated by ncurses and restore console
	//to pre-curses state.  If curses has already been stopped, this method
	//won't attempt to stop it again.

	if(cursesActive)
	{
		endwin();
	}

	cursesActive = false;
}

void WindowManager::createMainWin()
{
	//postcondition: mainWin field is instantiated w/ proper size, position,
	//and default title.

	mainWin = new CursesWindow(32,32);
}

void WindowManager::createChoiceWin()
{
	//postcondition: choiceWin field is instantiated w/ proper size, position,
	//and default title.

	choiceWin = new CursesWindow(17,12, 32,0);
	choiceWin->setTitle(WIN_TITLE_CHOICES);
}

void WindowManager::createMessageWin()
{
	//postcondition: msgWin field is instantiated w/ proper size, position and
	//default title.

	msgWin = new CursesWindow(49,12, 0,32);
	msgWin->setTitle(WIN_TITLE_MESSAGES);
}

void WindowManager::destroyWindows()
{
	//postcondition: de-allocates all Window fields held by the WindowManager

	if(mainWin != NULL)
	{
		delete mainWin;
		mainWin = NULL;
	}

	if(choiceWin != NULL)
	{
		delete choiceWin;
		choiceWin = NULL;
	}

	if(msgWin != NULL)
	{
		delete msgWin;
		msgWin = NULL;
	}
}
