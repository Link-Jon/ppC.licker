#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

string input = "string";
bool clicking = false;
bool basic = false;
bool savefile[10];
int timeoutSeconds = 120;
int counter = 0;
int save = -1;
int x[10];
int y[10];


int main() {

	// Intro

	system("TITLE Mouse Clicker by sandaasu");
	cout << "Mouse Clicker by sandaasu\n";
	cout << "======================================================\n";
	cout << "[ HOTKEYS ]\n\n";
	cout << "Numpad1 = Save mouse position\n";
	cout << "NumPad2 = Activate autoclicker on saved position\n";
	cout << "NumPad3 = STOP\n";
	cout << "NumPad5 = Text Commands\n";
	cout << "Escape  = Close\n\n";
	cout << "======================================================\n\n";
	cout << "[ LOG ]\n\n";

	// Main Loop

	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			save++;
			if (save > 9) {
				cout << "Save file at 9; continue from 0?\n {y / n}\n STRING << ";
				cin >> input;
				if (input == "y") { save = 0; };
				if (input == "n") { save = 9; };
			};

			POINT cursorPos;
			GetCursorPos(&cursorPos);

			x[save] = cursorPos.x;
			y[save] = cursorPos.y;
			savefile[save] = true;

			cout << "Mouse X = " << x[save] << endl;
			cout << "Mouse Y = " << y[save] << endl;
			cout << "Saved to slot " << save << endl;

			Sleep(100);
		}

		if (GetAsyncKeyState(VK_NUMPAD5)) {
			cout << "What do you want to do?\n['save' || 'timeout']\n STRING <<";
			cin >> input;
			if (input == "timeout") {
				cout << "What do you want the timer to be? (In Seconds):\nINTEGER << ";
				cin >> timeoutSeconds;
				if (timeoutSeconds < 1)
				{
					cout << "\nTimeout Disabled\n";
				};
				//else;
				{ cout << "Timeout set to " << timeoutSeconds << "Seconds.\n"; };
			}//end safety timeout setup logic.

			else if (input == "save") {
				cout << "What do you want to do?\nForce select save slot [0 - 9] (slot1 to slot 10)\nDelete data in slot [-1 - -10 || -100] (slot1 to slot 10 || ALL)\n";
				cin >> counter;

				if (counter > -1 and counter < 10) {
					save = counter;
				}
				{//else
					counter = counter * -1;
					x[counter] = 0;
					y[counter] = 0;
				}
			}

			{cout << "Warning: Unknown input. Don't capitlize?"; };

		} // END Text commands

		if (GetAsyncKeyState(VK_ESCAPE)) {
			cout << "Bye Bye <3\n";
			Sleep(500);
			PostQuitMessage(0); //Requests to close process, debug detail is 0. (AKA no issue.)
		}

		if (GetAsyncKeyState(VK_NUMPAD2)) {
			cout << "Clicking !\n";
			clicking = true;
			counter = timeoutSeconds * 1000;
			Sleep(100);
		}

		while (clicking) {

			// locking the mouse isnt exactly user safe
			// until we can garrentee the stop hotkey will work anywhere.
			// SetCursorPos()
			if (basic == true) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}

			{//Else: 
				for (int iter = 0; iter >= 10; iter++) {

					if (savefile[iter] == false or savefile[iter] == NULL) { continue; };

					if (GetAsyncKeyState(VK_NUMPAD3) or GetAsyncKeyState(VK_NUMPAD2)) {
						cout << "Stopping the clicker..\n";
						clicking = false;
						break;
					}

					if (GetAsyncKeyState(VK_ESCAPE)) {
						cout << "Bye Bye <3\n";
						Sleep(500);
						PostQuitMessage(0);
					}

					if (0 >= counter and !1 > timeoutSeconds) { cout << "Timed out\n"; clicking = false; break; };
					//if timeout exists, and the counter is over, break while loop.

					SetCursorPos(x[iter], y[iter]);
					mouse_event(MOUSEEVENTF_LEFTDOWN, x[iter], y[iter], 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, x[iter], y[iter], 0, 0);

					counter--;
					Sleep(1);
				}
			}
		}
	}
}

//Variant 1
// A -- Take the user's mouse, and click at specified locations.
// B -- Extra Credit -- Quit after specified time to assist in damage control.

//Variant 2
// A -- Find top layer window at coordinate (Find it's HWND, specifically.)
// B -- Use the HWND to send a WM_LBUTTON at the requested coords
// C -- Profit.

//Variant 3
// A -- Make a fake mouse
// B -- Click locations
// C -- Profit
// D -- Extra credit; make an opensource multimouse program lol
