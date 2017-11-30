// 2017/11/23 Back Propagation Neural Network
// 4���루4����������10�������㡢3��������ֱ��Ӧĳ��������ĳһ�ַ���Ŀ����ԣ�

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include "bp.h"
using namespace std;

vector<Data> my_data;

void ReadTxt(string file)
{
	ifstream infile;
	infile.open(file.data());			// ���ļ����������ļ���������
	assert(infile.is_open());			// ����ʧ�ܣ������������Ϣ������ֹ��������
	my_data.clear();					// ������������ʼ��
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
		my_data.push_back(temp);				// ���ָ�õ����ݼ���vector����
	}
}


int main()
{
	// ��ѵ������
	ReadTxt("Iris-train.txt");

	// Ҫ���������10�Σ�����ÿһ�ε�Ԥ��׼ȷ�ʣ�������ƽ��׼ȷ��
	for (int run_times = 0; run_times < 10; run_times++)
	{
		Bp my_bp;

		// BP������ѵ��
		for (int i = 0; i < 1000; i++) my_bp.TrainGroup(my_data);

		// ����ѵ���õ�BP�����紦��������ݣ�������Ԥ��׼ȷ��
		ReadTxt("Iris-test.txt");

		my_bp.BpnnCalc(my_data);
	}

	system("pause");

	return 0;
}
