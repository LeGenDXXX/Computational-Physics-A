#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 1000000 //16807�����������������������
#define PI 3.1415926 //PI�Ĵ�С

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double Random1[NUM_16807]; //��������theta�ĳ���
double Random2[NUM_16807]; //��������phi�ĳ���

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



void main() {
	int num, i;
	double sin_theta, cos_theta, phi, x, y, z; //��������ر���
	FILE *file = NULL;
	char filename[20] = {};

	printf("�����������������");
	scanf("%d", &num);

	//��16807��������������ȵ���������������������Ӧtheta��phi�ĳ���
	srand(time(NULL)); //�����������
	RNG_16807(Random1, num, rand());
	RNG_16807(Random2, num, rand());

	//������ݵ��ļ���
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		for (i = 0; i < num; i++) {
			//�򵥳����±任��theta��phi
			cos_theta = 1 - 2*Random1[i];
			phi = 2 * PI*Random2[i];

			//�����Ӧ���x��y��z����
			x = sqrt(1 - pow(cos_theta, 2))*cos(phi);
			y = sqrt(1 - pow(cos_theta, 2))*sin(phi);
			z = cos_theta;

			//���x��y��z���굽�ļ���
			fprintf(file, "%.15lf,%.15lf,%.15lf\n", x, y, z);
		}
		fclose(file);
	}
}