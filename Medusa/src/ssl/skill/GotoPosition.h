#ifndef _GOTO_POSITION_V2_H_
#define _GOTO_POSITION_V2_H_
#include <skill/PlayerTask.h>
#include <geometry.h>
/************************************************************************/
/*                     CGotoPosition / ≈‹Œª                           */
/************************************************************************/

struct PlayerCapabilityT;

class CGotoPosition : public CPlayerTask {
public:
	CGotoPosition();
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }

protected:
	virtual void toStream(std::ostream& os) const;
	PlayerCapabilityT setCapability(const CVisionModule* pVision);

private:
	CGeoPoint _target;
	int playerFlag;
};

#endif
