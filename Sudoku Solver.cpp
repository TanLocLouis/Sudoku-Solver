#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

const int size = 9;
int cnt = 0;

bool check(int x, int y, int num, vector<vector<int>>& board) {
	for (int i = 0; i < size; i++) // check row
		if (board[x][i] == num) return false;

	for (int i = 0; i < size; i++) // check column
		if (board[i][y] == num) return false;

	int m = (x / 3) * 3; // check 3 x 3 square
	int n = (y / 3) * 3;
	for (int i = m; i < m + 3; i++)
		for (int j = n; j < n + 3; j++)
			if (board[i][j] == num) return false;
		
	return true;
}

void sendKeyDown(unsigned char keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;

    input.ki.wVk = keyCode;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void sendKeyUp(unsigned char keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;

    input.ki.wVk = keyCode;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void autofill(vector<vector<int>>& board) { // show board
	cout << "----------Answer-----------" <<  endl;
	cout << "After " << cnt << " caculations" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) cout << board[i][j] << char(32);
		cout << endl;
	}
	cout << "Autofill in 10s" << endl;
	Sleep(10000);
	
	cout << "----------Filling----------" <<  endl;
	for (int i = 0; i < size; i++) {
		if (i % 3 == 0)
			cout << "------------------------------" << endl;
		
		for (int j = 0; j < size; j++) {
			char c = char(board[i][j] + 48);
			sendKeyDown(c);
			sendKeyUp(c);
			
			if (j % 3 == 0) cout << " | ";
			cout << board[i][j] << char(32);
			
			sendKeyDown(VK_RIGHT);
			sendKeyUp(VK_RIGHT);
			Sleep(100);
		}
		
		cout << endl;
		sendKeyDown(VK_DOWN);
		sendKeyUp(VK_DOWN);
		for (int k = 1; k <= 8; k++) {
			sendKeyDown(VK_LEFT);
			sendKeyUp(VK_LEFT);
		}
	}
	cout << "Win!!!";
	Sleep(20000);
}

void solve(int cell, vector<vector<int>>& board) {
	if (cell == 81) {
		autofill(board);
		return;
	}
	
	cnt++;
	
	int x = cell / 9;
	int y = cell % 9;
	
	if (board[x][y] != 0)
		solve(cell + 1, board);
	
	if (board[x][y] == 0) {
		for (int num = 1; num < 10; num++)
		if (check(x, y, num, board)) {
			board[x][y] = num;
			solve(cell + 1, board);
		}

		board[x][y] = 0	;	
	}	
}

void input(vector<vector<int>>& board) {
	cout << "Input number (0 at fill cell): " << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> board[i][j];
}

int main() {
	vector<vector<int>> board(size, vector<int>(size, 0));
	
	cout << "/----------Sudoku Solver----------/" << endl;
	cout << "/----------TanLocLouis------------/" << endl;
	input(board);
	solve(0, board);
	return 0;
}
