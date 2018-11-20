#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807�����������������������
#define N 114 //�ܵĵ���

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double xs[NUM_16807], ys[NUM_16807]; //�������������
int energy[N], count[N]; //���������ȡ������
double p[N]; //������ȡ�������




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
	FILE *file = NULL;
	int i, j, num, sum, ra_count, xi;
	char filename[20] = {};

	//���������ĸ���
	printf("�����������ĸ�����");
	scanf("%d", &num);
	

	srand(time(NULL)); //�����������

	//��16807����������������������
	RNG_16807(xs, num, rand());
	RNG_16807(ys, num, rand());

	//��ȡdata.TXT�е����ݣ����ұ������ݵ�energy��count������
	file = fopen("data.TXT", "r");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0, sum = 0; i < N; i++) {
			fscanf(file, "%d", &energy[i]); //�����Ӧ��������������
			fscanf(file, "%d", &count[i]); //����������µļ�����������
			sum += count[i]; //�����ܼ���
		}
		fclose(file);
	}
	


	//ֱ�ӳ�����

	//�����ۼƺ�����ֵ������p��
	for (i = 0; i < N; i++)
		if (i != 0)
			p[i] = p[i - 1] + double(count[i]) / sum;
		else
			p[i] = double(count[i]) / sum;

	//����ֱ�ӳ����õ����������ļ���
	sprintf(filename, "direct_num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < num; i++) //ѭ�������
			for (j = 0; j < N; j++) //ѭ����ɢ�ֲ�
				if (xs[i] <= p[j]) { //�������С��i�����ۼƺ���ʱ�����õ��������浽�ļ��У��ҽ�����һ��������ѭ��
					fprintf(file, "%d\n", energy[j]);
					break;
				}
		fclose(file);
	}
	


	//��ѡ������

	//������ѡ���õ����������ļ���
	sprintf(filename, "ra_num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0, ra_count = 0; i < num; i++) {//ѭ�������
			if (xs[i] <= 141.0 / 341) {
				xi = energy[int(xs[i] * 682 / 3)];
				if (0.015*ys[i] <= double(count[xi - 2900]) / sum) {
					fprintf(file, "%d\n", xi);
					ra_count++;
				}
			}
			else {
				xi = energy[94 + int((xs[i] - 141.0 / 341) * 341 / 10)];
				if (0.100*ys[i] <= double(count[xi - 2900]) / sum) {
					fprintf(file, "%d\n", xi);
					ra_count++;
				}
			}
		}
		fprintf(file, "%f", double(ra_count) / num);
		fclose(file);
	}
}