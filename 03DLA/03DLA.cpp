#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GENERATE_PARTICLE_RANGE 400 //���������ӵı߽�
#define EDGE 500 //�������߽磬���ڴ˱߽��ʱ�����²�������
#define PICTURE_RANGE 800 //ͼƬ��С
#define INCREAMENT 50
#define COEFFICIENT_BOXCOUNT 15
#define COEFFICIENT_SANDBOX 9

int middle = PICTURE_RANGE / 2; //ͼƬ������
static unsigned char particles[PICTURE_RANGE][PICTURE_RANGE] = { 0 }; //��ʾ���ӵĶ�ά���顣����Ԫ��Ϊ1��ʾ�ô������ӣ�Ϊ0��ʾ�ó�������



//������ߺ�����ֻ�����������ĸ�����������
void RandomWalk(int *x, int *y) {
	int walk = rand() % 4; //�������0��1��2��3�ĸ����е�һ�����ֱ�������ϡ��¡������ĸ�������

	//�������
	switch (walk) {
	case 0:
		(*y)++;
		break;
	case 1:
		(*y)--;
		break;
	case 2:
		(*x)--;
		break;
	case 3:
		(*x)++;
		break;
	}
}



//�ڲ������ӵ������α߽��ϵ����������������һ��������
void GenerateParticle(int *x, int *y,int generate_particle_range) {
	int side = rand() % 4; //�������0��1��2��3�ĸ����е�һ�����ֱ�����ϡ��¡�����������
	int coordinate = rand() % generate_particle_range; //��������������ϵ�һ�������

	//�������������
	switch (side) {
	case 0:
		*x = middle - generate_particle_range / 2 + coordinate;
		*y = middle + generate_particle_range / 2;
		break;
	case 1:
		*x = middle - generate_particle_range / 2 + coordinate;
		*y = middle - generate_particle_range / 2;
		break;
	case 2:
		*x = middle - generate_particle_range / 2;
		*y = middle - generate_particle_range / 2 + coordinate;
		break;
	case 3:
		*x = middle + generate_particle_range / 2;
		*y = middle - generate_particle_range / 2 + coordinate;
		break;
	}
}



//�ж��Ƿ���Ҫ���²���һ��������
//�����ӵ����곬��ͼƬ�߽���߾ۼ����Ѿ����ɵ��Ŵ��ϣ�����Ҫ���ֲ���һ�������ӣ���������Ҫ����������
//������Ҫ����������ʱ����0�������Ӿۼ����Ѿ����ɵ��Ŵ���ʱ����1�������ӳ����߽�ʱ����2
int NeedNewParticle(int x, int y, unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int *num,int edge) {
	//�����ӳ����߽�ʱ����Ҫ���������ӣ�����2
	if (x<middle - edge / 2 || x>middle + edge / 2 || y<middle - edge / 2 || y>middle + edge / 2)
		return 2;
	//�����Ӿۼ����Ѿ����ɵ��Ŵ���ʱ���Ŵ��е�������+1����Ҫ���������ӣ�����1
	if (particles[x - 1][y] == 1 || particles[x + 1][y] == 1 || particles[x][y - 1] == 1 || particles[x][y + 1] == 1
		|| particles[x - 1][y - 1] == 1 || particles[x - 1][y + 1] == 1 || particles[x + 1][y - 1] == 1 || particles[x + 1][y + 1] == 1
		) {
		particles[x][y] = 1;
		(*num)++;
		return 1;
	}
	//Ŀǰ���������������������Ҫ�����ӣ�����0
	return 0;
}



//�м�����
int BoxCount(unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int r, int range) {
	int x, y, i, j, count = 0, flag = 0;
	for (x = middle - range / 2; x <= middle + range / 2; x += r) {
		for (y = middle - range / 2; y <= middle + range / 2; y += r) {
			for (i = x; i < x + r && x <= middle + range / 2; i++) {
				for (j = y; j < y + r && y <= middle + range / 2; j++) {
					if (particles[i][j] == 1) {
						flag = 1;
						count++;
						break;
					}
				}
				if (flag == 1)
					break;
			}
			if (flag == 1)
				flag = 0;
		}
	}
	return count;
}



//Sandbox��
int Sandbox(unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int r) {
	int x, y, count = 0;
	for (x = middle - r / 2; x <= middle + r / 2; x++) {
		for (y = middle - r / 2; y <= middle + r / 2; y++)
			if (particles[x][y] == 1)
				count++;
	}
	return count;
}



//������
int main() {
	//��������
	//����Ϊ�������ڵĺᡢ�����꣬�������������ǰ���������������ӵı߽緶Χ����������������룬���ӵ�״̬��ͼƬ�Ĵ�С
	int x_now, y_now, maxnum, num, generate_particle_range, edge, flag;

	//��ʼʱ��������һ�����ӣ���ʼ������Ϊ1
	particles[middle][middle] = 1;
	num = 1;
	//�趨��ʼֵ
	generate_particle_range = GENERATE_PARTICLE_RANGE;
	edge = EDGE;
	printf("�������ά��ʱ��������Դ������ѡ����ʵĲ���(�������ƺм�������Sandbox��ѡȡ�Ĵ�С��Χ)��\n\n");
	printf("�������Ŵص����������(����С��10000)��");
	scanf("%d", &maxnum);

	srand(time(NULL)); //�������������

	//���ļ�����ʧ���򱨴�
	FILE *p = fopen("data.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		//������ʼ��
		fprintf(p, "%d,%d\n", middle, middle);

		//��ǰ������С�������������ʱ�����С������������
		while (num < maxnum) {
			//�������������ж�������״̬
			GenerateParticle(&x_now, &y_now, generate_particle_range);
			flag = NeedNewParticle(x_now, y_now, particles, &num, edge);

			//������Ҫ����������ʱ���������һ�����ж��µ�λ�õ�����״̬��һֱѭ��ֱ����Ҫ����������
			while (flag == 0) {
				RandomWalk(&x_now, &y_now);
				flag = NeedNewParticle(x_now, y_now, particles, &num, edge);
			}

			//����Ҫ��������������Ϊ���Ӿۼ����Ŵ���ʱ���������ӵ�ǰ���굽�ļ���
			if (flag == 1) {
				fprintf(p, "%d,%d\n", x_now, y_now);
				
				//����Ŵر߽絽����������ӵı߽磬�򽫲��������ӵı߽����󡣵��߽糬��ͼƬ��Сʱ���˳�
				if (abs(x_now - middle) > generate_particle_range / 2 || abs(y_now - middle) > generate_particle_range / 2) {
					generate_particle_range += INCREAMENT;
					edge += INCREAMENT;
					if (edge > PICTURE_RANGE)
						break;
				}
				
			}
		}
		//����������ݺͳ�ʼ�㵽�ļ���
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //�ر��ļ�
	}

	int r;

	//���ļ�����ʧ���򱨴�
	p = fopen("Boxcount.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		for (r = 8; r <= PICTURE_RANGE / COEFFICIENT_BOXCOUNT; r += 4) {
			fprintf(p, "%d,%d\n", r, BoxCount(particles, r, generate_particle_range));
		}
		//����������ݺͳ�ʼ�㵽�ļ���
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //�ر��ļ�
	}

	//���ļ�����ʧ���򱨴�
	p = fopen("Sandbox.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		for (r = PICTURE_RANGE / 50; r <= generate_particle_range - COEFFICIENT_SANDBOX * INCREAMENT; r += PICTURE_RANGE / 50) {
			fprintf(p, "%d,%d\n", r, Sandbox(particles, r));
		}
		//����������ݺͳ�ʼ�㵽�ļ���
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //�ر��ļ�
	}
}