/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team：		SSL-ZJUNlict											*/
/* HomePage:	http://www.nlict.zju.edu.cn/ssl/WelcomePage.html		*/
/************************************************************************/
/* File:	  gpuBestAlgThread.cpp										*/
/* Func:	  计算最佳跑位点的线程，支持CPU模式和GPU模式				*/
/* Author:	  王群 2012-08-18											*/
/*            叶杨笙 2014-03-01                                         */
/* Refer:	  ###														*/
/* E-mail:	  wangqun1234@zju.edu.cn									*/
/************************************************************************/
/* 后续修改：															*/
/* 支持GPU算点，并将信息发送到owl2中用来可视化	from chen siyaun		*/
/************************************************************************/

#include "gpuBestAlgThread.h"
#include "Vision/VisionModule.h"
#include "GDebugEngine.h"
#include "ShootRangeList.h"
#include "param.h"
#include "src_heatMap.pb.h"
#include <time.h>
#include <thread>
#include "Semaphore.h"
extern Semaphore vision_to_cuda;

#define has_GPU false

#if has_GPU
extern "C" void calc_with_gpu(float* map_cpu, float* start_pos_cpu, int height, int width, int pos_num, float* pitch_info);
#else
void calc_with_gpu(float* map_cpu, float* start_pos_cpu, int height, int width, int pos_num, float* pitch_info) {};
#endif // 


#define OURPLAYER_NUM	8
#define THEIRPLAYER_NUM 8
#define BALL_NUM		1

namespace gpuCalcArea {
    std::thread* _best_calculation_thread = nullptr;
    QUdpSocket* heatMap_socket;
    int heatMap_port;
	const double PI = 3.1415926;
	const int Color_Size = 256;

	const double middleFrontBorderX = Param::Field::PITCH_LENGTH / 6;
	const double middleBackBorderX = -Param::Field::PITCH_LENGTH / 6;
	const double centerLeftBorderY = -Param::Field::PENALTY_AREA_WIDTH / 2;
	const double centerRightBorderY = Param::Field::PENALTY_AREA_WIDTH / 2;

	const double sideLineLeftBorderY = -ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_WIDTH / 2;
    //-450
    const double sideLineRightBorderY = ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_WIDTH / 2;
    //450
	const double goalLineFrontBorderX = Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH;
    //480
	const double goalLineBackBorderX = -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH;
    //-480
	const double penaltyFrontBorderX = (Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH) / 2;
    //240
    const double penaltyBackBorderX = -(Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH) / 2;
    //-240
	// 场地标号
	// 新的场地信息
	//           6 3 0  
	//  己方球门 7 4 1  敌方球门
	//           8 5 2
	// 该部分代码已适应新的上位机以及新的GPU运算方法
	// from siyuan chen
	// 目前这个区域已经更新

	FieldRectangle fieldRectangleArray[AREANUM] = {
		FieldRectangle(CGeoPoint(middleFrontBorderX,centerLeftBorderY),CGeoPoint(goalLineFrontBorderX,sideLineLeftBorderY)),
        FieldRectangle(CGeoPoint(middleFrontBorderX + 150.0,centerRightBorderY),CGeoPoint(goalLineFrontBorderX - 50,centerLeftBorderY)),
        //FieldRectangle(CGeoPoint(450,0),CGeoPoint(450,0)),
        FieldRectangle(CGeoPoint(middleFrontBorderX,sideLineRightBorderY),CGeoPoint(goalLineFrontBorderX,centerRightBorderY)),

		FieldRectangle(CGeoPoint(middleBackBorderX,centerLeftBorderY),CGeoPoint(middleFrontBorderX,sideLineLeftBorderY)),
        FieldRectangle(CGeoPoint(middleBackBorderX,centerRightBorderY),CGeoPoint(middleFrontBorderX + 150.0,centerLeftBorderY)),
		FieldRectangle(CGeoPoint(middleBackBorderX,sideLineRightBorderY),CGeoPoint(middleFrontBorderX,centerRightBorderY)),

		FieldRectangle(CGeoPoint(goalLineBackBorderX,centerLeftBorderY),CGeoPoint(middleBackBorderX,sideLineLeftBorderY)),
		FieldRectangle(CGeoPoint(goalLineBackBorderX,centerRightBorderY),CGeoPoint(middleBackBorderX,centerLeftBorderY)),
		FieldRectangle(CGeoPoint(goalLineBackBorderX,sideLineRightBorderY),CGeoPoint(middleBackBorderX,centerRightBorderY)),
	};
}

extern QMutex* _best_visiondata_copy_mutex;
extern QMutex* _value_getter_mutex;

CGPUBestAlgThread::CGPUBestAlgThread() {
	sendPoint = CGeoPoint(0, 0);
	_pVision = NULL;

	for (int i = 0; i < AREANUM; i++) {
		_lastCycle[i] = 0;
		_bestPoint[i] = CGeoPoint(0, 0);
	}
	_lastGPUCycle = 0;

	if (has_GPU) {
		// 需要查找的区域
		_start_pos_x = -(int)(Param::Field::PITCH_LENGTH / 2);
		_start_pos_y = -(int)(Param::Field::PITCH_WIDTH / 2);
		// TODO 这里的width和height是和正常看owl2颠倒的，后续再修改一下
		_height = Param::Field::PITCH_LENGTH;
		_width = Param::Field::PITCH_WIDTH;
		_step = 10; // 搜索的步长
		if (_height % _step != 0 || _width % _step != 0) {
			cout << "warning warning 场地尺寸不是step的整数倍" << endl;
		}
		// 定义需要申请的空间
		_w = _width / _step;
		_h = _height / _step;
		int map_size = _w * _h * sizeof(float);
		// (2+1+2+2+OURPLAYER_NUM*_palyer_pos_num+THEIRPLAYER_NUM*_palyer_pos_num) * sizeof(float)
		// 依次为：搜索区域开始位置、步长step、球的位置、球的速度、我方小车的位置、朝向、速度（首位为是否valid）、敌方小车的位置、朝向、速度（首位为是否valid）
		// 如果修改这部分代码，请仔细阅读赋值及GPU部分代码并与之进行相应的修改
		// 需要注意的部分有CPU空间的申请，对其进行赋值，将其拷贝的GPU上时申请的空间、GPU对该列表信息的解析
		_palyer_pos_num = 6; //一个机器人所需传递的信息数目
		int pos_size = (2 + 1 + 2 + 2 + OURPLAYER_NUM * _palyer_pos_num + THEIRPLAYER_NUM * _palyer_pos_num) * sizeof(float);

		_PointPotentialOrigin = (float*)malloc(map_size); // 用于存储计算后的结果
		_PointPotential = (float*)malloc(map_size);
		_start_pos_cpu = (float*)malloc(pos_size); // 交给GPU运算的数据
		for (int i = 0; i < 2 + 1 + 2 + 2 + OURPLAYER_NUM * _palyer_pos_num + THEIRPLAYER_NUM * _palyer_pos_num; i++) {
			_start_pos_cpu[i] = 0;
		}
	}
}

CGPUBestAlgThread::~CGPUBestAlgThread() {
	free(_PointPotentialOrigin);
	free(_PointPotential);
	free(_start_pos_cpu);
    delete gpuCalcArea::heatMap_socket;
    gpuCalcArea::heatMap_socket = nullptr;
    delete gpuCalcArea::_best_calculation_thread;
    gpuCalcArea::_best_calculation_thread = nullptr;
}

void CGPUBestAlgThread::initialize(CVisionModule* pVision) {
	_pVision = pVision;
	// 开启 GPU 计算的线程
	if (has_GPU) {
        gpuCalcArea::_best_calculation_thread = new std::thread([=] {doBestCalculation();});
        gpuCalcArea::_best_calculation_thread->detach();
	}
}

void CGPUBestAlgThread::startComm() {
    gpuCalcArea::heatMap_socket = new QUdpSocket();
    COptionModule* pOption = new COptionModule();
    gpuCalcArea::heatMap_port = pOption->MyColor() == TEAM_YELLOW ? CParamManager::Instance()->yellow_heat : CParamManager::Instance()->blue_heat;
    delete pOption;
}

void CGPUBestAlgThread::setSendPoint(const CGeoPoint passPoint) {
	sendPoint = passPoint;
}

bool CGPUBestAlgThread::isClose(const CGeoPoint pos1, const CGeoPoint pos2, float x_distance, float y_distance) {
	if (abs(pos1.x() - pos2.x()) < x_distance && abs(pos1.y() - pos2.y()) < y_distance) {
		return true;
	}
	else {
		return false;
	}
}

void CGPUBestAlgThread::generatePointValue() {
	//if (_pVision->Cycle() != _lastGPUCycle) {
		//_lastGPUCycle = _pVision->Cycle();
		/************************************************************************/
		/* 数据算法数据传入：车球位置信息                                       */
		/************************************************************************/
		// 上锁
		_best_visiondata_copy_mutex->lock();
		// 拷贝
		_start_pos_cpu[0] = _start_pos_x;
		_start_pos_cpu[1] = _start_pos_y;
		_start_pos_cpu[2] = _step;
		_start_pos_cpu[3] = _pVision->Ball().Pos().x();
		_start_pos_cpu[4] = _pVision->Ball().Pos().y();
		_start_pos_cpu[5] = _pVision->Ball().VelX();
		_start_pos_cpu[6] = _pVision->Ball().VelX();
		// 己方机器人信息
		int our_start_idx = 7;    // 在数组中开始存储的位置
		float* our_player_info = _start_pos_cpu + our_start_idx;
		for (int i = 0; i < OURPLAYER_NUM; i++) {
			if (_pVision->OurPlayer(i).Valid()) {
				const PlayerVisionT& ourPlayer = _pVision->OurPlayer(i);
				our_player_info[_palyer_pos_num * i] = 1.0;
				our_player_info[_palyer_pos_num * i + 1] = ourPlayer.X();
				our_player_info[_palyer_pos_num * i + 2] = ourPlayer.Y();
				our_player_info[_palyer_pos_num * i + 3] = ourPlayer.Dir();
				our_player_info[_palyer_pos_num * i + 4] = ourPlayer.VelX();
				our_player_info[_palyer_pos_num * i + 5] = ourPlayer.VelY();
			}
			else {
				for (int j = 0; j < _palyer_pos_num; j++) {
					our_player_info[_palyer_pos_num * i + j] = 0.0;
				}
			}
		}
		// 敌方机器人信息
		int their_start_idx = 7 + _palyer_pos_num * OURPLAYER_NUM; // 在数组中开始存储的位置
		float* their_player_info = _start_pos_cpu + their_start_idx;
		for (int i = 0; i < THEIRPLAYER_NUM; i++) {
			if (_pVision->TheirPlayer(i).Valid()) {
				const PlayerVisionT& theirPlayer = _pVision->TheirPlayer(i);
				their_player_info[_palyer_pos_num * i] = 1.0;
				their_player_info[_palyer_pos_num * i + 1] = theirPlayer.X();
				their_player_info[_palyer_pos_num * i + 2] = theirPlayer.Y();
				their_player_info[_palyer_pos_num * i + 3] = theirPlayer.Dir();
				their_player_info[_palyer_pos_num * i + 4] = theirPlayer.VelX();
				their_player_info[_palyer_pos_num * i + 5] = theirPlayer.VelY();
			}
			else {
				for (int j = 0; j < _palyer_pos_num; j++) {
					their_player_info[_palyer_pos_num * i + j] = 0.0;
				}
			}
		}
		// 解锁
		_best_visiondata_copy_mutex->unlock();
		int pos_num = 2 + 1 + 2 + 2 + OURPLAYER_NUM * _palyer_pos_num + THEIRPLAYER_NUM * _palyer_pos_num;

		_value_getter_mutex->lock();
		calc_with_gpu(_PointPotentialOrigin, _start_pos_cpu, _h, _w, pos_num, _pitch_info);
		memcpy(_PointPotential, _PointPotentialOrigin, getMapSize());
		processPointValue();
		_value_getter_mutex->unlock();
	//}
	//else {
    //    std::this_thread::sleep_for(std::chrono::microseconds(10000));
		//cout << "not in cycle" << endl;
	//}
	// cout << "genarate time" << ends - start << endl;
}

CGeoPoint CGPUBestAlgThread::getBestPointFromArea(int area_idx) {
	if (area_idx > AREANUM) { // 处理越界情况，但是后三个点的位置并没有生成
		return _bestPoint[0];
	}
	else {
		return _bestPoint[area_idx];
	}
}

// 将某一区域内的值变为最大值，从而不被考虑
void CGPUBestAlgThread::erasePointPotentialValue(const CGeoPoint centerPoint, float length, float width) {
	// 场地参数
	float halfPitchLength = Param::Field::PITCH_LENGTH / 2;
	float halfPitchWidth = Param::Field::PITCH_WIDTH / 2;
	// 其方法基本与getBestPoint中的相同，只是将搜索变为复制
	// 在坐标系中
	float left_up_pos_x = centerPoint.x() - length / 2;
	float left_up_pos_y = centerPoint.y() - width / 2;
	float right_down_pos_x = centerPoint.x() + length / 2;
	float right_down_pos_y = centerPoint.y() + width / 2;

	// 考虑步长的情况下区域开始的位置
	int start_pos_x_idx = ceil((left_up_pos_x + halfPitchLength) / _step);
	int start_pos_y_idx = ceil((left_up_pos_y + halfPitchWidth) / _step);

	// 考虑步长的情况下区域结束的位置
	int end_pos_x_idx = floor((right_down_pos_x - left_up_pos_x) / _step) + start_pos_x_idx;
	int end_pos_y_idx = floor((right_down_pos_y - left_up_pos_y) / _step) + start_pos_y_idx;

	for (int i = start_pos_x_idx; i < end_pos_x_idx + 1; i++) {
		for (int j = start_pos_y_idx; j < end_pos_y_idx + 1; j++) {
			_PointPotential[i * _w + j] = 255;
		}
	}
}

// 计算每个区域的最优点和最优值，在generatePointValue中已经加了进程锁，所以这里没有加，所以这个函数不准在外面调用
void CGPUBestAlgThread::getBestPoint(const CGeoPoint leftUp, const CGeoPoint rightDown, CGeoPoint& bestPoint, float& minValue) {
	// 存下九个区域的最优点以供调用，并且需要记录每个点在当前cycle是否已经更新
	if (has_GPU) {
		// 初始化参数
		minValue = 255;
		// 场地参数
		float halfPitchLength = Param::Field::PITCH_LENGTH / 2;
		float halfPitchWidth = Param::Field::PITCH_WIDTH / 2;

		// 在坐标系中
		float left_up_pos_x = leftUp.x();
		float left_up_pos_y = leftUp.y();
		float right_down_pos_x = rightDown.x();
		float right_down_pos_y = rightDown.y();

		// 考虑步长的情况下区域开始的位置
		int start_pos_x_idx = ceil((left_up_pos_x + halfPitchLength) / _step);
		int start_pos_y_idx = ceil((left_up_pos_y + halfPitchWidth) / _step);

		// 考虑步长的情况下区域结束的位置
		int end_pos_x_idx = floor((right_down_pos_x - left_up_pos_x) / _step) + start_pos_x_idx;
		int end_pos_y_idx = floor((right_down_pos_y - left_up_pos_y) / _step) + start_pos_y_idx;

		//// 一些点的debug信息
		//float start_pos_x = start_pos_x_idx * _step - halfPitchLength;
		//float start_pos_y = start_pos_y_idx * _step - halfPitchWidth;
		//float end_pos_x = end_pos_x_idx * _step - halfPitchLength;
		//float end_pos_y = end_pos_y_idx * _step - halfPitchWidth;
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(start_pos_x, start_pos_y), COLOR_PURPLE);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(end_pos_x, end_pos_y), COLOR_RED);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(start_pos_x_idx * _step - halfPitchLength, end_pos_y_idx * _step - halfPitchWidth), COLOR_BLUE);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(end_pos_x_idx * _step - halfPitchLength, start_pos_y_idx * _step - halfPitchWidth), COLOR_GREEN);

		for (int i = start_pos_x_idx; i < end_pos_x_idx + 1; i++) {
			for (int j = start_pos_y_idx; j < end_pos_y_idx + 1; j++) {
				if (_PointPotential[i * _w + j] < minValue) {
					minValue = _PointPotential[i * _w + j];
					bestPoint = CGeoPoint(i * _step - halfPitchLength, j * _step - halfPitchWidth);
				}
			}
		}
	}
	else {
		minValue = 255;
		bestPoint = leftUp.midPoint(rightDown);
	}
}

// 处理每个区域，在generatePointValue中已经加了进程锁，所以这里没有加，所以这个函数不准在外面调用
void CGPUBestAlgThread::processPointValue() {
	// 对_PointPotential数据进行处理，并找出前六区域中的最优值，并存储在_bestPoint中
	AreaStructList areaStructList;
	CGeoPoint bestPoint;
	float minValue;
	int area_idx;

	// 搜索出所有区域的暂时最优点
	for (int area_idx = 0; area_idx < 6; area_idx++) {
		getBestPoint(gpuCalcArea::fieldRectangleArray[area_idx].centerArea()._leftUpPos, gpuCalcArea::fieldRectangleArray[area_idx].centerArea()._rightDownPos, bestPoint, minValue);
		areaStructList.push_back(AreaStruct(bestPoint, minValue, area_idx, false));
	}

	while (areaStructList.size()) {
		// 先排序
		sort(areaStructList.begin(), areaStructList.end(), greater<AreaStruct>());
		// 判断value最小的点是否被已选定点冲突
		if (areaStructList.at(0)._conflict) { // 如果冲突，重新计算该点，并更新该点信息
			area_idx = areaStructList.at(0)._area_idx;
			getBestPoint(gpuCalcArea::fieldRectangleArray[area_idx].centerArea()._leftUpPos, gpuCalcArea::fieldRectangleArray[area_idx].centerArea()._rightDownPos, bestPoint, minValue);
			areaStructList.at(0)._pos = bestPoint;
			areaStructList.at(0)._value = minValue;
			areaStructList.at(0)._conflict = false;
		}
		else { // 如果不冲突，将该点移出队列存放至规划点数组中，根据该点对场势进行erase并重新判断其余点是否冲突
			bestPoint = areaStructList.at(0)._pos;
			area_idx = areaStructList.at(0)._area_idx;
			areaStructList.pop_front();
			_bestPoint[area_idx] = bestPoint;
			// 判断是否已经全部移出队列，由于该操作，因此最后一个点并不会earse区域
			if (areaStructList.empty()) {
				break;
			}
			else {
				float length = 200;
				float width = 200;
				erasePointPotentialValue(bestPoint, length, width);
				for (int i = 0; i < areaStructList.size(); i++) {
					if (!areaStructList.at(i)._conflict) {  //如果已经冲突则不需要修改
						if (isClose(bestPoint, areaStructList.at(i)._pos, length / 2, width / 2)) {
							areaStructList.at(i)._conflict = true;
						}
					}
				}
			}
		}
	}


}

bool CGPUBestAlgThread::isLastOneValid(const CGeoPoint& p) {
	CShootRangeList shootRangeList(_pVision, 1, p);
	const CValueRangeList& shootRange = shootRangeList.getShootRange();
	if (shootRange.size() > 0) {
		const CValueRange* bestRange = shootRange.getMaxRangeWidth();
		if (bestRange->getWidth() > Param::Field::BALL_SIZE * 2.0) {
			return true;
		}
	}
	return false;
}

void CGPUBestAlgThread::doBestCalculation() {
    startComm();
	while (true) {
		vision_to_cuda.Wait();
		GPUBestAlgThread::Instance()->generatePointValue();
		GPUBestAlgThread::Instance()->setPointValue();
        GPUBestAlgThread::Instance()->sendPointValue();
	}
}

double CGPUBestAlgThread::getPosPotential(const CGeoPoint p) {
	return 0;
}

void CGPUBestAlgThread::setPointValue() {
	_value_getter_mutex->lock();
	pointValueList.clear();
	int size = _h * _w;
	for (int i = 0; i < size; i++) {
		if (_PointPotentialOrigin[i] < 0) _PointPotentialOrigin[i] = 0;
		PointValueStruct p;
		p.pos = i;
		p.value = _PointPotentialOrigin[i];
		pointValueList.push_back(p);
	}
	_value_getter_mutex->unlock();
}

void CGPUBestAlgThread::sendPointValue() {
	//将点均分为若干个颜色,现在情况为把所有点按分值大小分配为256部分，每部分对应一个颜色
	sort(pointValueList.begin(), pointValueList.end(), greater<PointValueStruct>());
	int point_size = pointValueList.size();
    //Heat_Map msgs;
    OWL::Protocol::Heat_Map_New msgs;
	for (int m = gpuCalcArea::Color_Size - 1; m >= 0; m--) { //先把重要的点发过去
		msgs.set_login_name(OParamManager::Instance()->LoginName);
		auto points = msgs.add_points();
		for (int n = m * point_size / gpuCalcArea::Color_Size; n < (m + 1) * point_size / gpuCalcArea::Color_Size; n++) {
			points->add_pos(pointValueList.at(n).pos);
			points->set_color(max(255 - (int)pointValueList.at(n).value, 0));
			//auto pos = points->add_pos();
			//pos->set_x(pointValueList.at(n).pos_x);
			//pos->set_y(pointValueList.at(n).pos_y);
		}
		//由于UDP发包大小的限制，所以将颜色信息分批次发送
		//发送message//
		int size = msgs.ByteSize();
        QByteArray output(size, 0);
        msgs.SerializeToArray(output.data(), size);
        gpuCalcArea::heatMap_socket->writeDatagram(output.data(), size, QHostAddress(CParamManager::Instance()->local_address), gpuCalcArea::heatMap_port);
		//删除掉message的部分，回收空间//
		msgs.Clear();
		//delete[] msgs;
	}
}
