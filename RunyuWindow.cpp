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
#include "WordListFile.h"

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
#include <LocaleRoster.h>
#include <Roster.h>
#include <String.h>

RunyuWindow::RunyuWindow(BRect frame, const char* title)
	: BWindow(frame, title, B_TITLED_WINDOW,
		B_NOT_ZOOMABLE | B_AVOID_FRONT, B_ALL_WORKSPACES | B_QUIT_ON_WINDOW_CLOSE | B_CLOSE_ON_ESCAPE)
{	
	// Create window view & layout
	BGroupLayout* layout = new BGroupLayout(B_VERTICAL, 0);
	SetLayout(layout);

	// Add menubar
	BMenuBar *menuBar = new BMenuBar("menu");
	layout->AddView(menuBar);
	
	// File menu
	BMenu* fileMenu = new BMenu("File");
	fileMenu->AddItem(new BMenuItem("Update Dictionary",
		new BMessage(kMsgUpdateDictionary), 'U'));
	fileMenu->AddSeparatorItem();
	fileMenu->AddItem(new BMenuItem("Quit",
		new BMessage(B_QUIT_REQUESTED), 'Q'));
	menuBar->AddItem(fileMenu);
	
	// Help menu
	BMenu* helpMenu = new BMenu("Help");
	helpMenu->AddItem(new BMenuItem("Learn Na'vi",
		new BMessage(kMsgLearnNavi)));
	helpMenu->AddItem(new BMenuItem("About Runyu",
		new BMessage(kMsgAboutRunyu)));
	menuBar->AddItem(helpMenu);
	
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
	be_app->PostMessage(B_QUIT_REQUESTED);
	Hide();
	return true;
}

void
RunyuWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kMessageSearch:
		{
			_SearchForWord(searchInput->Text());
			break;
		}	
		case kMsgLearnNavi:
		{			
			// Is there a nicer way to do this?
			entry_ref ref;
			if (get_ref_for_path("/bin/open", &ref))
				return;
			const char* args[] = { "/bin/open", "https://learnnavi.org/", NULL};
			be_roster->Launch(&ref, 2, args);
			break;
		}
		
		case kMsgAboutRunyu:
		{
			// This should use AboutWindow.h which is part of interface kit
			// however I can't figure how to get it compiled with the
			// #include <AboutWindow.h>
			break;
		}
		
		default:
		{
			BWindow::MessageReceived(message);
			break;
		}
	}
}

void
RunyuWindow::_SearchForWord(const char* word)
{
	// Open the dictionary and start looking for the word
	results->SetText("Searching...");
	
	// Get preferred language
	BMessage preferredLanguages;
	BLocaleRoster::Default()->GetPreferredLanguages(&preferredLanguages);
	const char* firstLanguage;
	if (preferredLanguages.FindString("language", &firstLanguage) != B_OK) {
		firstLanguage = "en"; // Fallback to english
	}
	
	// Now open word list.
	// TODO: Check if file exists if not pick next available language else or error
	// TODO: Move to BPath?
	BString basePath("/boot/home/config/settings/Runyu/");
	
	BString naviPath(basePath);
	naviPath += "nvi.words";
	
	BString localPath(basePath);
	localPath += firstLanguage;
	localPath += ".words";
	
	WordListFile naviDict = WordListFile(naviPath.String());
	WordListFile localDict = WordListFile(localPath.String());
	
	// Now search through both dictionaries looking for the word
	int lineno = 0;
	bool foundWord = false;
	BString currentWord;
	BString definition;
	
	while (true)
	{
		naviDict.ReadWord(currentWord);
		
		// If it's empty then we've finished
		if (currentWord.Length() == 0)
			break;
		
		if (currentWord == word) {
			// Found it!
			localDict.ReadLine(definition, lineno);
			results->SetText(definition.String());
			foundWord = true;
		}
		
		lineno++;
	}
	
	
	if (!foundWord) {
		BString error(word);
		error += " can't be found in the dictionary.";
		error.Capitalize();
		results->SetText(error.String());
	}
}
