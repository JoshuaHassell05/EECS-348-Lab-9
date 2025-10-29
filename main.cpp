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
int main (){
    int matrix1[max][max];
    int matrix2[max][max];
    int size;
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    load_matrices(filename, matrix1, matrix2, size);
    return 0;
}