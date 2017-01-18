#include "multiplayer.h"

int Load_map();
int move_cell_harif(int d, int xm, int ym) {

	if (d == 1) { //North psn_of_Cell_harif[ym][xm]
		if (ym + 1 == fs.height || psn_of_Cell_harif[ym + 1][xm] >= 0) {
			return -1;
		}
		psn_of_Cell_harif[ym + 1][xm] = psn_of_Cell_harif[ym][xm];
		psn_of_Cell_harif[ym][xm] = -1;
	}
	else if (d == 2) { //South psn_of_Cell_harif[ym][xm]
		if (ym - 1 == -1 || psn_of_Cell_harif[ym - 1][xm] >= 0) {
			return -1;
		}
		psn_of_Cell_harif[ym - 1][xm] = psn_of_Cell_harif[ym][xm];
		psn_of_Cell_harif[ym][xm] = -1;
	}
	if (xm % 2 == 0) {
		if (d == 3) { //Northeast psn_of_Cell_harif[ym][xm]
			if (ym + 1 == fs.height || xm + 1 == fs.width || psn_of_Cell_harif[ym + 1][xm + 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym + 1][xm + 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 4) { //Northwest psn_of_Cell_harif[ym][xm]
			if (ym + 1 == fs.height || xm - 1 == -1 || psn_of_Cell_harif[ym + 1][xm - 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym + 1][xm - 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 5) { //Southeast psn_of_Cell_harif[ym][xm]
			if (xm + 1 == fs.width || psn_of_Cell_harif[ym][xm + 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym][xm + 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 6) { //Southwest psn_of_Cell_harif[ym][xm]
			if (xm - 1 == -1 || psn_of_Cell_harif[ym][xm - 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym][xm - 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
	}
	else {
		if (d == 3) { //Northeast psn_of_Cell_harif[ym][xm]
			if (xm + 1 == fs.width || psn_of_Cell_harif[ym][xm + 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym][xm + 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 4) { //Northwest psn_of_Cell_harif[ym][xm]
			if (xm - 1 == -1 || psn_of_Cell_harif[ym][xm - 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym][xm - 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 5) { //Southeast psn_of_Cell_harif[ym][xm]
			if (ym - 1 == -1 || xm + 1 == fs.width || psn_of_Cell_harif[ym - 1][xm + 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym - 1][xm + 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
		else if (d == 6) { //Southwest psn_of_Cell_harif[ym][xm]
			if (ym - 1 == -1 || psn_of_Cell_harif[ym - 1][xm - 1] >= 0) {
				return -1;
			}
			psn_of_Cell_harif[ym - 1][xm - 1] = psn_of_Cell_harif[ym][xm];
			psn_of_Cell_harif[ym][xm] = -1;
		}
	}

	return 0;
}
int boost_energy_in_multi() {

	int i, j, a = fs.height - 1 - y;

	if (Block_Cell[a][x] == '1') {
		if (Energy_Cell[a][x * 4] >= 15) {
			if (psn_of_Cell[y][x] <= 85) {
				psn_of_Cell[y][x] += 15;
				Energy_Cell[a][x * 4] -= 15;
			}
			else {
				printf("With this Energy cell has more than 100 Energy, Try again diffrent cell by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 100;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				return -1;
			}
		}
		else if (Energy_Cell[a][x * 4] > 0) {
			if (Energy_Cell[a][x * 4] <= 100 - psn_of_Cell[y][x]) {
				psn_of_Cell[y][x] += Energy_Cell[a][x * 4];
				Energy_Cell[a][x * 4] = 0;
			}
			else {
				printf("With this Energy cell has more than 100 Energy, Try again diffrent cell by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 100;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				return -1;
			}
		}
		else {
			printf("Block Energy is 0, Try again diffrent block by Enter!");
			getch();
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 100;i++)
				printf(" ");
			gotoxy(0, fs.height * 4 + 4);
			return -1;
		}
	}
	else {
		printf("Cell must be in the source block, Try again by Enter!");
		getch();
		gotoxy(0, fs.height * 4 + 4);
		for (i = 0;i < 60;i++)
			printf(" ");
		gotoxy(0, fs.height * 4 + 4);
		return -1;
	}

	a = fs.height - 1 - cp.y;
	if (Energy_Cell_harif[a][cp.x * 4] >= 15) {
		if (psn_of_Cell[y][cp.x] <= 85) {
			psn_of_Cell_harif[y][cp.x] += 15;
			Energy_Cell_harif[a][cp.x * 4] -= 15;
		}
		else {
			printf("With this Energy cell has more than 100 Energy, Try again diffrent cell by Enter!");
			getch();
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 100;i++)
				printf(" ");
			gotoxy(0, fs.height * 4 + 4);
			return -1;
		}
	}
	else if (Energy_Cell_harif[a][cp.x * 4] > 0) {
		if (Energy_Cell_harif[a][cp.x * 4] <= 100 - psn_of_Cell_harif[y][cp.x]) {
			psn_of_Cell_harif[y][cp.x] += Energy_Cell_harif[a][cp.x * 4];
			Energy_Cell_harif[a][cp.x * 4] = 0;
		}
		else {
			printf("With this Energy cell has more than 100 Energy, Try again diffrent cell by Enter!");
			getch();
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 100;i++)
				printf(" ");
			gotoxy(0, fs.height * 4 + 4);
			return -1;
		}
	}
	else {
		printf("Block Energy is 0, Try again diffrent block by Enter!");
		getch();
		gotoxy(0, fs.height * 4 + 4);
		for (i = 0;i < 100;i++)
			printf(" ");
		gotoxy(0, fs.height * 4 + 4);
		return -1;
	}

	return 0;
}
int show_MoveMenu_in_multi() {

a:	int i, j, k, a = fs.height - 1 - y;
	char c;

	printf("[1] North\n[2] South\n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n[7] Return\n");

b:	c = getch();

	if (c == 49) { //North psn_of_Cell[y][x]
		k = move_cell(1, 0, 1);
		cmd.cell_energy = Energy_Cell[a + 1][x * 4];
		cmd.move_direction = SOUTH;
		cmd = cell_move(cmd);
	}
	else if (c == 50) { //South psn_of_Cell[y][x]
		k = move_cell(2, 0, 1);
		cmd.cell_energy = Energy_Cell[a - 1][x * 4];
		cmd.move_direction = NORTH;
		cmd = cell_move(cmd);
	}
	else if (c == 51) { //Northeast psn_of_Cell[y][x]
		k = move_cell(3, 0, 1);
		cmd.cell_energy = Energy_Cell[a + 1][(x + 1) * 4];
		cmd.move_direction = NORTHEAST;
		cmd = cell_move(cmd);
	}
	else if (c == 52) { //Northwest psn_of_Cell[y][x]
		k = move_cell(4, 0, 1);
		cmd.cell_energy = Energy_Cell[a + 1][(x - 1) * 4];
		cmd.move_direction = NORTHWEST;
		cmd = cell_move(cmd);
	}
	else if (c == 53) { //Southeast psn_of_Cell[y][x]
		k = move_cell(5, 0, 1);
		cmd.cell_energy = Energy_Cell[a - 1][(x + 1) * 4];
		cmd.move_direction = SOUTHEAST;
		cmd = cell_move(cmd);
	}
	else if (c == 54) { //Southwest psn_of_Cell[y][x]
		k = move_cell(6, 0, 1);
		cmd.cell_energy = Energy_Cell[a - 1][(x - 1) * 4];
		cmd.move_direction = SOUTHWEST;
		cmd = cell_move(cmd);
	}
	else if (c == 55) {
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 7;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		return -1;
	}
	else {
		goto b;
	}

	gotoxy(0, fs.height * 4 + 4);
	for (j = 0;j < 7;j++) {
		for (i = 0;i < 60;i++)
			printf(" ");
		printf("\n");
	}
	gotoxy(0, fs.height * 4 + 4);

	if (k == -1) {
		printf("Cell can't go to your selction, Try again by enter!");
		getch();
		gotoxy(0, fs.height * 4 + 4);
		for (i = 0;i < 60;i++)
			printf(" ");
		gotoxy(0, fs.height * 4 + 4);
		goto a;
	}

	a = fs.height - 1 - cp.y;
	if (cmd.move_direction == NORTH) {
		Energy_Cell_harif[a + 1][(cp.x) * 4] = cmd.cell_energy;
		k = move_cell_harif(1, cp.x, cp.y);
	}
	else if (cmd.move_direction == SOUTH) {
		Energy_Cell_harif[a - 1][(cp.x) * 4] = cmd.cell_energy;
		k = move_cell_harif(2, cp.x, cp.y);
	}
	else if (cmd.move_direction == NORTHEAST) {
		Energy_Cell_harif[a + 1][(cp.x + 1) * 4] = cmd.cell_energy;
		k = move_cell_harif(3, cp.x, cp.y);
	}
	else if (cmd.move_direction == NORTHWEST) {
		Energy_Cell_harif[a + 1][(cp.x - 1) * 4] = cmd.cell_energy;
		k = move_cell_harif(4, cp.x, cp.y);
	}
	else if (cmd.move_direction == SOUTHEAST) {
		Energy_Cell_harif[a - 1][(cp.x + 1) * 4] = cmd.cell_energy;
		k = move_cell_harif(5, cp.x, cp.y);
	}
	else if (cmd.move_direction == SOUTHWEST) {
		Energy_Cell_harif[a - 1][(cp.x - 1) * 4] = cmd.cell_energy;
		k = move_cell_harif(6, cp.x, cp.y);
	}

	if (k == -1) {
		printf("Harif cell can't move, Try again by enter!");
		getch();
		gotoxy(0, fs.height * 4 + 4);
		for (i = 0;i < 60;i++)
			printf(" ");
		gotoxy(0, fs.height * 4 + 4);
	}

	return 0;

}
int show_MainMenu_in_multi() {

a:	int i, j, k;
	char c;

	printf("[1] Move\n[2] Boost energy\n[3] Return\n");

b:	c = getch();

	if (c == 49) { //Move
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		k = show_MoveMenu_in_multi();
		if (k == -1)
			goto a;
		Update_Screen();
	}
	else if (c == 50) { //Boost energy
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		k = boost_energy_in_multi();
		if (k == -1)
			goto a;
		Update_Screen();
	}
	else if (c == 51) { //Return
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		return -1;
	}
	else {
		goto b;
	}

	return 0;
}
int select_cell_in_multi() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

a:	int i, j, a, k;

	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, fs.height * 4 + 4);
	printf("Enter a cell cordinate X Y:                       \n              \n            ");
	gotoxy(28, fs.height * 4 + 4);
	scanf("%d %d", &x, &y);
	if (psn_of_Cell[y][x] == -1) {
		gotoxy(0, fs.height * 4 + 4);
		printf("Wrong selection a cell, Try again by Enter!\n");
		getch();
		goto a;
	}
	else {
		if (x % 2 == 0) {
			a = fs.height - 1 - y;
			SetConsoleTextAttribute(hConsole, 44);
			gotoxy(x * 7 + 3, a * 4 + 2);
			printf("X");
			SetConsoleTextAttribute(hConsole, 15);
		}
		else {
			a = fs.height - 1 - y;
			SetConsoleTextAttribute(hConsole, 44);
			gotoxy(x * 7 + 3, a * 4 + 4);
			printf("X");
			SetConsoleTextAttribute(hConsole, 15);
		}
	}
	gotoxy(0, fs.height * 4 + 4);
	for (i = 0;i < 60;i++)
		printf(" ");
	gotoxy(0, fs.height * 4 + 4);

	k = show_MainMenu_in_multi();
	if (k == -1) {
		Update_Screen();
	}

	return 0;
}
int show_Menu_in_multi() {

a: char c;
	int i, j;

	gotoxy(0, fs.height * 4 + 4);

	printf("[1] Select a cell\n[2] Save\n[3] Return\n");

b:	c = getch();

	if (c == 49) { //Select a cell
		select_cell_in_multi();
		goto a;
	}
	else if (c == 50) { //Save
		//save_game();
		goto a;
	}
	else if (c == 51) { //Return
		return -1;
	}
	else {
		goto b;
	}

	return 0;
}
int paly_multi_player() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, j, k, a, b;
	char c;

	clrscr();
	gotoxy(0, 0);
	printf("Which Map:\n[1] Defult Map\n[2] My Selction Map");
a:	c = getch();
	if (c == 49) {
		fs.width = 4;
		fs.height = 4;
		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell[j][i] = -1;
		Energy_Cell[0][0] = 30;
		Energy_Cell[1][4] = 60;
		Energy_Cell[2][8] = 90;
		Energy_Cell[3][8] = 45;
		Energy_Cell[3][12] = 20;
		Block_Cell[0][0] = '1';
		Block_Cell[0][1] = '4';
		Block_Cell[0][2] = '4';
		Block_Cell[0][3] = '2';
		Block_Cell[1][0] = '2';
		Block_Cell[1][1] = '1';
		Block_Cell[1][2] = '4';
		Block_Cell[1][3] = '2';
		Block_Cell[2][0] = '2';
		Block_Cell[2][1] = '2';
		Block_Cell[2][2] = '1';
		Block_Cell[2][3] = '4';
		Block_Cell[3][0] = '3';
		Block_Cell[3][1] = '3';
		Block_Cell[3][2] = '1';
		Block_Cell[3][3] = '1';
		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell_harif[j][i] = -1;
	}
	else if (c == 50) {
		k = Load_map();
		if (k == 0) {
			clrscr();
			printf("Your map's cell number is more than 1, Try again with 0 or 1 cell number by Enter!");
			getch();
			return -1;
		}
	}
	else {
		goto a;
	}

	{//locate one cell in map
	b:	a = fs.height - randn(0, fs.height) - 1;
		b = randn(0, fs.width);
		if (Block_Cell[a][b] == '3' || psn_of_Cell[fs.height - 1 - a][b] == 0)
			goto b;
		else {
			psn_of_Cell[fs.height - 1 - a][b] = 0;
			if (b % 2 == 0) {
				SetConsoleTextAttribute(hConsole, 14);
				gotoxy(b * 7 + 3, a * 4 + 2);
				printf("X");
			}
			else {
				SetConsoleTextAttribute(hConsole, 14);
				gotoxy(b * 7 + 3, a * 4 + 4);
				printf("X");
			}
		}
		{//cell_new
			cp.x = fs.height - a - 1;
			cp.y = b;
			cp = cell_new(cp);
			a = fs.height - 1 - cp.y;
			b = cp.x;
			psn_of_Cell_harif[cp.y][cp.x] = 0;
			if (b % 2 == 0) {
				SetConsoleTextAttribute(hConsole, 13);
				gotoxy(b * 7 + 3, a * 4 + 2);
				printf("X");
			}
			else {
				SetConsoleTextAttribute(hConsole, 13);
				gotoxy(b * 7 + 3, a * 4 + 4);
				printf("X");
			}
		}
		Update_Screen();
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(0, fs.height * 4 + 4);
		k = show_Menu_in_multi();
		if (k == -1)
			return -1;
	}


	return 0;
}
