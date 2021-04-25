#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <vector>       // массив для хранения данных из csv файла
#include <algorithm>    // используем для random_shuffle, чтобы перемешать вектор

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};

int main() {
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;
  // меняете значение переменной operation на ту операцию, которую надо вам проанализировать
  string operation = "remove";
  // в переменной trials - кол-во прогонов
  int trials = 10;
  // ну тут по имени переменной думаю всё понятно
  string count_of_elements = "5000000";
  // номер набора данных, тоже меняете)
  string dataset = "01";
  if (operation == "insert") {
    for (int i = 0; i < trials; i++) {
      SplayTree sTree;
      string line = "1"; // нужна, чтобы прошел первый прогон, так как сначала строка пустая (в следующих операциях точно также)
      // открываем csv файл (в следующих операциях точно также)
      auto input_file = ifstream(path + "/insert/" + dataset + "/" + count_of_elements + ".csv");
      const auto time_point_before = chrono::steady_clock::now();
      // здесь находится участок кода, время которого необходимо замерить
      // заполнение дерева
      if (input_file) {
        while (line != "") {
          getline(input_file, line);
          if (line == "") {
            break;
          }
          sTree.insert(stoi(line)); //используем stoi(string to integer), так как первоначально line имеет тип string
        }
      }
      const auto time_point_after = chrono::steady_clock::now();
      input_file.close();
      const auto time_diff = time_point_after - time_point_before;
      const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
      cout << time_elapsed_ns << endl;
    }
  }
  if (operation == "search") {
    for (int i = 0; i < trials; i++) {
      SplayTree sTree;
      auto input_file = ifstream(path + "/5000000.csv");
      string line = "1";
      // заполнение дерева определенным датасетом с количеством элементов >= количества элемента при поиске
      if (input_file) {
        while (line != "") {
          getline(input_file, line);
          if (line == "") {
            break;
          }
          sTree.insert(stoi(line));
        }
      }
      input_file.close();
      input_file = ifstream(path + "/find/" + dataset + "/" + count_of_elements + ".csv");
      line = "1";
      const auto time_point_before = chrono::steady_clock::now();
      // замер операции поиск
      if (input_file) {
        while (line != "") {
          getline(input_file, line);
          if (line == "") {
            break;
          }
          sTree.search(stoi(line));
        }
      }
      const auto time_point_after = chrono::steady_clock::now();
      input_file.close();
      const auto time_diff = time_point_after - time_point_before;
      const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
      cout << time_elapsed_ns << endl;
    }
  }
  if (operation == "remove") {
    string line = "1";
    auto input_file = ifstream(path + "/remove/" + dataset + "/" + count_of_elements + ".csv");
    // создание вектора
    vector<int> csv;
    //заполнение вектора
    if (input_file) {
      while (line != "") {
        getline(input_file, line);
        if (line == "") {
          break;
        }
        csv.push_back(stoi(line));
      }
    }
    input_file.close();
    //перемешивание вектора
    random_shuffle(csv.begin(), csv.end());
    //прогонка
    for (int i = 0; i < trials; i++) {
      SplayTree sTree;  //создание дерева
      auto input_file = ifstream(path + "/remove/" + dataset + "/" + count_of_elements + ".csv");
      line = "1";
      //заполнение дерева
      while (line != "") {
        getline(input_file, line);
        if (line == "") {
          break;
        }
        sTree.insert(stoi(line));
      }
      input_file.close();
      //замер времени для операции remove
      const auto time_point_before = chrono::steady_clock::now();
      for (int element : csv) {
        sTree.remove(element);
      }
      const auto time_point_after = chrono::steady_clock::now();
      const auto time_diff = time_point_after - time_point_before;
      const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
      cout << time_elapsed_ns << endl;
    }
  }
  return 0;
}
