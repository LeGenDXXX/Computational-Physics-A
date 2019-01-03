#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define MAX_NUM_PARTICLES 1000000
double m = 1;
double vs[MAX_NUM_PARTICLES] = { 0 };



int main() {
	int i, N=10000000, M=100000, num, n, steps, i_now;
	double xi, step, E_d = 0, v_now, H = 0, delta_H, sum1 = 0, sum2 = 0;
	char filename[20] = {};
	FILE *file = NULL;

	//�����������
	printf("�������ܵ���������");
	scanf("%d", &num);
	printf("�����벽����");
	scanf("%lf", &step);
	/*
	printf("������demon�ĳ�ʼ������");
	scanf("%lf", &E_d);
	*/
	srand(time(NULL)); //�������������

	//��ʼ���ٶ�����Ϊ1��ͬʱ��������
	for (i = 0; i < num; i++) {
		vs[i] = 0;
		H += m / 2 * (vs[i] * vs[i]);
	}
	
	//�Ȼ��׶�
	for (i = 0; i < M; i++) {
		i_now = rand() % num; //ѡȡ��i_now������
		v_now = vs[i_now] + (2 * double(rand()) / RAND_MAX - 1)*step; //��i_now�����ӵ��ٶȽ��иı�
		delta_H = m / 2 * (v_now*v_now - vs[i_now] * vs[i_now]); //ϵ�۵��������иı�

		if (delta_H < 0) { //ϵ��������������ܴ˴γ���
			vs[i_now] = v_now; //�ı��ٶ�
			H = H + delta_H; //�ı�����
			E_d = E_d - delta_H; //�ı�demon����
		}
		else
			if (E_d > delta_H) {
				vs[i_now] = v_now; //�ı��ٶ�
				H = H + delta_H; //�ı�����
				E_d = E_d - delta_H; //�ı�demon����
			}
	}

	//���дﵽƽ��̬�Ĺ��̣�ͬʱ��demon���������뵽�ļ���
	//sprintf(filename, "T.txt");
	sprintf(filename, "demon_energy.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//���дﵽƽ��̬�Ĺ���
		for (i = 0; i < N - M; i++) {
			i_now = rand() % num; //ѡȡ��i_now������
			v_now = vs[i_now] + (2 * double(rand()) / RAND_MAX - 1)*step; //��i_now�����ӵ��ٶȽ��иı�
			delta_H = m / 2 * (v_now*v_now - vs[i_now] * vs[i_now]); //ϵ�۵��������иı�

			if (delta_H < 0) { //ϵ��������������ܴ˴γ���
				vs[i_now] = v_now; //�ı��ٶ�
				H = H + delta_H; //�ı�����
				E_d = E_d - delta_H; //�ı�demon����
			}
			else
				if (E_d > delta_H) {
					vs[i_now] = v_now; //�ı��ٶ�
					H = H + delta_H; //�ı�����
					E_d = E_d - delta_H; //�ı�demon����
				}
			//fprintf(file, "%.6lf\n", 2 * H / num);
			fprintf(file, "%.6lf\n", E_d);
		}

		fclose(file);
	}

	//��ӡ�ٶ����ݵ��ļ���
	sprintf(filename, "vs.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < num; i++) {
			fprintf(file, "%.6lf\n", vs[i]);
			sum1 += vs[i];
			sum2 += vs[i] * vs[i];
		}
		fprintf(file, "%.6lf\n%.6lf\n%.6lf", sum1 / num, sum2 / num, sum2 / num - sum1 * sum1 / (num*num));
			
		fclose(file);
	}
}