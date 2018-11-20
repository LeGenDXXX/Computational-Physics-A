#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 100000 //16807�����������������������
#define N 10 

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double x[N][NUM_16807]; //�������������
int Ns[3] = { 2,5,10 };


//16807������������������������ɵ������������x�����������num����ʼ��start����16807����������������������������һά������
void RNG_16807(double x[], int num, int start) {
	int i;
	x[0] = double(start) / m;

	//����Schrage������16807��������������������
	for (i = 1; i < num; i++) {
		start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
		x[i] = double(start) / m;
	}
}



int main() {
	int i, j, k;
	double x_now, E, Var;
	char filename[20] = {};
	FILE *file = NULL;

	srand(time(NULL)); //��������

	for (i = 0; i < 3; i++) {
		for (j = 0; j < Ns[i]; j++)
			RNG_16807(x[j], NUM_16807, rand()); //���������
		
		//0-1�ֲ�
		E = 0.5, Var = 0.25;
		sprintf(filename, "01,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //���������
				for (x_now = 0, j = 0; j<Ns[i]; j++) //����Xi
					if (x[j][k]<= 0.5)
						x_now += 0;
					else
						x_now += 1;
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //��ӡ���ļ���
			}
			fclose(file);
		}
		


		//����ֲ�
		E = 2.5, Var = 1.25;
		sprintf(filename, "binom,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //���������
				for (x_now = 0, j = 0; j < Ns[i]; j++) //����Xi
					if (x[j][k] <= 1.0 / 32)
						x_now += 0;
					else if (x[j][k] <= 6.0 / 32)
						x_now += 1;
					else if (x[j][k] <= 16.0 / 32)
						x_now += 2;
					else if (x[j][k] <= 26.0 / 32)
						x_now += 3;
					else if (x[j][k] <= 31.0 / 32)
						x_now += 4;
					else
						x_now += 5;
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //��ӡ���ļ���
			}
			fclose(file);
		}


		
		//���ȷֲ�
		E = 1, Var = 1.0/3;
		sprintf(filename, "uni,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //���������
				for (x_now = 0, j = 0; j < Ns[i]; j++) //����Xi
					x_now += 2 * x[j][k];
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //��ӡ���ļ���
			}
			fclose(file);
		}
		



		//ָ���ֲ�
		E = 1, Var = 1;
		sprintf(filename, "expo,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //���������
				for (x_now = 0, j = 0; j < Ns[i]; j++) //����Xi
					x_now += -log(1 - x[j][k]);
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //��ӡ���ļ���
			}
			fclose(file);
		}
	}
}