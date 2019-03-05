#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

///////////////////////////////////////////////////////////////////////

int const N = 20;
int const M = 40;
int Coordinate[N][M], SumTail = 2;
int PS, SG, Speed = 500;
//Создаём перечесления для состояний игры
enum PlayerState
{
	PlayRightNow = 1, 
	Lose, 
	Stop
};
enum StateGame
{
	GameActivity = 1, 
	ZoneBuild, 
	MenuGame, 
	Play, 
	Pause, 
	GameOver, 
	Error
};
//Пеменная поля игры
char GameZone[N][M];

///////////////////////////////////////////////////////////////////////

//Первое построение зоны игры
int FirstBuildZone(char GameZone[N][M])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if ((i == 0 || i == N - 1) && (j == 0 || j == M - 1)) GameZone[i][j] = '+';
			else if (i == 0 || i == N - 1) GameZone[i][j] = '-';
			else if (j == 0 || j == M - 1) GameZone[i][j] = '|';
			else GameZone[i][j] == '\0';
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << GameZone[i][j];
		}
		cout << endl;
	}

	return ZoneBuild;
}

///////////////////////////////////////////////////////////////////////

//Дальнейшее построение меню
void BuildZone(char GameZone[N][M])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << GameZone[i][j];
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////

//Меню
int menu()
{
	int i = 0;
	
	while (true)
	{
		cout << "Движение по меню осуществляется кнопками w и s. Выбрать можно кнопкой f" << endl;
		cout << "Start";
		if (i == 0) cout << "   <--" << endl;
		else cout << endl;
		cout << "Stop";
		if (i == 1) cout << "    <--" << endl;
		else cout << endl;
		cout << "Setting";
		if (i == 2) cout << " <--" << endl;
		else cout << endl;
		cout << "Exit";
		if (i == 3) cout << "    <--" << endl;
		else cout << endl;

		switch (_getch())
		{
		case 'w':
			i--;
			break;
		case 's':
			i++;
			break;
		case 'f':
			system("cls");
			return i;
			break;
		default:
			break;
		}

		if (i == -1) i = 3;
		else if (i == 4) i = 0;

		system("cls");
	}

	return MenuGame;
}


///////////////////////////////////////////////////////////////////////

//Меню в игре
void MenuInGame()
{
	system("cls");

	int i = 0;
	bool Check = false;

	while (Check == false)
	{
		cout << "Движение по меню осуществляется кнопками w и s. Выбрать можно кнопкой f" << endl;
		cout << "Continue";
		if (i == 0) cout << " <--" << endl;
		else cout << endl;
		cout << "Restart";
		if (i == 1) cout << " <--" << endl;
		else cout << endl;
		cout << "Setting";
		if (i == 2) cout << " <--" << endl;
		else cout << endl;
		cout << "Exit";
		if (i == 3) cout << "    <--" << endl;
		else cout << endl;

		switch (_getch())
		{
		case 'w':
			i--;
			break;
		case 's':
			i++;
			break;
		case 'f':
			system("cls");
			Check = true;
			break;
		default:
			break;
		}

		if (i == -1) i = 3;
		else if (i == 4) i = 0;

		system("cls");
	}

	switch (i)
	{
	case 0:
		break;
	case 1:
		FirstBuildZone(GameZone);
		break;
	case 2:
		cout << "Низя сюда тыкать!" << endl;
		Sleep(1000);
		system("cls");
		break;
	case 3:
		exit(0);
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////


class Game
{
private:
	int StartTail_x = 9, 
		StartTail_y = 19,
		EndTail_x = StartTail_x + 3, 
		EndTail_y = StartTail_y,
		Fruit_x, 
		Fruit_y,
		CheckTurn = 0;
	bool FruitCheck = false, 
		 CheckWin = false;
	enum P
	{
		Up = 1,
		Down,
		Left,
		Right
	};
	int Route = Up;
public:
	void SnackInGame(char GameZone[N][M])
	{
		GameZone[StartTail_x][StartTail_y] = '*';
		GameZone[StartTail_x + 1][StartTail_y] = '*';
		GameZone[StartTail_x + 2][StartTail_y] = '*';
		GameZone[EndTail_x][EndTail_y] = '*';

		while (SG != GameOver)
		{
			while (FruitCheck == false)
			{
				srand(time(NULL));
				Fruit_x = rand() % N - 1;
				Fruit_y = rand() % M - 1;
				if (GameZone[Fruit_x][Fruit_y] == '\0')
				{
					GameZone[Fruit_x][Fruit_y] = '#';
					FruitCheck = true;
					break;
				}
			}

			if (_kbhit())
			{
				switch (_getch())
				{
				case 'w':
					if (Route == Down && CheckTurn == 0)
					{
						CheckTurn++;
						break;
					}
					else
					{
						Route = Up;
						CheckTurn = 0;
					}
					break;
				case 's':
					if (Route == Up && CheckTurn == 0)
					{
						CheckTurn++;
						break;
					}
					else
					{
						Route = Down;
						CheckTurn = 0;
					}
					break;
				case 'a':
					if (Route == Right && CheckTurn == 0)
					{
						CheckTurn++;
						break;
					}
					else
					{
						Route = Left;
						CheckTurn = 0;
					}
					break;
				case 'd':
					if (Route == Left && CheckTurn == 0)
					{
						CheckTurn++;
						break;
					}
					else
					{
						Route = Right;
						CheckTurn = 0;
					}
					break;
				case 'm':
					SG = MenuGame;
					MenuInGame();
					break;
				default:
					break;
				}
			}

			if (StartTail_x == Fruit_x && StartTail_y == Fruit_y) FruitCheck = false;
			else
			{
				GameZone[EndTail_x][EndTail_y] = ' ';

				if (GameZone[EndTail_x + 1][EndTail_y] == '*') EndTail_x++;
				else if (GameZone[EndTail_x - 1][EndTail_y] == '*') EndTail_x--;
				else if (GameZone[EndTail_x][EndTail_y + 1] == '*') EndTail_y++;
				else if (GameZone[EndTail_x][EndTail_y - 1] == '*') EndTail_y--;
			}

			switch (Route)
			{
			case Up:
				StartTail_x--;
				if (GameZone[StartTail_x][StartTail_y] == '*') CheckWin = true;
				else GameZone[StartTail_x][StartTail_y] = '*';
				break;
			case Down:
				StartTail_x++;
				if (GameZone[StartTail_x][StartTail_y] == '*') CheckWin = true;
				else GameZone[StartTail_x][StartTail_y] = '*';
				break;
			case Left:
				StartTail_y--;
				if (GameZone[StartTail_x][StartTail_y] == '*') CheckWin = true;
				else GameZone[StartTail_x][StartTail_y] = '*';
				break;
			case Right:
				StartTail_y++;
				if (GameZone[StartTail_x][StartTail_y] == '*') CheckWin = true;
				else GameZone[StartTail_x][StartTail_y] = '*';
				break;
			default:
				break;
			}

			if (StartTail_x == 0 || StartTail_x == 19 || StartTail_y == 0 || StartTail_y == 39 || CheckWin == true)
			{
				system("cls");
				if (rand() % 3 == 0) cout << "ДТП с участием стенки!" << endl;
				else if (rand() % 3 == 1) cout << "Стена с мемами не здесь." << endl;
				else if (rand() % 3 == 2) cout << "В стене есть смысл только когда присутсвует наблюдатель. Конфуций 538 год д.н." << endl;
				SG = GameOver;
				system("pause");
			}
			else if (Route == Up && GameZone[StartTail_x - 1][StartTail_y] == '*')
			{
				system("cls");
				if (rand() % 3 == 0) cout << "Ты себя не любишь? Зачем себя обижаешь..." << endl;
				else if (rand() % 3 == 1) cout << "Интересная штука время. Где начало и конец? С чего все началось? Что есть время?... О! А ты проиграл!" << endl;
				else if (rand() % 3 == 2) cout << "Бан." << endl;
				SG = GameOver;
				system("pause");
			}
			else if (Route == Down && GameZone[StartTail_x + 1][StartTail_y] == '*')
			{
				system("cls");
				if (rand() % 3 == 0) cout << "Ты себя не любишь? Зачем себя обижаешь..." << endl;
				else if (rand() % 3 == 1) cout << "Интересная штука время. Где начало и конец? С чего все началось? Что есть время?... О! А ты проиграл!" << endl;
				else if (rand() % 3 == 2) cout << "Бан." << endl;
				SG = GameOver;
				system("pause");
			}
			else if (Route == Left && GameZone[StartTail_x][StartTail_y - 1] == '*')
			{
				system("cls");
				if (rand() % 3 == 0) cout << "Ты себя не любишь? Зачем себя обижаешь..." << endl;
				else if (rand() % 3 == 1) cout << "Интересная штука время. Где начало и конец? С чего все началось? Что есть время?... О! А ты проиграл!" << endl;
				else if (rand() % 3 == 2) cout << "Бан." << endl;
				SG = GameOver;
				system("pause");
			}
			else if (Route == Right && GameZone[StartTail_x][StartTail_y + 1] == '*')
			{
				system("cls");
				if (rand() % 3 == 0) cout << "Ты себя не любишь? Зачем себя обижаешь..." << endl;
				else if (rand() % 3 == 1) cout << "Интересная штука время. Где начало и конец? С чего все началось? Что есть время?... О! А ты проиграл!" << endl;
				else if (rand() % 3 == 2) cout << "Бан." << endl;
				SG = GameOver;
				system("pause");
			}
			else BuildZone(GameZone);
			Sleep(Speed);
			system("cls");
		}
	}
};

///////////////////////////////////////////////////////////////////////

Game GameNow;

///////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "Russian");

	SG = GameActivity;
	cout << SG << " - Запуск игры";
	Sleep(1000);
	for (int i = 0; i < 3; i++)
	{
		cout << '.';
		Sleep(10);
	}
	system("cls");


	SG = FirstBuildZone(GameZone);
	cout << SG << " - Игра запущена. Переход в главное меню";
	for (int i = 0; i < 3; i++)
	{
		cout << '.';
		Sleep(10);
	}
	system("cls");

	int k, q = 0, l = 0;

	while (true)
	{
		k = menu();
		if (k == 0)
		{
			SG = Play;
			GameNow.SnackInGame(GameZone);
		}

		else if (k == 1)
		{
			if (q == 0)
			{
				cout << "Ну и что ты остановил?" << endl;
				q++;
			}
			else if (q == 1)
			{
				cout << "Что ты делаешь?" << endl;
				q++;
			}
			else if (q == 2)
			{
				cout << "Тут как бы не игра в кнопку стоп. Играй! Послденее предупереждение!" << endl;
				q++;
			}
			else if (q == 3)
			{
				cout << "Хорошо ты сам напросился..." << endl;
				q++;
			}
			else if (q == 4)
			{
				cout << "Выход из игры!" << endl;
				Sleep(1000);
				exit(0);
			}

			Sleep(3000);
		}

		else if (k == 2)
		{
			system("cls");

			cout << "";

			int u = 0;
			bool Check = false;

			while (Check == false)
			{
				cout << "Движение по меню осуществляется кнопками w и s. Выбрать можно кнопкой f" << endl;
				cout << "100";
				if (u == 0) cout << " <--" << endl;
				else cout << endl;
				cout << "200";
				if (u == 1) cout << " <--" << endl;
				else cout << endl;
				cout << "300";
				if (u == 2) cout << " <--" << endl;
				else cout << endl;
				cout << "400";
				if (u == 3) cout << " <--" << endl;
				else cout << endl;
				cout << "500";
				if (u == 4) cout << " <--" << endl;
				else cout << endl;
				cout << "600";
				if (u == 5) cout << " <--" << endl;
				else cout << endl;
				cout << "700";
				if (u == 6) cout << " <--" << endl;
				else cout << endl;
				cout << "800";
				if (u == 7) cout << " <--" << endl;
				else cout << endl;

				switch (_getch())
				{
				case 'w':
					u--;
					break;
				case 's':
					u++;
					break;
				case 'f':
					system("cls");
					Check = true;
					break;
				default:
					break;
				}

				if (u == -1) u = 7;
				else if (u == 8) u = 0;

				system("cls");
			}

			switch (u)
			{
			case 0:
				Speed = 100;
				break;
			case 1:
				Speed = 200;
				break;
			case 2:
				Speed = 300;
				break;
			case 3:
				Speed = 400;
				break;
			case 4:
				Speed = 500;
				break;
			case 5:
				Speed = 600;
				break;
			case 6:
				Speed = 700;
				break;
			case 7:
				Speed = 800;
				break;
			default:
				break;
			}
		}

		else if (k == 3)
		{
			cout << "Закрытие иргы.";
			for (int i = 0; i < 3; i++)
			{
				cout << '.';
				Sleep(1000);
			}
			exit(0);
		}
	}

	system("pause");
	return 0;
}