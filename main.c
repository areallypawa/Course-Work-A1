#include <stdio.h>
#include <stdlib.h>

// Очистка консоли
void clear();
// Пауза консоли
void pause();
// Вывод меню и подменю
void show_menu(int l);
// Функция для создания квадратной матрицы N×N
int** create_square_matrix(int n);
// Функция для ввода матрицы
void input_matrix(int** matrix, int n, char matrix_num);
// Функция для освобождения памяти
void free_matrix(int** matrix, int n);
// Функция для вывода матрицы с нумерацией
void print_matrix(int** matrix, int n, char name);
// Функция для считывания чисел с файла в матрицы
int read_matrices_from_file(const char* filename, int*** A, int*** B, int*** C, int* n);
// Функция для сохранения всех трех матриц в один файл
int save_all_matrices_to_file(const char* filename, int** A, int** B, int** C, int n);
// Функция для редактирования элемента матрицы
void edit_matrix_element(int** matrix, int n, char matrix_name);
// Функция умножения матрицы на скаляр (изменяет исходную матрицу)
void multiply_matrix_by_scalar(int** matrix, int n, char matrix_name);
// Функция проверки, является ли матрица C произведением матриц A и B
int is_matrix_product(int** A, int** B, int** C, int n);

// Основная функция 
int main() {
    setlocale(0, "Ru");
    int n = 0;
    int** matrix_A = NULL;
    int** matrix_B = NULL;
    int** matrix_C = NULL;
    int user_choice;
    int user_choice_matrix;


    while (1) {
        clear();
        show_menu(1);

        scanf_s("%d", &user_choice);

        switch (user_choice) {
        case 0:
            return 1;
            break;
        case 1:
        {
            clear();
            // Ввод размерности матрицы
            printf("Введите размер квадратной матрицы (N): ");
            scanf("%d", &n);


            if (n <= 0) {
                printf("Размер матрицы должен быть положительным числом!\n");
                return 1;
            }

            // Создание матрицы
            matrix_A = create_square_matrix(n);
            matrix_B = create_square_matrix(n);
            matrix_C = create_square_matrix(n);
            if (matrix_A == NULL || matrix_B == NULL || matrix_C == NULL) {
                // Освобождаем то, что успели создать
                if (matrix_A) free_matrix(matrix_A, n);
                if (matrix_B) free_matrix(matrix_B, n);
                if (matrix_C) free_matrix(matrix_C, n);
                return 1;
            }
            // Ввод элементов матрицы
            input_matrix(matrix_A, n, 'A');
            input_matrix(matrix_B, n, 'B');
            input_matrix(matrix_C, n, 'C');

            break;
        }
        case 2:
        {
            clear();
            // Ввод размерности матрицы
            printf("Введите размер квадратной матрицы (N): ");
            scanf("%d", &n);
            // Ввод с файла
            read_matrices_from_file("C:\\Users\\neiln\\source\\repos\\Kurs_Sasha\\Matrix.txt", &matrix_A, &matrix_B, &matrix_C, &n);
            pause();
            break;
        }
        case 3:
        {
            clear();
            // Вывод всех матриц в одну строку (компактный вариант)
            print_matrix(matrix_A, n, 'A');
            print_matrix(matrix_B, n, 'B');
            print_matrix(matrix_C, n, 'C');
            pause();

            break;
        }
        case 4:
        {
            clear();
            if (n == 0 || !matrix_A || !matrix_B || !matrix_C) {
                printf("Нет матриц для сохранения!\n");
                break;
            }
            save_all_matrices_to_file("C:\\Users\\neiln\\source\\repos\\Kurs_Sasha\\output.txt", matrix_A, matrix_B, matrix_C, n);
            pause();
            break;
        }
        case 5:
        {
            clear();
            show_menu(3);
            scanf("%d", &user_choice);
            switch (user_choice) {
            case 0:
                break;
            case 1:
                clear();
                show_menu(2);
                scanf("%d", &user_choice_matrix);
                switch (user_choice_matrix) {
                case 0:
                    break;
                case 1:
                    edit_matrix_element(matrix_A, n, 'A');
                    break;
                case 2:
                    edit_matrix_element(matrix_B, n, 'B');
                    break;
                case 3:
                    edit_matrix_element(matrix_C, n, 'C');
                    break;
                }
                break;
            case 2:
                clear();
                show_menu(2);
                scanf("%d", &user_choice_matrix);
                switch (user_choice_matrix) {
                case 0:
                    break;
                case 1:
                    multiply_matrix_by_scalar(matrix_A, n, 'A');
                    break;
                case 2:
                    multiply_matrix_by_scalar(matrix_B, n, 'B');
                    break;
                case 3:
                    multiply_matrix_by_scalar(matrix_C, n, 'C');
                    break;
                }
            }
            break;
        }
        case 6:
        {
            clear();
            is_matrix_product(matrix_A, matrix_B, matrix_C, n);
            pause();
            break;
        }
        }
    }
    return 0;
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    printf("\n");
    system("Pause");
}

void show_menu(int l) {
    switch (l) {
    case 1:
        printf("================ MENU ================\n");
        printf("| 1. Создать матрицы A, B, C в ручную\n");
        printf("| 2. Взять матрицы A, B, C из файла\n");
        printf("| 3. Показать все матрицы\n");
        printf("| 4. Сохранить матрицы в файлы\n");
        printf("| 5. Редактировать элемент матрицы A\n");
        printf("| 6. Определить, является ли матрица С результатом перемножения матриц А и В\n");
        printf("| 0. Выход\n");
        break;
    case 2:
        printf("======== MENU =======\n");
        printf("| 1. Редактировать А\n");
        printf("| 2. Редактировать B\n");
        printf("| 3. Редактировать С\n");

        printf("| 0. Выход\n");
        break;
    case 3:
        printf("============= MENU ============\n");
        printf("| 1. Изменить один элемент\n");
        printf("| 2. Умножить матрицу на скаляр\n");

        printf("| 0. Выход\n");
    }

    printf("Input: ");
}

// Функция для создания квадратной матрицы N×N
int** create_square_matrix(int n) {
    // Выделяем память под массив указателей на строки
    int** matrix = (int**)malloc(n * sizeof(int*));

    if (matrix == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    // Выделяем память для каждой строки
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d!\n", i);
            // Освобождаем ранее выделенную память
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

// Функция для ввода матрицы
void input_matrix(int** matrix, int n, char matrix_num) {
    printf("\n=== Матрица %c ===\n", matrix_num);
    printf("Введите %d чисел для матрицы %dx%d:\n", n * n, n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Функция для освобождения памяти
void free_matrix(int** matrix, int n) {
    if (matrix == NULL) return;

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для вывода матрицы с нумерацией
void print_matrix(int** matrix, int n, char name) {
    printf("\n=== Матрица %c (%dx%d) ===\n", name, n, n);

    // Верхняя граница
    printf("+");
    for (int j = 0; j < n; j++) {
        printf("---");
        if (j < n - 1) printf("+");
    }
    printf("+\n");

    // Элементы матрицы
    for (int i = 0; i < n; i++) {
        printf("|");
        for (int j = 0; j < n; j++) {
            printf("%3d", matrix[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("|\n");

        // Разделительная линия между строками (кроме последней)
        if (i < n - 1) {
            printf("+");
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j < n - 1) printf("+");
            }
            printf("+\n");
        }
    }

    // Нижняя граница
    printf("+");
    for (int j = 0; j < n; j++) {
        printf("---");
        if (j < n - 1) printf("+");
    }
    printf("+\n");
}

// Считывание чисел с файла в матрицы
int read_matrices_from_file(const char* filename, int*** A, int*** B, int*** C, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }

    // Создаем матрицы
    *A = create_square_matrix(*n);
    *B = create_square_matrix(*n);
    *C = create_square_matrix(*n);

    if (*A == NULL || *B == NULL || *C == NULL) {
        printf("Ошибка выделения памяти для матриц\n");
        fclose(file);
        return 0;
    }

    // Читаем матрицу A
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &(*A)[i][j]) != 1) {
                printf("Ошибка чтения элемента A[%d][%d]\n", i, j);
                fclose(file);
                return 0;
            }
        }
    }

    // Читаем матрицу B
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &(*B)[i][j]) != 1) {
                printf("Ошибка чтения элемента B[%d][%d]\n", i, j);
                fclose(file);
                return 0;
            }
        }
    }

    // Читаем матрицу C
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &(*C)[i][j]) != 1) {
                printf("Ошибка чтения элемента C[%d][%d]\n", i, j);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    printf("Матрицы успешно загружены из файла %s\n", filename);
    return 1;
}

// Функция для сохранения всех трех матриц в один файл
int save_all_matrices_to_file(const char* filename, int** A, int** B, int** C, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка создания файла %s\n", filename);
        return 0;
    }

    // Записываем размер матриц
    fprintf(file, "%d\n\n", n);

    // Записываем матрицу A
    fprintf(file, "Матрица A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", A[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    // Записываем матрицу B
    fprintf(file, "Матрица B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", B[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    // Записываем матрицу C
    fprintf(file, "Матрица C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", C[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Все матрицы сохранены в файл %s\n", filename);
    return 1;
}

// Функция для редактирования элемента матрицы
void edit_matrix_element(int** matrix, int n, char matrix_name) {
    int row, col, new_value;

    print_matrix(matrix, n, matrix_name);
    // Ввод координат элемента
    printf("\nВведите номер строки (1-%d): ", n);
    scanf("%d", &row);
    printf("Введите номер столбца (1-%d): ", n);
    scanf("%d", &col);

    // Проверка корректности координат
    if (row < 1 || row > n || col < 1 || col > n) {
        printf("Ошибка: координаты должны быть в диапазоне 1-%d\n", n);
        return;
    }

    // Преобразуем в индексы C (0-based)
    row--;
    col--;

    // Показываем текущее значение
    printf("Текущее значение элемента [%d][%d]: %d\n",
        row + 1, col + 1, matrix[row][col]);

    // Ввод нового значения
    printf("Введите новое значение: ");
    scanf("%d", &new_value);

    // Изменение значения
    matrix[row][col] = new_value;

    printf("Элемент успешно изменен!\n");
    pause();
}

// Функция умножения матрицы на скаляр (изменяет исходную матрицу)
void multiply_matrix_by_scalar(int** matrix, int n, char matrix_name) {
    int scalar;
    print_matrix(matrix, n, matrix_name);
    printf("\nВведи скаляр: ");
    scanf("%d", &scalar);

    printf("\nУмножение матрицы %dx%d на скаляр %d...\n", n, n, scalar);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] *= scalar;
        }
    }
    print_matrix(matrix, n, matrix_name);
    pause();
}

// Функция проверки, является ли матрица C произведением матриц A и B
int is_matrix_product(int** A, int** B, int** C, int n) {
    // Проверка входных данных
    if (A == NULL || B == NULL || C == NULL || n <= 0) {
        printf("Ошибка: некорректные входные данные\n");
        return 0;
    }

    printf("Проверка: C = A * B?\n");
    printf("Размер матриц: %dx%d\n", n, n);

    // Проверяем каждый элемент
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Вычисляем элемент произведения A * B
            int calculated = 0;
            for (int k = 0; k < n; k++) {
                calculated += A[i][k] * B[k][j];
            }

            // Сравниваем с соответствующим элементом матрицы C
            if (calculated != C[i][j]) {
                printf("Найдено несоответствие:\n");
                printf("C[%d][%d] = %d\n", i, j, C[i][j]);
                printf("(A*B)[%d][%d] = %d\n", i, j, calculated);
                printf("Элементы не равны!\n");
                return 0; // false
            }
        }
    }

    printf("Проверка пройдена: C действительно равно A * B\n");
    return 1; // true
}

