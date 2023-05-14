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
#include <sstream>
#include "TaskMediator.h"
extern Semaphore vision_to_cuda;


#ifdef ENABLE_CUDA
extern "C" void calc_with_gpu(float* map_cpu, float* start_pos_cpu, int length, int width, int pos_num, float* pitch_info);
extern "C" void ball_model_calc_with_gpu(float* vel_data_cpu, float* predict_results, float* a_1_matrix_cpu, float* bias_1_matrix_cpu, float* a_2_matrix_cpu, float* bias_2_matrix_cpu);
#else
void calc_with_gpu(float* map_cpu, float* start_pos_cpu, int length, int width, int pos_num, float* pitch_info) {};
void ball_model_calc_with_gpu(float* vel_data_cpu, float* predict_results, float* a_1_matrix_cpu, float* bias_1_matrix_cpu, float* a_2_matrix_cpu, float* bias_2_matrix_cpu) {};
#endif // 


#define OURPLAYER_NUM	6
#define THEIRPLAYER_NUM 6
#define BALL_NUM		1

namespace gpuCalcArea {
    std::thread* _best_calculation_thread = nullptr;
    QUdpSocket* heatMap_socket;
    int heatMap_port;
	const double PI = 3.1415926;
	const int Color_Size = 256;

	const double differenceX = Param::Field::PITCH_LENGTH / 9;

	const double middleFrontBorderX = Param::Field::PITCH_LENGTH / 6;
	const double middleBackBorderX = -Param::Field::PITCH_LENGTH / 6;
	const double centerLeftBorderY = -Param::Field::PENALTY_AREA_WIDTH / 2;
	const double centerRightBorderY = Param::Field::PENALTY_AREA_WIDTH / 2;
	
	const double sideLineFrontBorderX = ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_LENGTH / 2;

	const double sideLineBackBorderX = -ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_LENGTH / 2;

	const double sideLineLeftBorderY = -ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_WIDTH / 2;
    //-450
    const double sideLineRightBorderY = ParamManager::Instance()->SUPPORT_DIST * Param::Field::PITCH_WIDTH / 2;
    //450
	const double goalLineFrontBorderX = Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH * 2 / 3;
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
		FieldRectangle(CGeoPoint(middleFrontBorderX,centerLeftBorderY),CGeoPoint(goalLineFrontBorderX, sideLineLeftBorderY)),
        FieldRectangle(CGeoPoint(middleFrontBorderX + differenceX,centerRightBorderY),CGeoPoint(goalLineFrontBorderX,centerLeftBorderY)),
        //FieldRectangle(CGeoPoint(450,0),CGeoPoint(450,0)), 
        FieldRectangle(CGeoPoint(middleFrontBorderX,sideLineRightBorderY),CGeoPoint(goalLineFrontBorderX,centerRightBorderY)),

		FieldRectangle(CGeoPoint(middleBackBorderX,centerLeftBorderY),CGeoPoint(middleFrontBorderX,sideLineLeftBorderY)),
        FieldRectangle(CGeoPoint(middleBackBorderX,centerRightBorderY),CGeoPoint(middleFrontBorderX + differenceX,centerLeftBorderY)),
		FieldRectangle(CGeoPoint(middleBackBorderX,sideLineRightBorderY),CGeoPoint(middleFrontBorderX,centerRightBorderY)),

		// FieldRectangle(CGeoPoint(goalLineBackBorderX,centerLeftBorderY),CGeoPoint(middleBackBorderX,sideLineLeftBorderY)),
		// FieldRectangle(CGeoPoint(goalLineBackBorderX,centerRightBorderY),CGeoPoint(middleBackBorderX,centerLeftBorderY)),
		// FieldRectangle(CGeoPoint(goalLineBackBorderX,sideLineRightBorderY),CGeoPoint(middleBackBorderX,centerRightBorderY)),
	};
	FieldRectangle processed_fieldRectangleArray[AREANUM] = {
		FieldRectangle(CGeoPoint(middleFrontBorderX,centerLeftBorderY),CGeoPoint(goalLineFrontBorderX,sideLineLeftBorderY)),
		FieldRectangle(CGeoPoint(middleFrontBorderX + differenceX,centerRightBorderY),CGeoPoint(goalLineFrontBorderX,centerLeftBorderY)),
		//FieldRectangle(CGeoPoint(450,0),CGeoPoint(450,0)),
		FieldRectangle(CGeoPoint(middleFrontBorderX,sideLineRightBorderY),CGeoPoint(goalLineFrontBorderX,centerRightBorderY)),

		FieldRectangle(CGeoPoint(middleBackBorderX,centerLeftBorderY),CGeoPoint(middleFrontBorderX,sideLineLeftBorderY)),
		FieldRectangle(CGeoPoint(middleBackBorderX,centerRightBorderY),CGeoPoint(middleFrontBorderX + differenceX,centerLeftBorderY)),
		FieldRectangle(CGeoPoint(middleBackBorderX,sideLineRightBorderY),CGeoPoint(middleFrontBorderX,centerRightBorderY)),

		// FieldRectangle(CGeoPoint(goalLineBackBorderX,centerLeftBorderY),CGeoPoint(middleBackBorderX,sideLineLeftBorderY)),
		// FieldRectangle(CGeoPoint(goalLineBackBorderX,centerRightBorderY),CGeoPoint(middleBackBorderX,centerLeftBorderY)),
		// FieldRectangle(CGeoPoint(goalLineBackBorderX,sideLineRightBorderY),CGeoPoint(middleBackBorderX,centerRightBorderY)),
	};

}

extern QMutex* _best_visiondata_copy_mutex;
extern QMutex* _value_getter_mutex;
extern QMutex* _ball_pos_prediction_mutex;

CGPUBestAlgThread::CGPUBestAlgThread() {
	sendPoint = CGeoPoint(0, 0);
	_pVision = NULL;
	for (int i = 0; i < AREANUM; i++) {
		_lastCycle[i] = 0;
		_bestPoint[i] = CGeoPoint(0, 0);
	}
	_lastGPUCycle = 0;

	// 球速预测部分
	input_dim = 10;
	hidden_layer_dim = 80;
	output_dim = 50;

	_history_ball_vel = (float*)malloc(input_dim * sizeof(float));
	for (int i = 0; i < input_dim; i++) {
		_history_ball_vel[i] = 0.0f;
	}
	_ball_pos_prediction_results = (float*)malloc(output_dim * sizeof(float));
	for (int i = 0; i < output_dim; i++) {
		_ball_pos_prediction_results[i] = 0.0f;
	}

#ifdef ENABLE_CUDA
		// 需要查找的区域
		_length = Param::Field::PITCH_LENGTH / 2 - gpuCalcArea::middleBackBorderX;
		_width = Param::Field::PITCH_WIDTH;
		_step = ParamManager::Instance()->step; // 搜索的步长
		// 起始点使得所有点都距离边线有半个步长的距离
		_start_pos_x = ParamManager::Instance()->startPosX + _step * 0.5;
		_start_pos_y = ParamManager::Instance()->startPosY + _step * 0.5;
		if (_length % _step != 0 || _width % _step != 0) {
			cout << "warning warning 场地尺寸不是step的整数倍" << endl;
		}
		// 定义需要申请的空间
		_w = _width / _step;
		_l = _length / _step;
		int map_size = _w * _l * sizeof(float);
		// (2+1+2+2+OURPLAYER_NUM*_player_pos_num+THEIRPLAYER_NUM*_player_pos_num) * sizeof(float)
		// 依次为：搜索区域开始位置、步长step、球的位置、球的速度、我方小车的位置、朝向、速度（首位为是否valid）、敌方小车的位置、朝向、速度（首位为是否valid）
		// 如果修改这部分代码，请仔细阅读赋值及GPU部分代码并与之进行相应的修改
		// 需要注意的部分有CPU空间的申请，对其进行赋值，将其拷贝的GPU上时申请的空间、GPU对该列表信息的解析
		_player_pos_num = 6; //一个机器人所需传递的信息数目
		int pos_size = (2 + 1 + 2 + 2 + OURPLAYER_NUM * _player_pos_num + THEIRPLAYER_NUM * _player_pos_num) * sizeof(float);

		_PointPotentialOrigin = (float*)malloc(map_size); // 用于存储计算后的结果
		_PointPotential = (float*)malloc(map_size);
		_start_pos_cpu = (float*)malloc(pos_size); // 交给GPU运算的数据
		for (int i = 0; i < 2 + 1 + 2 + 2 + OURPLAYER_NUM * _player_pos_num + THEIRPLAYER_NUM * _player_pos_num; i++) {
			_start_pos_cpu[i] = 0.0f;
		}

		// 读取矩阵
		// 线性层：y=x*A+b  ，这里的A与pytorch param中的矩阵是转置关系
		a_1_matrix_cpu = (float*)malloc((input_dim * hidden_layer_dim) * sizeof(float));
		bias_1_matrix_cpu = (float*)malloc(hidden_layer_dim * sizeof(float));
		a_2_matrix_cpu = (float*)malloc((hidden_layer_dim * output_dim) * sizeof(float));
		bias_2_matrix_cpu = (float*)malloc(output_dim * sizeof(float));
		
		int status1 = getMatrix("../data/BallModel/model_param/a_1.txt", input_dim, hidden_layer_dim, a_1_matrix_cpu);
		int status2 = getMatrix("../data/BallModel/model_param/b_1.txt", hidden_layer_dim, 1, bias_1_matrix_cpu);
		int status3 = getMatrix("../data/BallModel/model_param/a_2.txt", hidden_layer_dim, output_dim, a_2_matrix_cpu);
		int status4 = getMatrix("../data/BallModel/model_param/b_2.txt", output_dim, 1, bias_2_matrix_cpu);


		if (status1 && status2 && status3 && status4) {
			//std::cout << "a1 matrix:";
			//for (int i = 0; i < 5; i++) {
			//	std::cout << a_1_matrix_cpu[i] << " ";
			//}
			//std::cout << std::endl;
			matrix_ok = true;
		}
#endif
}

CGPUBestAlgThread::~CGPUBestAlgThread() {
	free(_PointPotentialOrigin);
	free(_PointPotential);
	free(_start_pos_cpu);
	free(_history_ball_vel);
	free(_ball_pos_prediction_results);
	free(a_1_matrix_cpu);
	free(bias_1_matrix_cpu);
	free(a_2_matrix_cpu);
	free(bias_2_matrix_cpu);
    delete gpuCalcArea::heatMap_socket;
    gpuCalcArea::heatMap_socket = nullptr;
    delete gpuCalcArea::_best_calculation_thread;
    gpuCalcArea::_best_calculation_thread = nullptr;
}

void CGPUBestAlgThread::initialize(CVisionModule* pVision) {
	_pVision = pVision;
	// 开启 GPU 计算的线程
#ifdef ENABLE_CUDA
        gpuCalcArea::_best_calculation_thread = new std::thread([=] {doBestCalculation();});
        gpuCalcArea::_best_calculation_thread->detach();
#endif
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
		// _best_visiondata_copy_mutex->lock();
		// 拷贝
		_start_pos_cpu[0] = _start_pos_x;
		_start_pos_cpu[1] = _start_pos_y;
		_start_pos_cpu[2] = _step;
		_start_pos_cpu[3] = _pVision->Ball().Pos().x();
		_start_pos_cpu[4] = _pVision->Ball().Pos().y();
		_start_pos_cpu[5] = _pVision->Ball().VelX();
		_start_pos_cpu[6] = _pVision->Ball().VelY();
		// 己方机器人信息
		int our_start_idx = 7;    // 在数组中开始存储的位置
		float* our_player_info = _start_pos_cpu + our_start_idx;
		int count = 0;
		for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
			if (_pVision->OurPlayer(i).Valid()) {
				const PlayerVisionT& ourPlayer = _pVision->OurPlayer(i);
				our_player_info[_player_pos_num * count] = 1.0;
				our_player_info[_player_pos_num * count + 1] = ourPlayer.X();
				our_player_info[_player_pos_num * count + 2] = ourPlayer.Y();
				our_player_info[_player_pos_num * count + 3] = ourPlayer.Dir();
				our_player_info[_player_pos_num * count + 4] = ourPlayer.VelX();
				our_player_info[_player_pos_num * count + 5] = ourPlayer.VelY();
				count++;
			}
		}
		if (count < OURPLAYER_NUM) {
			for (int i = count; i < OURPLAYER_NUM; i++) {
				for (int j = 0; j < _player_pos_num; j++) {
					our_player_info[_player_pos_num * i + j] = 0.0;
				}
			}
		}
		count = 0;
		// 敌方机器人信息
		int their_start_idx = 7 + _player_pos_num * OURPLAYER_NUM; // 在数组中开始存储的位置
		float* their_player_info = _start_pos_cpu + their_start_idx;
		for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
			if (_pVision->TheirPlayer(i).Valid()) {
				const PlayerVisionT& theirPlayer = _pVision->TheirPlayer(i);
				their_player_info[_player_pos_num * i] = 1.0;
				their_player_info[_player_pos_num * i + 1] = theirPlayer.X();
				their_player_info[_player_pos_num * i + 2] = theirPlayer.Y();
				their_player_info[_player_pos_num * i + 3] = theirPlayer.Dir();
				their_player_info[_player_pos_num * i + 4] = theirPlayer.VelX();
				their_player_info[_player_pos_num * i + 5] = theirPlayer.VelY();
				count++;
			}
		}
		if (count < THEIRPLAYER_NUM) {
			for (int i = count; i < THEIRPLAYER_NUM; i++) {
				for (int j = 0; j < _player_pos_num; j++) {
					their_player_info[_player_pos_num * i + j] = 0.0;
				}
			}
		}
		// 解锁
		// _best_visiondata_copy_mutex->unlock();
		int pos_num = 2 + 1 + 2 + 2 + OURPLAYER_NUM * _player_pos_num + THEIRPLAYER_NUM * _player_pos_num;

		_value_getter_mutex->lock();
		calc_with_gpu(_PointPotentialOrigin, _start_pos_cpu, _l, _w, pos_num, _pitch_info);
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

void CGPUBestAlgThread::predictBallPos() {
	//clock_t begin, end;
	//begin = clock();
	
	// _best_visiondata_copy_mutex->lock();
	// 拷贝
	
	for (int i = 0; i < input_dim - 1; i++) {
		_history_ball_vel[i] = _history_ball_vel[i + 1];
	}
	_history_ball_vel[input_dim - 1] = _pVision->Ball().Vel().mod();
	//std::cout << "ball vel: ";
	//for (int i = 0; i < 10; i++) {
	//	std::cout << _history_ball_vel[i] << " ";
	//}
	//std::cout << std::endl;
	// 解锁
	// _best_visiondata_copy_mutex->unlock();

	if (matrix_ok) {
		// set模型的参数
		//int set_status = set_ball_model_param(a_1_matrix_cpu, bias_1_matrix_cpu, a_2_matrix_cpu, bias_2_matrix_cpu);
		//for (int i = 0; i < 5; i++) {
		//	std::cout << a_1_matrix_cpu[i] << " ";
		//}
		//std::cout << std::endl;
		float* results = (float*)malloc(output_dim * sizeof(float));
		ball_model_calc_with_gpu(_history_ball_vel, results, a_1_matrix_cpu, bias_1_matrix_cpu, a_2_matrix_cpu, bias_2_matrix_cpu);

		_ball_pos_prediction_mutex->lock();
		memcpy(_ball_pos_prediction_results, results, output_dim * sizeof(float));
		//for (int i = 0; i < 3; i++) {
		//	std::cout << results[i * 10] << " ";
		//}
		//std::cout << std::endl;
		free(results);
		_ball_pos_prediction_mutex->unlock();
	}

	//end = clock();
	//std::cout << "ball pos predict calc time (GPU): " << double(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

int CGPUBestAlgThread::getBallArea() {
	CGeoPoint ballPos = _pVision->Ball().Pos();
	int advancer = TaskMediator::Instance()->advancer();
	if (advancer != 0)
		ballPos = _pVision->OurPlayer(advancer).Pos();
	int areaNum;
	for (areaNum = 0; areaNum < AREANUM; areaNum++){
		if (gpuCalcArea::processed_fieldRectangleArray[areaNum].check4inclusion(ballPos))
			break;
	}
	return areaNum;
}

// 按照打表的方式返回支撑点列表
void CGPUBestAlgThread::supportSort() {
	int ball_area = getBallArea();
	if (ball_area == AREANUM)
		ball_area = 1; //防止越界，返回对方禁区所在区域
	//           3 0  
	//  己方球门 4 1  敌方球门
	//           5 2
	switch (ball_area)
	{ // 以下注释均为当前重要性排序，球所在区域均为最低优先级
	case 0:
		//           3 球  
		//  己方球门 2 0  敌方球门
		//           4 1
		_bestSupport[0] = _bestPoint[1];
		_bestSupport[1] = _bestPoint[2];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[3];
		_bestSupport[4] = _bestPoint[5];
		_bestSupport[5] = _bestPoint[0];
		break;
	case 1:
		//           3 0
		//  己方球门 2 球  敌方球门
		//           4 1
		_bestSupport[0] = _bestPoint[0];
		_bestSupport[1] = _bestPoint[2];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[3];
		_bestSupport[4] = _bestPoint[5];
		_bestSupport[5] = _bestPoint[1];
		break;
	case 2:
		//           4 1
		//  己方球门 2 0 敌方球门
		//           3 球
		_bestSupport[0] = _bestPoint[1];
		_bestSupport[1] = _bestPoint[0];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[5];
		_bestSupport[4] = _bestPoint[3];
		_bestSupport[5] = _bestPoint[2];
		break;
	case 3:
		//           球1
		//  己方球门 2 0 敌方球门
		//           4 3
		_bestSupport[0] = _bestPoint[1];
		_bestSupport[1] = _bestPoint[0];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[2];
		_bestSupport[4] = _bestPoint[5];
		_bestSupport[5] = _bestPoint[3];
		break;
	case 4:
		//           3 1
		//  己方球门 球0 敌方球门
		//           4 2
		_bestSupport[0] = _bestPoint[1];
		_bestSupport[1] = _bestPoint[0];
		_bestSupport[2] = _bestPoint[2];
		_bestSupport[3] = _bestPoint[3];
		_bestSupport[4] = _bestPoint[5];
		_bestSupport[5] = _bestPoint[4];
		break;
	case 5:
		//           4 3
		//  己方球门 2 0敌方球门
		//           球1
		_bestSupport[0] = _bestPoint[1];
		_bestSupport[1] = _bestPoint[2];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[0];
		_bestSupport[4] = _bestPoint[3];
		_bestSupport[5] = _bestPoint[5];
		break;
	default://假设球在禁区内
		//           3 0
		//  己方球门 2 球  敌方球门
		//           4 1
		_bestSupport[0] = _bestPoint[0];
		_bestSupport[1] = _bestPoint[2];
		_bestSupport[2] = _bestPoint[4];
		_bestSupport[3] = _bestPoint[3];
		_bestSupport[4] = _bestPoint[5];
		_bestSupport[5] = _bestPoint[1];
		break;
	}
}

// 按照点的分值返回支撑点列表
void CGPUBestAlgThread::supportSortV2() {
	int ball_area = getBallArea();
	std::vector<PointValueStruct> pointValueList;
	for (int areaNum = 0; areaNum < AREANUM; areaNum++) {
		if (areaNum != ball_area) { // 不考虑球所在区域
			PointValueStruct p;
			p.pos = areaNum;
			p.value = _pointPotential[areaNum];
			pointValueList.push_back(p);
		}
	}
	sort(pointValueList.begin(), pointValueList.end()); // 排序，从小到大
	int needRemove = (int)(ball_area < AREANUM);
	if (needRemove) { // 将球所在区域的放在最后
		_bestSupport[AREANUM - 1] = _bestPoint[ball_area];
	}
	for (int index = 0; index < AREANUM - needRemove; index++) {
		_bestSupport[index] = _bestPoint[(int)pointValueList.at(index).pos];
	}	
}

CGeoPoint CGPUBestAlgThread::getBestPointFromArea(int support_idx) {
	
	CGeoPoint temp_bestSupport;
	_value_getter_mutex->lock();
	if (support_idx > AREANUM) { // 处理越界情况，但是后三个点的位置并没有生成
		temp_bestSupport = _bestSupport[0];
	}
	else {
		if (support_idx == 0)
			sendFieldRectangle(); // 动态边界debug信息
		temp_bestSupport =  _bestSupport[support_idx];
	}
	_value_getter_mutex->unlock();
	return temp_bestSupport;
}

CGeoPoint CGPUBestAlgThread::getBallPosFromFrame(CGeoPoint ball_pos, CVector ball_vel, int frame) {
	frame = max(min(frame, output_dim - 1), 0);
	float ball_move_dist = 0.0;
	_ball_pos_prediction_mutex->lock();
	ball_move_dist = _ball_pos_prediction_results[frame];
	_ball_pos_prediction_mutex->unlock();
	return ball_pos + ball_vel / (ball_vel.mod() + 1e-8) * ball_move_dist;
}

// 将某一区域内的值变为最大值，从而不被考虑
void CGPUBestAlgThread::erasePointPotentialValue(const CGeoPoint centerPoint, float length, float width) {
	// 场地参数
	// float halfPitchLength = Param::Field::PITCH_LENGTH / 2;
	// float halfPitchWidth = Param::Field::PITCH_WIDTH / 2;
	// 其方法基本与getBestPoint中的相同，只是将搜索变为复制
	// 在坐标系中
	float left_up_pos_x = centerPoint.x() - length / 2;
	float left_up_pos_y = centerPoint.y() - width / 2;
	float right_down_pos_x = centerPoint.x() + length / 2;
	float right_down_pos_y = centerPoint.y() + width / 2;

	// 考虑步长的情况下区域开始的位置
	int start_pos_x_idx = ceil((left_up_pos_x - _start_pos_x) / _step);
	int start_pos_y_idx = ceil((left_up_pos_y - _start_pos_y) / _step);
	// int start_pos_x_idx = ceil((left_up_pos_x + halfPitchLength) / _step);
	// int start_pos_y_idx = ceil((left_up_pos_y + halfPitchWidth) / _step);

	// 考虑步长的情况下区域结束的位置
	int end_pos_x_idx = floor((right_down_pos_x - _start_pos_x) / _step);
	int end_pos_y_idx = floor((right_down_pos_y - _start_pos_y) / _step);
	// int end_pos_x_idx = floor((right_down_pos_x + halfPitchLength) / _step);
	// int end_pos_y_idx = floor((right_down_pos_y + halfPitchWidth) / _step);
	// int end_pos_x_idx = floor((right_down_pos_x - left_up_pos_x) / _step) + start_pos_x_idx;
	// int end_pos_y_idx = floor((right_down_pos_y - left_up_pos_y) / _step) + start_pos_y_idx;

	for (int i = max(start_pos_x_idx, 0); i < min(end_pos_x_idx + 1, _l); i++) {
		for (int j = max(start_pos_y_idx, 0); j < min(end_pos_y_idx + 1, _w); j++) {
			if (i * _w + j >= _w * _l) {
				std::cout << "index error";
			}
			_PointPotential[i * _w + j] = 255;
		}
	}
}

// 计算每个区域的最优点和最优值，在generatePointValue中已经加了进程锁，所以这里没有加，所以这个函数不准在外面调用
void CGPUBestAlgThread::getBestPoint(const CGeoPoint leftUp, const CGeoPoint rightDown, CGeoPoint& bestPoint, float& minValue) {
	// 存下九个区域的最优点以供调用，并且需要记录每个点在当前cycle是否已经更新
#ifdef ENABLE_CUDA
		// 初始化参数
		minValue = 255;
		// 场地参数
		// float halfPitchLength = Param::Field::PITCH_LENGTH / 2;
		// float halfPitchWidth = Param::Field::PITCH_WIDTH / 2;

		// 在坐标系中
		float left_up_pos_x = leftUp.x();
		float left_up_pos_y = leftUp.y();
		float right_down_pos_x = rightDown.x();
		float right_down_pos_y = rightDown.y();

		// 考虑步长的情况下区域开始的位置
		int start_pos_x_idx = ceil((left_up_pos_x - _start_pos_x) / _step);
		int start_pos_y_idx = ceil((left_up_pos_y - _start_pos_y) / _step);
		// int start_pos_x_idx = ceil((left_up_pos_x + halfPitchLength) / _step);
		// int start_pos_y_idx = ceil((left_up_pos_y + halfPitchWidth) / _step);

		// 考虑步长的情况下区域结束的位置
		int end_pos_x_idx = floor((right_down_pos_x - _start_pos_x) / _step);
		int end_pos_y_idx = floor((right_down_pos_y - _start_pos_y) / _step);
		// int end_pos_x_idx = floor((right_down_pos_x + halfPitchLength) / _step);
		// int end_pos_y_idx = floor((right_down_pos_y + halfPitchWidth) / _step);
		// int end_pos_x_idx = floor((right_down_pos_x - left_up_pos_x) / _step) + start_pos_x_idx;
		// int end_pos_y_idx = floor((right_down_pos_y - left_up_pos_y) / _step) + start_pos_y_idx;

		//// 一些点的debug信息
		//float start_pos_x = start_pos_x_idx * _step - halfPitchLength;
		//float start_pos_y = start_pos_y_idx * _step - halfPitchWidth;
		//float end_pos_x = end_pos_x_idx * _step - halfPitchLength;
		//float end_pos_y = end_pos_y_idx * _step - halfPitchWidth;
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(start_pos_x, start_pos_y), COLOR_PURPLE);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(end_pos_x, end_pos_y), COLOR_RED);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(start_pos_x_idx * _step - halfPitchLength, end_pos_y_idx * _step - halfPitchWidth), COLOR_BLUE);
		//GDebugEngine::Instance()->gui_debug_x(CGeoPoint(end_pos_x_idx * _step - halfPitchLength, start_pos_y_idx * _step - halfPitchWidth), COLOR_GREEN);

		for (int i = max(start_pos_x_idx, 0); i < min(end_pos_x_idx + 1, _l); i++) {
		  	for (int j = max(start_pos_y_idx, 0); j < min(end_pos_y_idx + 1, _w); j++) { 
				if (_PointPotential[i * _w + j] <= minValue) { // 分值相同的选择更靠近球门的
					if (_PointPotential[i * _w + j] == minValue) {
						CGeoPoint theirGoal = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
						CGeoPoint temp_bestPoint = CGeoPoint(i * _step + _start_pos_x, j * _step + _start_pos_y);
						if (temp_bestPoint.dist(theirGoal) < bestPoint.dist(theirGoal)) {
							minValue = _PointPotential[i * _w + j];
							bestPoint = temp_bestPoint;
						}
					}
					else {
						minValue = _PointPotential[i * _w + j];
						bestPoint = CGeoPoint(i * _step + _start_pos_x, j * _step + _start_pos_y);
					}
					// bestPoint = CGeoPoint(i * _step - halfPitchLength, j * _step - halfPitchWidth);
				}
			}
		}
#else
		minValue = 255;
		bestPoint = leftUp.midPoint(rightDown);
#endif
}

double CGPUBestAlgThread::limitPosY(double y) {
	return std::min(std::max(y, gpuCalcArea::sideLineLeftBorderY), gpuCalcArea::sideLineRightBorderY);
}

double CGPUBestAlgThread::limitPosX(double x) {
	return std::min(std::max(x, gpuCalcArea::middleBackBorderX), gpuCalcArea::sideLineFrontBorderX);
}

void CGPUBestAlgThread::obscureBoundaryV2() {
	// 移动边界
	double ball_X = _pVision->Ball().Pos().x();
	double ball_Y = _pVision->Ball().Pos().y();
	double avoidBallDist = 100;
	double up_Y = limitPosY(ball_Y - avoidBallDist), down_Y = limitPosY(ball_Y + avoidBallDist);
	float left_X = limitPosX(ball_X - avoidBallDist), right_X = limitPosX(ball_X + avoidBallDist);
	float middle_X = (left_X + right_X) * 0.5;
	float sideLineFrontBorderX = gpuCalcArea::sideLineFrontBorderX - (gpuCalcArea::goalLineFrontBorderX - right_X);
	sideLineFrontBorderX = sideLineFrontBorderX > gpuCalcArea::sideLineFrontBorderX ? gpuCalcArea::sideLineFrontBorderX : sideLineFrontBorderX;
	// 粗分区域，以球为中心前后左右环绕
	gpuCalcArea::processed_fieldRectangleArray[0] = FieldRectangle(CGeoPoint(middle_X, up_Y), CGeoPoint(sideLineFrontBorderX, gpuCalcArea::sideLineLeftBorderY));
	gpuCalcArea::processed_fieldRectangleArray[1] = FieldRectangle(CGeoPoint(right_X, down_Y), CGeoPoint(sideLineFrontBorderX, up_Y));
	gpuCalcArea::processed_fieldRectangleArray[2] = FieldRectangle(CGeoPoint(middle_X, gpuCalcArea::sideLineRightBorderY), CGeoPoint(sideLineFrontBorderX, down_Y));
	gpuCalcArea::processed_fieldRectangleArray[3] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, up_Y), CGeoPoint(middle_X, gpuCalcArea::sideLineLeftBorderY));
	gpuCalcArea::processed_fieldRectangleArray[4] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, down_Y), CGeoPoint(left_X, up_Y));
	gpuCalcArea::processed_fieldRectangleArray[5] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(middle_X, down_Y));
	// gpuCalcArea::processed_fieldRectangleArray[6] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, up_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineLeftBorderY));
	// gpuCalcArea::processed_fieldRectangleArray[7] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, down_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, up_Y));
	// gpuCalcArea::processed_fieldRectangleArray[8] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(gpuCalcArea::middleBackBorderX, down_Y));
	// 矫正区域
	// 挤压左侧区域，右侧区域裂变
	if (up_Y < gpuCalcArea::sideLineLeftBorderY + Param::Vehicle::V2::PLAYER_SIZE * 7) {
		double fixed_Y = (down_Y + gpuCalcArea::sideLineRightBorderY) * 0.5;
		gpuCalcArea::processed_fieldRectangleArray[0] = FieldRectangle(CGeoPoint(middle_X, gpuCalcArea::sideLineRightBorderY), CGeoPoint(sideLineFrontBorderX, fixed_Y));
		gpuCalcArea::processed_fieldRectangleArray[1] = FieldRectangle(CGeoPoint(right_X, down_Y), CGeoPoint(sideLineFrontBorderX, gpuCalcArea::sideLineLeftBorderY));
		gpuCalcArea::processed_fieldRectangleArray[2] = FieldRectangle(CGeoPoint(middle_X, fixed_Y), CGeoPoint(sideLineFrontBorderX, down_Y));
		gpuCalcArea::processed_fieldRectangleArray[3] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(middle_X, fixed_Y));
		gpuCalcArea::processed_fieldRectangleArray[4] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, down_Y), CGeoPoint(left_X, gpuCalcArea::sideLineLeftBorderY));
		gpuCalcArea::processed_fieldRectangleArray[5] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, fixed_Y), CGeoPoint(middle_X, down_Y));
		// gpuCalcArea::processed_fieldRectangleArray[6] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(gpuCalcArea::middleBackBorderX, fixed_Y));
		// gpuCalcArea::processed_fieldRectangleArray[7] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, down_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineLeftBorderY));
		// gpuCalcArea::processed_fieldRectangleArray[8] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, fixed_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, down_Y));
	}
	// 挤压右侧区域，左侧区域裂变
	else if (down_Y > gpuCalcArea::sideLineRightBorderY - Param::Vehicle::V2::PLAYER_SIZE * 7) {
		double fixed_Y = (up_Y + gpuCalcArea::sideLineLeftBorderY) * 0.5;
		gpuCalcArea::processed_fieldRectangleArray[0] = FieldRectangle(CGeoPoint(middle_X, up_Y), CGeoPoint(sideLineFrontBorderX, fixed_Y));
		gpuCalcArea::processed_fieldRectangleArray[1] = FieldRectangle(CGeoPoint(right_X, gpuCalcArea::sideLineRightBorderY), CGeoPoint(sideLineFrontBorderX, up_Y));
		gpuCalcArea::processed_fieldRectangleArray[2] = FieldRectangle(CGeoPoint(middle_X, fixed_Y), CGeoPoint(sideLineFrontBorderX, gpuCalcArea::sideLineLeftBorderY));
		gpuCalcArea::processed_fieldRectangleArray[3] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, up_Y), CGeoPoint(middle_X, fixed_Y));
		gpuCalcArea::processed_fieldRectangleArray[4] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(left_X, up_Y));
		gpuCalcArea::processed_fieldRectangleArray[5] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, fixed_Y), CGeoPoint(middle_X, gpuCalcArea::sideLineLeftBorderY));
		// gpuCalcArea::processed_fieldRectangleArray[6] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, up_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, fixed_Y));
		// gpuCalcArea::processed_fieldRectangleArray[7] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, gpuCalcArea::sideLineRightBorderY), CGeoPoint(gpuCalcArea::middleBackBorderX, up_Y));
		// gpuCalcArea::processed_fieldRectangleArray[8] = FieldRectangle(CGeoPoint(gpuCalcArea::goalLineBackBorderX, fixed_Y), CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::sideLineLeftBorderY));
	}
	// 挤压正前方区域，正后方区域裂变，注意保持之前的矫正
	if (right_X > gpuCalcArea::sideLineFrontBorderX - Param::Vehicle::V2::PLAYER_SIZE * 7) {
		double fixed_X = (left_X + gpuCalcArea::middleBackBorderX) * 0.5;
		gpuCalcArea::processed_fieldRectangleArray[1] = FieldRectangle(gpuCalcArea::processed_fieldRectangleArray[4]._leftDownPos, CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[4]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[4] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[4]._leftDownPos.y()), gpuCalcArea::processed_fieldRectangleArray[4]._rightUpPos);
	}
	// 挤压后侧区域，前方区域裂变并向底线延伸
	else if (left_X < gpuCalcArea::middleBackBorderX + Param::Vehicle::V2::PLAYER_SIZE * 7) {
		double fixed_X = (right_X + gpuCalcArea::sideLineFrontBorderX) * 0.5;
		gpuCalcArea::processed_fieldRectangleArray[4] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[1]._leftDownPos.y()), CGeoPoint(gpuCalcArea::sideLineFrontBorderX, gpuCalcArea::processed_fieldRectangleArray[1]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[1] = FieldRectangle(gpuCalcArea::processed_fieldRectangleArray[1]._leftDownPos, CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[1]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[3] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[0]._leftDownPos.y()), CGeoPoint(gpuCalcArea::sideLineFrontBorderX, gpuCalcArea::processed_fieldRectangleArray[0]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[0] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::processed_fieldRectangleArray[0]._leftDownPos.y()), CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[0]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[5] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[2]._leftDownPos.y()), CGeoPoint(gpuCalcArea::sideLineFrontBorderX, gpuCalcArea::processed_fieldRectangleArray[2]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[2] = FieldRectangle(CGeoPoint(gpuCalcArea::middleBackBorderX, gpuCalcArea::processed_fieldRectangleArray[2]._leftDownPos.y()), CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[2]._rightUpPos.y()));
	}
	// 挤压斜前方区域，不太会出现
	if (middle_X > gpuCalcArea::sideLineFrontBorderX - Param::Vehicle::V2::PLAYER_SIZE * 7) {
		double fixed_X = (middle_X + gpuCalcArea::middleBackBorderX) * 0.5;
		gpuCalcArea::processed_fieldRectangleArray[0] = FieldRectangle(gpuCalcArea::processed_fieldRectangleArray[3]._leftDownPos, CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[3]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[3] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[3]._leftDownPos.y()), CGeoPoint(gpuCalcArea::sideLineFrontBorderX, gpuCalcArea::processed_fieldRectangleArray[3]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[2] = FieldRectangle(gpuCalcArea::processed_fieldRectangleArray[5]._leftDownPos, CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[5]._rightUpPos.y()));
		gpuCalcArea::processed_fieldRectangleArray[5] = FieldRectangle(CGeoPoint(fixed_X, gpuCalcArea::processed_fieldRectangleArray[5]._leftDownPos.y()), CGeoPoint(gpuCalcArea::sideLineFrontBorderX, gpuCalcArea::processed_fieldRectangleArray[5]._rightUpPos.y()));
	}
}

// 动态边界：按照区域边界端点到球的距离向量成比例移动
void CGPUBestAlgThread::obscureBoundary() {
	float ball_X = _pVision->Ball().Pos().x();
	float ball_Y = _pVision->Ball().Pos().y();
	float obsRate = 0.2; // 该函数唯一参数：模糊系数，范围为[0, 1]
	float mov_luX[AREANUM]; float mov_luY[AREANUM];
	float mov_rdX[AREANUM]; float mov_rdY[AREANUM];

	for (int area_idx = 0; area_idx < AREANUM; area_idx++) {
		mov_luX[area_idx] = obsRate * (ball_X - gpuCalcArea::fieldRectangleArray[area_idx]._leftUpPos.x());
		mov_luY[area_idx] = obsRate * (ball_Y - gpuCalcArea::fieldRectangleArray[area_idx]._leftUpPos.y());
		mov_rdX[area_idx] = obsRate * (ball_X - gpuCalcArea::fieldRectangleArray[area_idx]._rightDownPos.x());
		mov_rdY[area_idx] = obsRate * (ball_Y - gpuCalcArea::fieldRectangleArray[area_idx]._rightDownPos.y());//获取区域端点到球的距离向量
		// qDebug() << area_idx << mov_X[area_idx] << mov_Y[area_idx];
	}
	CGeoPoint temp_leftUp;
	CGeoPoint temp_rightDown;
	
	//按顺序重新生成新边界【012345】
	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[0]._leftUpPos.x()    + mov_luX[0], gpuCalcArea::fieldRectangleArray[0]._leftUpPos.y());
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[0]._rightDownPos.x()           , gpuCalcArea::fieldRectangleArray[0]._rightDownPos.y() + mov_rdY[0]);
	gpuCalcArea::processed_fieldRectangleArray[0].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[1]._leftUpPos.x()    + mov_luX[1], gpuCalcArea::fieldRectangleArray[1]._leftUpPos.y()    + mov_luY[1]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[1]._rightDownPos.x() + mov_rdX[1], gpuCalcArea::fieldRectangleArray[1]._rightDownPos.y() + mov_rdY[1]);
	gpuCalcArea::processed_fieldRectangleArray[1].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[2]._leftUpPos.x()    + mov_luX[2], gpuCalcArea::fieldRectangleArray[2]._leftUpPos.y()    + mov_luY[2]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[2]._rightDownPos.x()           , gpuCalcArea::fieldRectangleArray[2]._rightDownPos.y());
	gpuCalcArea::processed_fieldRectangleArray[2].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[3]._leftUpPos.x()    + mov_luX[3], gpuCalcArea::fieldRectangleArray[3]._leftUpPos.y());
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[3]._rightDownPos.x() + mov_rdX[3], gpuCalcArea::fieldRectangleArray[3]._rightDownPos.y() + mov_rdY[3]);
	gpuCalcArea::processed_fieldRectangleArray[3].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[4]._leftUpPos.x()    + mov_luX[4], gpuCalcArea::fieldRectangleArray[4]._leftUpPos.y()    + mov_luY[4]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[4]._rightDownPos.x() + mov_rdX[4], gpuCalcArea::fieldRectangleArray[4]._rightDownPos.y() + mov_rdY[4]);
	gpuCalcArea::processed_fieldRectangleArray[4].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[5]._leftUpPos.x()    + mov_luX[5], gpuCalcArea::fieldRectangleArray[5]._leftUpPos.y()    + mov_luY[5]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[5]._rightDownPos.x() + mov_rdX[5], gpuCalcArea::fieldRectangleArray[5]._rightDownPos.y());
	gpuCalcArea::processed_fieldRectangleArray[5].processField(temp_leftUp, temp_rightDown);

	/*
	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[6]._leftUpPos.x()              , gpuCalcArea::fieldRectangleArray[6]._leftUpPos.y() );
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[6]._rightDownPos.x() + mov_X[6], gpuCalcArea::fieldRectangleArray[6]._rightDownPos.y() + mov_Y[6]);
	gpuCalcArea::processed_fieldRectangleArray[6].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[7]._leftUpPos.x()              , gpuCalcArea::fieldRectangleArray[7]._leftUpPos.y()    + mov_Y[7]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[7]._rightDownPos.x() + mov_X[7], gpuCalcArea::fieldRectangleArray[7]._rightDownPos.y() + mov_Y[7]);
	gpuCalcArea::processed_fieldRectangleArray[7].processField(temp_leftUp, temp_rightDown);

	temp_leftUp    = CGeoPoint(gpuCalcArea::fieldRectangleArray[8]._leftUpPos.x()              , gpuCalcArea::fieldRectangleArray[8]._leftUpPos.y()    + mov_Y[8]);
	temp_rightDown = CGeoPoint(gpuCalcArea::fieldRectangleArray[8]._rightDownPos.x() + mov_X[8], gpuCalcArea::fieldRectangleArray[8]._rightDownPos.y());
	gpuCalcArea::processed_fieldRectangleArray[8].processField(temp_leftUp, temp_rightDown);
	*/


	return;
}

void CGPUBestAlgThread::increaseRobust() {
	cum = (cum+1)%10;
	if (abs(_prePointPotential[0] - _pointPotential[0]) < thresholdValue)
	{
		for (int i = 0; i < AREANUM; i++) {
			_bestSupport[i] = _preBestSupport[i];
			_pointPotential[i] = _prePointPotential[i];
		}
	}
	for (int i = 0; cum == 0 && i < AREANUM; i++) {
		_preBestSupport[i] = _bestSupport[i];
		_prePointPotential[i] = _pointPotential[i];
	}
}


// 处理每个区域，在generatePointValue中已经加了进程锁，所以这里没有加，所以这个函数不准在外面调用
void CGPUBestAlgThread::processPointValue() {
	// 对_PointPotential数据进行处理，并找出前六区域中的最优值，并存储在_bestPoint中
	AreaStructList areaStructList;
	CGeoPoint bestPoint;
	float minValue;
	int area_idx;

	if (ParamManager::Instance()->boundaryVersion == 1) {
		obscureBoundary(); //动态模糊边界
	}
	else if (ParamManager::Instance()->boundaryVersion == 2) {
		obscureBoundaryV2();
	}


	// 搜索出所有区域的暂时最优点
	for (int area_idx = 0; area_idx < AREANUM; area_idx++) {
		getBestPoint(gpuCalcArea::processed_fieldRectangleArray[area_idx].centerArea()._leftUpPos, gpuCalcArea::processed_fieldRectangleArray[area_idx].centerArea()._rightDownPos, bestPoint, minValue);
		areaStructList.push_back(AreaStruct(bestPoint, minValue, area_idx, false));
	}

	while (areaStructList.size()) {
		// 先排序，从小到大
		sort(areaStructList.begin(), areaStructList.end());
		// 判断value最小的点是否被已选定点冲突
		if (areaStructList.at(0)._conflict) { // 如果冲突，重新计算该点，并更新该点信息
			area_idx = areaStructList.at(0)._area_idx;
			getBestPoint(gpuCalcArea::processed_fieldRectangleArray[area_idx].centerArea()._leftUpPos, gpuCalcArea::processed_fieldRectangleArray[area_idx].centerArea()._rightDownPos, bestPoint, minValue);
			areaStructList.at(0)._pos = bestPoint;
			areaStructList.at(0)._value = minValue;
			areaStructList.at(0)._conflict = false;
		}
		else { // 如果不冲突，将该点移出队列存放至规划点数组中，根据该点对场势进行erase并重新判断其余点是否冲突
			minValue = areaStructList.at(0)._value;
			bestPoint = areaStructList.at(0)._pos;
			area_idx = areaStructList.at(0)._area_idx;
			areaStructList.pop_front();
			_pointPotential[area_idx] = minValue;
			_bestPoint[area_idx] = bestPoint;
			// 判断是否已经全部移出队列，由于该操作，因此最后一个点并不会earse区域
			if (areaStructList.empty()) {
				break;
			}
			else {
				float length = 130; // 200;
				float width = 130; // 200;
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

	// if (ParamManager::Instance()->boundaryVersion == 1) {
	 	supportSortV2(); // 按照重要性对支撑点进行排序	
	// }
	// else if (ParamManager::Instance()->boundaryVersion == 2) {
	// 	supportSortV2(); 
	// }
	// increaseRobust(); // 防止跳变的设定，从0开始进行筛选

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
		GPUBestAlgThread::Instance()->predictBallPos();
		// GPUBestAlgThread::Instance()->sendFieldRectangle();
		GPUBestAlgThread::Instance()->setPointValue();
        GPUBestAlgThread::Instance()->sendPointValue();
	}
}

double CGPUBestAlgThread::getPosPotential(const CGeoPoint p) {
	return 0;
}

void CGPUBestAlgThread::setPointValue() {
	// _value_getter_mutex->lock();
	pointValueList.clear();
	int size = _l * _w;
	for (int i = 0; i < size; i++) {
		if (_PointPotentialOrigin[i] < 0) _PointPotentialOrigin[i] = 0;
		else if (_PointPotentialOrigin[i] > 255) _PointPotentialOrigin[i] = 255;
		PointValueStruct p;
		p.pos = i;
		p.value = _PointPotentialOrigin[i];
		pointValueList.push_back(p);
	}
	// _value_getter_mutex->unlock();
}

void CGPUBestAlgThread::sendPointValue() {
	//将点均分为若干个颜色,现在情况为把所有点按分值大小分配为256部分，每部分对应一个颜色
	//排序，从大到小
	sort(pointValueList.begin(), pointValueList.end(), greater<PointValueStruct>());
	int point_size = pointValueList.size();
    //Heat_Map msgs;
    OWL::Protocol::Heat_Map_New msgs;
	for (int m = gpuCalcArea::Color_Size - 1; m >= 0; m--) { //先把重要的点发过去，分值较小的
		msgs.set_login_name(OParamManager::Instance()->LoginName);
		auto points = msgs.add_points();
		for (int n = m * point_size / gpuCalcArea::Color_Size; n < (m + 1) * point_size / gpuCalcArea::Color_Size; n++) {
			points->add_pos(pointValueList.at(n).pos);
			points->set_color(255 - pointValueList.at(n).value);
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

int CGPUBestAlgThread::getMatrix(const string file_name, int max_row_num, int max_col_num, float* matrix)
{
	ifstream file_stream;
	string one_line = "";	//输入文件的某一行
	double tmp = 0;		//当前位置上的数值
	int row_count = 0;	// 行数计数器
	int col_count = 0;	// 列数计数器
	int max_index = max_row_num * (max_col_num - 1) - 1;
	string line;

	// 打开文件
	file_stream.open(file_name, ios::in);	//ios::in 表示以只读的方式读取文件
	if (file_stream.fail()){ //文件打开失败:返回0
		cout << "matrix: " << file_name << "doesn't exit." << endl;
		file_stream.close();
		system("pause");
		return 0;
	}

	while (getline(file_stream, line)) // line中不包括每行的换行符
	{
		string number;
		istringstream readstr(line); //string数据流化
		//将一行数据按'，'分割
		for (int col = 0; col < max_col_num; col++) { //可根据数据的实际情况取循环获取
			getline(readstr, number, ' '); //循环读取数据
			int index = row_count * max_col_num + col;
			matrix[index] = atof(number.c_str());
		}
		row_count++;
	}
	return 1;
}// END OF getInputData

void CGPUBestAlgThread::sendFieldRectangle() {
	//区域边界debug信息
	for (int i = 0; i < AREANUM; i++) {
		CGeoPoint leftUpPos = gpuCalcArea::processed_fieldRectangleArray[i]._leftUpPos;
		CGeoPoint rightUpPos = gpuCalcArea::processed_fieldRectangleArray[i]._rightUpPos;
		CGeoPoint leftDownPos = gpuCalcArea::processed_fieldRectangleArray[i]._leftDownPos;
		CGeoPoint rightDownPos = gpuCalcArea::processed_fieldRectangleArray[i]._rightDownPos;
		CGeoPoint centerPos = gpuCalcArea::processed_fieldRectangleArray[i].getCenter();
		/*
		GDebugEngine::Instance()->gui_debug_line(leftUpPos, rightUpPos, COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_line(rightUpPos, rightDownPos, COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_line(rightDownPos, leftDownPos, COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_line(leftDownPos, leftUpPos, COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_x(_bestSupport[i], COLOR_WHITE);
		GDebugEngine::Instance()->gui_debug_msg(_bestSupport[i], QString::number(i).toStdString().c_str(), COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_msg(centerPos, QString::number(_pointPotential[i]).toStdString().c_str(), COLOR_BLACK);
		*/
	}
	//支撑点顺序debug信息
	/*
	//GDebugEngine::Instance()->gui_debug_msg(_bestSupport[0], QString::number(cum).toStdString().c_str(), COLOR_BLACK);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[0], "000", COLOR_YELLOW);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[1], "111", COLOR_YELLOW);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[2], "222", COLOR_YELLOW);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[3], "333", COLOR_YELLOW);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[4], "444", COLOR_YELLOW);
	GDebugEngine::Instance()->gui_debug_msg(_bestSupport[5], "555", COLOR_YELLOW);
	*/
}
