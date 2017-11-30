// 2017/11/23 Back Propagation Neural Network
// 4输入（4个特征）、10个隐含层、3个输出（分别对应某样本属于某一种分类的可能性）

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
	infile.open(file.data());			// 将文件流对象与文件连接起来
	assert(infile.is_open());			// 若打开失败，则输出错误消息，并终止程序运行
	my_data.clear();					// 将数据容器初始化
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
		my_data.push_back(temp);				// 将分割好的数据加入vector容器
	}
}


int main()
{
	// 读训练数据
	ReadTxt("Iris-train.txt");

	// 要求独立运行10次，计算每一次的预测准确率，并计算平均准确率
	for (int run_times = 0; run_times < 10; run_times++)
	{
		Bp my_bp;

		// BP神经网络训练
		for (int i = 0; i < 1000; i++) my_bp.TrainGroup(my_data);

		// 利用训练好的BP神经网络处理测试数据，并计算预测准确率
		ReadTxt("Iris-test.txt");

		my_bp.BpnnCalc(my_data);
	}

	system("pause");

	return 0;
}
