#include <Windows.h>
#include <stdio.h>
#include "constants.h"
#include "handler.h"

bool Handler::EXECUTE;
bool Handler::STOPPED;

/**
 *	Constructor, initializes necessary variables
 *	
 *	@access	public
 */
Handler::Handler(void) {
	Handler::thread = NULL;
	Handler::setExecute(false);
	Handler::setStopped(true);
}

/**
 *	Function in which the handle thread runs once started by Handler::handler_start
 *	
 *	@access	private
 *	@return	unsigned long __stdcall
 */
DWORD WINAPI Handler::handler_execute(void* data) {
	{
		Handler::setStopped(false);
		printf("Handler started.\n");
		{
			while (Handler::getExecute()) {
				printf("Running ...\n");
				Sleep(DELAY);
			}
		}
		printf("Handler stopped.\n");
		Handler::setStopped(true);
	}
	return 0;// Thread goes away when funct. returns
}

/**
 *	Starts the handler
 *	
 *	@access	public
 *	@return	bool
 */
bool Handler::handler_start() {
	{
		if (Handler::getExecute() || !Handler::getStopped()) return false;
		Handler::setExecute(true);
		Handler::thread = CreateThread(NULL, 0, Handler::handler_execute, NULL, 0, NULL);
	}
	return true;
}

/**
 *	Stops the handler
 *	
 *	@access	public
 */
void Handler::handler_stop()  {
	Handler::EXECUTE = false;
}

/**
 *	Sets a new value for variable EXECUTE
 *	
 *	@access	private
 *	@param	bool	new value
 */
void Handler::setExecute(bool _EXECUTE) {
	Handler::EXECUTE = _EXECUTE;
}

/**
 *	Sets a new value for variable STOPPED
 *	
 *	@access	private
 *	@param	bool	new value
 */
void Handler::setStopped(bool _STOPPED) {
	Handler::STOPPED = _STOPPED;
}

/**
 *	Returns value of variable EXECUTE
 *	
 *	@access	private
 *	@return	bool	value of vairable EXECUTE
 */
bool Handler::getExecute(void) {
	return Handler::EXECUTE;
}

/**
 *	Returns value of variable STOPPED
 *	
 *	@access	private
 *	@return	bool	value of vairable STOPPED
 */
bool Handler::getStopped(void) {
	return Handler::STOPPED;
}