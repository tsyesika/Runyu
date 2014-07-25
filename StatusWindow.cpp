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

#include "StatusWindow.h"

#include <Application.h>
#include <GroupLayout.h>

StatusWindow::StatusWindow(BRect frame)
	: BWindow(frame, "Download Status", B_TITLED_WINDOW,
		B_NOT_CLOSABLE | B_NOT_RESIZABLE | B_NOT_ZOOMABLE, B_ALL_WORKSPACES)
{
	BGroupLayout* layout = new BGroupLayout(B_VERTICAL, 0);
	SetLayout(layout);
	
	fLayout = new BGroupLayout(B_VERTICAL);
	fLayout->SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING,
		B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING);
	fLayout->SetSpacing(B_USE_DEFAULT_SPACING);
	
	BView* fview = new BView("view", 0, fLayout);
	fview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	layout->AddView(fview);
	
	fProgressBar = new BStatusBar("progress", "Dictionary download:");
	fProgressBar->SetMaxValue(100);
	fProgressBar->SetBarHeight(12);
	fProgressBar->SetTo(0.0, NULL, "Finding dictionary");
	fLayout->AddView(fProgressBar);
}

StatusWindow::~StatusWindow()
{
}

void
StatusWindow::MessageReceived(BMessage* message)
{
	switch (message->what)
	{
		default:
			BWindow::MessageReceived(message);
	}
}

void
StatusWindow::SetProgress(int progress, const char* status)
{
	fProgressBar->SetTo(progress, NULL, status);
}

bool
StatusWindow::QuitRequested()
{
	BWindow::Quit();
	return true;
}
