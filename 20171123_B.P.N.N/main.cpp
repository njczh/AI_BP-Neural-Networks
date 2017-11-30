// 2017/11/23 Back Propagation Neural Network
// 4输入（4个特征）、10个隐含层、3个输出（分别对应某样本属于某一种分类的可能性）

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
	infile.open(file.data());			// 将文件流对象与文件连接起来
	assert(infile.is_open());			// 若打开失败，则输出错误消息，并终止程序运行
	data.clear();						// 将数据容器初始化
	string s;

	while (getline(infile, s))
	{
		int i = 0;
		string str_temp = "";			// 初始化string为空，不用加 ="" 也行
		Data temp;

		for (int j = 0; s[j] != '\0'; j++) {	// 分割每一行的数据
			if (s[j] != ' ') {					// 以空格作为分割符
				if (s[j + 1] == '\0')
					temp.label = s[j] - 48;		// 数据最后一个元素是标签
				else str_temp += s[j];
			}
			else {
				// 将string类型的数据转换成对应的double类型
				temp.in[i++] = (atof(str_temp.c_str()));
				str_temp.clear();
			}
		}
		data.push_back(temp);				// 将分割好的数据加入vector容器
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

	// 独立运行10次，计算每一次的预测准确率，并计算平均准确率
	printf("独立运行 %d 次，每次BP神经网络训练 %d 次。结果如下：\n", RUN_TIMES, TRAIN_TIMES);
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

		// BP神经网络训练
		for (int i = 0; i < TRAIN_TIMES; i++)
			my_bp.TrainGroup(train_data);

		// 利用训练好的BP神经网络处理测试数据，并计算预测准确率
		result[run_times] = my_bp.BpnnCalc(test_data);
		sum += result[run_times];
	}

	// 计算平均准确率及标准差；
	double avg = sum / RUN_TIMES;
	cout << "平均准确率为：" << avg << endl;

	sum = 0;
	for (int i = 0; i < RUN_TIMES; i++)
		if (avg != result[i])sum += pow((avg - result[i]), 2);

	cout << "标准差为：" << sqrt((sum / RUN_TIMES)) << endl;

	system("pause");

	return 0;
}
