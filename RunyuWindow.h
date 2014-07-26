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
#ifndef _RUNYU_WINDOW_H
#define _RUNYU_WINDOW_H

#include <Window.h>
#include <GroupLayout.h>
#include <TextControl.h>

static const uint32 kMessageSearch = 'srch';
static const uint32 kMsgUpdateDictionary = 'updd';
static const uint32 kMsgLearnNavi = 'lnvi';
static const uint32 kMsgAboutRunyu = 'abtr';

class RunyuWindow : public BWindow {
	public:
						RunyuWindow(BRect frame, const char* title);
		virtual			~RunyuWindow();
		virtual void	MessageReceived(BMessage* message);
		virtual	bool	QuitRequested();

	private:
		void			_InitWindow();
		void			_SearchForWord(const char*);
		void			_WriteDefinition(BString&, BString&, BString&);
	
	private:
		BGroupLayout*	fLayout;
		BTextView*		results;
		BTextControl*	searchInput;
};

#endif // _RUNYU_WINDOW_H
