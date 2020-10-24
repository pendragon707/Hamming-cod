#include "message.h"
#include <clocale>
#include <locale>

int menu()
{
	int indicator;
	std::cout << "1 - Закодировать сообщение" << std::endl;
	std::cout << "2 - Передать сообщение со случайной ошибкой " << std::endl;
	std::cout << "3 - Передать сообщение с определённой ошибкой " << std::endl;
	std::cout << "4 - Декодировать сообщение " << std::endl;
	std::cout << "5 - Печать таблицы с корректирующей способностью " << std::endl;
	std::cout << "6 - Выход " << std::endl;
	std::cout << "Введите номер выбранного пункта меню: ";
	std::cin >> indicator;
	std::cout << std::endl;
	return indicator;
}

int main()
{
	srand( time(0) );

	Message message;
	std::vector<int> input;
	std::vector<int> input_error;
	while( true ) 
	{
		switch( menu() )
		{
			case 1:
				std::cout << "Введите вектор из 4 элементов, равных 1 или 0, нажимайте Enter " << std::endl;
				input = input_vector(4);
				std::cout << "Оригинальный вектор: ";
				print(input);
				std::cout << "Закодированный вектор: ";
				print(message.encode(input));
				break;
			case 2:
				std::cout << "Переданный вектор: ";
				print(message.get_message());
				std::cout << "Полученный вектор: ";
				print(message.transmit());
				break;
			case 3:
				std::cout << "Переданный вектор: ";
				print(message.get_message());
				std::cout << "Введите вектор ошибки из 7 элементов, равных 1 или 0, нажимайте Enter " << std::endl;
				input_error = input_vector(7);
				std::cout << "Ошибка: ";
				print(input_error);
				std::cout << "Полученный вектор: ";
				print(message.error(input_error));
				break;
			case 4:
				std::cout << "Закодированный вектор: ";
				print(message.get_message());
				std::cout << "Декодированный вектор: ";
				print(message.decode());
				break;
			case 5:
				print_table();
				break;
			case 6:
				return 0;
			default:
				return 0;

		}

	}
	return 0;
}
