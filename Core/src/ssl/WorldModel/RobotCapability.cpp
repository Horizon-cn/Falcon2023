#include "WorldModel/RobotCapability.h"
#include "ParamManagerNew.h"

namespace{
	class OmniAuto{
	protected:
		OmniAuto()
		{
            MAX_TRANSLATION_SPEED_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_SPEED_GOALIE;
            MAX_TRANSLATION_ACC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_ACC_GOALIE;
            MAX_TRANSLATION_DEC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_DEC_GOALIE;
            MAX_ROTATION_ACC_GOALIE = ParamManager::Instance()->MAX_ROTATION_ACC_GOALIE;
            MAX_ROTATION_SPEED_GOALIE = ParamManager::Instance()->MAX_ROTATION_SPEED_GOALIE;

            // 后卫单独控制平动参数
            MAX_TRANSLATION_SPEED_BACK = ParamManager::Instance()->MAX_TRANSLATION_SPEED_BACK;
            MAX_TRANSLATION_ACC_BACK = ParamManager::Instance()->MAX_TRANSLATION_ACC_BACK;
            MAX_TRANSLATION_DEC_BACK = ParamManager::Instance()->MAX_TRANSLATION_DEC_BACK;
            MAX_ROTATION_ACC_BACK = ParamManager::Instance()->MAX_ROTATION_ACC_BACK;
            MAX_ROTATION_SPEED_BACK = ParamManager::Instance()->MAX_ROTATION_SPEED_BACK;

            // 其他车的平动参数
            MAX_TRANSLATION_SPEED = ParamManager::Instance()->MAX_TRANSLATION_SPEED;
            MAX_TRANSLATION_ACC = ParamManager::Instance()->MAX_TRANSLATION_ACC;
            MAX_TRANSLATION_DEC = ParamManager::Instance()->MAX_TRANSLATION_DEC;

            MAX_ROTATION_SPEED = ParamManager::Instance()->MAX_ROTATION_SPEED;
            MAX_ROTATION_ACC = ParamManager::Instance()->MAX_ROTATION_ACC;

            TRANSLATION_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ACC_LIMIT;
            TRANSLATION_SPEED_LIMIT = ParamManager::Instance()->TRANSLATION_SPEED_LIMIT;
            TRANSLATION_ROTATE_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ROTATE_ACC_LIMIT;
		}

		double maxSpeedGoalie(const double angle) const { return MAX_TRANSLATION_SPEED_GOALIE; }
		double maxAccelerationGoalie(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_ACC_GOALIE; }
		double maxDecGoalie(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_DEC_GOALIE; }

		double maxSpeedBack(const double angle) const { return MAX_TRANSLATION_SPEED_BACK; }
		double maxAccelerationBack(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_ACC_BACK; }
		double maxDecBack(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_DEC_BACK; }

		double maxSpeed(const double angle) const { return MAX_TRANSLATION_SPEED; }
		double maxAcceleration(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_ACC; }
		double maxDec(const CVector& velocity, const double angle) const { return MAX_TRANSLATION_DEC; }

		double maxAngularSpeed() const { return MAX_ROTATION_SPEED; }
		double maxAngularAcceleration() const { return MAX_ROTATION_ACC; }
		double maxAngularDec() const { return MAX_ROTATION_DEC; }
		
	private:
		double TRANSLATION_SPEED_LIMIT;//最大速度
		double TRANSLATION_ACC_LIMIT;
		double TRANSLATION_ROTATE_ACC_LIMIT;

		double MAX_TRANSLATION_SPEED;
		double MAX_TRANSLATION_ACC;	//最大加速度
		double MAX_TRANSLATION_DEC;	//最大减速度
		double MAX_ROTATION_SPEED;			//最大角速度
		double MAX_ROTATION_ACC;	//最大角加速度
		double MAX_ROTATION_DEC;	//最大角减速度

		/// 守门员专用
		double MAX_TRANSLATION_SPEED_GOALIE;
		double MAX_TRANSLATION_ACC_GOALIE;
		double MAX_TRANSLATION_DEC_GOALIE;
		double MAX_ROTATION_ACC_GOALIE;
		double MAX_ROTATION_SPEED_GOALIE;

		/// 后卫专用
		double MAX_TRANSLATION_SPEED_BACK;
		double MAX_TRANSLATION_ACC_BACK;
		double MAX_TRANSLATION_DEC_BACK;
		double MAX_ROTATION_ACC_BACK;
		double MAX_ROTATION_SPEED_BACK;
	};
	
	// 挑球的特性
	class ChipKick{ // 有挑球装置
	protected:
		ChipKick() : ChipKickEnabled(true), MinChipKickObstacleDist(10), MaxChipKickDist(300), MaxChipShootDist(180), 
						MinChipShootExtra(20)
		{}
		double minChipKickObstacleDist() const { return ChipKickEnabled ? MinChipKickObstacleDist : 100000; }
		double maxChipKickDist() const { return MaxChipKickDist; }
		double maxChipShootDist() const { return MaxChipShootDist; }
		double minChipShootExtra(const double dist) const { return MinChipShootExtra; }
	private:
		bool ChipKickEnabled; // 是否开启ChipKick
		double MinChipKickObstacleDist;
		double MaxChipKickDist;
		double MaxChipShootDist;
		double MinChipShootExtra;
	};
	
	// 击球的特性
	class KickAuto{
	protected:
		KickAuto() : MinShootAngleWidth(Param::Field::BALL_SIZE*1.5)
		{}
		double minShootAngleWidth() const { return MinShootAngleWidth; }
	private:
		double MinShootAngleWidth;
	};

	template < class MovingCap, class KickCap, class ChipKickCap>
	class ConcretRobotCapability : public CRobotCapability, MovingCap, KickCap, ChipKickCap{
	public:
		virtual double minShootAngleWidth() const { return KickCap::minShootAngleWidth(); }

		virtual double minChipKickObstacleDist() const { return ChipKickCap::minChipKickObstacleDist(); }
		virtual double maxChipKickDist() const { return ChipKickCap::maxChipKickDist(); }
		virtual double maxChipShootDist() const { return ChipKickCap::maxChipShootDist(); }
		virtual double minChipShootExtra(const double dist) const { return ChipKickCap::minChipShootExtra(dist); }
		
		virtual double maxAccelerationGoalie(const CVector& velocity, const double angle) const { return MovingCap::maxAccelerationGoalie(velocity, angle); }
		virtual double maxDecGoalie(const CVector& velocity, const double angle) const { return MovingCap::maxDecGoalie(velocity, angle);}
		virtual double maxSpeedGoalie(const double angle) const { return MovingCap::maxSpeedGoalie(angle); }

		virtual double maxAccelerationBack(const CVector& velocity, const double angle) const { return MovingCap::maxAccelerationBack(velocity, angle); }
		virtual double maxDecBack(const CVector& velocity, const double angle) const { return MovingCap::maxDecBack(velocity, angle);}
		virtual double maxSpeedBack(const double angle) const { return MovingCap::maxSpeedBack(angle); }

		virtual double maxAcceleration(const CVector& velocity, const double angle) const { return MovingCap::maxAcceleration(velocity, angle); }
		virtual double maxDec(const CVector& velocity, const double angle) const { return MovingCap::maxDec(velocity, angle);}
		virtual double maxSpeed(const double angle) const { return MovingCap::maxSpeed(angle); }

		virtual double maxAngularAcceleration() const { return MovingCap::maxAngularAcceleration(); }
		virtual double maxAngularDec() const { return MovingCap::maxAngularDec();}
		virtual double maxAngularSpeed() const { return MovingCap::maxAngularSpeed(); }
	};
}
CRobotCapFactory::CRobotCapFactory()
{
	// 初始化每个车的能力，注意,每次比赛前要检查此处! 看是否正确
	typedef ConcretRobotCapability< OmniAuto, KickAuto, ChipKick > VehicleAuto;
	
	_robotCaps.push_back(new VehicleAuto); // 类型0

	// 小车的类型, 0表示10系的, 1表示9系的
	for( int i=0; i<Param::Field::MAX_PLAYER; ++i ){
		LeftRobotType[i] = 0;
		RightRobotType[i] = 0;
	}
}

