// projectLab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Вариант 20
int main()
{
	const int n = 3;

	const int m = 3;

	srand(time(0));
	
	int k = 0;

	cout << "Vvedite k for check square matrix: " << endl;

	cin >> k;

	int arr[n][m];
	
	//Заполнение строк
	for (int i = 0; i < n; i++)
	{
		//Заполнение столбцов
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = rand() % 100;
			printf("%4.1i", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	if (k < 0) {
		cout << "K doljna bit bolshe 0";
		return 0;
	}

	//Опредения общего количества подквадратов: (n - k) * (m - k)
	for (int i = 0; i <= n - k; i++)
	{
		for (int j = 0; j <= m - k; j++)
		{
			//Передвижение квадрата по матрице
			for (int x = 0; x < k; x++)
			{
				for (int y = 0; y < k; y++)
				{
					printf("%1.1i ", arr[i + x][j + y]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}

	//Определение цвета

	//Очистка буфера ввода
	cin.ignore(1000, '\n');

	string text;
	cout << "Vvedite text: ";
	getline(cin, text);

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == '#') {
			// Проверка длинного цвета #ffffff
			if (i + 6 < text.length() &&
				//Проверка на шестандцеричный цифрой
				isxdigit(text[i + 1]) &&
				isxdigit(text[i + 2]) &&
				isxdigit(text[i + 3]) &&
				isxdigit(text[i + 4]) &&
				isxdigit(text[i + 5]) &&
				isxdigit(text[i + 6])) {
				cout << text.substr(i, 7) << endl;
				i += 6;
			}
			// Проверка короткого цвета #fff
			else if (i + 3 < text.length() &&
				isxdigit(text[i + 1]) &&
				isxdigit(text[i + 2]) &&
				isxdigit(text[i + 3])) {
				cout << text.substr(i, 4) << endl;
				i += 3;
			}
		}
	}

}