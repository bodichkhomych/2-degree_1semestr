#include <iostream>
#define MaxNodes 4
using namespace std;
class Warshall
{
private:
	unsigned Adj[MaxNodes][MaxNodes];  //Матрица смежностей.
	unsigned Path[MaxNodes][MaxNodes]; //Матрица достижимости.
	unsigned PathT[MaxNodes][MaxNodes];//Транспонированная матрица достижимости.
	unsigned Adam[MaxNodes][MaxNodes]; //Результат адамарова 
									   //произведения Path*PathT.
public:
	void Vvod();
	void TransClose();
	void Vyvod_D();
	void Trans();
	void Adamar();
	void Vyvod_A();
};

void Warshall::Vvod()
{
	//Ввод матрицы смежностей заданного графа.
	cout << "Вводите элементы матрицы смежностей по строкам:\n";
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
		{
			cout << "Введите Adj[" << (i + 1) << "][" << (j + 1) << "]: ";
			cin >> Adj[i][j];
		}
}

void Warshall::TransClose()
//Вычисление матрицы достижимости.
{
	//Инициализация матрицы Path матрицей смежностей Adj.
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
			Path[i][j] = Adj[i][j];
	//Нахождение следующих значений матрицы Path.
	for (int k = 0; k<MaxNodes; k++)
		for (int i = 0; i<MaxNodes; i++)
			if (Path[i][k] == 1)
				for (int j = 0; j<MaxNodes; j++)
					Path[i][j] = (Path[i][j] || Path[k][j]);
}

void Warshall::Vyvod_D()
//Вывод матрицы достижимости.
{
	cout << "Матрица достижимости:\n";
	for (int i = 0; i<MaxNodes; i++)
	{
		for (int j = 0; j<MaxNodes; j++)
			cout << Path[i][j] << " ";
		cout << endl;
	}
}

void Warshall::Trans()
//Транспонирование матрицы Path и помещение результата в
//матрицу PathT.
{
	unsigned k, r;
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
		{
			k = Path[i][j]; r = Path[j][i];
			PathT[j][i] = k; PathT[i][j] = r;
		}
}

void Warshall::Adamar()
//Нахождение адамарова произведения PathхPathT.
{
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
			Adam[i][j] = Path[i][j] * PathT[i][j];
}

void Warshall::Vyvod_A()
//Вывод адамарова произведения.
{
	cout << "Адамарово произведение:\n";
	for (int i = 0; i<MaxNodes; i++)
	{
		for (int j = 0; j<MaxNodes; j++)
			cout << Adam[i][j] << " ";
		cout << endl;
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	Warshall A;
	A.Vvod();
	A.TransClose();
	A.Vyvod_D();
	A.Trans();
	A.Adamar();
	A.Vyvod_A();
	system("pause");
}