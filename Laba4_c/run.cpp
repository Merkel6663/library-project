#include <iostream>
#include <clocale>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#define N1 10
#define N2 10
#define N 10
using namespace std;

int* getPointer_0(int* arr, int size) {
    int* ptr = nullptr;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == 0) {
            ptr = &arr[i];
            break;
        }
    }
    return ptr;

}

int task1(){
    setlocale(LC_ALL,"Russian");
    srand(time(0));
    int A[N1], B[N2];
    int i;
    for (i=0; i<N1; i++){
        A[i] = rand() % 21 - 10;
    }
    for (i=0; i<N2; i++){
        B[i] = rand() % 21 - 10;
    }
    int* p0_A = getPointer_0(A, N1);
    int* p0_B = getPointer_0(B, N2);
    if (p0_A == nullptr || p0_B == nullptr) return 1;

    int sum1_A = 0, sum2_A = 0, sum1_B = 0, sum2_B = 0;
    for (i = 0; i < N1; i++){
        if (&A[i] < p0_A) sum1_A += A[i];
        else if (&A[i] > p0_A) sum2_A += A[i];
    }

    for (i=0; i<N2; i++){
        if (&B[i] < p0_B) sum1_B += B[i];
        else if (&B[i] > p0_B) sum2_B += B[i];
    }
    int flag = 0;
    cout << "Массив A: ";
    for (i=0; i<N1; i++){
        if (A[i] == 0 && flag ==0){
            flag = 1;
            cout << "\033[31m" << A[i] << "\033[0m" << '\t';
        } 
        else cout << A[i] << '\t';

    } 
    cout << endl;

    cout << "Сумма элементов до нуля: " << sum1_A << '\t' << "Сумма элементов после нуля: " << sum2_A << endl;
    flag = 0;
    cout << "Массив B: ";
    for (i=0; i<N1; i++){
        if (B[i] == 0 && flag ==0){
            flag = 1;
            cout << "\033[31m" << B[i] << "\033[0m" << '\t';
        } 
        else cout << B[i] << '\t';

    } 
    cout << endl;
    cout << "Сумма элементов до нуля: " << sum1_B << '\t' << "Сумма элементов после нуля: " << sum2_B << endl;

    cout << "Повторить? (1 - да, 0 - нет): ";
    cin >> i;
    if (i == 1){
        system("clear");
        return 1;
    }
    else
        return 0;
}

int* find_max_min_abs(int arr[][N], int size) {
    static int result[2];
    int* p = &arr[0][0];
    int* end = &arr[0][0] + size * size;
    int max_abs = abs(*p);
    int min_abs = abs(*p);
    int max_val = *p;
    int min_val = *p;
    for (; p < end; ++p) {
        if ((p - &arr[0][0]) / size <= (p - &arr[0][0]) % size) {
            int abs_val = abs(*p);
            if (abs_val > max_abs) {
                max_abs = abs_val;
                max_val = *p;
            }
            if (abs_val < min_abs) {
                min_abs = abs_val;
                min_val = *p;
            }
        }
        
    }
    result[0] = max_val;
    result[1] = min_val;
    return result;
}


int task2(){
    setlocale(LC_ALL,"Russian");
    int A[N][N];
    int i, j;
    srand(time(0));
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            A[i][j] = rand() % 2001 - 1000;
        }
    }
    int* max_min_abs = find_max_min_abs(A, N);
    int max_abs = max_min_abs[0];
    int min_abs = max_min_abs[1];
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            if (i <= j){
                if (abs(A[i][j]) == max_abs || abs(A[i][j]) == min_abs) cout << "\033[31m" << A[i][j] << "\033[0m" << '\t';
                else cout << "\033[32m" << A[i][j] << "\033[0m" << '\t';
            }
            else cout << A[i][j] << '\t';
            }
        cout << endl;
    }
    cout << "Максимальный по модулю элемент в верхнем треугольнике: " << max_min_abs[0] << endl;
    cout << "Минимальный по модулю элемент в верхнем треугольнике: " << max_min_abs[1] << endl;
    cout << "Повторить? (1 - да, 0 - нет): ";
    cin >> i;
    if (i == 1){
        system("clear");
        return 1;
    }
    else
        return 0;
}

int main(){
    int result = 1;
    while (result == 1){
        result = task2();
    }

    return 0;
}
