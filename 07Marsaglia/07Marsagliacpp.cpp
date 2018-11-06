#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807�������������������������һ��Ҫ��С��210000000

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double u[NUM_16807]; //��������u�ĳ���
double v[NUM_16807]; //��������v�ĳ���

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
	int num, i, count = 0;
	double u_now, v_now, r2, x, y, z; //��������ر���
	FILE *file = NULL;
	char filename[20] = {};

	printf("�����������������");
	scanf("%d", &num);

	srand(time(NULL)); //�����������

	//������ݵ��ļ���
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		while (count < num) {

			//��16807��������������ȵ���������������������Ӧu��v�ĳ���
			RNG_16807(u, NUM_16807, rand());
			RNG_16807(v, NUM_16807, rand());

			for (i = 0; i<NUM_16807; i++) {
				//ʹ16807�������������[-1,1]���������·ֲ�
				u_now = -1 + 2 * u[i];
				v_now = -1 + 2 * v[i];
				r2 = u_now * u_now + v_now * v_now;
				if (r2 <= 1) {
					//�����Ӧ���x��y��z����
					x = 2 * u_now * sqrt(1 - r2);
					y = 2 * v_now * sqrt(1 - r2);
					z = 1 - 2 * r2;

					//���x��y��z���굽�ļ���
					fprintf(file, "%.10lf,%.10lf,%.10lf\n", x, y, z);

					count++; //������һ
					if (count >= num) //���ﵽnumʱ�������˳�
						break;
				}
			}
		}
		fclose(file);
	}
}