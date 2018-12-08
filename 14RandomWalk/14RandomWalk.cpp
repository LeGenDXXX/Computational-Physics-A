#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



int main() {
	int i, j, k, num_particles, num_steps, x_now, y_now, z_now, count, randomnumber;
	char filename[20] = {};
	FILE *file = NULL;

	//�����������
	printf("�������ܵ���������");
	scanf("%d", &num_particles);
	printf("�������ܵĲ�����");
	scanf("%d", &num_steps);

	srand(time(NULL)); //�������������

	sprintf(filename, "data.txt"); //��ӡ�ļ���
	file = fopen(filename, "w"); //���ļ�
	if (!file)
		printf("Can't Open File!\n"); //��ʧ����ʾ
	else {
		printf("Steps\t\td = 1\t\td = 2\t\td = 3\n"); //��ӡ

		for (i = 2; i <= num_steps; i+=2) { //ѭ����������Ϊ�����εĲ�������Ϊ0�����ֻ��ż���ε�
			printf("%d\t\t", i);
			fprintf(file, "%d,", i);
			

			//��d=1ʱ�ĸ��ʵĴ���
			for (j = 0, count = 0; j < num_particles; j++) { //ѭ�����Ӹ���
				for (k = 1, x_now = 0; k <= i; k++) { //ÿ������������ߣ�������߹������£������ڱ�����д��
					randomnumber = rand() % 2;
					if (randomnumber == 0)
						x_now--;
					else
						x_now++;
				}
				if (x_now == 0) //�ص�ԭ��ʱ������һ
					count++;
			}
			//��ӡ���ݵ������к��ļ���
			printf("%.5lf\t\t", double(count) / num_particles);
			fprintf(file, "%.10lf,", double(count) / num_particles);


			//��d=2ʱ�ĸ��ʵĴ���
			for (j = 0, count = 0; j < num_particles; j++) { //ѭ�����Ӹ���
				for (k = 1, x_now = 0, y_now = 0; k <= i; k++) { //ÿ������������ߣ�������߹������£������ڱ�����д��
					randomnumber = rand() % 4;
					if (randomnumber == 0)
						x_now--;
					else if (randomnumber == 1)
						x_now++;
					else if (randomnumber == 2)
						y_now--;
					else
						y_now++;
				}
				if (x_now == 0 && y_now == 0) //�ص�ԭ��ʱ������һ
					count++;
			}
			//��ӡ���ݵ������к��ļ���
			printf("%.5lf\t\t", double(count) / num_particles);
			fprintf(file, "%.10lf,", double(count) / num_particles);


			//��d=3ʱ�ĸ��ʵĴ���
			for (j = 0, count=0; j < num_particles; j++) { //ѭ�����Ӹ���
				for (k = 1, x_now = 0, y_now = 0, z_now = 0; k <= i; k++) { //ÿ������������ߣ�������߹������£������ڱ�����д��
					randomnumber = rand() % 6;
					if (randomnumber == 0)
						x_now--;
					else if (randomnumber == 1)
						x_now++;
					else if (randomnumber == 2)
						y_now--;
					else if (randomnumber == 3)
						y_now++;
					else if (randomnumber == 4)
						z_now--;
					else
						z_now++;
				}	
				if (x_now == 0 && y_now == 0 && z_now == 0) //�ص�ԭ��ʱ������һ
					count++;
			}
			//��ӡ���ݵ������к��ļ���
			printf("%.5lf\n", double(count) / num_particles);
			fprintf(file, "%.10lf\n", double(count) / num_particles);
		}

		fclose(file); //�ر��ļ�
	}
	system("pause");
}