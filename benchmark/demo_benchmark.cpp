#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};

int main() {
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;

  int trials = 10;
  string files[1] = {"01"};
  SplayTree sTree;
  for(string elem : files) {
    for (int i = 0; i < trials; i++) {
      string line = "1";
      auto input_file = ifstream(path + "/insert/" + elem + "/1000000.csv");
      const auto time_point_before = chrono::steady_clock::now();
      // здесь находится участок кода, время которого необходимо замерить

      if (input_file) {
        while (line != "") {
          getline(input_file, line);
          if (line == "") {
            break;
          }
          sTree.insert(stoi(line));
        }
      }
      const auto time_point_after = chrono::steady_clock::now();
      Node *curr = sTree.root;
      sTree.Clear(curr);
      input_file.close();
      const auto time_diff = time_point_after - time_point_before;
      const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
      cout << time_elapsed_ns << endl;
    }
  }
  return 0;
}
