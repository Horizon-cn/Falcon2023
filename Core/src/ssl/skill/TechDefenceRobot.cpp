
CTechDefenceRobot::CTechDefence()
{

}
void CTechDefenceRobot::plan(const CVisionModule* pVision)
{
	int runner = task().executor;
	const BallVisionT& ball = pVision->Ball();
	TaskT Go_task(task());
	Go_task.executor=runner;
	CGeoPoint POS(50,50);
	if (ball.X()>0) POS.setX(-50),Go_task.player.pos=POS;
	if (ball.X()<0) POS.setX(50),Go_task.player.pos=POS;
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(Go_task));
	CStatedTask::plan(pVision);

}
CPlayerCommand* CTechDefence::execute(const CVisionModule* pVision)
{
	if (subTask()){
		return subTask()->execute(pVision);
	}
	return NULL;
}