#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// вывод двумерного массива
void print2d(vector<vector<int>> arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

// вывод обычного массива
void print(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}

// вычисление расстояния между двумя точками
double getDistance(vector<int> point1, vector<int> point2) {

    // разница координат по x
    int xDiff = point1[0] - point2[0];

    // разница координат по y
    int yDiff = point1[1] - point2[1];

    // формула расстояния между двумя точками
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

// поиск мин суммы расстояний
double findBestSum(vector<vector<int>> redPoints,
                   vector<vector<int>> bluePoints,
                   vector<bool> usedBlue,
                   int redIndex,
                   double currentSum,
                   double minSum) {

    // колво красных точек
    int count = redPoints.size();

    // если текущая сумма уже больше минимальной
    // дальше проверять нет смысла
    if (currentSum >= minSum) {
        return minSum;
    }

    // если все красные точки уже использованы
    if (redIndex == count) {

        // обновляем минимальную сумму
        if (currentSum < minSum) {
            minSum = currentSum;
        }

        return minSum;
    }

    // перебираем все синие точки
    for (int i = 0; i < count; i++) {

        // если синяя точка еще не использована
        if (!usedBlue[i]) {

            // отмечаем как использованную
            usedBlue[i] = true;

            // расстояние между точками
            double dist = getDistance(redPoints[redIndex], bluePoints[i]);

            // новая сумма
            double newSum = currentSum + dist;

            // рекурсивный вызов для следующей красной точки
            double result = findBestSum(
                redPoints,
                bluePoints,
                usedBlue,
                redIndex + 1,
                newSum,
                minSum
            );

            // если нашли лучший вариант
            if (result < minSum) {
                minSum = result;
            }

            // откат изменений назад
            usedBlue[i] = false;
        }
    }

    return minSum;
}

int main() {

    // общее колво точек
    int totalPoints;
    cin >> totalPoints;

    // массив красных точек
    vector<vector<int>> redPoints;

    // массив синих точек
    vector<vector<int>> bluePoints;

    // считываем точки
    for (int i = 0; i < totalPoints; i++) {

        char color;
        cin >> color;

        int x, y;
        cin >> x >> y;

        // временный массив для хранения точки
        vector<int> point;

        point.push_back(x);
        point.push_back(y);

        // добавляем точку в нужный массив
        if (color == 'r') {
            redPoints.push_back(point);
        }
        else {
            bluePoints.push_back(point);
        }
    }

    // количество пар
    int pairCount = redPoints.size();

    // массив использованных синих точек
    vector<bool> usedBlue(pairCount, false);

    // начальное большое значение и поиск мин суммы
    double minSum = 1e9;
    double answer = findBestSum(
        redPoints,
        bluePoints,
        usedBlue,
        0,
        0.0,
        minSum
    );

    cout << answer << endl;
}