#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807�����������������������
#define PI 3.1415926
#define C 0.92153762 //����õ���Lorentz Like�ֲ����������������Сϵ��
#define BLOCK 100 //ֱ��ͼ����

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double xs[NUM_16807], ys[NUM_16807]; //�������������
double sample[NUM_16807]; //���������������
int counts[BLOCK] = { 0 }; //��������ֶ�����



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



//Lorentz-like ���ۼƺ���
double CumulativeFunction(double x) {
	return ((2 * atan(1 + sqrt(2)*x) - 2 * atan(1 - sqrt(2)*x) + log((x*x + sqrt(2)*x + 1) / (x*x - sqrt(2)*x + 1))) / (4 * PI) + 1.0 / 2);
}



int main() {
	double x, y1, y2;
	int i, j, n, count, num;
	FILE *file = NULL;
	char filename[20] = {};

	printf("������������ĸ�����");
	scanf("%d", &num);

	srand(time(NULL)); //�������������

	//��16807��������������������
	RNG_16807(xs, num, 1);
	RNG_16807(ys, num, rand());

	for (i = 0, count = 0; i < num; i++) {
		/*
		//���ۼƺ����ķ�������ĳ���������������ѡȡ�ڱ����У�
		if (xs[i] < 0.005299474)
			continue;
		else
			if (xs[i] < 0.164117)
				x = log(xs[i] - 0.005299474) / 2.3;
			else
				if (xs[i] < 0.3651704)
					x = (xs[i] - 0.4858025) / 0.402107;
				else
					if (xs[i] < 0.6348296)
						x = (xs[i] - 0.5) / 0.449432;
					else
						if (xs[i] < 0.835883)
							x = (xs[i] - 0.5141975) / 0.402107;
						else
							if (xs[i] < 0.994700525)
								x = -log(0.994700525 - xs[i]) / 2.3;
							else
								continue;
		*/

		//��ɢ���ֲ���������ȡ��Ӧ���е�Ϊxֵ
		for (j = 0; j < BLOCK; j++)
			if (CumulativeFunction(-3 + j * 6.0 / BLOCK) <= xs[i] && CumulativeFunction(-3 + (j + 1) * 6.0 / BLOCK) > xs[i]) {
				x = -3 + (j + 0.5)*6.0 / BLOCK;
				//���㵱ǰ�����µ���������ֵ
				y1 = exp(-x * x / 2) / sqrt(2 * PI);
				y2 = C / (1 + pow(x, 4));

				//��ѡ����������Ҫ�����ĺ���ʱ����������Ϊ����ֵ
				if (y1 > y2*ys[i]) {
					sample[count] = x;
					count++;
				}
				break;
			}
				
		/*
		//���㵱ǰ�����µ���������ֵ
		y1 = exp(-x * x / 2) / sqrt(2 * PI);
		y2 = C / (1 + pow(x, 4));

		//��ѡ����������Ҫ�����ĺ���ʱ����������Ϊ����ֵ
		if (y1 > y2*ys[i]) {
			sample[count] = x;
			count++;
		}
		*/
	}

	//�������õ�������ӡ���ļ���
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n\n");
	else {
		fprintf(file, "%lf\n", double(count) / num); //������Ч�ʴ�ӡ���ļ���
		fprintf(file, "%d\n", BLOCK); //��ֱ��ͼ������ӡ���ļ���
		for (i = 0; i < count; i++)
			fprintf(file, "%.10f\n", sample[i]); //�����������ӡ���ļ���
		fclose(file);
	}

	//���������д�ӡ������
	printf("%lf\n", double(count) / num);
	system("pause");
}