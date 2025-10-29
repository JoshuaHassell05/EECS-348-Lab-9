#include <iostream>
#include <fstream>
const int max = 100;
void load_matrices(const std::string& filename, int matrix1[max][max], int matrix2[max][max], int& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error: Cannot open file: " << std::endl;
        return;
    }
    file >> size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix1[i][j];
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix2[i][j];
        }
    }
    file.close();
}
void add_matrices(int matrix1[max][max], int matrix2[max][max], int size) {
    int result[max][max];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    std::cout << "Resultant Matrix after Addition:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void multiply_matrices(int matrix1[max][max], int matrix2[max][max], int size) {
    int result[max][max] = {0};
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    std::cout << "Resultant Matrix after Multiplication:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void sum_diagonal_elements(int matrix[max][max], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += matrix[i][i];
    }
    std::cout << "Sum of diagonal elements: " << sum << std::endl;
}
void swap_rows(int matrix[max][max], int size, int row1, int row2) {
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
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void swap_columns(int matrix[max][max], int size, int col1, int col2) {
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
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void update_element(int matrix[max][max], int size, int row, int col, int new_value) {
    if (row < 0 || col < 0 || row >= size || col >= size) {
        std::cout << "Invalid indices." << std::endl;
        return;
    }
    matrix[row][col] = new_value;
    std::cout << "After updating element at (" << row << ", " << col << ") to " << new_value << ":" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int matrix1[max][max];
    int matrix2[max][max];
    int size;
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    load_matrices(filename, matrix1, matrix2, size);
    add_matrices(matrix1, matrix2, size);
    multiply_matrices(matrix1, matrix2, size);
    sum_diagonal_elements(matrix1, size);
    sum_diagonal_elements(matrix2, size);
    int choice;
    int (*selected_matrix)[max];
    std::cout << "Choose matrix for row swap (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = matrix1;
    } else if (choice == 2) {
        selected_matrix = matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int row1, row2;
    std::cout << "Enter two row indices to swap: ";
    std::cin >> row1 >> row2;
    swap_rows(selected_matrix, size, row1, row2);
    std::cout << "Choose matrix for column swap (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = matrix1;
    } else if (choice == 2) {
        selected_matrix = matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int col1, col2;
    std::cout << "Enter two column indices to swap ";
    std::cin >> col1 >> col2;
    swap_columns(selected_matrix, size, col1, col2);
    std::cout << "Choose matrix to change the element of (1 or 2): ";
    std::cin >> choice;
    if (choice == 1) {
        selected_matrix = matrix1;
    } else if (choice == 2) {
        selected_matrix = matrix2;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }
    int row, col, new_value;
    std::cout << "Enter row index, column index, and new value: ";
    std::cin >> row >> col >> new_value;
    update_element(selected_matrix, size, row, col, new_value);
    return 0;
}