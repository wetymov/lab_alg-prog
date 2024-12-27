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

//вверх, вниз, влево, вправо, диагонали
int dir[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1,1}, {1, -1}, {-1, 1}, {-1, -1} };

//хранение расстояний
int dist[SIZE][SIZE];

//хранение предыдущих клеток
int prevX[SIZE][SIZE];
int prevY[SIZE][SIZE];

// очередь для хранения координат и стоимостей клеток
int queueX[SIZE * SIZE];
int queueY[SIZE * SIZE];
int queueCost[SIZE * SIZE];
int queueSize = 0;

//вставка элемента в очередь (с сортировкой по возрастанию стоимости)
void enqueue(int x, int y, int cost) {
    int i = queueSize;
    queueX[queueSize] = x;
    queueY[queueSize] = y;
    queueCost[queueSize] = cost;
    queueSize++;

    // Сортировка по возрастанию стоимости
    while (i > 0 && queueCost[i] < queueCost[i - 1]) {
        // Меняем местами элементы
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

// Функция извлечения элемента с наименьшей стоимостью из очереди
void dequeue(int* x, int* y, int* cost) {
    *x = queueX[0];
    *y = queueY[0];
    *cost = queueCost[0];

    // Сдвигаем оставшиеся элементы влево
    for (int i = 0; i < queueSize - 1; i++) {
        queueX[i] = queueX[i + 1];
        queueY[i] = queueY[i + 1];
        queueCost[i] = queueCost[i + 1];
    }
    queueSize--;
}

// Функция инициализации массива расстояний и предыдущих клеток
void initDist() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dist[i][j] = INF; // Начально все расстояния бесконечны
            prevX[i][j] = -1; // -1 означает, что нет предыдущей клетки
            prevY[i][j] = -1;
        }
    }
}

// Функция вывода поля
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

// Алгоритм Дейкстры
int dijkstra(int startX, int startY, int finishX, int finishY) {
    initDist();  // Инициализируем расстояния
    dist[startX][startY] = 0; 
    enqueue(startX, startY, 0);  // Добавляем стартовую точку в очередь

    while (queueSize > 0) {
        int x, y, currentCost;
        dequeue(&x, &y, &currentCost);

        // достигли финиша
        if (x == finishX && y == finishY) {
            return 1;
        }

        // все возможные направления движения
        for (int i = 0; i < 8; i++) {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && weights[nx][ny] != -1) {
                int newCost = currentCost + weights[nx][ny];

                //более короткий путь до клетки
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    prevX[nx][ny] = x;  //предыдущие координаты
                    prevY[nx][ny] = y;
                    enqueue(nx, ny, newCost);  //новая клетка в очередь
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
    printf("Сетка с отмеченным путём:\n");
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

    printf("ИТОГОВЫЙ ПУТЬ СОСТАВИЛ %d КЛЕТОК\n", pathLength);
}


int main() {
    setlocale(LC_ALL, "Rus");
    int startX = 0, startY = 0;
    int finishX = 9, finishY = 9;

    printf("Сетка начальных весов:\n");
    printGrid(weights);

    //алгоритма Дейкстры
    if (dijkstra(startX, startY, finishX, finishY)) {
        printf("\nКратчайший путь найден!\n");
        printf("\nСетка расстояний :\n");
        printGrid(dist);

        // Восстановление и вывод кратчайшего пути
        printf("\nПуть от начала до конца:\n");
        findPath(startX, startY, finishX, finishY, dist);
    }
    else {
        printf("Путь не найден\n");
    }

    return 0;
}
