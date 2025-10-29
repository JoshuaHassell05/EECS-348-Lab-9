#include <iostream>
#include <fstream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

void print_aligned(const Matrix& M, const char* title = nullptr) {
    if (title) {
        std::cout << title << std::endl;
    }
    if (M.empty()) {
        std::cout << "(empty)\n";
        return;
    }
    int n = (int)M.size();
    std::vector<int> widths(n, 1);
    for (int j = 0; j < n; ++j) {
        int max_width = 1;
        for (int i = 0; i < n; ++i) {
            int temp = M[i][j];
            int width = (temp <= 0) ? 1 : 0; 
            if (temp == 0) width = 1;
            while (temp != 0) {
                temp /= 10;
                width++;
            }
            if (width > max_width) {
                max_width = width;
            }
        }
        widths[j] = max_width;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num = M[i][j];
            int temp = num;
            int w = (temp <= 0) ? 1 : 0;
            if (temp == 0) w = 1;
            while (temp != 0) {
                temp /= 10;
                w++;
            }
            int spaces = widths[j] - w + 2; 
            while (spaces-- > 0) std::cout << ' ';

            std::cout << num;
        }
        std::cout << '\n';
    }
}
void load_matrices(const char* filename, Matrix& matrix1, Matrix& matrix2, int& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error: Cannot open file: " << std::endl;
        size = 0;
        return;
    }
    file >> size;
    if (!file || size <= 0) {
        std::cout << "Error: Invalid matrix size." << std::endl;
        size = 0;
        return;
    }
    matrix1.assign(size, std::vector<int>(size, 0));
    matrix2.assign(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (!(file >> matrix1[i][j])) {
                std::cout << "Error: insufficient data for matrix 1." << std::endl;
                size = 0; return;
            }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (!(file >> matrix2[i][j])) {
                std::cout << "Error: insufficient data for matrix 2." << std::endl;
                size = 0; return;
            }
    file.close();
    print_aligned(matrix1, "\nMatrix 1:");
    print_aligned(matrix2, "\nMatrix 2:");
}
void add_matrices(const Matrix& matrix1, const Matrix& matrix2, int size) {
    Matrix result(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = matrix1[i][j] + matrix2[i][j];
    std::cout << "Resultant Matrix after Addition:" << std::endl;
    print_aligned(result, nullptr);
}
void multiply_matrices(const Matrix& matrix1, const Matrix& matrix2, int size) {
    Matrix result(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            for (int k = 0; k < size; ++k)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
    std::cout << "Resultant Matrix after Multiplication:" << std::endl;
    print_aligned(result, nullptr);
}
void sum_diagonal_elements(const Matrix& matrix, int size) {
    int main_sum = 0;
    int secondary_sum = 0;
    for (int i = 0; i < size; ++i) {
        main_sum += matrix[i][i];
        secondary_sum += matrix[i][size - 1 - i];
    }
    std::cout << "\tMain diagonal sum: " << main_sum << std::endl;
    std::cout << "\tSecondary diagonal sum: " << secondary_sum << std::endl;
}
void swap_rows(Matrix& matrix, int size, int row1, int row2) {
    if (row1 < 0 || row2 < 0 || row1 >= size || row2 >= size) {
        std::cout << "Invalid row indices." << std::endl;
        return;
    }
    for (int j = 0; j < size; ++j) {
        int temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
    std::cout << "After swapping rows " << row1 << " and " << row2 << ":" << std::endl;
    print_aligned(matrix, nullptr);
}
void swap_columns(Matrix& matrix, int size, int col1, int col2) {
    if (col1 < 0 || col2 < 0 || col1 >= size || col2 >= size) {
        std::cout << "Invalid column indices." << std::endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        int temp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = temp;
    }
    std::cout << "After swapping columns " << col1 << " and " << col2 << ":" << std::endl;
    print_aligned(matrix, nullptr);
}
void update_element(Matrix& matrix, int size, int row, int col, int new_value) {
    if (row < 0 || col < 0 || row >= size || col >= size) {
        std::cout << "Invalid indices." << std::endl;
        return;
    }
    matrix[row][col] = new_value;
    std::cout << "After updating element at (" << row << ", " << col << ") to " << new_value << ":" << std::endl;
    print_aligned(matrix, nullptr);
}
int main() {
    Matrix matrix1;
    Matrix matrix2;
    int size = 0;
    char filename[256];
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    load_matrices(filename, matrix1, matrix2, size);
    add_matrices(matrix1, matrix2, size);
    multiply_matrices(matrix1, matrix2, size);
    std::cout << "Matrix 1 diagonal sums:\n";
    sum_diagonal_elements(matrix1, size);
    std::cout << "\nMatrix 2 diagonal sums:\n";
    sum_diagonal_elements(matrix2, size);
    int choice;
    Matrix* selected_matrix;
    std::cout << "Choose matrix for row swap (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = &matrix1;
    } else if (choice == 2) {
        selected_matrix = &matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int row1, row2;
    std::cout << "Enter first row indice to swap: ";
    std::cin >> row1;
    std::cout << "Enter secound row indice to swap ";
    std::cin >> row2;
    swap_rows(*selected_matrix, size, row1, row2);
    std::cout << "Choose matrix for column swap (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = &matrix1;
    } else if (choice == 2) {
        selected_matrix = &matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int col1, col2;
    std::cout << "Enter first column indice to swap: ";
    std::cin >> col1;
    std::cout << "Enter secound column indice to swap ";
    std::cin >> col2;
    swap_columns(*selected_matrix, size, col1, col2);
    std::cout << "Choose matrix to change the element of (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = &matrix1;
    } else if (choice == 2) {
        selected_matrix = &matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int row, col, new_value;
    std::cout << "Enter row index: ";
    std::cin >> row;
    std::cout << "Enter column index: ";
    std::cin >> col;
    std::cout << "Enter new value: ";
    std::cin >> new_value;
    update_element(*selected_matrix, size, row, col, new_value);
    return 0;
}