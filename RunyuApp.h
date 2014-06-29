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

#ifndef _RUNYUAPP_H
#define _RUNYUAPP_H

#include <Application.h>

class RunyuApp : public BApplication {
	public:
					RunyuApp();
		virtual		~RunyuApp();
		void		ReadyToRun();
		void		MessageReceived(BMessage *message);

};

#endif // _RUNYU_APP_H
