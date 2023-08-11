#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

vector<vector<int>> M;  // La matriz. La vamos a ir pasando por referencia y sus los valores
vector<int> sf;         // Vector de la suma en cada fila
vector<int> sc;         // Vector con la suma en cada columna
vector<int> sd;         // Vector con la suma en cada diagonal
int nm;                 // El numero magico
int kEsimo;             // Representa cuantos cuadrados magicos ya encontramos
int k;                  // Representa el cuadrado magico que buscamos
int n;                  // Dimensiones del cuadrado
bool encontrado;        // Nos dice si ya encontramos el cuadrado magico o no
vector<bool> disponible;    // Representa al conjunto de números que estan disponibles para ser agregados a la matriz
// Los numeros que puedo agregar aparecen con true y los que no, con false

bool completo (int i, int j){
    return (i==n) && (j==0);
}

int numeroMagico(int n){
    return (pow(n,3) + n)/2;      // La formula vista en la guia;
}

void imprimirMatriz(vector<vector<int>> &M){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << M[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

pair<int,int> sig(int i, int j, int n){         //calcula la siguiente celda en la matriz
    if(j==n-1) {
        i++;
        j = 0;
    }else{
        j++;
    }
    return {i,j};
}

void sumar(int i, int j,int q){        // Suma el numero q a todas las sumas parciales
    sf[i] = sf[i]+q;
    sc[j] = sc[j]+q;
    if(i==j){
        sd[0] = sd[0]+q;
    }
    if(i==(n-1-j)){
        sd[1]=sd[1]+q;
    }
}

void restar(int i, int j, int q){      // Resta el numero q a todas las sumas parciales
    sf[i] = sf[i]-q;
    sc[j] = sc[j]-q;
    if(i==j){
        sd[0]=sd[0]-q;
    }
    if(i==(n-1-j)){
        sd[1]=sd[1]-q;
    }
    M[i][j]=0;
}

bool poda1(int i, int j){               // Poda por factibilidad
    return (sf[i]>nm || sc[j]>nm || sd[0]>nm || sd[1]>nm);      // Chequeamos de no pasarnos del numero magico en cada fila, columna o diagonal a la que estemos sumando
}

bool poda2(int i, int j){               // Poda por optimalidad
    return (j==(n-2) && (i!=(n-1)));    // Podemos completar la ultima celda de una fila en base a las anteriores celdas de la fila
}

bool poda3(int i, int j){               // Poda por optimalidad
    return (i==(n-1) && (j==0));        // Podemos completar la ultima fila en base a las anteriores filas
}

void aplicarPoda2(int i, int j, vector<bool> &disponible, vector<vector<int>> &M, function<void(int, int, vector<bool>& , vector<vector<int>>& )> CM){
    int q=nm-sf[i];
    if(0<=q && q<=pow(n,2) && disponible[q]){
        sumar(i,j+1,q);
        if (!poda1(i,j+1)){
            M[i][j + 1] = q;
            disponible[q]=false;
            pair<int, int> ij2 = sig(i, j + 1, n);
            CM(ij2.first, ij2.second, disponible,M);
            disponible[q]=true;
        }
        restar(i, j + 1, q);
    }
}


void aplicarPoda3(int i, int j, vector<bool> &disponible, vector<vector<int>> &M, function<void(int, int, vector<bool>&, vector<vector<int>>& )> CM){
    int cantidad = 0;
    for(int j=0;j<n;j++){
        int q=nm-sc[j];
        if(0<=q && q<=pow(n,2) && disponible[q]){
            sumar(i,j,q);
            M[i][j] = q;
            cantidad++;
            disponible[q]=false;
        }
    }
    if(sf[n-1]==nm && sd[0]==nm && sd[1]==nm && cantidad==n){
        pair<int, int> ij2 = sig(n-1, n-1, n);
        CM(ij2.first, ij2.second, disponible,M);
    }
    for(int j=0;j<n;j++){
        disponible[M[n-1][j]]=true;
        restar(n-1,j,M[n-1][j]);

    }
}

void CM(int i, int j,  vector<bool> &disponible, vector<vector<int>> &M){        // Busca completar el cuadrado magico a partir de la celda (i,j) con los numeros disponibles que estan en C
    if(!encontrado){
        if (completo(i,j)){                     // Si no quedan numeros por agregar, la matriz paso todas las podas y esta completa
            kEsimo++;                       // Siempre colocamos los numeros de C en orden. Ademas, iteramos las celdas de M en orden lexicografico
            if(kEsimo==k){                  // Por lo que las sucesivas matrices se construyen en orden lexicografico
                imprimirMatriz(M);
                encontrado = true;
            }
        }else{
            if(poda3(i,j)) {
                aplicarPoda3(i, j, disponible, M,CM);
            }else{
                for(int q=1; q<pow(n,2)+1;q++){                         // Probamos poner en orden cada uno de los números disponibles en la posición actual
                    if(disponible[q]){
                        sumar(i,j,q);
                        if (!poda1(i,j)){
                            M[i][j]=q;
                            disponible[q]=false;
                            if(poda2(i,j)){
                                aplicarPoda2(i,j,disponible,M, CM);
                            }else{
                                pair<int,int> ij2 = sig(i,j,n);
                                CM(ij2.first,ij2.second,disponible,M);
                            }
                            disponible[q]=true;
                        }
                        restar(i,j,q);
                    }
                }
            }
        }
    }
}

int main() {
    cin >> n >> k;
    M.resize(n,vector<int>(n,0));
    disponible.resize(pow(n,2)+1);
    for(int i=1;i<pow(n,2)+1;i++){
        disponible[i]=true;
    }
    sf.resize(n,0);
    sc.resize(n,0);
    sd.resize(2,0);
    nm = numeroMagico(n);
    kEsimo=0;                               // Representa la cantidad de cuadrados magicos que encontramos
    encontrado = false;                     // Nos dice si ya encontramos la respuesta

    CM(0,0,disponible,M);

    if(!encontrado){
        cout << -1;
    }
    return 0;
}
