#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807�����������������������
#define COEFFICIENT 0.0 //�糡Ӱ������
#define OMEGA 0.0 //�糡���е�omega

int a = 16807, m = 2147483647, r = m % a, q = m / a; //��ز�������
double x[NUM_16807]; //�������������
int randomwalk[5][1000]; //����������ʾ������ߵ���������


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



//������糡������ĸ���
double p_right(int n, double coefficient, double omega) {
	return (double(1 + coefficient* sin(omega*n)) / 2);
}



int main() {
	int i, j, x_now, num_particles, num_steps;
	double x_1, x_2, coefficient, omega;
	char filename[40] = {};
	FILE *file = NULL;

	//�����������
	printf("�������ܵ���������");
	scanf("%d", &num_particles);
	printf("������糡����Ӱ��Ч����");
	scanf("%lf", &coefficient);
	printf("������糡���е�omega��");
	scanf("%lf", &omega);

	srand(time(NULL)); //�������������


	
	//��ӡ�������ʾ��ͼ����ֻ��ʾ5������,ÿ����������100��
	sprintf(filename, "Random_Walk,c=%.1lf,omega=%.2lf.txt", coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//���ӽ����������
		for (i = 0; i < 5; i++) { //����num_particles������
			x_now = 0; //��ʼ������0
			RNG_16807(x, 1000, rand()); //��16807��������������������
			for (j = 0; j < 1000; j++) { //����������ߣ��������ҵĸ���ʱ������+1����������-1�������������Ϊϵͳ�Դ��Ĳ�����
				randomwalk[i][j] = x_now;
				if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
					x_now++;
				else
					x_now--;
			}
		}
		
		//��ӡ���ݵ��ļ���
		for (j = 0; j < 1000; j++)
			for (i = 0; i < 5; i++)  //��������
				//��ӡ�������ÿ�����ڵ����굽�ļ���
				if (i != 4)
					fprintf(file, "%d,", randomwalk[i][j]);
				else
					fprintf(file, "%d\n", randomwalk[i][j]);

		fclose(file);
	}
	

	
	//��ӡx��1�׾���2�׾����
	sprintf(filename, "particles=%d,c=%.1f,omega=%.2f.txt", num_particles, coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (num_steps = 10; num_steps <= 1000; num_steps += 10) { //���ò�ͬ�Ĳ���
			for (i = 0, x_1 = 0, x_2 = 0; i < num_particles; i++) { //����num_particles������
				x_now = 0; //��ʼ������0

				/*
				RNG_16807(x, num_steps, rand()); //��16807��������������������
				
				for (j = 0; j < num_steps; j++) //����������ߣ��������ҵĸ���ʱ������+1����������-1�������������Ϊ16807
					if (x[j] <= p_right(j, coefficient, omega))
						x_now++;
					else
						x_now--;
				*/

				for (j = 0; j < num_steps; j++) //����������ߣ��������ҵĸ���ʱ������+1����������-1�������������Ϊϵͳ�Դ��Ĳ�����
					if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
						x_now++;
					else
						x_now--;
				
				x_1 += double(x_now); //��x��1�η��ۼ�
				x_2 += double(x_now) * double(x_now); //��x�Ķ��η��ۼ�
			}
			fprintf(file, "%d,%.5f,%.5f\n", num_steps, x_1 / num_particles, x_2 / num_particles); //��ӡ������x��1�׾��x��2�׾ൽ�ļ���
		}
		fclose(file);
	}
	



	//��֤�ֲ�Ϊ��̬�ֲ�����
	sprintf(filename, "end_x,c=%.1lf,omega=%.2lf.txt", coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//���ӽ����������
		for (i = 0; i < num_particles; i++) { //����num_particles������
			x_now = 0; //��ʼ������0
			RNG_16807(x, 1000, rand()); //��16807��������������������
			for (j = 0; j < 1000; j++) { //����������ߣ��������ҵĸ���ʱ������+1����������-1�������������Ϊϵͳ�Դ��Ĳ�����
				if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
					x_now++;
				else
					x_now--;
			}
			fprintf(file, "%d\n", x_now);
		}
		fclose(file);
	}
}