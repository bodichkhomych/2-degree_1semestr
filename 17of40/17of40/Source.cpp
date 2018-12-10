#include <iostream>
#define MaxNodes 4
using namespace std;
class Warshall
{
private:
	unsigned Adj[MaxNodes][MaxNodes];  //������� ����������.
	unsigned Path[MaxNodes][MaxNodes]; //������� ������������.
	unsigned PathT[MaxNodes][MaxNodes];//����������������� ������� ������������.
	unsigned Adam[MaxNodes][MaxNodes]; //��������� ��������� 
									   //������������ Path*PathT.
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
	//���� ������� ���������� ��������� �����.
	cout << "������� �������� ������� ���������� �� �������:\n";
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
		{
			cout << "������� Adj[" << (i + 1) << "][" << (j + 1) << "]: ";
			cin >> Adj[i][j];
		}
}

void Warshall::TransClose()
//���������� ������� ������������.
{
	//������������� ������� Path �������� ���������� Adj.
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
			Path[i][j] = Adj[i][j];
	//���������� ��������� �������� ������� Path.
	for (int k = 0; k<MaxNodes; k++)
		for (int i = 0; i<MaxNodes; i++)
			if (Path[i][k] == 1)
				for (int j = 0; j<MaxNodes; j++)
					Path[i][j] = (Path[i][j] || Path[k][j]);
}

void Warshall::Vyvod_D()
//����� ������� ������������.
{
	cout << "������� ������������:\n";
	for (int i = 0; i<MaxNodes; i++)
	{
		for (int j = 0; j<MaxNodes; j++)
			cout << Path[i][j] << " ";
		cout << endl;
	}
}

void Warshall::Trans()
//���������������� ������� Path � ��������� ���������� �
//������� PathT.
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
//���������� ��������� ������������ Path�PathT.
{
	for (int i = 0; i<MaxNodes; i++)
		for (int j = 0; j<MaxNodes; j++)
			Adam[i][j] = Path[i][j] * PathT[i][j];
}

void Warshall::Vyvod_A()
//����� ��������� ������������.
{
	cout << "��������� ������������:\n";
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