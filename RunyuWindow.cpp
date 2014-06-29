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
#include "RunyuWindow.h"

#include <Application.h>
#include <Locale.h>
#include <File.h>
#include <ControlLook.h>
#include <GridView.h>
#include <GroupView.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <GroupLayout.h>
#include <TextControl.h>
#include <Button.h>

RunyuWindow::RunyuWindow(BRect frame, const char* title)
	: BWindow(frame, title, B_TITLED_WINDOW,
		B_NOT_ZOOMABLE | B_AVOID_FRONT, B_ALL_WORKSPACES | B_QUIT_ON_WINDOW_CLOSE | B_CLOSE_ON_ESCAPE)
{	
	// Create window view & layout
	BGroupLayout* layout = new BGroupLayout(B_VERTICAL, 0);
	SetLayout(layout);
	
	fLayout = new BGroupLayout(B_VERTICAL);
	fLayout->SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING,
		B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING);
	fLayout->SetSpacing(B_USE_DEFAULT_SPACING);
	
	BView* fview = new BView("view", 0, fLayout);
	fview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	layout->AddView(fview);
	
	// Draw the top box with word input and button.
	BGroupView* searchLayout = new BGroupView(B_HORIZONTAL);
	searchInput = new BTextControl("search", "Word:", " ", NULL);
	BButton* searchButton = new BButton("search",
		"Search", new BMessage(kMessageSearch));
	
	searchLayout->GroupLayout()->AddItem(searchInput->CreateLabelLayoutItem());
	searchLayout->GroupLayout()->AddItem(searchInput->CreateTextViewLayoutItem());
	searchLayout->GroupLayout()->AddView(searchButton);
	fLayout->AddView(searchLayout);
	
	results = new BTextView("results");
	results->MakeEditable(false);
	results->MakeSelectable(true);
	
	fLayout->AddView(results);
	
	// Focus the searchInput dealio
	searchInput->MakeFocus(true);
	searchInput->SetText("");
}

RunyuWindow::~RunyuWindow()
{
}

bool
RunyuWindow::QuitRequested()
{
	BWindow::Quit();
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void
RunyuWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kMessageSearch:
			_SearchForWord(searchInput->Text());
		
		default:
			message->PrintToStream();
	}
}

void
RunyuWindow::_SearchForWord(const char* word)
{
	// Open the dictionary and start looking for the word
	results->SetText("Searching...");
	
	// Open wordlist
	const BLocale* locale = BLocale::Default();
	results->SetText(locale->GetString(0));
}
