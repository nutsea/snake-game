#include <iostream>
#include <ctime>
#include "conio.h"

using namespace std;

int size, change_x, change_y, coordinates_x[1000], coordinates_y[1000]; // размер, направление движения, координаты частей тела змейки
int food_x = -1, food_y = -1; // координаты еды
int score = -1; // счет
char symbol, a[30][30]; // нажатая клавиша, игровое поле
int N = 20, M = 20; // высота, ширина поля

void change_direction(){ // смена направления
    symbol = getch();
    switch (symbol){
        case 'w':
            if (change_x != 1 || change_y != 0)
            change_x = -1;
            change_y = 0;
            break;
        case 'a':
            if (change_x != 0 || change_y != 1)
            change_y = -1; 
            change_x = 0;
            break;
        case 's':
            if (change_x != -1 || change_y != 0)
            change_x = 1; 
            change_y = 0;
            break;
        case 'd':
            if (change_x != 0 || change_y != -1)
            change_y = 1; 
            change_x = 0;
            break;
        case 'q':
            system("clear");
            cout << "\nYou stopped the game\n\n";
            exit(0);
        default:
            break;
    }
}

bool game_over(){ // съела ли змейка саму себя
    for (int i = 2; i <= size; i++)
        if (coordinates_x[1] == coordinates_x[i] && coordinates_y[1] == coordinates_y[i]) return true; //если координаты головы совпадают с координатами тела
    return false;
}

void show_table(int score){ // вывод игрового поля
    system("clear");
    cout << "Press Q to stop\n\nSnake game\nScore: " << score << endl;
    for (int i = 0; i <= N + 1; i++){
        for (int j = 0; j <= M + 1; j++){
            if (i == 0 || i == N + 1) cout << ". ";
            else{
                if (j == 0) cout << ". ";
                else{
                    if (j == M + 1) cout << ". ";
                    else cout << a[i][j] << ' ';
                }
            }
        }
        cout << endl;
    }
}

void show_over(int score){ // вывод конца игры
    system("clear");
    int q;
    for (int i = 0; i <= N + 1; i++){
        q = i;
        switch (q){
            case 0:
            case 21:
                for (int j = 0; j <= M + 1; j++) cout << ". ";
                break;
            case 5: 
                cout << ". ";
                for (int j = 0; j < 7; j++) cout << "  ";
                cout << "Game over!";
                for (int j = 0; j < 8; j++) cout << "  ";
                cout << ".";
                break;
            case 6:
                cout << ". ";
                if (score > 9){
                    for (int j = 0; j < 7; j++) cout << "  ";
                    cout << "Score:  " << score;
                    for (int j = 0; j < 8; j++) cout << "  ";
                    cout << ".";
                }
                else{
                    for (int j = 0; j < 7; j++) cout << "  ";
                    cout << " Score: " << score;
                    for (int j = 0; j < 8; j++) cout << "  ";
                    cout << " .";
                }
                break;
            case 10:
                cout << ". ";
                for (int j = 0; j < 8; j++) cout << "  ";
                cout << "x    x";
                for (int j = 0; j < 9; j++) cout << "  ";
                cout << ".";
                break;
            case 11:
                cout << ". ";
                for (int j = 0; j < 8; j++) cout << "  ";
                cout << " ____";
                for (int j = 0; j < 9; j++) cout << "  ";
                cout << " .";
                break;
            case 17:
                cout << ". ";
                for (int j = 0; j < 4; j++) cout << "  ";
                cout << "Press Q to start again";
                for (int j = 0; j < 5; j++) cout << "  ";
                cout << ".";
                break;
            case 1: case 2: case 3: case 4: case 7:
            case 8: case 9: case 12: case 13: case 14:
            case 15: case 16: case 18: case 19: case 20:
                cout << ". ";
                for (int j = 0; j < 20; j++) cout << "  ";
                cout << ". ";
                break;
            default:
                break;
        }
        cout << endl;
    }
}

void clear_snake_on_table(){ // удаление змейки с поля
    for (int i = 1; i <= size; i++) a[coordinates_x[i]][coordinates_y[i]] = ' ';
}

void show_snake_on_table(){ // добавление змейки на поле
    a[coordinates_x[1]][coordinates_y[1]] = '*';
    for (int i = 2; i <= size; i++) a[coordinates_x[i]][coordinates_y[i]] = '.';
}

void check_coordinates(){ // если змейка вышла за поле, возвращаем на противоположную сторону поля
    if (coordinates_x[1] > N) coordinates_x[1] = 1;
    if (coordinates_x[1] < 1) coordinates_x[1] = N;
    if (coordinates_y[1] > M) coordinates_y[1] = 1;
    if (coordinates_y[1] < 1) coordinates_y[1] = M;
}

void next_step(int score){ // движение змейки
    clear_snake_on_table();
    for (int i = size; i >= 2; i--){ // координаты тела змейки
        coordinates_x[i] = coordinates_x[i - 1];
        coordinates_y[i] = coordinates_y[i - 1];
    }
    coordinates_x[1] += change_x; // координаты головы
    coordinates_y[1] += change_y;
    check_coordinates(); // не вышла ли змейка за поле
    if (coordinates_x[1] == food_x && coordinates_y[1] == food_y){ // если змейка съела еду, размер увеличивается, еда удаляется
        size++;
        food_x = -1;
        food_y = -1;
    }
    show_snake_on_table();
}

bool food_check(){ // проверка наличия еды
    if (food_x == -1 && food_y == -1) return false;
    return true;
}

void place_food(){ // добавление еды на поле
    srand(time(NULL));
    for (int i = 1; i <= 9; i++){
        int x = rand(), y = rand();
        if (x < 0) x *= -1;
        if (y < 0) y *= -1;
        x %= (N + 1);
        y %= (M + 1);
        if (x == 0) x++;
        if (y == 0) y++;
        if (a[x][y] != '.' && a[x][y] != '*'){
        food_x = x;
        food_y = y;
        a[x][y] = 'o';
        return;
        }
    }
}

void standart_settings(){ // начальные настройки
    size = 2;
    coordinates_x[1] = 1;
    coordinates_y[1] = 2;
    coordinates_x[2] = 1;
    coordinates_y[2] = 1;
    change_x = 0;
    change_y = 1;
}

int main(){
    standart_settings();
    int time = 120000; // интервал (скорость движения змейки)
    for (int i = 0; i < N + 1; i++){ // заполнение поля пробелами
        for (int j = 0; j < M + 1; j++){
            a[i][j] = ' ';
        }
    }
    nonblock_enable(); // отключаем ожидание ввода значения, чтобы можно было управлять змейкой в процессе игры
    while (true){ // цикл игры
        if (!game_over()){
            if (kbhit() != 0) change_direction();
            next_step(score);
            if (!food_check()){
                place_food();
                score++;
            }
            show_table(score);
            usleep(120000);
        }
        else{
            clear_snake_on_table();
            show_over(score);
            time = rand(); // эффект помех при окончании игры
            time %= 500000;
            usleep(time);
            system ("clear");
            time %= 20000;
            usleep(time);
            if (kbhit() != 0){
                symbol = getch();
                switch (symbol){
                    case 'q':
                        score = 0;
                        standart_settings();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}