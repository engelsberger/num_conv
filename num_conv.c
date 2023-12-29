#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_ITERATIONS 1000



/*
* Converts a given char (0-9, A-Z) to its decimal value (case insensitive)
* A = 10, B = 11, ...
* 
* @param digit The given digit to convert
* @return The char digit converted to decimal
* @return -1 On error
*/
int char_to_dec(char digit) {

	if (digit >= '0' && digit <= '9') return digit - '0';
	else if (digit >= 'A' && digit <= 'Z') return digit - 'A' + 10;
	else if (digit >= 'a' && digit <= 'z') return digit - 'a' + 10;

	return -1;
}


/*
* Converts a given number (0-35) to its char value
* 10 = A, 11 = B, ...
*
* @param digit The given digit to convert
* @return The number converted to char
* @return -1 On error
*/
char dec_to_char(int digit) {

	if (digit >= 0 && digit <= 9) return digit + '0';
	else if (digit >= 10 && digit <= 35) return digit + 'A' - 10;

	return -1;
}


/*
* Checks if the given input is correct
* 
* @param input The given input
* @return 0 If successful
* @return -1 If input contains unallowed chars or is too large/small
*/
int check_input_num_system(char* input) {

	int num_system = 0;

	for (int i = 0; i < MAX_ITERATIONS && *(input + i) != '\0'; i++) {

		if (*(input + i) < '0' || *(input + i) > '9') return -1;
	}

	num_system = atoi(input);

	if (num_system < 2 || num_system > 36) return -1;

	return 0;
}


/*
* Checks if the given input matches the given num_system
*
* @param input The given input
* @param num_system The given num system
* @return 0 If no error is found
* @return -1 If input contains unallowed chars in respect to the given input num_system
*/
int check_input_number(char* input_str, int num_system) {

	for (int i = 0; i < MAX_ITERATIONS && *(input_str + i) != '\0'; i++) {

		char input = *(input_str + i);

		if (input >= 'a' && input <= 'z') input += 'A' - 'a';

		if ((input < '0' || input > '0' + num_system - 1) && (input < 'A' || input > 'A' + (num_system > 10 ? num_system - 11 : (-1)))) return -1;
	}

	return 0;
}


/*
* Is given a number and a number system to convert the number to
* Writes the converted number as an array of chars(string) into a given output.
* 
* @param input The given number
* @param output Where the solution gets written to
* @param input_num_system The given input number system
* @param output_num_system The given output number system
* @return 0 If successful
* @return -1 If input number is too large
*/
int convert_number(char* input, char* output, int input_num_system, int output_num_system) {

	char converted_inverted[65] = { 0 };
	long long int input_decimal = 0;
	int length = 0;

	//Determine input length
	for (length = 0; length < MAX_ITERATIONS && *(input + length) != '\0'; length++);

	//Convert input to decimal system
	if (input_num_system != 10) {

		for (int i = 0; i < length; i++) {

			input_decimal += char_to_dec(*(input + i)) * pow(input_num_system, length - i - 1);

			//Return -1 if input number gets too large (long long int overflows)
			if (input_decimal < 0) return -1;
		}
	}
	else input_decimal = atoll(input);

	length = 0;

	//Convert from decimal to output number system
	for (int i = 0; i < MAX_ITERATIONS && input_decimal > 0; i++) {

		converted_inverted[i] = dec_to_char(input_decimal % output_num_system);
		input_decimal /= output_num_system;
		length++;
	}

	//Flip output
	for (int i = 0; i < length; i++) {
		*(output + i) = converted_inverted[length - i - 1];
	}

	return 0;
}


/*
* main-function
* 
* @return 0 if successful
* @return -1 for wrong input
*/
int main(int argc, char* argv[]) {
	
	char converted[65] = { 0 };
	int input_num_system = 10;
	int output_num_system = 0;

	if ((argc != 3 && argc != 4) || check_input_num_system(argv[2]) || (argc == 4 && check_input_num_system(argv[3])) || 
		(argc == 3 && check_input_number(argv[1], input_num_system)) || (argc == 4 && check_input_number(argv[1], input_num_system = atoi(argv[2])))) {

		printf("Error: Wrong input. This program expects two or three arguments:\n");
		printf("1. A number to convert (case insensitive).\n");
		printf("2. (skippable) The number system for the number above from 2 to 36, assumes decimal input by default.\n");
		printf("3. An output number system from 2 to 36.\n");
		printf("For example: \"num_conv 3F 16 2\" converts hexadecimal 3F to binary.\n");
		return -1;
	}

	output_num_system = (argc == 3 ? atoi(argv[2]) : atoi(argv[3]));

	if (convert_number(argv[1], converted, input_num_system, output_num_system)) {

		printf("Error: Input number is too large.\n");
		return -1;
	}
	
	printf("%s\n", converted);

	return 0;
}
