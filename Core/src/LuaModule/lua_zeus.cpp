/*
** Lua binding: zeus
** Generated automatically by tolua++-1.0.92 on Sun Mar 12 18:06:11 2023.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_zeus_open (lua_State* tolua_S);

#include "gpuBestAlgThread.h"
#include <BestPlayer.h>
#include "DefenceInfo.h"
#include "DefendUtils.h"
#include "DefPos2015.h"
#include "game_state.h"
#include "GDebugEngine.h"
#include "geometry.h"
#include "Global.h"
#include "GuardPos.h"
#include "PointCalculation/IndirectDefender.h"
#include "KickDirection.h"
#include "KickStatus.h"
#include "matrix.h"
#include "munkres.h"
#include "NormalPlayUtils.h"
#include "PointCalculation/SupportPos.h"
#include "SupportPos2022.h"
#include "TandemPos.h"
#include "utils.h"
#include <Vision/VisionModule.h>
#include "WorldDefine.h"
#include "WorldModel/WorldModel.h"
#include "RobotSensor.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TranslationT (lua_State* tolua_S)
{
 TranslationT* self = (TranslationT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CBestPlayer (lua_State* tolua_S)
{
 CBestPlayer* self = (CBestPlayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoEllipse (lua_State* tolua_S)
{
 CGeoEllipse* self = (CGeoEllipse*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CSupportPos2022 (lua_State* tolua_S)
{
 CSupportPos2022* self = (CSupportPos2022*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoShape (lua_State* tolua_S)
{
 CGeoShape* self = (CGeoShape*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineCircleIntersection (lua_State* tolua_S)
{
 CGeoLineCircleIntersection* self = (CGeoLineCircleIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_PlayerCapabilityT (lua_State* tolua_S)
{
 PlayerCapabilityT* self = (PlayerCapabilityT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineRectangleIntersection (lua_State* tolua_S)
{
 CGeoLineRectangleIntersection* self = (CGeoLineRectangleIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Matrix_double_ (lua_State* tolua_S)
{
 Matrix<double>* self = (Matrix<double>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoSegment (lua_State* tolua_S)
{
 CGeoSegment* self = (CGeoSegment*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_vector_MarkField_ (lua_State* tolua_S)
{
 vector<MarkField>* self = (vector<MarkField>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CKickStatus (lua_State* tolua_S)
{
 CKickStatus* self = (CKickStatus*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_MarkField (lua_State* tolua_S)
{
 MarkField* self = (MarkField*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_RotationT (lua_State* tolua_S)
{
 RotationT* self = (RotationT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_AreaStruct (lua_State* tolua_S)
{
 AreaStruct* self = (AreaStruct*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TwoKickPos (lua_State* tolua_S)
{
 TwoKickPos* self = (TwoKickPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CBestPlayer__ToBallPotentialPair (lua_State* tolua_S)
{
 CBestPlayer::ToBallPotentialPair* self = (CBestPlayer::ToBallPotentialPair*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineLineIntersection (lua_State* tolua_S)
{
 CGeoLineLineIntersection* self = (CGeoLineLineIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoRectangle (lua_State* tolua_S)
{
 CGeoRectangle* self = (CGeoRectangle*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGuardPos (lua_State* tolua_S)
{
 CGuardPos* self = (CGuardPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CIndirectDefender (lua_State* tolua_S)
{
 CIndirectDefender* self = (CIndirectDefender*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_AttackerStruct (lua_State* tolua_S)
{
 AttackerStruct* self = (AttackerStruct*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ChipPosT (lua_State* tolua_S)
{
 ChipPosT* self = (ChipPosT*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoSegmentCircleIntersection (lua_State* tolua_S)
{
 CGeoSegmentCircleIntersection* self = (CGeoSegmentCircleIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoCirlce (lua_State* tolua_S)
{
 CGeoCirlce* self = (CGeoCirlce*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CRobotSensor (lua_State* tolua_S)
{
 CRobotSensor* self = (CRobotSensor*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLine (lua_State* tolua_S)
{
 CGeoLine* self = (CGeoLine*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_PointValueStruct (lua_State* tolua_S)
{
 PointValueStruct* self = (PointValueStruct*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CWorldModel (lua_State* tolua_S)
{
 CWorldModel* self = (CWorldModel*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_GameState (lua_State* tolua_S)
{
 GameState* self = (GameState*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SupportPosStruct2022 (lua_State* tolua_S)
{
 SupportPosStruct2022* self = (SupportPosStruct2022*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CSupportPos (lua_State* tolua_S)
{
 CSupportPos* self = (CSupportPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CVisionModule (lua_State* tolua_S)
{
 CVisionModule* self = (CVisionModule*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CKickDirection (lua_State* tolua_S)
{
 CKickDirection* self = (CKickDirection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGPUBestAlgThread (lua_State* tolua_S)
{
 CGPUBestAlgThread* self = (CGPUBestAlgThread*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CDefPos2015 (lua_State* tolua_S)
{
 CDefPos2015* self = (CDefPos2015*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CTandemPos (lua_State* tolua_S)
{
 CTandemPos* self = (CTandemPos*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CDefenceInfo (lua_State* tolua_S)
{
 CDefenceInfo* self = (CDefenceInfo*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_FieldRectangle (lua_State* tolua_S)
{
 FieldRectangle* self = (FieldRectangle*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Defend2015 (lua_State* tolua_S)
{
 Defend2015* self = (Defend2015*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CVector (lua_State* tolua_S)
{
 CVector* self = (CVector*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoLineEllipseIntersection (lua_State* tolua_S)
{
 CGeoLineEllipseIntersection* self = (CGeoLineEllipseIntersection*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGeoPoint (lua_State* tolua_S)
{
 CGeoPoint* self = (CGeoPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CGDebugEngine (lua_State* tolua_S)
{
 CGDebugEngine* self = (CGDebugEngine*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TranslationT");
 tolua_usertype(tolua_S,"CBestPlayer");
 tolua_usertype(tolua_S,"CRobotSensor");
 tolua_usertype(tolua_S,"CAttributeSet");
 tolua_usertype(tolua_S,"CWorldModel");
 tolua_usertype(tolua_S,"CChipBallJudge");
 tolua_usertype(tolua_S,"CGeoShape");
 tolua_usertype(tolua_S,"ROBOTINFO");
 tolua_usertype(tolua_S,"CVector");
 tolua_usertype(tolua_S,"PlayerCapabilityT");
 tolua_usertype(tolua_S,"BallVisionT");
 tolua_usertype(tolua_S,"CDefPos1G2D");
 tolua_usertype(tolua_S,"CGeoLineRectangleIntersection");
 tolua_usertype(tolua_S,"CPlayerCommand");
 tolua_usertype(tolua_S,"Matrix<double>");
 tolua_usertype(tolua_S,"CGeoSegment");
 tolua_usertype(tolua_S,"vector<MarkField>");
 tolua_usertype(tolua_S,"PlayerVisionT");
 tolua_usertype(tolua_S,"COppPlayer");
 tolua_usertype(tolua_S,"ParamManagerOwl");
 tolua_usertype(tolua_S,"CTrigger");
 tolua_usertype(tolua_S,"GameInfoT");
 tolua_usertype(tolua_S,"MarkField");
 tolua_usertype(tolua_S,"RotationT");
 tolua_usertype(tolua_S,"GameState");
 tolua_usertype(tolua_S,"TwoKickPos");
 tolua_usertype(tolua_S,"CDribbleStatus");
 tolua_usertype(tolua_S,"CBestPlayer::ToBallPotentialPair");
 tolua_usertype(tolua_S,"CGeoLineLineIntersection");
 tolua_usertype(tolua_S,"CSupportPos2022");
 tolua_usertype(tolua_S,"SupportPosStruct2022");
 tolua_usertype(tolua_S,"CGeoRectangle");
 tolua_usertype(tolua_S,"CSupportPos");
 tolua_usertype(tolua_S,"CGPUBestAlgThread");
 tolua_usertype(tolua_S,"CIndirectDefender");
 tolua_usertype(tolua_S,"AttackerStruct");
 tolua_usertype(tolua_S,"ChipPosT");
 tolua_usertype(tolua_S,"CKickStatus");
 tolua_usertype(tolua_S,"ParamManagerSimulator");
 tolua_usertype(tolua_S,"FieldRectangle");
 tolua_usertype(tolua_S,"CKickDirection");
 tolua_usertype(tolua_S,"CGeoLineCircleIntersection");
 tolua_usertype(tolua_S,"CGuardPos");
 tolua_usertype(tolua_S,"CDefPos2013");
 tolua_usertype(tolua_S,"CGeoCirlce");
 tolua_usertype(tolua_S,"ParamManagerVision");
 tolua_usertype(tolua_S,"CGeoLine");
 tolua_usertype(tolua_S,"PointValueStruct");
 tolua_usertype(tolua_S,"ParamManagerCfg");
 tolua_usertype(tolua_S,"CParamManagerSkill");
 tolua_usertype(tolua_S,"CGeoSegmentCircleIntersection");
 tolua_usertype(tolua_S,"CGDebugEngine");
 tolua_usertype(tolua_S,"CVisionModule");
 tolua_usertype(tolua_S,"CGeoEllipse");
 tolua_usertype(tolua_S,"KickOffArea");
 tolua_usertype(tolua_S,"CDefPos2015");
 tolua_usertype(tolua_S,"CTandemPos");
 tolua_usertype(tolua_S,"CDefenceInfo");
 tolua_usertype(tolua_S,"Munkres");
 tolua_usertype(tolua_S,"Defend2015");
 tolua_usertype(tolua_S,"CGeoPoint");
 tolua_usertype(tolua_S,"CGeoLineEllipseIntersection");
 tolua_usertype(tolua_S,"AreaStruct");
 tolua_usertype(tolua_S,"COptionModule");
}

/* get function: pos_x of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_get_PointValueStruct_pos_x
static int tolua_get_PointValueStruct_pos_x(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos_x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pos_x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos_x of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_set_PointValueStruct_pos_x
static int tolua_set_PointValueStruct_pos_x(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos_x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos_x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos_y of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_get_PointValueStruct_pos_y
static int tolua_get_PointValueStruct_pos_y(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos_y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pos_y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos_y of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_set_PointValueStruct_pos_y
static int tolua_set_PointValueStruct_pos_y(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos_y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos_y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_get_PointValueStruct_pos
static int tolua_get_PointValueStruct_pos(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pos);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_set_PointValueStruct_pos
static int tolua_set_PointValueStruct_pos(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: value of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_get_PointValueStruct_value
static int tolua_get_PointValueStruct_value(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->value);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: value of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_set_PointValueStruct_value
static int tolua_set_PointValueStruct_value(lua_State* tolua_S)
{
  PointValueStruct* self = (PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->value = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_PointValueStruct_new00
static int tolua_zeus_PointValueStruct_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PointValueStruct",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PointValueStruct* tolua_ret = (PointValueStruct*)  Mtolua_new((PointValueStruct)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PointValueStruct");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_PointValueStruct_new00_local
static int tolua_zeus_PointValueStruct_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PointValueStruct",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PointValueStruct* tolua_ret = (PointValueStruct*)  Mtolua_new((PointValueStruct)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PointValueStruct");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  PointValueStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_PointValueStruct__eq00
static int tolua_zeus_PointValueStruct__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PointValueStruct",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PointValueStruct",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PointValueStruct* self = (const PointValueStruct*)  tolua_tousertype(tolua_S,1,0);
  const PointValueStruct* p = ((const PointValueStruct*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _pos of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_get_AreaStruct__pos
static int tolua_get_AreaStruct__pos(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_pos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_pos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _pos of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_set_AreaStruct__pos
static int tolua_set_AreaStruct__pos(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_pos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _value of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_get_AreaStruct__value
static int tolua_get_AreaStruct__value(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_value'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->_value);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _value of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_set_AreaStruct__value
static int tolua_set_AreaStruct__value(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_value'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_value = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _area_idx of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_get_AreaStruct__area_idx
static int tolua_get_AreaStruct__area_idx(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_area_idx'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->_area_idx);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _area_idx of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_set_AreaStruct__area_idx
static int tolua_set_AreaStruct__area_idx(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_area_idx'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_area_idx = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _conflict of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_get_AreaStruct__conflict
static int tolua_get_AreaStruct__conflict(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_conflict'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->_conflict);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _conflict of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_set_AreaStruct__conflict
static int tolua_set_AreaStruct__conflict(lua_State* tolua_S)
{
  AreaStruct* self = (AreaStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_conflict'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_conflict = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_AreaStruct_new00
static int tolua_zeus_AreaStruct_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AreaStruct",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* pos = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
  int area_idx = ((int)  tolua_tonumber(tolua_S,4,0));
  bool conflict = ((bool)  tolua_toboolean(tolua_S,5,0));
  {
   AreaStruct* tolua_ret = (AreaStruct*)  Mtolua_new((AreaStruct)(*pos,value,area_idx,conflict));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AreaStruct");
   tolua_pushnumber(tolua_S,(lua_Number)value);
   tolua_pushnumber(tolua_S,(lua_Number)area_idx);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_AreaStruct_new00_local
static int tolua_zeus_AreaStruct_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AreaStruct",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* pos = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
  int area_idx = ((int)  tolua_tonumber(tolua_S,4,0));
  bool conflict = ((bool)  tolua_toboolean(tolua_S,5,0));
  {
   AreaStruct* tolua_ret = (AreaStruct*)  Mtolua_new((AreaStruct)(*pos,value,area_idx,conflict));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AreaStruct");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushnumber(tolua_S,(lua_Number)value);
   tolua_pushnumber(tolua_S,(lua_Number)area_idx);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  AreaStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_AreaStruct__eq00
static int tolua_zeus_AreaStruct__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AreaStruct",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AreaStruct",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AreaStruct* self = (const AreaStruct*)  tolua_tousertype(tolua_S,1,0);
  const AreaStruct* area = ((const AreaStruct*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*area);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_FieldRectangle_new00
static int tolua_zeus_FieldRectangle_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FieldRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ld = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint ru = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   FieldRectangle* tolua_ret = (FieldRectangle*)  Mtolua_new((FieldRectangle)(ld,ru));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FieldRectangle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_FieldRectangle_new00_local
static int tolua_zeus_FieldRectangle_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FieldRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ld = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint ru = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   FieldRectangle* tolua_ret = (FieldRectangle*)  Mtolua_new((FieldRectangle)(ld,ru));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FieldRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: centerArea of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_FieldRectangle_centerArea00
static int tolua_zeus_FieldRectangle_centerArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FieldRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'centerArea'", NULL);
#endif
  {
   FieldRectangle tolua_ret = (FieldRectangle)  self->centerArea();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((FieldRectangle)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"FieldRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(FieldRectangle));
     tolua_pushusertype(tolua_S,tolua_obj,"FieldRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'centerArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCenter of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_FieldRectangle_getCenter00
static int tolua_zeus_FieldRectangle_getCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FieldRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCenter'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getCenter();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _rangeX of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__rangeX
static int tolua_get_FieldRectangle__rangeX(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rangeX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->_rangeX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _rangeX of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__rangeX
static int tolua_set_FieldRectangle__rangeX(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rangeX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_rangeX = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _rangeY of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__rangeY
static int tolua_get_FieldRectangle__rangeY(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rangeY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->_rangeY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _rangeY of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__rangeY
static int tolua_set_FieldRectangle__rangeY(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rangeY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_rangeY = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _leftDownPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__leftDownPos
static int tolua_get_FieldRectangle__leftDownPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_leftDownPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_leftDownPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _leftDownPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__leftDownPos
static int tolua_set_FieldRectangle__leftDownPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_leftDownPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_leftDownPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _rightUpPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__rightUpPos
static int tolua_get_FieldRectangle__rightUpPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rightUpPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_rightUpPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _rightUpPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__rightUpPos
static int tolua_set_FieldRectangle__rightUpPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rightUpPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_rightUpPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _leftUpPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__leftUpPos
static int tolua_get_FieldRectangle__leftUpPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_leftUpPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_leftUpPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _leftUpPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__leftUpPos
static int tolua_set_FieldRectangle__leftUpPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_leftUpPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_leftUpPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _rightDownPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__rightDownPos
static int tolua_get_FieldRectangle__rightDownPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rightDownPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_rightDownPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _rightDownPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__rightDownPos
static int tolua_set_FieldRectangle__rightDownPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_rightDownPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_rightDownPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _centerPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_get_FieldRectangle__centerPos
static int tolua_get_FieldRectangle__centerPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_centerPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_centerPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _centerPos of class  FieldRectangle */
#ifndef TOLUA_DISABLE_tolua_set_FieldRectangle__centerPos
static int tolua_set_FieldRectangle__centerPos(lua_State* tolua_S)
{
  FieldRectangle* self = (FieldRectangle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_centerPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_centerPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_new00
static int tolua_zeus_CGPUBestAlgThread_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGPUBestAlgThread* tolua_ret = (CGPUBestAlgThread*)  Mtolua_new((CGPUBestAlgThread)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGPUBestAlgThread");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_new00_local
static int tolua_zeus_CGPUBestAlgThread_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGPUBestAlgThread* tolua_ret = (CGPUBestAlgThread*)  Mtolua_new((CGPUBestAlgThread)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGPUBestAlgThread");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_delete00
static int tolua_zeus_CGPUBestAlgThread_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialize of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_initialize00
static int tolua_zeus_CGPUBestAlgThread_initialize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  CVisionModule* _pVision = ((CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialize'", NULL);
#endif
  {
   self->initialize(_pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBestPointFromArea of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getBestPointFromArea00
static int tolua_zeus_CGPUBestAlgThread_getBestPointFromArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  int area_idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBestPointFromArea'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getBestPointFromArea(area_idx);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBestPointFromArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePointValue of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_generatePointValue00
static int tolua_zeus_CGPUBestAlgThread_generatePointValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePointValue'", NULL);
#endif
  {
   self->generatePointValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePointValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLastOneValid of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_isLastOneValid00
static int tolua_zeus_CGPUBestAlgThread_isLastOneValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLastOneValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLastOneValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLastOneValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSendPoint of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_setSendPoint00
static int tolua_zeus_CGPUBestAlgThread_setSendPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint passPoint = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSendPoint'", NULL);
#endif
  {
   self->setSendPoint(passPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSendPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosPotential of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getPosPotential00
static int tolua_zeus_CGPUBestAlgThread_getPosPotential00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint p = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosPotential'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getPosPotential(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosPotential'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapSize of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_getMapSize00
static int tolua_zeus_CGPUBestAlgThread_getMapSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMapSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startComm of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_startComm00
static int tolua_zeus_CGPUBestAlgThread_startComm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startComm'", NULL);
#endif
  {
   self->startComm();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startComm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPointValue of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_setPointValue00
static int tolua_zeus_CGPUBestAlgThread_setPointValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPointValue'", NULL);
#endif
  {
   self->setPointValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPointValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendPointValue of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_sendPointValue00
static int tolua_zeus_CGPUBestAlgThread_sendPointValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendPointValue'", NULL);
#endif
  {
   self->sendPointValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendPointValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doBestCalculation of class  CGPUBestAlgThread */
#ifndef TOLUA_DISABLE_tolua_zeus_CGPUBestAlgThread_doBestCalculation00
static int tolua_zeus_CGPUBestAlgThread_doBestCalculation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGPUBestAlgThread",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGPUBestAlgThread* self = (CGPUBestAlgThread*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doBestCalculation'", NULL);
#endif
  {
   self->doBestCalculation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doBestCalculation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_ToBallPotentialPair_new00
static int tolua_zeus_CBestPlayer_ToBallPotentialPair_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer::ToBallPotentialPair",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  double p = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CBestPlayer::ToBallPotentialPair* tolua_ret = (CBestPlayer::ToBallPotentialPair*)  Mtolua_new((CBestPlayer::ToBallPotentialPair)(n,p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer::ToBallPotentialPair");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_ToBallPotentialPair_new00_local
static int tolua_zeus_CBestPlayer_ToBallPotentialPair_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer::ToBallPotentialPair",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  double p = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CBestPlayer::ToBallPotentialPair* tolua_ret = (CBestPlayer::ToBallPotentialPair*)  Mtolua_new((CBestPlayer::ToBallPotentialPair)(n,p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer::ToBallPotentialPair");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: num of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_get_CBestPlayer__ToBallPotentialPair_num
static int tolua_get_CBestPlayer__ToBallPotentialPair_num(lua_State* tolua_S)
{
  CBestPlayer::ToBallPotentialPair* self = (CBestPlayer::ToBallPotentialPair*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'num'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->num);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: num of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_set_CBestPlayer__ToBallPotentialPair_num
static int tolua_set_CBestPlayer__ToBallPotentialPair_num(lua_State* tolua_S)
{
  CBestPlayer::ToBallPotentialPair* self = (CBestPlayer::ToBallPotentialPair*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'num'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->num = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: potential of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_get_CBestPlayer__ToBallPotentialPair_potential
static int tolua_get_CBestPlayer__ToBallPotentialPair_potential(lua_State* tolua_S)
{
  CBestPlayer::ToBallPotentialPair* self = (CBestPlayer::ToBallPotentialPair*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'potential'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->potential);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: potential of class  ToBallPotentialPair */
#ifndef TOLUA_DISABLE_tolua_set_CBestPlayer__ToBallPotentialPair_potential
static int tolua_set_CBestPlayer__ToBallPotentialPair_potential(lua_State* tolua_S)
{
  CBestPlayer::ToBallPotentialPair* self = (CBestPlayer::ToBallPotentialPair*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'potential'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->potential = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_new00
static int tolua_zeus_CBestPlayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CBestPlayer* tolua_ret = (CBestPlayer*)  Mtolua_new((CBestPlayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_new00_local
static int tolua_zeus_CBestPlayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CBestPlayer* tolua_ret = (CBestPlayer*)  Mtolua_new((CBestPlayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CBestPlayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_delete00
static int tolua_zeus_CBestPlayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_update00
static int tolua_zeus_CBestPlayer_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurMesurementZ of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getCurMesurementZ00
static int tolua_zeus_CBestPlayer_getCurMesurementZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurMesurementZ'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurMesurementZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurMesurementZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOurPotential of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getOurPotential00
static int tolua_zeus_CBestPlayer_getOurPotential00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOurPotential'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getOurPotential(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurPotential'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirPotential of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getTheirPotential00
static int tolua_zeus_CBestPlayer_getTheirPotential00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CBestPlayer* self = (const CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirPotential'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getTheirPotential(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirPotential'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: withBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_withBall00
static int tolua_zeus_CBestPlayer_withBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CBestPlayer* self = (const CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'withBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->withBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'withBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oppWithBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_oppWithBall00
static int tolua_zeus_CBestPlayer_oppWithBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CBestPlayer* self = (const CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oppWithBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->oppWithBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oppWithBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOurBestPlayerChanged of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isOurBestPlayerChanged00
static int tolua_zeus_CBestPlayer_isOurBestPlayerChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOurBestPlayerChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOurBestPlayerChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOurBestPlayerChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOurBestPlayer of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getOurBestPlayer00
static int tolua_zeus_CBestPlayer_getOurBestPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOurBestPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOurBestPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurBestPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTheirBestPlayerChanged of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isTheirBestPlayerChanged00
static int tolua_zeus_CBestPlayer_isTheirBestPlayerChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTheirBestPlayerChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTheirBestPlayerChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTheirBestPlayerChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirBestPlayer of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_getTheirBestPlayer00
static int tolua_zeus_CBestPlayer_getTheirBestPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirBestPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTheirBestPlayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirBestPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOurPlayerStrictControlBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isOurPlayerStrictControlBall00
static int tolua_zeus_CBestPlayer_isOurPlayerStrictControlBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOurPlayerStrictControlBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOurPlayerStrictControlBall(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOurPlayerStrictControlBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOurPlayerLooseControlBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isOurPlayerLooseControlBall00
static int tolua_zeus_CBestPlayer_isOurPlayerLooseControlBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOurPlayerLooseControlBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOurPlayerLooseControlBall(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOurPlayerLooseControlBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTheirPlayerStrictControlBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isTheirPlayerStrictControlBall00
static int tolua_zeus_CBestPlayer_isTheirPlayerStrictControlBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTheirPlayerStrictControlBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTheirPlayerStrictControlBall(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTheirPlayerStrictControlBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTheirPlayerLooseControlBall of class  CBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_CBestPlayer_isTheirPlayerLooseControlBall00
static int tolua_zeus_CBestPlayer_isTheirPlayerLooseControlBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CBestPlayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CBestPlayer* self = (CBestPlayer*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTheirPlayerLooseControlBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTheirPlayerLooseControlBall(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTheirPlayerLooseControlBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_new00
static int tolua_zeus_CVisionModule_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVisionModule* tolua_ret = (CVisionModule*)  Mtolua_new((CVisionModule)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVisionModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_new00_local
static int tolua_zeus_CVisionModule_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVisionModule* tolua_ret = (CVisionModule*)  Mtolua_new((CVisionModule)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVisionModule");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_delete00
static int tolua_zeus_CVisionModule_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOption of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_registerOption00
static int tolua_zeus_CVisionModule_registerOption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const COptionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  const COptionModule* pOption = ((const COptionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOption'", NULL);
#endif
  {
   self->registerOption(pOption);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOption'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getValidNum00
static int tolua_zeus_CVisionModule_getValidNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNum'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getValidNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTheirValidNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getTheirValidNum00
static int tolua_zeus_CVisionModule_getTheirValidNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTheirValidNum'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getTheirValidNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirValidNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRefRecvMsg of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_SetRefRecvMsg00
static int tolua_zeus_CVisionModule_SetRefRecvMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const GameInfoT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  const GameInfoT msg = *((const GameInfoT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRefRecvMsg'", NULL);
#endif
  {
   self->SetRefRecvMsg(msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRefRecvMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNewVision of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_SetNewVision00
static int tolua_zeus_CVisionModule_SetNewVision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const GameInfoT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  const GameInfoT* vInfo = ((const GameInfoT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNewVision'", NULL);
#endif
  {
   self->SetNewVision(*vInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNewVision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AllPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_AllPlayer00
static int tolua_zeus_CVisionModule_AllPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AllPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->AllPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AllPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurPlayer00
static int tolua_zeus_CVisionModule_OurPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->OurPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirPlayer00
static int tolua_zeus_CVisionModule_TheirPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->TheirPlayer(num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ball of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Ball00
static int tolua_zeus_CVisionModule_Ball00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ball'", NULL);
#endif
  {
   const BallVisionT& tolua_ret = (const BallVisionT&)  self->Ball();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BallVisionT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ball'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurPlayer01
static int tolua_zeus_CVisionModule_OurPlayer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->OurPlayer(cycle,num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_OurPlayer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirPlayer of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirPlayer01
static int tolua_zeus_CVisionModule_TheirPlayer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirPlayer'", NULL);
#endif
  {
   const PlayerVisionT& tolua_ret = (const PlayerVisionT&)  self->TheirPlayer(cycle,num);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PlayerVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_TheirPlayer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ball of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Ball01
static int tolua_zeus_CVisionModule_Ball01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ball'", NULL);
#endif
  {
   const BallVisionT& tolua_ret = (const BallVisionT&)  self->Ball(cycle);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BallVisionT");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVisionModule_Ball00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlayerCommand of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_SetPlayerCommand00
static int tolua_zeus_CVisionModule_SetPlayerCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const CPlayerCommand",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  const CPlayerCommand* pCmd = ((const CPlayerCommand*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlayerCommand'", NULL);
#endif
  {
   self->SetPlayerCommand(num,pCmd);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlayerCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameState of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_gameState00
static int tolua_zeus_CVisionModule_gameState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameState'", NULL);
#endif
  {
   const GameState& tolua_ret = (const GameState&)  self->gameState();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const GameState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cycle of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Cycle00
static int tolua_zeus_CVisionModule_Cycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cycle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Cycle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LastCycle of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_LastCycle00
static int tolua_zeus_CVisionModule_LastCycle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LastCycle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LastCycle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LastCycle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Side of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_Side00
static int tolua_zeus_CVisionModule_Side00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Side'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Side();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Side'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentRefereeMsg of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_GetCurrentRefereeMsg00
static int tolua_zeus_CVisionModule_GetCurrentRefereeMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentRefereeMsg'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->GetCurrentRefereeMsg();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentRefereeMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastRefereeMsg of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_GetLastRefereeMsg00
static int tolua_zeus_CVisionModule_GetLastRefereeMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastRefereeMsg'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->GetLastRefereeMsg();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastRefereeMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurGoal of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurGoal00
static int tolua_zeus_CVisionModule_OurGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurGoal'", NULL);
#endif
  {
   int tolua_ret = (int)  self->OurGoal();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirGoal of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirGoal00
static int tolua_zeus_CVisionModule_TheirGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirGoal'", NULL);
#endif
  {
   int tolua_ret = (int)  self->TheirGoal();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirGoalie of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirGoalie00
static int tolua_zeus_CVisionModule_TheirGoalie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirGoalie'", NULL);
#endif
  {
   int tolua_ret = (int)  self->TheirGoalie();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirGoalie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurRawPlayerSpeed of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_OurRawPlayerSpeed00
static int tolua_zeus_CVisionModule_OurRawPlayerSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurRawPlayerSpeed'", NULL);
#endif
  {
   const CVector tolua_ret = (const CVector)  self->OurRawPlayerSpeed(num);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurRawPlayerSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TheirRawPlayerSpeed of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_TheirRawPlayerSpeed00
static int tolua_zeus_CVisionModule_TheirRawPlayerSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TheirRawPlayerSpeed'", NULL);
#endif
  {
   const CVector tolua_ret = (const CVector)  self->TheirRawPlayerSpeed(num);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TheirRawPlayerSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTheirPenaltyNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_GetTheirPenaltyNum00
static int tolua_zeus_CVisionModule_GetTheirPenaltyNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTheirPenaltyNum'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->GetTheirPenaltyNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTheirPenaltyNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetTheirPenaltyNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_ResetTheirPenaltyNum00
static int tolua_zeus_CVisionModule_ResetTheirPenaltyNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetTheirPenaltyNum'", NULL);
#endif
  {
   self->ResetTheirPenaltyNum();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetTheirPenaltyNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTheirGoalieStrategyNum of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_GetTheirGoalieStrategyNum00
static int tolua_zeus_CVisionModule_GetTheirGoalieStrategyNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTheirGoalieStrategyNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTheirGoalieStrategyNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTheirGoalieStrategyNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallVelStable of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getBallVelStable00
static int tolua_zeus_CVisionModule_getBallVelStable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallVelStable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBallVelStable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallVelStable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallPlacementPosition of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_getBallPlacementPosition00
static int tolua_zeus_CVisionModule_getBallPlacementPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* self = (const CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallPlacementPosition'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getBallPlacementPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallPlacementPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballVelValid of class  CVisionModule */
#ifndef TOLUA_DISABLE_tolua_zeus_CVisionModule_ballVelValid00
static int tolua_zeus_CVisionModule_ballVelValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVisionModule* self = (CVisionModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballVelValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ballVelValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballVelValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_zeus_MarkField_new00
static int tolua_zeus_MarkField_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MarkField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   MarkField* tolua_ret = (MarkField*)  Mtolua_new((MarkField)(upLeft,downRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MarkField");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_zeus_MarkField_new00_local
static int tolua_zeus_MarkField_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MarkField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   MarkField* tolua_ret = (MarkField*)  Mtolua_new((MarkField)(upLeft,downRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MarkField");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _upLeft of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_get_MarkField__upLeft
static int tolua_get_MarkField__upLeft(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_upLeft'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_upLeft,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _upLeft of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_set_MarkField__upLeft
static int tolua_set_MarkField__upLeft(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_upLeft'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _downRight of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_get_MarkField__downRight
static int tolua_get_MarkField__downRight(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_downRight'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_downRight,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _downRight of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_set_MarkField__downRight
static int tolua_set_MarkField__downRight(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_downRight'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: markTouchNum of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_get_MarkField_markTouchNum
static int tolua_get_MarkField_markTouchNum(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'markTouchNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->markTouchNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: markTouchNum of class  MarkField */
#ifndef TOLUA_DISABLE_tolua_set_MarkField_markTouchNum
static int tolua_set_MarkField_markTouchNum(lua_State* tolua_S)
{
  MarkField* self = (MarkField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'markTouchNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->markTouchNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_AttackerStruct_new00
static int tolua_zeus_AttackerStruct_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AttackerStruct",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  int pri = ((int)  tolua_tonumber(tolua_S,3,0));
  double subV = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   AttackerStruct* tolua_ret = (AttackerStruct*)  Mtolua_new((AttackerStruct)(n,pri,subV));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AttackerStruct");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_zeus_AttackerStruct_new00_local
static int tolua_zeus_AttackerStruct_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AttackerStruct",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  int pri = ((int)  tolua_tonumber(tolua_S,3,0));
  double subV = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   AttackerStruct* tolua_ret = (AttackerStruct*)  Mtolua_new((AttackerStruct)(n,pri,subV));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AttackerStruct");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: num of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_get_AttackerStruct_num
static int tolua_get_AttackerStruct_num(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'num'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->num);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: num of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_set_AttackerStruct_num
static int tolua_set_AttackerStruct_num(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'num'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->num = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: prioirty of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_get_AttackerStruct_prioirty
static int tolua_get_AttackerStruct_prioirty(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'prioirty'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->prioirty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: prioirty of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_set_AttackerStruct_prioirty
static int tolua_set_AttackerStruct_prioirty(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'prioirty'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->prioirty = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: subValue of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_get_AttackerStruct_subValue
static int tolua_get_AttackerStruct_subValue(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'subValue'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->subValue);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: subValue of class  AttackerStruct */
#ifndef TOLUA_DISABLE_tolua_set_AttackerStruct_subValue
static int tolua_set_AttackerStruct_subValue(lua_State* tolua_S)
{
  AttackerStruct* self = (AttackerStruct*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'subValue'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->subValue = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_new00
static int tolua_zeus_CDefenceInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefenceInfo* tolua_ret = (CDefenceInfo*)  Mtolua_new((CDefenceInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefenceInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_new00_local
static int tolua_zeus_CDefenceInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefenceInfo* tolua_ret = (CDefenceInfo*)  Mtolua_new((CDefenceInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefenceInfo");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_delete00
static int tolua_zeus_CDefenceInfo_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialization of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_initialization00
static int tolua_zeus_CDefenceInfo_initialization00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialization'", NULL);
#endif
  {
   self->initialization();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialization'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDefenceInfo of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_updateDefenceInfo00
static int tolua_zeus_CDefenceInfo_updateDefenceInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDefenceInfo'", NULL);
#endif
  {
   self->updateDefenceInfo(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDefenceInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoChangeFlag of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setNoChangeFlag00
static int tolua_zeus_CDefenceInfo_setNoChangeFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoChangeFlag'", NULL);
#endif
  {
   self->setNoChangeFlag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoChangeFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearNoChangeFlag of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearNoChangeFlag00
static int tolua_zeus_CDefenceInfo_clearNoChangeFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearNoChangeFlag'", NULL);
#endif
  {
   self->clearNoChangeFlag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearNoChangeFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoMarkingField of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setNoMarkingField00
static int tolua_zeus_CDefenceInfo_setNoMarkingField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoMarkingField'", NULL);
#endif
  {
   self->setNoMarkingField(upLeft,downRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoMarkingField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearNoMarkingField of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearNoMarkingField00
static int tolua_zeus_CDefenceInfo_clearNoMarkingField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearNoMarkingField'", NULL);
#endif
  {
   self->clearNoMarkingField(upLeft,downRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearNoMarkingField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAll of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_clearAll00
static int tolua_zeus_CDefenceInfo_clearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAll'", NULL);
#endif
  {
   self->clearAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeAttrSet of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_changeAttrSet00
static int tolua_zeus_CDefenceInfo_changeAttrSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CAttributeSet",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CAttributeSet* as = ((CAttributeSet*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeAttrSet'", NULL);
#endif
  {
   self->changeAttrSet(*as);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeAttrSet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoMarkingNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setNoMarkingNum00
static int tolua_zeus_CDefenceInfo_setNoMarkingNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int enemyNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoMarkingNum'", NULL);
#endif
  {
   self->setNoMarkingNum(enemyNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoMarkingNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetMarkingInfo of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_resetMarkingInfo00
static int tolua_zeus_CDefenceInfo_resetMarkingInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetMarkingInfo'", NULL);
#endif
  {
   self->resetMarkingInfo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetMarkingInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOppoNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getOppoNum00
static int tolua_zeus_CDefenceInfo_getOppoNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOppoNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOppoNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOppoNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getAttackNum00
static int tolua_zeus_CDefenceInfo_getAttackNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttackNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttackOppNumByPri of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getAttackOppNumByPri00
static int tolua_zeus_CDefenceInfo_getAttackOppNumByPri00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttackOppNumByPri'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttackOppNumByPri(i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttackOppNumByPri'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSteadyAttackOppNumByPri of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00
static int tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSteadyAttackOppNumByPri'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSteadyAttackOppNumByPri(i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSteadyAttackOppNumByPri'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: queryMarked of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_queryMarked00
static int tolua_zeus_CDefenceInfo_queryMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'queryMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->queryMarked(i);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'queryMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOurMarkDenfender of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getOurMarkDenfender00
static int tolua_zeus_CDefenceInfo_getOurMarkDenfender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const int enemyNum = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOurMarkDenfender'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOurMarkDenfender(enemyNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurMarkDenfender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMarkMode of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getMarkMode00
static int tolua_zeus_CDefenceInfo_getMarkMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const int enemy = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMarkMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getMarkMode(enemy);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMarkMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerState of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getTriggerState00
static int tolua_zeus_CDefenceInfo_getTriggerState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTriggerState();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOppPlayerByNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getOppPlayerByNum00
static int tolua_zeus_CDefenceInfo_getOppPlayerByNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOppPlayerByNum'", NULL);
#endif
  {
   COppPlayer* tolua_ret = (COppPlayer*)  self->getOppPlayerByNum(i);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"COppPlayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOppPlayerByNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallTaken of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getBallTaken00
static int tolua_zeus_CDefenceInfo_getBallTaken00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallTaken'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBallTaken();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallTaken'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMarkFieldList of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getMarkFieldList00
static int tolua_zeus_CDefenceInfo_getMarkFieldList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMarkFieldList'", NULL);
#endif
  {
   vector<MarkField> tolua_ret = (vector<MarkField>)  self->getMarkFieldList();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((vector<MarkField>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"vector<MarkField>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(vector<MarkField>));
     tolua_pushusertype(tolua_S,tolua_obj,"vector<MarkField>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMarkFieldList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkInRecArea of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_checkInRecArea00
static int tolua_zeus_CDefenceInfo_checkInRecArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"MarkField",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int enemyNum = ((int)  tolua_tonumber(tolua_S,2,0));
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,3,0));
  MarkField markField = *((MarkField*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkInRecArea'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkInRecArea(enemyNum,pVision,markField);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkInRecArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkOurInRecArea of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_checkOurInRecArea00
static int tolua_zeus_CDefenceInfo_checkOurInRecArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"MarkField",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,3,0));
  MarkField markField = *((MarkField*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkOurInRecArea'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkOurInRecArea(myNum,pVision,markField);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkOurInRecArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMarkingTouchNum of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_getMarkingTouchNum00
static int tolua_zeus_CDefenceInfo_getMarkingTouchNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint downRight = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMarkingTouchNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMarkingTouchNum(upLeft,downRight);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMarkingTouchNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMarkList of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setMarkList00
static int tolua_zeus_CDefenceInfo_setMarkList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMarkList'", NULL);
#endif
  {
   self->setMarkList(pVision,myNum,enemyNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMarkList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMarkingTouchInfo of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setMarkingTouchInfo00
static int tolua_zeus_CDefenceInfo_setMarkingTouchInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  CGeoPoint upLeft = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMarkingTouchInfo'", NULL);
#endif
  {
   self->setMarkingTouchInfo(pVision,myNum,upLeft,rightDown);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMarkingTouchInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMarkMode of class  CDefenceInfo */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefenceInfo_setMarkMode00
static int tolua_zeus_CDefenceInfo_setMarkMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefenceInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefenceInfo* self = (CDefenceInfo*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,3,0));
  bool mode = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMarkMode'", NULL);
#endif
  {
   self->setMarkMode(myNum,enemyNum,mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMarkMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getPenaltyFronter */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getPenaltyFronter00
static int tolua_zeus_DefendUtils_getPenaltyFronter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  DefendUtils::getPenaltyFronter();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPenaltyFronter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::isPosInOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_isPosInOurPenaltyArea00
static int tolua_zeus_DefendUtils_isPosInOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::isPosInOurPenaltyArea(*pos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPosInOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::reversePoint */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_reversePoint00
static int tolua_zeus_DefendUtils_reversePoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::reversePoint(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reversePoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcBlockAngle */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcBlockAngle00
static int tolua_zeus_DefendUtils_calcBlockAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* player = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  DefendUtils::calcBlockAngle(*target,*player);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcBlockAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::leftCirValid */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_leftCirValid00
static int tolua_zeus_DefendUtils_leftCirValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::leftCirValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leftCirValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::rightCirValid */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_rightCirValid00
static int tolua_zeus_DefendUtils_rightCirValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DefendUtils::rightCirValid(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rightCirValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getEnemyShooter */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getEnemyShooter00
static int tolua_zeus_DefendUtils_getEnemyShooter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  DefendUtils::getEnemyShooter();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemyShooter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getDefenceTargetAndLine */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getDefenceTargetAndLine00
static int tolua_zeus_DefendUtils_getDefenceTargetAndLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* RdefenceTarget = ((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double RdefendDir = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoLine tolua_ret = (CGeoLine)  DefendUtils::getDefenceTargetAndLine(*RdefenceTarget,RdefendDir);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoLine)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoLine));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)RdefendDir);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefenceTargetAndLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcDefenderPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcDefenderPoint00
static int tolua_zeus_DefendUtils_calcDefenderPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint Rtarget = *((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double Rdir = ((const double)  tolua_tonumber(tolua_S,2,0));
  posSide Rside = ((posSide) (int)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcDefenderPoint(Rtarget,Rdir,Rside);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcDefenderPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getSideBackTargetAndLine */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getSideBackTargetAndLine00
static int tolua_zeus_DefendUtils_getSideBackTargetAndLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* RSideTarget = ((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double RSideDir = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoLine tolua_ret = (CGeoLine)  DefendUtils::getSideBackTargetAndLine(*RSideTarget,RSideDir);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoLine)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoLine));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)RSideDir);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSideBackTargetAndLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcDefenderPointV2 */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcDefenderPointV200
static int tolua_zeus_DefendUtils_calcDefenderPointV200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint Rtarget = *((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double Rdir = ((const double)  tolua_tonumber(tolua_S,2,0));
  const posSide Rside = ((const posSide) (int)  tolua_tonumber(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
  double ratio = ((double)  tolua_tonumber(tolua_S,5,-1.0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcDefenderPointV2(Rtarget,Rdir,Rside,mode,ratio);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcDefenderPointV2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcDefenderPointV3 */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcDefenderPointV300
static int tolua_zeus_DefendUtils_calcDefenderPointV300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* RTarget = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double RDir = ((double)  tolua_tonumber(tolua_S,2,0));
  posSide RSide = ((posSide) (int)  tolua_tonumber(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcDefenderPointV3(*RTarget,RDir,RSide,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcDefenderPointV3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcGoaliePointV2 */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcGoaliePointV200
static int tolua_zeus_DefendUtils_calcGoaliePointV200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint Rtarget = *((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double Rdir = ((const double)  tolua_tonumber(tolua_S,2,0));
  const posSide Rside = ((const posSide) (int)  tolua_tonumber(tolua_S,3,0));
  CGeoPoint laststoredpoint = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  int mode = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcGoaliePointV2(Rtarget,Rdir,Rside,laststoredpoint,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcGoaliePointV2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcGoaliePointV3 */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcGoaliePointV300
static int tolua_zeus_DefendUtils_calcGoaliePointV300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* RTarget = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double RDir = ((double)  tolua_tonumber(tolua_S,2,0));
  posSide RSide = ((posSide) (int)  tolua_tonumber(tolua_S,3,0));
  const CGeoPoint* lastpoint = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  int mode = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcGoaliePointV3(*RTarget,RDir,RSide,*lastpoint,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcGoaliePointV3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::calcPenaltyLinePoint */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_calcPenaltyLinePoint00
static int tolua_zeus_DefendUtils_calcPenaltyLinePoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const double dir = ((const double)  tolua_tonumber(tolua_S,1,0));
  const posSide side = ((const posSide) (int)  tolua_tonumber(tolua_S,2,0));
  double ratio = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::calcPenaltyLinePoint(dir,side,ratio);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcPenaltyLinePoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::isBallShotToTheGoal */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_isBallShotToTheGoal00
static int tolua_zeus_DefendUtils_isBallShotToTheGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  DefendUtils::isBallShotToTheGoal();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBallShotToTheGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::BallIsToPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_BallIsToPenaltyArea00
static int tolua_zeus_DefendUtils_BallIsToPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  DefendUtils::BallIsToPenaltyArea();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BallIsToPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::inHalfCourt */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_inHalfCourt00
static int tolua_zeus_DefendUtils_inHalfCourt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint target = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double dir = ((double)  tolua_tonumber(tolua_S,2,0));
  int sideFactor = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  DefendUtils::inHalfCourt(target,dir,sideFactor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'inHalfCourt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getBallShooted */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getBallShooted00
static int tolua_zeus_DefendUtils_getBallShooted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  DefendUtils::getBallShooted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallShooted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getEnemyPass */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getEnemyPass00
static int tolua_zeus_DefendUtils_getEnemyPass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  DefendUtils::getEnemyPass();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemyPass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getCornerAreaPos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getCornerAreaPos00
static int tolua_zeus_DefendUtils_getCornerAreaPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getCornerAreaPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCornerAreaPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getMiddleAreaPos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getMiddleAreaPos00
static int tolua_zeus_DefendUtils_getMiddleAreaPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getMiddleAreaPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddleAreaPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getDeDribblePos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getDeDribblePos00
static int tolua_zeus_DefendUtils_getDeDribblePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getDeDribblePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeDribblePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getIndirectDefender00
static int tolua_zeus_DefendUtils_getIndirectDefender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double radius = ((double)  tolua_tonumber(tolua_S,1,0));
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getIndirectDefender(radius,leftUp,rightDown,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIndirectDefender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getMiddleDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getMiddleDefender00
static int tolua_zeus_DefendUtils_getMiddleDefender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double bufferX = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getMiddleDefender(bufferX);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddleDefender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::getDefaultPos */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_getDefaultPos00
static int tolua_zeus_DefendUtils_getDefaultPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  DefendUtils::getDefaultPos(index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DefendUtils::checkInDeadArea */
#ifndef TOLUA_DISABLE_tolua_zeus_DefendUtils_checkInDeadArea00
static int tolua_zeus_DefendUtils_checkInDeadArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  DefendUtils::checkInDeadArea();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkInDeadArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_leftD
static int tolua_get_Defend2015_leftD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_leftD
static int tolua_set_Defend2015_leftD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_rightD
static int tolua_get_Defend2015_rightD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_rightD
static int tolua_set_Defend2015_rightD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftFrontD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_leftFrontD
static int tolua_get_Defend2015_leftFrontD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftFrontD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftFrontD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftFrontD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_leftFrontD
static int tolua_set_Defend2015_leftFrontD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftFrontD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftFrontD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightFrontD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_rightFrontD
static int tolua_get_Defend2015_rightFrontD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightFrontD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightFrontD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightFrontD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_rightFrontD
static int tolua_set_Defend2015_rightFrontD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightFrontD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightFrontD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftBackD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_leftBackD
static int tolua_get_Defend2015_leftBackD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftBackD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftBackD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftBackD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_leftBackD
static int tolua_set_Defend2015_leftBackD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftBackD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftBackD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightBackD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_rightBackD
static int tolua_get_Defend2015_rightBackD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightBackD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightBackD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightBackD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_rightBackD
static int tolua_set_Defend2015_rightBackD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightBackD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightBackD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftCenD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_leftCenD
static int tolua_get_Defend2015_leftCenD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftCenD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftCenD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftCenD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_leftCenD
static int tolua_set_Defend2015_leftCenD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftCenD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftCenD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightCenD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_rightCenD
static int tolua_get_Defend2015_rightCenD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightCenD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightCenD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightCenD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_rightCenD
static int tolua_set_Defend2015_rightCenD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightCenD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightCenD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: middleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_middleD
static int tolua_get_Defend2015_middleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'middleD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->middleD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: middleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_middleD
static int tolua_set_Defend2015_middleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'middleD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->middleD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: singleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_singleD
static int tolua_get_Defend2015_singleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'singleD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->singleD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: singleD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_singleD
static int tolua_set_Defend2015_singleD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'singleD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->singleD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: goalieD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_goalieD
static int tolua_get_Defend2015_goalieD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'goalieD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->goalieD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: goalieD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_goalieD
static int tolua_set_Defend2015_goalieD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'goalieD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->goalieD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sideD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_get_Defend2015_sideD
static int tolua_get_Defend2015_sideD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sideD'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->sideD,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sideD of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_set_Defend2015_sideD
static int tolua_set_Defend2015_sideD(lua_State* tolua_S)
{
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sideD'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sideD = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSidePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getSidePos00
static int tolua_zeus_Defend2015_getSidePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSidePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSidePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSidePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getLeftPos00
static int tolua_zeus_Defend2015_getLeftPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getLeftPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getRightPos00
static int tolua_zeus_Defend2015_getRightPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getRightPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftCenPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getLeftCenPos00
static int tolua_zeus_Defend2015_getLeftCenPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftCenPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getLeftCenPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftCenPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightCenPos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getRightCenPos00
static int tolua_zeus_Defend2015_getRightCenPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightCenPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getRightCenPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightCenPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMiddlePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getMiddlePos00
static int tolua_zeus_Defend2015_getMiddlePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMiddlePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getMiddlePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddlePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSinglePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getSinglePos00
static int tolua_zeus_Defend2015_getSinglePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSinglePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSinglePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSinglePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGoaliePos of class  Defend2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_Defend2015_getGoaliePos00
static int tolua_zeus_Defend2015_getGoaliePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Defend2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Defend2015* self = (Defend2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGoaliePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getGoaliePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGoaliePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_new00
static int tolua_zeus_CDefPos2015_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefPos2015* tolua_ret = (CDefPos2015*)  Mtolua_new((CDefPos2015)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefPos2015");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_new00_local
static int tolua_zeus_CDefPos2015_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDefPos2015* tolua_ret = (CDefPos2015*)  Mtolua_new((CDefPos2015)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDefPos2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_delete00
static int tolua_zeus_CDefPos2015_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_generatePos00
static int tolua_zeus_CDefPos2015_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefPos2015 of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getDefPos201500
static int tolua_zeus_CDefPos2015_getDefPos201500(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefPos2015'", NULL);
#endif
  {
   Defend2015 tolua_ret = (Defend2015)  self->getDefPos2015(pVision);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Defend2015)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Defend2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Defend2015));
     tolua_pushusertype(tolua_S,tolua_obj,"Defend2015");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefPos2015'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkCollision of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_checkCollision00
static int tolua_zeus_CDefPos2015_checkCollision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
  int myself = ((int)  tolua_tonumber(tolua_S,2,0));
  CGeoPoint targetPoint = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkCollision'", NULL);
#endif
  {
   double tolua_ret = (double)  self->checkCollision(myself,targetPoint,pVision);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkCollision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSidePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getSidePos00
static int tolua_zeus_CDefPos2015_getSidePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSidePos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getSidePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSidePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftPos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getLeftPos00
static int tolua_zeus_CDefPos2015_getLeftPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getLeftPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightPos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getRightPos00
static int tolua_zeus_CDefPos2015_getRightPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getRightPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftCenPos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getLeftCenPos00
static int tolua_zeus_CDefPos2015_getLeftCenPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftCenPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getLeftCenPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftCenPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightCenPos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getRightCenPos00
static int tolua_zeus_CDefPos2015_getRightCenPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightCenPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getRightCenPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightCenPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMiddlePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getMiddlePos00
static int tolua_zeus_CDefPos2015_getMiddlePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMiddlePos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getMiddlePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMiddlePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSinglePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getSinglePos00
static int tolua_zeus_CDefPos2015_getSinglePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSinglePos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getSinglePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSinglePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGoaliePos of class  CDefPos2015 */
#ifndef TOLUA_DISABLE_tolua_zeus_CDefPos2015_getGoaliePos00
static int tolua_zeus_CDefPos2015_getGoaliePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDefPos2015",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDefPos2015* self = (CDefPos2015*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGoaliePos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->getGoaliePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGoaliePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_new00
static int tolua_zeus_GameState_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameState* tolua_ret = (GameState*)  Mtolua_new((GameState)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_new00_local
static int tolua_zeus_GameState_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameState* tolua_ret = (GameState*)  Mtolua_new((GameState)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameState");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_init00
static int tolua_zeus_GameState_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameState* self = (GameState*)  tolua_tousertype(tolua_S,1,0);
  int _color = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   self->init(_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_get00
static int tolua_zeus_GameState_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
   int tolua_ret = (int)  self->get();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_set00
static int tolua_zeus_GameState_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameState* self = (GameState*)  tolua_tousertype(tolua_S,1,0);
  int _state = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
   self->set(_state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: transition of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_transition00
static int tolua_zeus_GameState_transition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameState* self = (GameState*)  tolua_tousertype(tolua_S,1,0);
  char ref_command = ((char)  tolua_tonumber(tolua_S,2,0));
  bool ball_kicked = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'transition'", NULL);
#endif
  {
   self->transition(ref_command,ball_kicked);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOn of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOn00
static int tolua_zeus_GameState_gameOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOn();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOff of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOff00
static int tolua_zeus_GameState_gameOff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOff'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOff();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gameOver of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_gameOver00
static int tolua_zeus_GameState_gameOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gameOver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->gameOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gameOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: restart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_restart00
static int tolua_zeus_GameState_restart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'restart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->restart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourRestart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourRestart00
static int tolua_zeus_GameState_ourRestart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourRestart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourRestart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourRestart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirRestart of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirRestart00
static int tolua_zeus_GameState_theirRestart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirRestart'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirRestart();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirRestart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: kickoff of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_kickoff00
static int tolua_zeus_GameState_kickoff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'kickoff'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->kickoff();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'kickoff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourKickoff of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourKickoff00
static int tolua_zeus_GameState_ourKickoff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourKickoff'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourKickoff();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourKickoff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirKickoff of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirKickoff00
static int tolua_zeus_GameState_theirKickoff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirKickoff'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirKickoff();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirKickoff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: penaltyKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_penaltyKick00
static int tolua_zeus_GameState_penaltyKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'penaltyKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->penaltyKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'penaltyKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourPenaltyKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourPenaltyKick00
static int tolua_zeus_GameState_ourPenaltyKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourPenaltyKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourPenaltyKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourPenaltyKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirPenaltyKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirPenaltyKick00
static int tolua_zeus_GameState_theirPenaltyKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirPenaltyKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirPenaltyKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirPenaltyKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: directKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_directKick00
static int tolua_zeus_GameState_directKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'directKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->directKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'directKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourDirectKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourDirectKick00
static int tolua_zeus_GameState_ourDirectKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourDirectKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourDirectKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourDirectKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirDirectKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirDirectKick00
static int tolua_zeus_GameState_theirDirectKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirDirectKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirDirectKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirDirectKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: indirectKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_indirectKick00
static int tolua_zeus_GameState_indirectKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'indirectKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->indirectKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'indirectKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourIndirectKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourIndirectKick00
static int tolua_zeus_GameState_ourIndirectKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourIndirectKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourIndirectKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourIndirectKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirIndirectKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirIndirectKick00
static int tolua_zeus_GameState_theirIndirectKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirIndirectKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirIndirectKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirIndirectKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: freeKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_freeKick00
static int tolua_zeus_GameState_freeKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'freeKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->freeKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'freeKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourFreeKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourFreeKick00
static int tolua_zeus_GameState_ourFreeKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourFreeKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourFreeKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourFreeKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirFreeKick of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirFreeKick00
static int tolua_zeus_GameState_theirFreeKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirFreeKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirFreeKick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirFreeKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ballPlacement of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ballPlacement00
static int tolua_zeus_GameState_ballPlacement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ballPlacement'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ballPlacement();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballPlacement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ourBallPlacement of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_ourBallPlacement00
static int tolua_zeus_GameState_ourBallPlacement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ourBallPlacement'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ourBallPlacement();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ourBallPlacement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theirBallPlacement of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_theirBallPlacement00
static int tolua_zeus_GameState_theirBallPlacement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theirBallPlacement'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->theirBallPlacement();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theirBallPlacement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canMove of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_canMove00
static int tolua_zeus_GameState_canMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canMove'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canMove();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: allowedNearBall of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_allowedNearBall00
static int tolua_zeus_GameState_allowedNearBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allowedNearBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->allowedNearBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'allowedNearBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canKickBall of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_canKickBall00
static int tolua_zeus_GameState_canKickBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canKickBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canKickBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canKickBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canEitherKickBall of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_canEitherKickBall00
static int tolua_zeus_GameState_canEitherKickBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canEitherKickBall'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canEitherKickBall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canEitherKickBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOurTimeout of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_isOurTimeout00
static int tolua_zeus_GameState_isOurTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOurTimeout'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOurTimeout();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOurTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTheirTimeout of class  GameState */
#ifndef TOLUA_DISABLE_tolua_zeus_GameState_isTheirTimeout00
static int tolua_zeus_GameState_isTheirTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameState* self = (const GameState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTheirTimeout'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTheirTimeout();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTheirTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_new00
static int tolua_zeus_CGDebugEngine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGDebugEngine* tolua_ret = (CGDebugEngine*)  Mtolua_new((CGDebugEngine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGDebugEngine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_new00_local
static int tolua_zeus_CGDebugEngine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGDebugEngine* tolua_ret = (CGDebugEngine*)  Mtolua_new((CGDebugEngine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGDebugEngine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_delete00
static int tolua_zeus_CGDebugEngine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_x of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_x00
static int tolua_zeus_CGDebugEngine_gui_debug_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,3,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_x'", NULL);
#endif
  {
   self->gui_debug_x(*p,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_line of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_line00
static int tolua_zeus_CGDebugEngine_gui_debug_line00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,4,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_line'", NULL);
#endif
  {
   self->gui_debug_line(*p1,*p2,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_line'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_arc of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_arc00
static int tolua_zeus_CGDebugEngine_gui_debug_arc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double r = ((double)  tolua_tonumber(tolua_S,3,0));
  double start_angle = ((double)  tolua_tonumber(tolua_S,4,0));
  double span_angle = ((double)  tolua_tonumber(tolua_S,5,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,6,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_arc'", NULL);
#endif
  {
   self->gui_debug_arc(*p,r,start_angle,span_angle,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_arc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_triangle of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_triangle00
static int tolua_zeus_CGDebugEngine_gui_debug_triangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const CGeoPoint* p3 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,5,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_triangle'", NULL);
#endif
  {
   self->gui_debug_triangle(*p1,*p2,*p3,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_triangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_robot of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_robot00
static int tolua_zeus_CGDebugEngine_gui_debug_robot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double robot_dir = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_robot'", NULL);
#endif
  {
   self->gui_debug_robot(*p,robot_dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_robot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_msg of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_msg00
static int tolua_zeus_CGDebugEngine_gui_debug_msg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const char* msgstr = ((const char*)  tolua_tostring(tolua_S,3,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,4,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_msg'", NULL);
#endif
  {
   self->gui_debug_msg(*p,msgstr,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_msg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gui_debug_curve of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_gui_debug_curve00
static int tolua_zeus_CGDebugEngine_gui_debug_curve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  const double num = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double maxLimit = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double minLimit = ((const double)  tolua_tonumber(tolua_S,4,0));
  char debug_color = ((char)  tolua_tonumber(tolua_S,5,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gui_debug_curve'", NULL);
#endif
  {
   self->gui_debug_curve(num,maxLimit,minLimit,debug_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gui_debug_curve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  CGDebugEngine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGDebugEngine_send00
static int tolua_zeus_CGDebugEngine_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGDebugEngine",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGDebugEngine* self = (CGDebugEngine*)  tolua_tousertype(tolua_S,1,0);
  bool teamIsBlue = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'send'", NULL);
#endif
  {
   self->send(teamIsBlue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new00
static int tolua_zeus_CVector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new00_local
static int tolua_zeus_CVector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new01
static int tolua_zeus_CVector_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new01_local
static int tolua_zeus_CVector_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new02
static int tolua_zeus_CVector_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(*v));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_new02_local
static int tolua_zeus_CVector_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   CVector* tolua_ret = (CVector*)  Mtolua_new((CVector)(*v));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVector of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_setVector00
static int tolua_zeus_CVector_setVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVector* self = (CVector*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVector'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setVector(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mod of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_mod00
static int tolua_zeus_CVector_mod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mod'", NULL);
#endif
  {
   double tolua_ret = (double)  self->mod();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mod2 of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_mod200
static int tolua_zeus_CVector_mod200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mod2'", NULL);
#endif
  {
   double tolua_ret = (double)  self->mod2();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mod2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dir of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_dir00
static int tolua_zeus_CVector_dir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: theta of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_theta00
static int tolua_zeus_CVector_theta00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CVector* self = (CVector*)  tolua_tousertype(tolua_S,1,0);
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'theta'", NULL);
#endif
  {
   double tolua_ret = (double)  self->theta(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'theta'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_rotate00
static int tolua_zeus_CVector_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double angle = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->rotate(angle);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unit of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_unit00
static int tolua_zeus_CVector_unit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unit'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->unit();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_x00
static int tolua_zeus_CVector_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'", NULL);
#endif
  {
   double tolua_ret = (double)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_y00
static int tolua_zeus_CVector_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: value of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector_value00
static int tolua_zeus_CVector_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double angle = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'value'", NULL);
#endif
  {
   double tolua_ret = (double)  self->value(angle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'value'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__add00
static int tolua_zeus_CVector__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__sub00
static int tolua_zeus_CVector__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__mul00
static int tolua_zeus_CVector__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double a = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator*(a);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__mul01
static int tolua_zeus_CVector__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  CVector b = *((CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   double tolua_ret = (double)  self->operator*(b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__div00
static int tolua_zeus_CVector__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
  double a = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator/(a);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CVector */
#ifndef TOLUA_DISABLE_tolua_zeus_CVector__sub01
static int tolua_zeus_CVector__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* self = (const CVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CVector__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new00
static int tolua_zeus_CGeoPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new00_local
static int tolua_zeus_CGeoPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_delete00
static int tolua_zeus_CGeoPoint_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new01
static int tolua_zeus_CGeoPoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new01_local
static int tolua_zeus_CGeoPoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new02
static int tolua_zeus_CGeoPoint_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(*p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_new02_local
static int tolua_zeus_CGeoPoint_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint* tolua_ret = (CGeoPoint*)  Mtolua_new((CGeoPoint)(*p));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoPoint_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__eq00
static int tolua_zeus_CGeoPoint__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* rhs = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_x00
static int tolua_zeus_CGeoPoint_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'", NULL);
#endif
  {
   double tolua_ret = (double)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_y00
static int tolua_zeus_CGeoPoint_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setX of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_setX00
static int tolua_zeus_CGeoPoint_setX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setX'", NULL);
#endif
  {
   self->setX(x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setY of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_setY00
static int tolua_zeus_CGeoPoint_setY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  double y = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setY'", NULL);
#endif
  {
   self->setY(y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fill of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_fill00
static int tolua_zeus_CGeoPoint_fill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint* self = (CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->fill(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_dist00
static int tolua_zeus_CGeoPoint_dist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist2 of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_dist200
static int tolua_zeus_CGeoPoint_dist200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist2'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist2(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__add00
static int tolua_zeus_CGeoPoint__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__mul00
static int tolua_zeus_CGeoPoint__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const double a = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->operator*(a);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)a);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint__sub00
static int tolua_zeus_CGeoPoint__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   CVector tolua_ret = (CVector)  self->operator-(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: midPoint of class  CGeoPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoPoint_midPoint00
static int tolua_zeus_CGeoPoint_midPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* self = (const CGeoPoint*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'midPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->midPoint(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'midPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new00
static int tolua_zeus_CGeoLine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new00_local
static int tolua_zeus_CGeoLine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new01
static int tolua_zeus_CGeoLine_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new01_local
static int tolua_zeus_CGeoLine_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new02
static int tolua_zeus_CGeoLine_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double angle = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p,angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_new02_local
static int tolua_zeus_CGeoLine_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double angle = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoLine* tolua_ret = (CGeoLine*)  Mtolua_new((CGeoLine)(*p,angle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLine");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoLine_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: calABC of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_calABC00
static int tolua_zeus_CGeoLine_calABC00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLine* self = (CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calABC'", NULL);
#endif
  {
   self->calABC();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calABC'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: projection of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_projection00
static int tolua_zeus_CGeoLine_projection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'projection'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->projection(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'projection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_point100
static int tolua_zeus_CGeoLine_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->point1();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_point200
static int tolua_zeus_CGeoLine_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->point2();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine__eq00
static int tolua_zeus_CGeoLine__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoLine",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoLine* self = (CGeoLine*)  tolua_tousertype(tolua_S,1,0);
  const CGeoLine* rhs = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: a of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_a00
static int tolua_zeus_CGeoLine_a00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'a'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->a();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'a'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: b of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_b00
static int tolua_zeus_CGeoLine_b00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'b'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->b();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'b'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: c of class  CGeoLine */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLine_c00
static int tolua_zeus_CGeoLine_c00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* self = (const CGeoLine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'c'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->c();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_new00
static int tolua_zeus_CGeoLineLineIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineLineIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line_1 = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoLine* line_2 = ((const CGeoLine*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineLineIntersection* tolua_ret = (CGeoLineLineIntersection*)  Mtolua_new((CGeoLineLineIntersection)(*line_1,*line_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineLineIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_new00_local
static int tolua_zeus_CGeoLineLineIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineLineIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line_1 = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoLine* line_2 = ((const CGeoLine*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineLineIntersection* tolua_ret = (CGeoLineLineIntersection*)  Mtolua_new((CGeoLineLineIntersection)(*line_1,*line_2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineLineIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Intersectant of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_Intersectant00
static int tolua_zeus_CGeoLineLineIntersection_Intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineLineIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineLineIntersection* self = (const CGeoLineLineIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IntersectPoint of class  CGeoLineLineIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineLineIntersection_IntersectPoint00
static int tolua_zeus_CGeoLineLineIntersection_IntersectPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineLineIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineLineIntersection* self = (const CGeoLineLineIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IntersectPoint'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->IntersectPoint();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IntersectPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new00
static int tolua_zeus_CGeoSegment_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new00_local
static int tolua_zeus_CGeoSegment_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new01
static int tolua_zeus_CGeoSegment_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoSegment_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_new01_local
static int tolua_zeus_CGeoSegment_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegment* tolua_ret = (CGeoSegment*)  Mtolua_new((CGeoSegment)(*p1,*p2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegment");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoSegment_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPointOnLineOnSegment of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00
static int tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPointOnLineOnSegment'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPointOnLineOnSegment(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPointOnLineOnSegment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSegmentsIntersect of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_IsSegmentsIntersect00
static int tolua_zeus_CGeoSegment_IsSegmentsIntersect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoSegment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoSegment* p = ((const CGeoSegment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSegmentsIntersect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSegmentsIntersect(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSegmentsIntersect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: segmentsIntersectPoint of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_segmentsIntersectPoint00
static int tolua_zeus_CGeoSegment_segmentsIntersectPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoSegment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoSegment* p = ((const CGeoSegment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'segmentsIntersectPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->segmentsIntersectPoint(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'segmentsIntersectPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist2Point of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_dist2Point00
static int tolua_zeus_CGeoSegment_dist2Point00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoSegment* self = (CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist2Point'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist2Point(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist2Point'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist2Segment of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_dist2Segment00
static int tolua_zeus_CGeoSegment_dist2Segment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoSegment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoSegment* self = (CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
  const CGeoSegment* s = ((const CGeoSegment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist2Segment'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist2Segment(*s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist2Segment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_start00
static int tolua_zeus_CGeoSegment_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->start();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_end00
static int tolua_zeus_CGeoSegment_end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* self = (const CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->end();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: center of class  CGeoSegment */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegment_center00
static int tolua_zeus_CGeoSegment_center00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoSegment",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoSegment* self = (CGeoSegment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'center'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->center();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'center'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CGeoShape */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoShape_delete00
static int tolua_zeus_CGeoShape_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoShape* self = (CGeoShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasPoint of class  CGeoShape */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoShape_HasPoint00
static int tolua_zeus_CGeoShape_HasPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoShape* self = (const CGeoShape*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasPoint(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new00
static int tolua_zeus_CGeoRectangle_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new00_local
static int tolua_zeus_CGeoRectangle_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new01
static int tolua_zeus_CGeoRectangle_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* leftTop = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* rightDown = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(*leftTop,*rightDown));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoRectangle_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new01_local
static int tolua_zeus_CGeoRectangle_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* leftTop = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* rightDown = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(*leftTop,*rightDown));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoRectangle_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new02
static int tolua_zeus_CGeoRectangle_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double y1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(x1,y1,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoRectangle_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_new02_local
static int tolua_zeus_CGeoRectangle_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double y1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
  {
   CGeoRectangle* tolua_ret = (CGeoRectangle*)  Mtolua_new((CGeoRectangle)(x1,y1,x2,y2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoRectangle");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoRectangle_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: calPoint of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_calPoint00
static int tolua_zeus_CGeoRectangle_calPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoRectangle* self = (CGeoRectangle*)  tolua_tousertype(tolua_S,1,0);
  double x1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double y1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calPoint'", NULL);
#endif
  {
   self->calPoint(x1,y1,x2,y2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist2Point of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_dist2Point00
static int tolua_zeus_CGeoRectangle_dist2Point00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoRectangle* self = (CGeoRectangle*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist2Point'", NULL);
#endif
  {
   double tolua_ret = (double)  self->dist2Point(*p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist2Point'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasPoint of class  CGeoRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoRectangle_HasPoint00
static int tolua_zeus_CGeoRectangle_HasPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoRectangle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoRectangle* self = (const CGeoRectangle*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasPoint(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_new00
static int tolua_zeus_CGeoLineRectangleIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoRectangle* rect = ((const CGeoRectangle*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineRectangleIntersection* tolua_ret = (CGeoLineRectangleIntersection*)  Mtolua_new((CGeoLineRectangleIntersection)(*line,*rect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineRectangleIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_new00_local
static int tolua_zeus_CGeoLineRectangleIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineRectangleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoRectangle",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoRectangle* rect = ((const CGeoRectangle*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineRectangleIntersection* tolua_ret = (CGeoLineRectangleIntersection*)  Mtolua_new((CGeoLineRectangleIntersection)(*line,*rect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineRectangleIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectant of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_intersectant00
static int tolua_zeus_CGeoLineRectangleIntersection_intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineRectangleIntersection* self = (const CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_point100
static int tolua_zeus_CGeoLineRectangleIntersection_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineRectangleIntersection* self = (const CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point1();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLineRectangleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineRectangleIntersection_point200
static int tolua_zeus_CGeoLineRectangleIntersection_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineRectangleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineRectangleIntersection* self = (const CGeoLineRectangleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_new00
static int tolua_zeus_CGeoCirlce_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoCirlce",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoCirlce* tolua_ret = (CGeoCirlce*)  Mtolua_new((CGeoCirlce)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoCirlce");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_new00_local
static int tolua_zeus_CGeoCirlce_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoCirlce",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoCirlce* tolua_ret = (CGeoCirlce*)  Mtolua_new((CGeoCirlce)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoCirlce");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_new01
static int tolua_zeus_CGeoCirlce_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoCirlce",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* c = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double r = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoCirlce* tolua_ret = (CGeoCirlce*)  Mtolua_new((CGeoCirlce)(*c,r));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoCirlce");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoCirlce_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_new01_local
static int tolua_zeus_CGeoCirlce_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoCirlce",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* c = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double r = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CGeoCirlce* tolua_ret = (CGeoCirlce*)  Mtolua_new((CGeoCirlce)(*c,r));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoCirlce");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoCirlce_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasPoint of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_HasPoint00
static int tolua_zeus_CGeoCirlce_HasPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoCirlce",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoCirlce* self = (const CGeoCirlce*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasPoint(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Center of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_Center00
static int tolua_zeus_CGeoCirlce_Center00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoCirlce",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoCirlce* self = (const CGeoCirlce*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Center'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->Center();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Center'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Radius of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_Radius00
static int tolua_zeus_CGeoCirlce_Radius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoCirlce",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoCirlce* self = (const CGeoCirlce*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Radius'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Radius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Radius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Radius2 of class  CGeoCirlce */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoCirlce_Radius200
static int tolua_zeus_CGeoCirlce_Radius200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoCirlce",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoCirlce* self = (const CGeoCirlce*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Radius2'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Radius2();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Radius2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineCircleIntersection_new00
static int tolua_zeus_CGeoLineCircleIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineCircleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoCirlce",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoCirlce* circle = ((const CGeoCirlce*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineCircleIntersection* tolua_ret = (CGeoLineCircleIntersection*)  Mtolua_new((CGeoLineCircleIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineCircleIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineCircleIntersection_new00_local
static int tolua_zeus_CGeoLineCircleIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineCircleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoCirlce",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoCirlce* circle = ((const CGeoCirlce*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineCircleIntersection* tolua_ret = (CGeoLineCircleIntersection*)  Mtolua_new((CGeoLineCircleIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineCircleIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectant of class  CGeoLineCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineCircleIntersection_intersectant00
static int tolua_zeus_CGeoLineCircleIntersection_intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineCircleIntersection* self = (const CGeoLineCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLineCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineCircleIntersection_point100
static int tolua_zeus_CGeoLineCircleIntersection_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineCircleIntersection* self = (const CGeoLineCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point1();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLineCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineCircleIntersection_point200
static int tolua_zeus_CGeoLineCircleIntersection_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineCircleIntersection* self = (const CGeoLineCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_new00
static int tolua_zeus_CGeoEllipse_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoEllipse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoEllipse* tolua_ret = (CGeoEllipse*)  Mtolua_new((CGeoEllipse)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoEllipse");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_new00_local
static int tolua_zeus_CGeoEllipse_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoEllipse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGeoEllipse* tolua_ret = (CGeoEllipse*)  Mtolua_new((CGeoEllipse)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoEllipse");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_new01
static int tolua_zeus_CGeoEllipse_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoEllipse",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGeoPoint c = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double m = ((double)  tolua_tonumber(tolua_S,3,0));
  double n = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoEllipse* tolua_ret = (CGeoEllipse*)  Mtolua_new((CGeoEllipse)(c,m,n));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoEllipse");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoEllipse_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_new01_local
static int tolua_zeus_CGeoEllipse_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoEllipse",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CGeoPoint c = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double m = ((double)  tolua_tonumber(tolua_S,3,0));
  double n = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoEllipse* tolua_ret = (CGeoEllipse*)  Mtolua_new((CGeoEllipse)(c,m,n));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoEllipse");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_CGeoEllipse_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Center of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_Center00
static int tolua_zeus_CGeoEllipse_Center00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoEllipse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoEllipse* self = (const CGeoEllipse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Center'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->Center();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Center'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasPoint of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_HasPoint00
static int tolua_zeus_CGeoEllipse_HasPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoEllipse",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoEllipse* self = (const CGeoEllipse*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasPoint(*p);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Xaxis of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_Xaxis00
static int tolua_zeus_CGeoEllipse_Xaxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoEllipse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoEllipse* self = (const CGeoEllipse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Xaxis'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Xaxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Xaxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Yaxis of class  CGeoEllipse */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoEllipse_Yaxis00
static int tolua_zeus_CGeoEllipse_Yaxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoEllipse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoEllipse* self = (const CGeoEllipse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Yaxis'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Yaxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Yaxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoLineEllipseIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineEllipseIntersection_new00
static int tolua_zeus_CGeoLineEllipseIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineEllipseIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoEllipse",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoEllipse* circle = ((const CGeoEllipse*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineEllipseIntersection* tolua_ret = (CGeoLineEllipseIntersection*)  Mtolua_new((CGeoLineEllipseIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineEllipseIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoLineEllipseIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineEllipseIntersection_new00_local
static int tolua_zeus_CGeoLineEllipseIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoLineEllipseIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoLine",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoEllipse",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLine* line = ((const CGeoLine*)  tolua_tousertype(tolua_S,2,0));
  const CGeoEllipse* circle = ((const CGeoEllipse*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoLineEllipseIntersection* tolua_ret = (CGeoLineEllipseIntersection*)  Mtolua_new((CGeoLineEllipseIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoLineEllipseIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectant of class  CGeoLineEllipseIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineEllipseIntersection_intersectant00
static int tolua_zeus_CGeoLineEllipseIntersection_intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineEllipseIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineEllipseIntersection* self = (const CGeoLineEllipseIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoLineEllipseIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineEllipseIntersection_point100
static int tolua_zeus_CGeoLineEllipseIntersection_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineEllipseIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineEllipseIntersection* self = (const CGeoLineEllipseIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point1();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoLineEllipseIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoLineEllipseIntersection_point200
static int tolua_zeus_CGeoLineEllipseIntersection_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoLineEllipseIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoLineEllipseIntersection* self = (const CGeoLineEllipseIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_new00
static int tolua_zeus_CGeoSegmentCircleIntersection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegmentCircleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoSegment",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoCirlce",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* line = ((const CGeoSegment*)  tolua_tousertype(tolua_S,2,0));
  const CGeoCirlce* circle = ((const CGeoCirlce*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegmentCircleIntersection* tolua_ret = (CGeoSegmentCircleIntersection*)  Mtolua_new((CGeoSegmentCircleIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegmentCircleIntersection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_new00_local
static int tolua_zeus_CGeoSegmentCircleIntersection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGeoSegmentCircleIntersection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoSegment",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoCirlce",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegment* line = ((const CGeoSegment*)  tolua_tousertype(tolua_S,2,0));
  const CGeoCirlce* circle = ((const CGeoCirlce*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoSegmentCircleIntersection* tolua_ret = (CGeoSegmentCircleIntersection*)  Mtolua_new((CGeoSegmentCircleIntersection)(*line,*circle));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGeoSegmentCircleIntersection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectant of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_intersectant00
static int tolua_zeus_CGeoSegmentCircleIntersection_intersectant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegmentCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegmentCircleIntersection* self = (const CGeoSegmentCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectant'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectant();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point1 of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_point100
static int tolua_zeus_CGeoSegmentCircleIntersection_point100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegmentCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegmentCircleIntersection* self = (const CGeoSegmentCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point1'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point1();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point2 of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_point200
static int tolua_zeus_CGeoSegmentCircleIntersection_point200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CGeoSegmentCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoSegmentCircleIntersection* self = (const CGeoSegmentCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point2'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->point2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  CGeoSegmentCircleIntersection */
#ifndef TOLUA_DISABLE_tolua_zeus_CGeoSegmentCircleIntersection_size00
static int tolua_zeus_CGeoSegmentCircleIntersection_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGeoSegmentCircleIntersection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoSegmentCircleIntersection* self = (CGeoSegmentCircleIntersection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: paramManager */
#ifndef TOLUA_DISABLE_tolua_get_paramManager_ptr
static int tolua_get_paramManager_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)paramManager,"CParamManagerSkill");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: paramManager */
#ifndef TOLUA_DISABLE_tolua_set_paramManager_ptr
static int tolua_set_paramManager_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CParamManagerSkill",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  paramManager = ((CParamManagerSkill*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: oParamManager */
#ifndef TOLUA_DISABLE_tolua_get_oParamManager_ptr
static int tolua_get_oParamManager_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)oParamManager,"ParamManagerOwl");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: oParamManager */
#ifndef TOLUA_DISABLE_tolua_set_oParamManager_ptr
static int tolua_set_oParamManager_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"ParamManagerOwl",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  oParamManager = ((ParamManagerOwl*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cParamManager */
#ifndef TOLUA_DISABLE_tolua_get_cParamManager_ptr
static int tolua_get_cParamManager_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)cParamManager,"ParamManagerCfg");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cParamManager */
#ifndef TOLUA_DISABLE_tolua_set_cParamManager_ptr
static int tolua_set_cParamManager_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"ParamManagerCfg",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  cParamManager = ((ParamManagerCfg*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vParamManager */
#ifndef TOLUA_DISABLE_tolua_get_vParamManager_ptr
static int tolua_get_vParamManager_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)vParamManager,"ParamManagerVision");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vParamManager */
#ifndef TOLUA_DISABLE_tolua_set_vParamManager_ptr
static int tolua_set_vParamManager_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"ParamManagerVision",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  vParamManager = ((ParamManagerVision*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sParamManager */
#ifndef TOLUA_DISABLE_tolua_get_sParamManager_ptr
static int tolua_get_sParamManager_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)sParamManager,"ParamManagerSimulator");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sParamManager */
#ifndef TOLUA_DISABLE_tolua_set_sParamManager_ptr
static int tolua_set_sParamManager_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"ParamManagerSimulator",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  sParamManager = ((ParamManagerSimulator*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vision */
#ifndef TOLUA_DISABLE_tolua_get_vision_ptr
static int tolua_get_vision_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)vision,"CVisionModule");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vision */
#ifndef TOLUA_DISABLE_tolua_set_vision_ptr
static int tolua_set_vision_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CVisionModule",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  vision = ((CVisionModule*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: kickStatus */
#ifndef TOLUA_DISABLE_tolua_get_kickStatus_ptr
static int tolua_get_kickStatus_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)kickStatus,"CKickStatus");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: kickStatus */
#ifndef TOLUA_DISABLE_tolua_set_kickStatus_ptr
static int tolua_set_kickStatus_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CKickStatus",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  kickStatus = ((CKickStatus*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dribbleStatus */
#ifndef TOLUA_DISABLE_tolua_get_dribbleStatus_ptr
static int tolua_get_dribbleStatus_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)dribbleStatus,"CDribbleStatus");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dribbleStatus */
#ifndef TOLUA_DISABLE_tolua_set_dribbleStatus_ptr
static int tolua_set_dribbleStatus_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDribbleStatus",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  dribbleStatus = ((CDribbleStatus*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: debugEngine */
#ifndef TOLUA_DISABLE_tolua_get_debugEngine_ptr
static int tolua_get_debugEngine_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)debugEngine,"CGDebugEngine");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: debugEngine */
#ifndef TOLUA_DISABLE_tolua_set_debugEngine_ptr
static int tolua_set_debugEngine_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CGDebugEngine",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  debugEngine = ((CGDebugEngine*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: world */
#ifndef TOLUA_DISABLE_tolua_get_world_ptr
static int tolua_get_world_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)world,"CWorldModel");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: world */
#ifndef TOLUA_DISABLE_tolua_set_world_ptr
static int tolua_set_world_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CWorldModel",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  world = ((CWorldModel*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: kickDirection */
#ifndef TOLUA_DISABLE_tolua_get_kickDirection_ptr
static int tolua_get_kickDirection_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)kickDirection,"CKickDirection");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: kickDirection */
#ifndef TOLUA_DISABLE_tolua_set_kickDirection_ptr
static int tolua_set_kickDirection_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CKickDirection",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  kickDirection = ((CKickDirection*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bestAlg */
#ifndef TOLUA_DISABLE_tolua_get_bestAlg_ptr
static int tolua_get_bestAlg_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)bestAlg,"CGPUBestAlgThread");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bestAlg */
#ifndef TOLUA_DISABLE_tolua_set_bestAlg_ptr
static int tolua_set_bestAlg_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CGPUBestAlgThread",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  bestAlg = ((CGPUBestAlgThread*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defPos2015 */
#ifndef TOLUA_DISABLE_tolua_get_defPos2015_ptr
static int tolua_get_defPos2015_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)defPos2015,"CDefPos2015");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defPos2015 */
#ifndef TOLUA_DISABLE_tolua_set_defPos2015_ptr
static int tolua_set_defPos2015_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDefPos2015",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  defPos2015 = ((CDefPos2015*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: guardPos */
#ifndef TOLUA_DISABLE_tolua_get_guardPos_ptr
static int tolua_get_guardPos_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)guardPos,"CGuardPos");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: guardPos */
#ifndef TOLUA_DISABLE_tolua_set_guardPos_ptr
static int tolua_set_guardPos_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CGuardPos",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  guardPos = ((CGuardPos*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defPos2013 */
#ifndef TOLUA_DISABLE_tolua_get_defPos2013_ptr
static int tolua_get_defPos2013_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)defPos2013,"CDefPos2013");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defPos2013 */
#ifndef TOLUA_DISABLE_tolua_set_defPos2013_ptr
static int tolua_set_defPos2013_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDefPos2013",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  defPos2013 = ((CDefPos2013*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tandemPos */
#ifndef TOLUA_DISABLE_tolua_get_tandemPos_ptr
static int tolua_get_tandemPos_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)tandemPos,"CTandemPos");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tandemPos */
#ifndef TOLUA_DISABLE_tolua_set_tandemPos_ptr
static int tolua_set_tandemPos_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CTandemPos",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  tandemPos = ((CTandemPos*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bestPlayer */
#ifndef TOLUA_DISABLE_tolua_get_bestPlayer_ptr
static int tolua_get_bestPlayer_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)bestPlayer,"CBestPlayer");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bestPlayer */
#ifndef TOLUA_DISABLE_tolua_set_bestPlayer_ptr
static int tolua_set_bestPlayer_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CBestPlayer",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  bestPlayer = ((CBestPlayer*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defenceInfo */
#ifndef TOLUA_DISABLE_tolua_get_defenceInfo_ptr
static int tolua_get_defenceInfo_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)defenceInfo,"CDefenceInfo");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defenceInfo */
#ifndef TOLUA_DISABLE_tolua_set_defenceInfo_ptr
static int tolua_set_defenceInfo_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CDefenceInfo",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  defenceInfo = ((CDefenceInfo*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: chipBallJudge */
#ifndef TOLUA_DISABLE_tolua_get_chipBallJudge_ptr
static int tolua_get_chipBallJudge_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)chipBallJudge,"CChipBallJudge");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: chipBallJudge */
#ifndef TOLUA_DISABLE_tolua_set_chipBallJudge_ptr
static int tolua_set_chipBallJudge_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CChipBallJudge",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  chipBallJudge = ((CChipBallJudge*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: indirectDefender */
#ifndef TOLUA_DISABLE_tolua_get_indirectDefender_ptr
static int tolua_get_indirectDefender_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)indirectDefender,"CIndirectDefender");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: indirectDefender */
#ifndef TOLUA_DISABLE_tolua_set_indirectDefender_ptr
static int tolua_set_indirectDefender_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CIndirectDefender",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  indirectDefender = ((CIndirectDefender*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: supportPos */
#ifndef TOLUA_DISABLE_tolua_get_supportPos_ptr
static int tolua_get_supportPos_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)supportPos,"CSupportPos");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: supportPos */
#ifndef TOLUA_DISABLE_tolua_set_supportPos_ptr
static int tolua_set_supportPos_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CSupportPos",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  supportPos = ((CSupportPos*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: supportPos2022 */
#ifndef TOLUA_DISABLE_tolua_get_supportPos2022_ptr
static int tolua_get_supportPos2022_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)supportPos2022,"CSupportPos2022");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: supportPos2022 */
#ifndef TOLUA_DISABLE_tolua_set_supportPos2022_ptr
static int tolua_set_supportPos2022_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"CSupportPos2022",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  supportPos2022 = ((CSupportPos2022*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: initializeSingleton */
#ifndef TOLUA_DISABLE_tolua_zeus_initializeSingleton00
static int tolua_zeus_initializeSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   initializeSingleton();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initializeSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_new00
static int tolua_zeus_CGuardPos_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGuardPos* tolua_ret = (CGuardPos*)  Mtolua_new((CGuardPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGuardPos");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_new00_local
static int tolua_zeus_CGuardPos_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGuardPos* tolua_ret = (CGuardPos*)  Mtolua_new((CGuardPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGuardPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: backPos of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_backPos00
static int tolua_zeus_CGuardPos_backPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGuardPos* self = (CGuardPos*)  tolua_tousertype(tolua_S,1,0);
  int guardNum = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'backPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->backPos(guardNum,index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'backPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackNum of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_setBackNum00
static int tolua_zeus_CGuardPos_setBackNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGuardPos* self = (CGuardPos*)  tolua_tousertype(tolua_S,1,0);
  int realNum = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackNum'", NULL);
#endif
  {
   self->setBackNum(realNum,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkValidNum of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_checkValidNum00
static int tolua_zeus_CGuardPos_checkValidNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGuardPos* self = (CGuardPos*)  tolua_tousertype(tolua_S,1,0);
  int guardNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkValidNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->checkValidNum(guardNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkValidNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: validBackPos of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_validBackPos00
static int tolua_zeus_CGuardPos_validBackPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGuardPos* self = (CGuardPos*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint backPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  int realNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'validBackPos'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->validBackPos(backPos,realNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'validBackPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: missingBackIndex of class  CGuardPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CGuardPos_missingBackIndex00
static int tolua_zeus_CGuardPos_missingBackIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGuardPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGuardPos* self = (CGuardPos*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'missingBackIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->missingBackIndex(i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'missingBackIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _Left of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea__Left
static int tolua_get_KickOffArea__Left(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Left'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_Left,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _Left of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea__Left
static int tolua_set_KickOffArea__Left(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Left'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_Left = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _Right of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea__Right
static int tolua_get_KickOffArea__Right(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Right'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->_Right,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _Right of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea__Right
static int tolua_set_KickOffArea__Right(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_Right'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_Right = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: baseDir of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea_baseDir
static int tolua_get_KickOffArea_baseDir(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDir'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->baseDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: baseDir of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea_baseDir
static int tolua_set_KickOffArea_baseDir(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDir'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDir = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: radius of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_get_KickOffArea_radius
static int tolua_get_KickOffArea_radius(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->radius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: radius of class  KickOffArea */
#ifndef TOLUA_DISABLE_tolua_set_KickOffArea_radius
static int tolua_set_KickOffArea_radius(lua_State* tolua_S)
{
  KickOffArea* self = (KickOffArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->radius = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: onePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_get_TwoKickPos_onePos
static int tolua_get_TwoKickPos_onePos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'onePos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->onePos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: onePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_set_TwoKickPos_onePos
static int tolua_set_TwoKickPos_onePos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'onePos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->onePos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_get_TwoKickPos_anotherPos
static int tolua_get_TwoKickPos_anotherPos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anotherPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->anotherPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_set_TwoKickPos_anotherPos
static int tolua_set_TwoKickPos_anotherPos(lua_State* tolua_S)
{
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anotherPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anotherPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOnePos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_zeus_TwoKickPos_getOnePos00
static int tolua_zeus_TwoKickPos_getOnePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TwoKickPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOnePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getOnePos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOnePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnotherPos of class  TwoKickPos */
#ifndef TOLUA_DISABLE_tolua_zeus_TwoKickPos_getAnotherPos00
static int tolua_zeus_TwoKickPos_getAnotherPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TwoKickPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TwoKickPos* self = (TwoKickPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnotherPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getAnotherPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnotherPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_new00
static int tolua_zeus_CIndirectDefender_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIndirectDefender* tolua_ret = (CIndirectDefender*)  Mtolua_new((CIndirectDefender)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CIndirectDefender");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_new00_local
static int tolua_zeus_CIndirectDefender_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIndirectDefender* tolua_ret = (CIndirectDefender*)  Mtolua_new((CIndirectDefender)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CIndirectDefender");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_delete00
static int tolua_zeus_CIndirectDefender_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefPos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_getDefPos00
static int tolua_zeus_CIndirectDefender_getDefPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double radius = ((double)  tolua_tonumber(tolua_S,3,0));
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
  int mode = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getDefPos(pVision,radius,leftUp,rightDown,mode);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTwoDefPos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_getTwoDefPos00
static int tolua_zeus_CIndirectDefender_getTwoDefPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,8,&tolua_err) || !tolua_isusertype(tolua_S,8,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double radius1 = ((double)  tolua_tonumber(tolua_S,3,0));
  CGeoPoint left1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint right1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
  double radius2 = ((double)  tolua_tonumber(tolua_S,6,0));
  CGeoPoint left2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,7,0));
  CGeoPoint right2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTwoDefPos'", NULL);
#endif
  {
   TwoKickPos tolua_ret = (TwoKickPos)  self->getTwoDefPos(pVision,radius1,left1,right1,radius2,left2,right2);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((TwoKickPos)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"TwoKickPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(TwoKickPos));
     tolua_pushusertype(tolua_S,tolua_obj,"TwoKickPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTwoDefPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateTwoDefPos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_generateTwoDefPos00
static int tolua_zeus_CIndirectDefender_generateTwoDefPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateTwoDefPos'", NULL);
#endif
  {
   self->generateTwoDefPos(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateTwoDefPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_generatePos00
static int tolua_zeus_CIndirectDefender_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->generatePos(pVision);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefendPos of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_DefendPos00
static int tolua_zeus_CIndirectDefender_DefendPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint ballPos = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const double dir = ((const double)  tolua_tonumber(tolua_S,3,0));
  double radius = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefendPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->DefendPos(ballPos,dir,radius);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefendPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindMinMax of class  CIndirectDefender */
#ifndef TOLUA_DISABLE_tolua_zeus_CIndirectDefender_FindMinMax00
static int tolua_zeus_CIndirectDefender_FindMinMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIndirectDefender",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIndirectDefender* self = (CIndirectDefender*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindMinMax'", NULL);
#endif
  {
   self->FindMinMax(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindMinMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_new00
static int tolua_zeus_CKickDirection_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickDirection* tolua_ret = (CKickDirection*)  Mtolua_new((CKickDirection)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickDirection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_new00_local
static int tolua_zeus_CKickDirection_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickDirection* tolua_ret = (CKickDirection*)  Mtolua_new((CKickDirection)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickDirection");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateShootDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_GenerateShootDir00
static int tolua_zeus_CKickDirection_GenerateShootDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  const int player = ((const int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint pos = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateShootDir'", NULL);
#endif
  {
   self->GenerateShootDir(player,pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateShootDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKickValid of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getKickValid00
static int tolua_zeus_CKickDirection_getKickValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKickValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getKickValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKickValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCompensate of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getCompensate00
static int tolua_zeus_CKickDirection_getCompensate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCompensate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCompensate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCompensate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRawKickDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getRawKickDir00
static int tolua_zeus_CKickDirection_getRawKickDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRawKickDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getRawKickDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRawKickDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCompensateDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getCompensateDir00
static int tolua_zeus_CKickDirection_getCompensateDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCompensateDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getCompensateDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCompensateDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRealKickDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getRealKickDir00
static int tolua_zeus_CKickDirection_getRealKickDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRealKickDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getRealKickDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRealKickDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsKickValid of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getIsKickValid00
static int tolua_zeus_CKickDirection_getIsKickValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsKickValid'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getIsKickValid();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsKickValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRawDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getRawDir00
static int tolua_zeus_CKickDirection_getRawDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRawDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getRawDir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRawDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calCompensate of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_calCompensate00
static int tolua_zeus_CKickDirection_calCompensate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calCompensate'", NULL);
#endif
  {
   double tolua_ret = (double)  self->calCompensate(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calCompensate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calGussiFuncA of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_calGussiFuncA00
static int tolua_zeus_CKickDirection_calGussiFuncA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  double x1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double y1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calGussiFuncA'", NULL);
#endif
  {
   double tolua_ret = (double)  self->calGussiFuncA(x1,y1,x2,y2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calGussiFuncA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calGussiFuncB of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_calGussiFuncB00
static int tolua_zeus_CKickDirection_calGussiFuncB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  double x1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double y1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double x2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double y2 = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calGussiFuncB'", NULL);
#endif
  {
   double tolua_ret = (double)  self->calGussiFuncB(x1,y1,x2,y2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calGussiFuncB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPointShootDir of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_getPointShootDir00
static int tolua_zeus_CKickDirection_getPointShootDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint startPoint = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPointShootDir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getPointShootDir(pVision,startPoint);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPointShootDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTheShootPoint of class  CKickDirection */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickDirection_GetTheShootPoint00
static int tolua_zeus_CKickDirection_GetTheShootPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickDirection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickDirection* self = (CKickDirection*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint startPoint = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTheShootPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->GetTheShootPoint(pVision,startPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTheShootPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_new00
static int tolua_zeus_CKickStatus_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickStatus* tolua_ret = (CKickStatus*)  Mtolua_new((CKickStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickStatus");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_new00_local
static int tolua_zeus_CKickStatus_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CKickStatus* tolua_ret = (CKickStatus*)  Mtolua_new((CKickStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CKickStatus");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setKick00
static int tolua_zeus_CKickStatus_setKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double power = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setKick'", NULL);
#endif
  {
   self->setKick(num,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChipKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setChipKick00
static int tolua_zeus_CKickStatus_setChipKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double power = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChipKick'", NULL);
#endif
  {
   self->setChipKick(num,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChipKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBothKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setBothKick00
static int tolua_zeus_CKickStatus_setBothKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double kick = ((double)  tolua_tonumber(tolua_S,3,0));
  double chip = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBothKick'", NULL);
#endif
  {
   self->setBothKick(num,kick,chip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBothKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAllKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setAllKick00
static int tolua_zeus_CKickStatus_setAllKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  double kick = ((double)  tolua_tonumber(tolua_S,3,0));
  double chip = ((double)  tolua_tonumber(tolua_S,4,0));
  double pass = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAllKick'", NULL);
#endif
  {
   self->setAllKick(num,kick,chip,pass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAllKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: needKick of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_needKick00
static int tolua_zeus_CKickStatus_needKick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'needKick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->needKick(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'needKick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKickPower of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getKickPower00
static int tolua_zeus_CKickStatus_getKickPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKickPower'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getKickPower(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKickPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChipKickDist of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getChipKickDist00
static int tolua_zeus_CKickStatus_getChipKickDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChipKickDist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getChipKickDist(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChipKickDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPassDist of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getPassDist00
static int tolua_zeus_CKickStatus_getPassDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPassDist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getPassDist(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPassDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKiker of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getKiker00
static int tolua_zeus_CKickStatus_getKiker00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKiker'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getKiker();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKiker'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAll of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_clearAll00
static int tolua_zeus_CKickStatus_clearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAll'", NULL);
#endif
  {
   self->clearAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetKick2ForceClose of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_resetKick2ForceClose00
static int tolua_zeus_CKickStatus_resetKick2ForceClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  bool forceClose = ((bool)  tolua_toboolean(tolua_S,2,false));
  int forceCloseCycle = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetKick2ForceClose'", NULL);
#endif
  {
   self->resetKick2ForceClose(forceClose,forceCloseCycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetKick2ForceClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateForceClose of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_updateForceClose00
static int tolua_zeus_CKickStatus_updateForceClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  int currentCycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateForceClose'", NULL);
#endif
  {
   self->updateForceClose(currentCycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateForceClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isForceClosed of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_isForceClosed00
static int tolua_zeus_CKickStatus_isForceClosed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isForceClosed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isForceClosed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isForceClosed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAdvancerPassTo of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getAdvancerPassTo00
static int tolua_zeus_CKickStatus_getAdvancerPassTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAdvancerPassTo'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getAdvancerPassTo();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAdvancerPassTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAdvancerPassTo of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_setAdvancerPassTo00
static int tolua_zeus_CKickStatus_setAdvancerPassTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAdvancerPassTo'", NULL);
#endif
  {
   self->setAdvancerPassTo(pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAdvancerPassTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetAdvancerPassTo of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_resetAdvancerPassTo00
static int tolua_zeus_CKickStatus_resetAdvancerPassTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CKickStatus* self = (CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetAdvancerPassTo'", NULL);
#endif
  {
   self->resetAdvancerPassTo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetAdvancerPassTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNextAdvancer of class  CKickStatus */
#ifndef TOLUA_DISABLE_tolua_zeus_CKickStatus_getNextAdvancer00
static int tolua_zeus_CKickStatus_getNextAdvancer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CKickStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CKickStatus* self = (const CKickStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextAdvancer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getNextAdvancer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextAdvancer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new00
static int tolua_zeus_Matrix_double__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new00_local
static int tolua_zeus_Matrix_double__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new01
static int tolua_zeus_Matrix_double__new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int rows = ((int)  tolua_tonumber(tolua_S,2,0));
  int columns = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(rows,columns));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new01_local
static int tolua_zeus_Matrix_double__new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int rows = ((int)  tolua_tonumber(tolua_S,2,0));
  int columns = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(rows,columns));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new02
static int tolua_zeus_Matrix_double__new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Matrix<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Matrix<double>* other = ((const Matrix<double>*)  tolua_tousertype(tolua_S,2,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__new02_local
static int tolua_zeus_Matrix_double__new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Matrix<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Matrix<double>* other = ((const Matrix<double>*)  tolua_tousertype(tolua_S,2,0));
  {
   Matrix<double>* tolua_ret = (Matrix<double>*)  Mtolua_new((Matrix<double>)(*other));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Matrix_double__new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__delete00
static int tolua_zeus_Matrix_double__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resize of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__resize00
static int tolua_zeus_Matrix_double__resize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  int rows = ((int)  tolua_tonumber(tolua_S,2,0));
  int columns = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resize'", NULL);
#endif
  {
   self->resize(rows,columns);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: identity of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__identity00
static int tolua_zeus_Matrix_double__identity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'identity'", NULL);
#endif
  {
   self->identity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'identity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__clear00
static int tolua_zeus_Matrix_double__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__setValue00
static int tolua_zeus_Matrix_double__setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  double value = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'", NULL);
#endif
  {
   self->setValue(x,y,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__getValue00
static int tolua_zeus_Matrix_double__getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getValue(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: trace of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__trace00
static int tolua_zeus_Matrix_double__trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'trace'", NULL);
#endif
  {
   double tolua_ret = (double)  self->trace();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: transpose of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__transpose00
static int tolua_zeus_Matrix_double__transpose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'transpose'", NULL);
#endif
  {
   Matrix<double>& tolua_ret = (Matrix<double>&)  self->transpose();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Matrix<double>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transpose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: product of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__product00
static int tolua_zeus_Matrix_double__product00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Matrix<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
  Matrix<double>* other = ((Matrix<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'product'", NULL);
#endif
  {
   Matrix<double> tolua_ret = (Matrix<double>)  self->product(*other);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Matrix<double>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Matrix<double>));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix<double>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'product'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: minsize of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__minsize00
static int tolua_zeus_Matrix_double__minsize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'minsize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->minsize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'minsize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: columns of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__columns00
static int tolua_zeus_Matrix_double__columns00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'columns'", NULL);
#endif
  {
   int tolua_ret = (int)  self->columns();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'columns'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rows of class  Matrix<double> */
#ifndef TOLUA_DISABLE_tolua_zeus_Matrix_double__rows00
static int tolua_zeus_Matrix_double__rows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Matrix<double>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Matrix<double>* self = (Matrix<double>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rows'", NULL);
#endif
  {
   int tolua_ret = (int)  self->rows();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: solve of class  Munkres */
#ifndef TOLUA_DISABLE_tolua_zeus_Munkres_solve00
static int tolua_zeus_Munkres_solve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Munkres",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Matrix<double>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Munkres* self = (Munkres*)  tolua_tousertype(tolua_S,1,0);
  Matrix<double>* m = ((Matrix<double>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'solve'", NULL);
#endif
  {
   self->solve(*m);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'solve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isEnemyBlockShootLine */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00
static int tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ball = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double shootDir = ((double)  tolua_tonumber(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isEnemyBlockShootLine(ball,shootDir,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnemyBlockShootLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isEnemyFrontToBall */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isEnemyFrontToBall00
static int tolua_zeus_NormalPlayUtils_isEnemyFrontToBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  double range = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isEnemyFrontToBall(pVision,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnemyFrontToBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isEnemyCloseToReceiver */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isEnemyCloseToReceiver00
static int tolua_zeus_NormalPlayUtils_isEnemyCloseToReceiver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint receiver = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isEnemyCloseToReceiver(pVision,receiver,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnemyCloseToReceiver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isPosInSquareArea */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isPosInSquareArea00
static int tolua_zeus_NormalPlayUtils_isPosInSquareArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint smallVertex = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint bigVertex = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isPosInSquareArea(pos,smallVertex,bigVertex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPosInSquareArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isPosCloseBorder */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isPosCloseBorder00
static int tolua_zeus_NormalPlayUtils_isPosCloseBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint smallVertex = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint bigVertex = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isPosCloseBorder(pos,smallVertex,bigVertex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPosCloseBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::isReceiverCloseToPassPos */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_isReceiverCloseToPassPos00
static int tolua_zeus_NormalPlayUtils_isReceiverCloseToPassPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint passPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::isReceiverCloseToPassPos(pVision,passPos,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReceiverCloseToPassPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::getOurMostClosetoPos */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_getOurMostClosetoPos00
static int tolua_zeus_NormalPlayUtils_getOurMostClosetoPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   int tolua_ret = (int)  NormalPlayUtils::getOurMostClosetoPos(pVision,pos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOurMostClosetoPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::getTheirMostClosetoPos */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_getTheirMostClosetoPos00
static int tolua_zeus_NormalPlayUtils_getTheirMostClosetoPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   int tolua_ret = (int)  NormalPlayUtils::getTheirMostClosetoPos(pVision,pos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTheirMostClosetoPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::ballMoveToOurDefendArea */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_ballMoveToOurDefendArea00
static int tolua_zeus_NormalPlayUtils_ballMoveToOurDefendArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::ballMoveToOurDefendArea(pVision);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ballMoveToOurDefendArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::noEnemyInPassLine */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_noEnemyInPassLine00
static int tolua_zeus_NormalPlayUtils_noEnemyInPassLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint ball = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint passPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double range = ((const double)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::noEnemyInPassLine(pVision,ball,passPos,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'noEnemyInPassLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::canPassBetweenTwoPos */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_canPassBetweenTwoPos00
static int tolua_zeus_NormalPlayUtils_canPassBetweenTwoPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint passPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  int meNum = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::canPassBetweenTwoPos(pVision,passPos,meNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canPassBetweenTwoPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::generatePassPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_generatePassPoint00
static int tolua_zeus_NormalPlayUtils_generatePassPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGeoPoint ball = *((CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint* passPosOne = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint* passPosTwo = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint* passPosThree = ((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint* passPosFour = ((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::generatePassPoint(ball,*passPosOne,*passPosTwo,*passPosThree,*passPosFour);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePassPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::generateKickAtEnemyDir */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_generateKickAtEnemyDir00
static int tolua_zeus_NormalPlayUtils_generateKickAtEnemyDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerVisionT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  const PlayerVisionT* me = ((const PlayerVisionT*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  NormalPlayUtils::generateKickAtEnemyDir(pVision,*me);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateKickAtEnemyDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::patchForBestPlayer */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_patchForBestPlayer00
static int tolua_zeus_NormalPlayUtils_patchForBestPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  int lastAdvancerNum = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  NormalPlayUtils::patchForBestPlayer(pVision,lastAdvancerNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'patchForBestPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::generateTandemCond */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_generateTandemCond00
static int tolua_zeus_NormalPlayUtils_generateTandemCond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  CGeoPoint* tandemPos = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  int meNum = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   double tolua_ret = (double)  NormalPlayUtils::generateTandemCond(pVision,*tandemPos,meNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateTandemCond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::antiNormalize */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_antiNormalize00
static int tolua_zeus_NormalPlayUtils_antiNormalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  NormalPlayUtils::antiNormalize(dir);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'antiNormalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::faceTheirGoal */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_faceTheirGoal00
static int tolua_zeus_NormalPlayUtils_faceTheirGoal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  const int executor = ((const int)  tolua_tonumber(tolua_S,2,0));
  const double pre = ((const double)  tolua_tonumber(tolua_S,3,Param::Math::PI / 180 * 3));
  {
   bool tolua_ret = (bool)  NormalPlayUtils::faceTheirGoal(pVision,executor,pre);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'faceTheirGoal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalPlayUtils::getSuitSider */
#ifndef TOLUA_DISABLE_tolua_zeus_NormalPlayUtils_getSuitSider00
static int tolua_zeus_NormalPlayUtils_getSuitSider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  {
   int tolua_ret = (int)  NormalPlayUtils::getSuitSider(pVision);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSuitSider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_new00
static int tolua_zeus_CSupportPos_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos* tolua_ret = (CSupportPos*)  Mtolua_new((CSupportPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_new00_local
static int tolua_zeus_CSupportPos_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos* tolua_ret = (CSupportPos*)  Mtolua_new((CSupportPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_delete00
static int tolua_zeus_CSupportPos_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_generatePos00
static int tolua_zeus_CSupportPos_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos(pVision,num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSupPos of class  CSupportPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos_getSupPos00
static int tolua_zeus_CSupportPos_getSupPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos* self = (CSupportPos*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSupPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getSupPos(pVision,num);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSupPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_get_SupportPosStruct2022_leftSupportPos
static int tolua_get_SupportPosStruct2022_leftSupportPos(lua_State* tolua_S)
{
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftSupportPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftSupportPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_set_SupportPosStruct2022_leftSupportPos
static int tolua_set_SupportPosStruct2022_leftSupportPos(lua_State* tolua_S)
{
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftSupportPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftSupportPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rightSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_get_SupportPosStruct2022_rightSupportPos
static int tolua_get_SupportPosStruct2022_rightSupportPos(lua_State* tolua_S)
{
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightSupportPos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rightSupportPos,"CGeoPoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rightSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_set_SupportPosStruct2022_rightSupportPos
static int tolua_set_SupportPosStruct2022_rightSupportPos(lua_State* tolua_S)
{
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rightSupportPos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rightSupportPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_SupportPosStruct2022_getLeftSupportPos00
static int tolua_zeus_SupportPosStruct2022_getLeftSupportPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SupportPosStruct2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftSupportPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getLeftSupportPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftSupportPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightSupportPos of class  SupportPosStruct2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_SupportPosStruct2022_getRightSupportPos00
static int tolua_zeus_SupportPosStruct2022_getRightSupportPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SupportPosStruct2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SupportPosStruct2022* self = (SupportPosStruct2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightSupportPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getRightSupportPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightSupportPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_new00
static int tolua_zeus_CSupportPos2022_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos2022* tolua_ret = (CSupportPos2022*)  Mtolua_new((CSupportPos2022)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos2022");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_new00_local
static int tolua_zeus_CSupportPos2022_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSupportPos2022* tolua_ret = (CSupportPos2022*)  Mtolua_new((CSupportPos2022)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSupportPos2022");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_delete00
static int tolua_zeus_CSupportPos2022_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateSupportPoint of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_generateSupportPoint00
static int tolua_zeus_CSupportPos2022_generateSupportPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateSupportPoint'", NULL);
#endif
  {
   self->generateSupportPoint(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateSupportPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSupportPos of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_getSupportPos00
static int tolua_zeus_CSupportPos2022_getSupportPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSupportPos'", NULL);
#endif
  {
   SupportPosStruct2022 tolua_ret = (SupportPosStruct2022)  self->getSupportPos(pVision);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((SupportPosStruct2022)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"SupportPosStruct2022");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(SupportPosStruct2022));
     tolua_pushusertype(tolua_S,tolua_obj,"SupportPosStruct2022");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSupportPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEmpty of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_isEmpty00
static int tolua_zeus_CSupportPos2022_isEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CSupportPos2022",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CSupportPos2022* self = (const CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEmpty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEmpty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAreaScore of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_getAreaScore00
static int tolua_zeus_CSupportPos2022_getAreaScore00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double v_max = ((double)  tolua_tonumber(tolua_S,3,0));
  double v_min = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAreaScore'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAreaScore(pVision,v_max,v_min);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAreaScore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateBestPoint of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_generateBestPoint00
static int tolua_zeus_CSupportPos2022_generateBestPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double v_max = ((double)  tolua_tonumber(tolua_S,3,0));
  double v_min = ((double)  tolua_tonumber(tolua_S,4,0));
  double maxDist = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateBestPoint'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->generateBestPoint(pVision,v_max,v_min,maxDist);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateBestPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calcMaxDist of class  CSupportPos2022 */
#ifndef TOLUA_DISABLE_tolua_zeus_CSupportPos2022_calcMaxDist00
static int tolua_zeus_CSupportPos2022_calcMaxDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSupportPos2022",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoLine",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSupportPos2022* self = (CSupportPos2022*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
  double middleDir = ((double)  tolua_tonumber(tolua_S,3,0));
  CGeoLine angleBisector = *((CGeoLine*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calcMaxDist'", NULL);
#endif
  {
   double tolua_ret = (double)  self->calcMaxDist(pVision,middleDir,angleBisector);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calcMaxDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_new00
static int tolua_zeus_CTandemPos_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTandemPos* tolua_ret = (CTandemPos*)  Mtolua_new((CTandemPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTandemPos");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_new00_local
static int tolua_zeus_CTandemPos_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTandemPos* tolua_ret = (CTandemPos*)  Mtolua_new((CTandemPos)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTandemPos");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_delete00
static int tolua_zeus_CTandemPos_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePos of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_generatePos00
static int tolua_zeus_CTandemPos_generatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePos'", NULL);
#endif
  {
   self->generatePos();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemPos of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_getTandemPos00
static int tolua_zeus_CTandemPos_getTandemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemPos'", NULL);
#endif
  {
   CGeoPoint tolua_ret = (CGeoPoint)  self->getTandemPos();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: analyzeSituation of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_analyzeSituation00
static int tolua_zeus_CTandemPos_analyzeSituation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
  int teamnum = ((int)  tolua_tonumber(tolua_S,2,0));
  int oppnnum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'analyzeSituation'", NULL);
#endif
  {
   self->analyzeSituation(teamnum,oppnnum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'analyzeSituation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: planAssistAttack of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_planAssistAttack00
static int tolua_zeus_CTandemPos_planAssistAttack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
  int teamnum = ((int)  tolua_tonumber(tolua_S,2,0));
  int oppnum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'planAssistAttack'", NULL);
#endif
  {
   self->planAssistAttack(teamnum,oppnum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'planAssistAttack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: planBlock of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_planBlock00
static int tolua_zeus_CTandemPos_planBlock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
  int teamnnum = ((int)  tolua_tonumber(tolua_S,2,0));
  int oppnum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'planBlock'", NULL);
#endif
  {
   self->planBlock(teamnnum,oppnum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'planBlock'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: planAssistGetBall of class  CTandemPos */
#ifndef TOLUA_DISABLE_tolua_zeus_CTandemPos_planAssistGetBall00
static int tolua_zeus_CTandemPos_planAssistGetBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTandemPos",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTandemPos* self = (CTandemPos*)  tolua_tousertype(tolua_S,1,0);
  int teamnum = ((int)  tolua_tonumber(tolua_S,2,0));
  int oppnum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'planAssistGetBall'", NULL);
#endif
  {
   self->planAssistGetBall(teamnum,oppnum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'planAssistGetBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Normalize */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Normalize00
static int tolua_zeus_Utils_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double angle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  Utils::Normalize(angle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::Polar2Vector */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_Polar2Vector00
static int tolua_zeus_Utils_Polar2Vector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double m = ((double)  tolua_tonumber(tolua_S,1,0));
  double angle = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CVector tolua_ret = (CVector)  Utils::Polar2Vector(m,angle);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Polar2Vector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::VectorDot */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_VectorDot00
static int tolua_zeus_Utils_VectorDot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* v1 = ((const CVector*)  tolua_tousertype(tolua_S,1,0));
  const CVector* v2 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  Utils::VectorDot(*v1,*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VectorDot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::dirDiff */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_dirDiff00
static int tolua_zeus_Utils_dirDiff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVector* v1 = ((const CVector*)  tolua_tousertype(tolua_S,1,0));
  const CVector* v2 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  {
   double tolua_ret = (double)  Utils::dirDiff(*v1,*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dirDiff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween00
static int tolua_zeus_Utils_InBetween00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* p1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* p2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Utils::InBetween(*p,*p1,*p2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InBetween'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween01
static int tolua_zeus_Utils_InBetween01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double v = ((double)  tolua_tonumber(tolua_S,1,0));
  double v1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double v2 = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Utils::InBetween(v,v1,v2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_InBetween00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::AngleBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_AngleBetween00
static int tolua_zeus_Utils_AngleBetween00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double d = ((double)  tolua_tonumber(tolua_S,1,0));
  double d1 = ((double)  tolua_tonumber(tolua_S,2,0));
  double d2 = ((double)  tolua_tonumber(tolua_S,3,0));
  double buffer = ((double)  tolua_tonumber(tolua_S,4,Param::Math::PI/30));
  {
   bool tolua_ret = (bool)  Utils::AngleBetween(d,d1,d2,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AngleBetween'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InBetween */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InBetween02
static int tolua_zeus_Utils_InBetween02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CVector",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CVector* v = ((const CVector*)  tolua_tousertype(tolua_S,1,0));
  const CVector* v1 = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
  const CVector* v2 = ((const CVector*)  tolua_tousertype(tolua_S,3,0));
  double buffer = ((double)  tolua_tonumber(tolua_S,4,Param::Math::PI/30));
  {
   bool tolua_ret = (bool)  Utils::InBetween(*v,*v1,*v2,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_InBetween01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeInField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeInField00
static int tolua_zeus_Utils_MakeInField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeInField(*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeInField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::OutOfField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_OutOfField00
static int tolua_zeus_Utils_OutOfField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::OutOfField(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OutOfField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::IsInField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_IsInField00
static int tolua_zeus_Utils_IsInField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint p = *((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  double buffer = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::IsInField(p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfOurPenaltyArea00
static int tolua_zeus_Utils_MakeOutOfOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfOurPenaltyArea(*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfTheirPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfTheirPenaltyArea00
static int tolua_zeus_Utils_MakeOutOfTheirPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfTheirPenaltyArea(*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfTheirPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfCircleAndInField */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfCircleAndInField00
static int tolua_zeus_Utils_MakeOutOfCircleAndInField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* center = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfCircleAndInField(*center,radius,*p,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfCircleAndInField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfCircle00
static int tolua_zeus_Utils_MakeOutOfCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* center = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  const bool isBack = ((const bool)  tolua_toboolean(tolua_S,5,false));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfCircle(*center,radius,*target,buffer,isBack);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfCircle01
static int tolua_zeus_Utils_MakeOutOfCircle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* center = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  const bool isBack = ((const bool)  tolua_toboolean(tolua_S,5,0));
  const CGeoPoint* mePos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,6,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfCircle(*center,radius,*target,buffer,isBack,*mePos);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_MakeOutOfCircle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfCircle02
static int tolua_zeus_Utils_MakeOutOfCircle02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* center = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  const bool isBack = ((const bool)  tolua_toboolean(tolua_S,5,0));
  const CGeoPoint* mePos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,6,0));
  const CVector adjustVec = *((const CVector*)  tolua_tousertype(tolua_S,7,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfCircle(*center,radius,*target,buffer,isBack,*mePos,adjustVec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_MakeOutOfCircle01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfLongCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfLongCircle00
static int tolua_zeus_Utils_MakeOutOfLongCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* seg_start = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* seg_end = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,3,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,5,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfLongCircle(*seg_start,*seg_end,radius,*target,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfLongCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfLongCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfLongCircle01
static int tolua_zeus_Utils_MakeOutOfLongCircle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CGeoPoint* seg_start = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* seg_end = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const double radius = ((const double)  tolua_tonumber(tolua_S,3,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,5,0));
  const CVector adjustVec = *((const CVector*)  tolua_tousertype(tolua_S,6,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfLongCircle(*seg_start,*seg_end,radius,*target,buffer,adjustVec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_MakeOutOfLongCircle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfRectangle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfRectangle00
static int tolua_zeus_Utils_MakeOutOfRectangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* recP1 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const CGeoPoint* recP2 = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,4,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfRectangle(*recP1,*recP2,*target,buffer);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeOutOfRectangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InOurPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InOurPenaltyArea00
static int tolua_zeus_Utils_InOurPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::InOurPenaltyArea(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InOurPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::InTheirPenaltyArea */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_InTheirPenaltyArea00
static int tolua_zeus_Utils_InTheirPenaltyArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,1,0));
  const double buffer = ((const double)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Utils::InTheirPenaltyArea(*p,buffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InTheirPenaltyArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::PlayerNumValid */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_PlayerNumValid00
static int tolua_zeus_Utils_PlayerNumValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Utils::PlayerNumValid(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerNumValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetOutSidePenaltyPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetOutSidePenaltyPos00
static int tolua_zeus_Utils_GetOutSidePenaltyPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  double delta = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetOutSidePenaltyPos(dir,delta);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOutSidePenaltyPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetOutSidePenaltyPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetOutSidePenaltyPos01
static int tolua_zeus_Utils_GetOutSidePenaltyPos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  double delta = ((double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint targetPoint = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetOutSidePenaltyPos(dir,delta,targetPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_GetOutSidePenaltyPos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetOutTheirSidePenaltyPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetOutTheirSidePenaltyPos00
static int tolua_zeus_Utils_GetOutTheirSidePenaltyPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  double delta = ((double)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* targetPoint = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetOutTheirSidePenaltyPos(dir,delta,*targetPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOutTheirSidePenaltyPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetInterPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetInterPos00
static int tolua_zeus_Utils_GetInterPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetInterPos(dir);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInterPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetInterPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetInterPos01
static int tolua_zeus_Utils_GetInterPos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  const CGeoPoint targetPoint = *((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetInterPos(dir,targetPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_GetInterPos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::GetTheirInterPos */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_GetTheirInterPos00
static int tolua_zeus_Utils_GetTheirInterPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double dir = ((double)  tolua_tonumber(tolua_S,1,0));
  const CGeoPoint* targetPoint = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::GetTheirInterPos(dir,*targetPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTheirInterPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::SquareRootFloat */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_SquareRootFloat00
static int tolua_zeus_Utils_SquareRootFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float number = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   float tolua_ret = (float)  Utils::SquareRootFloat(number);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SquareRootFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::canGo */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_canGo00
static int tolua_zeus_Utils_canGo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,1,0));
  const int num = ((const int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint* target = ((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  const int flag = ((const int)  tolua_tonumber(tolua_S,4,0));
  const double avoidBuffer = ((const double)  tolua_tonumber(tolua_S,5,0));
  {
   bool tolua_ret = (bool)  Utils::canGo(pVision,num,*target,flag,avoidBuffer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canGo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::dist_SegToPoint */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_dist_SegToPoint00
static int tolua_zeus_Utils_dist_SegToPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double segFirstX = ((double)  tolua_tonumber(tolua_S,1,0));
  double segFirstY = ((double)  tolua_tonumber(tolua_S,2,0));
  double segSecondX = ((double)  tolua_tonumber(tolua_S,3,0));
  double segSecondY = ((double)  tolua_tonumber(tolua_S,4,0));
  double pointX = ((double)  tolua_tonumber(tolua_S,5,0));
  double pointY = ((double)  tolua_tonumber(tolua_S,6,0));
  {
   double tolua_ret = (double)  Utils::dist_SegToPoint(segFirstX,segFirstY,segSecondX,segSecondY,pointX,pointY);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist_SegToPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::MakeOutOfLongCircle */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_MakeOutOfLongCircle02
static int tolua_zeus_Utils_MakeOutOfLongCircle02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double segFirstX = ((double)  tolua_tonumber(tolua_S,1,0));
  double segFirstY = ((double)  tolua_tonumber(tolua_S,2,0));
  double segSecondX = ((double)  tolua_tonumber(tolua_S,3,0));
  double segSecondY = ((double)  tolua_tonumber(tolua_S,4,0));
  const CGeoPoint* p = ((const CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
  {
   CGeoPoint tolua_ret = (CGeoPoint)  Utils::MakeOutOfLongCircle(segFirstX,segFirstY,segSecondX,segSecondY,*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_zeus_Utils_MakeOutOfLongCircle01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::point_OnLineOnSeg */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_point_OnLineOnSeg00
static int tolua_zeus_Utils_point_OnLineOnSeg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const double segFirstX = ((const double)  tolua_tonumber(tolua_S,1,0));
  const double segFirstY = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double segSecondX = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double segSecondY = ((const double)  tolua_tonumber(tolua_S,4,0));
  const double pointX = ((const double)  tolua_tonumber(tolua_S,5,0));
  const double pointY = ((const double)  tolua_tonumber(tolua_S,6,0));
  {
   bool tolua_ret = (bool)  Utils::point_OnLineOnSeg(segFirstX,segFirstY,segSecondX,segSecondY,pointX,pointY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point_OnLineOnSeg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::min_Obs */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_min_Obs00
static int tolua_zeus_Utils_min_Obs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double a = ((double)  tolua_tonumber(tolua_S,1,0));
  double b = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   double tolua_ret = (double)  Utils::min_Obs(a,b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'min_Obs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Utils::max_Obs */
#ifndef TOLUA_DISABLE_tolua_zeus_Utils_max_Obs00
static int tolua_zeus_Utils_max_Obs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double a = ((double)  tolua_tonumber(tolua_S,1,0));
  double b = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   double tolua_ret = (double)  Utils::max_Obs(a,b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'max_Obs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_new00
static int tolua_zeus_TranslationT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TranslationT* tolua_ret = (TranslationT*)  Mtolua_new((TranslationT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TranslationT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_new00_local
static int tolua_zeus_TranslationT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TranslationT* tolua_ret = (TranslationT*)  Mtolua_new((TranslationT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TranslationT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pos of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_Pos00
static int tolua_zeus_TranslationT_Pos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->Pos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPos of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetPos00
static int tolua_zeus_TranslationT_SetPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'", NULL);
#endif
  {
   self->SetPos(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPos of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetPos01
static int tolua_zeus_TranslationT_SetPos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* pos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'", NULL);
#endif
  {
   self->SetPos(*pos);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_TranslationT_SetPos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: X of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_X00
static int tolua_zeus_TranslationT_X00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'X'", NULL);
#endif
  {
   double tolua_ret = (double)  self->X();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'X'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Y of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_Y00
static int tolua_zeus_TranslationT_Y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Y'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVel of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetVel00
static int tolua_zeus_TranslationT_SetVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVel'", NULL);
#endif
  {
   self->SetVel(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVel of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetVel01
static int tolua_zeus_TranslationT_SetVel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  const CVector* vel = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVel'", NULL);
#endif
  {
   self->SetVel(*vel);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_TranslationT_SetVel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAcc of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetAcc00
static int tolua_zeus_TranslationT_SetAcc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAcc'", NULL);
#endif
  {
   self->SetAcc(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAcc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAcc of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetAcc01
static int tolua_zeus_TranslationT_SetAcc01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  const CVector* acc = ((const CVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAcc'", NULL);
#endif
  {
   self->SetAcc(*acc);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_TranslationT_SetAcc00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Vel of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_Vel00
static int tolua_zeus_TranslationT_Vel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Vel'", NULL);
#endif
  {
   const CVector& tolua_ret = (const CVector&)  self->Vel();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Vel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Acc of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_Acc00
static int tolua_zeus_TranslationT_Acc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Acc'", NULL);
#endif
  {
   const CVector& tolua_ret = (const CVector&)  self->Acc();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Acc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VelX of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_VelX00
static int tolua_zeus_TranslationT_VelX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VelX'", NULL);
#endif
  {
   double tolua_ret = (double)  self->VelX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VelX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VelY of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_VelY00
static int tolua_zeus_TranslationT_VelY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VelY'", NULL);
#endif
  {
   double tolua_ret = (double)  self->VelY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VelY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AccX of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_AccX00
static int tolua_zeus_TranslationT_AccX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AccX'", NULL);
#endif
  {
   double tolua_ret = (double)  self->AccX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AccX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AccY of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_AccY00
static int tolua_zeus_TranslationT_AccY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AccY'", NULL);
#endif
  {
   double tolua_ret = (double)  self->AccY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AccY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValid of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_SetValid00
static int tolua_zeus_TranslationT_SetValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TranslationT",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TranslationT* self = (TranslationT*)  tolua_tousertype(tolua_S,1,0);
  bool v = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValid'", NULL);
#endif
  {
   self->SetValid(v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Valid of class  TranslationT */
#ifndef TOLUA_DISABLE_tolua_zeus_TranslationT_Valid00
static int tolua_zeus_TranslationT_Valid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TranslationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TranslationT* self = (const TranslationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Valid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Valid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Valid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ChipPosT */
#ifndef TOLUA_DISABLE_tolua_zeus_ChipPosT_new00
static int tolua_zeus_ChipPosT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ChipPosT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ChipPosT* tolua_ret = (ChipPosT*)  Mtolua_new((ChipPosT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ChipPosT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ChipPosT */
#ifndef TOLUA_DISABLE_tolua_zeus_ChipPosT_new00_local
static int tolua_zeus_ChipPosT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ChipPosT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ChipPosT* tolua_ret = (ChipPosT*)  Mtolua_new((ChipPosT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ChipPosT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChipPredictPos of class  ChipPosT */
#ifndef TOLUA_DISABLE_tolua_zeus_ChipPosT_ChipPredictPos00
static int tolua_zeus_ChipPosT_ChipPredictPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ChipPosT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ChipPosT* self = (const ChipPosT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChipPredictPos'", NULL);
#endif
  {
   const CGeoPoint& tolua_ret = (const CGeoPoint&)  self->ChipPredictPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CGeoPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChipPredictPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChipPredict of class  ChipPosT */
#ifndef TOLUA_DISABLE_tolua_zeus_ChipPosT_SetChipPredict00
static int tolua_zeus_ChipPosT_SetChipPredict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ChipPosT",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ChipPosT* self = (ChipPosT*)  tolua_tousertype(tolua_S,1,0);
  const CGeoPoint* chipPos = ((const CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChipPredict'", NULL);
#endif
  {
   self->SetChipPredict(*chipPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChipPredict'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChipPredict of class  ChipPosT */
#ifndef TOLUA_DISABLE_tolua_zeus_ChipPosT_SetChipPredict01
static int tolua_zeus_ChipPosT_SetChipPredict01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ChipPosT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ChipPosT* self = (ChipPosT*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChipPredict'", NULL);
#endif
  {
   self->SetChipPredict(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_zeus_ChipPosT_SetChipPredict00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_new00
static int tolua_zeus_RotationT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RotationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RotationT* tolua_ret = (RotationT*)  Mtolua_new((RotationT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RotationT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_new00_local
static int tolua_zeus_RotationT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RotationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RotationT* tolua_ret = (RotationT*)  Mtolua_new((RotationT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RotationT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dir of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_Dir00
static int tolua_zeus_RotationT_Dir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RotationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RotationT* self = (const RotationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dir'", NULL);
#endif
  {
   double tolua_ret = (double)  self->Dir();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDir of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_SetDir00
static int tolua_zeus_RotationT_SetDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RotationT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RotationT* self = (RotationT*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDir'", NULL);
#endif
  {
   self->SetDir(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RotVel of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_RotVel00
static int tolua_zeus_RotationT_RotVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RotationT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RotationT* self = (const RotationT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RotVel'", NULL);
#endif
  {
   double tolua_ret = (double)  self->RotVel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RotVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotVel of class  RotationT */
#ifndef TOLUA_DISABLE_tolua_zeus_RotationT_SetRotVel00
static int tolua_zeus_RotationT_SetRotVel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RotationT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RotationT* self = (RotationT*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotVel'", NULL);
#endif
  {
   self->SetRotVel(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotVel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __RotationT__ of class  PlayerVisionT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerVisionT___RotationT__
static int tolua_get_PlayerVisionT___RotationT__(lua_State* tolua_S)
{
  PlayerVisionT* self = (PlayerVisionT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__RotationT__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<RotationT*>(self), "RotationT");
#else
   tolua_pushusertype(tolua_S,(void*)((RotationT*)self), "RotationT");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __ChipPosT__ of class  BallVisionT */
#ifndef TOLUA_DISABLE_tolua_get_BallVisionT___ChipPosT__
static int tolua_get_BallVisionT___ChipPosT__(lua_State* tolua_S)
{
  BallVisionT* self = (BallVisionT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__ChipPosT__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<ChipPosT*>(self), "ChipPosT");
#else
   tolua_pushusertype(tolua_S,(void*)((ChipPosT*)self), "ChipPosT");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerCapabilityT_new00
static int tolua_zeus_PlayerCapabilityT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerCapabilityT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerCapabilityT* tolua_ret = (PlayerCapabilityT*)  Mtolua_new((PlayerCapabilityT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerCapabilityT");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_zeus_PlayerCapabilityT_new00_local
static int tolua_zeus_PlayerCapabilityT_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerCapabilityT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerCapabilityT* tolua_ret = (PlayerCapabilityT*)  Mtolua_new((PlayerCapabilityT)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerCapabilityT");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAccel
static int tolua_get_PlayerCapabilityT_maxAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAccel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAccel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAccel
static int tolua_set_PlayerCapabilityT_maxAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAccel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAccel = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxSpeed
static int tolua_get_PlayerCapabilityT_maxSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxSpeed
static int tolua_set_PlayerCapabilityT_maxSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxSpeed = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularAccel
static int tolua_get_PlayerCapabilityT_maxAngularAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularAccel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularAccel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularAccel of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularAccel
static int tolua_set_PlayerCapabilityT_maxAngularAccel(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularAccel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularAccel = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularSpeed
static int tolua_get_PlayerCapabilityT_maxAngularSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularSpeed of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularSpeed
static int tolua_set_PlayerCapabilityT_maxAngularSpeed(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularSpeed = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxDec
static int tolua_get_PlayerCapabilityT_maxDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxDec'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxDec);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxDec
static int tolua_set_PlayerCapabilityT_maxDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxDec'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxDec = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxAngularDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_get_PlayerCapabilityT_maxAngularDec
static int tolua_get_PlayerCapabilityT_maxAngularDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularDec'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxAngularDec);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxAngularDec of class  PlayerCapabilityT */
#ifndef TOLUA_DISABLE_tolua_set_PlayerCapabilityT_maxAngularDec
static int tolua_set_PlayerCapabilityT_maxAngularDec(lua_State* tolua_S)
{
  PlayerCapabilityT* self = (PlayerCapabilityT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxAngularDec'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxAngularDec = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRobotNum of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_get_ROBOTINFO_nRobotNum
static int tolua_get_ROBOTINFO_nRobotNum(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRobotNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nRobotNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRobotNum of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_set_ROBOTINFO_nRobotNum
static int tolua_set_ROBOTINFO_nRobotNum(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRobotNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRobotNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInfraredInfo of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_get_ROBOTINFO_bInfraredInfo
static int tolua_get_ROBOTINFO_bInfraredInfo(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInfraredInfo'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bInfraredInfo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInfraredInfo of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_set_ROBOTINFO_bInfraredInfo
static int tolua_set_ROBOTINFO_bInfraredInfo(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInfraredInfo'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInfraredInfo = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nKickInfo of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_get_ROBOTINFO_nKickInfo
static int tolua_get_ROBOTINFO_nKickInfo(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKickInfo'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nKickInfo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nKickInfo of class  ROBOTINFO */
#ifndef TOLUA_DISABLE_tolua_set_ROBOTINFO_nKickInfo
static int tolua_set_ROBOTINFO_nKickInfo(lua_State* tolua_S)
{
  ROBOTINFO* self = (ROBOTINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKickInfo'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nKickInfo = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_new00
static int tolua_zeus_CWorldModel_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CWorldModel* tolua_ret = (CWorldModel*)  Mtolua_new((CWorldModel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CWorldModel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_new00_local
static int tolua_zeus_CWorldModel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CWorldModel* tolua_ret = (CWorldModel*)  Mtolua_new((CWorldModel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CWorldModel");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerVision of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_registerVision00
static int tolua_zeus_CWorldModel_registerVision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CVisionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  const CVisionModule* pVision = ((const CVisionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerVision'", NULL);
#endif
  {
   self->registerVision(pVision);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerVision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOption of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_registerOption00
static int tolua_zeus_CWorldModel_registerOption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const COptionModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  const COptionModule* pOption = ((const COptionModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOption'", NULL);
#endif
  {
   self->registerOption(pOption);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOption'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vision of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_vision00
static int tolua_zeus_CWorldModel_vision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CWorldModel* self = (const CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vision'", NULL);
#endif
  {
   const CVisionModule* tolua_ret = (const CVisionModule*)  self->vision();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const CVisionModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: option of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_option00
static int tolua_zeus_CWorldModel_option00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CWorldModel* self = (const CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'option'", NULL);
#endif
  {
   const COptionModule* tolua_ret = (const COptionModule*)  self->option();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const COptionModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'option'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: self2ball of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_self2ball00
static int tolua_zeus_CWorldModel_self2ball00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'self2ball'", NULL);
#endif
  {
   const CVector tolua_ret = (const CVector)  self->self2ball(current_cycle,myNum,enemyNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CVector));
     tolua_pushusertype(tolua_S,tolua_obj,"const CVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'self2ball'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: self2ballDist of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_self2ballDist00
static int tolua_zeus_CWorldModel_self2ballDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'self2ballDist'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->self2ballDist(current_cycle,myNum,enemyNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'self2ballDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: self2ballDir of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_self2ballDir00
static int tolua_zeus_CWorldModel_self2ballDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
  int enemyNum = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'self2ballDir'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->self2ballDir(current_cycle,myNum,enemyNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'self2ballDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CurrentRefereeMsg of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_CurrentRefereeMsg00
static int tolua_zeus_CWorldModel_CurrentRefereeMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CurrentRefereeMsg'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->CurrentRefereeMsg();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CurrentRefereeMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OurRobotNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_OurRobotNum00
static int tolua_zeus_CWorldModel_OurRobotNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OurRobotNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->OurRobotNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OurRobotNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBallKicked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsBallKicked00
static int tolua_zeus_CWorldModel_IsBallKicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_1 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBallKicked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBallKicked(tolua_var_1);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBallKicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBestPlayerChanged of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsBestPlayerChanged00
static int tolua_zeus_CWorldModel_IsBestPlayerChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBestPlayerChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBestPlayerChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBestPlayerChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CurrentBayes of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_CurrentBayes00
static int tolua_zeus_CWorldModel_CurrentBayes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CurrentBayes'", NULL);
#endif
  {
   string tolua_ret = (string)  self->CurrentBayes();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CurrentBayes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanDefenceExit of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_CanDefenceExit00
static int tolua_zeus_CWorldModel_CanDefenceExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanDefenceExit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CanDefenceExit();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanDefenceExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: timeToTarget of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_timeToTarget00
static int tolua_zeus_CWorldModel_timeToTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int player = ((int)  tolua_tonumber(tolua_S,2,0));
  const CGeoPoint target = *((const CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'timeToTarget'", NULL);
#endif
  {
   double tolua_ret = (double)  self->timeToTarget(player,target);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'timeToTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NeedExitAttackDef of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_NeedExitAttackDef00
static int tolua_zeus_CWorldModel_NeedExitAttackDef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int mode = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NeedExitAttackDef'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->NeedExitAttackDef(leftUp,rightDown,mode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NeedExitAttackDef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ball2MarkingTouch of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_ball2MarkingTouch00
static int tolua_zeus_CWorldModel_ball2MarkingTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftUp = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint rightDown = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ball2MarkingTouch'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ball2MarkingTouch(leftUp,rightDown);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ball2MarkingTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMarkingFrontValid of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isMarkingFrontValid00
static int tolua_zeus_CWorldModel_isMarkingFrontValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint checkPos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double checkDir = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMarkingFrontValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMarkingFrontValid(checkPos,checkDir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMarkingFrontValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEnemyKickOffNum of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getEnemyKickOffNum00
static int tolua_zeus_CWorldModel_getEnemyKickOffNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEnemyKickOffNum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEnemyKickOffNum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemyKickOffNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkEnemyKickOffNumChanged of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00
static int tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkEnemyKickOffNumChanged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkEnemyKickOffNumChanged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkEnemyKickOffNumChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMarkingTouchArea of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getMarkingTouchArea00
static int tolua_zeus_CWorldModel_getMarkingTouchArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint leftPos1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint leftPos2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint rightPos1 = *((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint rightPos2 = *((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMarkingTouchArea'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMarkingTouchArea(leftPos1,leftPos2,rightPos1,rightPos2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMarkingTouchArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SPlayFSMSwitchClearAll of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00
static int tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  bool clear_flag = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SPlayFSMSwitchClearAll'", NULL);
#endif
  {
   self->SPlayFSMSwitchClearAll(clear_flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SPlayFSMSwitchClearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: KickDirArrived of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_KickDirArrived00
static int tolua_zeus_CWorldModel_KickDirArrived00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  double kickdir = ((double)  tolua_tonumber(tolua_S,3,0));
  double kickdirprecision = ((double)  tolua_tonumber(tolua_S,4,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KickDirArrived'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->KickDirArrived(current_cycle,kickdir,kickdirprecision,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KickDirArrived'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canProtectBall of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canProtectBall00
static int tolua_zeus_CWorldModel_canProtectBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canProtectBall'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canProtectBall(current_cycle,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canProtectBall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canShootOnBallPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canShootOnBallPos00
static int tolua_zeus_CWorldModel_canShootOnBallPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canShootOnBallPos'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canShootOnBallPos(current_cycle,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canShootOnBallPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canPassOnBallPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canPassOnBallPos00
static int tolua_zeus_CWorldModel_canPassOnBallPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  CGeoPoint* passPos = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint* guisePos = ((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canPassOnBallPos'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canPassOnBallPos(current_cycle,*passPos,*guisePos,myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canPassOnBallPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canKickAtEnemy of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_canKickAtEnemy00
static int tolua_zeus_CWorldModel_canKickAtEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  CGeoPoint* kickDir = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  int myNum = ((int)  tolua_tonumber(tolua_S,4,0));
  int priority = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canKickAtEnemy'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->canKickAtEnemy(current_cycle,*kickDir,myNum,priority);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canKickAtEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallStatus of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getBallStatus00
static int tolua_zeus_CWorldModel_getBallStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int current_cycle = ((int)  tolua_tonumber(tolua_S,2,0));
  int meNum = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallStatus'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->getBallStatus(current_cycle,meNum);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: generatePassPoint of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_generatePassPoint00
static int tolua_zeus_CWorldModel_generatePassPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CGeoPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint* passOne = ((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  CGeoPoint* passTwo = ((CGeoPoint*)  tolua_tousertype(tolua_S,3,0));
  CGeoPoint* passThree = ((CGeoPoint*)  tolua_tousertype(tolua_S,4,0));
  CGeoPoint* passFour = ((CGeoPoint*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generatePassPoint'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->generatePassPoint(*passOne,*passTwo,*passThree,*passFour);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generatePassPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getTandemPos00
static int tolua_zeus_CWorldModel_getTandemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getTandemPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTandemDir of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getTandemDir00
static int tolua_zeus_CWorldModel_getTandemDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTandemDir'", NULL);
#endif
  {
   const double tolua_ret = (const double)  self->getTandemDir(myNum);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTandemDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBallToucher of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getBallToucher00
static int tolua_zeus_CWorldModel_getBallToucher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBallToucher'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getBallToucher();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBallToucher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOurBallByAutoReferee of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_IsOurBallByAutoReferee00
static int tolua_zeus_CWorldModel_IsOurBallByAutoReferee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOurBallByAutoReferee'", NULL);
#endif
  {
   const bool tolua_ret = (const bool)  self->IsOurBallByAutoReferee();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOurBallByAutoReferee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearBallStateCouter of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_clearBallStateCouter00
static int tolua_zeus_CWorldModel_clearBallStateCouter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearBallStateCouter'", NULL);
#endif
  {
   self->clearBallStateCouter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearBallStateCouter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSuitSider of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getSuitSider00
static int tolua_zeus_CWorldModel_getSuitSider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSuitSider'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSuitSider();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSuitSider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBallHandler of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_setBallHandler00
static int tolua_zeus_CWorldModel_setBallHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBallHandler'", NULL);
#endif
  {
   self->setBallHandler(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBallHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRecordRunPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isRecordRunPos00
static int tolua_zeus_CWorldModel_isRecordRunPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRecordRunPos'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRecordRunPos();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRecordRunPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBeingMarked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isBeingMarked00
static int tolua_zeus_CWorldModel_isBeingMarked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBeingMarked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBeingMarked(myNum);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBeingMarked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPassLineBlocked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isPassLineBlocked00
static int tolua_zeus_CWorldModel_isPassLineBlocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double allowance = ((double)  tolua_tonumber(tolua_S,3,4.0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPassLineBlocked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPassLineBlocked(myNum,allowance);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPassLineBlocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShootLineBlocked of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isShootLineBlocked00
static int tolua_zeus_CWorldModel_isShootLineBlocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,150));
  double allowance = ((double)  tolua_tonumber(tolua_S,4,3.0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShootLineBlocked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShootLineBlocked(myNum,range,allowance);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShootLineBlocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShootLineBlockedFromPoint of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00
static int tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CGeoPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  CGeoPoint pos = *((CGeoPoint*)  tolua_tousertype(tolua_S,2,0));
  double range = ((double)  tolua_tonumber(tolua_S,3,150));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShootLineBlockedFromPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShootLineBlockedFromPoint(pos,range);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShootLineBlockedFromPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawReflect of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_drawReflect00
static int tolua_zeus_CWorldModel_drawReflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawReflect'", NULL);
#endif
  {
   self->drawReflect(myNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawReflect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getLeftReflectPos00
static int tolua_zeus_CWorldModel_getLeftReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getLeftReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getRightReflectPos00
static int tolua_zeus_CWorldModel_getRightReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getRightReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReflectPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getReflectPos00
static int tolua_zeus_CWorldModel_getReflectPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReflectPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getReflectPos(myNum);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReflectPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReflectTouchPos of class  CWorldModel */
#ifndef TOLUA_DISABLE_tolua_zeus_CWorldModel_getReflectTouchPos00
static int tolua_zeus_CWorldModel_getReflectTouchPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CWorldModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CWorldModel* self = (CWorldModel*)  tolua_tousertype(tolua_S,1,0);
  int myNum = ((int)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReflectTouchPos'", NULL);
#endif
  {
   const CGeoPoint tolua_ret = (const CGeoPoint)  self->getReflectTouchPos(myNum,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CGeoPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CGeoPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CGeoPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReflectTouchPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_new00
static int tolua_zeus_CRobotSensor_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CRobotSensor* tolua_ret = (CRobotSensor*)  Mtolua_new((CRobotSensor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRobotSensor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_new00_local
static int tolua_zeus_CRobotSensor_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CRobotSensor* tolua_ret = (CRobotSensor*)  Mtolua_new((CRobotSensor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CRobotSensor");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_delete00
static int tolua_zeus_CRobotSensor_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_Update00
static int tolua_zeus_CRobotSensor_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
  int cycle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(cycle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInfoValid of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_IsInfoValid00
static int tolua_zeus_CRobotSensor_IsInfoValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInfoValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInfoValid(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInfoValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInfraredOn of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_IsInfraredOn00
static int tolua_zeus_CRobotSensor_IsInfraredOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInfraredOn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInfraredOn(num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInfraredOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetInraredOn of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_ResetInraredOn00
static int tolua_zeus_CRobotSensor_ResetInraredOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetInraredOn'", NULL);
#endif
  {
   self->ResetInraredOn(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetInraredOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsKickerOn of class  CRobotSensor */
#ifndef TOLUA_DISABLE_tolua_zeus_CRobotSensor_IsKickerOn00
static int tolua_zeus_CRobotSensor_IsKickerOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CRobotSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CRobotSensor* self = (CRobotSensor*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsKickerOn'", NULL);
#endif
  {
   int tolua_ret = (int)  self->IsKickerOn(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsKickerOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_zeus_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PointValueStruct","PointValueStruct","",tolua_collect_PointValueStruct);
  #else
  tolua_cclass(tolua_S,"PointValueStruct","PointValueStruct","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PointValueStruct");
   tolua_variable(tolua_S,"pos_x",tolua_get_PointValueStruct_pos_x,tolua_set_PointValueStruct_pos_x);
   tolua_variable(tolua_S,"pos_y",tolua_get_PointValueStruct_pos_y,tolua_set_PointValueStruct_pos_y);
   tolua_variable(tolua_S,"pos",tolua_get_PointValueStruct_pos,tolua_set_PointValueStruct_pos);
   tolua_variable(tolua_S,"value",tolua_get_PointValueStruct_value,tolua_set_PointValueStruct_value);
   tolua_function(tolua_S,"new",tolua_zeus_PointValueStruct_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_PointValueStruct_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_PointValueStruct_new00_local);
   tolua_function(tolua_S,".eq",tolua_zeus_PointValueStruct__eq00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AreaStruct","AreaStruct","",tolua_collect_AreaStruct);
  #else
  tolua_cclass(tolua_S,"AreaStruct","AreaStruct","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AreaStruct");
   tolua_variable(tolua_S,"_pos",tolua_get_AreaStruct__pos,tolua_set_AreaStruct__pos);
   tolua_variable(tolua_S,"_value",tolua_get_AreaStruct__value,tolua_set_AreaStruct__value);
   tolua_variable(tolua_S,"_area_idx",tolua_get_AreaStruct__area_idx,tolua_set_AreaStruct__area_idx);
   tolua_variable(tolua_S,"_conflict",tolua_get_AreaStruct__conflict,tolua_set_AreaStruct__conflict);
   tolua_function(tolua_S,"new",tolua_zeus_AreaStruct_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_AreaStruct_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_AreaStruct_new00_local);
   tolua_function(tolua_S,".eq",tolua_zeus_AreaStruct__eq00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FieldRectangle","FieldRectangle","",tolua_collect_FieldRectangle);
  #else
  tolua_cclass(tolua_S,"FieldRectangle","FieldRectangle","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FieldRectangle");
   tolua_function(tolua_S,"new",tolua_zeus_FieldRectangle_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_FieldRectangle_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_FieldRectangle_new00_local);
   tolua_function(tolua_S,"centerArea",tolua_zeus_FieldRectangle_centerArea00);
   tolua_function(tolua_S,"getCenter",tolua_zeus_FieldRectangle_getCenter00);
   tolua_variable(tolua_S,"_rangeX",tolua_get_FieldRectangle__rangeX,tolua_set_FieldRectangle__rangeX);
   tolua_variable(tolua_S,"_rangeY",tolua_get_FieldRectangle__rangeY,tolua_set_FieldRectangle__rangeY);
   tolua_variable(tolua_S,"_leftDownPos",tolua_get_FieldRectangle__leftDownPos,tolua_set_FieldRectangle__leftDownPos);
   tolua_variable(tolua_S,"_rightUpPos",tolua_get_FieldRectangle__rightUpPos,tolua_set_FieldRectangle__rightUpPos);
   tolua_variable(tolua_S,"_leftUpPos",tolua_get_FieldRectangle__leftUpPos,tolua_set_FieldRectangle__leftUpPos);
   tolua_variable(tolua_S,"_rightDownPos",tolua_get_FieldRectangle__rightDownPos,tolua_set_FieldRectangle__rightDownPos);
   tolua_variable(tolua_S,"_centerPos",tolua_get_FieldRectangle__centerPos,tolua_set_FieldRectangle__centerPos);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGPUBestAlgThread","CGPUBestAlgThread","",tolua_collect_CGPUBestAlgThread);
  #else
  tolua_cclass(tolua_S,"CGPUBestAlgThread","CGPUBestAlgThread","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGPUBestAlgThread");
   tolua_function(tolua_S,"new",tolua_zeus_CGPUBestAlgThread_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGPUBestAlgThread_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGPUBestAlgThread_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGPUBestAlgThread_delete00);
   tolua_function(tolua_S,"initialize",tolua_zeus_CGPUBestAlgThread_initialize00);
   tolua_function(tolua_S,"getBestPointFromArea",tolua_zeus_CGPUBestAlgThread_getBestPointFromArea00);
   tolua_function(tolua_S,"generatePointValue",tolua_zeus_CGPUBestAlgThread_generatePointValue00);
   tolua_function(tolua_S,"isLastOneValid",tolua_zeus_CGPUBestAlgThread_isLastOneValid00);
   tolua_function(tolua_S,"setSendPoint",tolua_zeus_CGPUBestAlgThread_setSendPoint00);
   tolua_function(tolua_S,"getPosPotential",tolua_zeus_CGPUBestAlgThread_getPosPotential00);
   tolua_function(tolua_S,"getMapSize",tolua_zeus_CGPUBestAlgThread_getMapSize00);
   tolua_function(tolua_S,"startComm",tolua_zeus_CGPUBestAlgThread_startComm00);
   tolua_function(tolua_S,"setPointValue",tolua_zeus_CGPUBestAlgThread_setPointValue00);
   tolua_function(tolua_S,"sendPointValue",tolua_zeus_CGPUBestAlgThread_sendPointValue00);
   tolua_function(tolua_S,"doBestCalculation",tolua_zeus_CGPUBestAlgThread_doBestCalculation00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CBestPlayer","CBestPlayer","",tolua_collect_CBestPlayer);
  #else
  tolua_cclass(tolua_S,"CBestPlayer","CBestPlayer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CBestPlayer");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ToBallPotentialPair","CBestPlayer::ToBallPotentialPair","",tolua_collect_CBestPlayer__ToBallPotentialPair);
   #else
   tolua_cclass(tolua_S,"ToBallPotentialPair","CBestPlayer::ToBallPotentialPair","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ToBallPotentialPair");
    tolua_function(tolua_S,"new",tolua_zeus_CBestPlayer_ToBallPotentialPair_new00);
    tolua_function(tolua_S,"new_local",tolua_zeus_CBestPlayer_ToBallPotentialPair_new00_local);
    tolua_function(tolua_S,".call",tolua_zeus_CBestPlayer_ToBallPotentialPair_new00_local);
    tolua_variable(tolua_S,"num",tolua_get_CBestPlayer__ToBallPotentialPair_num,tolua_set_CBestPlayer__ToBallPotentialPair_num);
    tolua_variable(tolua_S,"potential",tolua_get_CBestPlayer__ToBallPotentialPair_potential,tolua_set_CBestPlayer__ToBallPotentialPair_potential);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"new",tolua_zeus_CBestPlayer_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CBestPlayer_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CBestPlayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CBestPlayer_delete00);
   tolua_function(tolua_S,"update",tolua_zeus_CBestPlayer_update00);
   tolua_function(tolua_S,"getCurMesurementZ",tolua_zeus_CBestPlayer_getCurMesurementZ00);
   tolua_function(tolua_S,"getOurPotential",tolua_zeus_CBestPlayer_getOurPotential00);
   tolua_function(tolua_S,"getTheirPotential",tolua_zeus_CBestPlayer_getTheirPotential00);
   tolua_function(tolua_S,"withBall",tolua_zeus_CBestPlayer_withBall00);
   tolua_function(tolua_S,"oppWithBall",tolua_zeus_CBestPlayer_oppWithBall00);
   tolua_function(tolua_S,"isOurBestPlayerChanged",tolua_zeus_CBestPlayer_isOurBestPlayerChanged00);
   tolua_function(tolua_S,"getOurBestPlayer",tolua_zeus_CBestPlayer_getOurBestPlayer00);
   tolua_function(tolua_S,"isTheirBestPlayerChanged",tolua_zeus_CBestPlayer_isTheirBestPlayerChanged00);
   tolua_function(tolua_S,"getTheirBestPlayer",tolua_zeus_CBestPlayer_getTheirBestPlayer00);
   tolua_function(tolua_S,"isOurPlayerStrictControlBall",tolua_zeus_CBestPlayer_isOurPlayerStrictControlBall00);
   tolua_function(tolua_S,"isOurPlayerLooseControlBall",tolua_zeus_CBestPlayer_isOurPlayerLooseControlBall00);
   tolua_function(tolua_S,"isTheirPlayerStrictControlBall",tolua_zeus_CBestPlayer_isTheirPlayerStrictControlBall00);
   tolua_function(tolua_S,"isTheirPlayerLooseControlBall",tolua_zeus_CBestPlayer_isTheirPlayerLooseControlBall00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CVisionModule","CVisionModule","",tolua_collect_CVisionModule);
  #else
  tolua_cclass(tolua_S,"CVisionModule","CVisionModule","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CVisionModule");
   tolua_function(tolua_S,"new",tolua_zeus_CVisionModule_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVisionModule_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVisionModule_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CVisionModule_delete00);
   tolua_function(tolua_S,"registerOption",tolua_zeus_CVisionModule_registerOption00);
   tolua_function(tolua_S,"getValidNum",tolua_zeus_CVisionModule_getValidNum00);
   tolua_function(tolua_S,"getTheirValidNum",tolua_zeus_CVisionModule_getTheirValidNum00);
   tolua_function(tolua_S,"SetRefRecvMsg",tolua_zeus_CVisionModule_SetRefRecvMsg00);
   tolua_function(tolua_S,"SetNewVision",tolua_zeus_CVisionModule_SetNewVision00);
   tolua_function(tolua_S,"AllPlayer",tolua_zeus_CVisionModule_AllPlayer00);
   tolua_function(tolua_S,"OurPlayer",tolua_zeus_CVisionModule_OurPlayer00);
   tolua_function(tolua_S,"TheirPlayer",tolua_zeus_CVisionModule_TheirPlayer00);
   tolua_function(tolua_S,"Ball",tolua_zeus_CVisionModule_Ball00);
   tolua_function(tolua_S,"OurPlayer",tolua_zeus_CVisionModule_OurPlayer01);
   tolua_function(tolua_S,"TheirPlayer",tolua_zeus_CVisionModule_TheirPlayer01);
   tolua_function(tolua_S,"Ball",tolua_zeus_CVisionModule_Ball01);
   tolua_function(tolua_S,"SetPlayerCommand",tolua_zeus_CVisionModule_SetPlayerCommand00);
   tolua_function(tolua_S,"gameState",tolua_zeus_CVisionModule_gameState00);
   tolua_function(tolua_S,"Cycle",tolua_zeus_CVisionModule_Cycle00);
   tolua_function(tolua_S,"LastCycle",tolua_zeus_CVisionModule_LastCycle00);
   tolua_function(tolua_S,"Side",tolua_zeus_CVisionModule_Side00);
   tolua_function(tolua_S,"GetCurrentRefereeMsg",tolua_zeus_CVisionModule_GetCurrentRefereeMsg00);
   tolua_function(tolua_S,"GetLastRefereeMsg",tolua_zeus_CVisionModule_GetLastRefereeMsg00);
   tolua_function(tolua_S,"OurGoal",tolua_zeus_CVisionModule_OurGoal00);
   tolua_function(tolua_S,"TheirGoal",tolua_zeus_CVisionModule_TheirGoal00);
   tolua_function(tolua_S,"TheirGoalie",tolua_zeus_CVisionModule_TheirGoalie00);
   tolua_function(tolua_S,"OurRawPlayerSpeed",tolua_zeus_CVisionModule_OurRawPlayerSpeed00);
   tolua_function(tolua_S,"TheirRawPlayerSpeed",tolua_zeus_CVisionModule_TheirRawPlayerSpeed00);
   tolua_function(tolua_S,"GetTheirPenaltyNum",tolua_zeus_CVisionModule_GetTheirPenaltyNum00);
   tolua_function(tolua_S,"ResetTheirPenaltyNum",tolua_zeus_CVisionModule_ResetTheirPenaltyNum00);
   tolua_function(tolua_S,"GetTheirGoalieStrategyNum",tolua_zeus_CVisionModule_GetTheirGoalieStrategyNum00);
   tolua_function(tolua_S,"getBallVelStable",tolua_zeus_CVisionModule_getBallVelStable00);
   tolua_function(tolua_S,"getBallPlacementPosition",tolua_zeus_CVisionModule_getBallPlacementPosition00);
   tolua_function(tolua_S,"ballVelValid",tolua_zeus_CVisionModule_ballVelValid00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CAttributeSet","CAttributeSet","",NULL);
  tolua_beginmodule(tolua_S,"CAttributeSet");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTrigger","CTrigger","",NULL);
  tolua_beginmodule(tolua_S,"CTrigger");
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MarkField","MarkField","",tolua_collect_MarkField);
  #else
  tolua_cclass(tolua_S,"MarkField","MarkField","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MarkField");
   tolua_function(tolua_S,"new",tolua_zeus_MarkField_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_MarkField_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_MarkField_new00_local);
   tolua_variable(tolua_S,"_upLeft",tolua_get_MarkField__upLeft,tolua_set_MarkField__upLeft);
   tolua_variable(tolua_S,"_downRight",tolua_get_MarkField__downRight,tolua_set_MarkField__downRight);
   tolua_variable(tolua_S,"markTouchNum",tolua_get_MarkField_markTouchNum,tolua_set_MarkField_markTouchNum);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AttackerStruct","AttackerStruct","",tolua_collect_AttackerStruct);
  #else
  tolua_cclass(tolua_S,"AttackerStruct","AttackerStruct","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AttackerStruct");
   tolua_function(tolua_S,"new",tolua_zeus_AttackerStruct_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_AttackerStruct_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_AttackerStruct_new00_local);
   tolua_variable(tolua_S,"num",tolua_get_AttackerStruct_num,tolua_set_AttackerStruct_num);
   tolua_variable(tolua_S,"prioirty",tolua_get_AttackerStruct_prioirty,tolua_set_AttackerStruct_prioirty);
   tolua_variable(tolua_S,"subValue",tolua_get_AttackerStruct_subValue,tolua_set_AttackerStruct_subValue);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDefenceInfo","CDefenceInfo","",tolua_collect_CDefenceInfo);
  #else
  tolua_cclass(tolua_S,"CDefenceInfo","CDefenceInfo","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDefenceInfo");
   tolua_function(tolua_S,"new",tolua_zeus_CDefenceInfo_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CDefenceInfo_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CDefenceInfo_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CDefenceInfo_delete00);
   tolua_function(tolua_S,"initialization",tolua_zeus_CDefenceInfo_initialization00);
   tolua_function(tolua_S,"updateDefenceInfo",tolua_zeus_CDefenceInfo_updateDefenceInfo00);
   tolua_function(tolua_S,"setNoChangeFlag",tolua_zeus_CDefenceInfo_setNoChangeFlag00);
   tolua_function(tolua_S,"clearNoChangeFlag",tolua_zeus_CDefenceInfo_clearNoChangeFlag00);
   tolua_function(tolua_S,"setNoMarkingField",tolua_zeus_CDefenceInfo_setNoMarkingField00);
   tolua_function(tolua_S,"clearNoMarkingField",tolua_zeus_CDefenceInfo_clearNoMarkingField00);
   tolua_function(tolua_S,"clearAll",tolua_zeus_CDefenceInfo_clearAll00);
   tolua_function(tolua_S,"changeAttrSet",tolua_zeus_CDefenceInfo_changeAttrSet00);
   tolua_function(tolua_S,"setNoMarkingNum",tolua_zeus_CDefenceInfo_setNoMarkingNum00);
   tolua_function(tolua_S,"resetMarkingInfo",tolua_zeus_CDefenceInfo_resetMarkingInfo00);
   tolua_function(tolua_S,"getOppoNum",tolua_zeus_CDefenceInfo_getOppoNum00);
   tolua_function(tolua_S,"getAttackNum",tolua_zeus_CDefenceInfo_getAttackNum00);
   tolua_function(tolua_S,"getAttackOppNumByPri",tolua_zeus_CDefenceInfo_getAttackOppNumByPri00);
   tolua_function(tolua_S,"getSteadyAttackOppNumByPri",tolua_zeus_CDefenceInfo_getSteadyAttackOppNumByPri00);
   tolua_function(tolua_S,"queryMarked",tolua_zeus_CDefenceInfo_queryMarked00);
   tolua_function(tolua_S,"getOurMarkDenfender",tolua_zeus_CDefenceInfo_getOurMarkDenfender00);
   tolua_function(tolua_S,"getMarkMode",tolua_zeus_CDefenceInfo_getMarkMode00);
   tolua_function(tolua_S,"getTriggerState",tolua_zeus_CDefenceInfo_getTriggerState00);
   tolua_function(tolua_S,"getOppPlayerByNum",tolua_zeus_CDefenceInfo_getOppPlayerByNum00);
   tolua_function(tolua_S,"getBallTaken",tolua_zeus_CDefenceInfo_getBallTaken00);
   tolua_function(tolua_S,"getMarkFieldList",tolua_zeus_CDefenceInfo_getMarkFieldList00);
   tolua_function(tolua_S,"checkInRecArea",tolua_zeus_CDefenceInfo_checkInRecArea00);
   tolua_function(tolua_S,"checkOurInRecArea",tolua_zeus_CDefenceInfo_checkOurInRecArea00);
   tolua_function(tolua_S,"getMarkingTouchNum",tolua_zeus_CDefenceInfo_getMarkingTouchNum00);
   tolua_function(tolua_S,"setMarkList",tolua_zeus_CDefenceInfo_setMarkList00);
   tolua_function(tolua_S,"setMarkingTouchInfo",tolua_zeus_CDefenceInfo_setMarkingTouchInfo00);
   tolua_function(tolua_S,"setMarkMode",tolua_zeus_CDefenceInfo_setMarkMode00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"POS_SIDE_LEFT",POS_SIDE_LEFT);
  tolua_constant(tolua_S,"POS_SIDE_RIGHT",POS_SIDE_RIGHT);
  tolua_constant(tolua_S,"POS_SIDE_MIDDLE",POS_SIDE_MIDDLE);
  tolua_module(tolua_S,"DefendUtils",0);
  tolua_beginmodule(tolua_S,"DefendUtils");
   tolua_function(tolua_S,"getPenaltyFronter",tolua_zeus_DefendUtils_getPenaltyFronter00);
   tolua_function(tolua_S,"isPosInOurPenaltyArea",tolua_zeus_DefendUtils_isPosInOurPenaltyArea00);
   tolua_function(tolua_S,"reversePoint",tolua_zeus_DefendUtils_reversePoint00);
   tolua_function(tolua_S,"calcBlockAngle",tolua_zeus_DefendUtils_calcBlockAngle00);
   tolua_function(tolua_S,"leftCirValid",tolua_zeus_DefendUtils_leftCirValid00);
   tolua_function(tolua_S,"rightCirValid",tolua_zeus_DefendUtils_rightCirValid00);
   tolua_function(tolua_S,"getEnemyShooter",tolua_zeus_DefendUtils_getEnemyShooter00);
   tolua_function(tolua_S,"getDefenceTargetAndLine",tolua_zeus_DefendUtils_getDefenceTargetAndLine00);
   tolua_function(tolua_S,"calcDefenderPoint",tolua_zeus_DefendUtils_calcDefenderPoint00);
   tolua_function(tolua_S,"getSideBackTargetAndLine",tolua_zeus_DefendUtils_getSideBackTargetAndLine00);
   tolua_function(tolua_S,"calcDefenderPointV2",tolua_zeus_DefendUtils_calcDefenderPointV200);
   tolua_function(tolua_S,"calcDefenderPointV3",tolua_zeus_DefendUtils_calcDefenderPointV300);
   tolua_function(tolua_S,"calcGoaliePointV2",tolua_zeus_DefendUtils_calcGoaliePointV200);
   tolua_function(tolua_S,"calcGoaliePointV3",tolua_zeus_DefendUtils_calcGoaliePointV300);
   tolua_function(tolua_S,"calcPenaltyLinePoint",tolua_zeus_DefendUtils_calcPenaltyLinePoint00);
   tolua_function(tolua_S,"isBallShotToTheGoal",tolua_zeus_DefendUtils_isBallShotToTheGoal00);
   tolua_function(tolua_S,"BallIsToPenaltyArea",tolua_zeus_DefendUtils_BallIsToPenaltyArea00);
   tolua_function(tolua_S,"inHalfCourt",tolua_zeus_DefendUtils_inHalfCourt00);
   tolua_function(tolua_S,"getBallShooted",tolua_zeus_DefendUtils_getBallShooted00);
   tolua_function(tolua_S,"getEnemyPass",tolua_zeus_DefendUtils_getEnemyPass00);
   tolua_function(tolua_S,"getCornerAreaPos",tolua_zeus_DefendUtils_getCornerAreaPos00);
   tolua_function(tolua_S,"getMiddleAreaPos",tolua_zeus_DefendUtils_getMiddleAreaPos00);
   tolua_function(tolua_S,"getDeDribblePos",tolua_zeus_DefendUtils_getDeDribblePos00);
   tolua_function(tolua_S,"getIndirectDefender",tolua_zeus_DefendUtils_getIndirectDefender00);
   tolua_function(tolua_S,"getMiddleDefender",tolua_zeus_DefendUtils_getMiddleDefender00);
   tolua_function(tolua_S,"getDefaultPos",tolua_zeus_DefendUtils_getDefaultPos00);
   tolua_function(tolua_S,"checkInDeadArea",tolua_zeus_DefendUtils_checkInDeadArea00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Defend2015","Defend2015","",tolua_collect_Defend2015);
  #else
  tolua_cclass(tolua_S,"Defend2015","Defend2015","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Defend2015");
   tolua_variable(tolua_S,"leftD",tolua_get_Defend2015_leftD,tolua_set_Defend2015_leftD);
   tolua_variable(tolua_S,"rightD",tolua_get_Defend2015_rightD,tolua_set_Defend2015_rightD);
   tolua_variable(tolua_S,"leftFrontD",tolua_get_Defend2015_leftFrontD,tolua_set_Defend2015_leftFrontD);
   tolua_variable(tolua_S,"rightFrontD",tolua_get_Defend2015_rightFrontD,tolua_set_Defend2015_rightFrontD);
   tolua_variable(tolua_S,"leftBackD",tolua_get_Defend2015_leftBackD,tolua_set_Defend2015_leftBackD);
   tolua_variable(tolua_S,"rightBackD",tolua_get_Defend2015_rightBackD,tolua_set_Defend2015_rightBackD);
   tolua_variable(tolua_S,"leftCenD",tolua_get_Defend2015_leftCenD,tolua_set_Defend2015_leftCenD);
   tolua_variable(tolua_S,"rightCenD",tolua_get_Defend2015_rightCenD,tolua_set_Defend2015_rightCenD);
   tolua_variable(tolua_S,"middleD",tolua_get_Defend2015_middleD,tolua_set_Defend2015_middleD);
   tolua_variable(tolua_S,"singleD",tolua_get_Defend2015_singleD,tolua_set_Defend2015_singleD);
   tolua_variable(tolua_S,"goalieD",tolua_get_Defend2015_goalieD,tolua_set_Defend2015_goalieD);
   tolua_variable(tolua_S,"sideD",tolua_get_Defend2015_sideD,tolua_set_Defend2015_sideD);
   tolua_function(tolua_S,"getSidePos",tolua_zeus_Defend2015_getSidePos00);
   tolua_function(tolua_S,"getLeftPos",tolua_zeus_Defend2015_getLeftPos00);
   tolua_function(tolua_S,"getRightPos",tolua_zeus_Defend2015_getRightPos00);
   tolua_function(tolua_S,"getLeftCenPos",tolua_zeus_Defend2015_getLeftCenPos00);
   tolua_function(tolua_S,"getRightCenPos",tolua_zeus_Defend2015_getRightCenPos00);
   tolua_function(tolua_S,"getMiddlePos",tolua_zeus_Defend2015_getMiddlePos00);
   tolua_function(tolua_S,"getSinglePos",tolua_zeus_Defend2015_getSinglePos00);
   tolua_function(tolua_S,"getGoaliePos",tolua_zeus_Defend2015_getGoaliePos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDefPos2015","CDefPos2015","",tolua_collect_CDefPos2015);
  #else
  tolua_cclass(tolua_S,"CDefPos2015","CDefPos2015","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDefPos2015");
   tolua_function(tolua_S,"new",tolua_zeus_CDefPos2015_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CDefPos2015_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CDefPos2015_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CDefPos2015_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CDefPos2015_generatePos00);
   tolua_function(tolua_S,"getDefPos2015",tolua_zeus_CDefPos2015_getDefPos201500);
   tolua_function(tolua_S,"checkCollision",tolua_zeus_CDefPos2015_checkCollision00);
   tolua_function(tolua_S,"getSidePos",tolua_zeus_CDefPos2015_getSidePos00);
   tolua_function(tolua_S,"getLeftPos",tolua_zeus_CDefPos2015_getLeftPos00);
   tolua_function(tolua_S,"getRightPos",tolua_zeus_CDefPos2015_getRightPos00);
   tolua_function(tolua_S,"getLeftCenPos",tolua_zeus_CDefPos2015_getLeftCenPos00);
   tolua_function(tolua_S,"getRightCenPos",tolua_zeus_CDefPos2015_getRightCenPos00);
   tolua_function(tolua_S,"getMiddlePos",tolua_zeus_CDefPos2015_getMiddlePos00);
   tolua_function(tolua_S,"getSinglePos",tolua_zeus_CDefPos2015_getSinglePos00);
   tolua_function(tolua_S,"getGoaliePos",tolua_zeus_CDefPos2015_getGoaliePos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameState","GameState","",tolua_collect_GameState);
  #else
  tolua_cclass(tolua_S,"GameState","GameState","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameState");
   tolua_function(tolua_S,"new",tolua_zeus_GameState_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_GameState_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_GameState_new00_local);
   tolua_function(tolua_S,"init",tolua_zeus_GameState_init00);
   tolua_function(tolua_S,"get",tolua_zeus_GameState_get00);
   tolua_function(tolua_S,"set",tolua_zeus_GameState_set00);
   tolua_function(tolua_S,"transition",tolua_zeus_GameState_transition00);
   tolua_function(tolua_S,"gameOn",tolua_zeus_GameState_gameOn00);
   tolua_function(tolua_S,"gameOff",tolua_zeus_GameState_gameOff00);
   tolua_function(tolua_S,"gameOver",tolua_zeus_GameState_gameOver00);
   tolua_function(tolua_S,"restart",tolua_zeus_GameState_restart00);
   tolua_function(tolua_S,"ourRestart",tolua_zeus_GameState_ourRestart00);
   tolua_function(tolua_S,"theirRestart",tolua_zeus_GameState_theirRestart00);
   tolua_function(tolua_S,"kickoff",tolua_zeus_GameState_kickoff00);
   tolua_function(tolua_S,"ourKickoff",tolua_zeus_GameState_ourKickoff00);
   tolua_function(tolua_S,"theirKickoff",tolua_zeus_GameState_theirKickoff00);
   tolua_function(tolua_S,"penaltyKick",tolua_zeus_GameState_penaltyKick00);
   tolua_function(tolua_S,"ourPenaltyKick",tolua_zeus_GameState_ourPenaltyKick00);
   tolua_function(tolua_S,"theirPenaltyKick",tolua_zeus_GameState_theirPenaltyKick00);
   tolua_function(tolua_S,"directKick",tolua_zeus_GameState_directKick00);
   tolua_function(tolua_S,"ourDirectKick",tolua_zeus_GameState_ourDirectKick00);
   tolua_function(tolua_S,"theirDirectKick",tolua_zeus_GameState_theirDirectKick00);
   tolua_function(tolua_S,"indirectKick",tolua_zeus_GameState_indirectKick00);
   tolua_function(tolua_S,"ourIndirectKick",tolua_zeus_GameState_ourIndirectKick00);
   tolua_function(tolua_S,"theirIndirectKick",tolua_zeus_GameState_theirIndirectKick00);
   tolua_function(tolua_S,"freeKick",tolua_zeus_GameState_freeKick00);
   tolua_function(tolua_S,"ourFreeKick",tolua_zeus_GameState_ourFreeKick00);
   tolua_function(tolua_S,"theirFreeKick",tolua_zeus_GameState_theirFreeKick00);
   tolua_function(tolua_S,"ballPlacement",tolua_zeus_GameState_ballPlacement00);
   tolua_function(tolua_S,"ourBallPlacement",tolua_zeus_GameState_ourBallPlacement00);
   tolua_function(tolua_S,"theirBallPlacement",tolua_zeus_GameState_theirBallPlacement00);
   tolua_function(tolua_S,"canMove",tolua_zeus_GameState_canMove00);
   tolua_function(tolua_S,"allowedNearBall",tolua_zeus_GameState_allowedNearBall00);
   tolua_function(tolua_S,"canKickBall",tolua_zeus_GameState_canKickBall00);
   tolua_function(tolua_S,"canEitherKickBall",tolua_zeus_GameState_canEitherKickBall00);
   tolua_function(tolua_S,"isOurTimeout",tolua_zeus_GameState_isOurTimeout00);
   tolua_function(tolua_S,"isTheirTimeout",tolua_zeus_GameState_isTheirTimeout00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGDebugEngine","CGDebugEngine","",tolua_collect_CGDebugEngine);
  #else
  tolua_cclass(tolua_S,"CGDebugEngine","CGDebugEngine","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGDebugEngine");
   tolua_function(tolua_S,"new",tolua_zeus_CGDebugEngine_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGDebugEngine_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGDebugEngine_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGDebugEngine_delete00);
   tolua_function(tolua_S,"gui_debug_x",tolua_zeus_CGDebugEngine_gui_debug_x00);
   tolua_function(tolua_S,"gui_debug_line",tolua_zeus_CGDebugEngine_gui_debug_line00);
   tolua_function(tolua_S,"gui_debug_arc",tolua_zeus_CGDebugEngine_gui_debug_arc00);
   tolua_function(tolua_S,"gui_debug_triangle",tolua_zeus_CGDebugEngine_gui_debug_triangle00);
   tolua_function(tolua_S,"gui_debug_robot",tolua_zeus_CGDebugEngine_gui_debug_robot00);
   tolua_function(tolua_S,"gui_debug_msg",tolua_zeus_CGDebugEngine_gui_debug_msg00);
   tolua_function(tolua_S,"gui_debug_curve",tolua_zeus_CGDebugEngine_gui_debug_curve00);
   tolua_function(tolua_S,"send",tolua_zeus_CGDebugEngine_send00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CVector","CVector","",tolua_collect_CVector);
  #else
  tolua_cclass(tolua_S,"CVector","CVector","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CVector");
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CVector_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CVector_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CVector_new02_local);
   tolua_function(tolua_S,"setVector",tolua_zeus_CVector_setVector00);
   tolua_function(tolua_S,"mod",tolua_zeus_CVector_mod00);
   tolua_function(tolua_S,"mod2",tolua_zeus_CVector_mod200);
   tolua_function(tolua_S,"dir",tolua_zeus_CVector_dir00);
   tolua_function(tolua_S,"theta",tolua_zeus_CVector_theta00);
   tolua_function(tolua_S,"rotate",tolua_zeus_CVector_rotate00);
   tolua_function(tolua_S,"unit",tolua_zeus_CVector_unit00);
   tolua_function(tolua_S,"x",tolua_zeus_CVector_x00);
   tolua_function(tolua_S,"y",tolua_zeus_CVector_y00);
   tolua_function(tolua_S,"value",tolua_zeus_CVector_value00);
   tolua_function(tolua_S,".add",tolua_zeus_CVector__add00);
   tolua_function(tolua_S,".sub",tolua_zeus_CVector__sub00);
   tolua_function(tolua_S,".mul",tolua_zeus_CVector__mul00);
   tolua_function(tolua_S,".mul",tolua_zeus_CVector__mul01);
   tolua_function(tolua_S,".div",tolua_zeus_CVector__div00);
   tolua_function(tolua_S,".sub",tolua_zeus_CVector__sub01);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoPoint","CGeoPoint","",tolua_collect_CGeoPoint);
  #else
  tolua_cclass(tolua_S,"CGeoPoint","CGeoPoint","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoPoint");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CGeoPoint_delete00);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoPoint_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoPoint_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoPoint_new02_local);
   tolua_function(tolua_S,".eq",tolua_zeus_CGeoPoint__eq00);
   tolua_function(tolua_S,"x",tolua_zeus_CGeoPoint_x00);
   tolua_function(tolua_S,"y",tolua_zeus_CGeoPoint_y00);
   tolua_function(tolua_S,"setX",tolua_zeus_CGeoPoint_setX00);
   tolua_function(tolua_S,"setY",tolua_zeus_CGeoPoint_setY00);
   tolua_function(tolua_S,"fill",tolua_zeus_CGeoPoint_fill00);
   tolua_function(tolua_S,"dist",tolua_zeus_CGeoPoint_dist00);
   tolua_function(tolua_S,"dist2",tolua_zeus_CGeoPoint_dist200);
   tolua_function(tolua_S,".add",tolua_zeus_CGeoPoint__add00);
   tolua_function(tolua_S,".mul",tolua_zeus_CGeoPoint__mul00);
   tolua_function(tolua_S,".sub",tolua_zeus_CGeoPoint__sub00);
   tolua_function(tolua_S,"midPoint",tolua_zeus_CGeoPoint_midPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLine","CGeoLine","",tolua_collect_CGeoLine);
  #else
  tolua_cclass(tolua_S,"CGeoLine","CGeoLine","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLine");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLine_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLine_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLine_new02_local);
   tolua_function(tolua_S,"calABC",tolua_zeus_CGeoLine_calABC00);
   tolua_function(tolua_S,"projection",tolua_zeus_CGeoLine_projection00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLine_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLine_point200);
   tolua_function(tolua_S,".eq",tolua_zeus_CGeoLine__eq00);
   tolua_function(tolua_S,"a",tolua_zeus_CGeoLine_a00);
   tolua_function(tolua_S,"b",tolua_zeus_CGeoLine_b00);
   tolua_function(tolua_S,"c",tolua_zeus_CGeoLine_c00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineLineIntersection","CGeoLineLineIntersection","",tolua_collect_CGeoLineLineIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineLineIntersection","CGeoLineLineIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineLineIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineLineIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineLineIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineLineIntersection_new00_local);
   tolua_function(tolua_S,"Intersectant",tolua_zeus_CGeoLineLineIntersection_Intersectant00);
   tolua_function(tolua_S,"IntersectPoint",tolua_zeus_CGeoLineLineIntersection_IntersectPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoSegment","CGeoSegment","CGeoLine",tolua_collect_CGeoSegment);
  #else
  tolua_cclass(tolua_S,"CGeoSegment","CGeoSegment","CGeoLine",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoSegment");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoSegment_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoSegment_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoSegment_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoSegment_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoSegment_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoSegment_new01_local);
   tolua_function(tolua_S,"IsPointOnLineOnSegment",tolua_zeus_CGeoSegment_IsPointOnLineOnSegment00);
   tolua_function(tolua_S,"IsSegmentsIntersect",tolua_zeus_CGeoSegment_IsSegmentsIntersect00);
   tolua_function(tolua_S,"segmentsIntersectPoint",tolua_zeus_CGeoSegment_segmentsIntersectPoint00);
   tolua_function(tolua_S,"dist2Point",tolua_zeus_CGeoSegment_dist2Point00);
   tolua_function(tolua_S,"dist2Segment",tolua_zeus_CGeoSegment_dist2Segment00);
   tolua_function(tolua_S,"start",tolua_zeus_CGeoSegment_start00);
   tolua_function(tolua_S,"end",tolua_zeus_CGeoSegment_end00);
   tolua_function(tolua_S,"center",tolua_zeus_CGeoSegment_center00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoShape","CGeoShape","",tolua_collect_CGeoShape);
  #else
  tolua_cclass(tolua_S,"CGeoShape","CGeoShape","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoShape");
   tolua_function(tolua_S,"delete",tolua_zeus_CGeoShape_delete00);
   tolua_function(tolua_S,"HasPoint",tolua_zeus_CGeoShape_HasPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoRectangle","CGeoRectangle","CGeoShape",tolua_collect_CGeoRectangle);
  #else
  tolua_cclass(tolua_S,"CGeoRectangle","CGeoRectangle","CGeoShape",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoRectangle");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoRectangle_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoRectangle_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoRectangle_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoRectangle_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoRectangle_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoRectangle_new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoRectangle_new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoRectangle_new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoRectangle_new02_local);
   tolua_function(tolua_S,"calPoint",tolua_zeus_CGeoRectangle_calPoint00);
   tolua_function(tolua_S,"dist2Point",tolua_zeus_CGeoRectangle_dist2Point00);
   tolua_function(tolua_S,"HasPoint",tolua_zeus_CGeoRectangle_HasPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineRectangleIntersection","CGeoLineRectangleIntersection","",tolua_collect_CGeoLineRectangleIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineRectangleIntersection","CGeoLineRectangleIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineRectangleIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineRectangleIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineRectangleIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineRectangleIntersection_new00_local);
   tolua_function(tolua_S,"intersectant",tolua_zeus_CGeoLineRectangleIntersection_intersectant00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLineRectangleIntersection_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLineRectangleIntersection_point200);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoCirlce","CGeoCirlce","CGeoShape",tolua_collect_CGeoCirlce);
  #else
  tolua_cclass(tolua_S,"CGeoCirlce","CGeoCirlce","CGeoShape",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoCirlce");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoCirlce_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoCirlce_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoCirlce_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoCirlce_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoCirlce_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoCirlce_new01_local);
   tolua_function(tolua_S,"HasPoint",tolua_zeus_CGeoCirlce_HasPoint00);
   tolua_function(tolua_S,"Center",tolua_zeus_CGeoCirlce_Center00);
   tolua_function(tolua_S,"Radius",tolua_zeus_CGeoCirlce_Radius00);
   tolua_function(tolua_S,"Radius2",tolua_zeus_CGeoCirlce_Radius200);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineCircleIntersection","CGeoLineCircleIntersection","",tolua_collect_CGeoLineCircleIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineCircleIntersection","CGeoLineCircleIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineCircleIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineCircleIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineCircleIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineCircleIntersection_new00_local);
   tolua_function(tolua_S,"intersectant",tolua_zeus_CGeoLineCircleIntersection_intersectant00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLineCircleIntersection_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLineCircleIntersection_point200);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoEllipse","CGeoEllipse","CGeoShape",tolua_collect_CGeoEllipse);
  #else
  tolua_cclass(tolua_S,"CGeoEllipse","CGeoEllipse","CGeoShape",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoEllipse");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoEllipse_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoEllipse_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoEllipse_new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_CGeoEllipse_new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoEllipse_new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoEllipse_new01_local);
   tolua_function(tolua_S,"Center",tolua_zeus_CGeoEllipse_Center00);
   tolua_function(tolua_S,"HasPoint",tolua_zeus_CGeoEllipse_HasPoint00);
   tolua_function(tolua_S,"Xaxis",tolua_zeus_CGeoEllipse_Xaxis00);
   tolua_function(tolua_S,"Yaxis",tolua_zeus_CGeoEllipse_Yaxis00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoLineEllipseIntersection","CGeoLineEllipseIntersection","",tolua_collect_CGeoLineEllipseIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoLineEllipseIntersection","CGeoLineEllipseIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoLineEllipseIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoLineEllipseIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoLineEllipseIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoLineEllipseIntersection_new00_local);
   tolua_function(tolua_S,"intersectant",tolua_zeus_CGeoLineEllipseIntersection_intersectant00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoLineEllipseIntersection_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoLineEllipseIntersection_point200);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGeoSegmentCircleIntersection","CGeoSegmentCircleIntersection","",tolua_collect_CGeoSegmentCircleIntersection);
  #else
  tolua_cclass(tolua_S,"CGeoSegmentCircleIntersection","CGeoSegmentCircleIntersection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGeoSegmentCircleIntersection");
   tolua_function(tolua_S,"new",tolua_zeus_CGeoSegmentCircleIntersection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGeoSegmentCircleIntersection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGeoSegmentCircleIntersection_new00_local);
   tolua_function(tolua_S,"intersectant",tolua_zeus_CGeoSegmentCircleIntersection_intersectant00);
   tolua_function(tolua_S,"point1",tolua_zeus_CGeoSegmentCircleIntersection_point100);
   tolua_function(tolua_S,"point2",tolua_zeus_CGeoSegmentCircleIntersection_point200);
   tolua_function(tolua_S,"size",tolua_zeus_CGeoSegmentCircleIntersection_size00);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"paramManager",tolua_get_paramManager_ptr,tolua_set_paramManager_ptr);
  tolua_variable(tolua_S,"oParamManager",tolua_get_oParamManager_ptr,tolua_set_oParamManager_ptr);
  tolua_variable(tolua_S,"cParamManager",tolua_get_cParamManager_ptr,tolua_set_cParamManager_ptr);
  tolua_variable(tolua_S,"vParamManager",tolua_get_vParamManager_ptr,tolua_set_vParamManager_ptr);
  tolua_variable(tolua_S,"sParamManager",tolua_get_sParamManager_ptr,tolua_set_sParamManager_ptr);
  tolua_variable(tolua_S,"vision",tolua_get_vision_ptr,tolua_set_vision_ptr);
  tolua_variable(tolua_S,"kickStatus",tolua_get_kickStatus_ptr,tolua_set_kickStatus_ptr);
  tolua_variable(tolua_S,"dribbleStatus",tolua_get_dribbleStatus_ptr,tolua_set_dribbleStatus_ptr);
  tolua_variable(tolua_S,"debugEngine",tolua_get_debugEngine_ptr,tolua_set_debugEngine_ptr);
  tolua_variable(tolua_S,"world",tolua_get_world_ptr,tolua_set_world_ptr);
  tolua_variable(tolua_S,"kickDirection",tolua_get_kickDirection_ptr,tolua_set_kickDirection_ptr);
  tolua_variable(tolua_S,"bestAlg",tolua_get_bestAlg_ptr,tolua_set_bestAlg_ptr);
  tolua_variable(tolua_S,"defPos2015",tolua_get_defPos2015_ptr,tolua_set_defPos2015_ptr);
  tolua_variable(tolua_S,"guardPos",tolua_get_guardPos_ptr,tolua_set_guardPos_ptr);
  tolua_variable(tolua_S,"defPos2013",tolua_get_defPos2013_ptr,tolua_set_defPos2013_ptr);
  tolua_variable(tolua_S,"tandemPos",tolua_get_tandemPos_ptr,tolua_set_tandemPos_ptr);
  tolua_variable(tolua_S,"bestPlayer",tolua_get_bestPlayer_ptr,tolua_set_bestPlayer_ptr);
  tolua_variable(tolua_S,"defenceInfo",tolua_get_defenceInfo_ptr,tolua_set_defenceInfo_ptr);
  tolua_variable(tolua_S,"chipBallJudge",tolua_get_chipBallJudge_ptr,tolua_set_chipBallJudge_ptr);
  tolua_variable(tolua_S,"indirectDefender",tolua_get_indirectDefender_ptr,tolua_set_indirectDefender_ptr);
  tolua_variable(tolua_S,"supportPos",tolua_get_supportPos_ptr,tolua_set_supportPos_ptr);
  tolua_variable(tolua_S,"supportPos2022",tolua_get_supportPos2022_ptr,tolua_set_supportPos2022_ptr);
  tolua_function(tolua_S,"initializeSingleton",tolua_zeus_initializeSingleton00);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CGuardPos","CGuardPos","",tolua_collect_CGuardPos);
  #else
  tolua_cclass(tolua_S,"CGuardPos","CGuardPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CGuardPos");
   tolua_function(tolua_S,"new",tolua_zeus_CGuardPos_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CGuardPos_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CGuardPos_new00_local);
   tolua_function(tolua_S,"backPos",tolua_zeus_CGuardPos_backPos00);
   tolua_function(tolua_S,"setBackNum",tolua_zeus_CGuardPos_setBackNum00);
   tolua_function(tolua_S,"checkValidNum",tolua_zeus_CGuardPos_checkValidNum00);
   tolua_function(tolua_S,"validBackPos",tolua_zeus_CGuardPos_validBackPos00);
   tolua_function(tolua_S,"missingBackIndex",tolua_zeus_CGuardPos_missingBackIndex00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"KickOffArea","KickOffArea","",NULL);
  tolua_beginmodule(tolua_S,"KickOffArea");
   tolua_variable(tolua_S,"_Left",tolua_get_KickOffArea__Left,tolua_set_KickOffArea__Left);
   tolua_variable(tolua_S,"_Right",tolua_get_KickOffArea__Right,tolua_set_KickOffArea__Right);
   tolua_variable(tolua_S,"baseDir",tolua_get_KickOffArea_baseDir,tolua_set_KickOffArea_baseDir);
   tolua_variable(tolua_S,"radius",tolua_get_KickOffArea_radius,tolua_set_KickOffArea_radius);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TwoKickPos","TwoKickPos","",tolua_collect_TwoKickPos);
  #else
  tolua_cclass(tolua_S,"TwoKickPos","TwoKickPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TwoKickPos");
   tolua_variable(tolua_S,"onePos",tolua_get_TwoKickPos_onePos,tolua_set_TwoKickPos_onePos);
   tolua_variable(tolua_S,"anotherPos",tolua_get_TwoKickPos_anotherPos,tolua_set_TwoKickPos_anotherPos);
   tolua_function(tolua_S,"getOnePos",tolua_zeus_TwoKickPos_getOnePos00);
   tolua_function(tolua_S,"getAnotherPos",tolua_zeus_TwoKickPos_getAnotherPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CIndirectDefender","CIndirectDefender","CDefPos1G2D",tolua_collect_CIndirectDefender);
  #else
  tolua_cclass(tolua_S,"CIndirectDefender","CIndirectDefender","CDefPos1G2D",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CIndirectDefender");
   tolua_function(tolua_S,"new",tolua_zeus_CIndirectDefender_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CIndirectDefender_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CIndirectDefender_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CIndirectDefender_delete00);
   tolua_function(tolua_S,"getDefPos",tolua_zeus_CIndirectDefender_getDefPos00);
   tolua_function(tolua_S,"getTwoDefPos",tolua_zeus_CIndirectDefender_getTwoDefPos00);
   tolua_function(tolua_S,"generateTwoDefPos",tolua_zeus_CIndirectDefender_generateTwoDefPos00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CIndirectDefender_generatePos00);
   tolua_function(tolua_S,"DefendPos",tolua_zeus_CIndirectDefender_DefendPos00);
   tolua_function(tolua_S,"FindMinMax",tolua_zeus_CIndirectDefender_FindMinMax00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CKickDirection","CKickDirection","",tolua_collect_CKickDirection);
  #else
  tolua_cclass(tolua_S,"CKickDirection","CKickDirection","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CKickDirection");
   tolua_function(tolua_S,"new",tolua_zeus_CKickDirection_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CKickDirection_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CKickDirection_new00_local);
   tolua_function(tolua_S,"GenerateShootDir",tolua_zeus_CKickDirection_GenerateShootDir00);
   tolua_function(tolua_S,"getKickValid",tolua_zeus_CKickDirection_getKickValid00);
   tolua_function(tolua_S,"getCompensate",tolua_zeus_CKickDirection_getCompensate00);
   tolua_function(tolua_S,"getRawKickDir",tolua_zeus_CKickDirection_getRawKickDir00);
   tolua_function(tolua_S,"getCompensateDir",tolua_zeus_CKickDirection_getCompensateDir00);
   tolua_function(tolua_S,"getRealKickDir",tolua_zeus_CKickDirection_getRealKickDir00);
   tolua_function(tolua_S,"getIsKickValid",tolua_zeus_CKickDirection_getIsKickValid00);
   tolua_function(tolua_S,"getRawDir",tolua_zeus_CKickDirection_getRawDir00);
   tolua_function(tolua_S,"calCompensate",tolua_zeus_CKickDirection_calCompensate00);
   tolua_function(tolua_S,"calGussiFuncA",tolua_zeus_CKickDirection_calGussiFuncA00);
   tolua_function(tolua_S,"calGussiFuncB",tolua_zeus_CKickDirection_calGussiFuncB00);
   tolua_function(tolua_S,"getPointShootDir",tolua_zeus_CKickDirection_getPointShootDir00);
   tolua_function(tolua_S,"GetTheShootPoint",tolua_zeus_CKickDirection_GetTheShootPoint00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CKickStatus","CKickStatus","",tolua_collect_CKickStatus);
  #else
  tolua_cclass(tolua_S,"CKickStatus","CKickStatus","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CKickStatus");
   tolua_function(tolua_S,"new",tolua_zeus_CKickStatus_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CKickStatus_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CKickStatus_new00_local);
   tolua_function(tolua_S,"setKick",tolua_zeus_CKickStatus_setKick00);
   tolua_function(tolua_S,"setChipKick",tolua_zeus_CKickStatus_setChipKick00);
   tolua_function(tolua_S,"setBothKick",tolua_zeus_CKickStatus_setBothKick00);
   tolua_function(tolua_S,"setAllKick",tolua_zeus_CKickStatus_setAllKick00);
   tolua_function(tolua_S,"needKick",tolua_zeus_CKickStatus_needKick00);
   tolua_function(tolua_S,"getKickPower",tolua_zeus_CKickStatus_getKickPower00);
   tolua_function(tolua_S,"getChipKickDist",tolua_zeus_CKickStatus_getChipKickDist00);
   tolua_function(tolua_S,"getPassDist",tolua_zeus_CKickStatus_getPassDist00);
   tolua_function(tolua_S,"getKiker",tolua_zeus_CKickStatus_getKiker00);
   tolua_function(tolua_S,"clearAll",tolua_zeus_CKickStatus_clearAll00);
   tolua_function(tolua_S,"resetKick2ForceClose",tolua_zeus_CKickStatus_resetKick2ForceClose00);
   tolua_function(tolua_S,"updateForceClose",tolua_zeus_CKickStatus_updateForceClose00);
   tolua_function(tolua_S,"isForceClosed",tolua_zeus_CKickStatus_isForceClosed00);
   tolua_function(tolua_S,"getAdvancerPassTo",tolua_zeus_CKickStatus_getAdvancerPassTo00);
   tolua_function(tolua_S,"setAdvancerPassTo",tolua_zeus_CKickStatus_setAdvancerPassTo00);
   tolua_function(tolua_S,"resetAdvancerPassTo",tolua_zeus_CKickStatus_resetAdvancerPassTo00);
   tolua_function(tolua_S,"getNextAdvancer",tolua_zeus_CKickStatus_getNextAdvancer00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Matrix_double_","Matrix<double>","",tolua_collect_Matrix_double_);
  #else
  tolua_cclass(tolua_S,"Matrix_double_","Matrix<double>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Matrix_double_");
   tolua_function(tolua_S,"new",tolua_zeus_Matrix_double__new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_Matrix_double__new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_Matrix_double__new00_local);
   tolua_function(tolua_S,"new",tolua_zeus_Matrix_double__new01);
   tolua_function(tolua_S,"new_local",tolua_zeus_Matrix_double__new01_local);
   tolua_function(tolua_S,".call",tolua_zeus_Matrix_double__new01_local);
   tolua_function(tolua_S,"new",tolua_zeus_Matrix_double__new02);
   tolua_function(tolua_S,"new_local",tolua_zeus_Matrix_double__new02_local);
   tolua_function(tolua_S,".call",tolua_zeus_Matrix_double__new02_local);
   tolua_function(tolua_S,"delete",tolua_zeus_Matrix_double__delete00);
   tolua_function(tolua_S,"resize",tolua_zeus_Matrix_double__resize00);
   tolua_function(tolua_S,"identity",tolua_zeus_Matrix_double__identity00);
   tolua_function(tolua_S,"clear",tolua_zeus_Matrix_double__clear00);
   tolua_function(tolua_S,"setValue",tolua_zeus_Matrix_double__setValue00);
   tolua_function(tolua_S,"getValue",tolua_zeus_Matrix_double__getValue00);
   tolua_function(tolua_S,"trace",tolua_zeus_Matrix_double__trace00);
   tolua_function(tolua_S,"transpose",tolua_zeus_Matrix_double__transpose00);
   tolua_function(tolua_S,"product",tolua_zeus_Matrix_double__product00);
   tolua_function(tolua_S,"minsize",tolua_zeus_Matrix_double__minsize00);
   tolua_function(tolua_S,"columns",tolua_zeus_Matrix_double__columns00);
   tolua_function(tolua_S,"rows",tolua_zeus_Matrix_double__rows00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Munkres","Munkres","",NULL);
  tolua_beginmodule(tolua_S,"Munkres");
   tolua_function(tolua_S,"solve",tolua_zeus_Munkres_solve00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"NormalPlayUtils",0);
  tolua_beginmodule(tolua_S,"NormalPlayUtils");
   tolua_function(tolua_S,"isEnemyBlockShootLine",tolua_zeus_NormalPlayUtils_isEnemyBlockShootLine00);
   tolua_function(tolua_S,"isEnemyFrontToBall",tolua_zeus_NormalPlayUtils_isEnemyFrontToBall00);
   tolua_function(tolua_S,"isEnemyCloseToReceiver",tolua_zeus_NormalPlayUtils_isEnemyCloseToReceiver00);
   tolua_function(tolua_S,"isPosInSquareArea",tolua_zeus_NormalPlayUtils_isPosInSquareArea00);
   tolua_function(tolua_S,"isPosCloseBorder",tolua_zeus_NormalPlayUtils_isPosCloseBorder00);
   tolua_function(tolua_S,"isReceiverCloseToPassPos",tolua_zeus_NormalPlayUtils_isReceiverCloseToPassPos00);
   tolua_function(tolua_S,"getOurMostClosetoPos",tolua_zeus_NormalPlayUtils_getOurMostClosetoPos00);
   tolua_function(tolua_S,"getTheirMostClosetoPos",tolua_zeus_NormalPlayUtils_getTheirMostClosetoPos00);
   tolua_function(tolua_S,"ballMoveToOurDefendArea",tolua_zeus_NormalPlayUtils_ballMoveToOurDefendArea00);
   tolua_function(tolua_S,"noEnemyInPassLine",tolua_zeus_NormalPlayUtils_noEnemyInPassLine00);
   tolua_function(tolua_S,"canPassBetweenTwoPos",tolua_zeus_NormalPlayUtils_canPassBetweenTwoPos00);
   tolua_function(tolua_S,"generatePassPoint",tolua_zeus_NormalPlayUtils_generatePassPoint00);
   tolua_function(tolua_S,"generateKickAtEnemyDir",tolua_zeus_NormalPlayUtils_generateKickAtEnemyDir00);
   tolua_function(tolua_S,"patchForBestPlayer",tolua_zeus_NormalPlayUtils_patchForBestPlayer00);
   tolua_function(tolua_S,"generateTandemCond",tolua_zeus_NormalPlayUtils_generateTandemCond00);
   tolua_function(tolua_S,"antiNormalize",tolua_zeus_NormalPlayUtils_antiNormalize00);
   tolua_function(tolua_S,"faceTheirGoal",tolua_zeus_NormalPlayUtils_faceTheirGoal00);
   tolua_function(tolua_S,"getSuitSider",tolua_zeus_NormalPlayUtils_getSuitSider00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CSupportPos","CSupportPos","",tolua_collect_CSupportPos);
  #else
  tolua_cclass(tolua_S,"CSupportPos","CSupportPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CSupportPos");
   tolua_function(tolua_S,"new",tolua_zeus_CSupportPos_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CSupportPos_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CSupportPos_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CSupportPos_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CSupportPos_generatePos00);
   tolua_function(tolua_S,"getSupPos",tolua_zeus_CSupportPos_getSupPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SupportPosStruct2022","SupportPosStruct2022","",tolua_collect_SupportPosStruct2022);
  #else
  tolua_cclass(tolua_S,"SupportPosStruct2022","SupportPosStruct2022","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SupportPosStruct2022");
   tolua_variable(tolua_S,"leftSupportPos",tolua_get_SupportPosStruct2022_leftSupportPos,tolua_set_SupportPosStruct2022_leftSupportPos);
   tolua_variable(tolua_S,"rightSupportPos",tolua_get_SupportPosStruct2022_rightSupportPos,tolua_set_SupportPosStruct2022_rightSupportPos);
   tolua_function(tolua_S,"getLeftSupportPos",tolua_zeus_SupportPosStruct2022_getLeftSupportPos00);
   tolua_function(tolua_S,"getRightSupportPos",tolua_zeus_SupportPosStruct2022_getRightSupportPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CSupportPos2022","CSupportPos2022","",tolua_collect_CSupportPos2022);
  #else
  tolua_cclass(tolua_S,"CSupportPos2022","CSupportPos2022","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CSupportPos2022");
   tolua_function(tolua_S,"new",tolua_zeus_CSupportPos2022_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CSupportPos2022_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CSupportPos2022_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CSupportPos2022_delete00);
   tolua_function(tolua_S,"generateSupportPoint",tolua_zeus_CSupportPos2022_generateSupportPoint00);
   tolua_function(tolua_S,"getSupportPos",tolua_zeus_CSupportPos2022_getSupportPos00);
   tolua_function(tolua_S,"isEmpty",tolua_zeus_CSupportPos2022_isEmpty00);
   tolua_function(tolua_S,"getAreaScore",tolua_zeus_CSupportPos2022_getAreaScore00);
   tolua_function(tolua_S,"generateBestPoint",tolua_zeus_CSupportPos2022_generateBestPoint00);
   tolua_function(tolua_S,"calcMaxDist",tolua_zeus_CSupportPos2022_calcMaxDist00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTandemPos","CTandemPos","",tolua_collect_CTandemPos);
  #else
  tolua_cclass(tolua_S,"CTandemPos","CTandemPos","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTandemPos");
   tolua_function(tolua_S,"new",tolua_zeus_CTandemPos_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CTandemPos_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CTandemPos_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CTandemPos_delete00);
   tolua_function(tolua_S,"generatePos",tolua_zeus_CTandemPos_generatePos00);
   tolua_constant(tolua_S,"Special",CTandemPos::Special);
   tolua_constant(tolua_S,"BallMovingtoTheirHalf",CTandemPos::BallMovingtoTheirHalf);
   tolua_constant(tolua_S,"BallMovingtoOurHalf",CTandemPos::BallMovingtoOurHalf);
   tolua_constant(tolua_S,"OurChance",CTandemPos::OurChance);
   tolua_constant(tolua_S,"TheirChance",CTandemPos::TheirChance);
   tolua_function(tolua_S,"getTandemPos",tolua_zeus_CTandemPos_getTandemPos00);
   tolua_function(tolua_S,"analyzeSituation",tolua_zeus_CTandemPos_analyzeSituation00);
   tolua_function(tolua_S,"planAssistAttack",tolua_zeus_CTandemPos_planAssistAttack00);
   tolua_function(tolua_S,"planBlock",tolua_zeus_CTandemPos_planBlock00);
   tolua_function(tolua_S,"planAssistGetBall",tolua_zeus_CTandemPos_planAssistGetBall00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Utils",0);
  tolua_beginmodule(tolua_S,"Utils");
   tolua_function(tolua_S,"Normalize",tolua_zeus_Utils_Normalize00);
   tolua_function(tolua_S,"Polar2Vector",tolua_zeus_Utils_Polar2Vector00);
   tolua_function(tolua_S,"VectorDot",tolua_zeus_Utils_VectorDot00);
   tolua_function(tolua_S,"dirDiff",tolua_zeus_Utils_dirDiff00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween01);
   tolua_function(tolua_S,"AngleBetween",tolua_zeus_Utils_AngleBetween00);
   tolua_function(tolua_S,"InBetween",tolua_zeus_Utils_InBetween02);
   tolua_function(tolua_S,"MakeInField",tolua_zeus_Utils_MakeInField00);
   tolua_function(tolua_S,"OutOfField",tolua_zeus_Utils_OutOfField00);
   tolua_function(tolua_S,"IsInField",tolua_zeus_Utils_IsInField00);
   tolua_function(tolua_S,"MakeOutOfOurPenaltyArea",tolua_zeus_Utils_MakeOutOfOurPenaltyArea00);
   tolua_function(tolua_S,"MakeOutOfTheirPenaltyArea",tolua_zeus_Utils_MakeOutOfTheirPenaltyArea00);
   tolua_function(tolua_S,"MakeOutOfCircleAndInField",tolua_zeus_Utils_MakeOutOfCircleAndInField00);
   tolua_function(tolua_S,"MakeOutOfCircle",tolua_zeus_Utils_MakeOutOfCircle00);
   tolua_function(tolua_S,"MakeOutOfCircle",tolua_zeus_Utils_MakeOutOfCircle01);
   tolua_function(tolua_S,"MakeOutOfCircle",tolua_zeus_Utils_MakeOutOfCircle02);
   tolua_function(tolua_S,"MakeOutOfLongCircle",tolua_zeus_Utils_MakeOutOfLongCircle00);
   tolua_function(tolua_S,"MakeOutOfLongCircle",tolua_zeus_Utils_MakeOutOfLongCircle01);
   tolua_function(tolua_S,"MakeOutOfRectangle",tolua_zeus_Utils_MakeOutOfRectangle00);
   tolua_function(tolua_S,"InOurPenaltyArea",tolua_zeus_Utils_InOurPenaltyArea00);
   tolua_function(tolua_S,"InTheirPenaltyArea",tolua_zeus_Utils_InTheirPenaltyArea00);
   tolua_function(tolua_S,"PlayerNumValid",tolua_zeus_Utils_PlayerNumValid00);
   tolua_function(tolua_S,"GetOutSidePenaltyPos",tolua_zeus_Utils_GetOutSidePenaltyPos00);
   tolua_function(tolua_S,"GetOutSidePenaltyPos",tolua_zeus_Utils_GetOutSidePenaltyPos01);
   tolua_function(tolua_S,"GetOutTheirSidePenaltyPos",tolua_zeus_Utils_GetOutTheirSidePenaltyPos00);
   tolua_function(tolua_S,"GetInterPos",tolua_zeus_Utils_GetInterPos00);
   tolua_function(tolua_S,"GetInterPos",tolua_zeus_Utils_GetInterPos01);
   tolua_function(tolua_S,"GetTheirInterPos",tolua_zeus_Utils_GetTheirInterPos00);
   tolua_function(tolua_S,"SquareRootFloat",tolua_zeus_Utils_SquareRootFloat00);
   tolua_function(tolua_S,"canGo",tolua_zeus_Utils_canGo00);
   tolua_function(tolua_S,"dist_SegToPoint",tolua_zeus_Utils_dist_SegToPoint00);
   tolua_function(tolua_S,"MakeOutOfLongCircle",tolua_zeus_Utils_MakeOutOfLongCircle02);
   tolua_function(tolua_S,"point_OnLineOnSeg",tolua_zeus_Utils_point_OnLineOnSeg00);
   tolua_function(tolua_S,"min_Obs",tolua_zeus_Utils_min_Obs00);
   tolua_function(tolua_S,"max_Obs",tolua_zeus_Utils_max_Obs00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TranslationT","TranslationT","",tolua_collect_TranslationT);
  #else
  tolua_cclass(tolua_S,"TranslationT","TranslationT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TranslationT");
   tolua_function(tolua_S,"new",tolua_zeus_TranslationT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_TranslationT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_TranslationT_new00_local);
   tolua_function(tolua_S,"Pos",tolua_zeus_TranslationT_Pos00);
   tolua_function(tolua_S,"SetPos",tolua_zeus_TranslationT_SetPos00);
   tolua_function(tolua_S,"SetPos",tolua_zeus_TranslationT_SetPos01);
   tolua_function(tolua_S,"X",tolua_zeus_TranslationT_X00);
   tolua_function(tolua_S,"Y",tolua_zeus_TranslationT_Y00);
   tolua_function(tolua_S,"SetVel",tolua_zeus_TranslationT_SetVel00);
   tolua_function(tolua_S,"SetVel",tolua_zeus_TranslationT_SetVel01);
   tolua_function(tolua_S,"SetAcc",tolua_zeus_TranslationT_SetAcc00);
   tolua_function(tolua_S,"SetAcc",tolua_zeus_TranslationT_SetAcc01);
   tolua_function(tolua_S,"Vel",tolua_zeus_TranslationT_Vel00);
   tolua_function(tolua_S,"Acc",tolua_zeus_TranslationT_Acc00);
   tolua_function(tolua_S,"VelX",tolua_zeus_TranslationT_VelX00);
   tolua_function(tolua_S,"VelY",tolua_zeus_TranslationT_VelY00);
   tolua_function(tolua_S,"AccX",tolua_zeus_TranslationT_AccX00);
   tolua_function(tolua_S,"AccY",tolua_zeus_TranslationT_AccY00);
   tolua_function(tolua_S,"SetValid",tolua_zeus_TranslationT_SetValid00);
   tolua_function(tolua_S,"Valid",tolua_zeus_TranslationT_Valid00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ChipPosT","ChipPosT","",tolua_collect_ChipPosT);
  #else
  tolua_cclass(tolua_S,"ChipPosT","ChipPosT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ChipPosT");
   tolua_function(tolua_S,"new",tolua_zeus_ChipPosT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_ChipPosT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_ChipPosT_new00_local);
   tolua_function(tolua_S,"ChipPredictPos",tolua_zeus_ChipPosT_ChipPredictPos00);
   tolua_function(tolua_S,"SetChipPredict",tolua_zeus_ChipPosT_SetChipPredict00);
   tolua_function(tolua_S,"SetChipPredict",tolua_zeus_ChipPosT_SetChipPredict01);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RotationT","RotationT","",tolua_collect_RotationT);
  #else
  tolua_cclass(tolua_S,"RotationT","RotationT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RotationT");
   tolua_function(tolua_S,"new",tolua_zeus_RotationT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_RotationT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_RotationT_new00_local);
   tolua_function(tolua_S,"Dir",tolua_zeus_RotationT_Dir00);
   tolua_function(tolua_S,"SetDir",tolua_zeus_RotationT_SetDir00);
   tolua_function(tolua_S,"RotVel",tolua_zeus_RotationT_RotVel00);
   tolua_function(tolua_S,"SetRotVel",tolua_zeus_RotationT_SetRotVel00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerVisionT","PlayerVisionT","TranslationT",NULL);
  tolua_beginmodule(tolua_S,"PlayerVisionT");
   tolua_variable(tolua_S,"__RotationT__",tolua_get_PlayerVisionT___RotationT__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BallVisionT","BallVisionT","TranslationT",NULL);
  tolua_beginmodule(tolua_S,"BallVisionT");
   tolua_variable(tolua_S,"__ChipPosT__",tolua_get_BallVisionT___ChipPosT__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerCapabilityT","PlayerCapabilityT","",tolua_collect_PlayerCapabilityT);
  #else
  tolua_cclass(tolua_S,"PlayerCapabilityT","PlayerCapabilityT","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerCapabilityT");
   tolua_function(tolua_S,"new",tolua_zeus_PlayerCapabilityT_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_PlayerCapabilityT_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_PlayerCapabilityT_new00_local);
   tolua_variable(tolua_S,"maxAccel",tolua_get_PlayerCapabilityT_maxAccel,tolua_set_PlayerCapabilityT_maxAccel);
   tolua_variable(tolua_S,"maxSpeed",tolua_get_PlayerCapabilityT_maxSpeed,tolua_set_PlayerCapabilityT_maxSpeed);
   tolua_variable(tolua_S,"maxAngularAccel",tolua_get_PlayerCapabilityT_maxAngularAccel,tolua_set_PlayerCapabilityT_maxAngularAccel);
   tolua_variable(tolua_S,"maxAngularSpeed",tolua_get_PlayerCapabilityT_maxAngularSpeed,tolua_set_PlayerCapabilityT_maxAngularSpeed);
   tolua_variable(tolua_S,"maxDec",tolua_get_PlayerCapabilityT_maxDec,tolua_set_PlayerCapabilityT_maxDec);
   tolua_variable(tolua_S,"maxAngularDec",tolua_get_PlayerCapabilityT_maxAngularDec,tolua_set_PlayerCapabilityT_maxAngularDec);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ROBOTINFO","ROBOTINFO","",NULL);
  tolua_beginmodule(tolua_S,"ROBOTINFO");
   tolua_variable(tolua_S,"nRobotNum",tolua_get_ROBOTINFO_nRobotNum,tolua_set_ROBOTINFO_nRobotNum);
   tolua_variable(tolua_S,"bInfraredInfo",tolua_get_ROBOTINFO_bInfraredInfo,tolua_set_ROBOTINFO_bInfraredInfo);
   tolua_variable(tolua_S,"nKickInfo",tolua_get_ROBOTINFO_nKickInfo,tolua_set_ROBOTINFO_nKickInfo);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CWorldModel","CWorldModel","",tolua_collect_CWorldModel);
  #else
  tolua_cclass(tolua_S,"CWorldModel","CWorldModel","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CWorldModel");
   tolua_function(tolua_S,"new",tolua_zeus_CWorldModel_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CWorldModel_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CWorldModel_new00_local);
   tolua_function(tolua_S,"registerVision",tolua_zeus_CWorldModel_registerVision00);
   tolua_function(tolua_S,"registerOption",tolua_zeus_CWorldModel_registerOption00);
   tolua_function(tolua_S,"vision",tolua_zeus_CWorldModel_vision00);
   tolua_function(tolua_S,"option",tolua_zeus_CWorldModel_option00);
   tolua_function(tolua_S,"self2ball",tolua_zeus_CWorldModel_self2ball00);
   tolua_function(tolua_S,"self2ballDist",tolua_zeus_CWorldModel_self2ballDist00);
   tolua_function(tolua_S,"self2ballDir",tolua_zeus_CWorldModel_self2ballDir00);
   tolua_function(tolua_S,"CurrentRefereeMsg",tolua_zeus_CWorldModel_CurrentRefereeMsg00);
   tolua_function(tolua_S,"OurRobotNum",tolua_zeus_CWorldModel_OurRobotNum00);
   tolua_function(tolua_S,"IsBallKicked",tolua_zeus_CWorldModel_IsBallKicked00);
   tolua_function(tolua_S,"IsBestPlayerChanged",tolua_zeus_CWorldModel_IsBestPlayerChanged00);
   tolua_function(tolua_S,"CurrentBayes",tolua_zeus_CWorldModel_CurrentBayes00);
   tolua_function(tolua_S,"CanDefenceExit",tolua_zeus_CWorldModel_CanDefenceExit00);
   tolua_function(tolua_S,"timeToTarget",tolua_zeus_CWorldModel_timeToTarget00);
   tolua_function(tolua_S,"NeedExitAttackDef",tolua_zeus_CWorldModel_NeedExitAttackDef00);
   tolua_function(tolua_S,"ball2MarkingTouch",tolua_zeus_CWorldModel_ball2MarkingTouch00);
   tolua_function(tolua_S,"isMarkingFrontValid",tolua_zeus_CWorldModel_isMarkingFrontValid00);
   tolua_function(tolua_S,"getEnemyKickOffNum",tolua_zeus_CWorldModel_getEnemyKickOffNum00);
   tolua_function(tolua_S,"checkEnemyKickOffNumChanged",tolua_zeus_CWorldModel_checkEnemyKickOffNumChanged00);
   tolua_function(tolua_S,"getMarkingTouchArea",tolua_zeus_CWorldModel_getMarkingTouchArea00);
   tolua_function(tolua_S,"SPlayFSMSwitchClearAll",tolua_zeus_CWorldModel_SPlayFSMSwitchClearAll00);
   tolua_function(tolua_S,"KickDirArrived",tolua_zeus_CWorldModel_KickDirArrived00);
   tolua_function(tolua_S,"canProtectBall",tolua_zeus_CWorldModel_canProtectBall00);
   tolua_function(tolua_S,"canShootOnBallPos",tolua_zeus_CWorldModel_canShootOnBallPos00);
   tolua_function(tolua_S,"canPassOnBallPos",tolua_zeus_CWorldModel_canPassOnBallPos00);
   tolua_function(tolua_S,"canKickAtEnemy",tolua_zeus_CWorldModel_canKickAtEnemy00);
   tolua_function(tolua_S,"getBallStatus",tolua_zeus_CWorldModel_getBallStatus00);
   tolua_function(tolua_S,"generatePassPoint",tolua_zeus_CWorldModel_generatePassPoint00);
   tolua_function(tolua_S,"getTandemPos",tolua_zeus_CWorldModel_getTandemPos00);
   tolua_function(tolua_S,"getTandemDir",tolua_zeus_CWorldModel_getTandemDir00);
   tolua_function(tolua_S,"getBallToucher",tolua_zeus_CWorldModel_getBallToucher00);
   tolua_function(tolua_S,"IsOurBallByAutoReferee",tolua_zeus_CWorldModel_IsOurBallByAutoReferee00);
   tolua_function(tolua_S,"clearBallStateCouter",tolua_zeus_CWorldModel_clearBallStateCouter00);
   tolua_function(tolua_S,"getSuitSider",tolua_zeus_CWorldModel_getSuitSider00);
   tolua_function(tolua_S,"setBallHandler",tolua_zeus_CWorldModel_setBallHandler00);
   tolua_function(tolua_S,"isRecordRunPos",tolua_zeus_CWorldModel_isRecordRunPos00);
   tolua_function(tolua_S,"isBeingMarked",tolua_zeus_CWorldModel_isBeingMarked00);
   tolua_function(tolua_S,"isPassLineBlocked",tolua_zeus_CWorldModel_isPassLineBlocked00);
   tolua_function(tolua_S,"isShootLineBlocked",tolua_zeus_CWorldModel_isShootLineBlocked00);
   tolua_function(tolua_S,"isShootLineBlockedFromPoint",tolua_zeus_CWorldModel_isShootLineBlockedFromPoint00);
   tolua_function(tolua_S,"drawReflect",tolua_zeus_CWorldModel_drawReflect00);
   tolua_function(tolua_S,"getLeftReflectPos",tolua_zeus_CWorldModel_getLeftReflectPos00);
   tolua_function(tolua_S,"getRightReflectPos",tolua_zeus_CWorldModel_getRightReflectPos00);
   tolua_function(tolua_S,"getReflectPos",tolua_zeus_CWorldModel_getReflectPos00);
   tolua_function(tolua_S,"getReflectTouchPos",tolua_zeus_CWorldModel_getReflectTouchPos00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CRobotSensor","CRobotSensor","",tolua_collect_CRobotSensor);
  #else
  tolua_cclass(tolua_S,"CRobotSensor","CRobotSensor","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CRobotSensor");
   tolua_function(tolua_S,"new",tolua_zeus_CRobotSensor_new00);
   tolua_function(tolua_S,"new_local",tolua_zeus_CRobotSensor_new00_local);
   tolua_function(tolua_S,".call",tolua_zeus_CRobotSensor_new00_local);
   tolua_function(tolua_S,"delete",tolua_zeus_CRobotSensor_delete00);
   tolua_function(tolua_S,"Update",tolua_zeus_CRobotSensor_Update00);
   tolua_function(tolua_S,"IsInfoValid",tolua_zeus_CRobotSensor_IsInfoValid00);
   tolua_function(tolua_S,"IsInfraredOn",tolua_zeus_CRobotSensor_IsInfraredOn00);
   tolua_function(tolua_S,"ResetInraredOn",tolua_zeus_CRobotSensor_ResetInraredOn00);
   tolua_function(tolua_S,"IsKickerOn",tolua_zeus_CRobotSensor_IsKickerOn00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_zeus (lua_State* tolua_S) {
 return tolua_zeus_open(tolua_S);
};
#endif

