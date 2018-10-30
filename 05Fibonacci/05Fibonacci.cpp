#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define OPERATOR + //Fibonacci�ӳٲ�������������������+��-��*��XOR
#define NUM_16807 210000000 //16807�������������������������һ��Ҫ��С��210000000
#define NUM_FIBONACCI  20000000 //Fibonacci��������������������һ��Ҫ��С��20000000������long long���鳤��̫��
#define START_NUM 10 //������ʼ��start�ĸ���


int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double x[NUM_16807]; //�������������
long long I[NUM_FIBONACCI]; //��������Fibonacci�ӳ���nС��p��qʱ����������
int starts[START_NUM]; //����������ʼֵstart������

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


//Fibonacci�ӳٲ������������������ɵ������������x�����������num���ӳ�������p��q����Fibonacci�ӳٲ����������������������һά������
//Fibonacci�ӳٲ������ĳ�ʼ������startΪ��ʼ���16807���������������
void RNG_Fibonacci(long long I[], double x[], int num,int start, int Fibonacci_p, int Fibonacci_q) {
	int i;
	
	I[0] = start;
	x[0] = double(start) / m;

	//����Schrage������16807���������������Fibonacci��ʼ����
	for (i = 1; i < (Fibonacci_p < Fibonacci_q ? Fibonacci_q : Fibonacci_p); i++) {
		start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
		I[i] = start;
		x[i] = double(start) / m;
	}

	//Fibonacci�ӳٲ�����
	for (; i < num; i++) {
		I[i] = (I[i - Fibonacci_p] OPERATOR I[i - Fibonacci_q]) % m;
		x[i] = double(I[i]) / m;
	}
}


//Count�������������ɵ������������x�����������num�����������ϵx[i - 1] < x[i + 1] < x[i]�ı���
double Count(double x[], int num) {
	int i, count = 0;
	for (i = 1; i < num - 1; i++)
		if (x[i - 1] < x[i + 1] && x[i + 1] < x[i]) //�����ϵ�����+1
			count++;
	return (double(count) / (num - 2)); //Ҫ����double
}



int main() {
	int start = 1, num = 1;//��ʼֵ
	int i, Fibonacci_p = 0, Fibonacci_q = 0; //�ֱ�Ϊѭ������i��Fibonacci�ӳ�p��q
	char filename[50] = {}; //�ļ���
	FILE *file = NULL;

	srand(time(NULL)); //���һ��������ӣ�Ϊ�Ժ�ʹ��

	//�����������
	//printf("�������ĸ�������ҪС��2*10^7����");
	//scanf("%d", &num);
	printf("��������ʼֵ��");
	scanf("%d", &start);
	printf("������Fibonacci�ӳٲ������ӳ�p��");
	scanf("%d", &Fibonacci_p);
	printf("������Fibonacci�ӳٲ������ӳ�q��");
	scanf("%d", &Fibonacci_q);

	
	//16807�����������������ʼֵ���������
	sprintf(filename, "16807,start=%d.txt", start);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		printf("\n\n   16807���������������ռ����\n\n");

		//��ͬ��������������16807���������������ռ����
		for (num = 100; num < NUM_16807; num *= 2) { //ѭ�����������
			RNG_16807(x, num, start);
			printf("   N = %-10d\tCount = %f\n", num, Count(x, num));
			fprintf(file, "%d,%.15f\n", num, Count(x, num));
		}
	}
	
	
	//16807����������������ʼֵ�������������ʼֵ��������������
	sprintf(filename, "16807,start=0.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else{
		//��ش�ӡ
		printf("\n\n   16807���������������ռ����\n\n");
		printf("      Num\t\t");
		fprintf(file, "1,"); //�����壬ֻ��Ϊ��python��ȡ����ʱ�ܹ�ֱ����numpy������ȡ��Ҫ��������Ϊ����

		//���������ʼ����ֵ����ӡ
		for (i = 0; i < START_NUM; i++) {
			start = rand();
			starts[i] = start;

			if (i != START_NUM - 1) {
				printf("%d\t", start);
				fprintf(file, "%d,", start);
			}
			else {
				printf("%d\n\n", start);
				fprintf(file, "%d\n", start);
			}
		}

		//16807����������������������ͬʱ��ӡ�ڿ���̨��������ļ���
		for (num = 100; num < NUM_16807; num *= 2) { //ѭ�����������N
			fprintf(file, "%d,", num);
			printf("   N = %-10d\t", num);

			for (i = 0; i < START_NUM; i++) { //ѭ����ʼ��
				RNG_16807(x, num, starts[i]);
				if (i != START_NUM - 1) {
					printf("%.4f\t", Count(x, num));
					fprintf(file, "%.15f,", Count(x, num));
				}
				else {
					printf("%.4f\n", Count(x, num));
					fprintf(file, "%.15f\n", Count(x, num));
				}
			}
		}
		printf("\n");
	}
	

	
	//Fibonacci�ӳ��������ʼֵ���������

	//�������p��q��������Ҫ��ע�͵�
	//Fibonacci_p = rand();
	//Fibonacci_q = rand();

	sprintf(filename, "4Fibonacci,%d,%d.txt", Fibonacci_p, Fibonacci_q);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		//��ش�ӡ
		printf("\n\n   Fibonacci���������������ռ����\n\n");
		printf("   p = %d, q = %d\n\n", Fibonacci_p, Fibonacci_q);
		printf("      Num\t\t");
		fprintf(file, "1,"); //�����壬ֻ��Ϊ��python��ȡ����ʱ�ܹ�ֱ����numpy������ȡ��Ҫ��������Ϊ����

		//���������ʼ����ֵ����ӡ
		for (i = 0; i < START_NUM; i++) {
			start = rand();
			starts[i] = start;

			if (i != START_NUM - 1) {
				printf("%d\t", start);
				fprintf(file, "%d,", start);
			}
			else {
				printf("%d\n\n", start);
				fprintf(file, "%d\n", start);
			}
		}
		
		//Fibonacci�ӳ��������������ͬʱ��ӡ�ڿ���̨��������ļ���
		for (num = 100; num < NUM_FIBONACCI; num *= 2) { //ѭ�����������N
			fprintf(file, "%d,", num);
			printf("   N = %-10d\t", num);

			for (i = 0; i < START_NUM; i++) { //ѭ����ʼ��
				RNG_Fibonacci(I, x, num, starts[i], Fibonacci_p, Fibonacci_q);
				if (i != START_NUM - 1) {
					printf("%.4f\t", Count(x, num));
					fprintf(file, "%.15f,", Count(x, num));
				}
				else {
					printf("%.4f\n", Count(x, num));
					fprintf(file, "%.15f\n", Count(x, num));
				}
			}
		}
		printf("\n");
	}
	

	system("pause");
}