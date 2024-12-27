#include <stdio.h>
#include <locale.h>

#define SIZE 10
#define INF 10000

int weights[SIZE][SIZE] = {
    {1, 1, 2, 1, 3, 2, 1, 1, 1, 1},
    {1, -1, -1, -1, -1, -1, -1, 1, 1, 1},
    {1, -1, 2, 2, 1, 1, -1, 1, 1, 1},
    {1, -1, 1, -1, -1, 3, -1, 1, 1, 1},
    {1, -1, 2, -1, 1, 1, -1, 1, 1, 1},
    {1, 1, 1, -1, 1, -1, -1, 2, 1, 1},
    {1, -1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, -1, -1, -1, -1, -1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, -1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 3, 1, 1}
};

//�����, ����, �����, ������, ���������
int dir[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1,1}, {1, -1}, {-1, 1}, {-1, -1} };

//�������� ����������
int dist[SIZE][SIZE];

//�������� ���������� ������
int prevX[SIZE][SIZE];
int prevY[SIZE][SIZE];

// ������� ��� �������� ��������� � ���������� ������
int queueX[SIZE * SIZE];
int queueY[SIZE * SIZE];
int queueCost[SIZE * SIZE];
int queueSize = 0;

//������� �������� � ������� (� ����������� �� ����������� ���������)
void enqueue(int x, int y, int cost) {
    int i = queueSize;
    queueX[queueSize] = x;
    queueY[queueSize] = y;
    queueCost[queueSize] = cost;
    queueSize++;

    // ���������� �� ����������� ���������
    while (i > 0 && queueCost[i] < queueCost[i - 1]) {
        // ������ ������� ��������
        int tmpX = queueX[i], tmpY = queueY[i], tmpCost = queueCost[i];
        queueX[i] = queueX[i - 1];
        queueY[i] = queueY[i - 1];
        queueCost[i] = queueCost[i - 1];
        queueX[i - 1] = tmpX;
        queueY[i - 1] = tmpY;
        queueCost[i - 1] = tmpCost;
        i--;
    }
}

// ������� ���������� �������� � ���������� ���������� �� �������
void dequeue(int* x, int* y, int* cost) {
    *x = queueX[0];
    *y = queueY[0];
    *cost = queueCost[0];

    // �������� ���������� �������� �����
    for (int i = 0; i < queueSize - 1; i++) {
        queueX[i] = queueX[i + 1];
        queueY[i] = queueY[i + 1];
        queueCost[i] = queueCost[i + 1];
    }
    queueSize--;
}

// ������� ������������� ������� ���������� � ���������� ������
void initDist() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dist[i][j] = INF; // �������� ��� ���������� ����������
            prevX[i][j] = -1; // -1 ��������, ��� ��� ���������� ������
            prevY[i][j] = -1;
        }
    }
}

// ������� ������ ����
void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == -1) {
                printf(" # ");
            }
            else if (grid[i][j] == INF) {
                printf(" . ");
            }
            else {
                printf("%2d ", grid[i][j]);
            }
        }
        printf("\n");
    }
}

// �������� ��������
int dijkstra(int startX, int startY, int finishX, int finishY) {
    initDist();  // �������������� ����������
    dist[startX][startY] = 0; 
    enqueue(startX, startY, 0);  // ��������� ��������� ����� � �������

    while (queueSize > 0) {
        int x, y, currentCost;
        dequeue(&x, &y, &currentCost);

        // �������� ������
        if (x == finishX && y == finishY) {
            return 1;
        }

        // ��� ��������� ����������� ��������
        for (int i = 0; i < 8; i++) {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && weights[nx][ny] != -1) {
                int newCost = currentCost + weights[nx][ny];

                //����� �������� ���� �� ������
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    prevX[nx][ny] = x;  //���������� ����������
                    prevY[nx][ny] = y;
                    enqueue(nx, ny, newCost);  //����� ������ � �������
                }
            }
        }
    }
    return 0;
}

void findPath(int startX, int startY, int finishX, int finishY, int grid[SIZE][SIZE]) {
    int x = finishX;
    int y = finishY;

    int pathX[SIZE * SIZE];
    int pathY[SIZE * SIZE];
    int pathLength = 0;

    while (x != -1 && y != -1) {
        pathX[pathLength] = x;
        pathY[pathLength] = y;
        pathLength++;
        int tempX = prevX[x][y];
        int tempY = prevY[x][y];
        x = tempX;
        y = tempY;
    }

    for (int i = 0; i < pathLength; i++) {
        grid[pathX[i]][pathY[i]] = '+';
    }
    printf("����� � ���������� ����:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == '+') {
                printf(" + ");
            }
            else if (grid[i][j] == INF) {
                printf(" . ");
            }
            else {
                printf("%2d ", grid[i][j]);
            }
        }
        printf("\n");
    }

    printf("�������� ���� �������� %d ������\n", pathLength);
}


int main() {
    setlocale(LC_ALL, "Rus");
    int startX = 0, startY = 0;
    int finishX = 9, finishY = 9;

    printf("����� ��������� �����:\n");
    printGrid(weights);

    //��������� ��������
    if (dijkstra(startX, startY, finishX, finishY)) {
        printf("\n���������� ���� ������!\n");
        printf("\n����� ���������� :\n");
        printGrid(dist);

        // �������������� � ����� ����������� ����
        printf("\n���� �� ������ �� �����:\n");
        findPath(startX, startY, finishX, finishY, dist);
    }
    else {
        printf("���� �� ������\n");
    }

    return 0;
}
