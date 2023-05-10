/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team：		SSL-ZJUNlict											*/
/* HomePage:	http://www.nlict.zju.edu.cn/ssl/WelcomePage.html		*/
/************************************************************************/
/* File:	  gpuBestAlgThread.h										*/
/* Func:	  计算最佳跑位点的线程，支持CPU模式和GPU模式				*/
/* Author:	  王群 2012-08-18											*/
/*            叶杨笙 2014-03-01                                         */
/* Refer:	  ###														*/
/* E-mail:	  wangqun1234@zju.edu.cn									*/
/* Version:	  0.0.1														*/
/************************************************************************/

#ifndef _GPU_BEST_ALG_THREAD_H
#define _GPU_BEST_ALG_THREAD_H

#include <QMutex>

#include <fstream>
#include <singleton.h>
#include <deque>
#include "Vision/VisionModule.h"
#include "geometry.h"
#include "NormalPlayUtils.h"
#include "param.h"

#define AREANUM 6 // 区域数目

struct PointValueStruct {
	float pos_x;
	float pos_y;
	float pos;
	float value;
	PointValueStruct() : pos_x(0), pos_y(0), pos(0), value(0) {}
	bool operator < (const PointValueStruct& p) const {
		if (value < p.value)
		{
			return true;
		}
		return false;
	}
	bool operator == (const PointValueStruct& p) const {
		if (value == p.value)
		{
			return true;
		}
		return false;
	}
	bool operator > (const PointValueStruct& p) const {
		if (value > p.value)
		{
			return true;
		}
		return false;
	}
};
typedef std::vector<PointValueStruct> PointValueList;

struct AreaStruct {
	CGeoPoint _pos;
	float _value;
	int _area_idx;
	bool _conflict;

	AreaStruct(CGeoPoint& pos, float& value, int& area_idx, bool conflict) {
		_pos = pos;
		_value = value;
		_area_idx = area_idx;
		_conflict = conflict;
	}

	bool operator < (const AreaStruct& area) const {
		if (_value < area._value) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator > (const AreaStruct& area) const {
		if (_value > area._value) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator == (const AreaStruct& area) const {
		if (_value == area._value) {
			return true;
		}
		else {
			return false;
		}
	}
};
typedef std::deque<AreaStruct> AreaStructList;

// 区域的一个结构体，实现了区域的相加
// 构造时传入左下点与右上点
// centerArea返回一个中心点不变，长宽变为0.9倍的区域
struct FieldRectangle {
	FieldRectangle(CGeoPoint ld, CGeoPoint ru) { 
		_leftDownPos = ld;
		_rightUpPos = ru;
		_leftUpPos = CGeoPoint(ld.x(), ru.y());
		_rightDownPos = CGeoPoint(ru.x(), ld.y());
		double tempX = (ld.x() + ru.x()) / 2, tempY = (ld.y() + ru.y()) / 2;
		_centerPos = CGeoPoint(tempX, tempY);
		_rangeX = (ru.x() - ld.x()) * 0.45;
		_rangeY = (ld.y() - ru.y()) * 0.45;
	}

	void processField(CGeoPoint lu, CGeoPoint rd) {
		_leftUpPos = lu;
		_rightDownPos = rd;

		_leftDownPos = CGeoPoint(lu.x(), rd.y());
		_rightUpPos = CGeoPoint(rd.x(), lu.y());

		double tempX = (lu.x() + rd.x()) / 2, tempY = (lu.y() + rd.y()) / 2;
		_centerPos = CGeoPoint(tempX, tempY);
		_rangeX = (rd.x() - lu.x()) * 0.45;
		_rangeY = (rd.y() - lu.y()) * 0.45;
	}

	bool check4inclusion(CGeoPoint point) {
		if ( ((point.x() >= _leftUpPos.x() && point.x() <= _rightUpPos.x())  ||
			  (point.x() <= _leftUpPos.x() && point.x() >= _rightUpPos.x())) &&
			 ((point.y() >= _leftUpPos.y() && point.y() <= _leftDownPos.y()) ||
			  (point.y() <= _leftUpPos.y() && point.y() >= _leftDownPos.y()))  )
			return true;
		else
			return false;
	}

	// 区域相加功能重构后还未实现，此部分代码需要结合x轴向右，y轴向上的的坐标系理解 from siyuan chen
	//FieldRectangle operator +(FieldRectangle& param){
	//	if (param._leftDownPos.x()<this->_leftDownPos.x()
	//		&&param._leftDownPos.y()<this->_leftDownPos.y()){
	//		return FieldRectangle(param._leftDownPos,this->_rightUpPos);
	//	}else{
	//		return FieldRectangle(this->_leftDownPos,param._rightUpPos);
	//	}
	//}
	FieldRectangle centerArea() {
		_rangeX = (_rightDownPos.x() - _leftUpPos.x()) * 0.45;
		_rangeY = (_rightDownPos.y() - _leftUpPos.y()) * 0.45;
		return FieldRectangle(CGeoPoint(_centerPos.x() - _rangeX, _centerPos.y() + _rangeY), CGeoPoint(_centerPos.x() + _rangeX, _centerPos.y() - _rangeY));
	}
	CGeoPoint getCenter() {
		return _centerPos;
	}
	double _rangeX, _rangeY;
	CGeoPoint _leftDownPos;
	CGeoPoint _rightUpPos;
	CGeoPoint _leftUpPos;
	CGeoPoint _rightDownPos;
	CGeoPoint _centerPos;
};


/**
@brief    计算最佳跑位点的线程，支持GPU计算
@details  本类是独立于主线程的算法线程，提供全场多区域的最佳跑位点的计算。
@note	注意，在每一帧当中，在使用对外接口getBestPoint函数前，要调用一次setSendPoint函数，设定
传球的点。一般此处为球当前所在的点*/

class CGPUBestAlgThread {
public:
	CGPUBestAlgThread();
	~CGPUBestAlgThread();

	/**
	@brief	注册视觉信息并且开启算法线程*/
	void initialize(CVisionModule* _pVision);

	/**
	@brief	本模块的对外接口
	@param	传入区域的id，区域具体位置在gpuBestAlgThread.cpp中定义
	目前所有需要GPU算点的功能均调用该接口，日后如果需要也可以根据getBestPoint()自定义其它接口，但为了代码的规范性不推荐*/
	CGeoPoint getBestPointFromArea(int area_idx);

	/**
	@brief	球速预测模块的对外接口
	@param	ball_pos 当前球的位置
	@param	ball_dir 当前球的运动方向
	@param	传入frame，返回frame帧时球的预测位置*/
	CGeoPoint getBallPosFromFrame(CGeoPoint ball_pos, CVector ball_vel, int frame);

	/**
	@brief 全场所有点的势能值的生成*/
	void generatePointValue();

	/**
	@brief 预测球的位置*/
	void CGPUBestAlgThread::predictBallPos();

	/**
	@brief	判断某一区域前一帧的最佳跑位点是否仍有效*/
	// TODO 目前无用，整理代码后准备删除
	bool isLastOneValid(const CGeoPoint& p);
	/**
	@brief	设定传球点
	@param	passPoint 当前传球点*/
	// TODO 目前并未使用
	void setSendPoint(const CGeoPoint passPoint);

	// 目前为空函数
	double getPosPotential(const CGeoPoint p);

	// 返回场势图的size
	int getMapSize() { return _w * _l * sizeof(float); }

	// owl2可视化所需函数
	void startComm();
	void setPointValue();
	void sendPointValue();
	void sendFieldRectangle();

	/**
	@brief	开启线程所用的函数*/
    void doBestCalculation();

private:
	/**
	@brief	将一定区域内的value都置为255（最大值）
	@param	cneterPoint，传入的区域中心点
	@param	length，区域的长（沿x轴方向）
	@param	width，区域的宽（沿y轴方向）*/
	void erasePointPotentialValue(const CGeoPoint centerPoint, float length, float width);

	/**
	@brief	按照重要性排序调整bestpoint顺序*/
	void supportSort();
	void supportSortV2();

	/**
	@brief	获取球所在区域index*/
	int getBallArea();

	/**
	@brief	寻找一定区域里的最优点
	@param	leftUp 取点区域的左上点(x轴向正右方向的直角坐标系中)
	@param	rightDown 取点区域的右下点(x轴向正右方向的直角坐标系中)
	原来支持选择区域形状以及去掉保持系统控制参数的传入，目前暂未实现，先实现基础功能，后续有需要可以加入*/
	void getBestPoint(const CGeoPoint leftUp, const CGeoPoint rightDown, CGeoPoint& bestPoint, float& minValue);

	/**
	@brief	动态模糊边界*/
	void obscureBoundary();
	void obscureBoundaryV2();

	double limitPosX(double);
	double limitPosY(double);

	/**
	@brief 处理全场势能点，并搜索前六个区域中的最优点
	目前处理的目的为：避免区域生成的点过近*/
	void processPointValue();

	/**
	@brief 判断两个点是否距离较近，目前是判断是否在一个矩阵内
	用于避免区域生成的点过近*/
	bool isClose(const CGeoPoint pos1, const CGeoPoint pos2, float x_distance, float y_distance);
	 
	/**
	@brief 读取矩阵*/
	int getMatrix(const string file_name, int max_row_num, int max_col_num, float* matrix);
private:

	float* _PointPotentialOrigin, * _PointPotential, * _start_pos_cpu;	     ///GPU势能值数组、处理后的GPU势能值数组、场地上机器人及球的信息数组
	// 注意：_start_pos_cpu中存储了小车、球的信息，并会被复制到GPU中，如果修改了其中信息的传递规则，请仔细阅读赋值部分代码与GPU部分解析代码
	//

	CVisionModule* _pVision;			             ///<图像指针
	int _lastGPUCycle;					 ///上一帧GPU帧号
	int _lastCycle[AREANUM] = { 0 };           ///  上一帧9个区域的CPU帧号
	float _pointPotential[AREANUM];        /// 9个区域最优点的分值  
	CGeoPoint _bestPoint[AREANUM];         /// 当前帧9个区域的最优点
	CGeoPoint _bestSupport[AREANUM];         /// 按照支撑点重要性进行排序后的最优点


	int _start_pos_x, _start_pos_y, _width, _length, _step;     ///搜索区域参数，分别为左上角坐标、区域长与宽、搜索步长
	int _w, _l;                                       /// 申请空间参数  
	int _player_pos_num;                              //一个机器人所需传递的信息数目，目前为小车的位置、朝向、速度（首位为是否valid）

	CGeoPoint sendPoint;				///<传球点，一般为球所在的点
	int halfLength; // 场地半长
	int halfWidth;  // 场地半宽
	int halfGoalWidth;
    float _pitch_info[4] = { static_cast<float>(Param::Field::PITCH_LENGTH), static_cast<float>(Param::Field::PITCH_WIDTH), static_cast<float>(Param::Field::PENALTY_AREA_DEPTH), static_cast<float>(Param::Field::PENALTY_AREA_WIDTH) }; // 场地信息，依次为场地长、宽、禁区深度、宽

	PointValueList pointValueList;

	// 球速预测部分
	bool matrix_ok = false;
	int input_dim, output_dim, hidden_layer_dim;
	float* a_1_matrix_cpu, * bias_1_matrix_cpu, * a_2_matrix_cpu, * bias_2_matrix_cpu;
	float* _history_ball_vel,* _ball_pos_prediction_results;
};

typedef Falcon::NormalSingleton<CGPUBestAlgThread> GPUBestAlgThread;
#endif
