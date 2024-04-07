#include "ChaseToPenalty.h"
#include ""
#include ""
#include ""
#include ""
#include ""
#include ""
#include ""

using namespace Param;
namespace
{

}

CChaseToPenalty::CChaseToPenalty()
{

}

void CChaseToPenalty::plan(const CVisionModule* pVision)
{

}

CPlayerCommand* CChaseToPenalty::execute(const CVisionModule* pVision)
{
	if( subTask() ){
		return subTask()->execute(pVision);
	}
	if( _directCommand != NULL ){
		return _directCommand;
	}
	return NULL;
}