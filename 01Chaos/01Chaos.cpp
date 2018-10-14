#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// һ����ֵ�趨��
#define X0 0.5 //x�ĳ�ֵ
#define LAMBDA0 0.6 //lambda��ʼֵ
#define LAMBDA_LIMIT 0.9 //lambda��ֵ
#define STEP 0.00001 //lambda����ֵ
#define N 100000 //����lambda�����鳤�ȣ�Ҫ���� lambdaȡֵ��Χ / step
#define ITERATION 10000 //��ʼ�ĺ�����������
#define NUM 100 //ITERATION�κ��ʼ�ĵ�������
#define ERROR 0.00001 //����double�������ݴ�С���
#define PI 3.1415926 //PI��ֵ
#define FUNCTION(x,lambda) ( (lambda)*sin(PI*(x)) ) //��Ҫ�����ĺ���

//������Ϊsq���Ա����ͣ���������x��ֵ
typedef struct sq {
	double x;
	sq *next = NULL;
} sq;

//�����ĺ���
double function(double x, double lambda) {
	return (FUNCTION(x, lambda));
}





// ����������
int main() {
	//��ر�������
	double x = X0;
	double lambda = LAMBDA0;
	double lambda_limit = LAMBDA_LIMIT;
	double step = STEP;
	double lambda_now; //lambda_now��������ѭ���е�ǰ��lambdaֵ
	int iteration = ITERATION;
	int num = NUM;
	double error = ERROR;
	//value[i]Ϊһ��sq�������ͷָ��
	//���Ա������ݱ���lambda = LAMBDA0 + i*STEP����ITERATION�κ��ٵ���NUM�ε�NUM��xֵ
	sq* value[N] = { NULL };
	//unique_lambda[i]Ϊһ��sq�������ͷָ��
	//���Ա������ݱ���lambda = LAMBDA0 + i*STEP��Ψһ��xֵ����value[i]�в��ظ���xֵ
	sq* unique_lambda[N] = { NULL };
	//Feigenbaum�������汶���ڷֲ�ʱ��lambda
	double Feigenbaum[10] = { 0 };
	sq *end = NULL, *q = NULL;
	int i, j, count, flag = 1;

	//�ֶ���������
	//�������ʡ�ԣ���ͨ�������ڲ���defineֱ������
	printf("������lambda��ʼֵ���Ƽ�%lf����",lambda);
	scanf("%lf", &lambda);
	printf("������lambda��ֵֹ���Ƽ�%lf����",lambda_limit);
	scanf("%lf", &lambda_limit);
	printf("�����벽�����Ƽ�%lf����",step);
	scanf("%lf", &step);
	printf("������ÿ��lambdaֵ���ӵ�е�xֵ�����Ƽ�%d����",num);
	scanf("%d", &num);
	printf("\n�������������У�\n");

	//��1��forѭ��������������value
	for (i = 0, lambda_now = lambda; lambda_now < lambda_limit; lambda_now = lambda + i * step, i++) {
		x = X0;

		//��ʼ����ITERATION��
		for (j = 0; j < iteration; j++)
			x = function(x, lambda_now);
		//value[i]Ϊ��ʱ������ͷָ��
		x = function(x, lambda_now);
		value[i] = (sq*)malloc(sizeof(sq));
		value[i]->x = x;
		value[i]->next = NULL;
		end = value[i];
		//��������(NUM-1)�Σ������õ���x���ӳ�value[i]������
		for (j = 0; j < num - 1; j++) {
			x = function(x, lambda_now);
			//value[i]��Ϊ��ʱ��������β������x
			end->next = (sq*)malloc(sizeof(sq));
			end->next->x = x;
			end->next->next = NULL;
			end = end->next;
		}
	}



	//��2�����ļ�data.dat�������õ���(lambda,x)��ӡ��data.dat��
	FILE *p = fopen("data.dat", "w");
	//����Ƿ�ɹ���  
	if (p == NULL)
		printf("Open failed\n");

	else {
		//����value[i]������(lambda_now,x)��ӡ��data.dat��
		for (i = 0; value[i] != NULL; i++) {
			lambda_now = lambda + step * i;
			//��ӡ(lambda_now,x)
			for (end = value[i]; end != NULL; end = end->next) {
				fprintf(p, "%lf,", lambda_now);
				fprintf(p, "%lf\n", end->x);
			}
		}
	}

	//�ͷ�ָ��
	fclose(p);



	//��3��forѭ��������������unique_lambda
	for (i = 0, lambda_now = lambda; lambda_now < lambda_limit; lambda_now = lambda + i * step, i++) {
		//��value[i]��һ��ֵ���뵽unique_lambda[i]��
		end = value[i];
		q = (sq*)malloc(sizeof(sq));
		q->x = end->x;
		q->next = NULL;
		unique_lambda[i] = q;
		//����value
		for (end = end->next; end != NULL; end = end->next) {
			//��value��xֵ���һ��������ERRORʱ����x���뵽unique_lambda[i]β��
			if (fabs(end->x - value[i]->x) > error) {
				q->next = (sq*)malloc(sizeof(sq));
				q->next->x = end->x;
				q->next->next = NULL;
				q = q->next;
			}
			//��value��xֵ���һ�����С��ERRORʱ������ѭ��
			else
				break;
		}
	}



	/*
	��������ʡ�ԣ�������Ŀ����Ϊ�˼������
	//��4�����ļ�unique value.txt�������õ���(lambda,x1,x2,x3,...)��ӡ��unique value.txt��
	p = fopen("unique value.txt", "w");
	//����Ƿ�ɹ���
	if (p == NULL)
		printf("Open failed\n");

	else {
		//����unique_lambda[i]������(lambda,x1,x2,x3,...)��ӡ��unique value.txt��
		for (i = 0; unique_lambda[i] != NULL; i++) {
			lambda_now = lambda + step * i;
			//��ӡlambda
			fprintf(p, "%lf", lambda_now);
			//��ӡx
			for (end = unique_lambda[i]; end != NULL; end = end->next)
				fprintf(p, ",%lf", end->x);
			fprintf(p, "\n"); //ÿ�н�������  
		}
	}

	fclose(p);//�ͷ�ָ��
	*/


	//��5�����ļ�Feigenbaum.txt�������õ���(lambda,count)��ӡ��Feigenbaum.txt�У�count�ǲ�ͬ��xֵ�ĸ���
	p = fopen("Feigenbaum.txt", "w");
	//����Ƿ�ɹ���  
	if (p == NULL)
		printf("Open failed\n");
	
	else {
		//����unique_lambda[i]������(lambda,count)��ӡ��Feigenbaum.txt��
		for (i = 0, j = 0; unique_lambda[i] != NULL; i++) {
			lambda_now = lambda + i * step;
			count = 1;
			//��unique_lambda[i]��Ԫ�ظ���
			for (end = unique_lambda[i]->next; end != NULL; end = end->next)
				count++;
			//�������µı����ڵ�ʱ����(lambda,count)��ӡ��Feigenbaum.txt��
			if (count != flag) {
				fprintf(p, "%lf,", lambda_now);
				fprintf(p, "%d\n", count);
				flag = count;
				//����lambda��Feigenbaum��
				Feigenbaum[j] = lambda_now;
				j++;
			}
			if (j >= 7)
				break;
		}
	}

	//�ͷ�ָ�� 
	fclose(p);



	//��6����ӡFeigenbaum����
	printf("\nFeigenbaum�������㣺\nlambda\t\t�����ڷֲ�\tFeigenbaum����\n\n");
	printf("%lf\t1->2\n\n", Feigenbaum[0]);
	for (i = 1; i < 6; i++) {
		printf("%lf\t%d->%d\t\t%lf\n\n", Feigenbaum[i], int(pow(2, i)), int(pow(2, i + 1)), (Feigenbaum[i] - Feigenbaum[i - 1]) / (Feigenbaum[i + 1] - Feigenbaum[i]));
	}



	printf("\n����������ϣ�����������ļ��У�\n\n�����������");
	getchar();
	getchar();
}