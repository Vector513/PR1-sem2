#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

int currStudent = 0;
int currVb = 0;
const int countStudents = 200;
const int countVB = 50;
const int countGrades = 8;
const int stringLength = 40;
const int lengths[countGrades] = { 9, 3, 16, 9, 3, 10, 6, 11 };
const int sLength = 121;
const int fsLength = 88;
const char subjects[countGrades][stringLength] = {"Матанализ", "АИГ", "Программирование", "Философия", "ОРГ", "Английский", "Физика", "Информатика"};
const char separator[sLength] = "------------------------------------------------------------------------------------------------------------------------";
const char fileSeparator[fsLength] = "---------------------------------------------------------------------------------------";

struct Student
{
	char name[stringLength] = "Unknown";
	char surname[stringLength] = "Unknown";
	char patronymic[stringLength] = "Unknown";
	char sex = '?';
	int group = 0;
	int id = 0;
	int grades[countGrades] = {}; // >>
	float avgScore = 0;
	float getAvgScore() 
	{
		int sum = 0;
		for (int i = 0; i < countGrades; i++) {
			sum += grades[i];
		}
		avgScore = float(sum) / countGrades;
		return avgScore;
	}
};

struct Valleyballer 
{
	char name[stringLength] = "Unknown";
	char surname[stringLength] = "Unknown";
	char patronymic[stringLength] = "Unknown";
	char sex = '?';
	int age = 0;
	char clothingSize[stringLength] = "Unknown";
	bool sportCategory = 0;
	int course = 0;
};

Student students[countStudents] = {};
Valleyballer vbs[countVB] = {};

/*
bool compare(char string1[], char string2[]) 
{
	int i = 0;
	for (; i < stringLength; i++) {
		if (string1[i] != string2[i]) {
			cout << i;
			return false;
		}
		else if (string1[i] == '\0' || string2[i] == '\0') {
			break;
		}
	}
	cout << i;
	return true;
}
*/

void createRecord(Student* student)
{
	cout << "ФИО: ";
	cin >> student->surname >> student->name >> student->patronymic;
	cout << "Пол: ";
	cin >> student->sex;
	cout << "Номер группы: ";
	cin >> student->group;
	cout << "Номер в списке группы: ";
	cin >> student->id;
	for (int i = 0; i < countGrades; i++) {
		cout << subjects[i] << ": ";
		cin >> student->grades[i];
	}
}

void createVb(Valleyballer* player) 
{
	cout << "ФИО: ";
	cin >> player->surname >> player->name >> player->patronymic;
	cout << "Пол: ";
	cin >> player->sex;
	cout << "Возраст: ";
	cin >> player->age;
	cout << "Размер одежды: ";
	cin >> player->clothingSize;
	cout << "Наличие разряда: ";
	cin >> player->sportCategory;
	cout << "Номер курса: ";
	cin >> player->course;

}

void showRecord(Student* student)
{
	cout << "ФИО: " << student->surname << ' ' << student->name << ' ' << student->patronymic << '\n';
	cout << "Пол: " << student->sex << '\n';
	cout << "Номер группы: " << student->group << '\n';
	cout << "Номер в списке группы: " << student->id << '\n';
	for (int i = 0; i < countGrades; i++) {
		cout << subjects[i] << ": " << student->grades[i] << '\n';
	}
}

void showValleyballer(Valleyballer* vb) 
{
	cout << "ФИО: " << vb->surname << ' ' << vb->name << ' ' << vb->patronymic << '\n';
	cout << "Пол: " << vb->sex << '\n';
	cout << "Возраст: " << vb->age << '\n';
	cout << "Размер одежды: " << vb->clothingSize << '\n';
	cout << "Наличие разряда: " << vb->sportCategory << '\n';
	cout << "Номер курса: " << vb->course << '\n';
}

void readFile(ifstream& file, Student* students)
{
	while (file.peek() != EOF) {
		file.seekg(5, ios::cur);
		file >> (students+currStudent)->surname >> (students + currStudent)->name >> (students + currStudent)->patronymic;
		file.seekg(6, ios::cur);
		file >> (students + currStudent)->sex;
		file.seekg(15, ios::cur);
		file >> (students + currStudent)->group;
		file.seekg(24, ios::cur);
		file >> (students + currStudent)->id;
		for (int i = 0; i < countGrades; i++) {
			//file.seekg(subjects[i].length() + 3, ios::cur);
			file.seekg(lengths[i] + 3, ios::cur);
			file >> (students + currStudent)->grades[i];
		}
		//file.seekg(fileSeparator.length() + 4, ios::cur);
		file.seekg(fsLength + 3, ios::cur);

		currStudent++;
	}
}

void readFileVb(ifstream& file, Valleyballer* vbs) 
{
	while (file.peek() != EOF) {
		file.seekg(5, ios::cur);
		file >> (vbs + currVb)->surname >> (vbs + currVb)->name >> (vbs + currVb)->patronymic;
		file.seekg(6, ios::cur);
		file >> (vbs + currVb)->sex;
		file.seekg(10, ios::cur);
		file >> (vbs + currVb)->age;
		file.seekg(16, ios::cur);
		file >> (vbs + currVb)->clothingSize;
		file.seekg(18, ios::cur);
		file >> (vbs + currVb)->sportCategory;
		file.seekg(14, ios::cur);
		file >> (vbs + currVb)->course;
		//file.seekg(fileSeparator.length() + 4, ios::cur);
		file.seekg(fsLength + 3, ios::cur);

		currVb++;
	}
}

void writeFile(ofstream& file, Student* student)
{
	file << "ФИО: " << student->surname << ' ' << student->name << ' ' << student->patronymic << '\n';
	file << "Пол: " << student->sex << '\n';
	file << "Номер группы: " << student->group << '\n';
	file << "Номер в списке группы: " << student->id << '\n';
	for (int i = 0; i < countGrades; i++) {
		file << subjects[i] << ": " << student->grades[i] << '\n';
	}

	file << fileSeparator << '\n';
}

void writeFileVb(ofstream& file, Valleyballer* vb) 
{
	file << "ФИО: " << vb->surname << ' ' << vb->name << ' ' << vb->patronymic << '\n';
	file << "Пол: " << vb->sex << '\n';
	file << "Возраст: " << vb->age << '\n';
	file << "Размер одежды: " << vb->clothingSize << '\n';
	file << "Наличие разряда: " << vb->sportCategory << '\n';
	file << "Номер курса: " << vb->course << '\n';

	file << fileSeparator << '\n';
}

//	Павелко Владислав Сергеевич М 3372 19 3 3 5 4 4 5 4 4
//	Баранов Алексей Александрович М 3372 2 4 3 3 5 5 5 4 5
//	Беляев Кирилл Валерьевич М 3372 3 5 5 5 5 5 5 5 5
//	Зайцев Богдан Андреевич М 8342 11 5 5 5 5 5 5 5 5
//	Веселов Алексей Сергеевич М 3372 6 3 3 3 3 3 3 3 3
//	Петухов Евгений Николаевич М 3372 22 3 3 3 3 5 3 3 4 
//	Чепрасов Артём Геннадиевич М 3372 28 4 4 4 4 4 4 4 4
//	Долгих Алексей Михайлович М 3373 9 3 4 3 4 3 4 4 3


// Павелко Владислав Сергеевич М 17 L 1 1
// Рогут Мария Андреевна Ж 18 S 0 2
// Петухов Евгений Николаевич М 19 XS 1 3
void launch()
{
	ifstream fromFile, fromFileVb;
	ofstream inFile, inFileVb;
	char path[] = "students.txt";
	char pathVb[] = "valleyballers.txt";
	fromFile.open(path, ios::in);
	fromFileVb.open(pathVb, ios::in);
	inFile.open(path, ios::app);
	inFileVb.open(pathVb, ios::app);

	if (fromFile.is_open() && inFile.is_open() && inFileVb.is_open() && fromFileVb.is_open()) {
		readFile(fromFile, students);
		readFileVb(fromFileVb, vbs);
		cout << "Файл был открыт и обработан\n" << separator << '\n';
	}
	else {
		cout << "Файл не был открыт\n" << separator << '\n';
	}

	char commands[] = "1) Создать новую запись о студенте из консоли\n2) Внести изменения в уже имеющуюся запись\n3) Вывести все данные о студентах\n4) Вывести информацию обо всех студентах группы N\n5) Вывести топ самых успешных студентов с наивысшим по рейтнгу средним баллов за прошедшую сессию\n6) Вывести количества студентов мужского и женского пола\n7) Вывести данные о студентах, которые не получают стипендию; учатся только на \"хорошо\" и \"отлично\"; учатся только на \"отлично\"\n8) Вывести данные о студентах, имеющих номер в списке - k\nis) Вывести данные о всех волейболистах\ni0) Ввести данные о волейболисте\ni1) Вывести данные о студентах, имеющих разряд по волейболу\ni2) Вывести данные о женской сборной волейбольной спортивной секции\ni3) Вывести данные обо всех студентах k курса\ni4) Вывести данные о студентах мужского пола, чей размер одежды больше, чем S\nc) Вывести список комманд\ne) Выйти из программы\n";

	char command = 'c';

	do {
		if (command == 'e') {
			cout << "Программа завершена по воле пользователя\n";
			fromFile.close();
			fromFileVb.close();
			inFile.close();
			inFileVb.close();
			break;
		}

		else if (command == 'c') {
			cout << commands;
		}

		else if (command == '1') {
			cout << "Введите данные о студенте: \n";
			createRecord(&students[currStudent]);
			writeFile(inFile, &students[currStudent]);
			currStudent++;
			cout << "Запись создана и добавлена в файл\n";
		}

		else if (command == '2') {
			cout << "Введите ФИО студента запись которого хотите изменить: ";
			char surname[stringLength], name[stringLength], patronymic[stringLength];
			cin >> surname >> name >> patronymic;
			bool isThere = false;
			for (int i = 0; i < currStudent; i++) {
				if (*students[i].surname == *surname && *students[i].name == *name && *students[i].patronymic == *patronymic) {
					createRecord(&students[i]);
					isThere = true;
					break;
				}
			}

			if (isThere) {
				cout << "Запись студента была отредактирована\n";
			}
			else {
				cout << "Запись студента не была найдена\n";
			}

		}

		else if (command == '3') {
			for (int i = 0; i < currStudent; i++) {
				cout << separator << '\n';
				showRecord(&students[i]);
			}
		}

		else if (command == '4') {
			cout << "Введите номер группы: ";
			int group;
			cin >> group;

			bool isThere = false;
			for (int i = 0; i < currStudent; i++) {
				if (students[i].group == group) {
					cout << separator << '\n';
					showRecord(&students[i]);
					isThere = true;
				}
			}

			if (!isThere) {
				cout << "Нет записей студентов группы " << group << '\n';
			}
		}
		
		else if (command == '5') {
			for (int i = 0; i < currStudent; i++) {
				bool notSwap = true;
				for (int j = 0; j < currStudent - 1 - i; j++) {
					if (students[j].getAvgScore() < students[j + 1].getAvgScore()) {
						swap(students[j], students[j + 1]);
						notSwap = false;
					}
				}
				if (notSwap) {
					break;
				}
			}

			for (int i = 1; i <= min(currStudent, 5); i++) {
				cout << i << " место: " << students[i-1].surname << ' ' << students[i-1].name << ' ' << students[i-1].patronymic << ": " << students[i-1].avgScore << '\n';
			}
		}

		else if (command == '6') {
			int men = 0, women = 0;
			for (int i = 0; i < currStudent; i++) {
				if (students[i].sex == 'М') {
					men++;
				}
				else if (students[i].sex == 'Ж') {
					women++;
				}
			}

			cout << "Количество студентов мужского пола: " << men << '\n' << "Количество студентов женского пола: " << women << '\n';
		}

		else if (command == '7') {
			cout << "Студенты, которые не получают стипендию: \n\n";
			for (int i = 0; i < currStudent; i++) {
				bool flag = false;
				for (int j = 0; j < countGrades; j++) {
					if (students[i].grades[j] == 3) {
						flag = true;
						break;
					}
				}
				if (flag) {
					//cout << students[i].surname << ' ' << students[i].name << ' ' << students[i].patronymic << "\n";
					cout << separator;
					showRecord(&students[i]);
				}
			}

			cout << separator << "\n\nСтуденты, которые учатся на \"хорошо\" и \"отлично\": \n\n";
			for (int i = 0; i < currStudent; i++) {
				bool flag1 = true, flag2 = false;
				for (int j = 0; j < countGrades; j++) {
					if (students[i].grades[j] == 3) {
						flag1 = false;
						break;
					}
					else if (students[i].grades[j] == 4) {
						flag2 = true;
					}
				}
				if (flag1 && flag2) {
					//cout << students[i].surname << ' ' << students[i].name << ' ' << students[i].patronymic << "\n";
					cout << separator;
					showRecord(&students[i]);
				}
			}

			cout << separator << "\n\nСтуденты, которые учатся на \"отлично\": \n\n";
			for (int i = 0; i < currStudent; i++) {
				bool flag = true;
				for (int j = 0; j < countGrades; j++) {
					if (students[i].grades[j] < 5 && j != 7) {
						flag = false;
						break;
					}
				}
				if (flag) {
					//cout << students[i].surname << ' ' << students[i].name << ' ' << students[i].patronymic << "\n";
					cout << separator;
					showRecord(&students[i]);
				}
			}
		}

		else if (command == '8') {
			cout << "Введите номер в списках групп: ";
			int k;
			cin >> k;

			for (int i = 0; i < currStudent; i++) {
				if (students[i].id == k) {
					cout << separator;
					showRecord(&students[i]);
				}
			}
		}

		else if (command == 'i') {
			cin >> command;
			
			if (command == 's') {
				for (int i = 0; i < currVb; i++) {
					cout << separator;
					showValleyballer(&vbs[i]);
				}
			}

			else if (command == '0') {
				createVb(&vbs[currVb]);
				writeFileVb(inFileVb, &vbs[currVb]);
				currVb++;
				cout << "Запись создана\n";
			}

			else if (command == '1') {
				for (int i = 0; i < currVb; i++) {
					if (vbs[i].sportCategory) {
						cout << separator << '\n';
						showValleyballer(&vbs[i]);
					}
				}
			}

			else if (command == '2') {
				for (int i = 0; i < currVb; i++) {
					if (vbs[i].sex == 'Ж') {
						cout << separator << '\n';
						showValleyballer(&vbs[i]);
					}
				}
			}

			else if (command == '3') {
				cout << "Введите номер курса: ";
				int course;
				cin >> course;

				for (int i = 0; i < currVb; i++) {
					if (vbs[i].course == course) {
						cout << separator << '\n';
						showValleyballer(&vbs[i]);
					}
				}
			}

			else if (command == '4') {
				char cs1[stringLength] = "XS", cs2[stringLength] = "S";
				for (int i = 0; i < currVb; i++) {
					if (*vbs[i].clothingSize != *cs1 && *vbs[i].clothingSize != *cs2) {
						cout << separator << '\n';
						showValleyballer(&vbs[i]);
					}
				}
			}
		}

		cout << separator << '\n';
		cout << "Введите комманду: ";
		cin >> command;
		cout << '\n';

	} while (true);
}

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	/**
	fstream inFile;
	char path[] = "students.txt";
	inFile.open(path);

	if (inFile.is_open()) {
		cout << "Файл был открыт\n";
		inFile << "HUIIIIIIIIIIIIIIIIIIIIIIIIIIii\n";
	}
	else {
		cout << "Ошибка\n";
	}
	*/
	launch();


	return 0;
}