#include <iostream>
#include <math.h>
#include <iomanip>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#ifdef _WIN32
#include <conio.h> // Solo para Windows
#endif

using namespace std;

void dibujar_carro(char matriz_carro[3][3]) //Dibujamos el carro en una matriz pequenia
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((i == 0 && j == 0) || (i == 2 && j == 2) || (i == 0 && j == 2) || (i == 2 && j == 0))
            {
                matriz_carro[i][j] = ' ';
            }
            else
            {
                matriz_carro[i][j] = '*';
            }
        }
    }
}

void sustituir(char matriz[12][13], char matriz_peque[3][3], int fila_inicio, int columna_inicio)//Le pasamos la matriz pequenia (tiene el carro dibujado) a la main matriz
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matriz[fila_inicio + i][columna_inicio + j] = matriz_peque[i][j];
        }
    }
}

void limpiar(char matriz[12][13], int fila_inicio, int columna_inicio)//limpiamos donde habia un carro para realizar el desplazamiento
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matriz[fila_inicio + i][columna_inicio + j] = ' ';
        }
    }
}

void rellenar_matriz(char matriz[12][13])//creamos el formato del juego en la matriz principal
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (j == 0 || j == 12 || j % 4 == 0)
            {
                matriz[i][j] = '|';
            }
            else
            {
                matriz[i][j] = ' ';
            }
        }
    }
}

void imprimirMatrizPrincipal(char matriz[12][13])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void limpiarConsola()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int obtenerNumeroAleatorio()
{
    // Inicializamos el generador de números aleatorios con una semilla basada en el tiempo actual
    std::random_device rd;
    std::mt19937 gen(rd());

    // Creamos una distribución uniforme entre 0 y 2 (ambos inclusive)
    std::uniform_int_distribution<> distribucion(0, 2);

    // Generamos un número aleatorio entre 0 y 2
    int aleatorio = distribucion(gen);

    // Mapeamos el número aleatorio a 1, 5 o 9 y lo devolvemos
    switch (aleatorio)
    {
    case 0:
        return 1;
    case 1:
        return 5;
    default:
        return 9;
    }
}

void pausar(int segundos)//pausamos la consola durante n cantidad de segundos
{
    this_thread::sleep_for(chrono::seconds(segundos));
}

bool buscarAsterisco(char matriz[12][13])
{
    int cont = 0;
    for (int i = 2; i < 11; i += 4)
    {
        if (matriz[11][i] == '*')
        {
            cont++;
        }
    }
    return (cont > 1);
}

void traslacion(char matriz[12][13], int x, int posicion)//funcino para realizar la traslacion del carro en la matriz principal
{
    int pos = 0;
    if (buscarAsterisco(matriz) && x != posicion)// si tiene dos carros, pero ninguno de ellos es el carro del usuario, 
    {                                           //realizamos el desplazamiento completo de la columna
        pos = 12;
    }
    else if (matriz[11][x + 1] == '*' && x == posicion)//de lo contrario, hay 2 o 3 carros en una columna y uno de ellos es el del usuario,
    {                                                   //por lo cual solo se realiza la traslacion del otro carro
        pos = 7;
    }
    else    //si no se cumple ninguna, significa que solo hay un carro en un carril, y se puede realizar la traslacion sin problemas
    {
        pos = 12;
    }
    for (int i = pos; i >= 0; i--)
    {
        for (int j = x; j < x + 3; j++)
        {
            char aux = matriz[i][j];
            matriz[i][j] = matriz[i + 1][j];
            matriz[i + 1][j] = aux;
        }
    }
    for (int j = x; j < x + 3; j++)
    {
        matriz[0][j] = ' ';
    }
}

void imprimirGameOver()
{
    std::cout << "  _____          __  __ ______    ______      ________ _____  \n";
    std::cout << " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n";
    std::cout << "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n";
    std::cout << "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n";
    std::cout << "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n";
    std::cout << " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\ \n";
    std::cout << "                                                               \n";
}

int main()
{
    char matriz[12][13];//matriz principal
    char matriz_carro[3][3];//matriz que contiene el carro
    rellenar_matriz(matriz);
    dibujar_carro(matriz_carro);

    // dibujamos carros en la matriz principal
    sustituir(matriz, matriz_carro, 0, 1);
    sustituir(matriz, matriz_carro, 9, 9);//carro manejado por el usuario

    int posicion = 9;
    int aux2 = posicion;
    int c = 0;
    for (int i = 0;;)
    {
        aux2 = posicion;
        imprimirMatrizPrincipal(matriz);
        if (matriz[9][posicion + 1] == '*' && matriz[8][posicion + 1] == '*')//condicion para ver si no hay un choque de frente entre dos carros
        {
            break;
        }

        traslacion(matriz, 1, posicion);//traslacion del primer carro

        posicion = aux2;
        traslacion(matriz, 5, posicion);//traslacion del segundo carro

        posicion = aux2;
        int aux = aux2;
        traslacion(matriz, 9, posicion);//traslacion del carro del usuario

        posicion = aux;

        if (c % 7 == 0 && c != 0)//condicion para la aparicion de un segundo carro
        {
            sustituir(matriz, matriz_carro, 0, obtenerNumeroAleatorio());
        }

        std::cout << "Presiona la flecha izquierda o derecha para desplazarse, o cualquier tecla para continuar..." << std::endl;
        int tecla = 0;

        while (true)
        {
            tecla = _getch(); // Leer una tecla sin necesidad de presionar Enter en Windows

            if (tecla == 224)
            {                     // Si es una tecla especial (como las flechas)
                tecla = _getch(); // Leer el segundo byte de la secuencia
                switch (tecla)
                {
                case 75: // Flecha izquierda
                    if (posicion != 1)
                    {
                        if (matriz[11][posicion - 3] == '*' && matriz[11][posicion + 1] == '*')//conficion para validar choques laterales
                        {
                            imprimirGameOver();
                            pausar(3);
                            return 0;
                        }
                        else
                        {
                            limpiar(matriz, 9, posicion);//para mover un carro primero limpiamos el dibujo
                            posicion = posicion - 4;
                            sustituir(matriz, matriz_carro, 9, posicion);//despues de limpiar lo volvemos a dibujar en su nueva posicion
                        }
                    }
                    break;
                case 77: // Flecha derecha
                    if (posicion != 9)
                    {
                        if (matriz[11][posicion + 1] == '*' && matriz[11][posicion + 5] == '*')//conficion para validar choques laterales
                        {
                            imprimirGameOver();
                            pausar(3);
                            return 0;
                        } else {
                            limpiar(matriz, 9, posicion);//para mover un carro primero limpiamos el dibujo
                            posicion = posicion + 4;
                            sustituir(matriz, matriz_carro, 9, posicion);//despues de limpiar lo volvemos a dibujar en su nueva posicion
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        }

        limpiarConsola();

        c++;
    }

    imprimirGameOver();

    pausar(3);
    return 0;
}