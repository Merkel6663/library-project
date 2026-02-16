#include <iostream>

typedef struct{
    char* last_name;
    char* name;
    char* surname;
} FIO;

typedef struct{
    int day;
    char* month;
    int year;
} Date;

typedef struct{
    FIO fio;
    char* dep;
    char* subject;
    Date itb;
} Teacher;

void add_new_teacher(Teacher** teacher_array, int index){
    if (index == 0) *teacher_array = (Teacher*)malloc((index+1)*sizeof(Teacher));
    else *teacher_array = (Teacher*)realloc(*teacher_array, (index+1)*sizeof(Teacher));
    memset(&(*teacher_array)[index], 0, sizeof(Teacher));
    char buffer[1000];
    std::cout << "Введите фамилию преподавателя: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].fio.last_name = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].fio.last_name, buffer);

    std::cout << "Введите имя преподавателя: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].fio.name = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].fio.name, buffer);

    std::cout << "Введите отчество преподавателя: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].fio.surname = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].fio.surname, buffer);

    std::cout << "Введите кафедру преподавателя: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].dep = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].dep, buffer);

    std::cout << "Введите предмет преподавателя: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].subject = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].subject, buffer);

    std::cout << "Введите дату прохождения ИТБ: " << std::endl;
    std::cout << "День: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].itb.day = atoi(buffer);
    std::cout << "Месяц(на русском языке с большой буквы в именительном падеже): ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].itb.month = (char*)malloc(strlen(buffer) + 1);
    strcpy((*teacher_array)[index].itb.month, buffer);
    std::cout << "Год: ";
    std::cin.getline(buffer, 1000);
    (*teacher_array)[index].itb.year = atoi(buffer);
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
    std::cout << out;
    int pad = width - utf8_len(out);
    for (int k = 0; k < pad; ++k) std::cout << ' ';
}

void printTeachers(Teacher* teachers, int count) {
    if (teachers == nullptr || count <= 0) {
        std::cout << "Нет данных для отображения" << std::endl;
        std::cin.get();
        return;
    }
    
    char* date_as_str;
    const char* hdr_name = "Имя";
    const char* hdr_last = "Фамилия";
    const char* hdr_surname = "Отчество";
    const char* hdr_dep = "Кафедра";
    const char* hdr_sub = "Предмет";
    const char* hdr_itb = "Дата прохождения ИТБ";
    const char* hdr_itb_d = "День";
    const char* hdr_itb_m = "Месяц";
    const char* hdr_itb_y = "Год";

    int max_name = utf8_len(hdr_name);
    int max_last_name = utf8_len(hdr_last);
    int max_surname = utf8_len(hdr_surname);
    int max_dep = utf8_len(hdr_dep);
    int max_subject = utf8_len(hdr_sub);
    int max_itb = utf8_len(hdr_itb);
    int max_itb_d = utf8_len(hdr_itb_d);
    int max_itb_m = utf8_len(hdr_itb_m);
    int max_itb_y = utf8_len(hdr_itb_y);

    for (int i = 0; i < count; i++) {
        if (teachers[i].fio.name) {
            int l = utf8_len(teachers[i].fio.name);
            if (l > max_name) max_name = l;
        }
        if (teachers[i].fio.last_name) {
            int l = utf8_len(teachers[i].fio.last_name);
            if (l > max_last_name) max_last_name = l;
        }
        if (teachers[i].fio.surname) {
            int l = utf8_len(teachers[i].fio.surname);
            if (l > max_surname) max_surname = l;
        }
        if (teachers[i].dep) {
            int l = utf8_len(teachers[i].dep);
            if (l > max_dep) max_dep = l;
        }
        if (teachers[i].subject) {
            int l = utf8_len(teachers[i].subject);
            if (l > max_subject) max_subject = l;
        }
        if (teachers[i].itb.month) {
            int l = utf8_len(teachers[i].itb.month);
            if (l > max_itb) max_itb_m = l;
        }
    }

    int scale = 5;
    max_name += scale; max_last_name += scale; max_surname += scale; max_dep += scale; max_subject += scale; max_itb += scale;
    max_itb_d += scale; max_itb_m += scale; max_itb_y += scale;
    int total_width = max_name + max_last_name + max_surname + max_dep + max_subject + max_itb + max_itb_d + max_itb_m + max_itb_y;


    printField(hdr_name, max_name);
    printField(hdr_last, max_last_name);
    printField(hdr_surname, max_surname);
    printField(hdr_dep, max_dep);
    printField(hdr_sub, max_subject);
    printField(hdr_itb, max_itb);
    printField(hdr_itb_d, max_itb_d);
    printField(hdr_itb_m, max_itb_m);
    printField(hdr_itb_y, max_itb_y);

    std::cout << std::endl;
    std::cout << std::string(total_width, '-') << std::endl;

    for (int i = 0; i < count; i++) {
        printField(teachers[i].fio.name, max_name);
        printField(teachers[i].fio.last_name, max_last_name);
        printField(teachers[i].fio.surname, max_surname);
        printField(teachers[i].dep, max_dep);
        printField(teachers[i].subject, max_subject);
        printField(" ", max_itb);
        printField(std::to_string(teachers[i].itb.day).c_str(), max_itb_d);
        printField(teachers[i].itb.month, max_itb_m);
        printField(std::to_string(teachers[i].itb.year).c_str(), max_itb_y);
        std::cout << std::endl;
    }

    std::cout << std::string(total_width, '-') << std::endl;
    std::cout << "Всего преподавателей: " << count << std::endl;
    std::cin.get();
}

void find_subjects_by_teacher(Teacher* teachers, int count){
    std::cout << "Введите фамилию + имя преподавателя: ";
    char buff[100];
    int subject_count = 0;
    char** subjects = (char**)malloc(count * sizeof(char*));
    std::cin.getline(buff, 100);
    char* last_name = &buff[0];
    for (int i = 0; i < strlen(buff); i++){
        if (buff[i] == ' '){
            buff[i] = '\0';
            char* name = &buff[i + 1];
            break;
        }
    }

    for (int i = 0; i < count; i++){
        if (strcmp(teachers[i].fio.last_name, last_name) == 0 && strcmp(teachers[i].fio.name, &buff[strlen(last_name) + 1]) == 0){
            subjects[subject_count] = (char*)malloc(strlen(teachers[i].subject) + 1);
            strcpy(subjects[subject_count], teachers[i].subject);
            subject_count++;
        }
    }

    subjects[subject_count] = nullptr;
    std::cout << "Предметы, которые ведет данный преподаватель:" << std::endl;
        for (int i = 0; subjects[i] != nullptr; i++){
            std::cout << subjects[i] << std::endl;
        }
    for (int i = 0; i < subject_count; i++){
        free(subjects[i]);
    }
    free(subjects);
    std::cin.get();
}

char** find_teachers_by_dep(Teacher* teachers, int count, int& dep_teacher_count){
    std::cout << "Введите название кафедры: ";
    char buff[100];
    char** teacher_names = (char**)malloc(count * sizeof(char*));
    std::cin.getline(buff, 100);
    for (int i = 0; i < count; i++){
        if (strcmp(teachers[i].dep, buff) == 0){
            teacher_names[dep_teacher_count] = (char*)malloc(strlen(teachers[i].fio.name) + strlen(teachers[i].fio.last_name) + 2);
            strcpy(teacher_names[dep_teacher_count], teachers[i].fio.last_name);
            strcat(teacher_names[dep_teacher_count], " ");
            strcat(teacher_names[dep_teacher_count], teachers[i].fio.name);
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

void last_date_itb(Teacher* teachers, int count, int cur_day, int cur_month, int cur_year){
    int teacher_date_m;
    int num_teachers = 0;
    char** result_arr = (char**)malloc(count * sizeof(char*));
    char months[12][20] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    for (int j = 0; j < count; j++){
        for (int i = 0; i < 12; i++){
            if (strcmp(months[i], teachers[j].itb.month) == 0){
                teacher_date_m = i + 1;
                break;
            }
        }
        int months_diff = (cur_year - teachers[j].itb.year) * 12 + (cur_month - teacher_date_m);
        if (months_diff > 15 || (months_diff == 15 && cur_day > teachers[j].itb.day)){
            result_arr[num_teachers] = (char*)malloc(strlen(teachers[j].fio.name) + strlen(teachers[j].fio.last_name) + 2);
            strcpy(result_arr[num_teachers], teachers[j].fio.last_name);
            strcat(result_arr[num_teachers], " ");
            strcat(result_arr[num_teachers], teachers[j].fio.name);
            num_teachers++;
        }
    }
    if (num_teachers == 0){
        std::cout << "Преподавателей, у которых с даты последнего ИТБ прошло более 15 месяцев, нет." << std::endl;
        free(result_arr);
        std::cin.get();
        return;
    }
    else {
        std::cout << "Преподаватели, у которых с даты последнего ИТБ прошло более 15 месяцев:" << std::endl;
        for (int i = 0; i < num_teachers; i++){
            std::cout << result_arr[i] << std::endl;
            free(result_arr[i]);
        }
        free(result_arr);
        std::cin.get();
    }


}

int menu(){
    do{
        std::cout << "Меню:" << std::endl;
        std::cout << "Добавить нового преподавателя........................................................1" << std::endl;
        std::cout << "Распечатать информацию о преподавателях в табличном виде.............................2" << std::endl;
        std::cout << "Найти все предметы которые ведет заданный преподаватель..............................3" << std::endl;
        std::cout << "Найти всех преподавателей заданной кафедры...........................................4" << std::endl;
        std::cout << "Найти всех преподавателей, у которых с даты последнего ИТБ прошло более 15 месяцев...5" << std::endl;
        std::cout << "Выход................................................................................0" << std::endl;
        std::cout << "Введите номер задачи: ";
        int choice;
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice >= 0 && choice <= 5)
            return choice;
        else
            std::cout << "Неверный ввод. Введите номер задачи (от 0 до 5)." << std::endl;
            std::cin.get();
    } while (true);
}

void save_to_file(Teacher* teachers, int index, const char* filename){
    FILE* file = fopen(filename, "wb");
    int len;
    if (!file){
        std::cout << "Ошибка сохранения файла!" << std::endl;
        return;
    }
    else{
        fwrite(&index, sizeof(int), 1, file);
        for (int i = 0; i < index; i++){
            len = teachers[i].fio.last_name ? strlen(teachers[i].fio.last_name)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].fio.last_name, sizeof(char), len, file);

            len = teachers[i].fio.name ? strlen(teachers[i].fio.name)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].fio.name, sizeof(char), len, file); 

            len = teachers[i].fio.surname ? strlen(teachers[i].fio.surname)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].fio.surname, sizeof(char), len, file); 

            len = teachers[i].dep ? strlen(teachers[i].dep)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].dep, sizeof(char), len, file); 

            len = teachers[i].subject ? strlen(teachers[i].subject)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].subject, sizeof(char), len, file); 

            fwrite(&teachers[i].itb.day, sizeof(int), 1, file);

            len = teachers[i].itb.month ? strlen(teachers[i].itb.month)+1 : 0;
            fwrite(&len, sizeof(int), 1, file);
            if (len > 0) fwrite(teachers[i].itb.month, sizeof(char), len, file); 

            fwrite(&teachers[i].itb.year, sizeof(int), 1, file);
        }

        fclose(file);

        std::cout << "Данные успешно сохранены!";
    }
}

int read_from_file(Teacher** teachers, const char* filename){
    FILE* file = fopen(filename, "rb");
    if (!file){
        return -1;
    }
    int index, len;
    fread(&index, sizeof(int), 1, file);
    *teachers = (Teacher*)calloc(index, sizeof(Teacher));
    for (int i = 0; i < index; i++){
        char buffer[100];
        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].fio.last_name = (char*)malloc(len);
            strcpy((*teachers)[i].fio.last_name, buffer);
        }
        else (*teachers)[i].fio.last_name = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].fio.name = (char*)malloc(len);
            strcpy((*teachers)[i].fio.name, buffer);
        }
        else (*teachers)[i].fio.name = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].fio.surname = (char*)malloc(len);
            strcpy((*teachers)[i].fio.surname, buffer);
        }
        else (*teachers)[i].fio.surname = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].dep = (char*)malloc(len);
            strcpy((*teachers)[i].dep, buffer);
        }
        else (*teachers)[i].dep = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].subject = (char*)malloc(len);
            strcpy((*teachers)[i].subject, buffer);
        }
        else (*teachers)[i].subject = nullptr;

        fread(&(*teachers)[i].itb.day, sizeof(int), 1, file);

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*teachers)[i].itb.month = (char*)malloc(len);
            strcpy((*teachers)[i].itb.month, buffer);
        }
        else (*teachers)[i].itb.month = nullptr;

        fread(&(*teachers)[i].itb.year, sizeof(int), 1, file);
    }
    fclose(file);
    return index;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Teacher *teacher_array;
    const char* filename = "/Users/maxim2720icloud.com/Documents/VS Code Folder/Laba7_c/data.dat";
    int index = 0, choice;
    index = read_from_file(&teacher_array, filename);
    if (index == -1){
        index = 0;
        add_new_teacher(&teacher_array, index);
        index = 1;
    }
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_c);
    do{
        system("clear");
        choice = menu();
        switch(choice){
            case 1:
                add_new_teacher(&teacher_array, index);
                index++;
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
                    std::cout << "Преподавателей на данной кафедре нет." << std::endl;
                    free(array);
                    std::cin.get();
                    break;
                }
                else {
                    std::cout << "Преподаватели данной кафедры в алфавитном порядке:" << std::endl;
                    for (int i = 0; i < dep_teacher_count; i++){
                        std::cout << array[i] << std::endl;
                        free(array[i]);
                    }
                    free(array);
                    std::cin.get();
                }
                break;
            }
            case 5:{
                last_date_itb(teacher_array, index, local_tm.tm_mday, local_tm.tm_mon + 1, local_tm.tm_year + 1900);
                break;
            }
            case 0: {
                save_to_file(teacher_array, index, filename);
                for (int i = 0; i < index; i++){
                    free(teacher_array[i].fio.name);
                    free(teacher_array[i].fio.last_name);
                    free(teacher_array[i].fio.surname);
                    free(teacher_array[i].dep);
                    free(teacher_array[i].subject);
                    free(teacher_array[i].itb.month);
                }
                free(teacher_array);
                return 0;
            }
        }
    } while (true);
}