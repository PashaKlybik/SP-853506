// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <ctime>
#include <chrono>
#include <string>
#include "Dir.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <dirent.h>

#define DT_DIR 4

bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

std::vector<std::string> explore(std::string path) {
	std::vector<std::string> file_names;
	Dir dir(path);
	for (const auto& ent : dir) {
		if (ent.d_type == DT_DIR && strcmp(ent.d_name, "..") && strcmp(ent.d_name, ".")) {
			std::string nested_dir_path = path + "/" + std::string(ent.d_name);
			std::vector<std::string> nested_file_names = explore(nested_dir_path);
			file_names.insert(file_names.end(), nested_file_names.begin(), nested_file_names.end());
		}
		file_names.push_back(ent.d_name);
	}
	return file_names;
}

int main(int argc, const char * argv[]) {

	std::string extension;
	std::cout << "Enter the extension: ";
	std::cin >> extension;

	std::string start_directory;
	std::cout << "Enter the directory to start exploring: ";
	std::cin >> start_directory;

	std::string file_path;
	std::cout << "Enter the path to output file: ";
	std::cin >> file_path;

	std::vector<std::string> files = explore(start_directory);

	auto end = std::chrono::system_clock::now();
	std::ofstream file(file_path, std::ios_base::app);
	if (files.empty()) {
		file << "There are no files with such extension" << std::endl;
	}
	else {
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		file << std::ctime(&end_time) << std::endl;
	}

	for (const auto& name : files) {
		if (hasEnding(name, extension)) {
			file << name << std::endl;
			std::cout << name << std::endl;
		}
	}
	file.close();

	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
