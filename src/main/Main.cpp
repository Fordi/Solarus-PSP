/*
 * Copyright (C) 2006-2015 Christopho, Solarus - http://www.solarus-games.org
 *
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOLARUS_NOMAIN

#include "solarus/lowlevel/Debug.h"
#include "solarus/lowlevel/Output.h"
#include "solarus/Arguments.h"
#include "solarus/MainLoop.h"

#include <iostream>
#include <string>

#include <pspdisplay.h>
#include <psppower.h>
#include <pspdebug.h>
#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <psploadexec.h>
#include <pspctrl.h>

#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("Solarus", PSP_MODULE_USER, 1, 2);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-64);
PSP_MAIN_THREAD_STACK_SIZE_KB(192);

//deleted print_help
/* PSP Callbacks */
bool widescreen = false // stretch quest to fit the whole screen
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}
/**
 * \brief Usual entry point of the program.
 *
 * Usage: solarus [options] [quest_path]
 *
 * The quest path is the name of a directory that contains either the data
 * directory ("data") or the data archive ("data.solarus" or
 * "data.solarus.zip").
 * If the quest path is not specified, it is set to the preprocessor constant
 * DEFAULT_QUEST, which is the current directory "." by default.
 * In all cases, this quest path is relative to the working directory,
 * or to the solarus executable directory if no quest is found in the working
 * directory.
 */
int main(int argc, char** argv) {

  using namespace Solarus;
  scePowerSetClockFrequency(333,333,166);
  widescreen = true // stretch the screen to fit the whole psp screen
  
  sceKernelDelayThread(2 * 1000 * 1000); //compute a load time, just to be sure everythin loads fine

   // PSP additions
   sceCtrlSetSamplingCycle(0);
   sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
  // Store the command-line arguments.
  const Arguments args(argc, argv);

  // Run the main loop.
  MainLoop(args).run(); // run the game
  
  sceKernelExitGame();

  return 0;
}

#endif

