#include "RRTPathPlannerNew.h"
#include <time.h>
#include <cstdlib>
#include <omp.h>
namespace {
const double PROB_ADD_PATH_POINTS_TO_WAY_POINTS = 0.1;

const size_t MAX_SIZE_NUM = size_t(-1);

inline int intTypeRandomZeroToRandMax() {
    return rand();
}

inline double doubleTypeRandomZeroToOne() {
    return double(1.0 * intTypeRandomZeroToRandMax() / RAND_MAX);
}

inline double doubleTypeRandomMinusOneToOne() {
    return (2 * doubleTypeRandomZeroToOne() - 1);
}
}

KDTreeNew CRRTPathPlannerNew::_searchTree = KDTreeNew();
KDTreeNew CRRTPathPlannerNew::_searchTreeRev = KDTreeNew();

CRRTPathPlannerNew::CRRTPathPlannerNew() {
    _inited = false;
    srand(time(0));
}

inline stateNew CRRTPathPlannerNew::generateRandomState() {
    stateNew randomState;
    /*_searchInCircle = false;*/
    if(!_searchInCircle) {
        double factor1 = doubleTypeRandomMinusOneToOne(), factor2 = doubleTypeRandomMinusOneToOne();
        /*randomState.pos = CGeoPoint((Param::Field::PITCH_LENGTH / 2.0 + Param::Field::GOAL_DEPTH) * factor1, (Param::Field::PITCH_LENGTH / 2.0 + Param::Field::GOAL_DEPTH) * factor2);*/
        randomState.pos = CGeoPoint((Param::Field::PITCH_LENGTH / 2.0) * factor1, (Param::Field::PITCH_WIDTH / 2.0) * factor2);  // from chen siyuan，现在限制范围大小即为场地大小
    } else {
        double r = doubleTypeRandomZeroToOne() * _circleRadius;
        double angle = doubleTypeRandomMinusOneToOne() * Param::Math::PI;
        randomState.pos = CGeoPoint(_circleCenter.x() + r * cos(angle), _circleCenter.y() + r * sin(angle));
    }
    randomState.orient = 0.0;
    randomState.rotVel = 0.0;
    randomState.vel = CVector(0.0, 0.0);
    /*std::cout << "x:" << randomState.pos.x() << "\ty:" << randomState.pos.y() << endl;*/
    return randomState;
}

inline stateNew CRRTPathPlannerNew::generateNodeStateAccordingToProb(targetType &tType) {
    double randomNum = doubleTypeRandomZeroToOne();
    if(randomNum < _targetChooseProb) {
        tType = finalTarget;
        return _target;
    } else if(randomNum < _targetChooseProb + _wayPointsChooseProb) {
        tType = wayPoint;
        int indexOfWayPoint = intTypeRandomZeroToRandMax() % _maxWayPointsNum;
        return _wayPoints[indexOfWayPoint];
    } else {
        tType = randomState;
        return generateRandomState();
    }
}

inline stateNew CRRTPathPlannerNew::generateNodeStateAccordingToProbRev(targetType &tType) {
    double randomNum = doubleTypeRandomZeroToOne();
    if(randomNum < _targetChooseProb) {
        tType = finalTarget;
        return _start;
    } else if(randomNum < _targetChooseProb + _wayPointsChooseProb) {
        tType = wayPoint;
        int indexOfWayPoint = intTypeRandomZeroToRandMax() % _maxWayPointsNum;
        return _wayPointsRev[indexOfWayPoint];
    } else {
        tType = randomState;
        return generateRandomState();
    }
}

inline void CRRTPathPlannerNew::addNode(stateNew node, size_t parent) {

    if(_nodes.size() >= _maxNodesNum) return;
    _searchTree.addNode(node, _nodes.size());
    _nodes.push_back(pair < stateNew, int > (node, parent));
}

inline void CRRTPathPlannerNew::addNodeRev(stateNew node, size_t parent) {

    if(_nodesRev.size() >= _maxNodesNum) return;
    _searchTreeRev.addNode(node, _nodesRev.size());
    _nodesRev.push_back(pair < stateNew, size_t > (node, parent));

}

inline int CRRTPathPlannerNew::findParent(stateNew nodeToAdd) {
    double bestDist = 0;
    int nearestIdx = _searchTree.indexOfNearestNode(bestDist, nodeToAdd.pos);
    return nearestIdx;
}

inline int CRRTPathPlannerNew::findParentRev(stateNew nodeToAdd) {
    double bestDist = 0;
    int nearestIdx = _searchTreeRev.indexOfNearestNode(bestDist, nodeToAdd.pos);
    return nearestIdx;
}

inline void CRRTPathPlannerNew::extend(size_t parent, stateNew nodeToAdd) {
    stateNew newNode;
    CVector step;
    newNode = _nodes[parent].first;
    step = nodeToAdd.pos - _nodes[parent].first.pos;
    step = step / step.mod() * _stepSize;
    newNode.pos = _nodes[parent].first.pos + step;

    if(_obs->check(newNode.pos, _nodes[parent].first.pos) && _searchTree.nodeInTree(newNode))
        addNode(newNode, parent);
    return;
}

inline void CRRTPathPlannerNew::extendRev(size_t parent, stateNew nodeToAdd) {
    stateNew newNode;
    CVector step;

    newNode = _nodesRev[parent].first;
    step = nodeToAdd.pos - _nodesRev[parent].first.pos;
    step = step / step.mod() * _stepSize;
    newNode.pos = _nodesRev[parent].first.pos + step;
    if(_obs->check(newNode.pos, _nodesRev[parent].first.pos) && _searchTreeRev.nodeInTree(newNode))
        addNodeRev(newNode, parent);
    return;
}

/*
By Tan Yuhong
这段代码是一个RRT（快速随机树）路径规划器的初始化函数。这个函数的参数包括：

maxNodesNum：规划器最多能生成的节点数。
maxWayPointsNum：规划器最多能生成的路径点数。
maxPathPointsNum：规划器最多能生成的路径点数（包括从起点到终点的路径）。
targetChooseProb：在规划器中选择目标点的概率。
wayPointsChooseProb：在规划器中选择路径点的概率。
stepSize：扩展树时每个步骤的长度。
planInOurField：一个布尔值，指示规划器是否应该在场地内规划。
searchInCircle：一个布尔值，指示规划器是否应该在一个圆形搜索区域内进行规划。
circleCenter：如果在圆形搜索区域内进行规划，圆心的位置。
circleRadius：如果在圆形搜索区域内进行规划，圆的半径。
函数首先将_inited标志设置为true，表示规划器已经初始化。
然后，它将参数值存储在规划器的成员变量中。接下来，它清空并分配内存用于存储路径点、节点和路径的向量。
它还计算了用于查找最近节点的距离_findDist，它是步长的一半。

函数接下来根据planInOurField的值设置搜索区域的边界。
如果planInOurField为true，则搜索区域边界将被设置为场地内的一侧。
否则，搜索区域的边界将被设置为整个场地。这个操作的目的是缩小树的搜索范围，避免规划器规划出界。

最后，函数生成随机的路径点和它们的反向路径点，并初始化两个搜索树，
一个用于正向搜索，另一个用于反向搜索。搜索树的边界是根据搜索区域的边界计算出来的。
*/
void CRRTPathPlannerNew::initPlanner(int maxNodesNum, int maxWayPointsNum, int maxPathPointsNum,double targetChooseProb, double wayPointsChooseProb, double stepSize, bool planInOurField, bool searchInCircle, CGeoPoint circleCenter, double circleRadius) {
    this->_inited = true;
    this->_maxNodesNum = maxNodesNum;
    this->_maxWayPointsNum = maxWayPointsNum;
    this->_maxPathPointsNum = maxPathPointsNum;
    this->_targetChooseProb = targetChooseProb;
    this->_wayPointsChooseProb = wayPointsChooseProb;
    this->_stepSize = stepSize;
    this->_findDist = stepSize / 2.0;
    this->_pathPointsAddToWayPointsProb = PROB_ADD_PATH_POINTS_TO_WAY_POINTS;


    this->_wayPoints.clear();
    this->_wayPoints.reserve(_maxWayPointsNum);
    this->_wayPointsRev.clear();
    this->_wayPointsRev.reserve(_maxWayPointsNum);
    this->_nodes.clear();
    this->_nodes.reserve(_maxNodesNum);
    this->_nodesRev.clear();
    this->_nodesRev.reserve(_maxNodesNum);
    this->_pathPoints.clear();
    this->_pathPoints.reserve(_maxPathPointsNum);
    this->_pathPointsRev.clear();
    this->_pathPointsRev.reserve(_maxPathPointsNum);

    /* from chen siyuan */
    /* 将RRT搜索范围缩小，避免规划出界 */
    if (planInOurField) {
        this->_searchAreaLeftBound = -Param::Field::PITCH_LENGTH / 2 - Param::Field::FIELD_WALL_DIST;
        this->_searchAreaRightBound = -Param::Vehicle::V2::PLAYER_SIZE;
        this->_searchAreaLowerBound = -Param::Field::PITCH_WIDTH / 2 - Param::Field::FIELD_WALL_DIST;
        this->_searchAreaUpperBound = Param::Field::PITCH_WIDTH / 2 + Param::Field::FIELD_WALL_DIST;
    }
    else {
        this->_searchAreaLeftBound = -Param::Field::PITCH_LENGTH / 2 - Param::Field::FIELD_WALL_DIST;
        this->_searchAreaRightBound = Param::Field::PITCH_LENGTH / 2 + Param::Field::FIELD_WALL_DIST;
        this->_searchAreaLowerBound = -Param::Field::PITCH_WIDTH / 2 - Param::Field::FIELD_WALL_DIST;
        this->_searchAreaUpperBound = Param::Field::PITCH_WIDTH / 2 + Param::Field::FIELD_WALL_DIST;
    }


    this->_searchInCircle = searchInCircle;
    this->_circleCenter = circleCenter;
    this->_circleRadius = circleRadius;
    for(int i = 0; i < maxWayPointsNum; i++) {
        this->_wayPoints.push_back(generateRandomState());
        this->_wayPointsRev.push_back(this->_wayPoints.back());
    }
    CGeoPoint lowerLeftBound, upperRightBound;

    lowerLeftBound = CGeoPoint(_searchAreaLeftBound, _searchAreaLowerBound);
    upperRightBound = CGeoPoint(_searchAreaRightBound, _searchAreaUpperBound);

    this->_searchTree.initTree(lowerLeftBound, upperRightBound, 4, 5);
    this->_searchTreeRev.initTree(lowerLeftBound, upperRightBound, 4, 5);
}

void CRRTPathPlannerNew::planPath(ObstaclesNew *obs, stateNew start, stateNew target) {
    this->_obs = obs;
    this->_start = start;
    this->_target = target;

    ///对输入参数值的有效性判断//
    size_t nearestNode = 0, nearestNodeRev = 0;
    vector < size_t > nearestIdxToTree, nearestIdxToTreeRev;
    _pathPoints.clear();
    _pathPointsRev.clear();

    ///can run directly
    if(obs->check(_start.pos, _target.pos)) {
        _pathPoints.push_back(_start);
        _pathPoints.push_back(_target);
    }
    else {
        #pragma omp parallel sections
        {
            #pragma omp section
                searchTreeGrow(nearestNode);
            #pragma omp section
                searchTreeRevGrow(nearestNodeRev);
        }
        #pragma omp barrier

        findBackTrackingIdx(nearestIdxToTree, nearestIdxToTreeRev);
        vector < backTrackIdx > lengthAndIdx;
        if(nearestIdxToTree.empty() || nearestIdxToTreeRev.empty()) {
            lengthAndIdx.resize(1);
            backTracking(nearestNode, 0, nearestNodeRev, 0);
        }
        else {
            lengthAndIdx.resize(nearestIdxToTree.size());

#pragma omp parallel for num_threads(4)
            for(int i = 0; i < nearestIdxToTree.size(); i++) {
                backTracking(nearestNode, nearestIdxToTree[i], nearestNodeRev, nearestIdxToTreeRev[i], i, lengthAndIdx);
            }
#pragma omp barrier
            sort(lengthAndIdx.begin(), lengthAndIdx.end());
            backTracking(nearestNode, nearestIdxToTree[lengthAndIdx.front().i], nearestNodeRev, nearestIdxToTreeRev[lengthAndIdx.front().i]);
        }
    }
    for (int i = 1; i < _pathPoints.size(); i++) {
        if (_pathPoints[i].pos.dist(_pathPoints[i - 1].pos) < 1e-8)
            cout << "Oh shit!!! Same pathPoints in RRT!!!! ---RRTPathPlannerNew.cpp" << endl;
    }
    addToWayPoints();
    addToWayPointsRev();
    return;
}

void CRRTPathPlannerNew::addToWayPoints() {
    if(_pathPoints.size() > 2) { //succeed to plan
        for(int i = 1; i < _pathPoints.size() - 1; i++) {
            if(doubleTypeRandomZeroToOne() > _pathPointsAddToWayPointsProb) continue;
            int indexOfWayPoint = intTypeRandomZeroToRandMax() % _maxWayPointsNum;
            _wayPoints[indexOfWayPoint] = _pathPoints[i];
        }
    } else {
        for(int i = 0; i < _wayPoints.size(); i++) {
            if(doubleTypeRandomZeroToOne() > _pathPointsAddToWayPointsProb) continue;
            _wayPoints[i] = generateRandomState();
        }
    }
    return;
}

void CRRTPathPlannerNew::addToWayPointsRev() {
    if(_pathPointsRev.size() > 1) {
        for(int i = 0; i < _pathPointsRev.size() - 1; i++) {
            if(doubleTypeRandomZeroToOne() > _pathPointsAddToWayPointsProb) continue;
            int indexOfWayPoint = intTypeRandomZeroToRandMax() % _maxWayPointsNum;
            _wayPointsRev[indexOfWayPoint] = _pathPointsRev[i];
        }
    } else {
        for(int i = 0; i < _wayPointsRev.size(); i++) {
            if(doubleTypeRandomZeroToOne() > _pathPointsAddToWayPointsProb) continue;
            _wayPointsRev[i] = generateRandomState();
        }
    }
}

void CRRTPathPlannerNew::searchTreeGrow(size_t& nearestIdx) {
    stateNew  nodeToAdd;
    size_t nearestNodeToNewNode = 0, nearestNode = 0;
    double nearestDist = 1e8;
    targetType tType;
    _nodes.clear();
    _searchTree.clearTree();
    addNode(_start, MAX_SIZE_NUM);

    for(int i = 0; i < _maxNodesNum; i++) {
        nodeToAdd = generateNodeStateAccordingToProb(tType);
        nearestNodeToNewNode = (tType == finalTarget ? nearestNode : findParent(nodeToAdd));
        if(nearestNodeToNewNode < 0 || nearestNodeToNewNode >= _nodes.size())
            cout << "BUG!!! Error nearest distance index!!! ---RRTPathPlannerNew" << endl;
        extend(nearestNodeToNewNode, nodeToAdd);
        double tempDist = _nodes.back().first.pos.dist(_target.pos);
        if(_nodes.size() == 1 && !_obs->check(_start.pos, _target.pos))
            tempDist = 1e9;
        if(tempDist < nearestDist) {
            nearestNode = _nodes.size() - 1;
            nearestDist = tempDist;
        }
    }
    nearestIdx = nearestNode;
    return;
}

void CRRTPathPlannerNew::searchTreeRevGrow(size_t& nearestIdx) {
    stateNew  nodeToAdd;
    int nearestNodeToNewNode = 0, nearestNodeRev = 0;
    double nearestDistRev = 1e8;
    targetType tType;
    _nodesRev.clear();
    _searchTreeRev.clearTree();
    addNodeRev(_target, MAX_SIZE_NUM);
    for(int i = 0; i < _maxNodesNum; i++) {
        nodeToAdd = generateNodeStateAccordingToProbRev(tType);
        nearestNodeToNewNode = (tType == finalTarget ? nearestNodeRev : findParentRev(nodeToAdd));
        if(nearestNodeToNewNode < 0 || nearestNodeToNewNode >= _nodesRev.size())
            cout << "BUG!!! Error nearest distance index when reverse!!! ---RRTPathPlannerNew" << endl;
        extendRev(nearestNodeToNewNode, nodeToAdd);
        double tempDistRev = _nodesRev.back().first.pos.dist(_start.pos);
        if(tempDistRev < nearestDistRev) {
            nearestNodeRev = _nodesRev.size() - 1;
            nearestDistRev = tempDistRev;
        }
    }
    nearestIdx = nearestNodeRev;
    return;
}

void CRRTPathPlannerNew::findBackTrackingIdx(vector < size_t >& idx, vector < size_t > &idxRev) {
    if(_nodes.empty() || _nodesRev.empty()) {
        cout << "Oh shit!!! Search tree is empty!!! ---RRTPathPlannerNew" << endl;
        return;
    }
    idx.clear();
    idxRev.clear();
    int tempIdxRev = 0;
    double tempDistBetweenTree = 0.0;
    for(int tempIdx = 0; tempIdx < _nodes.size(); tempIdx++) {
        tempIdxRev =  _searchTreeRev.indexOfNearestNode(tempDistBetweenTree, _nodes[tempIdx].first.pos);
        if(tempDistBetweenTree < _findDist) {
            idx.push_back(tempIdx);
            idxRev.push_back(tempIdxRev);
        }
    }
    return;
}

void CRRTPathPlannerNew::backTracking(size_t nearestNode, size_t nearestIdxToTree, size_t nearestNodeRev, size_t nearestIdxToTreeRev, int idx, vector < backTrackIdx >& lengthAndIdx) {
    size_t searchTreeIterator = MAX_SIZE_NUM;
    double totalLength = 0.0;

    int frontItor = nearestIdxToTree > 0 ? nearestIdxToTree : nearestNode;
    if(_nodes[nearestNode].first.pos.dist(_start.pos) > 1e-8)
        for(searchTreeIterator = frontItor; searchTreeIterator > 0; searchTreeIterator = _nodes[searchTreeIterator].second)
            totalLength += _nodes[searchTreeIterator].first.pos.dist(_nodes[_nodes[searchTreeIterator].second].first.pos);

    if(_nodesRev[nearestNodeRev].first.pos.dist(_target.pos) > 1e-8 && nearestIdxToTreeRev > 0) {
        for(searchTreeIterator = nearestIdxToTreeRev; searchTreeIterator > 0; searchTreeIterator = _nodesRev[searchTreeIterator].second)
            totalLength += _nodesRev[searchTreeIterator].first.pos.dist(_nodesRev[_nodesRev[searchTreeIterator].second].first.pos);
    }

    lengthAndIdx[idx].i = idx;
    lengthAndIdx[idx].length = totalLength;
}

void CRRTPathPlannerNew::backTracking(size_t nearestNode, size_t nearestIdxToTree, size_t nearestNodeRev, size_t nearestIdxToTreeRev) {
    size_t searchTreeIterator = MAX_SIZE_NUM;

    _pathPoints.push_back(_start);
    int frontItor = nearestIdxToTree > 0 ? nearestIdxToTree : nearestNode;
    if(_nodes[nearestNode].first.pos.dist(_start.pos) > 1e-8) {
        while(searchTreeIterator != frontItor) {
            for(searchTreeIterator = frontItor; searchTreeIterator < MAX_SIZE_NUM && !_obs->check(_pathPoints.back().pos, _nodes[searchTreeIterator].first.pos); searchTreeIterator = _nodes[searchTreeIterator].second);
            _pathPoints.push_back(_nodes[searchTreeIterator].first);
        }
    }

    if(_nodesRev[nearestNodeRev].first.pos.dist(_target.pos) > 1e-8 && nearestIdxToTreeRev > 0) {
        CGeoPoint nextPos = _nodesRev[nearestIdxToTreeRev].first.pos;
        searchTreeIterator = nearestIdxToTreeRev;
        if(_pathPoints.size() > 1 && _obs->check(_pathPoints.back().pos, _nodesRev[searchTreeIterator].first.pos) && _obs->check(_pathPoints[_pathPoints.size() - 2].pos, _nodesRev[searchTreeIterator].first.pos))
            _pathPoints.pop_back();

        while(searchTreeIterator > 0) {
            if(!_pathPoints.empty() && !_obs->check(nextPos, _pathPoints.back().pos)) {
                //cout << "Oh shit!!! Error node in tree! ---RRTPathPlannerNew " << (nearestIdxToTreeRev - searchTreeIterator) <<  nextPos << " " << _pathPoints.back().pos << endl;
                break;
            }
            while(searchTreeIterator > 0 && _obs->check(nextPos, _pathPoints.back().pos)) {
                searchTreeIterator = _nodesRev[searchTreeIterator].second;
                if(searchTreeIterator <= 0) break;
                nextPos = _nodesRev[_nodesRev[searchTreeIterator].second].first.pos;
            }
            _pathPoints.push_back(_nodesRev[searchTreeIterator].first);
            _pathPointsRev.push_back(_nodesRev[searchTreeIterator].first);
            if(searchTreeIterator <= 0) break;
            if(_nodesRev[searchTreeIterator].second < 0 || _nodesRev[searchTreeIterator].second > _nodesRev.size() - 1) {
                cout << "BUG!!! Error index when reverse!!! ---RRTPathPlannerNew" << endl;
            }
            nextPos = _nodesRev[_nodesRev[searchTreeIterator].second].first.pos;
        }
    }
    if(_obs->check(_target.pos, _pathPoints.back().pos))
        _pathPoints.pop_back();
    _pathPoints.push_back(_target);

}
