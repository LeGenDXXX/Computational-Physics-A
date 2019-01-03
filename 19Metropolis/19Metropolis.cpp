#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



int main() {
	int N = 1000000, M = 100000, i;
	double sigma_x, sigma_y, step, x0, y0, x_now, y_now, r, sum_x2 = 0, sum_y2 = 0, sum_xy2 = 0;
	char filename[50] = {};
	FILE *file = NULL;

	//�����������
	printf("������sigma_x��");
	scanf("%lf", &sigma_x);
	printf("������sigma_y��");
	scanf("%lf", &sigma_y);
	printf("�����벽����");
	scanf("%lf", &step);
	printf("��������ʼ�����꣺");
	scanf("%lf", &x0);
	printf("��������ʼ�����꣺");
	scanf("%lf", &y0);

	srand(time(NULL)); //�������������

	for (i = 0; i < M; i++) {
		//��������¸�λ�õ����겢�����ֵr
		x_now = x0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
		y_now = y0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
		r = exp(-0.5*(x_now * x_now / (sigma_x*sigma_x) + y_now * y_now / (sigma_y*sigma_y) - (x0 * x0 / (sigma_x*sigma_x) + y0 * y0 / (sigma_y*sigma_y))));

		//r>1ʱֱ��ѡ��ǰλ�õ�������
		if (r > 1) {
			x0 = x_now;
			y0 = y_now;
		}
		//r<=1ʱ�����³�ȡ[0,1]�ϵ����������С��r����ѡ��ǰλ�õ������У�����λ�ò���
		else
			if (double(rand() % RAND_MAX) / RAND_MAX < r) {
				x0 = x_now;
				y0 = y_now;
			}
	}

	sprintf(filename, "sx=%.1lf,sy=%.1lf,step=%.1lf.txt", sigma_x, sigma_y, step);
	//sprintf(filename, "error.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < N - M; i++) {
			//��������¸�λ�õ�����
			x_now = x0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
			y_now = y0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
			r = exp(-0.5*(x_now * x_now / (sigma_x*sigma_x) + y_now * y_now / (sigma_y*sigma_y) - (x0 * x0 / (sigma_x*sigma_x) + y0 * y0 / (sigma_y*sigma_y))));

			//r>1ʱֱ��ѡ��ǰλ�õ�������
			if (r > 1) {
				x0 = x_now;
				y0 = y_now;
			}
			//r<=1ʱ�����³�ȡ[0,1]�ϵ����������С��r����ѡ��ǰλ�õ������У�����λ�ò���
			else
				if (double(rand() % RAND_MAX) / RAND_MAX < r) {
					x0 = x_now;
					y0 = y_now;
				}
			//�����ǰ���굽�ļ���
			fprintf(file, "%.6lf,%.6lf\n", x0, y0);

			//����x^2,y^2,x^2+y^2
			sum_x2 += x0 * x0;
			sum_y2 += y0 * y0;
			sum_xy2 += x0 * x0 + y0 * y0;
			//fprintf(file, "%.6lf,%.6lf,%.6lf\n", sum_x2 / (i + 1) - sigma_x * sigma_x, sum_y2 / (i + 1) - sigma_y * sigma_y, sum_xy2 / (i + 1) - sigma_x * sigma_x - sigma_y * sigma_y);
		}
		//�������ľ�ֵ���ļ���
		fprintf(file, "%.6lf,%.6lf\n%.6lf,0", sum_x2 / (N - M), sum_y2 / (N - M), sum_xy2 / (N - M));
		
		//�ر��ļ�
		fclose(file);
	}
	printf("\n<x^2>=%.6lf\n<y^2>=%.6lf\n<x^2+y^2>=%.6lf\n", sum_x2 / (N - M), sum_y2 / (N - M), sum_xy2 / (N - M));
	system("pause");
}