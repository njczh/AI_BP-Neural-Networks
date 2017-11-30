#include "bp.h"

using namespace std;

inline double GetRandom()
{
	return (((2.0*(double)rand() / RAND_MAX) - 1));
}

inline double sigmoid(double x)
{
	return (1 / (1 + exp(-x)));
}

// ------ BP神经网络构造函数 ------
Bp::Bp()
{
	srand((unsigned)time(NULL));		// 随机数种子

	// 初始化输入层
	for (int i = 0; i < IN_NODE; i++)
		for (int j = 0; j < HIDE_NODE; j++)
			input_layer[i].weight.push_back(GetRandom());

	// 初始化隐含层(先考虑只有一层中间层)
	for (int i = 0; i < HIDE_NODE; i++)
	{
		hidden_layer[i].bias = GetRandom();

		for (int j = 0; j < OUT_NODE; j++)
			hidden_layer[i].weight.push_back(GetRandom());
	}

	for (int i = 0; i < OUT_NODE; i++)
		output_layer[i].bias = GetRandom();
}

void Bp::ForwardPropagationEpoc()
{
	// forward propagation on hidden layer
	for (int i = 0; i < HIDE_NODE; i++)
	{
		double sum = 0;
		for (int j = 0; j < IN_NODE; j++)
			sum += input_layer[j].value * input_layer[j].weight[i];  // ∑WiXi, i > 0
		sum += hidden_layer[i].bias;								 // i = 0
		hidden_layer[i].value = sigmoid(sum);
	}

	// forward propagation on output layer
	for (int i = 0; i < OUT_NODE; i++)
	{
		double sum = 0;
		for (int j = 0; j < HIDE_NODE; j++)
			sum += hidden_layer[j].value * hidden_layer[j].weight[i];
		sum += output_layer[i].bias;
		output_layer[i].value = sigmoid(sum);
	}
}

void Bp::BackPropagationEpoc()
{
	// backward propagation on output layer
	for (int i = 0; i < OUT_NODE; i++) {
		// delta = yi(1-yi)(ti-yi)
		output_layer[i].delta = output_layer[i].value
			*(1 - output_layer[i].value)
			*(output_layer[i].rightout - output_layer[i].value);
	}

	// backward propagation on hidden layer
	for (int i = 0; i < HIDE_NODE; i++)
	{
		double sum = 0;
		hidden_layer[i].delta = hidden_layer[i].value * (1 - hidden_layer[i].value);

		for (int j = 0; j < OUT_NODE; j++)
			sum += (hidden_layer[i].weight[j] * output_layer[j].delta);

		hidden_layer[i].delta *= sum;
	}

	// update input-hidden layer weight
	for (int j = 0; j < HIDE_NODE; j++){
		hidden_layer[j].bias += (learningRate * hidden_layer[j].delta);
		for (int i = 0; i < IN_NODE; i++)
			input_layer[i].weight[j] += (learningRate * hidden_layer[j].delta * input_layer[i].value);
	}

	// update hidden-output layer weight
	for (int j = 0; j < OUT_NODE; j++) {
		output_layer[j].bias += (learningRate * output_layer[j].delta);
		for (int i = 0; i < HIDE_NODE; i++)
			hidden_layer[i].weight[j] += (learningRate * output_layer[j].delta * hidden_layer[i].value);
	}
}

void Bp::TrainSimple()
{
	ForwardPropagationEpoc();
	BackPropagationEpoc();
}

void Bp::TrainGroup(vector<Data> group_data)
{
	for (vector<Data>::iterator iter = group_data.begin(); iter < group_data.end(); iter++)
	{
		for (int i = 0; i < IN_NODE; i++)
			input_layer[i].value = iter->in[i];
			
		for (int i = 0; i < OUT_NODE; i++)
		{
			if (iter->label == i) output_layer[i].rightout = 1;
			else output_layer[i].rightout = 0;
		}

		TrainSimple();
	}
}

void Bp::BpnnCalc(vector<Data> test_data)
{
	double count = 0;
	for (vector<Data>::iterator iter = test_data.begin(); iter < test_data.end(); iter++)
	{
		for (int i = 0; i < IN_NODE; i++) input_layer[i].value = iter->in[i];
		for (int i = 0; i < OUT_NODE; i++) if (iter->label == i) output_layer[i].rightout = 1;

		ForwardPropagationEpoc();

		double max = -1;
		int max_index = 0;
		for (int i = 0; i < OUT_NODE; i++)
			if (output_layer[i].value > max) { max = output_layer[i].value; max_index = i; }
		
		if (iter->label != max_index) count++;

		/*printf("[0].value = %f, [1].value = %f, [2].value = %f, rightout = %d, actual = %d\n"
			, output_layer[0].value, output_layer[1].value, output_layer[2].value,iter->label, max_index);*/
	}
	cout << "正确率为：" << (double)((test_data.size() - count) / test_data.size()) << endl;
}
