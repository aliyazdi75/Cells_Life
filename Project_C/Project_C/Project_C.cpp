unsigned char Energy_Cell_harif[100][100];
int psn_of_Cell_harif[15][15];


#include "Cells.h"
#include "Multi_Player.h"

void clrscr();
void gotoxy(int x, int y);
int randn(int m, int n);
void print_square(int x, int y, int k);
int Print_Screen(void);
int Update_Screen();
int Load_map();
int move_cell(int d, int b, int c);
int save_game();
int Allowed_block();
int split_cell();
int boost_energy();
int show_MoveMenu();
int show_MainMenu();
int select_cell();
int show_Menu();
int Load_menu_map();
int New_Game();
int Map_Editor();
int move_cell_harif(int d, int xm, int ym);
int boost_energy_in_multi();
int show_MoveMenu_in_multi();
int show_MainMenu_in_multi();
int select_cell_in_multi();
int show_Menu_in_multi();
int paly_multi_player();

int main(void) {

	//Final Project

a:	srand(time(NULL));

	int i, j, k;
	char c;

	clrscr();
	gotoxy(0, 0);
	for (j = 0;j < 4 * fs.height + 6;j++) {
		for (i = 0;i < 60;i++)
			printf(" ");
		printf("\n");
	}
	gotoxy(0, 0);

	printf("[1] Load\n[2] New single player game\n[3] New Multiplayer game\n[4] Map Editor\n[5] Exit\n");

b:	c = getch();

	if (c == 49) { //Load
		clrscr();
		k = Load_menu_map();
		clrscr();
		if (k == -1)
			goto a;
	}
	else if (c == 50) { //New single player game
		clrscr();
		printf("Enter cells number: ");
		scanf("%d", &xn);
		clrscr();
		k = New_Game();
		if (k == -1)
			goto a;
	}
	else if (c == 51) { //New Multiplayer game
		clrscr();
		q++;
		k = paly_multi_player();
		clrscr();
		if (k == -1)
			goto a;
	}
	else if (c == 52) { //Map Editor
		k = Map_Editor();
		clrscr();
		if (k == -1)
			goto a;
	}
	else if (c == 53) {//Exit
		exit(0);
	}
	else {
		goto b;
	}

	return 0;
}

int Load_map() {

	int i, j, k, a, b;
	char c, inname[30];
	FILE *fp;

	clrscr();
	gotoxy(0, 0);
	printf("How:\n[1] Text\n[2] Binary");
a:	c = getch();

	if (c == 49) { //Text
		clrscr();
		gotoxy(0, 0);
		printf("Enter Your Map Name To Open (WITH NO FORMAT): ");
		scanf("%s", inname);
		strcat(inname, ".txt");
		fp = fopen(inname, "r+");
		if (fp == NULL) {
			clrscr();
			printf("Cannot open file, Try again with Enter!\n");
			getch();
			return -1;
		}
		clrscr();

		fgets(arr, 50, fp);
		fscanf(fp, "[%d*%d]", &fs.width, &fs.height);

		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell[j][i] = -1;

		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell_harif[j][i] = -1;

		fgets(arr, 50, fp);
		fgets(arr, 50, fp);
		fgets(arr, 50, fp);
		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				for (k = 0;k < 10;k++)
					arr2[k] = 0;
				a = fs.height - j - 1;
				fscanf(fp, "[(%d,%d) = %d, %s", &i, &j, &Energy_Cell[a][i * 4], arr2);
				if (strcmp(arr2, "Source]") == 0)
					Block_Cell[a][i] = '1';
				else if (strcmp(arr2, "Split]") == 0)
					Block_Cell[a][i] = '2';
				else if (strcmp(arr2, "Wall]") == 0)
					Block_Cell[a][i] = '3';
				else if (strcmp(arr2, "Normal]") == 0)
					Block_Cell[a][i] = '4';
			fgets(arr, 50, fp);
			}
		}
		fgets(arr, 50, fp);
		fscanf(fp, "%d", &x1);
		fgets(arr, 50, fp);
		fgets(arr, 60, fp);
		for (k = 0;k < x1;k++) {
			fscanf(fp, "[(%d,%d", &i, &j);
			fscanf(fp, ") = %d]", &psn_of_Cell[j][i]);
			fgets(arr, 50, fp);
		}

		fclose(fp);
	}
	else if (c == 50) { //Binary
		clrscr();
		gotoxy(0, 0);
		printf("Enter Your Map Name To Open (WITH NO FORMAT): ");
		scanf("%s", inname);
		strcat(inname, ".bin");
		fp = fopen(inname, "r+b");
		if (fp == NULL) {
			clrscr();
			printf("Cannot open file, Try again with Enter!\n");
			getch();
			return -1;
		}
		clrscr();

		fread(&fs, sizeof(fs), 1, fp);

		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell[j][i] = -1;

		for (j = fs.height - 1;j >= 0;j--)
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell_harif[j][i] = -1;

		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				a = fs.height - 1 - j;
				fread(&Energy_Cell[a][i * 4], 4, 1, fp);
				fread(&Block_Cell[a][i], 1, 1, fp);
			}
		}
		fread(&x1, sizeof(int), 1, fp);
		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				fread(&psn_of_Cell[j][i], sizeof(int), 1, fp);
			}
		}
		fclose(fp);
	}
	else {
		goto a;
	}

	if (xn < x1 && xn != 0) {
		return -2;
	}

	if (x1 > 1 && xn == 0 && q == 1)
		return 0;

	Update_Screen();

	return 0;
}
int show_Menu() {

a: char c;
	int i, j;

	gotoxy(0, fs.height * 4 + 4);

	printf("[1] Select a cell\n[2] Save\n[3] Return\n");

b:	c = getch();

	if (c == 49) { //Select a cell
		select_cell();
		goto a;
	}
	else if (c == 50) { //Save
		save_game();
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
int Load_menu_map() {

	int k;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	k = Load_map();
	if (k == -1)
		return -1;
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, fs.height * 4 + 4);
	k = show_Menu();
	if (k == -1)
		return -1;

	return 0;
}
int New_Game() {

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
		if (k == -1)
			return -1;
		if (k == -2) {
			clrscr();
			printf("Your cell number is less than your selection map's cells, Try again with more cell number by Enter!");
			getch();
			return -1;
		}
	}
	else {
		goto a;
	}

	if (xn < fs.height*fs.width - cnt_wall) {
		for (k = x1;k < xn;k++) {
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
		}
		Update_Screen();
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(0, fs.height * 4 + 4);
		k = show_Menu();
		if (k == -1)
			return -1;
	}
	else {
		SetConsoleTextAttribute(hConsole, 15);
		clrscr();
		printf("Please select a correct number!");
		return -1;
	}

	return 0;
}




//What to do :
