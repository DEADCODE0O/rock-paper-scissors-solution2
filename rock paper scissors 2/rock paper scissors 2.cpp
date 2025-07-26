#include <iostream>  
#include <cstdlib>   
#include <ctime>     
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short HowManyRounds;
    do
    {
        cout << "Enter how many rounds you want to play (1-10): ";
        cin >> HowManyRounds;
    } while (HowManyRounds < 1 || HowManyRounds > 10);
    return HowManyRounds;
}

string Tabs(int Count)
{
    string TabsStr = "";
    for (int i = 0; i < Count; i++)
        TabsStr += "\t";
    return TabsStr;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;

    }
    return enWinner::Player1;
}


enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
    {
        return enWinner::Player1;
    }
    else if (ComputerWinTimes > Player1WinTimes)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::Draw;

    }
}


string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}


string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}



enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F"); // Green for Player1 win
        break;
    case enWinner::Computer:
        system("color 4F"); // Red for Computer win
        cout << "\a"; // Beep sound for Computer win
        break;
    case enWinner::Draw:
        system("color 7F"); // White for Draw
        break;
    }
}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << Tabs(5) << "____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << Tabs(5) << "Player1 Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << Tabs(5) << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << Tabs(5) << "Round Winner    : [" << RoundInfo.WinnerName << "]\n";
    cout << Tabs(5) << "_________________________________________\n" << endl;
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;

        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return  FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen()
{
    cout << "\n\n";
    cout << Tabs(5) << "**********************************\n";
    cout << Tabs(5) << "*                                *\n";
    cout << Tabs(5) << "*            Game Over           *\n";
    cout << Tabs(5) << "*                                *\n";
    cout << Tabs(5) << "**********************************\n\n";
}
void ShowGameResults(stGameResults GameResults)
{
    cout << "\n\n";
    cout << Tabs(5) << "**********************************\n";
    cout << Tabs(5) << "*          Game Results          *\n";
    cout << Tabs(5) << "**********************************\n";
    cout << Tabs(5) << "Total Rounds Played  : " << GameResults.GameRounds << endl;
    cout << Tabs(5) << "Player1 Wins         : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(5) << "Computer Wins        : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(5) << "Draws                : " << GameResults.DrawTimes << endl;
    cout << Tabs(5) << "Game Winner          : " << GameResults.WinnerName << endl;
    cout << Tabs(5) << "**********************************\n\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}
void ResetConsole()
{
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetConsole();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowGameResults(GameResults);
        cout << Tabs(2) << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}