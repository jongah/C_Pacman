#include "Pacman.h"
struct creature{
	int x;
	int y;
	int way;
	int check;
};


char map[13][51] = {
	{"111111111111111111111111111111111111111111111111111"},
	{"1g33133333333333311333333333333333333313331333133w1"},
	{"132333232222232131132311132222232212233323332333231"},
	{"132222232223332133332311132111232323231212132323231"},
	{"132333232222232222232222232222232323232111232333231"},
	{"133313333333133311133333331333333333333333333313331"},
	{"1311111313131313311311131s1311131131131111131313131"},
	{"133313331333331133333333133333333333333333333333331"},
	{"132333232222231113232222232222232212232222232212231"},
	{"132121233322233333232333332333232323232223332222231"},
	{"132232232222232222232222232323232323232222233323331"},
	{"1o33333333333311111333333333133333333333133313331t1"},
	{"111111111111111111111111111111111111111111111111111"}
};
char map_Play[13][51] = {
	{"111111111111111111111111111111111111111111111111111"},
	{"133313333333333331133333333333333333331333133313331"},
	{"132333232222232131132311132222232212233323332333231"},
	{"132222232223332133332311132111232323231212132323231"},
	{"132333232222232222232222232222232323232111232333231"},
	{"133313333333133311133333331333333333333333333313331"},
	{"131111131313131331131113131311131131131111131313131"},
	{"133313331333331133333333133333333333333333333333331"},
	{"132333232222231113232222232222232212232222232212231"},
	{"132121233322233333232333332333232323232223332222231"},
	{"132232232222232222232222232323232323232222233323331"},
	{"133333333333331111133333333313333333333313331333131"},
	{"111111111111111111111111111111111111111111111111111"}
};

void mapSet() {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 51; j++) {
			if (map[i][j] == '3')
				printf("＊");
			else if (map[i][j] == '1')
				printf("□");
			else if (map[i][j] == 's')
				printf("●");
			else if (map[i][j] == 'g')
				printf("◆");
			else if (map[i][j] == 'o')
				printf("★");
			else if (map[i][j] == 't')
				printf("●");
			else if (map[i][j] == 'w')
				printf("§");
			else
				printf("■");
		}
		printf("\n");
	}
}

int keyControl() {
	char key = getch();
	if (key == 'w' || key == 'W')
		return UP;
	else if (key == 's' || key == 'S')
		return DOWN;
	else if (key == 'd' || key == 'D')
		return RIGHT;
	else if (key == 'a' || key == 'A')
		return LEFT;
	else if (key == ' ')
		return PICK;
}

void titleText() {

}

void menuPick(int pic) {
	if (pic == 1)
		exit(0);
	else
		system("cls");
}

int menuSet() {
	int x = 45;
	int y = 13;
	gotoxy(x + 2, y);
	printf("게임시작★");
	gotoxy(x + 3, y + 1);
	printf("게임끝");
	gotoxy(x, y);
	printf(">");
	while (1) {
		int k = keyControl();
		switch (k) {
		case UP:
			if (y > 20) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf(">");
			}
			break;
		case DOWN:
			if (y < 21) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf(">");
			}
			break;
		case PICK:
			return y - 15;
		}
	}
}

int count = 0;

int xyPick(struct creature *c) {
	int temp_x = c->x;
	int temp_y = c->y;
	switch (c->way) {
	case UP:
		--temp_y;
		break;
	case DOWN:
		++temp_y;
		break;
	case RIGHT:
		temp_x += 2;
		break;
	case LEFT:
		temp_x -= 2;
		break;
	}
	char mapdata = map_Play[temp_y][temp_x / 2];
	if (mapdata == '1' || mapdata == '2') {
	}
	else {
		gotoxy(c->x, c->y);
		if (c->check == 2)
			printf("＊");
		else
			printf("  ");
		c->x = temp_x;
		c->y = temp_y;
		gotoxy(c->x, c->y);
		if (c->check == 1) {
			if(mapdata == '3')
				map_Play[c->y][c->x / 2] = '0';
			printf("○");
		}
		switch (count%5) {
		case 1:
			printf("●"); break;
		case 2:
			printf("§"); break;
		case 3:
			printf("★"); break;
		case 4:
			printf("◆"); break;
		}
		//if (c->check == 1 && mapdata == '3') {
		//	map_Play[temp_y][temp_x / 2] = '0';
		//}
		//gotoxy(c->x, c->y);
		//if (c->check == 2) {
		//	printf("＊");
		//}
		//else {
		//	printf("  ");
		//}
		//c->x = temp_x;
		//c->y = temp_y;
		//gotoxy(c->x, c->y);
		//if (c->check == 1)
		//	printf("○");
		//else
		//	printf("◆");
	}
}

void wayCheck(struct creature *c) {
	if (c->check == 1) {
		if (kbhit() == 1)
			c->way = keyControl();
	}
	else {
		c->way = gostCheck(c);
	}
	xyPick(c);
}

int gostWay(int y, int x) {
	if (map_Play[y][x] == '0')
		return 1;
	else if(map_Play[y][x] == '3')
		return 2;
	else
		return 0;
}
int gostCheck(struct creature* c) {
	c->check = 0;
	int way[4] = { 0 };
	int count = 0;
	int x, y;
	x = c->x / 2;
	y = c->y;

	way[0] = gostWay(y - 1, x);
	way[1] = gostWay(y + 1, x);
	way[2] = gostWay(y, x + 1);
	way[3] = gostWay(y, x - 1);
	
	for (int i = 0; i < 4; i++) {
		if (way[i] >= 1)
			count++;
	}
	int temp_way = 0;
	if (c->way == UP)
		temp_way = DOWN;
	else if (c->way == DOWN)
		temp_way = UP;
	else if (c->way == RIGHT)
		temp_way = LEFT;
	else if (c->way == LEFT)
		temp_way = RIGHT;
	
	//빈칸 고르기
	int blank[3] = {5,5,5};

	for (int i = 0; i < 4; i++) {
		if (way[i] >= 1) {
			for (int j = 0; j < 3; j++) {
				if (blank[j] == 5) {
					blank[j] = i;
					break;
				}
			}
		}
	}

	if (count == 1) {
		if (way[temp_way] == 2)
			c->check = 2;
		return temp_way;
	}
	else if (count == 2) {
		if (blank[0] != temp_way) {
			if (way[blank[0]] == 2)
				c->check = 2;
			return blank[0];
		}	
		else {
			if (way[blank[1]] == 2)
				c->check = 2;
			return blank[1];
		}
			
	}
	else {
		srand(time(NULL));
		while (1) {
			int random = rand() % 3;
			if (blank[random] != temp_way && blank[random] != 5) {
				if (way[blank[random]] == 2)
					c->check = 2;
				return blank[random];
			}	
		}
	}
}

struct creature pacman = {
	.x = 50,
	.y = 6,
	.way = 1,
	.check = 1
};

void move() {
	struct creature pacman;
	pacman.x = 50;
	pacman.y = 6;
	pacman.way = 1;
	pacman.check = 1;

	struct creature gost_1;
	gost_1.x = 98;
	gost_1.y = 1;
	gost_1.way = 0;
	gost_1.check = 0;

	struct creature gost_2;
	gost_2.x = 2;
	gost_2.y = 1;
	gost_2.way = 0;
	gost_2.check = 0;

	struct creature gost_3;
	gost_3.x = 2;
	gost_3.y = 11;
	gost_3.way = 0;
	gost_3.check = 0;

	struct creature gost_4;
	gost_4.x = 98;
	gost_4.y = 11;
	gost_4.way = 1;
	gost_4.check = 0;

	while (1) {
		wayCheck(&pacman);
		count += 1;
		wayCheck(&gost_1);
		count += 1;
		wayCheck(&gost_2);
		count += 1;
		wayCheck(&gost_3);
		count += 1;
		wayCheck(&gost_4);
		count += 1;
		Sleep(100);
	}
}