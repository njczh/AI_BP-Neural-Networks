#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
using namespace std;

#define IN_NODE 4							// 输入层结点数
#define OUT_NODE 3							// 输出层结点数
// #define hidelayer 1						// 隐含层层数 先从一层开始
#define HIDE_NODE 10						// 隐含层结点数
#define learningRate 0.01					// 学习速率，alpha


/// ------ 输入层结点 ------
struct inputNode
{
	double value;							// 结点对应的输入值
	vector<double> weight;					// 输入结点面对隐含第一层每一个结点的权值
};

///  ------ 隐含层结点 ------
struct hiddenNode
{
	double value;							// 结点当前值
	vector<double> weight;					// 面对下一层（更深隐含层/输出层）的每一个结点的权值
	double bias;							// 偏移量
	double delta;							// 误差项δ
};

/// ------ 输出层结点 ------
struct outputNode
{
	double value;							// 结点当前输出值
	double rightout;						// 正确输出值
	double bias;							// 偏移量
	double delta;							// 误差项δ
};

/// ------ 样本 ------
struct Data
{
	double in[IN_NODE];
	int label;
};

class Bp
{
public:
	inputNode input_layer[IN_NODE];			// 输入层仅一层
	outputNode output_layer[OUT_NODE];		// 输出层仅一层
	hiddenNode hidden_layer[HIDE_NODE];		// 隐含层先从一层开始

public:
	Bp();
	// ~Bp();
	void ForwardPropagationEpoc();			// 单个样本前向传播
	void BackPropagationEpoc();				// 单个样本后向传播
	void TrainSimple();						// 单个样本训练
	void TrainGroup(vector<Data>);			// 整组样本训练
	void BpnnCalc(vector<Data>);			// 利用BP神经网络分类

private:

};