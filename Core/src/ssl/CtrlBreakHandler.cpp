#include <CtrlBreakHandler.h>
#include <iostream>
#include <param.h>
#include <signal.h>
#ifdef WIN32
#include <Windows.h>
#endif
namespace{
	bool breakPressed = false;
	bool haltPressed = false;
    int countAfterBreak = 0;
#ifdef WIN32
    bool CtrlHandler(DWORD fdwCtrlType)
	{ 
		switch (fdwCtrlType){ 
		case CTRL_C_EVENT:
			if(haltPressed){
				std::cout << "resume system" << std::endl;
				haltPressed = false;
			}
			else{
				std::cout << "halt system" << std::endl;
				haltPressed = true;
			}
			return TRUE;
		case CTRL_CLOSE_EVENT:
		case CTRL_BREAK_EVENT:
			breakPressed = true;
			return TRUE; 
		case CTRL_LOGOFF_EVENT: 
		case CTRL_SHUTDOWN_EVENT: 
		default: 
			return FALSE; 
		} 
    }
#else
    extern "C"
    void CtrlHandler(int a) {
        if(haltPressed){
            std::cout << "resume system" << std::endl;
            haltPressed = false;
        }
        else{
            std::cout << "halt system" << std::endl;
            haltPressed = true;
        }
    }
#endif
}
CCtrlBreakHandler::CCtrlBreakHandler()
{
#ifdef WIN32
    if (!SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler,TRUE)){
		std::cout << "Could not set control handler" << Param::Output::NewLineCharacter;
    }
#else
    struct sigaction newhandler;
    newhandler.sa_handler = &CtrlHandler;
    sigaddset(&newhandler.sa_mask, SIGQUIT);
    newhandler.sa_flags = 0;
    sigaction(SIGINT, &newhandler, NULL);
#endif
}
int CCtrlBreakHandler::breaked()
{
	if(!breakPressed && countAfterBreak==0)		// 未按下ctrl+Break
		return -1;
	else
		++countAfterBreak;
	if(countAfterBreak <= 1) // 按下ctrl+Break后第一次
		return 0;
	else
		return 1;
}

bool CCtrlBreakHandler::halted()
{
	return haltPressed;
}
