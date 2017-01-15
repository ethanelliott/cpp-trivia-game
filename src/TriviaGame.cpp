//============================================================================
// Name        : TriviaGame
// Author      : Ethan Elliott
// Version     : 1.0.0
// Copyright   : (c) Ethan Elliott 2015
// Description :
//============================================================================

//*********************************//   Ethan's Base Code   //*********************************//
/*
        (c)Copyright Ethan Elliott 2015

        Everything I will ever need in a c++ program.

        Contains base functions and vaiables for all programs, including a library of
        functions for other c++ programs.

        Use as the base include in all c++ prpograms.
*/
#ifndef ETHANLIB_H
#define ETHANLIB_H

//Defines
#define DEFAULT_RETURN_VAL 0

#define QUESTIONS 100
#define ANSWERS 5

//Includes
	//Libraries
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <iostream>
	#include <sstream>
	#include <limits>
	#include <fstream>
	#include <windows.h>
	#include <conio.h>
	#include <cstdlib>
	#include <ctime>
	#include <math.h>
	#include <algorithm>
	#include <vector>

using namespace std;

void Cls()
{
    system("cls");
}//Cls

void Pause(string text)
{
    cout << "\n" << text;
    getch();
}//Pause

string Round(const double input, const int decDigits)
{
    stringstream out;
    out << fixed;
    out.precision(decDigits);
    out << input;
    return out.str();
}

bool MakeChoice(string question)
{
	bool isDone = false;
	bool r = false;
	cout << "\n" << question << " [y / n]\n";
	while (!isDone)
	{
		switch (getch())
		{
		case 'y':
			isDone = true;
			r = true;
			break;
		case 'n':
			isDone = true;
			r = false;
			break;
		default:
			isDone = false;
			break;
		}
	}
	return r;
}

string itostr(int num)
{
	stringstream z;
	z << num;
	return z.str();
}

int strtoi(string num)
{
	int x = 0;
	while(itostr(x) != num)
	{
		x++;
	}
	return x;
}

#endif // ETHANLIB_H

//*********************************//   END Ethan's Base Code   //*********************************//


class Trivia
{
private:
	string Questions[QUESTIONS][7];
public:
	static Trivia * instance;
	bool programIsDone;
	bool gameIsDone;
	int questionNum;
	bool score[QUESTIONS];
	char response[QUESTIONS];

	int fileCount;
	string Files[100];

	Trivia(void)
	{
		questionNum = 0;
		fileCount = 0;
		programIsDone = false;
		gameIsDone = false;
	}//constructor

	~Trivia(void)
	{
		delete instance;
	}//deconstructor

	static Trivia * GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Trivia();
		}
		return instance;
	}

	void Init()
	{
		Cls();
	}//Init

	void PrintHeader()
	{
		cout << "=============================================================" << endl;
		cout << "=                                                           =" << endl;
		cout << "=     _____     _       _    _   _   _             _        =" << endl;
		cout << "=    |_   _| __(_)_   _(_)  / \\ | |_| |_ __ _  ___| | __    =" << endl;
		cout << "=      | || '__| \\ \\ / / | / _ \\| __| __/ _` |/ __| |/ /    =" << endl;
		cout << "=      | || |  | |\\ V /| |/ ___ \\ |_| || (_| | (__|   <     =" << endl;
		cout << "=      |_||_|  |_| \\_/ |_/_/   \\_\\__|\\__\\__,_|\\___|_|\\_\\    =" << endl;
		cout << "=                                                           =" << endl;
		cout << "=============================================================" << endl;
	}//PrintHeader

	void PrintMenu()
	{
		cout << "\t\t 1)\t" << "Play The Game" << "\n";
		cout << "\t\t 2)\t" << "Make yor own game" << "\n";
		cout << "\t\t 3)\t" << "Exit" << "\n\n";
		cout << "\t\tMake a selection: ";
	}//PrintMenu

	void GetFileList()
	{
		int loopCount = 0;
		string fileName = "";

		fileCount = 0;

		system("dir /b > DATA.e");
		ifstream id("DATA.e");
		string str;
		string part;
		char del = '.';

		while (getline(id,str))
		{
			loopCount = 0;
			fileName = "";
			stringstream stream(str);
			while (getline(stream, part, del))
			{
				if (loopCount == 0)
				{
					fileName = part;
				}
				else if(loopCount == 1)
				{
					if (part == "quiz")
					{
						Files[fileCount] = fileName;
						fileCount++;
					}
				}
				loopCount++;
			}
		}
	}//GetFileList

	string ChooseGame()
	{
		int choice = 0;
		bool firstLoad = true;
		bool update = true;
		bool done = false;
		while (!done)
		{
			if (firstLoad)
			{
				firstLoad = false;
				update = false;
				Cls();
				PrintHeader();
				if (fileCount > 0)
				{
					cout << "\nUse your up and down arrow keys to select a game.\nPress the enter key to choose.\n";
					for(int x = 0; x < fileCount; x++)
					{
						if(x == choice)
						{
							cout << " > " << Files[x] << "\n";
						}
						else
						{
							cout << "   " << Files[x] << "\n";
						}
					}
				}
				else
				{
					cout << "\nNo Files found.\nPress any key to return to the menu.\n";
					Pause("");
					return "";
				}
			}
			else
			{
				if (update)
				{
					update = false;
					Cls();
					PrintHeader();

					if (fileCount > 0)
					{
						cout << "\nUse your up and down arrow keys to select a game.\nPress the enter key to choose.\n";
						for(int x = 0; x < fileCount; x++)
						{
							if(x == choice)
							{
								cout << " > " << Files[x] << "\n";
							}
							else
							{
								cout << "   " << Files[x] << "\n";
							}
						}
					}
					else
					{
						cout << "\nNo Files found.\n";
						return "";
					}
				}
				if(GetAsyncKeyState(13)) //Enter Key
				{
					if (!firstLoad)
					{
						stringstream x;
						cout << "You have chosen " << Files[choice] << "\n";
						switch (MakeChoice("Are you sure?"))
						{
						case true:
							x << Files[choice] << ".quiz";
							return x.str();
							break;
						case false:
							done = false;
							break;
						}
					}
					Sleep(200);
				}
				if(GetAsyncKeyState(VK_UP))
				{
					choice--;
					if(choice < 0)
					{
						choice = 0;
					}
					if (choice < fileCount && choice > 0)
					{
						update = true;
					}
					else
					{
						update = false;
					}
					Sleep(200);
				}
				if(GetAsyncKeyState(VK_DOWN))
				{
					choice++;
					if(choice >= fileCount)
					{
						choice = (fileCount-1);
					}
					if (choice < fileCount && choice > 0)
					{
						update = true;
					}
					else
					{
						update = false;
					}
					Sleep(200);
				}
			}
		}
		return "";
	}//ChooseGame

	void LoadTriviaData(string file)
	{
		if (file != "")
		{
			int a = 0;
			int b = 0;
			char del = '|';
			const char * filePath;
			filePath = file.c_str();
			ifstream is(filePath);
			string str;
			string part;
			if(is.good())
			{
				questionNum = 0;
				a = 0;
				while (getline(is,str))
				{
					b = 0;
					stringstream stream(str);
					while (getline(stream, part, del))
					{
						Questions[a][b] = part;
						b++;
					}
					a++;
					questionNum++;
				}
				//cout << questionNum;
			}
			else
			{
				cout << "File Not Found!\n" << "Please place the file in the correct directory and restart the program.\n";
			}
		}
		else
		{
			gameIsDone = true;
		}
	}//LoadTriviaData

	void AskQuestion(int question)
	{
		cout << "\n\nQuestion #" << question << "/" << questionNum << ":\n\n";
		cout << Questions[question-1][0] << "\n\n";
		for(int i = 2; i <= (ANSWERS+1); i++)
		{
			cout << (i-1) << ")  " << Questions[question-1][i] << "\n";
		}

	}//AskQuestion

	bool GetResponse(int question)
	{
		bool isAcceptableResponse = false;
		while (!isAcceptableResponse)
		{
			cout << "Answer: ";
			char i = getch();
			cout << "'" << i << "'\n";
			response[question] = i;
			switch(i)
			{
			case '1':
				isAcceptableResponse = true;
				if(Questions[question][1] == "1")
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case '2':
				isAcceptableResponse = true;
				if(Questions[question][1] == "2")
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case '3':
				isAcceptableResponse = true;
				if(Questions[question][1] == "3")
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case '4':
				isAcceptableResponse = true;
				if(Questions[question][1] == "4")
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			case '5':
				isAcceptableResponse = true;
				if(Questions[question][1] == "5")
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			default:
				isAcceptableResponse = false;
				cout << "Invalid response. Try Again\n";
				break;
			}
		}
	}//GetResponse

	void ShowScore(int NumOfQuestions)
	{
		int correct;
		correct = 0;
		cout << "\n\n\n" << "Score:\n\n";
		for(int x = 1; x <= NumOfQuestions; x++)
		{
			if (score[x-1])
			{
				cout << x << ")\tCorrect.\tCorrect Answer:[" << Questions[x-1][1] << "]\tYour Answer:[" << response[x-1] << "]\n";
				correct++;
			}
			else
			{
				cout << x << ")\tIncorrect.\tCorrect Answer:[" << Questions[x-1][1] << "]\tYour Answer:[" << response[x-1] << "]\n";
			}
		}
		cout << "\nTotal: " << correct << "/" << questionNum << "  " << Round(((double)correct/(double)NumOfQuestions)*100,0) << "%\n";
	}//ShowScore
};//Trivia

class WriteTrivia
{
private:

public:
	static WriteTrivia * instance;

	WriteTrivia(void)
	{

	}//Constructor

	~WriteTrivia(void)
	{
		delete instance;
	}//Deconstructor

	static WriteTrivia * GetInstance()
	{
		if (instance == NULL)
		{
			instance = new WriteTrivia();
		}
		return instance;
	}//GetInstance

	void PrintHeader()
	{
		cout << "=============================================================" << endl;
		cout << "=                                                           =" << endl;
		cout << "=     _____     _       _    _   _   _             _        =" << endl;
		cout << "=    |_   _| __(_)_   _(_)  / \\ | |_| |_ __ _  ___| | __    =" << endl;
		cout << "=      | || '__| \\ \\ / / | / _ \\| __| __/ _` |/ __| |/ /    =" << endl;
		cout << "=      | || |  | |\\ V /| |/ ___ \\ |_| || (_| | (__|   <     =" << endl;
		cout << "=      |_||_|  |_| \\_/ |_/_/   \\_\\__|\\__\\__,_|\\___|_|\\_\\    =" << endl;
		cout << "=                                                           =" << endl;
		cout << "=============================================================" << endl;
	}//PrintHeader

	void DoIt()
	{
		struct Question
		{
			string question;
			int correctAnswer;
			string a1;
			string a2;
			string a3;
			string a4;
			string a5;
		};
		struct Question q;
		const char * filePath;
		char del = '|';
		bool isDone = false;
		int questionCount = 0;
		stringstream Output;
		Output.clear();
		string input = "";
		string foo = "";
		filePath = "";
		Cls();
		PrintHeader();
		cout << "\n" << "Enter a name for your game: ";
		getline(cin,input);
		stringstream a;
		foo = input;
		a << input << ".quiz";
		input = a.str();
		filePath = input.c_str();
		while (!isDone)
		{
			q.question = "";
			q.correctAnswer = 0;
			q.a1 = "";
			q.a2 = "";
			q.a3 = "";
			q.a4 = "";
			q.a5 = "";

			Cls();
			PrintHeader();

			cout << "Game: " << foo << "\n\n";
			cout << "Question: #" << (questionCount+1) << "\n\n";
			cout << "Enter the question:\n";
			getline(cin,q.question);

			Cls();
			PrintHeader();

			cout << "Game: " << foo << "\n\n";
			cout << "Question: #" << (questionCount+1) << "\n\n";
			cout << "Question: " << q.question << "\n\n";

			cout << "You will now enter 5 possible answers.\nMake sure at least one of them is correct!\n";
			for (int x = 0; x < 5; x++)
			{
				cout << "\nAnswer #" << (x+1) << ":\n";
				switch (x)
				{
				case 0:
					getline(cin,q.a1);
					cout << "\n" << q.a1 << "\n";
					break;
				case 1:
					getline(cin,q.a2);
					cout << "\n" << q.a2 << "\n";
					break;
				case 2:
					getline(cin,q.a3);
					cout << "\n" << q.a3 << "\n";
					break;
				case 3:
					getline(cin,q.a4);
					cout << "\n" << q.a4 << "\n";
					break;
				case 4:
					getline(cin,q.a5);
					cout << "\n" << q.a5 << "\n";
					break;
				}
			}

			cout << "\n\n" << "Which answer is correct? (enter the question number)\n";
			while (!(cin >> q.correctAnswer))
			{
				cerr << "WHOA! That's not a number!\nTry Again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			Output << q.question << del << q.correctAnswer << del << q.a1 << del << q.a2 << del << q.a3 << del << q.a4 << del << q.a5 << endl;
			isDone = !MakeChoice("Add another question?");
			questionCount++;
		}

		ofstream of(filePath);
		of << Output.str();
		of.close();
	}//DoIt
};//WriteTrivia


Trivia * Trivia::instance = NULL;
WriteTrivia * WriteTrivia::instance = NULL;

int main()
{
	//Trivia Game Initializer
	Trivia * triviaGame;
	WriteTrivia * triviaWrite;
	triviaGame = Trivia::GetInstance();
	triviaWrite = WriteTrivia::GetInstance();

	//Initialize the game
	triviaGame->Init();

	//Begin Game
	while (!triviaGame->programIsDone)
	{
		//Set the game to not done
		triviaGame->gameIsDone = false;
		//Clear the screen, and print the header and menu
		Cls();
		triviaGame->PrintHeader();
		triviaGame->PrintMenu();
		//Begin menu options
		switch (getch())//Based on key press
		{
		case '1'://Option 1: Play game
			triviaGame->programIsDone = false;	//program is not done
			Cls();	//Clear screen
			triviaGame->GetFileList();	//Load files
			triviaGame->LoadTriviaData(triviaGame->ChooseGame());	//Let user choose the game
			while(!triviaGame->gameIsDone) //Loop through all questions
			{
				Cls();	//Clear the screen
				for(int x = 1; x <= triviaGame->questionNum; x++)	//Loop through all questions, storing answer.
				{
					triviaGame->PrintHeader();	//Print Header
					triviaGame->AskQuestion(x);	//Ask Question
					triviaGame->score[x-1] = triviaGame->GetResponse(x-1);	//Save Response
					Pause("Press any key for next question.");	//Move to next question
					Cls();	//Clear the screen
				}
				triviaGame->PrintHeader();	//Print the header
				triviaGame->ShowScore(triviaGame->questionNum);	//Show Score
				triviaGame->gameIsDone = !MakeChoice("Do you want to play again?");	//Ask to play again. If false, game ends.
			}
			break;
		case '2': //Option 2: Write your own game
			triviaGame->programIsDone = false;	//Game is not done
			triviaWrite->DoIt();	//Make your own game
			break;
		case '3': //Option 3: Exit program
			triviaGame->programIsDone = true;	//Game is done
			break;
		default: //Default Case: Do nothing
			break;
		}
	}
	//End Game
	Pause("\n\nPress any key to continue\n\n");
	return 0;
}//main

//End Program.
