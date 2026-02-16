#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

char* ins_text(char* line, char* in_line, int ix){
    size_t len1 = strlen(line);
    size_t len2 = strlen(in_line);
    if (ix < 0) ix = 0;
    if ((size_t)ix > len1) ix = (int)len1;

    char* result = (char*)malloc(len1 + len2 + 1);
    if (!result) return nullptr;

    for (int i = 0; i < ix; i++){
        result[i] = line[i];
    }
    for (size_t j = 0; j < len2; j++){
        result[ix + j] = in_line[j];
    }

    for (size_t k = ix; k < len1; k++){
        result[ix + len2 + (k - ix)] = line[k];
    }

    result[len1 + len2] = '\0';
    return result;
}

void to_lower_inplace(char* s) {
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

char* sort_words_return_newline(char* line) {

    char* buf = (char*)malloc(strlen(line) + 1);
    if (!buf) return nullptr;
    strcpy(buf, line);

    char* words[1000];
    char* words_og[1000];
    int word_count = 0;

    to_lower_inplace(buf);

    char* p = buf;
    char* p_og = line;
    while (*p) {
        while (*p && isspace((unsigned char)*p)){
            p++;
            p_og++;
        }
        if (!*p) break;
        if (word_count >= 1000) break;
        words[word_count] = p;
        words_og[word_count] = p_og;
        while (*p && !isspace((unsigned char)*p)){
            p++;
            p_og++;
        }
        if (*p) {
            *p = '\0';
            ++p;
        }
        if (*p_og) {
            *p_og = '\0';
            ++p_og;
        }
        word_count++;
    }

    for (int i = 0; i < word_count - 1; ++i) {
        for (int j = 0; j < word_count - 1 - i; ++j) {
            if (strcmp(words[j], words[j+1]) > 0) {

                char* tmp = words[j];
                words[j] = words[j+1];
                words[j+1] = tmp;

                char* tmp_og = words_og[j];
                words_og[j] = words_og[j+1];
                words_og[j+1] = tmp_og;
            }
        }
    }

    size_t total_len = 0;
    for (int i = 0; i < word_count; ++i) {
        total_len += strlen(words_og[i]);
    }
    if (word_count > 0) total_len += (word_count - 1);
    char* result = (char*)malloc(total_len + 1);
    if (!result) { free(buf); return nullptr; }

    char* dst = result;
    for (int i = 0; i < word_count; ++i) {
        size_t l = strlen(words_og[i]);
        memcpy(dst, words_og[i], l);
        dst += l;
        if (i != word_count - 1) {
            *dst = ' ';
            ++dst;
        }
    }
    *dst = '\0';

    free(buf);
    return result;
}

int task1(){
    char* line1 = nullptr;
    char* line2 = nullptr;
    char buffer[1000];

    cout << "Введите первую строку:";
    cin.getline(buffer, 1000);
    line1 = (char*)malloc(strlen(buffer) + 1);
    strcpy(line1, buffer);
    cout << "Введите вторую строку:";
    cin.getline(buffer, 1000);
    line2 = (char*)malloc(strlen(buffer) + 1);
    strcpy(line2, buffer);

    cout << "Введите позицию вставки: ";
    int ix;
    cin >> ix;

    char* sorted_line2 = sort_words_return_newline(line2);
    char* new_line = ins_text(line1, sorted_line2, ix);

    cout << "Результат вставки: " << new_line << endl;
    cout << "Отсортированная в лексикографическом порядке вторая строка: " << sorted_line2 << endl;

    free(line1);
    free(line2);
    free(sorted_line2);
    free(new_line);

    return 0;
}

double sum_chet(double** array, int rows, int cols){
    double result = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i <= j && j % 2 != 0) result += array[i][j];
        }
    }
    return result;
}

int task2(){
    int rows, cols;
    cout << "Введите размеры массива через пробел: ";
    cin >> rows >> cols;

    srand(time(0));
    double** array = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        array[i] = (double*)malloc(cols * sizeof(double));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = (rand() % 201 - 100)/10.;
        }
    }

    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            if (row <= col) cout << "\x1b[31m" << array[row][col] << "\x1b[0m" << "\t";
            else cout << array[row][col] << "\t";
        }
        cout << endl;
    }
    cout << "Сумма элементов четных столбцов:" << sum_chet(array, rows, cols) << endl;
    return 0;
}


char** find_lowercase_words(char* line, int& count) {
    count = 0;
    char** result = nullptr;
    char* ptr = line;

    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) ptr++;
        if (!*ptr) break;

        char* word_start = ptr;

        while (*ptr && !isspace((unsigned char)*ptr)) ptr++;

        unsigned char c = (unsigned char)word_start[0];
        if (isalpha(c) && islower(c)) {
            count++;
            result = (char**)realloc(result, count * sizeof(char*));
            result[count - 1] = word_start;
        }
    }

    return result;
}



int task3() {
    setlocale(LC_ALL,"Russian");
    char** lines = nullptr;
    int line_count = 0;
    char buffer[1000];

    // считываю строки
    cout << "Введите строки (для завершения введите \"yes\"):" << endl;
    while (cin.getline(buffer, 1000) && strcmp(buffer, "yes") != 0) {
        lines = (char**)realloc(lines, (line_count + 1) * sizeof(char*));
        lines[line_count] = (char*)malloc(strlen(buffer) + 1);
        strcpy(lines[line_count], buffer);
        line_count++;
    }


    for (int i = 0; i < line_count; i++) {
        int word_count = 0;
        int word_number = 0;
        char* ptr_start = lines[i];
        char* ptr_start_cur = lines[i];
        char* ptr_start_copy = lines[i];
        char** words = find_lowercase_words(lines[i], word_count);
        char* new_line = (char*)malloc((strlen(lines[i]) + 1) *sizeof(char));
        int len_newstr = 0;
        cout << word_count << endl;
        for (int j = 0; j < word_count; j++) {
            word_number++;
            int len_newstr_copy = len_newstr;
            ptr_start_copy = ptr_start_cur;
            for (int k = len_newstr_copy; k < (len_newstr_copy + (words[j] - ptr_start_copy)); k++) {
                len_newstr++;                                                                   //если вывод странный проверить тут
                new_line[k] = lines[i][ptr_start_cur - ptr_start];
                ptr_start_cur++;
            }
           

            string number_str = to_string(word_number);
            new_line = (char*)realloc(new_line, len_newstr + number_str.length() + 1);
            len_newstr += number_str.length();
            strcpy(&new_line[len_newstr-strlen(number_str.c_str())], number_str.c_str()); // добавление цифры(!)
            
            // если это последнее слово, добавляем остаток строки
            if (word_count == word_number) {
                while (lines[i][ptr_start_cur - ptr_start] != '\0') {
                    len_newstr++;
                    new_line = (char*)realloc(new_line, len_newstr + 1);
                    new_line[len_newstr - 1] = lines[i][ptr_start_cur - ptr_start];
                    ptr_start_cur++;
                }
            }

        }
        new_line[len_newstr+1] = '\0';
        lines[i] = new_line;
        
    }


    for (int i = 0; i < line_count; i++) {
        cout << lines[i] << endl;
        free(lines[i]);
    }
    return 0;
}



int** find_min(int** arr, int rows, int cols, int& min_count){
    int** result = nullptr;
    int min = arr[0][0];
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if ((i <= j) && arr[i][j] < min) min = arr[i][j];
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (arr[i][j] == min && i <= j){
                min_count++;
                result = (int**)realloc(result, (min_count)*sizeof(int*));
                result[min_count-1] = &arr[i][j];
            }
            
        }
    }

    return result;

}

int task4(int& rows_s, int& cols_s){
    int rows = rows_s, cols = cols_s;
    int min_count = 0;
    if (rows == 0 && cols == 0){
        cout << "Введите размеры массива через пробел: ";
        cin >> rows >> cols;
    }

    rows_s = rows;
    cols_s = cols;

    srand(time(0));
    int** array = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = rand() % 21 - 10;
        }
    }

    int** min_ptr_arr = find_min(array, rows, cols, min_count);
    
    if (min_count < 2) return 1;
    int flag = 0;
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            if (row <= col){
                for (int ptr = 0; ptr < min_count; ptr++){
                    if (&array[row][col] == min_ptr_arr[ptr]) flag = 1;
                }
                if (flag == 1){
                    cout << "\x1b[31m" << array[row][col] << "\x1b[0m" << "\t";
                    flag = 0;
                }
                else cout << "\x1b[32m" << array[row][col] << "\x1b[0m" << "\t";
            }
            else cout << array[row][col] << "\t";
        }
        cout << endl;
    }

    return 0;
}


int main() {
    int res = 1;
    while (res != 0){
        res = task2();
    }
    return 0;
}


int main() {
    int res = 1;
    while (res != 0){
        res = task3();
    }
    return 0;
}


/*
int main() {
    int rows_s = 0, cols_s = 0;
    int res = 1;
    while (res != 0){
        res = task4(rows_s, cols_s);
    }
    return 0;
}
*/
