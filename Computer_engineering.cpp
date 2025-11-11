///////////////////////////////////////////////
// Description: Computer Engineering Case Study
// A C++ Program to make the concordance of the words from the given text
// Author: Gulsim Azirakhmet
// Date Created: November 1, 2021
// NYUAD Assignment 3
///////////////////////////////////////////////


//Headers
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include<algorithm>
#include<cctype>

//Namespaces
using namespace std;

int ReadFile(string& filename, int& NumberofWords);//opens the file and reads number of words and strings in the file
string* ReadfromFile(string filename, int NumberofWords, string* arrayofwords);//opens the file and reads strings into arrayofwords dynamic array
string* ReadText(int NumberofWords, string* arrayofwords);//function to sort the words from punctuation characters and turn them to lower case
string* AlphabeticalOrder(int NumberofWords, string* words);//function to sort the words in alphabetical order
string* FrequencyofOccurence(string wordRead, string* words, int NumberofWords, int wordCount);//function to count the frequence of occurence of each word
void WriteToFile(string wordRead, int wordCount, int NumberofWords, string* words, string& filename1);//function to write the concordance to a file


//Main Function (Entry Point)
int main() {
	string filename, filename1, wordRead;//declare filename, filename1, wordRead as string
	int wordCount = 1, NumberofWords = 0;//declare wordCount = 1, NumberofWords = 0 as integer


	NumberofWords = ReadFile(filename, NumberofWords);//assign function ReadFile to NumberofWords
	string* arrayofwords;//declare dynamic array
	arrayofwords = new string[NumberofWords];//give new size to the dynamic array
	arrayofwords = ReadfromFile(filename, NumberofWords, arrayofwords);//assign function ReadfromFile to array of words
	arrayofwords = ReadText(NumberofWords, arrayofwords);//assign function ReadText to array of words
	arrayofwords = AlphabeticalOrder(NumberofWords, arrayofwords);//assign function AlphabeticalOrder to array of words
	arrayofwords = FrequencyofOccurence(wordRead, arrayofwords, NumberofWords, wordCount);//assign function FrequencyofOccurence to array of words
	WriteToFile(wordRead, wordCount, NumberofWords, arrayofwords, filename1);//function to write the concordance to a file


	delete[] arrayofwords;//deletes dynamically allocated array arrayofwords
	return 0;//default return code(0) for normal exit
}

int ReadFile(string& filename, int& NumberofWords)//opens the file and reads number of words and strings in the file
{
	string wordRead;//declare wordRead as string
	cout << "Please, enter the name of the file" << endl;//prints message to the output screen
	cin >> filename;//reads input to the filename

	ifstream wordNumber; 
	wordNumber.open(filename, ios::in);// open file to count the number of words
	if (wordNumber.fail())//if file fails to open
	{
		cerr << "Failed to open file";//print the message 
		exit(-1);//return (-1) if file fails to open
	}

	while (!wordNumber.eof())//until the end of the file
	{
		wordNumber >> wordRead;//reads words from the file to wordRead
		NumberofWords++;//counts number of words inside the file
	}
	wordNumber.close();//close the wordNumber file

	return NumberofWords;//return NumberofWords to the main function

}

string* ReadfromFile(string filename, int NumberofWords, string* arrayofwords)//opens the file and reads strings into arrayofwords dynamic array
{
	ifstream wordNumber;
	wordNumber.open(filename, ios::in);// open file to store words into string array
	if (wordNumber.fail())//if file fails to open
	{
		cerr << "Failed to open file";//print the message 
		exit(-1);//return (-1) if file fails to open
	}

	for (int i = 0; i < NumberofWords; i++)//loop to continue action NumberofWords times 
	{
		wordNumber >> arrayofwords[i]; // stores the text into the array
	}
	wordNumber.close();//close wordNumber file
	return arrayofwords;// return arrayofwords to the main function 
}


string* ReadText(int NumberofWords, string* arrayofwords)//function to sort the words from punctuation characters and turn them to lower case
{

	for (int row = 0; row < NumberofWords; row++)//loop to continue action NumberofWords times
	{
		for (int column = 0; arrayofwords[row][column] != '\0'; column++)//loop to continue action until the character equals to delimeter
		{
			if ((arrayofwords[row][column] >= 'a' && arrayofwords[row][column] <= 'z') || (arrayofwords[row][column] >= 'A' && arrayofwords[row][column] <= 'Z'))//if character is alphabet
			{
				arrayofwords[row][column] = (char)tolower(arrayofwords[row][column]);//change characters to lower case characters
			}

			if (arrayofwords[row][column] < 'A' || (arrayofwords[row][column] > 'Z' && arrayofwords[row][column] < 'a') || arrayofwords[row][column] > 'z')//if character is symbol
			{
				arrayofwords[row][column] = '\0';//character equals to delimeter
			}
		}

		arrayofwords[row].erase(remove(arrayofwords[row].begin(), arrayofwords[row].end(), '\0'), arrayofwords[row].end());//remove delimeters from the text
	}
	
	return arrayofwords;//return arrayofwords to the main function
}


string* AlphabeticalOrder(int NumberofWords, string* words)//function to sort the words in alphabetical order
{
	string temp;//declare temp as string

	for (int row = 0; row < NumberofWords; row++)//loop to continue action for NumberofWords times
	{
		for (int j = row+1; j < NumberofWords; j++)//loop to continue action from row+1 till the NumberofWords
		{
			if (words[row] > words[j])//if ASCII number of word in the text is larger than the ASCII number of the next word in the text 
			{
				temp = words[row];//assign word to the temp
				words[row] = words[j];//assign next word to the array words[row]
				words[j] = temp;//assign word to the array words[j]
			}
		}
	}
	return words;//return words to main function
}


string* FrequencyofOccurence(string wordRead, string* words, int NumberofWords, int wordCount)//function to count the frequence of occurence of each word
{
	wordRead = words[0];//assign first word in the array to the wordRead
	cout.setf(ios::left);//output messages assigned to the left

	for (int m = 1; m < NumberofWords; m++)//loop to continue NumberofWords times
	{
		if (wordRead != words[m])//if other words is not equal to the first word
		{
			cout << setw(20) << wordRead << setw(20) << wordCount << endl;//print the word with the wordCount=1
			wordCount = 0;//assign 0 to wordCount
			wordRead = words[m];//assign words[m] to wordRead
		}
		wordCount++;//otherwise increment wordCount
	}
	cout << setw(20) << wordRead << setw(20) << wordCount << endl;//print the word with the wordCount
	return words;//return words to main function
}

void WriteToFile(string wordRead, int wordCount, int NumberofWords, string* words, string& filename1)//function to write the concordance to a file
{
	cout << "Please, enter the name of the file to store the data" << endl;//prints message to the output screen
	cin >> filename1;//reads input to the filename1

	ofstream concordance(filename1, ios::out);//opens file concordance for writing
	concordance.setf(ios::left);
	if (concordance.fail()) // if file fails to open
	{
		cerr << "Failed to open file";//print the message
		exit(-1);//return (-1) if file fails to open
	}

	wordRead = words[0];//assign first word in the array to the wordRead
	for (int m = 1; m < NumberofWords; m++)//loop to continue NumberofWords times
	{
		if (wordRead != words[m]) // if other words is not equal to the prevoius word
		{
			concordance << setw(20) << wordRead << setw(20) << wordCount << endl;//write the word with the wordCount=1 into concordance file
			wordCount = 0;//assign 0 to wordCount
			wordRead = words[m];//assign words[m] to wordRead
		}
		wordCount++;//increment wordCount
	}
	concordance << setw(20) << wordRead << setw(20) << wordCount << endl;//write the word with the wordCoun into concordance file
	cout << "The concordance of the words is saved in text file. " << endl;//print message on the output screen
}
