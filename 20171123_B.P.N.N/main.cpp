// 2017/11/23 Back Propagation Neural Network
// 4���루4����������10�������㡢3��������ֱ��Ӧĳ��������ĳһ�ַ���Ŀ����ԣ�

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include "bp.h"
using namespace std;

#define RUN_TIMES 10
#define TRAIN_TIMES 750

void ReadTxt(string file, vector<Data> &data)
{
	ifstream infile;
	infile.open(file.data());			// ���ļ����������ļ���������
	assert(infile.is_open());			// ����ʧ�ܣ������������Ϣ������ֹ��������
	data.clear();						// ������������ʼ��
	string s;

	while (getline(infile, s))
	{
		int i = 0;
		string str_temp = "";			// ��ʼ��stringΪ�գ����ü� ="" Ҳ��
		Data temp;

		for (int j = 0; s[j] != '\0'; j++) {	// �ָ�ÿһ�е�����
			if (s[j] != ' ') {					// �Կո���Ϊ�ָ��
				if (s[j + 1] == '\0')
					temp.label = s[j] - 48;		// �������һ��Ԫ���Ǳ�ǩ
				else str_temp += s[j];
			}
			else {
				// ��string���͵�����ת���ɶ�Ӧ��double����
				temp.in[i++] = (atof(str_temp.c_str()));
				str_temp.clear();
			}
		}
		data.push_back(temp);				// ���ָ�õ����ݼ���vector����
	}
}

int main()
{
	vector<Data> train_data;
	vector<Data> test_data;
	ReadTxt("Iris-train.txt", train_data);
	ReadTxt("Iris-test.txt", test_data);

	double sum = 0;
	double result[RUN_TIMES];

	// ��������10�Σ�����ÿһ�ε�Ԥ��׼ȷ�ʣ�������ƽ��׼ȷ��
	printf("�������� %d �Σ�ÿ��BP������ѵ�� %d �Ρ�������£�\n", RUN_TIMES, TRAIN_TIMES);
	for (int run_times = 0; run_times < RUN_TIMES; run_times++)
	{
		switch (run_times)
		{
		case 0:printf("This is %2dst times run, ", run_times + 1); break;
		case 1:printf("This is %2drd times run, ", run_times + 1); break;
		default:
			printf("This is %2dth times run, ", run_times + 1); break;
		}

		Bp my_bp;

		// BP������ѵ��
		for (int i = 0; i < TRAIN_TIMES; i++)
			my_bp.TrainGroup(train_data);

		// ����ѵ���õ�BP�����紦��������ݣ�������Ԥ��׼ȷ��
		result[run_times] = my_bp.BpnnCalc(test_data);
		sum += result[run_times];
	}

	// ����ƽ��׼ȷ�ʼ���׼�
	double avg = sum / RUN_TIMES;
	cout << "ƽ��׼ȷ��Ϊ��" << avg << endl;

	sum = 0;
	for (int i = 0; i < RUN_TIMES; i++)
		if (avg != result[i])sum += pow((avg - result[i]), 2);

	cout << "��׼��Ϊ��" << sqrt((sum / RUN_TIMES)) << endl;

	system("pause");

	return 0;
}
