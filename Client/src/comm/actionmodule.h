#ifndef CACTIONMODULE_H
#define CACTIONMODULE_H
#include <QSerialPort>
#include <singleton.h>
#include "zss_cmd.pb.h"
#include "staticparams.h"
namespace Owl {
	class CActionModule : public QObject
	{
		Q_OBJECT
	public:
		CActionModule(QObject* parent = 0);
		~CActionModule();
		bool changeFrequency(int);
        int getFrequency() { return frequency; }
        int getMaxFrequency() { return 9; }
        QStringList& updatePortsList();
        bool changePorts(int);
        std::string getSerialPort() { return serial.portName().toStdString(); }
        bool openSerialPort();
        bool closeSerialPort();
        void updateCommandParams(int, int, int, int, bool, int, bool, bool, int);
        bool sendLegacy(int);
        bool encode(int);
        bool encodeNew(int);
        QSerialPort serial;
    signals:
        void receiveRobotInfo(int, int);
    private slots:
        void readData();
    private:
        void sendStartPacket();
    private:
        QStringList ports;
        int frequency;
        QByteArray tx;
        QByteArray rx;
        bool shoot[PARAM::ROBOTMAXID];
        bool ctrl[PARAM::ROBOTMAXID];
        bool shootMode[PARAM::ROBOTMAXID];//false is "flat shoot" and true is "lift shoot".
        int robotID[PARAM::ROBOTMAXID];
        int velX[PARAM::ROBOTMAXID];
        int velY[PARAM::ROBOTMAXID];
        int velR[PARAM::ROBOTMAXID];
        int ctrlPowerLevel[PARAM::ROBOTMAXID];
        int shootPowerLevel[PARAM::ROBOTMAXID];
    };
    typedef Falcon::MeyersSingleton<CActionModule> ActionModule;
}
#endif // CACTIONMODULE_H