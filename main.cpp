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
int main (){
    int matrix1[max][max];
    int matrix2[max][max];
    int size;
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    load_matrices(filename, matrix1, matrix2, size);
    add_matrices(matrix1, matrix2, size);
    multiply_matrices(matrix1, matrix2, size);
    return 0;
}