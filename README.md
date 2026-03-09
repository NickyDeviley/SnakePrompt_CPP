# Snake Game Console C++ 🐍

Link do vídeo: https://www.youtube.com/watch?v=e8lYLYlrGLg
Canal: Javidx9

Um clássico jogo da cobrinha desenvolvido inteiramente em C++ para rodar diretamente no terminal do Windows. O projeto utiliza a API do Windows (Windows.h) para manipulação de buffers de tela, permitindo uma renderização rápida e fluida sem a necessidade de bibliotecas gráficas externas como SDL ou SFML.
🚀 Funcionalidades

    Renderização de Alto Desempenho: Uso de CreateConsoleScreenBuffer e WriteConsoleOutputCharacter para evitar o "flicker" (piscar da tela) comum em jogos de console simples.

    Sistema de Pontuação: Contador em tempo real exibido no topo da tela.

    Lógica de Movimentação: A cobra cresce ao comer e o jogo termina se houver colisão com as bordas ou com o próprio corpo.

    Suporte a Caracteres Especiais: Configurado para exibir acentuação e caracteres wchar_t (Wide Characters).

🛠️ Tecnologias Utilizadas

    Linguagem: C++

    API: Windows API (para manipulação de console e entrada de teclado).

    Bibliotecas Padrão: iostream, list, thread, chrono.

🎮 Como Jogar
Pré-requisitos

    Sistema Operacional Windows.

    Compilador C++ (GCC, Clang ou MSVC).

Comandos

    Setas Esquerda/Direita: Controlam a direção da cobra (o sistema rotaciona a direção atual).

    Barra de Espaço: Reinicia o jogo após o Game Over.

Legenda de Caracteres

    @ : Cabeça da cobra.

    O : Corpo da cobra.

    % : Comida.

    X : Estado de morte (colisão).
