## 球预测模型

- loan_model:最早的模型，xy方向不独立训练，小速度效果极差
- loan_model_x/y:xy方向开始独立训练，kick_vx/vy用踢出的第一时刻速度
- loan_model_x_20/y_20:预测20帧后位置
- loan_model_x_50/y_50:预测50帧后位置
- loan_model_x_20_fixY/y_20_fixY:添加y方向大速度，降低y方向误差
- model_x_20_fixY_kick/y_20_fixY_kick:用踢出第7~10帧的平均速度作为踢球初速
