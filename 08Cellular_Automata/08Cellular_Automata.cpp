
//0�����������ϣ�1������������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define LENGTH 512
#define RATIO 0.12

char Spins[LENGTH][LENGTH] = { 0 }; //��������״̬�Ķ�ά����
int a = 16807, m = 2147483647, r = m % a, q = m / a; //16807�������������ز�������


//�����ʼ������
void InitSpins(char Spins[LENGTH][LENGTH], int start, double ratio) {
	int x, y;
	double now = double(start) / m;

	//���������ʼ������
	for (x = 0; x < LENGTH; x++)
		for (y = 0; y < LENGTH; y++) {
			//�������С��RATIO���������ϣ�������������
			if (now < ratio)
				Spins[x][y] = 0;
			else
				Spins[x][y] = 1;

			//16807������������������������ɵ������������x�����������num����ʼ��start����16807����������������������������һά������
			start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
			now = double(start) / m;
		}
}



//�ж�(x,y)�������Ƿ�Ҫ��ת�����Ҫ��ת���򷵻�1�����򷵻�0���߽�����Ϊ��������
int WhetherFlip(char Spins[LENGTH][LENGTH], int x, int y) {
	int a = y + 1, b = y - 1, c = x - 1, d = x + 1; //�����ϡ��¡������ĸ�λ�õ�����
	int count0 = 0, count1 = 0; //�����ھ���Ϊ0�ĸ�����Ϊ1�ĸ���

	//�����ڱ߽����������ϡ��¡����ҵ�����
	if (y == 511)
		a = 0;
	if (y == 0)
		b = 511;
	if (x == 0)
		c = 511;
	if (x == 511)
		d = 0;

	//�����ھ���Ϊ0�ĸ�����Ϊ1�ĸ���
	count0 = 4 - Spins[x][a] - Spins[x][b] - Spins[c][y] - Spins[d][y];
	count1 = 4 - count0;

	//���ھ���Ϊ0�ĸ�������Ϊ1�ĸ����������������ת������1�����򷵻�0
	if (count0 == count1)
		return 1;
	else
		return 0;
}



/*
//�ж�(x,y)�������Ƿ�Ҫ��ת�����Ҫ��ת���򷵻�1�����򷵻�0���߽�����Ϊ��ֵ����
int WhetherFlip(char Spins[LENGTH][LENGTH], int x, int y) {
	int a = y + 1, b = y - 1, c = x - 1, d = x + 1; //�����ϡ��¡������ĸ�λ�õ�����
	int count0 = 0, count1 = 0; //�����ھ���Ϊ0�ĸ�����Ϊ1�ĸ���

	//�ö�ֵ�߽����������ϡ��¡����ҵ�����
	if (y == 511)
		a = 0;
	else
		a = Spins[x][y + 1];
	if (y == 0)
		b = 0;
	else
		b = Spins[x][y - 1];
	if (x == 0)
		c = 0;
	else
		c = Spins[x - 1][y];
	if (x == 511)
		d = 0;
	else
		d = Spins[x + 1][y];

	//�����ھ���Ϊ0�ĸ�����Ϊ1�ĸ���
	count0 = 4 - a - b - c - d;
	count1 = 4 - count0;

	//���ھ���Ϊ0�ĸ�������Ϊ1�ĸ����������������ת������1�����򷵻�0
	if (count0 == count1)
		return 1;
	else
		return 0;
}
*/



//������Q2�������һ��������ת
void Flip(char Spins[LENGTH][LENGTH]) {
	int x, y, flag;

	//��ż���Ӹ���з�ת
	flag = 0;
	for (x = 0; x < LENGTH; x++) {
		for (y = flag; y < LENGTH; y += 2)
			if (WhetherFlip(Spins, x, y) == 1)
				Spins[x][y] = 1 - Spins[x][y];
		flag = 1 - flag;
	}

	//���������Ӹ���з�ת
	flag = 1;
	for (x = 0; x < LENGTH; x++) {
		for (y = flag; y < LENGTH; y += 2)
			if (WhetherFlip(Spins, x, y) == 1)
				Spins[x][y] = 1 - Spins[x][y];
		flag = 1 - flag;
	}
}



//ͳ���������ϵ�������ռ�ı���
double Calculate(char Spins[LENGTH][LENGTH]) {
	int x, y, count = 0;

	//�����������������������һ
	for (x = 0; x < LENGTH; x++)
		for (y = 0; y < LENGTH; y++)
			if (Spins[x][y] == 0)
				count++;
	return (double(count) / (512 * 512));
}



int main() {
	int num, i, x, y;
	double ratio = RATIO;
	FILE *file = NULL;
	char filename[20] = {};

	//��ʱ��������
	clock_t start, finish;
	double totaltime;
	start = clock();

	//���������ֵ
	printf("��������ʼ����������ռ������");
	scanf("%lf", &ratio);
	printf("��������������");
	scanf("%d", &num);

	srand(time(NULL)); //�����������
	InitSpins(Spins, rand(), ratio); //��ʼ������

	//������ݵ��ļ���
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		//��ӡ�������ʼ״̬������
		ratio = Calculate(Spins);
		printf("   %.10f\n", ratio);
		for (x = 0; x < LENGTH; x++)
			for (y = 0; y < LENGTH; y++)
				if (y != LENGTH - 1)
					fprintf(file, "%d,", Spins[x][y]);
				else
					fprintf(file, "%d\n", Spins[x][y]);
		for (x = 0; x<LENGTH; x++)
			if (x != LENGTH - 1)
				fprintf(file, "%.10f,", ratio);
			else
				fprintf(file, "%d\n", ratio);

		//���з�ת
		for (i = 0; i < num; i++) {
			Flip(Spins);
			//ÿ�η�ת������ݶ���������Բ���Ҫ��
			/*
			for (x = 0; x < LENGTH; x++)
				for (y = 0; y < LENGTH; y++)
					if (y != LENGTH - 1)
						fprintf(file, "%d,", Spins[x][y]);
					else
						fprintf(file, "%d\n", Spins[x][y]);			
			*/
			ratio = Calculate(Spins);
			printf("   %.10f\n", ratio);
		}

		//��ӡ�������ֹ״̬
		for (x = 0; x < LENGTH; x++)
			for (y = 0; y < LENGTH; y++)
				if (y != LENGTH - 1)
					fprintf(file, "%d,", Spins[x][y]);
				else
					fprintf(file, "%d\n", Spins[x][y]);
		for(x=0;x<LENGTH;x++)
			if (x != LENGTH - 1)
				fprintf(file, "%.10f,", ratio);
			else
				fprintf(file, "%d\n", ratio);

		fclose(file);
	}
	/*
	for (i = 0; i < LENGTH; i++) {
		for (j = 0; j < LENGTH; j++)
			printf("%d", Spins[i][j]);
			printf("\n");
		}
	*/

	//��ӡ�ܺ�ʱ
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n   �ܹ���ʱ��%f  seconds\n\n", totaltime);

	system("pause");
}