#pragma once

#include <iostream>
#include <vector>
using namespace std;

#define in_node 4		// 输入层结点数
#define out_node 3		// 输出层结点数
// #define hidelayer 1	// 隐含层层数 先从一层开始
#define hide_node 10	// 隐含层结点数


// ------ 输入层结点 ------
struct inputNode
{
	double value;			// 结点对应的输入值
	vector<double> weight;	// 输入结点面对隐含第一层每一个结点的权值
};

// ------ 输出层结点 ------
struct outputNode
{
	double value;			// 结点当前输出值
	double rightout;		// 正确输出值
	double delta;			// 当前结果与正确输出值之差(∆)
};

//  ------ 隐含层结点 ------
struct hiddenNode
{
	double value;			// 结点当前值
	double delta;			// 由后一层传递而来的“正确值”与当前值的差
	double bias;			// 偏移量
	vector<double> weight;	// 面对下一层（更深隐含层/输出层）的每一个结点的权值
};

class Bp
{
public:
	inputNode input_layer[in_node];			// 输入层仅一层
	outputNode output_layer[out_node];		// 输出层仅一层
	hiddenNode hidden_layer[hide_node];		// 隐含层先从一层开始

public:
	Bp();
	~Bp();

private:

};

Bp::Bp()
{
}

Bp::~Bp()
{
}