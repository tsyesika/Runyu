/*
 *  This file is part of Runyu.
 *
 *  Runyu is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Runyu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Runyu.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RunyuApp.h"
#include "RunyuWindow.h"

#include <Directory.h>
#include <FindDirectory.h>
#include <Path.h>
#include <Entry.h>

const char* kRunyuAppSig = "application/x-vnd.Runyu";

RunyuApp::RunyuApp()
	: BApplication(kRunyuAppSig)
{
}

RunyuApp::~RunyuApp()
{
}

void
RunyuApp::ReadyToRun()
{
	// Create directory for data.
	BPath 			path;
	BDirectory 		dir;
	BEntry			entry;
	
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &path, true) == B_OK)
	{
		dir.SetTo(path.Path());
		
		if (dir.FindEntry("Runyu", &entry) == B_NO_ERROR)
			dir.SetTo(&entry);
		else
			dir.CreateDirectory("Runyu", &dir);	
	}
	
	// Create a window
	BWindow* runyuWindow = new RunyuWindow(BRect(100, 100, 700, 500), "Runyu");
	runyuWindow->Show();
}

void
RunyuApp::MessageReceived(BMessage *message)
{
	switch (message->what) {
		default:
			BApplication::MessageReceived(message);
	}
}
