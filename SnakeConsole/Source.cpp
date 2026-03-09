#include <iostream>		// Para imprimir mensagens no console
#include <Windows.h>	// Para criar uma janela
#include <list>			// Para criar a lista de segmentos da cobra
#include <locale.h>		// Para atualizar a linguagem do prompt
#include <thread>		// Para criar uma pausa no loop
#include <chrono>		// Para criar uma pausa no loop
#include <iterator>		// Para iterar sobre a lista de segmentos da cobra

using namespace std;	// Para não precisar escrever "std::" toda hora

int nScreenWidth = 120;	// Largura
int nScreenHeight = 30;	// Altura

// Variável composta para armazenar
// as posições de cada segmento da cobra
struct sSnakeSegment {
	int x;
	int y;
};

int main(int argc, char* argv[]) {

	// Atualizando a linguagem do prompt
	// para imprimir acentos
	setlocale(LC_ALL, "portuguese");

	/*
		Criando o canvas = Aonde tudo será desenhado.
		Nós criamos um array com tamanho = 120 * 80,
		do tipo wchar, que significa "Wide Character".
		Char é uma variável de apenas 1 byte, wchar suporta
		2 bytes, permitindo utilizar caracteres mais complexos.

		Criamos um "objeto" HANDLE, no windows a maioria
		dos recursos é acessado através dele. (Não é exatamente um objeto);

		Então nós criamos com a função "CreateConsoleScreenBuffer" uma janela de console.
		Utilizamos os "GENERIC_READ | GENERIC_WRITE" para definir que podemos ler e escrever nesta janela.

		"CONSOLE_TEXTMODE_BUFFER" informa ao computador que a janela não
		será usada para gráficos complexos (Pixels Coloridos)

		Utilizamos a função "SetConsoleActiveScreenBuffer" para definir que a janela 
		que acabamos de criar é a janela ativa, ou seja, a janela que irá mostrar 
		o que desenharmos.

		"DWORD" é abreviação de "Double Word". Nós criamos essa "Variável"
		para armazenar quantos caracteres foram desenhados com sucesso.
	*/
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while (true) {

		// Corpo da Cobra
		list<sSnakeSegment> snake = { {60, 15}, {61, 15}, {62,15}, {63,15}, {64,15}, {65,15}, {66,15}, {67,15}, {68,15}, {69,15} };

		// Posição da comida
		int nFoodX = 30;
		int nFoodY = 15;
		int nScore = 0;				// Posição dos pontos
		int nSnakeDirection = 3;	// Direção da cobra
		bool bDead = false;			// Verifica se a cobra está morta

		// Verifica as posições que a cobra está se movendo
		bool bKeyLeft = false, bKeyRight = false, bKeyLeftOld = false, bKeyRightOld = false;

		while (!bDead) {

		// TIMING & INPUT
			// Pausa na atualização do loop
			//this_thread::sleep_for(200ms);

			// Get Input
			// Verifica se a tecla foi pressionada e retorna um valor booleano
			auto t1 = chrono::system_clock::now();
			while ((chrono::system_clock::now() - t1) < ((nSnakeDirection % 2 == 1) ? 120ms : 200ms)) {
				bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
				bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

				// Verifica se a cobra já não está se movendo naquela direção
				if (bKeyRight && !bKeyRightOld) {
					nSnakeDirection++;
					if (nSnakeDirection == 4) { nSnakeDirection = 0; }
				}
				if (bKeyLeft && !bKeyLeftOld) {
					nSnakeDirection--;
					if (nSnakeDirection == -1) { nSnakeDirection = 3; }
				}

				// Atualiza as variáveis de controle para a próxima leitura
				bKeyRightOld = bKeyRight;
				bKeyLeftOld = bKeyLeft;
			}

		// GAME LOGIC
				// Update Snake Position
				// Verifica qual posição a cobra deve se mover e atualiza sua posição
			switch (nSnakeDirection) {
			case 0:	// UP
				snake.push_front({ snake.front().x, snake.front().y - 1 });
				break;
			case 1:	// RIGHT
				snake.push_front({ snake.front().x + 1, snake.front().y });
				break;
			case 2:	// DOWN
				snake.push_front({ snake.front().x, snake.front().y + 1 });
				break;
			case 3:	// LEFT
				snake.push_front({ snake.front().x - 1, snake.front().y });
				break;
			}

			// Collision Detection
			// Verifica se a cobra colidiu com as bordas
			if (snake.front().x < 0 || snake.front().x >= nScreenWidth) { bDead = true; }
			if (snake.front().y < 3 || snake.front().y >= nScreenHeight) { bDead = true; }

			// Collision Detect Snake V Food
			// Verifica se a cobra colidiu com a comida
			if (snake.front().x == nFoodX && snake.front().y == nFoodY) {

				// Aumenta os pontos
				nScore++;

				// cria uma nova comida em uma posição aleatória
				while (screen[nFoodY * nScreenWidth + nFoodX] != L' ') {
					nFoodX = rand() % nScreenWidth;
					nFoodY = (rand() % (nScreenHeight - 3)) + 3;
				}

				// Aumenta o tamanho da cobra
				for (int i = 0; i < 5; i++) {
					snake.push_back({ snake.back().x, snake.back().y });
				}
			}

			// Collision Detect Snake V Snake
			// Verifica se a cobra colidiu com ela mesma
			for (list <sSnakeSegment>::iterator i = snake.begin(); i != snake.end(); i++) {
				if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y) { bDead = true; }

			}

			// Chop off Snakes Tail
			// Exclui a última posição da cobra para dar a ilusão de movimento
			snake.pop_back();

		// DISPLAY TO PLAYER

			// Clear Screen
			// Limpa a tela para a próxima atualização de movimento
			for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
				screen[i] = L' ';
			}

			// Draw Stats & Border
			// Desenha na tela o status e a borda superior
			for (int i = 0; i < nScreenWidth; i++) {
				screen[i] = L'=';
				screen[2 * nScreenWidth + i] = L'=';
			}
			wsprintf(&screen[nScreenWidth + 5], L"Snake Game Console            Pontuação = %d", nScore);

			// Draw Snake Body
			// Desenha o corpo da cobra
			for (auto s : snake) {
				screen[s.y * nScreenWidth + s.x] = bDead ? L'+' : L'O';
			}

			// Draw Snake Head
			// Desenha a cabeça da cobra
			screen[snake.front().y * nScreenWidth + snake.front().x] = bDead ? L'X' : L'@';

			// Drawn Food
			// Desenha a comida
			screen[nFoodY * nScreenWidth + nFoodX] = L'%';

			// Display Frame | Atualiza o que está desenhado
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
		}

		// Game Over Message
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
	}

	delete[] screen;
	screen = nullptr;

	return 0;
}