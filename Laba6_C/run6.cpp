#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cwchar>
#include <cstring>
#include <limits>

using namespace std;

typedef struct{
    char* name;
    char* last_name;
    char* dep;
    char* subject;
} Teacher;


void add_new_teacher(Teacher* teacher_array, int index){
    char buffer[1000];
    cout << "Введите имя преподавателя: ";
    cin.getline(buffer, 1000);
    teacher_array[index].name = (char*)malloc(strlen(buffer) + 1);
    strcpy(teacher_array[index].name, buffer);

    cout << "Введите фамилию преподавателя: ";
    cin.getline(buffer, 1000);
    teacher_array[index].last_name = (char*)malloc(strlen(buffer) + 1);
    strcpy(teacher_array[index].last_name, buffer);

    cout << "Введите кафедру преподавателя: ";
    cin.getline(buffer, 1000);
    teacher_array[index].dep = (char*)malloc(strlen(buffer) + 1);
    strcpy(teacher_array[index].dep, buffer);

    cout << "Введите предмет преподавателя: ";
    cin.getline(buffer, 1000);
    teacher_array[index].subject = (char*)malloc(strlen(buffer) + 1);
    strcpy(teacher_array[index].subject, buffer);

}


int utf8_len(const char* s){
    if (!s) return 0;
    int len = 0;
    for (size_t i = 0; s[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if ((c & 0xC0) != 0x80) ++len;
    }
    return len;
}


void printField(const char* s, int width) {
    const char* out = s ? s : "Н/Д";
    cout << out;
    int pad = width - utf8_len(out);
    for (int k = 0; k < pad; ++k) cout << ' ';
}


void printTeachers(Teacher* teachers, int count) {
    if (teachers == nullptr || count <= 0) {
        cout << "Нет данных для отображения" << endl;
        cin.get();
        return;
    }
    
    const char* hdr_name = "Имя";
    const char* hdr_last = "Фамилия";
    const char* hdr_dep = "Кафедра";
    const char* hdr_sub = "Предмет";

    int max_name = utf8_len(hdr_name);
    int max_last_name = utf8_len(hdr_last);
    int max_dep = utf8_len(hdr_dep);
    int max_subject = utf8_len(hdr_sub);

    for (int i = 0; i < count; i++) {
        if (teachers[i].name) {
            int l = utf8_len(teachers[i].name);
            if (l > max_name) max_name = l;
        }
        if (teachers[i].last_name) {
            int l = utf8_len(teachers[i].last_name);
            if (l > max_last_name) max_last_name = l;
        }
        if (teachers[i].dep) {
            int l = utf8_len(teachers[i].dep);
            if (l > max_dep) max_dep = l;
        }
        if (teachers[i].subject) {
            int l = utf8_len(teachers[i].subject);
            if (l > max_subject) max_subject = l;
        }
    }

    int scale = 5;
    max_name += scale; max_last_name += scale; max_dep += scale; max_subject += scale;
    int total_width = max_name + max_last_name + max_dep + max_subject;


    printField(hdr_name, max_name);
    printField(hdr_last, max_last_name);
    printField(hdr_dep, max_dep);
    printField(hdr_sub, max_subject);
    cout << endl;
    cout << string(total_width, '-') << endl;

    for (int i = 0; i < count; i++) {
        printField(teachers[i].name, max_name);
        printField(teachers[i].last_name, max_last_name);
        printField(teachers[i].dep, max_dep);
        printField(teachers[i].subject, max_subject);
        cout << endl;
    }

    cout << string(total_width, '-') << endl;
    cout << "Всего преподавателей: " << count << endl;
    cin.get();
}



void find_subjects_by_teacher(Teacher* teachers, int count){
    cout << "Введите фамилию + имя преподавателя: ";
    char buff[100];
    int subject_count = 0;
    char** subjects = (char**)malloc(count * sizeof(char*));
    cin.getline(buff, 100);
    char* last_name = &buff[0];
    for (int i = 0; i < strlen(buff); i++){
        if (buff[i] == ' '){
            buff[i] = '\0';
            char* name = &buff[i + 1];
            break;
        }
    }

    for (int i = 0; i < count; i++){
        if (strcmp(teachers[i].last_name, last_name) == 0 && strcmp(teachers[i].name, &buff[strlen(last_name) + 1]) == 0){
            subjects[subject_count] = (char*)malloc(strlen(teachers[i].subject) + 1);
            strcpy(subjects[subject_count], teachers[i].subject);
            subject_count++;
        }
    }

    subjects[subject_count] = nullptr;
    cout << "Предметы, которые ведет данный преподаватель:" << endl;
        for (int i = 0; subjects[i] != nullptr; i++){
            cout << subjects[i] << endl;
        }
    for (int i = 0; i < subject_count; i++){
        free(subjects[i]);
    }
    free(subjects);
    cin.get();
}

char** find_teachers_by_dep(Teacher* teachers, int count, int& dep_teacher_count){
    cout << "Введите название кафедры: ";
    char buff[100];
    char** teacher_names = (char**)malloc(count * sizeof(char*));
    cin.getline(buff, 100);
    for (int i = 0; i < count; i++){
        if (strcmp(teachers[i].dep, buff) == 0){
            teacher_names[dep_teacher_count] = (char*)malloc(strlen(teachers[i].name) + strlen(teachers[i].last_name) + 2);
            strcpy(teacher_names[dep_teacher_count], teachers[i].last_name);
            strcat(teacher_names[dep_teacher_count], " ");
            strcat(teacher_names[dep_teacher_count], teachers[i].name);
            dep_teacher_count++;
        }
    }
    return teacher_names;
}

char** sort_by_alphabet(char** teachers, int count){
    for (int i = 0; i < count - 1; i++){
        for (int j = 0; j < count - i - 1; j++){
            if (strcmp(teachers[j], teachers[j + 1]) > 0){
                char* temp = teachers[j];
                teachers[j] = teachers[j + 1];
                teachers[j + 1] = temp;
            }
        }
    }
    return teachers;
}

int menu(){
    do{
        cout << "Меню:" << endl;
        cout << "Добавить нового преподавателя...........................................1" << endl;
        cout << "Распечатать информацию о преподавателях в табличном виде................2" << endl;
        cout << "Найти все предметы которые ведет заданный преподаватель.................3" << endl;
        cout << "Найти всех преподавателей заданной кафедры..............................4" << endl;
        cout << "Выход...................................................................0" << endl;
        cout << "Введите номер задачи: ";
        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice >= 0 && choice <= 4)
            return choice;
        else
            cout << "Неверный ввод. Введите номер задачи (от 0 до 4)." << endl;
            cin.get();
    } while (true);
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Teacher *teacher_array;
    cout << "Введите количество преподавателей: ";
    int n, index = 0, choice;
    cin >> n;
    teacher_array = (Teacher*)malloc(n * sizeof(Teacher));

    do{
        system("clear");

        choice = menu();
        switch(choice){
            case 1:
                if (index < n){
                    add_new_teacher(teacher_array, index);
                    index++;
                }
                else{
                    cout << "Достигнуто максимальное количество преподавателей!" << endl;
                    cin.get();
                }
                break;
            case 2:
                printTeachers(teacher_array, index);
                break;
            case 3:
                find_subjects_by_teacher(teacher_array, index);
                break;
            case 4:{
                char** array = nullptr;
                int dep_teacher_count = 0;
                array = find_teachers_by_dep(teacher_array, index, dep_teacher_count);
                array = sort_by_alphabet(array, dep_teacher_count);
                if (dep_teacher_count == 0){
                    cout << "Преподавателей на данной кафедре нет." << endl;
                    free(array);
                    cin.get();
                    break;
                }
                else {
                    cout << "Преподаватели данной кафедры в алфавитном порядке:" << endl;
                    for (int i = 0; i < dep_teacher_count; i++){
                        cout << array[i] << endl;
                        free(array[i]);
                    }
                    free(array);
                    cin.get();
                }
                break;
            }
            case 0: {
                for (int i = 0; i < index; i++){
                    free(teacher_array[i].name);
                    free(teacher_array[i].last_name);
                    free(teacher_array[i].dep);
                    free(teacher_array[i].subject);
                }
                free(teacher_array);
                return 0;
            }
        }
    } while (true);
}