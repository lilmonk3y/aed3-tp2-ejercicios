#include <iostream>
#include <random>
using namespace std;

int main() {
	int fin;
	cin >> fin;
	random_device rd;
	mt19937 rng(rd());
	for (int i = 1; i <= fin; i++) {
		for (int j = 0; j < 5; j++) {
			normal_distribution<float> costos (2,3);

			cout << i << endl;
			for (int k = 0; k < i; k++) 
			{
				for (int l = 0; l <= k; l++)
				{
					cout << (int)(abs(costos(rng))+1) << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}


	return 0;
}
