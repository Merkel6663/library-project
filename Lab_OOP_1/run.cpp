#include <iostream>
#include <cstring>
#include <stdlib.h>

void wait_for_key() {
    std::cout << "\n\nНажмите Enter для продолжения...";
    std::cin.ignore();
    std::cin.get();
}

typedef struct {
    char* fam;
    char* name;
    char* arrival;
    double price;
} Ticket;

int utf8_len(const char* s){
    if (!s) return 0;
    int len = 0;
    for (size_t i = 0; s[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if ((c & 0xC0) != 0x80) ++len;
    }
    return len;
}

void add_new_ticket(Ticket** tickets_arr, int& index) {
    char buffer[1000];
    if (index == 0) *tickets_arr = (Ticket*)malloc((index+1)*sizeof(Ticket));
    else *tickets_arr = (Ticket*)realloc(*tickets_arr, (index+1)*sizeof(Ticket));

    std::cin.ignore();
    std::cout << "Введите фамилию пассажира:";
    std::cin.getline(buffer, 1000);
    (*tickets_arr)[index].fam = (char*)malloc(strlen(buffer) + 1);
    strcpy((*tickets_arr)[index].fam, buffer);

    std::cout << "Введите имя пассажира:";
    std::cin.getline(buffer, 1000);
    (*tickets_arr)[index].name = (char*)malloc(strlen(buffer) + 1);
    strcpy((*tickets_arr)[index].name, buffer);

    std::cout << "Введите пункт прибытия пассажира:";
    std::cin.getline(buffer, 1000);
    (*tickets_arr)[index].arrival = (char*)malloc(strlen(buffer) + 1);
    strcpy((*tickets_arr)[index].arrival, buffer);

    std::cout << "Введите цену билета:";
    std::cin >> (*tickets_arr)[index].price;
    std::cin.ignore();
}



void print_field(const char* str, int fsize){
    int cur_size = utf8_len(str);
    if (cur_size == 0) {
        std::cout << "Н/Д";
        cur_size = 3;
    }
    else{
        std::cout << str;
    }
    for (int i = cur_size; i < fsize; i++) {
        std::cout << " ";
    }
}

void print_tickets_blanket(Ticket* tickets_arr, int& index){
    const char* baze_fam = "Фамилия";
    const char* baze_name = "Имя";
    const char* baze_arrival = "Прибытие";
    const char* baze_price = "Цена билета";

    int baze_len_fam = utf8_len(baze_fam);
    int baze_len_name = utf8_len(baze_name);
    int baze_len_arrival = utf8_len(baze_arrival);
    int baze_len_price = utf8_len(baze_price);
    char price_str[30];

    for (int i=0;i<index;i++){
        if (utf8_len(tickets_arr[i].fam) > baze_len_fam) baze_len_fam = utf8_len(tickets_arr[i].fam);
        if (utf8_len(tickets_arr[i].name) > baze_len_name) baze_len_name = utf8_len(tickets_arr[i].name);
        if (utf8_len(tickets_arr[i].arrival) > baze_len_arrival) baze_len_arrival = utf8_len(tickets_arr[i].arrival);
        snprintf(price_str, sizeof(price_str), "%.2f", tickets_arr[i].price);
        if (strlen(price_str) > baze_len_price) baze_len_price = strlen(price_str);
    }

    int scale = 5;
    baze_len_fam += scale;
    baze_len_name += scale;
    baze_len_arrival += scale;
    baze_len_price += scale;

    print_field(baze_fam, baze_len_fam);
    print_field(baze_name, baze_len_name);
    print_field(baze_arrival, baze_len_arrival);
    print_field(baze_price, baze_len_price);
    std::cout << std::endl;
    std::cout << std::string(baze_len_fam + baze_len_name + baze_len_arrival + baze_len_price, '-') << std::endl;

    for (int i = 0; i < index; i++){
        print_field(tickets_arr[i].fam, baze_len_fam);
        print_field(tickets_arr[i].name, baze_len_name);
        print_field(tickets_arr[i].arrival, baze_len_arrival);
        snprintf(price_str, sizeof(price_str), "%.2f", tickets_arr[i].price);
        print_field(price_str, baze_len_price);
        std::cout << std::endl;
    }
}

int menu(){
    int res;
    while(true){
        std::cout << "Добавить новый билет......................................................1" << std::endl;
        std::cout << "Вывести таблицу всех билетов..............................................2" << std::endl;
        std::cout << "Поиск билета по имени и фамилии пассажира.................................3" << std::endl;
        std::cout << "Найти все билеты с ценой более заданного значения.........................4" << std::endl;
        std::cout << "===========================================================================" << std::endl;
        std::cout << "Выход.....................................................................0" << std::endl;
        std::cout << "Выберите нужное(1-4, 0): ";
        std::cin >> res;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод! Введите число от 1 до 4 или 0" << std::endl;
            wait_for_key();
            system("clear");
        }
        else if (res >= 1 && res <= 4 || res == 0) {
            return res;
        }
        else{
            std::cout << "Неверный ввод! Выберите от 1 до 4 или 0" << std::endl;
            wait_for_key();
            system("clear");
        }
    }
}

Ticket* search_name_fam(Ticket* ticket_arr, int& index, int& size){
    std::cin.ignore();
    std::cout << "Введите имя и фамилию пассажира (через пробел в именительном падеже):";
    char buffer[1000];
    std::cin.getline(buffer, 1000);

    Ticket* searched_tickets = nullptr;
    char* name = &buffer[0];
    char* last_name = nullptr;
    for (int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == ' '){
            buffer[i] = '\0';
            last_name = &buffer[i + 1];
            break;
        }
    }

    for (int i = 0; i < index; i++){
        if (strcmp(name, ticket_arr[i].name) == 0 && strcmp(last_name, ticket_arr[i].fam) == 0) {
            if (size == 0) searched_tickets = (Ticket*)malloc((size+1)*sizeof(Ticket));
            else searched_tickets = (Ticket*)realloc(searched_tickets, (size+1)*sizeof(Ticket));
            searched_tickets[size] = ticket_arr[i];
            size++;
        }
    }
    return searched_tickets;
}

Ticket* search_by_price(Ticket* ticket_arr, int& index, int& size){
    Ticket* searched_tickets = nullptr;
    double price;
    std::cin.ignore();
    std::cout << "Введите цену для поиска:";
    std:: cin >> price;

    for (int i = 0; i < index; i++){
        if (price < ticket_arr[i].price) {
            if (size == 0) searched_tickets = (Ticket*)malloc((size+1)*sizeof(Ticket));
            else searched_tickets = (Ticket*)realloc(searched_tickets, (size+1)*sizeof(Ticket));
            searched_tickets[size] = ticket_arr[i];
            size++;
        }
    }
    return searched_tickets;
}

void save_to_file(Ticket* tickets_arr, int index, const char* filename){
    FILE* file = fopen(filename, "wb");
    int len;
    if (!file){
        std::cout << "Ошибка сохранения файла!" << std::endl;
        return;
    }
    else{
        fwrite(&index, sizeof(int), 1, file);
        for (int i = 0; i < index; i++){
            len = tickets_arr[i].fam ? strlen(tickets_arr[i].fam)+1 : 0;
            fwrite(&len,sizeof(int), 1, file);
            if (len > 0) fwrite(tickets_arr[i].fam, sizeof(char), len, file);

            len = tickets_arr[i].name ? strlen(tickets_arr[i].name)+1 : 0;
            fwrite(&len,sizeof(int), 1, file);
            if (len > 0) fwrite(tickets_arr[i].name, sizeof(char), len, file);

            len = tickets_arr[i].arrival ? strlen(tickets_arr[i].arrival)+1 : 0;
            fwrite(&len,sizeof(int), 1, file);
            if (len > 0) fwrite(tickets_arr[i].arrival, sizeof(char), len, file);

            fwrite(&tickets_arr[i].price, sizeof(double), 1, file);
        }
        fclose(file);

        std::cout << "Данные успешно записаны!";
    }
}

int read_from_file(Ticket** tickets_arr, const char* filename){
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;
    int index, len;
    fread(&index, sizeof(int), 1, file);
    *tickets_arr = (Ticket*)calloc(index, sizeof(Ticket));
    for (int i = 0; i < index; i++){
        char buffer[1000];
        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*tickets_arr)[i].fam = (char*)malloc(len);
            strcpy((*tickets_arr)[i].fam, buffer);
        }
        else (*tickets_arr)[i].fam = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*tickets_arr)[i].name = (char*)malloc(len);
            strcpy((*tickets_arr)[i].name, buffer);
        }
        else (*tickets_arr)[i].name = nullptr;

        fread(&len, sizeof(int), 1, file);
        if (len > 0){
            fread(buffer, sizeof(char), len, file);
            (*tickets_arr)[i].arrival = (char*)malloc(len);
            strcpy((*tickets_arr)[i].arrival, buffer);
        }
        else (*tickets_arr)[i].arrival = nullptr;

        fread(&(*tickets_arr)[i].price, sizeof(double), 1, file);
    }
    return index;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Ticket *ticket_arr;
    int size;
    const char* filename = "/Users/maxim2720icloud.com/Documents/VS Code Folder/Lab_OOP_1/data.dat";
    int index = 0, choice;
    index = read_from_file(&ticket_arr, filename);
    if (index == -1){
        index = 0;
        add_new_ticket(&ticket_arr, index);
        index++;
    }
    do{
        system("clear");
        choice = menu();
        system("clear");
        switch(choice){
            case 1:
                add_new_ticket(&ticket_arr, index);
                index++;
                break;
            case 2:
                print_tickets_blanket(ticket_arr, index);
                wait_for_key();
                break;
            case 3:
                size = 0;
                print_tickets_blanket(search_name_fam(ticket_arr, index, size), size);
                wait_for_key();
                break;
            case 4:
                size = 0;
                print_tickets_blanket(search_by_price(ticket_arr, index, size), size);
                wait_for_key();
                break;
            case 0:
                save_to_file(ticket_arr, index, filename);
                for (int i = 0; i < index; i++){
                    free(ticket_arr[i].fam);
                    free(ticket_arr[i].name);
                    free(ticket_arr[i].arrival);
                }
                free(ticket_arr);
                return 0;
        }
    } while(true);
}