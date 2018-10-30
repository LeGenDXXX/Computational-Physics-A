#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double x[210000000];

int main() {
	int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
	int start = 1, num = 0, now; //start����ʼ�㣬num�ǵ�ĸ�����now�����ڵ�������
	double schrage = double(start) / m; //schrage�ǵ��������ڵ�������һ����
	double xk = 0, difference, coefficient; //xk��x��k�׾࣬difference�Ǽ����x��k�׾�������ֵ�Ĳ��coefficient�����ϵ��
	int menu, i, k;

	printf("16807������\n\n");
	printf("1������Nֵ�µ�16807�����������������ά�����\n");
	printf("2��x��k�׾������������\n");
	printf("3��C(l)���Զ�ά��������������\n\n");
	printf("��������Ҫ�Ĺ��ܣ�");
	scanf("%d", &menu);

	switch (menu) {
	case 1: {
		//�����������
		printf("�������ĸ�����");
		scanf("%d", &num);
		printf("��������ʼֵ��");
		scanf("%d", &start);
		schrage = double(start) / m; //doubleҪ����

		//���ļ�
		char filename[50] = {};
		sprintf(filename, "num=%d,start=%d.txt", num, start);
		FILE *p = fopen(filename, "w");
		//��ʧ���򱨴�
		if (!p)
			printf("Open Fail!");
		else
			//ѭ������������
			for (i = 0; i < num; i++) {
				fprintf(p, "%.18lf,", schrage); //���뵱ǰ��ĺ�����
				start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m); //����Schrage������16807�����������������һ�������
				schrage = double(start) / m;
				fprintf(p, "%.18lf\n", schrage); //����һ�����������������
			}

		fclose(p);
	}//Ҫ��ӻ�����
		break;

	case 2: {
		//���ļ�
		printf("\n��������ʼֵ��");
		scanf("%d", &start);
		char filename[50] = {};
		sprintf(filename, "xk test,start=%d.txt",start);
		FILE *p = fopen(filename, "w");
		//��ʧ���򱨴�
		if (!p)
			printf("Open Fail!");
		else {		
			printf("\n   Num\t\tk=1\t\tk=2\t\tk=3\t\tk=4\t\tk=5");
			//���ò�ͬ��Num��
			for (num = 100; num <= 210000000; num *= 2) {
				fprintf(p, "%d,", num);
				printf("\n   %-10d\t", num);
				//���ó�ʼֵ
				now = start;
				schrage = double(start) / m;
				x[0] = schrage;

				//����Schrage������16807��������������������
				for (i = 1; i < num; i++) {
					now = (a*(now%q) - r * (now / q) >= 0) ? (a*(now%q) - r * (now / q)) : (a*(now%q) - r * (now / q) + m); 
					schrage = double(now) / m;
					x[i] = schrage;
				}

				//��ͬkֵ�µ�k�׾�������ֵ������
				for (k = 1; k <= 5; k ++) {
					xk = 0;
					//��k�׾�
					for (i = 0; i < num; i++)
						xk += pow(x[i], k);
					xk = xk / num;
					//��������ֵ������
					difference = 1 / (double(k) + 1)- xk; //Ҫ����double
					if (k < 5)
						fprintf(p, "%.18lf,", difference);
					else
						fprintf(p, "%.18lf\n", difference);
					printf("%.6lf\t", difference);
				}
			}
		}
		printf("\n\n");
		system("pause");
	}
		break;

	case 3: {
		int l;
		double mean, square_mean, l_mean, coefficient;

		printf("\n��������ʼֵ��");
		scanf("%d", &start);
		//���ļ�
		char filename[50] = {};
		sprintf(filename, "C(l)test,start=%d.txt",start);
		FILE *p = fopen(filename, "w");
		//��ʧ���򱨴�
		if (!p)
			printf("Open Fail!");
		else {
			printf("\n   Num\t\tl=1     l=2     l=3     l=4     l=5     l=6     l=7     l=8     l=9     l=10");

			//���ò�ͬ��Numֵ
			for (num = 100; num <= 210000000; num *= 2) {
				printf("\n   %-10d\t", num);
				fprintf(p, "%d,", num);
				//���ó�ʼֵ
				now = start;
				schrage = double(start) / m;
				x[0] = schrage;
				mean = schrage;
				square_mean = pow(schrage, 2);

				//����Schrage������16807��������������������
				for (i = 1; i < num; i++) {
					now = (a*(now%q) - r * (now / q) >= 0) ? (a*(now%q) - r * (now / q)) : (a*(now%q) - r * (now / q) + m);
					schrage = double(now) / m;
					x[i] = schrage;
					mean += schrage;
					square_mean += pow(schrage, 2);
				}
				//��ƽ��ֵ�뷽��ֵ
				mean = mean / num;
				square_mean = square_mean / num;

				//��ͬl�µ�C(l)
				for (l = 1; l <= 10; l++) {
					l_mean = 0;
					for (i = 0; i + l < num; i++) 
						l_mean += x[i] * x[i + l];
					l_mean = l_mean / (num - l);
					coefficient = (l_mean - pow(mean, 2)) / (square_mean - pow(mean, 2));
					if (l != 10)
						fprintf(p, "%.18lf,", coefficient);
					else
						fprintf(p, "%.18lf\n", coefficient);
					printf("%.4lf\t", coefficient);
				}
			}
		}
		printf("\n\n");
		system("pause");
	}
		break;

	default:
		break;
	}
}