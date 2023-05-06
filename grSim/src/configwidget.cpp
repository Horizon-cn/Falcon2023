/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "configwidget.h"

#define ADD_ENUM(type,name,Defaultvalue,namestring) \
    v_##name = std::shared_ptr<Var##type>(new Var##type(namestring,Defaultvalue));
#define ADD_VALUE(parent,type,name,defaultvalue,namestring) \
    v_##name = std::shared_ptr<Var##type>(new Var##type(namestring,defaultvalue)); \
    parent->addChild(v_##name);

#define END_ENUM(parents, name) \
    parents->addChild(v_##name);
#define ADD_TO_ENUM(name,str) \
    v_##name->addItem(str);


ConfigWidget::ConfigWidget()
{ 
    auto opm = OParamManager::Instance();
    auto cpm = CParamManager::Instance();
    auto vpm = VParamManager::Instance();
    auto spm = SParamManager::Instance();
    opm->setFileName();
    cpm->setFileName();
    vpm->setFileName();
    spm->setFileName();
    
  tmodel=new VarTreeModel();
  this->setModel(tmodel);
  use_vars = VarListPtr(new VarList("User"));
  world.push_back(use_vars); 
  ADD_VALUE(use_vars,String,LoginName,opm->value("Alert", "LoginName", "SRC").toString().toStdString(),"LoginName")
  geo_vars = VarListPtr(new VarList("Geometry"));
  world.push_back(geo_vars);  
  robot_settings = new QSettings;

  VarListPtr game_vars(new VarList("Game"));
  geo_vars->addChild(game_vars);
  std::string type = opm->value("Alert", "field", "Division_A").toString() == "Division_B" ? "Division B" : "Division A";
  ADD_ENUM(StringEnum, Division, type, "Division")
  ADD_TO_ENUM(Division, "Division A");
  ADD_TO_ENUM(Division, "Division B");
  END_ENUM(game_vars, Division);
  ADD_VALUE(game_vars,Intz, Robots_Count, spm->value("Game/Robots_Count", 8).toInt(), "Robots Count")
  VarListPtr fields_vars(new VarList("Field"));
  VarListPtr div_a_vars(new VarList("Division A"));
  VarListPtr div_b_vars(new VarList("Division B"));
  geo_vars->addChild(fields_vars);
  fields_vars->addChild(div_a_vars);
  fields_vars->addChild(div_b_vars);

  ADD_VALUE(div_a_vars, Double, DivA_Field_Line_Width,0.001*opm->value("Division_A/field_line_width", 10).toDouble(),"Line Thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Length,0.001*opm->value("Division_A/field_length", 12000).toDouble(),"Length")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Width,0.001*opm->value("Division_A/field_width", 9000).toDouble(),"Width")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Rad,0.001*opm->value("Division_A/center_radius", 500).toDouble(),"Radius")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Free_Kick,0.001*opm->value("Division_A/field_free_kick", 700).toDouble(),"Free Kick Distance From Defense Area")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Width,0.001*opm->value("Division_A/penalty_width", 2400).toDouble(),"Penalty width")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Depth,0.001*opm->value("Division_A/penalty_depth", 1200).toDouble(),"Penalty depth")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Point,0.001*opm->value("Division_A/penalty_point", 1200).toDouble(),"Penalty point")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Margin,0.001*opm->value("Division_A/field_margin", 300).toDouble(),"Margin")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Referee_Margin,0.001*opm->value("Division_A/field_referee_margin", 400).toDouble(),"Referee margin")
  ADD_VALUE(div_a_vars, Double, DivA_Wall_Thickness,0.001*opm->value("Division_A/wall_thickness", 50).toDouble(),"Wall thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Thickness,0.001*opm->value("Division_A/goal_thickness", 20).toDouble(),"Goal thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Depth,0.001*opm->value("Division_A/goal_depth", 200).toDouble(),"Goal depth")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Width,0.001*opm->value("Division_A/goal_width", 1200).toDouble(),"Goal width")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Height,0.001*opm->value("Division_A/goal_height", 160).toDouble(),"Goal height")
  ADD_VALUE(div_a_vars, Double, overlap,0.001*opm->value("Division_A/camera_overlap", 200).toDouble(),"Camera Overlap")

  ADD_VALUE(div_b_vars, Double, DivB_Field_Line_Width,0.001*opm->value("Division_B/field_line_width", 10).toDouble(),"Line Thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Length, 0.001 * opm->value("Division_B/field_length", 9000).toDouble(),"Length")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Width, 0.001 * opm->value("Division_B/field_width", 6000).toDouble(),"Width")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Rad, 0.001 * opm->value("Division_B/center_radius", 500).toDouble(),"Radius")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Free_Kick, 0.001 * opm->value("Division_B/field_free_kick", 700).toDouble(),"Free Kick Distance From Defense Area")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Width, 0.001 * opm->value("Division_B/penalty_width", 2000).toDouble(),"Penalty width")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Depth, 0.001 * opm->value("Division_B/penalty_depth", 1000).toDouble(),"Penalty depth")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Point, 0.001 * opm->value("Division_B/penalty_point", 1000).toDouble(),"Penalty point")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Margin, 0.001 * opm->value("Division_B/field_margin", 300).toDouble(),"Margin")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Referee_Margin, 0.001 * opm->value("Division_B/field_referee_margin", 400).toDouble(),"Referee margin")
  ADD_VALUE(div_b_vars, Double, DivB_Wall_Thickness, 0.001 * opm->value("Division_B/wall_thickness", 50).toDouble(),"Wall thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Thickness, 0.001 * opm->value("Division_B/goal_thickness", 20).toDouble(),"Goal thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Depth, 0.001 * opm->value("Division_B/goal_depth", 200).toDouble(),"Goal depth")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Width, 0.001 * opm->value("Division_B/goal_width", 1000).toDouble(),"Goal width")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Height, 0.001 * opm->value("Division_B/goal_height", 160).toDouble(),"Goal height")

  ADD_ENUM(StringEnum,YellowTeam,spm->value("Team", "blueTeam", "SRC").toString().toStdString(),"Yellow Team");
  END_ENUM(geo_vars,YellowTeam)
  ADD_ENUM(StringEnum,BlueTeam,spm->value("Team", "yellowTeam", "SRC").toString().toStdString(),"Blue Team");
  END_ENUM(geo_vars,BlueTeam)

    VarListPtr ballg_vars(new VarList("Ball"));
    geo_vars->addChild(ballg_vars);
        ADD_VALUE(ballg_vars,Double,BallRadius,spm->value("Ball/BallRadius", 0.0215).toDouble(),"Radius")
  VarListPtr phys_vars(new VarList("Physics"));
  world.push_back(phys_vars);
    VarListPtr worldp_vars(new VarList("World"));
    phys_vars->addChild(worldp_vars);
        ADD_VALUE(worldp_vars,Intz,NumOfCam,opm->value("Camera/total_cameras", 1).toInt(),"The number of cameras")
        ADD_VALUE(worldp_vars,Double,DesiredFPS,spm->value("World/DesiredFPS", 75).toDouble(),"Desired FPS")
        ADD_VALUE(worldp_vars,Bool,SyncWithGL,spm->value("World", "SyncWithGL", false).toBool(),"Synchronize ODE with OpenGL")
        ADD_VALUE(worldp_vars,Double,DeltaTime,spm->value("World/DeltaTime", 0.016).toDouble(),"ODE time step")
        ADD_VALUE(worldp_vars,Double,Gravity,spm->value("World/Gravity", 9.8).toDouble(),"Gravity")
        ADD_VALUE(worldp_vars,Bool,ResetTurnOver,spm->value("World/ResetTurnOver", true).toBool(),"Auto reset turn-over")
		ADD_VALUE(worldp_vars, Bool, EnableYellowSim,spm->value("World/EnableYellowSim", true).toBool(), "Enable Yellow Simulator")		//xjw
		ADD_VALUE(worldp_vars, Bool, EnableWallSim,spm->value("World/EnableWallSim", true).toBool(), "Enable Wall Simulator")			//xjw
  VarListPtr ballp_vars(new VarList("Ball"));
    phys_vars->addChild(ballp_vars);
        ADD_VALUE(ballp_vars,Double,BallMass,spm->value("Ball/BallMass", 0.043).toDouble(),"Ball mass");
        ADD_VALUE(ballp_vars,Double,BallFriction,spm->value("Ball/BallFriction", 0.1).toDouble(),"Ball-ground friction")
        ADD_VALUE(ballp_vars,Double,BallSlip,spm->value("Ball/BallSlip", 1).toDouble(),"Ball-ground slip")
        ADD_VALUE(ballp_vars,Double,BallBounce,spm->value("Ball/BallBounce", 0.5).toDouble(),"Ball-ground bounce factor")
        ADD_VALUE(ballp_vars,Double,BallBounceVel,spm->value("Ball/BallBounceVel", 0.1).toDouble(),"Ball-ground bounce min velocity")
        ADD_VALUE(ballp_vars,Double,BallLinearDamp,spm->value("Ball/BallLinearDamp", 0.004).toDouble(),"Ball linear damping")
        ADD_VALUE(ballp_vars,Double,BallAngularDamp,spm->value("Ball/BallAngularDamp", 0.004).toDouble(),"Ball angular damping")
  VarListPtr comm_vars(new VarList("Communication"));
  world.push_back(comm_vars);
    ADD_VALUE(comm_vars,String,VisionMulticastAddr,cpm->value("IP", "ssl_address", "224.5.23.2").toString().toStdString(),"Vision multicast address")  //SSL Vision: "224.5.23.2"
    ADD_VALUE(comm_vars,Intz,VisionMulticastPort,opm->value("AlertPorts/VisionSim", 10020).toInt(),"Vision multicast port")
    ADD_VALUE(comm_vars,Intz,CommandListenPort,cpm->value("Ports/sim_send", 20011).toInt(),"Command listen port")
    ADD_VALUE(comm_vars,Intz,BlueStatusSendPort,cpm->value("Ports/blue_status", 30011).toInt(),"Blue Team status send port")
    ADD_VALUE(comm_vars,Intz,YellowStatusSendPort,cpm->value("Ports/yellow_status", 30012).toInt(),"Yellow Team status send port")
    ADD_VALUE(comm_vars,Intz,sendDelay,spm->value("Communication", "sendDelay", 0).toInt(),"Sending delay (milliseconds)")
    ADD_VALUE(comm_vars,Intz,sendGeometryEvery,spm->value("Communication/sendGeometryEvery", 120).toInt(),"Send geometry every X frames")
    ADD_VALUE(comm_vars, Bool, wheelSpeedCallBack, spm->value("Communication", "wheelSpeedCallBack", false).toBool(), "Send wheelSpeed every frame")
    VarListPtr gauss_vars(new VarList("Gaussian noise"));
        comm_vars->addChild(gauss_vars);
        ADD_VALUE(gauss_vars,Bool,noise,spm->value("Noise", "noise", false).toBool(),"Noise")
        ADD_VALUE(gauss_vars,Double,bot_noiseDeviation_x,spm->value("Noise/bot_noiseDeviation_x", 3).toDouble(),"Bot Deviation for x values")
        ADD_VALUE(gauss_vars,Double,bot_noiseDeviation_y,spm->value("Noise/bot_noiseDeviation_y", 3).toDouble(),"Bot Deviation for y values")
        ADD_VALUE(gauss_vars,Double,bot_noiseDeviation_angle,spm->value("Noise/bot_noiseDeviation_angle", 2).toDouble(),"Bot Deviation for angle values")
		ADD_VALUE(gauss_vars, Double, ball_noiseDeviation_x, spm->value("Noise/ball_noiseDeviation_x", 3).toDouble(), "Ball Deviation for x values")
		ADD_VALUE(gauss_vars, Double, ball_noiseDeviation_y, spm->value("Noise/ball_noiseDeviation_y", 3).toDouble(), "Ball Deviation for y values")
    VarListPtr vanishing_vars(new VarList("Vanishing probability"));
        comm_vars->addChild(vanishing_vars);
        ADD_VALUE(gauss_vars,Bool,vanishing,spm->value("Vanishing", "vanishing", false).toBool(),"Vanishing")
        ADD_VALUE(vanishing_vars,Double,blue_team_vanishing,spm->value("Vanishing", "blue_team_vanishing", 0).toDouble(),"Blue team")
        ADD_VALUE(vanishing_vars,Double,yellow_team_vanishing,spm->value("Vanishing", "yellow_team_vanishing", 0).toDouble(),"Yellow team")
        ADD_VALUE(vanishing_vars,Double,ball_vanishing,spm->value("Vanishing", "ball_vanishing", 0).toDouble(),"Ball")

    //world=VarXML::read(world,(qApp->applicationDirPath() + QString("/../data/config/") + QString(".grsim.xml")).toStdString());

    QDir dir;
    std::string blueteam = v_BlueTeam->getString();
    geo_vars->removeChild(v_BlueTeam);

    std::string yellowteam = v_YellowTeam->getString();
    geo_vars->removeChild(v_YellowTeam);

    ADD_ENUM(StringEnum,BlueTeam,blueteam.c_str(),"Blue Team");
    ADD_ENUM(StringEnum,YellowTeam,yellowteam.c_str(),"Yellow Team");

    dir.setCurrent(qApp->applicationDirPath()+"/../data/config/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QStringList s = fileInfo.fileName().split(".");
        QString str;
        if (s.count() > 0) str = s[0];
        ADD_TO_ENUM(BlueTeam,str.toStdString())
        ADD_TO_ENUM(YellowTeam,str.toStdString())
    }
    /**dir.setCurrent(qApp->applicationDirPath()+"/../share/grsim/config/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QStringList s = fileInfo.fileName().split(".");
        QString str;
        if (s.count() > 0) str = s[0];
        ADD_TO_ENUM(BlueTeam,str.toStdString())
        ADD_TO_ENUM(YellowTeam,str.toStdString())
    }**/

    END_ENUM(geo_vars,BlueTeam)
    END_ENUM(geo_vars,YellowTeam)

  v_BlueTeam->setString(blueteam);
  v_YellowTeam->setString(yellowteam);

  tmodel->setRootItems(world);

  this->expandAndFocus(geo_vars);
  this->expandAndFocus(phys_vars);
  this->expandAndFocus(comm_vars);

  this->fitColumns();

  resize(320,400);
  connect(v_BlueTeam.get(), SIGNAL(wasEdited(VarPtr)), this, SLOT(loadRobotsSettings()));
  connect(v_YellowTeam.get(), SIGNAL(wasEdited(VarPtr)), this, SLOT(loadRobotsSettings()));
  loadRobotsSettings();
}

ConfigWidget::~ConfigWidget() {
    //VarXML::write(world,(qApp->applicationDirPath() + QString("/../data/config/") + QString(".grsim.xml")).toStdString());
}


ConfigDockWidget::ConfigDockWidget(QWidget* _parent,ConfigWidget* _conf) : QDockWidget("Read-only Parameter", _parent) 
{
    parent=_parent;conf=_conf;
    setWidget(conf);
    conf->move(0,20);
}  
void ConfigDockWidget::closeEvent(QCloseEvent* event)
{
    emit closeSignal(false);
}


void ConfigWidget::loadRobotsSettings()
{
    loadRobotSettings(YellowTeam().c_str());
    yellowSettings = robotSettings;
    loadRobotSettings(BlueTeam().c_str());
    blueSettings = robotSettings;
}

void ConfigWidget::loadRobotSettings(QString team)
{
    QString ss = qApp->applicationDirPath()+QString("/../data/config/")+QString("%1.ini").arg(team);
    robot_settings = new QSettings(ss, QSettings::IniFormat);
    robotSettings.RobotCenterFromKicker = robot_settings->value("Geometery/CenterFromKicker", 0.073).toDouble();
    robotSettings.RobotRadius = robot_settings->value("Geometery/Radius", 0.09).toDouble();
    robotSettings.RobotHeight = robot_settings->value("Geometery/Height", 0.13).toDouble();
    robotSettings.BottomHeight = robot_settings->value("Geometery/RobotBottomZValue", 0.02).toDouble();
    robotSettings.KickerZ = robot_settings->value("Geometery/KickerZValue", 0.005).toDouble();
    robotSettings.KickerThickness = robot_settings->value("Geometery/KickerThickness", 0.005).toDouble();
    robotSettings.KickerWidth = robot_settings->value("Geometery/KickerWidth", 0.08).toDouble();
    robotSettings.KickerHeight = robot_settings->value("Geometery/KickerHeight", 0.04).toDouble();
    robotSettings.WheelRadius = robot_settings->value("Geometery/WheelRadius", 0.0325).toDouble();
    robotSettings.WheelThickness = robot_settings->value("Geometery/WheelThickness", 0.005).toDouble();
    robotSettings.Wheel1Angle = robot_settings->value("Geometery/Wheel1Angle", 60).toDouble();
    robotSettings.Wheel2Angle = robot_settings->value("Geometery/Wheel2Angle", 135).toDouble();
    robotSettings.Wheel3Angle = robot_settings->value("Geometery/Wheel3Angle", 225).toDouble();
    robotSettings.Wheel4Angle = robot_settings->value("Geometery/Wheel4Angle", 300).toDouble();

    robotSettings.BodyMass  = robot_settings->value("Physics/BodyMass", 2).toDouble();
    robotSettings.WheelMass = robot_settings->value("Physics/WheelMass", 0.2).toDouble();
    robotSettings.KickerMass= robot_settings->value("Physics/KickerMass",0.02).toDouble();
    robotSettings.KickerDampFactor = robot_settings->value("Physics/KickerDampFactor", 0.2f).toDouble();
    robotSettings.RollerTorqueFactor = robot_settings->value("Physics/RollerTorqueFactor", 0.06f).toDouble();
    robotSettings.RollerPerpendicularTorqueFactor = robot_settings->value("Physics/RollerPerpendicularTorqueFactor", 0.005f).toDouble();
    robotSettings.Kicker_Friction = robot_settings->value("Physics/KickerFriction", 0.8f).toDouble();
    robotSettings.WheelTangentFriction = robot_settings->value("Physics/WheelTangentFriction", 0.8f).toDouble();
    robotSettings.WheelPerpendicularFriction = robot_settings->value("Physics/WheelPerpendicularFriction", 0.05f).toDouble();
    robotSettings.Wheel_Motor_FMax = robot_settings->value("Physics/WheelMotorMaximumApplyingTorque", 0.2f).toDouble();
}
