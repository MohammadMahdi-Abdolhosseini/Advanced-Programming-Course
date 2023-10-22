#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> splitToWords(string line)
{
	vector<string> words;
	stringstream sLine(line);
	string word;
	while (sLine >> word)
	{
		words.push_back(word);
	}
	return words;
}

int findDayPage(vector<vector<vector<string>>> days, string date)
{
	for (int page = 0; page < days.size(); page++)
	{
		if (days[page][0][0] == date)
		{
			return page;
		}
	}
	return 0;
}

void print2Dvector(vector<vector<string>> v)
{
	for (int line = 1; line < v.size(); line++)
	{
		for (int word = 0; word < v[line].size(); word++)
		{
			cout << v[line][word];
			if (word != v[line].size() - 1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

int findTheLongestDayPage(vector<vector<vector<string>>> days)
{
	int theLongestPageLength = 0;
	int theLongestPageNumber = 0;
	for (int page = 0; page < days.size(); page++)
	{
		int pageLength = 0;
		for (int line = 0; line < days[page].size(); line++)
		{
			for (int word = 0; word < days[page][line].size(); word++)
			{
				pageLength += days[page][line][word].size();
			}
		}
		if (pageLength > theLongestPageLength)
		{
			theLongestPageLength = pageLength;
			theLongestPageNumber = page;
		}
	}
	return theLongestPageNumber;
}

void printPageSummary(vector<vector<string>> page)
{
	cout << page[0][0] << endl;
	int maxLength = 20, length = 0, word = 0, character = 0;
	while (length < maxLength)
	{
		cout << page[1][word][character];
		if (page[1][word].size() - 1 > character)
		{
			character++;
		}
		else if (page[1].size() - 1 > word)
		{
			character = 0;
			word++;
			cout << " ";
			length++;
		}
		else
		{
			cout << endl;
			break;
		}
		length++;
	}
	if (length == maxLength)
	{
		cout << "..." << endl;
	}
}

vector<string> readFile(string fileName)
{
	ifstream file(fileName);
	string word;
	vector<string> positiveWords;
	while (file >> word)
	{
		positiveWords.push_back(word);
	}
	file.close();
	return positiveWords;
}

int findTheBestDayPage(vector<vector<vector<string>>> days, vector<string> positiveWords)
{
	int theMostPositiveWordsNumber = 0;
	int pageWithTheMostPositiveWords = 0;
	for (int page = 0; page < days.size(); page++)
	{
		int positiveWordsNumber = 0;
		for (int line = 1; line < days[page].size(); line++)
		{
			for (int word = 0; word < days[page][line].size(); word++)
			{
				for (int i = 0; i < positiveWords.size(); i++)
				{
					if (days[page][line][word] == positiveWords[i])
					{
						positiveWordsNumber += 1;
					}
				}
			}
		}
		if (positiveWordsNumber > theMostPositiveWordsNumber)
		{
			theMostPositiveWordsNumber = positiveWordsNumber;
			pageWithTheMostPositiveWords = page;
		}
	}
	return pageWithTheMostPositiveWords;
}

int main()
{
	// days[page][line][word]
	vector<vector<vector<string>>> days;
	string line;
	while (getline(cin, line))
	{
		vector<string> words = splitToWords(line);

		if (words[0] == "start_day")
		{
			days.push_back({ {words[1]} });
		}
		else if (words[0] == "show_day")
		{
			int page = findDayPage(days, words[1]);
			print2Dvector(days[page]);
		}
		else if (words[0] == "show_the_longest_day")
		{
			int page = findTheLongestDayPage(days);
			printPageSummary(days[page]);
		}
		else if (words[0] == "show_the_best_day")
		{
			vector<string> positiveWords = readFile("positive-words.txt");
			int page = findTheBestDayPage(days, positiveWords);
			printPageSummary(days[page]);
		}
		else
		{
			int i = days.size() - 1;
			days[i].push_back(words);
		}
	}

	return 0;
}
