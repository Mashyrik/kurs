
#include <fstream>
#include <iomanip>
#include <iostream>

//hvakbvkasbgk
using namespace std;

void createFile();
void viewFile();
void addItem();
void linearSearch(const char* searchItem);
void selectionSort(const char* fileName);
void quickSort();
void binarySearch();
void findItemOverMonth(const char* fileName);

const int MAXLEN = 100;
struct Item {
    char name[MAXLEN];
    int quantity;
    double priceForOne;
    char dateOfEntry[MAXLEN];
};

void createFile() {
    string fileName;
    cout << "Введите имя файла(.txt): ";
    cin >> fileName;
    ofstream file(fileName);
    file.close();
    cout << "Файл создан!";
}

void viewFile() {
    string fileName;
    cout << "Введите имя файла: ";
    cin >> fileName;
    ifstream file(fileName);
    if (!file) {
        cout << "Файл не найден или не может быть открыт";
        return;
    }
    Item item;
    cout << std::setw(20) << "Name"
        << std::setw(15) << "Quantity"
        << std::setw(20) << "Price for One"
        << std::setw(20) << "Date of Entry" << std::endl;
    while (file >> item.name >> item.quantity >> item.priceForOne >> item.dateOfEntry) {
        cout << std::setw(20) << item.name
            << std::setw(15) << item.quantity
            << std::setw(20) << item.priceForOne
            << std::setw(20) << item.dateOfEntry << std::endl;
    }
    file.close();
}

void addItem() {
    string fileName;
    cout << "Введите имя файла: ";
    cin >> fileName;
    ofstream file(fileName, ios::app);
    if (!file) {
        cout << "Ошибка открытия файла!";
        return;
    }
    Item item;
    cout << "Введите наименование товара: ";
    cin.ignore();
    cin.getline(item.name, MAXLEN);
    cout << "Введите количество единиц товара: ";
    cin >> item.quantity;
    cout << "Введите цену за единицу товара: ";
    cin >> item.priceForOne;
    cout << "Введите дату поступления товара на склад: ";
    cin >> item.dateOfEntry;

    file << item.name << " " << item.quantity << " " << item.priceForOne << " " << item.dateOfEntry << endl;
    file.close();
    cout << "Товар добавлен в файл!";
}

void linearSearch(const char* searchItem) {
    string fileName;
    cout << "Введите имя файла: ";
    cin >> fileName;
    ifstream file(fileName);
    if (!file) {
        cout << "Файл не найден или не может быть открыт.";
        return;
    }

    char searchName[MAXLEN];
    cout << "Введите название товара для поиска: ";
    cin.ignore();
    cin.getline(searchName, MAXLEN);

    Item item;
    bool found = false;
    while (file >> item.name >> item.quantity >> item.priceForOne >> item.dateOfEntry) {
        if (strcmp(item.name, searchName) == 0) {
            cout << "Товар найден:\n";
            cout << "Наименование: " << item.name << "\n";
            cout << "Количество: " << item.quantity << "\n";
            cout << "Цена за единицу: " << item.priceForOne << "\n";
            cout << "Дата поступления: " << item.dateOfEntry << "\n";
            found = true;
        }
    }
    file.close();
    if (!found) {
        cout << "Товар не найден!";
    }
}


void selectionSort(const char* fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Файл не найден или не может быть открыт" << endl;
        return;
    }

    Item items[100]; // Массив для хранения всех товаров
    int numItems = 0;

    // Чтение данных из файла
    while (file >> items[numItems].name >> items[numItems].quantity >> items[numItems].priceForOne >> items[numItems].dateOfEntry) {
        numItems++;
    }
    file.close();

    // Сортировка выбором по наименованию товара
    for (int i = 0; i < numItems - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < numItems; j++) {
            if (strcmp(items[j].name, items[minIndex].name) < 0) { // Сравнение наименований товаров
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(items[i], items[minIndex]); // Обмен
        }
    }

    
        // Перезаписываем отсортированные данные в файл
        ofstream outFile(fileName, ios::out | ios::trunc);
    for (int i = 0; i < numItems; i++) {
        outFile << items[i].name << " " << items[i].quantity << " " << items[i].priceForOne << " " << items[i].dateOfEntry << endl;
    }
    outFile.close();

    cout << "Сортировка (selectionSort) завершена." << endl;
}

int partition(int low, int high, Item items[]) {
    Item pivot = items[high]; // Опорный элемент — последний товар в списке
    int i = low - 1; // Индекс меньшего элемента

    // Проходим по всем элементам массива
    for (int j = low; j < high; j++) {
        // Если текущий элемент меньше или равен опорному
        if (strcmp(items[j].name, pivot.name) < 0) {
            i++;
            swap(items[i], items[j]); // Меняем элементы местами
        }
    }
    swap(items[i + 1], items[high]); // Перемещаем опорный элемент на его правильную позицию
    return i + 1;
}

// Функция quickSort
void quickSort(int low, int high, Item items[]) {
    if (low < high) {
        int partitionIndex = partition(low, high, items); // Разделение массива и получение индекса опорного элемента
        quickSort(low, partitionIndex - 1, items); // Рекурсивная сортировка левой части
        quickSort(partitionIndex + 1, high, items); // Рекурсивная сортировка правой части
    }
}

// Главная функция для чтения файла и выполнения сортировки
void quickSort(const char* fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Файл не найден или не может быть открыт" << endl;
        return;
    }

    Item items[100]; // Массив для хранения всех товаров
    int numItems = 0;

    // Чтение данных из файла
    while (file >> items[numItems].name >> items[numItems].quantity >> items[numItems].priceForOne >> items[numItems].dateOfEntry) {
        numItems++;
    }

    file.close();

    // Вызов quickSort для сортировки
    quickSort(0, numItems - 1, items);

    // Запись отсортированных данных обратно в файл
    ofstream outFile(fileName, ios::out | ios::trunc);
    for (int i = 0; i < numItems; i++) {
        outFile << items[i].name << " " << items[i].quantity << " " << items[i].priceForOne << " " << items[i].dateOfEntry << endl;
    }

    outFile.close();

    cout << "Сортировка (Quick Sort) завершена." << endl;
}

void binarySearch(const char* fileName, const char* searchName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Файл не найден или не может быть открыт." << endl;
        return;
    }

    Item items[100];
    int numItems = 0;

    // Чтение данных из файла
    while (file >> items[numItems].name >> items[numItems].quantity >> items[numItems].priceForOne >> items[numItems].dateOfEntry) {
        numItems++;
    }
    file.close();

    // Сортировка данных для бинарного поиска
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = i + 1; j < numItems; j++) {
            if (strcmp(items[i].name, items[j].name) > 0) {
                swap(items[i], items[j]);
            }
        }
    }

    // Бинарный поиск для всех совпадений
    int left = 0, right = numItems - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(items[mid].name, searchName);

        if (cmp == 0) {
            found = true;
            cout << "Товар найден:\n";
            cout << "Наименование: " << items[mid].name << "\n";
            cout << "Количество: " << items[mid].quantity << "\n";
            cout << "Цена за единицу: " << items[mid].priceForOne << "\n";
            cout << "Дата поступления: " << items[mid].dateOfEntry << "\n";

            // Продолжение поиска влево и вправо от найденного элемента
            int temp = mid - 1;
            while (temp >= 0 && strcmp(items[temp].name, searchName) == 0) {
                cout << "Товар найден:\n";
                cout << "Наименование: " << items[temp].name << "\n";
                cout << "Количество: " << items[temp].quantity << "\n";
                cout << "Цена за единицу: " << items[temp].priceForOne << "\n";
                cout << "Дата поступления: " << items[temp].dateOfEntry << "\n";
                temp--;
            }

            temp = mid + 1;
            while (temp < numItems && strcmp(items[temp].name, searchName) == 0) {
                cout << "Товар найден:\n";
                cout << "Наименование: " << items[temp].name << "\n";
                cout << "Количество: " << items[temp].quantity << "\n";
                cout << "Цена за единицу: " << items[temp].priceForOne << "\n";
                cout << "Дата поступления: " << items[temp].dateOfEntry << "\n";
                temp++;
            }

            break;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "Товар не найден." << endl;
    }
}

void findItemOverMonth(const char* fileName) {
    string outputFileName;
    cout << "Введите имя файла для записи результата: ";
    cin >> outputFileName;

    int enteredMonth, enteredDay, enteredYear;
    cout << "Введите текущий номер месяца (1 - Январь, 2 - Февраль и т.д.): ";
    cin >> enteredMonth;
    cout << "Введите текущий день месяца: ";
    cin >> enteredDay;
    cout << "Введите текущий год: ";
    cin >> enteredYear;

    ifstream file(fileName);
    if (!file) {
        cerr << "Файл не найден или не может быть открыт." << endl;
        return;
    }

    ofstream outFile(outputFileName);
    if (!outFile) {
        cerr << "Ошибка создания выходного файла!" << endl;
        return;
    }

    /*Item item;
    while (file >> item.name >> item.quantity >> item.priceForOne >> item.dateOfEntry) {
        // Извлечение данных из даты поступления (формат MMDDYY)
        int itemMonth = (item.dateOfEntry[0] - '0') * 10 + (item.dateOfEntry[1] - '0'); // Месяц
        int itemDay = (item.dateOfEntry[2] - '0') * 10 + (item.dateOfEntry[3] - '0');   // День
        int itemYear = (item.dateOfEntry[4] - '0') * 10 + (item.dateOfEntry[5] - '0');  // Год

        // Условия проверки:
        bool addToFile = false;

        // Условие 1: Если текущий год больше года поступления на 1 и больше ++
        if (enteredYear > itemYear + 1) {
            addToFile = true;
        }
        // Условие 2: Если текущий месяц больше месяца поступления на 2
        else if (enteredMonth - itemMonth > 2) {
            addToFile = true;
        }
        // Условие 3: Если прошло более 28 дней
        else if
            (28 - itemDay + enteredDay > 28) {
            addToFile = true;
        }

        // Запись в файл, если товар удовлетворяет условиям
        if (addToFile) {
            outFile << item.name << " " << item.quantity << " " << item.priceForOne << " " << item.dateOfEntry << endl;
            cout << "Товар удовлетворяет условиям: " << item.name << endl;
        }
    }

    outFile.close();
    file.close();
    cout << "Результаты записаны в файл: " << outputFileName << endl;
}*/
    Item item;
    while (file >> item.name >> item.quantity >> item.priceForOne >> item.dateOfEntry) {
        // Извлечение данных из даты поступления (формат MMDDYY)
        int itemMonth = (item.dateOfEntry[0] - '0') * 10 + (item.dateOfEntry[1] - '0'); // Месяц
        int itemDay = (item.dateOfEntry[2] - '0') * 10 + (item.dateOfEntry[3] - '0');   // День
        int itemYear = (item.dateOfEntry[4] - '0') * 10 + (item.dateOfEntry[5] - '0');  // Год

        // Условия проверки:
        bool addToFile = false;

        // Условие 1: Если текущий год больше года поступления на 1 и больше
        if (enteredYear > itemYear) {
            addToFile = true;

        }
        // Условие 2: Если текущий месяц больше месяца поступления на 2
        else if (enteredYear == itemYear && (enteredMonth - itemMonth > 1)) {
            addToFile = true;
        }
        // Условие 3: Если прошло более 28 дней
        else if (enteredYear == itemYear && enteredMonth == itemMonth &&
            (28 - itemDay + enteredDay > 28)) {
            addToFile = true;
        }

        // Запись в файл, если товар удовлетворяет условиям
        if (addToFile) {
            outFile << item.name << " " << item.quantity << " " << item.priceForOne << " " << item.dateOfEntry << endl;
            cout << "Товар удовлетворяет условиям: " << item.name << endl;
        }
    }
}


int main() {
    int choice;
    char item[MAXLEN];
    do {
        cout << "\n1.Создать файл\n2.Просмотреть файл\n3.Добавить товар\n4.Линейный поиск\n5.Сортировка прямым выбором\n";
        cout << "6.Сортировка quicksort\n7.Бинарный поиск\n8.Товары лежащие на складе больше месяца со стоимостью больше 100 000р\n9.Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createFile();
            break;
        case 2:
            viewFile();
            break;
        case 3:
            addItem();
            break;
        case 4:
            linearSearch(item);
            break;
        case 5: {
            char filename2[MAXLEN];
            cout << "Введите название файла: ";
            cin >> filename2;

            selectionSort(filename2);
            cout << "Сортировка выполнена!\n";
            break;
        }
        case 6: {
            char filename[MAXLEN];
            cout << "Введите название файла: ";
            cin >> filename;

            quickSort(filename);
            cout << "Сортировка выполнена!\n";
            break;
        }
        case 7: {
            char fileName[MAXLEN], searchName[MAXLEN];
            cout << "Введите имя файла: ";
            cin >> fileName;
            cout << "Введите название товара для поиска: ";
            cin.ignore();
            cin.getline(searchName, MAXLEN);

            binarySearch(fileName, searchName);
            break;
        }
        case 8:
            char fileName[MAXLEN];
            cout << "Введите имя файла: ";
            cin >> fileName;

            findItemOverMonth(fileName);
            break;
        
        case 9:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неправильный выбор! Попробуйте снова.\n";
            break;
        }

    } while (choice != 9);

    return 0;
}//в1
