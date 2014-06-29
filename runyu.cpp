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

#include <Application.h>
#include "RunyuWindow.h"

const char* appSignature = "application/x-vnd.Runyu";

int
main(int argc, char* argv[])
{
	BApplication app(appSignature);
	
	// Create a window
	BWindow* runyuWindow = new RunyuWindow(BRect(100, 100, 700, 500), "Runyu");
	runyuWindow->Show();
	
	app.Run();
	return 0;
}
