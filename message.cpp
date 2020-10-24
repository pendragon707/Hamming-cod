#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include "message.h"

std::vector<int> Message::encode(std::vector<int>& orig_message)
{
	this->message = dot(orig_message, this->H);
	return this->message;
}

std::vector<int> Message::decode()
{
	std::vector<int> decode_message;
	int num_error = bin_to_dec(find_error());
	if(num_error != 0)
	{
		this->message[7 - num_error] = this->message[7 - num_error]^1;
	}	
	for(int i=0; i < message.size(); i++)
	{
		if(i == 3 || i == 5 || i == 6)
			continue;
		decode_message.push_back(message[i]);
	}
	return decode_message;
}

bool Message::detect_error()
{
	int num_error = bin_to_dec(find_error());
	if(num_error != 0)
		return true;
	else 
		return false;
}

std::vector<int> Message::find_error()
{
	std::vector<int> decode_message;
	decode_message = dot(this->message, this->G);
	return decode_message;
}

std::vector<int> Message::transmit()    //В канале наиболее вероятны ошибки 1-ой кратности
{
	std::vector<int> err_vector = dec_to_bin(pow(2,rand()%7));
	for(int i = 0; i < message.size(); i++)
	{
		message[i] = message[i] ^ err_vector[i];
}
	return message;
}

int bin_to_dec(const std::vector<int> &vector)
{
	int sum = 0;
	for(int i=0; i<vector.size(); i++)
	{
		sum += vector[i]*pow(2,i); 
	}
	return sum;
}

std::vector<int> dec_to_bin(int num)
{
	std::vector<int> answer(7);
	int i = 6;
	do{
		answer[i] = num % 2;
		num = num / 2;
		i--;
	}while(num > 0 && i >= 0);
	return answer;
}

void check_N0_Nk(std::vector<int> &detected_errors,std::vector<int> &corrected_errors)
{
	std::vector<int> message = {1,1,0,0};
	std::vector<int> err_vector;
	Message test_message(message);   //encode
	for(int i = 0; i < 128; i++)
	{
		test_message.encode(message);
		err_vector = dec_to_bin(i);
		test_message.error(err_vector);
		if (test_message.detect_error())
			detected_errors[error_level(err_vector) - 1] += 1;
		else
			continue;
		if(test_message.decode() == message)
		{
			corrected_errors[error_level(err_vector) - 1] += 1;
		}
	}
}

int error_level(std::vector<int> error)
{
	int level = 0;
	for(int i = 0; i < error.size(); i++)
	{
		if(error[i] == 1)
			level+=1;
	}
	return level;
}

int factorial(int num)
{
	int result = 1;
	for(int i = 1; i <= num; i++)
		result *= i;
	return result;
}

float get_combination(int n, int i)
{
	return factorial(n)/(factorial(n - i)*factorial(i));
}

float get_corrected_ability(float comb, float count)
{
	return count/comb;
}




std::vector<int> dot(std::vector<int> &message, const std::vector<int> &err_vector)
{
	for(int i = 0; i < message.size(); i++)
	{
		message[i] = message[i] ^ err_vector[i];
	}
	return message;
}

std::vector<int> dot(const std::vector<int> &matrix1, const std::vector< std::vector<int> > &matrix2)
{
	std::vector<int> dot_matrix(matrix2[0].size(), 0);
		for(int j=0; j<matrix2[0].size(); j++)
		{
			for(int k = 0; k<matrix1.size(); k++)
				dot_matrix[j] = dot_matrix[j] ^ (matrix1[k] * matrix2[k][j]);
		}
	return dot_matrix;
}




std::vector<int> input_vector(int size)
{
	std::vector<int> input(size, 0);
	char symbol;
	for(int i = 0; i < input.size(); i++)
	{
		std::cin >> symbol;
		if(symbol == '0' || symbol == '1')
			input[i] = (int)(symbol - '0');
		else
		{
			std::cout << "Ошибка ввода: нужно вводить 0 или 1" << std::endl;
			return input;
		}
	}
	return input;
}




void print(const std::vector< std::vector<int> > &matrix)
{
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print(const std::vector<int> &vector)
{
	for(int i=0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

void print_table()
{
	std::vector<int> detected_errors(7, 0);
	std::vector<int> corrected_errors(7, 0);
	check_N0_Nk(detected_errors, corrected_errors);
	std::cout << "=====================================" << std::endl;
	std::cout << "|| i || Ошибки ||  N0  || Nk || Ck ||" << std::endl;
	std::cout << "=====================================" << std::endl;
	for(int i = 0; i < detected_errors.size(); i++)
	{
		int combinations = get_combination(7, i + 1);
		std::cout << "|| " << i + 1 << " || " << combinations << "     ";
		if(combinations < 10)
		{
			std::cout << " ";
		}
		std::cout << "|| " << detected_errors[i] << "   ";
		if(detected_errors[i] < 10)
			std::cout << " ";
		std::cout << "|| " << corrected_errors[i] << "  || " << get_corrected_ability(get_combination(7, i + 1), corrected_errors[i]) << "  ||" << std::endl;	
	std::cout << "-------------------------------------" << std::endl;
	}
}

