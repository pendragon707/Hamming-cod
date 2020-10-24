#ifndef ADD_H
#define ADD_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

std::vector<int> dot(const std::vector<int> &matrix1, const std::vector< std::vector<int> > &matrix2);
std::vector<int> dot(std::vector<int> &message, const std::vector<int> &err_vector);
int bin_to_dec(const std::vector<int> &vector);
std::vector<int> dec_to_bin(int num);
int error_level(std::vector<int> error);
std::vector<int> input_vector(int size);
void print(const std::vector< std::vector<int> > &matrix);
void print(const std::vector<int> &vector);
void print_table();

class Message
{
	private:										
		std::vector< std::vector<int> > H { {1,0,0,1,0,1,1},
						    {0,1,0,1,0,1,0},
						    {0,0,1,1,0,0,1},
						    {0,0,0,0,1,1,1} };
											
		std::vector< std::vector<int> > G { {1,1,1},
						    {0,1,1},
						    {1,0,1},
						    {0,0,1},
						    {1,1,0},
						    {0,1,0},
						    {1,0,0} };
		std::vector<int> message;
	public:
		Message()
		{
			this->message = {0,0,0,0,0,0,0};
		}
		Message(std::vector<int> &in_message)
		{
			this->encode(in_message);
		}
		std::vector<int> get_message() { return this->message; }
		void put_message(std::vector<int> &new_message) { this->message = new_message; }
		std::vector<int> encode(std::vector<int>& orig_message); 										// Возвращает вектор(7) и сохраняет внутри
		std::vector<int> decode(); 																		// Возвращает вектор(4), исправив при необходимости (внутри исправляет тоже)
		std::vector<int> error(std::vector<int> err_vector) { return dot(this->message, err_vector); }  // Изменяет сообщение с указанной ошибкой
		std::vector<int> transmit(); 																	// Изменяет сообщение со случайной ошибкой кратности 1
		std::vector<int> find_error(); 																	// Возвращает синдром ошибки
		bool detect_error(); 																			// Есть/нет ошибка
};

#endif
