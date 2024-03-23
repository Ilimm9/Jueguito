#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

/*void puntos_recta(double x1, double y1, double x2, double y2){
    double m = (y2-y1)/(x2-x1); //pendiente
    //if(m<0){}
    double B = y1-m*x1; //Origen

    for(int x=x1; x<=x2; x++){
        int y = round(m*x+B);
        cout<<"("<<x<<","<<y<<")"<<endl;
    }
}*/

void dibujar_carro(char matriz_carro[3][3])
{
    // cout << "separador" << endl;
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

void sustituir(char matriz[12][13], char matriz_peque[3][3], int fila_inicio, int columna_inicio)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matriz[fila_inicio + i][columna_inicio + j] = matriz_peque[i][j];
        }
    }
}

void rellenar_matriz(char matriz[12][13])
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

void traslacion(char matriz[12][13], int x,int y){
for(int i=1; i<4; i++){
    for(int j=0; j<12; j++){
            char aux = matriz[i][j];
            //matriz[i][j+1] = aux;
            matriz[i+1][j] = aux;
            matriz[i][j]=' ';
    }

}
}
int main()
{
    int y=0,x=1;
    char matriz[12][13];
    char matriz_carro[3][3];
    rellenar_matriz(matriz);
    dibujar_carro(matriz_carro);
    sustituir(matriz, matriz_carro, y, x);
    sustituir(matriz, matriz_carro, 9, 9);
    imprimirMatrizPrincipal(matriz);
    traslacion(matriz,x,y   );
        imprimirMatrizPrincipal(matriz);

    x+=1;
    return 0;
}

