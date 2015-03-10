#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <mysql.h>
#include "constants.h"
#include "main.h"
#include "handler.h"


/**
 *	Watches for user input
 *	
 *	@access	public
 */
void Application::watch_input() {
	
	RUN = true;
	char row[MAX_CMD_LEN + 1];// + '\0'
	
	while (RUN) {
		fgets(row, MAX_CMD_LEN + 1, stdin);
		handle_input(row);
		memset(row, 0, sizeof row);
		fflush(stdin);
	}
}

/**
 *	Handles user input
 *	
 *	@access	public
 *	@param	The user input string
 */
void Application::handle_input(char row[]) {
	if (strncmp(row, "START", 5) == 0 || strncmp(row, "start", 5) == 0) {
		Application::funct_start();
	} else
	if (strncmp(row, "STOP", 4) == 0 || strncmp(row, "stop", 4) == 0) {
		Application::funct_stop();
	} else
	if (strncmp(row, "EXIT", 4) == 0 || strncmp(row, "exit", 4) == 0) {
		Application::funct_exit();
	} else
	if (strncmp(row, "HELP", 4) == 0 || strncmp(row, "help", 4) == 0) {
		Application::funct_help();
	} else {
		printf("Unknown command.\n");
	}
}

/**
 *	Handles the start command
 *	
 *	@access	private
 */
void Application::funct_start() {
	Handler handler;
	if (!handler.handler_start()) {
		printf("Failed to start handler, already running?\n");
	}
}

/**
 *	Handles the stop command
 *	
 *	@access	private
 */
void Application::funct_stop() {
	Handler handler;
	handler.handler_stop();
}

/**
 *	Handles the exit command
 *	
 *	@access	private
 */
void Application::funct_exit() {
	exit(0);
}

/**
 *	Handles the help command
 *	
 *	@access	private
 */
void Application::funct_help() {
	printf("==\n");
	printf(" START	- Start server handler\n");
	printf(" STOP	- Stop server handler\n");
	printf(" EXIT	- Exit application\n");
	printf("==\n");
}

/**
 *	Entry Point
 */
int main() {
	Application application;
	printf("Revision [Version: %s]\n", VERSION);

	if (AUTO_START) {
		printf("Autostart enabled!");
		application.handle_input("START");
	}
	
	printf("Waiting for commands ...\n");
	application.watch_input();

	if (DEBUG) getchar();// Leave window open
	return 0;
}