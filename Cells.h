#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <string.h>

unsigned char Energy_Cell[100][100], Block_Cell[100][100];
char arr[60], arr2[60];
int cnt_source, cnt_split, cnt_wall, cnt_normal, xn, x1, x, y, q, psn_of_Cell[15][15], rand_use[6], s, score1, score2;

struct file_size {
	unsigned int width;
	unsigned int height;
};
struct file_size fs;

void clrscr() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // gets the window handle
	COORD coord = { 0, 0 }; // sets coordinates to 0,0
	DWORD count;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi); // gets the buffer info (screen)

												// fill all characters as ' ' (empty the screen)
	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

	// resets the cursor position
	SetConsoleCursorPosition(hStdOut, coord);
}
void gotoxy(int x, int y) {
	COORD coord; // coordinates
	coord.X = x; coord.Y = y; // X and Y coordinates 75 15
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int randn(int m, int n) {
	int ir = rand();
	double fr = (n - m) *(ir + 1) / (RAND_MAX + 2.0) + m;
	return (fr);
}
void print_square(int x, int y, int k) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, k);
	gotoxy(x, y);
	printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	SetConsoleTextAttribute(hConsole, 15);
	printf("%c", 219);
	SetConsoleTextAttribute(hConsole, k);
	gotoxy(x, y + 1);
	printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	SetConsoleTextAttribute(hConsole, 15);
	printf("%c", 219);
	SetConsoleTextAttribute(hConsole, k);
	gotoxy(x, y + 2);
	printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	SetConsoleTextAttribute(hConsole, 15);
	printf("%c", 219);
	SetConsoleTextAttribute(hConsole, k);
	gotoxy(x, y + 3);
	SetConsoleTextAttribute(hConsole, 15);
	printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
}
int Print_Screen(void) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, j, k, kx = fs.width - 1, ky = 0;

	for (j = fs.height - 1;j >= 0;j--) {
		for (i = fs.width - 1;i >= 0;i--) {
			if (i % 2 == 0) {
				if (Block_Cell[j][i] == 0) {
					k = 119;
					print_square(i * 7 + 1, j * 4 + 1, k);
				}
				if (Block_Cell[j][i] == '1') {
					k = 9;
					print_square(i * 7 + 1, j * 4 + 1, k);
					if (Energy_Cell[j][i * 4] >= 0) {
						SetConsoleTextAttribute(hConsole, 159);
						gotoxy(i * 7 + 1, j * 4 + 3);
						printf("%d", Energy_Cell[j][i * 4]);
						SetConsoleTextAttribute(hConsole, 15);
					}
				}
				else if (Block_Cell[j][i] == '2') {
					k = 10;
					print_square(i * 7 + 1, j * 4 + 1, k);
				}
				else if (Block_Cell[j][i] == '3') {
					k = 12;
					print_square(i * 7 + 1, j * 4 + 1, k);
				}
				else if (Block_Cell[j][i] == '4') {
					k = 11;
					print_square(i * 7 + 1, j * 4 + 1, k);
				}
				if (j == fs.height - 1) {
					gotoxy(i * 7 + 4, j * 4 + 5);
					printf("%d", kx--);
				}
				if (i == 0) {
					gotoxy(i * 7, j * 4 + 2);
					printf("%d", ky++);
				}
			}
			else {
				if (Block_Cell[j][i] == 0) {
					k = 119;
					print_square(i * 7 + 1, j * 4 + 3, k);
				}
				if (Block_Cell[j][i] == '1') {
					k = 9;
					print_square(i * 7 + 1, j * 4 + 3, k);
					if (Energy_Cell[j][i * 4] >= 0) {
						SetConsoleTextAttribute(hConsole, 159);
						gotoxy(i * 7 + 1, j * 4 + 5);
						printf("%d", Energy_Cell[j][i * 4]);
						SetConsoleTextAttribute(hConsole, 15);
					}
				}
				else if (Block_Cell[j][i] == '2') {
					k = 10;
					print_square(i * 7 + 1, j * 4 + 3, k);
				}
				else if (Block_Cell[j][i] == '3') {
					k = 12;
					print_square(i * 7 + 1, j * 4 + 3, k);
				}
				else if (Block_Cell[j][i] == '4') {
					k = 11;
					print_square(i * 7 + 1, j * 4 + 3, k);
				}
				if (j == fs.height - 1) {
					gotoxy(i * 7 + 4, j * 4 + 7);
					printf("%d", kx--);
				}
				if (i == 0) {
					gotoxy(i * 7, j * 4 + 3);
					printf("%d", ky++);
				}
			}
		}
	}

	for (i = 0;i < 4;i++) {
		if (i == 0)
			SetConsoleTextAttribute(hConsole, 9);
		else if (i == 1)
			SetConsoleTextAttribute(hConsole, 10);
		else if (i == 2)
			SetConsoleTextAttribute(hConsole, 12);
		else if (i == 3)
			SetConsoleTextAttribute(hConsole, 11);
		gotoxy(fs.width * 7 + 3, i * 4 + 2);
		printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
		gotoxy(fs.width * 7 + 3, i * 4 + 3);
		printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
		gotoxy(fs.width * 7 + 3, i * 4 + 4);
		printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
		gotoxy(fs.width * 7 + 3, i * 4 + 5);
		if (i == 0)
			printf("Source");
		else if (i == 1)
			printf("Split");
		else if (i == 2)
			printf("Wall");
		else if (i == 3)
			printf("Normal");
	}

	return 0;
}
int Update_Screen() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, j, a;

	clrscr();
	Print_Screen();

	score1 = 0;
	for (j = fs.height - 1;j >= 0;j--)
		for (i = fs.width - 1;i >= 0;i--)
			if (psn_of_Cell[j][i] >= 0)
				score1 += psn_of_Cell[j][i];

	score2 = 0;
	for (j = fs.height - 1;j >= 0;j--)
		for (i = fs.width - 1;i >= 0;i--)
			if (psn_of_Cell_harif[j][i] >= 0)
				score2 += psn_of_Cell_harif[j][i];

	SetConsoleTextAttribute(hConsole, 15);
	if (q == 0) {
		gotoxy(fs.width * 8 + 6, 2);
		printf("Player Score: %d", score1);
	}
	else {
		gotoxy(fs.width * 8 + 6, 2);
		printf("1st Player Score: %d", score1);
		gotoxy(fs.width * 8 + 6, 3);
		printf("2nd Player Score: %d", score2);
	}
	for (j = fs.height - 1;j >= 0;j--) {
		for (i = fs.width - 1;i >= 0;i--) {
			if (psn_of_Cell[j][i] >= 0) {
				if (i % 2 == 0) {
					a = fs.height - 1 - j;
					SetConsoleTextAttribute(hConsole, 14);
					gotoxy(i * 7 + 3, a * 4 + 2);
					printf("X");
				}
				else {
					a = fs.height - 1 - j;
					SetConsoleTextAttribute(hConsole, 14);
					gotoxy(i * 7 + 3, a * 4 + 4);
					printf("X");
				}
			}
		}
	}
	for (j = fs.height - 1;j >= 0;j--) {
		for (i = fs.width - 1;i >= 0;i--) {
			if (psn_of_Cell_harif[j][i] >= 0) {
				if (i % 2 == 0) {
					a = fs.height - 1 - j;
					SetConsoleTextAttribute(hConsole, 13);
					gotoxy(i * 7 + 3, a * 4 + 2);
					printf("X");
				}
				else {
					a = fs.height - 1 - j;
					SetConsoleTextAttribute(hConsole, 13);
					gotoxy(i * 7 + 3, a * 4 + 4);
					printf("X");
				}
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 110);
	for (j = fs.height - 1;j >= 0;j--)
		for (i = fs.width - 1;i >= 0;i--)
			if (psn_of_Cell[j][i] >= 0) {
				if (i % 2 == 0) {
					a = fs.height - 1 - j;
					gotoxy(i * 7 + 1, a * 4 + 1);
					printf("%d", psn_of_Cell[j][i]);
				}
				else {
					a = fs.height - 1 - j;
					gotoxy(i * 7 + 1, a * 4 + 3);
					printf("%d", psn_of_Cell[j][i]);
				}
			}

	for (j = fs.height - 1;j >= 0;j--)
		for (i = fs.width - 1;i >= 0;i--)
			if (psn_of_Cell_harif[j][i] >= 0) {
				if (i % 2 == 0) {
					a = fs.height - 1 - j;
					gotoxy(i * 7 + 1, a * 4 + 1);
					printf("%d", psn_of_Cell_harif[j][i]);
				}
				else {
					a = fs.height - 1 - j;
					gotoxy(i * 7 + 1, a * 4 + 3);
					printf("%d", psn_of_Cell_harif[j][i]);
				}
			}

	SetConsoleTextAttribute(hConsole, 15);

	return 0;
}
int move_cell(int d, int b, int c) {

	int i, j, a = fs.height - 1 - y;

	if (d == 1) { //North psn_of_Cell[y][x]
		if (y + 1 == fs.height || Block_Cell[a - 1][x] == '3' || psn_of_Cell[y + 1][x] >= 0) {
			return -1;
		}
		if (b == 0) {
			psn_of_Cell[y + 1][x] = psn_of_Cell[y][x];
			psn_of_Cell[y][x] = -1;
		}
		else if (b == 1 && c == 1) {
			psn_of_Cell[y + 1][x] = 40;
			psn_of_Cell[y][x] = 40;
		}
		else if (b == 1 && c == 2) {
			psn_of_Cell[y + 1][x] = 40;
			psn_of_Cell[y][x] = -1;
		}
	}
	else if (d == 2) { //South psn_of_Cell[y][x]
		if (y - 1 == -1 || Block_Cell[a + 1][x] == '3' || psn_of_Cell[y - 1][x] >= 0) {
			return -1;
		}
		if (b == 0) {
			psn_of_Cell[y - 1][x] = psn_of_Cell[y][x];
			psn_of_Cell[y][x] = -1;
		}
		else if (b == 1 && c == 1) {
			psn_of_Cell[y - 1][x] = 40;
			psn_of_Cell[y][x] = 40;
		}
		else if (b == 1 && c == 2) {
			psn_of_Cell[y - 1][x] = psn_of_Cell[y][x];
			psn_of_Cell[y][x] = -1;
		}
	}
	if (x % 2 == 0) {
		if (d == 3) { //Northeast psn_of_Cell[y][x]
			if (y + 1 == fs.height || x + 1 == fs.width || Block_Cell[a - 1][x + 1] == '3' || psn_of_Cell[y + 1][x + 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y + 1][x + 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y + 1][x + 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y + 1][x + 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 4) { //Northwest psn_of_Cell[y][x]
			if (y + 1 == fs.height || x - 1 == -1 || Block_Cell[a - 1][x - 1] == '3' || psn_of_Cell[y + 1][x - 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y + 1][x - 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y + 1][x - 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y + 1][x - 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 5) { //Southeast psn_of_Cell[y][x]
			if (x + 1 == fs.width || Block_Cell[a][x + 1] == '3' || psn_of_Cell[y][x + 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y][x + 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y][x + 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y][x + 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 6) { //Southwest psn_of_Cell[y][x]
			if (x - 1 == -1 || Block_Cell[a][x - 1] == '3' || psn_of_Cell[y][x - 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y][x - 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y][x - 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y][x - 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
	}
	else {
		if (d == 3) { //Northeast psn_of_Cell[y][x]
			if (x + 1 == fs.width || Block_Cell[a][x + 1] == '3' || psn_of_Cell[y][x + 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y][x + 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y][x + 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y][x + 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 4) { //Northwest psn_of_Cell[y][x]
			if (x - 1 == -1 || Block_Cell[a][x - 1] == '3' || psn_of_Cell[y][x - 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y][x - 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y][x - 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y][x - 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 5) { //Southeast psn_of_Cell[y][x]
			if (y - 1 == -1 || x + 1 == fs.width || Block_Cell[a + 1][x + 1] == '3' || psn_of_Cell[y - 1][x + 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y - 1][x + 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y - 1][x + 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y - 1][x + 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
		else if (d == 6) { //Southwest psn_of_Cell[y][x]
			if (y - 1 == -1 || Block_Cell[a + 1][x - 1] == '3' || psn_of_Cell[y - 1][x - 1] >= 0) {
				return -1;
			}
			if (b == 0) {
				psn_of_Cell[y - 1][x - 1] = psn_of_Cell[y][x];
				psn_of_Cell[y][x] = -1;
			}
			else if (b == 1 && c == 1) {
				psn_of_Cell[y - 1][x - 1] = 40;
				psn_of_Cell[y][x] = 40;
			}
			else if (b == 1 && c == 2) {
				psn_of_Cell[y - 1][x - 1] = 40;
				psn_of_Cell[y][x] = -1;
			}
		}
	}

	return 0;
}
int save_game() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, j, a;
	char c, outname[30];
	FILE *fp;

	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, fs.height * 4 + 4);
	printf("How:             \n[1] Text\n[2] Binary");
a:	c = getch();
	if (c == 49) { //Text
		gotoxy(0, fs.height * 4 + 4);
		printf("Enter Your File Name To Save (WITH NO FORMAT):\n          \n          ");
		gotoxy(47, fs.height * 4 + 4);
		scanf("%s", outname);
		strcat(outname, ".txt");
		fp = fopen(outname, "w");
		if (fp == NULL) {
			printf("Cannot create file\n");
			return -1;
		}
		fprintf(fp, "Map Size [Width*Height]:\n");
		fprintf(fp, "[%d*%d]\n", fs.width, fs.height);
		fprintf(fp, "Blocks information [Psition(X,Y) = Energy, Type]:\n");
		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				a = fs.height - 1 - j;
				fprintf(fp, "[(%d,%d) = %d, ", i, j, int(Energy_Cell[a][i * 4]));
				if (Block_Cell[a][i] == '1')
					fprintf(fp, "Source]\n");
				else if (Block_Cell[a][i] == '2')
					fprintf(fp, "Split]\n");
				else if (Block_Cell[a][i] == '3')
					fprintf(fp, "Wall]\n");
				else if (Block_Cell[a][i] == '4')
					fprintf(fp, "Normal]\n");
			}
		}
		fprintf(fp, "Cell number:\n");

		if (x1 == 0) {
			for (j = fs.height - 1;j >= 0;j--)
				for (i = fs.width - 1;i >= 0;i--)
					if (psn_of_Cell[j][i] >= 0)
						x1++;
		}
		fprintf(fp, "%d\n", x1);

		fprintf(fp, "Cells information [Psition(X,Y) = Energy]:\n");
		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				if (psn_of_Cell[j][i] != -1)
					fprintf(fp, "[(%d,%d) = %d]\n", i, j, psn_of_Cell[j][i]);
			}
		}
		fclose(fp);
	}
	else if (c == 50) { //Binary
		gotoxy(0, fs.height * 4 + 4);
		printf("Enter Your File Name To Save (WITH NO FORMAT):\n          \n          ");
		gotoxy(47, fs.height * 4 + 4);
		scanf("%s", outname);
		strcat(outname, ".bin");
		fp = fopen(outname, "wb");
		if (fp == NULL) {
			printf("Cannot create file\n");
			return -1;
		}
		fwrite(&fs, sizeof(fs), 1, fp);
		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				a = fs.height - 1 - j;
				fwrite(&Energy_Cell[a][i * 4], 4, 1, fp);
				fwrite(&Block_Cell[a][i], 1, 1, fp);
			}
		}

		if (x1 == 0) {
			for (j = fs.height - 1;j >= 0;j--)
				for (i = fs.width - 1;i >= 0;i--)
					if (psn_of_Cell[j][i] >= 0)
						x1++;
		}
		fwrite(&x1, sizeof(int), 1, fp);

		for (i = 0;i < fs.width;i++) {
			for (j = fs.height - 1;j >= 0;j--) {
				fwrite(&psn_of_Cell[j][i], sizeof(int), 1, fp);
			}
		}
		fclose(fp);
	}
	else {
		goto a;
	}
	gotoxy(0, fs.height * 4 + 4);
	for (i = 0;i < 60;i++)
		printf(" ");
	gotoxy(0, fs.height * 4 + 4);

	return 0;
}
int Allowed_block() {

	int a = fs.height - 1 - y;

	s = 0;

	if (y + 1 != fs.height && Block_Cell[a - 1][x] != '3' && psn_of_Cell[y + 1][x] < 0) {
		rand_use[s++] = 1;
	}
	if (y - 1 != -1 && Block_Cell[a + 1][x] != '3' && psn_of_Cell[y - 1][x] < 0) {
		rand_use[s++] = 2;
	}
	if (x % 2 == 0) {
		if (y + 1 != fs.height && x + 1 != fs.width && Block_Cell[a - 1][x + 1] != '3' && psn_of_Cell[y + 1][x + 1] < 0) {
			rand_use[s++] = 3;
		}
		if (y + 1 != fs.height && x - 1 != -1 && Block_Cell[a - 1][x - 1] != '3' && psn_of_Cell[y + 1][x - 1] < 0) {
			rand_use[s++] = 4;
		}
		if (x + 1 != fs.width && Block_Cell[a + 1][x + 1] != '3' && psn_of_Cell[y][x + 1] < 0) {
			rand_use[s++] = 5;
		}
		if (x - 1 != -1 && Block_Cell[a + 1][x - 1] != '3' && psn_of_Cell[y][x - 1] < 0) {
			rand_use[s++] = 6;
		}
	}
	else {
		if (x + 1 != fs.width && Block_Cell[a][x + 1] != '3' && psn_of_Cell[y][x + 1] < 0) {
			rand_use[s++] = 3;
		}
		if (x - 1 != -1 && Block_Cell[a][x - 1] != '3' && psn_of_Cell[y][x - 1] < 0) {
			rand_use[s++] = 4;
		}
		if (y - 1 != -1 && x + 1 != fs.width && Block_Cell[a + 1][x + 1] != '3' && psn_of_Cell[y - 1][x + 1] < 0) {
			rand_use[s++] = 5;
		}
		if (y - 1 != -1 && Block_Cell[a + 1][x - 1] != '3' && psn_of_Cell[y - 1][x - 1] < 0) {
			rand_use[s++] = 6;
		}
	}

	s--;

	return 0;
}
int split_cell() {

	int i, j, r1, r2, k, a = fs.height - 1 - y;

	if (Block_Cell[a][x] == '2') {
		if (psn_of_Cell[y][x] >= 80) {
			Allowed_block();
			if (s >= 1) {
				r1 = rand_use[randn(0, s + 1)];
				r2 = rand_use[randn(0, s + 1)];
				while (r2 == r1)
					r2 = rand_use[randn(0, s + 1)];

				if (r1 == 1)
					k = move_cell(1, 1, 1);
				else if (r1 == 2)
					k = move_cell(2, 1, 1);
				else if (r1 == 3)
					k = move_cell(3, 1, 1);
				else if (r1 == 4)
					k = move_cell(4, 1, 1);
				else if (r1 == 5)
					k = move_cell(5, 1, 1);
				else if (r1 == 6)
					k = move_cell(6, 1, 1);

				if (r2 == 1)
					k = move_cell(1, 1, 2);
				else if (r2 == 2)
					k = move_cell(2, 1, 2);
				else if (r2 == 3)
					k = move_cell(3, 1, 2);
				else if (r2 == 4)
					k = move_cell(4, 1, 2);
				else if (r2 == 5)
					k = move_cell(5, 1, 2);
				else if (r2 == 6)
					k = move_cell(6, 1, 2);
				x1++;
			}
			else {
				printf("Cell can't split, Move this cell & try again by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 100;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				return -1;
			}

		}
		else {
			printf("Cell can't split with less than 80 Energy, Try again diffrent cell by Enter!");
			getch();
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 100;i++)
				printf(" ");
			gotoxy(0, fs.height * 4 + 4);
			return -1;
		}
	}
	else {
		printf("Cell must be in the split block, Try again by Enter!");
		getch();
		gotoxy(0, fs.height * 4 + 4);
		for (i = 0;i < 60;i++)
			printf(" ");
		gotoxy(0, fs.height * 4 + 4);
		return -1;
	}

	return 0;
}
int boost_energy() {

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

	return 0;
}
int show_MoveMenu() {

a :	int i, j, k, a = fs.height - 1 - y;
	char c;

	printf("[1] North\n[2] South\n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n[7] Return\n");

b :	c = getch();

	if (c == 49) { //North psn_of_Cell[y][x]
		k = move_cell(1, 0, 1);
	}
	else if (c == 50) { //South psn_of_Cell[y][x]
		k = move_cell(2, 0, 1);
	}
	else if (c == 51) { //Northeast psn_of_Cell[y][x]
		k = move_cell(3, 0, 1);
	}
	else if (c == 52) { //Northwest psn_of_Cell[y][x]
		k = move_cell(4, 0, 1);
	}
	else if (c == 53) { //Southeast psn_of_Cell[y][x]
		k = move_cell(5, 0, 1);
	}
	else if (c == 54) { //Southwest psn_of_Cell[y][x]
		k = move_cell(6, 0, 1);
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


	return 0;
}
int show_MainMenu() {

a:	int i, j, k;
	char c;

	printf("[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Return\n");

b:	c = getch();

	if (c == 49) { //Move
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		k = show_MoveMenu();
		if (k == -1)
			goto a;
		Update_Screen();
	}
	else if (c == 50) { //Split a cell
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		k = split_cell();
		if (k == -1)
			goto a;
		Update_Screen();
	}
	else if (c == 51) { //Boost energy
		gotoxy(0, fs.height * 4 + 4);
		for (j = 0;j < 4;j++) {
			for (i = 0;i < 60;i++)
				printf(" ");
			printf("\n");
		}
		gotoxy(0, fs.height * 4 + 4);
		k = boost_energy();
		if (k == -1)
			goto a;
		Update_Screen();
	}
	else if (c == 52) { //Return
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
int select_cell() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

a:	int i, j, a, k;

	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, fs.height * 4 + 4);
	printf("Enter a cell cordinate X Y:                       \n              \n            ");
	gotoxy(28, fs.height * 4 + 4);
	scanf("%d %d", &x, &y);
	if (psn_of_Cell[y][x] == -1 || y >= fs.height || x <= -1 || y <= -1 || x >= fs.width) {
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
	k = show_MainMenu();
	if (k == -1) {
		Update_Screen();
	}

	return 0;
}
int Map_Editor() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, j, k, a, c;

	for (i = 0;i < 20;i++)
		for (j = 0;j < 20;j++) {
			Energy_Cell[j][i] = { 0 };
			Block_Cell[j][i] = { 0 };
		}

	{//map size & number of objects
		clrscr();
		printf("Enter size Width Height: ");
		scanf("%d %d", &fs.width, &fs.height);
	a:	a = fs.width*fs.height;
		clrscr();
		int b = 0;
		gotoxy(0, 0);
		printf("Enter The Number of cells: ");
		scanf("%d", &x1);
		if (x1 > a) {
			printf("Wrong Number, Try again by Enter!");
			getch();
			goto a;
		}
		gotoxy(40, 0);
		printf("Block for chosen: %d", a);
		gotoxy(0, 0);
		printf("Enter the number of source block: ");
		scanf("%d", &cnt_source);
		clrscr();
		b += cnt_source;
		if (cnt_source > a) {
			printf("Wrong Number, Try again by Enter!");
			getch();
			goto a;
		}
		a -= cnt_source;
		gotoxy(40, 0);
		printf("Block for chosen: %d", a);
		gotoxy(0, 0);
		printf("Enter the number of split block: ");
		scanf("%d", &cnt_split);
		clrscr();
		b += cnt_split;
		if (cnt_split > a) {
			printf("Wrong Number, Try again by Enter!");
			getch();
			goto a;
		}
		a -= cnt_split;
		gotoxy(40, 0);
		printf("Block for chosen: %d", a);
		gotoxy(0, 0);
		printf("Enter the number of wall block: ");
		scanf("%d", &cnt_wall);
		clrscr();
		b += cnt_wall;
		if (cnt_wall > a) {
			printf("Wrong Number, Try again by Enter!");
			getch();
			goto a;
		}
		a -= cnt_wall;
		cnt_normal = fs.width*fs.height - b;
		printf("%d Other bocks are Normal, DONE by Enter!", cnt_normal);
		getch();
		clrscr();
	}

	{//Located in map
		for (k = cnt_source;k > 0;k--) {//Source
			Print_Screen();
			SetConsoleTextAttribute(hConsole, 15);
		b:	gotoxy(70, fs.height * 4 + 4);
			printf("Block for chosen: %d", k);
			gotoxy(0, fs.height * 4 + 4);
			printf("Enter Location of source block & Energy of block X Y ENERGY: ");
			scanf("%d %d", &i, &j);
			a = fs.height - 1 - j;
			if (a >= fs.height || a < 0 || i >= fs.width || i < 0 || Block_Cell[a][i] != 0) {
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 90;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				printf("Wrong Location, Try again by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 70;i++)
					printf(" ");
				goto b;
			}
			Block_Cell[a][i] = '1';
			scanf("%d", &Energy_Cell[a][i * 4]);
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 70;i++)
				printf(" ");
		}
		for (k = cnt_split;k > 0;k--) {//Split
			Print_Screen();
			SetConsoleTextAttribute(hConsole, 15);
		c:	gotoxy(70, fs.height * 4 + 4);
			printf("Block for chosen: %d", k);
			gotoxy(0, fs.height * 4 + 4);
			printf("Enter Location of split block X Y: ");
			scanf("%d %d", &i, &j);
			a = fs.height - 1 - j;
			if (a >= fs.height || a < 0 || i >= fs.width || i < 0 || Block_Cell[a][i] != 0) {
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 90;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				printf("Wrong Location, Try again by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 70;i++)
					printf(" ");
				goto c;
			}
			Block_Cell[a][i] = '2';
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 70;i++)
				printf(" ");
		}
		for (k = cnt_wall;k > 0;k--) {//Wall
			Print_Screen();
			SetConsoleTextAttribute(hConsole, 15);
		d:	gotoxy(70, fs.height * 4 + 4);
			printf("Block for chosen: %d", k);
			gotoxy(0, fs.height * 4 + 4);
			printf("Enter Location of wall block X Y: ");
			scanf("%d %d", &i, &j);
			a = fs.height - 1 - j;
			if (a >= fs.height || a < 0 || i >= fs.width || i < 0 || Block_Cell[a][i] != 0) {
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 90;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				printf("Wrong Location, Try again by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 70;i++)
					printf(" ");
				goto d;
			}
			Block_Cell[a][i] = '3';
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 70;i++)
				printf(" ");
		}
		for (j = fs.height - 1;j >= 0;j--) {//Normal
			for (i = fs.width - 1;i >= 0;i--) {
				if (Block_Cell[j][i] == 0) {
					Block_Cell[j][i] = '4';
				}
			}
		}
		for (j = fs.height - 1;j >= 0;j--) {
			for (i = fs.width - 1;i >= 0;i--)
				psn_of_Cell[j][i] = -1;
		}
		for (k = x1;k > 0;k--) {//Cells
			for (j = fs.height - 1;j >= 0;j--)
				for (i = fs.width - 1;i >= 0;i--)
					psn_of_Cell_harif[j][i] = -1;
			Update_Screen();
			SetConsoleTextAttribute(hConsole, 15);
		e:	gotoxy(70, fs.height * 4 + 4);
			printf("Block for chosen: %d", k);
			gotoxy(0, fs.height * 4 + 4);
			printf("Enter Location of cells blocks X Y: ");
			scanf("%d %d", &i, &j);
			a = fs.height - 1 - j;
			if (j >= fs.height || j < 0 || i >= fs.width || i < 0 || Block_Cell[a][i] == '3') {
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 90;i++)
					printf(" ");
				gotoxy(0, fs.height * 4 + 4);
				printf("Wrong Location, Try again by Enter!");
				getch();
				gotoxy(0, fs.height * 4 + 4);
				for (i = 0;i < 70;i++)
					printf(" ");
				goto e;
			}
			psn_of_Cell[j][i] = 0;
			gotoxy(0, fs.height * 4 + 4);
			for (i = 0;i < 90;i++)
				printf(" ");
		}
		Update_Screen();
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(70, fs.height * 4 + 4);
	}

	{//Show Menu

	f: char c;

		gotoxy(0, fs.height * 4 + 4);

		printf("[1] Select a cell\n[2] Save\n[3] Return\n");

	g:	c = getch();

		if (c == 49) { //Select a cell
			select_cell();
			goto f;
		}
		else if (c == 50) { //Save
			save_game();
			goto f;
		}
		else if (c == 51) { //Return
			return -1;
		}
		else {
			goto g;
		}
	}

	return 0;
}