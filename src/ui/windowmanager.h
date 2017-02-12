#ifndef SRC_UI_WINDOWMANAGER_H_
#define SRC_UI_WINDOWMANAGER_H_

#include <Window.h>

using winterchange::Window;

/* Singleton which can provide pointers to each of the Windows that make up
 * the UI.
 * Also contains methods to initialize and shutdown the ncurses subsystem used
 * for console UI.
 */
class WindowManager
{
	protected:
		static WindowManager* instance;

		Window* mainWin;
		Window* choiceWin;
		Window* msgWin;

		bool cursesActive;

		WindowManager();

		void initCurses();
		void shutdownCurses();

		void createMainWin();
		void createChoiceWin();
		void createMessageWin();
		void destroyWindows();

	public:
		static WindowManager* getInstance();
		virtual ~WindowManager();

		bool init();
		bool shutdown();

		Window* getMainWin();
		Window* getChoiceWin();
		Window* getMessageWin();
};

#endif
