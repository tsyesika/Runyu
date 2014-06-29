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

#ifndef _STATUSWINDOW_H
#define _STATUSWINDOW_H

#include <Window.h>
#include <GroupLayout.h>
#include <StatusBar.h>

static const uint32 kMessageProgressUpdate = 'prgu';

class StatusWindow : public BWindow {
	public:
							StatusWindow(BRect frame);
		virtual				~StatusWindow();
		virtual void		MessageReceived(BMessage* message);
		virtual bool		QuitRequested();		
	
	private:
		BGroupLayout*		fLayout;
		BStatusBar*			fProgressBar;
};

#endif
