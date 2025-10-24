/*
    Nombre y apellidos: Manuel Rojas Tuyen
    Sección: A
*/

// Prototipos de funciones
void leerAeropuertos(int &n);
double** crearMatrizDinamica(const int &n);
void llenarMatriz(const int &n, double ** mat);
void mostrarMatriz(const int &n, double ** mat);
double calcularPromedio(const int &n, double ** mat);
void mostrarAerMenorDistancia(const int &n, double ** mat);
void liberarMatriz(const int &n, double ** &mat);

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;

int main(){
    srand(time(0));
    
    int n;
    leerAeropuertos(n);
    const int N = n;

    double **aer = crearMatrizDinamica(N);
    llenarMatriz(N, aer);

    cout<<"\nLa matriz de distancias es:"<<endl;
    mostrarMatriz(N, aer);
    

    double prom = calcularPromedio(N, aer);
    cout<<"El promedio de todas las distancias es: "<<prom<<" km."<<endl;


    mostrarAerMenorDistancia(N, aer);

    liberarMatriz(N, aer);
    return 0;
}

void leerAeropuertos(int &n){
    cout<<"\nIngrese la cantidad de aeropuertos: "; cin>>n;
}
double** crearMatrizDinamica(const int &n){
    double ** f = new double*[n];
    for (int i = 0; i < n; i++)
    {
        *(f+i) = new double[n];
    }

    return f;
    
}
void llenarMatriz(const int &n, double ** mat){
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            // La distancia de un aeropuerto a si mismo es '0'
            if (i==j)
            {
                mat[i][j] = 0;
            }else
            {
                // Se llenan los elementos arriba de la diagonal
                mat[i][j] = rand() % 1401 + 100;
                // La matriz de distancias es simetrica, entonces el elemento [i][j] es igual 
                //    al elemento [j][i] 
                mat[j][i] = mat[i][j];
            }
        }
    }
}
void mostrarMatriz(const int &n, double ** mat){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<mat[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}
double calcularPromedio(const int &n, double ** mat){
    double suma = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            // Se suman solo los elementos arriba de la diagonal, ya que la matriz es simetrica
            if (i!=j)
            {
                suma += mat[i][j];
            }
            
            
        }
    }

    // El numero de elementos arriba o abajo de la diagonal es '2n'
    return ( suma/(2*n) );
    
}
void mostrarAerMenorDistancia(const int &n, double ** mat){
    double min=-1;

    double prom_actual=1;
    int indice_i=-1; 

    for (int i = 0; i < n; i++)
    {
        double suma = 0;
        for (int j = 0; j < n; j++)
        {
            suma+=mat[i][j];
        }

        // Se calcula el promedio ignorando el elemento '0'
        prom_actual = suma/(n-1);

        // Si es el primer promedio o si el promedio actual es menor que 'min' 
        if (min == -1 || prom_actual < min)
        {
            min = prom_actual;
            indice_i=i;
        }
    }

    cout<<"\nEl aeropuerto con la menor distancia promedio hacia los demas es: ";
    cout<<"Aeropuerto "<<indice_i+1<<endl;
    cout<<"La distancia promedio es: "<<min<<" km."<<endl;
    
}

//  Se pasa el puntero por referencia para poder modificarlo
//  Si se pasa como 'double ** mat' no se modificara al hacer 'mat = nullptr'
void liberarMatriz(const int &n, double ** &mat){
    for (int i = 0; i < n; i++)
    {
        delete[] mat[i];
        mat[i] = nullptr;
    }
    delete[] mat;
    mat = nullptr;
}