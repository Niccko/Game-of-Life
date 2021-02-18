#include <stdio.h>
#include <time.h>
#include <Windows.h>

char** createArray(int wd, int hg) {
	char** field = (char**)malloc(hg * sizeof(char*));
	for (int i = 0; i < hg; i++) {
		field[i] = (char*)malloc(wd * sizeof(char));
	}
	return field;
}

char** createField(int wd, int hg, int numStart) {
	char** field = createArray(wd, hg);
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			field[i][j] = ' ';
		}
	}
	int n = numStart;
	int x = 0; int y = 0;
	do {
		x = (int)rand() % wd;
		y = (int)rand() % hg;
		if (field[x][y] == ' ') {
			field[x][y] = '*';
			n--;
		}
		
	} while (n > 0);
	return field;

}

void printField(char** field, int wd, int hg) {
	
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			printf("%c ", field[i][j]);
		}
		printf("\n");
	}
	/*for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			if (field[i][j] == '*') {
				printf("%d ", getNeighbours(field, j, i, wd, hg));
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}*/
}

char** copy(char** field, int wd, int hg) {
	char** temp = createArray(wd, hg);
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			temp[i][j] = field[i][j];
		}
	}
	return temp;
}

int compare(char** field1, char** field2,int wd, int hg) {
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			if (field1[i][j] != field2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

char** update(char** field, int wd, int hg) {
	char** temp = copy(field, wd, hg);
	for (int i = 0; i < wd; i++) {
		for (int j = 0; j < hg; j++) {
			int n = getNeighbours(field, i, j,wd,hg);
			if (field[i][j] == '*') {
				if (n < 2 || n>3) {
					temp[i][j] = ' ';
				}
				else {
					temp[i][j] = '*';
				}
			}
			else {
				if (n == 3) {
					temp[i][j] = '*';
				}
				else {
					temp[i][j] = ' ';
				}
			}
		}
	}
	free(field);
	return temp;
}

int getNeighbours(char** field, int x, int y,int wd, int hg) {
	int res = 0;
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++) {
			
			if (field[(wd + x + i) % wd][(hg + y + j) % hg] == '*' && !(i==0 && j==0)) {
				res++;
			}
		}
	}
	return res;
}

int main() {
	srand(time(NULL));
	int wd = 0, hg = 0;
	int conf = 0;
	scanf_s("%d%d%d", &wd, &hg, &conf);

	char** field = createField(wd, hg, conf);

	int iterations = 0;

	while (1) {
		int startTime = time(NULL);
		printField(field, wd, hg);
		char** temp = copy(field, wd, hg);
		
		field = update(field, wd, hg);
		
		
		int n = compare(temp, field, wd, hg);
		free(temp);
		int endTime = time(NULL);
		printf("Iteration count: %d |~ %d ms\n", iterations++,endTime-startTime);
		if (n == 1) break;
		Sleep(1);
		
		system("cls");
	}
	printf("Stable point reached\n");


}