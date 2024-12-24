#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>

#define DEFAULT_FILE "students.txt"

struct Student {
	std::string surname;
	std::string passport;
	std::string gradeBook;
};

using IndexFile = std::map<std::string, Student>;

bool loadStudents(std::string_view filename,
		  IndexFile & passportIndex,
		  IndexFile & gradeBookIndex)
{
	std::ifstream file(filename.data());
	if (!file)
		return true;

	std::string line;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		Student student;
		if (!(iss >> student.surname >> student.passport >>
		      student.gradeBook)) {
			std::cerr << "Не удалось прочитать строку: " << line
				  << '\n';
			continue;
		}
		passportIndex[student.passport] = student;
		gradeBookIndex[student.gradeBook] = student;
	}

	return false;
}

void searchByPassport(IndexFile const & passportIndex,
		      std::string const & passport)
{
	auto it = passportIndex.find(passport);
	if (it == passportIndex.end()) {
		std::cout << "Студент с номером паспорта " << passport
			  << " не найден." << '\n';
		return;
	}
	Student const & student = it->second;
	std::cout << "Фамилия студента: " << student.surname
		  << ", номер паспорта: " << student.passport
		  << ", номер зачётной книжки: " << student.gradeBook << '\n';
}

void searchByGradeBook(IndexFile const & gradeBookIndex,
		       std::string const & gradeBook)
{
	auto it = gradeBookIndex.find(gradeBook);
	if (it == gradeBookIndex.end()) {
		std::cout << "Студент с номером зачётной книжки " << gradeBook
			  << " не найден." << '\n';
		return;
	}
	Student const & student = it->second;
	std::cout << "Фамилия студента: " << student.surname
		  << ", номер паспорта: " << student.passport
		  << ", номер зачётной книжки: " << student.gradeBook << '\n';
}

int main(int const argc, char const * const args[])
{
	IndexFile passportIndex;
	IndexFile gradeBookIndex;

	std::string_view fname{(argc > 1) ? args[1] : DEFAULT_FILE};

	// Загрузка данных студентов из файла
	if (loadStudents(fname, passportIndex, gradeBookIndex)) {
		std::perror(fname.data());
		return EXIT_FAILURE;
	}

	// Пример поиска
	std::string passport;
	std::cout << "Введите номер паспорта: ";
	std::cin >> passport;
	searchByPassport(passportIndex, passport);

	std::string gradeBook;
	std::cout << "Введите номер зачётной книжки: ";
	std::cin >> gradeBook;
	searchByGradeBook(gradeBookIndex, gradeBook);

	return EXIT_SUCCESS;
}
