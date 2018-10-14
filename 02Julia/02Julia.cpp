#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SMALL_RADIUS 0.0000001


int CountEscape(double x, double y, double x_c, double y_c, double small_radius, double large_radius, int num) {
	//�ú����������㸴ƽ���ϵĵ�(x,y)��Ҫ���ٴε����Żᵽԭ�����С��small_radius�����large_radius
	//����δ����num�κ����С��small_radius���򷵻�0
	//������num�ξ��봦��(small_radius,large_radius)���򷵻�-2����num
	//����δ����num�ξ���ʹ���large_radius���򷵻ؾ������large_radiusʱ�ĵ�������
	//x,yΪ���ʵ�����鲿
	//x_c,y_cΪ����Julia��ʱC��ʵ�����鲿
	//small_radius,large_radiusΪ�趨����С����������룬��ΪС��small_radius�ͽ���ԭ�㣬����large_radius�ͽ�����
	//numΪ�趨������������
	int count = 0, i; //countΪ���ݴ���
	double x_now = x, y_now = y; //x_now��y_nowΪ����ʱ���ڵ�x��yֵ
	for (i = 0; i < num; i++) {
		//����x��y
		x = (x_now * x_now - y_now * y_now) + x_c;
		y = 2 * x_now*y_now + y_c;
		count++; //��������+1
		if ((x*x + y * y) < (small_radius*small_radius)) //����δ����num�κ����С��small_radius���򷵻�0
			return 0;
		if ((x*x + y * y) > (large_radius*large_radius)) //����δ����num�ξ���ʹ���large_radius���򷵻ؾ������large_radiusʱ�ĵ�������
			return count;
		x_now = x;
		y_now = y;
	}
	//return -2; //������num�ξ��봦��(small_radius,large_radius)���򷵻�-2
	return count; //������num�ξ��봦��(small_radius,large_radius)���򷵻�num
}



int main() {
	//��ر�������
	double range, step; //ʵ���鲿�ķ�Χ
	//double x_low, x_high, y_low, y_high;
	double x_now, y_now; //���ڵ�x��y
	double x_c, y_c, small_radius = SMALL_RADIUS, large_radius; //x_c,y_cΪC��ʵ�����鲿��small_radius��large_radiusΪ�ж��ľ���
	double error = 0.00001; //double�ͱ����ж���Ϊ��ʹ�߽��ܹ�ȡ��
	int count, num, i, j;

	/*
	printf("������x�ķ�Χ��");
	scanf("%lf", &x_low);
	printf("������x�����ޣ�");
	scanf("%lf", &x_high);
	printf("������y�����ޣ�");
	scanf("%lf", &y_low);
	printf("������y�����ޣ�");
	scanf("%lf", &y_high);
	*/

	//��������
	printf("�����뷶Χ���Ƽ�1.5����");
	scanf("%lf", &range);
	printf("�����벽�����Ƽ�0.01������̫С���������ݺܴ󣩣�");
	scanf("%lf", &step);
	printf("������C��ʵ����");
	scanf("%lf", &x_c);
	printf("������C���鲿��");
	scanf("%lf", &y_c);
	//printf("��������С�ж����룺");
	//scanf("%lf", &small_radius);
	printf("���������ݾ��룺");
	scanf("%lf", &large_radius);
	printf("������������������");
	scanf("%d", &num);
	printf("\n��������������!\n");

	//���ļ�
	FILE *p = fopen("data.txt", "w");
	if(!p)
		printf("Open failed\n"); //��ʧ���򷵻�
	
	else {
		//��ӡ�������ļ���
		fprintf(p, "%lf %lf %d\n", range, step, num);
		fprintf(p, "%lf %lf %lf\n", x_c, y_c, large_radius);

		//���������������еĵ㣬�����������͵����������뵽�ļ���
		for (x_now = -range, i = 0; x_now - error < range; x_now = -range + i * step) {
			for (y_now = -range, j = 0; y_now - error < range; y_now = -range + j * step) {
				count = CountEscape(x_now, y_now, x_c, y_c, small_radius, large_radius, num);
				fprintf(p, "%lf %lf %d\n", x_now, y_now, count);
				j++;
			}
			i++;
		}

		printf("\n��������������ϣ������Ѿ����뵽data.dat��!\n");
	}

	fclose(p); //�ر��ļ�
}