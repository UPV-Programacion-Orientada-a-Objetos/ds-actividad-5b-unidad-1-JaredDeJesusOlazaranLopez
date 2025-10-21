#include <iostream>
using namespace std;
template <typename T>
class MatrizBase {
protected:
    int _filas;
    int _columnas;

public:
    MatrizBase(int filas, int columnas) : _filas(filas), _columnas(columnas) {}

    virtual ~MatrizBase() {}

    virtual void cargarValores() = 0;
    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const = 0;
    virtual void imprimir() const = 0;
};

template <typename T>
class MatrizDinamica : public MatrizBase<T> {
    T **_datos; 

public:
    MatrizDinamica(int filas, int columnas)
        : MatrizBase<T>(filas, columnas) {
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++)
            _datos[i] = new T[this->_columnas];
    }
    ~MatrizDinamica() {
        for (int i = 0; i < this->_filas; i++)
            delete[] _datos[i];
        delete[] _datos;
    }
    void cargarValores() override {
        cout << "Introduce los valores de una matriz "
             << this->_filas << "x" << this->_columnas << ":\n";
        for (int i = 0; i < this->_filas; i++)
            for (int j = 0; j < this->_columnas; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> _datos[i][j];
            }
    }
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        const MatrizDinamica<T>* o = dynamic_cast<const MatrizDinamica<T>*>(&otra);

        if (!o || this->_filas != o->_filas || this->_columnas != o->_columnas) {
            cout << "Error: dimensiones incompatibles para la suma.\n";
            return nullptr;
        }

        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->_filas, this->_columnas);

        for (int i = 0; i < this->_filas; i++)
            for (int j = 0; j < this->_columnas; j++)
                resultado->_datos[i][j] = this->_datos[i][j] + o->_datos[i][j];

        return resultado;
    }
    void imprimir() const override {
        for (int i = 0; i < this->_filas; i++) {
            cout << "| ";
            for (int j = 0; j < this->_columnas; j++)
                cout << _datos[i][j] << " ";
            cout << "|\n";
        }
    }
};

template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
    T _datos[M][N]; 

public:
    MatrizEstatica() : MatrizBase<T>(M, N) {}

    // Método para llenar la matriz
    void cargarValores() override {
        cout << "Introduce los valores de una matriz "
             << M << "x" << N << ":\n";
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> _datos[i][j];
            }
    }
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        const MatrizEstatica<T, M, N>* o = dynamic_cast<const MatrizEstatica<T, M, N>*>(&otra);

        if (!o) {
            cout << "Error: tipos o dimensiones incompatibles.\n";
            return nullptr;
        }

        MatrizEstatica<T, M, N>* resultado = new MatrizEstatica<T, M, N>();

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                resultado->_datos[i][j] = this->_datos[i][j] + o->_datos[i][j];

        return resultado;
    }

    void imprimir() const override {
        for (int i = 0; i < M; i++) {
            cout << "| ";
            for (int j = 0; j < N; j++)
                cout << _datos[i][j] << " ";
            cout << "|\n";
        }
    }
};

int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---\n\n";

    cout << ">> Demostración con tipo FLOAT <<\n\n";

    MatrizBase<float>* A = new MatrizDinamica<float>(2, 2);
    cout << "Matriz A:\n";
    A->cargarValores();

    MatrizBase<float>* B = new MatrizDinamica<float>(2, 2);
    cout << "\nMatriz B:\n";
    B->cargarValores();

    cout << "\nSUMANDO: Matriz C = A + B ...\n";
    MatrizBase<float>* C = A->sumar(*B);

    if (C) {
        cout << "\nMatriz Resultado C:\n";
        C->imprimir();
    }

    delete A;
    delete B;
    delete C;

    cout << "\n>> Memoria liberada correctamente. Programa finalizado. <<\n";
    return 0;
}
