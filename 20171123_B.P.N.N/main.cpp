// 2017/11/23 Back Propagation Neural Network
// 4输入（4个特征）、10个隐含层、3个输出（分别对应某样本属于某一种分类的可能性）

#include <iostream>
using namespace std;

int main()
{
	// 读训练数据
	// ReadData(string file_name);
	/// to do ... 

	// 要求独立运行10次，计算每一次的预测准确率，并计算平均准确率
	for (int run_times = 0; run_times < 10; run_times++)
	{
		// BP神经网络训练
		// BpnnTrain(trainData);
		/// to do ... 
			

		// 利用训练好的BP神经网络处理测试数据，并计算预测准确率
		// BpnnCalculate(testData);
		/// to do ...
	}
	// 计算平均预测准确率
	// CalPrecision();
	/// to do ...

	return 0;
}
