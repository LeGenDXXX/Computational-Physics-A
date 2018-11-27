#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

double lengths[4] = { 1,4,25,50 }; //����������γ���
double widths[4] = { 1,1,25,1 }; //����������ο��



int main() {
	int i, j, k, n, num_steps, num_particles;
	double length, width, step, x_now, y_now, theta_now, rn, r_2, Ct;
	char filename[50];
	FILE *file = NULL;
	
	printf("��������γ���");
	scanf("%lf", &length);
	printf("��������ο�");
	scanf("%lf", &width);
	printf("������һ�εĲ������ȣ�");
	scanf("%lf", &step);
	printf("����������������");
	scanf("%d", &num_particles);
	printf("������������ߴ�����");
	scanf("%d", &num_steps);
	
	srand(time(NULL));



	//��ʾ�������ʾ��ͼ
	sprintf(filename, "RW,length=%.1lf,width=%.1lf,num=%d.txt", length, width, num_steps); //�ļ���
	file = fopen(filename, "w"); //���ļ�
	if (!file)
		printf("Can��t Open File!\n"); //��ʧ����ʾ
	else {
		x_now = 0, y_now = 0, theta_now = 0; //��ʼ��
		fprintf(file, "%d,%.10lf, %.10lf, %.10lf\n", 0, x_now, y_now, theta_now); //����ʼ�������뵽�ļ���
		for (i = 0; i < num_steps; i++) {
			rn = double(rand()) / RAND_MAX; //rnΪ�ж������������������

			//�������������������ʼ״̬���εı�����x��y�ᣬ��������������ֱ����¡��ϡ����������ߵ��������
			//ÿ��������ߵ�����ͽǶȱ仯�ľ�������ڱ�����
			if (rn < length / (2 * (length + width))) {
				x_now -= step / sqrt(length)*sin(theta_now);
				y_now += step / sqrt(length)*cos(theta_now);
				theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
			}
			else if (rn < length / (length + width)) {
				x_now += step / sqrt(length)*sin(theta_now);
				y_now -= step / sqrt(length)*cos(theta_now);
				theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
			}
			else if (rn < (length + 0.5*width) / (length + width)) {
				x_now += step / sqrt(width)*cos(theta_now);
				y_now += step / sqrt(width)*sin(theta_now);
				theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
			}
			else {
				x_now -= step / sqrt(width)*cos(theta_now);
				y_now -= step / sqrt(width)*sin(theta_now);
				theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
			}
			fprintf(file, "%d,%.10lf, %.10lf, %.10lf\n", i, x_now, y_now, theta_now); //���ÿ��������ߺ������ͽǶȵ��ļ���
		}
		fclose(file); //�ر��ļ�
	}
	

	
	//����2�׾������غ���
	sprintf(filename, "RC.txt"); //�ļ���
	file = fopen(filename, "w"); //���ļ�
	if (!file)
		printf("Can��t Open File!\n"); //��ʧ����ʾ
	else {
		for (n = 0; n < 4; n++) { //���ò�ͬ�ľ��γ��ȺͿ��
			length = lengths[n];
			width = widths[n];
			for (i = 1; i <= 100; i ++) {//��������
				for (j = 0, r_2 = 0, Ct = 0; j < num_particles; j++) { //������ͬ������
					for (k = 0, x_now = 0, y_now = 0, theta_now = 0; k < i; k++) { //ÿ�����ӵ��������
						rn = double(rand()) / RAND_MAX; //rnΪ�ж������������������

						//�������������������ʼ״̬���εı�����x��y�ᣬ��������������ֱ����¡��ϡ����������ߵ��������
						//ÿ��������ߵ�����ͽǶȱ仯�ľ�������ڱ�����
						if (rn < length / (2 * (length + width))) {
							x_now -= step / sqrt(length)*sin(theta_now);
							y_now += step / sqrt(length)*cos(theta_now);
							theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
						}
						else if (rn < length / (length + width)) {
							x_now += step / sqrt(length)*sin(theta_now);
							y_now -= step / sqrt(length)*cos(theta_now);
							theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
						}
						else if (rn < (length + 0.5*width) / (length + width)) {
							x_now += step / sqrt(width)*cos(theta_now);
							y_now += step / sqrt(width)*sin(theta_now);
							theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
						}
						else {
							x_now -= step / sqrt(width)*cos(theta_now);
							y_now -= step / sqrt(width)*sin(theta_now);
							theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
						}
					}
					r_2 += x_now * x_now + y_now * y_now; //����ԭ������ƽ�����
					Ct += cos(theta_now); //��������غ����е��ۼӲ���
				}
				fprintf(file, "%d,%.10lf,%.10lf\n", i, r_2 / num_particles, Ct/num_particles); //���ÿ����2�׾������غ���
			}
		}
		
		fclose(file); //�ر��ļ�
	}
}