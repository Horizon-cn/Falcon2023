import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import joblib
from sklearn.multioutput import MultiOutputRegressor
import lightgbm as lgb
import datetime

TRAIN_PATH = ['BallSpeed2023-03-05-13-24-08.txt', 'BallSpeed2023-03-05-23-40-30.txt', 'BallSpeed2023-03-06-11-39-31.txt']
TEST_PATH = ['BallSpeed2023-03-05-21-01-03.txt']  # 'TestTimeCost.txt'
MODEL = ['model_x_20_fixY_kick_avg10.pkl', 'loan_model_y_20_fixY_avg10.pkl', 'model_x_20_fixY_kick.pkl', 'loan_model_y_20_fixY.pkl',
         'loan_model_x_20_fixY.pkl', 'model_y_20_fixY_kick.pkl', 'loan_model_x_20.pkl', 'loan_model_y_20.pkl', 'loan_model_x.pkl',
         'loan_model_y.pkl']
predicted_time = 20
TRAIN_VX = True
TRAIN_VY = True

def process_train_file(PATH, limit):
    data = {'time': [], 'vx': [], 'kick_vx': [], 'vy': [], 'kick_vy': [], 'x': [], 'y': []}
    train_data_vx = pd.DataFrame()
    train_data_vy = pd.DataFrame()
    for path in PATH:
        first_time = True
        last_kicker = 0
        timeStamp = 0
        with open(path, 'r', encoding='utf-8') as infile:
            for line in infile:
                if first_time:  # 避开第一行
                    first_time = False
                    continue
                data_line = line.strip("\n").split()  # 去除首尾换行符，并按空格划分
                if last_kicker != data_line[0]:
                    train_data_vx, train_data_vy = process_dataFrame(data, limit, train_data_vx, train_data_vy)
                    # print(train_data)
                    data = {'time': [], 'vx': [], 'kick_vx': [], 'vy': [], 'kick_vy': [], 'x': [], 'y': []}
                    last_kicker = data_line[0]
                    timeStamp = 0
                #     kick_vx = data_line[3]
                    kick_vy = data_line[4]
                else:
                    timeStamp = timeStamp + 1
                data['time'].append(timeStamp)
                if timeStamp >= 10:
                    kick_vx = np.mean(data['kick_vx'][6:9])
                #     kick_vy = np.mean(data['kick_vy'][6:9])
                else:
                      kick_vx = data_line[3]
                #      kick_vy = data_line[4]
                data['kick_vx'].append(float(kick_vx))
                data['kick_vy'].append(float(kick_vy))
                data['vx'].append(float(data_line[3]))
                data['vy'].append(float(data_line[4]))
                data['x'].append(float(data_line[5]))
                data['y'].append(float(data_line[6]))
            train_data_vx, train_data_vy = process_dataFrame(data, limit, train_data_vx, train_data_vy)
    return train_data_vx, train_data_vy

def process_dataFrame(data, limit, train_data_vx, train_data_vy):
    temp_train_data = pd.DataFrame(data)
    for i in range(1, 11, 1):
        temp_train_data['time-{}'.format(i)] = temp_train_data['time'].shift(i)
        temp_train_data['vx-{}'.format(i)] = temp_train_data['vx'].shift(i)
        temp_train_data['vy-{}'.format(i)] = temp_train_data['vy'].shift(i)
    temp_train_data['time+'] = temp_train_data['time'].shift(-predicted_time)
    temp_train_data['x+'] = temp_train_data['x'].shift(-predicted_time)
    temp_train_data['y+'] = temp_train_data['y'].shift(-predicted_time)
    for i in range(1, 11, 1):
        temp_train_data = temp_train_data[~temp_train_data['time-{}'.format(i)].isnull()]
        temp_train_data = temp_train_data[~temp_train_data['vx-{}'.format(i)].isnull()]
        temp_train_data = temp_train_data[~temp_train_data['vy-{}'.format(i)].isnull()]
    temp_train_data = temp_train_data[~temp_train_data['x+'].isnull()]
    temp_train_data = temp_train_data[~temp_train_data['y+'].isnull()]
    temp_train_data = temp_train_data[~temp_train_data['time+'].isnull()]
    temp_avg_vx = temp_train_data['vx-1']
    temp_avg_vy = temp_train_data['vy-1']
    temp_avg_delta_vx = temp_train_data['vx'] - temp_train_data['vx-1']
    temp_avg_delta_vy = temp_train_data['vy'] - temp_train_data['vy-1']
    for i in range(2, 11, 1):
        temp_avg_vx = temp_avg_vx + temp_train_data['vx-{}'.format(i)]
        temp_avg_vy = temp_avg_vy + temp_train_data['vy-{}'.format(i)]
        temp_avg_delta_vx = temp_avg_delta_vx + temp_train_data['vx-{}'.format(i-1)] - temp_train_data['vx-{}'.format(i)]
        temp_avg_delta_vy = temp_avg_delta_vy + temp_train_data['vy-{}'.format(i-1)] - temp_train_data['vy-{}'.format(i)]
    temp_train_data['avg_vx'] = temp_avg_vx * 0.1
    temp_train_data['avg_vy'] = temp_avg_vy * 0.1
    temp_train_data['avg_delta_vx'] = temp_avg_delta_vx * 0.1
    temp_train_data['avg_delta_vy'] = temp_avg_delta_vy * 0.1
    temp_train_data['delta_x+'] = temp_train_data['x+'] - temp_train_data['x']
    temp_train_data['delta_y+'] = temp_train_data['y+'] - temp_train_data['y']
    temp_train_data_vx = temp_train_data
    temp_train_data_vy = temp_train_data
    if limit:
        index = 0
        for vx in temp_train_data['vx']:
            if np.fabs(vx) < 0:  # 50:
                temp_train_data_vx = temp_train_data[0:index]
                break
            index = index + 1
        index = 0
        for vy in temp_train_data['vy']:
            if np.fabs(vy) < 0:  # 50:
                temp_train_data_vy = temp_train_data[0:index]
                break
            index = index + 1
        temp_train_data_vx = temp_train_data_vx.reset_index(drop=True)
        temp_train_data_vy = temp_train_data_vy.reset_index(drop=True)
        if train_data_vx.empty:
            train_data_vx = temp_train_data_vx
            train_data_vy = temp_train_data_vy
        else:
            train_data_vx = pd.concat([train_data_vx, temp_train_data_vx], ignore_index=True)
            train_data_vx = train_data_vx.reset_index(drop=True)
            train_data_vy = pd.concat([train_data_vy, temp_train_data_vy], ignore_index=True)
            train_data_vy = train_data_vy.reset_index(drop=True)
    else:
        index = 0
        for vx in temp_train_data['vx']:
            if np.fabs(vx) < 0:  # 25:
                temp_train_data_vx = temp_train_data[0:index]
                break
            index = index + 1
        temp_train_data_vx = temp_train_data.reset_index(drop=True)
        if train_data_vx.empty:
            train_data_vx = temp_train_data_vx
        else:
            train_data_vx = pd.concat([train_data_vx, temp_train_data_vx], ignore_index=True)
            train_data_vx = train_data_vx.reset_index(drop=True)
    return train_data_vx, train_data_vy

train_data_vx, train_data_vy = process_train_file(TRAIN_PATH, True)
test_data, _ = process_train_file(TEST_PATH, False)

# 写入txt
def write_to_txt(filename, data):
    file = open(filename, mode='w')
    for i in range(0, data.shape[0], 1):
        file.writelines([str(data['time'][i]), ' ', str(data['kick_vx'][i]), ' ', str(data['vx'][i]), ' ',
                         str(data['avg_vx'][i]), ' ', str(data['avg_delta_vx'][i]), ' ', str(data['delta_x+'][i]), '\n'])
    file.close()

# write_to_txt('train_vx.txt', train_data_vx)
# write_to_txt('test_vx.txt', test_data)
# train_data_vx1 = train_data_vx[['time', 'kick_vx', 'vx', 'avg_vx', 'avg_delta_vx', 'delta_x+']]
# test_data1 = test_data[['time', 'kick_vx', 'vx', 'avg_vx', 'avg_delta_vx', 'delta_x+']]
# train_data_vx1.to_csv('train_vx.csv', index=False, header=False)
# test_data1.to_csv('test_vx.csv', index=False, header=False)

# 选择机器学习训练需要的数据
feature_cols_vx = ['time', 'kick_vx', 'vx', 'avg_vx', 'avg_delta_vx']
# for i in range(1, 11, 1):
#     feature_cols_vx.append('time-{}'.format(i))
#     feature_cols_vx.append('vx-{}'.format(i))
feature_cols_vy = ['time', 'kick_vy', 'vy', 'avg_vy', 'avg_delta_vy']
# for i in range(1, 11, 1):
#     feature_cols_vy.append('time-{}'.format(i))
#     feature_cols_vy.append('vy-{}'.format(i))
# 规定输出模型的数据类型
target_cols_vx = ['delta_x+']
target_cols_vy = ['delta_y+']
input_dim_vx = len(feature_cols_vx)
output_dim_vx = len(target_cols_vx)
input_dim_vy = len(feature_cols_vy)
output_dim_vy = len(target_cols_vy)

X_vx = train_data_vx[feature_cols_vx].values
Y_vx = train_data_vx[target_cols_vx].values
X_test_vx = test_data[feature_cols_vx].values
X_vy = train_data_vy[feature_cols_vy].values
Y_vy = train_data_vy[target_cols_vy].values
X_test_vy = test_data[feature_cols_vy].values
# 训练参数
params = {'boosting_type': 'goss',  # 'gbdt',
          # 'learning_rate': 0.01,  #1.5,  # 0.1
          'objective': 'mape',  # 'mae',
          'metric': 'mape',  # 'mae',
          'num_threads': 6,
          # 'device': 'gpu',
          'bagging_freq': 5,
          'num_leaves': 9,  # 3,
          'verbose': -1,  # 0,
          'bagging_fraction': 1,  # 0.7
          'feature_fraction': 0.7,  # 0.95
         }
# 机器学习训练及检验
reg = MultiOutputRegressor(lgb.LGBMRegressor(**params, n_estimators=20000, force_col_wise=True))
# lgb.plot_metrics(reg, metrics='auc')
P_vx = np.zeros_like(Y_vx, dtype=float)
P_tst_vx = np.zeros((X_test_vx.shape[0], output_dim_vx), dtype=float)
if TRAIN_VX:
    reg.fit(X_vx, Y_vx)
    # 模型存储
    #joblib.dump(reg, MODEL[0])
# 模型加载
#reg = joblib.load(MODEL[0])
print('start to predict vx')
s = datetime.datetime.now()
P_tst_vx = reg.predict(X_test_vx)
e = datetime.datetime.now()
print ('predicting vx uses', (e - s).microseconds, 'us')

reg = MultiOutputRegressor(lgb.LGBMRegressor(**params, n_estimators=20000, force_col_wise=True))
P_vy = np.zeros_like(Y_vy, dtype=float)
P_tst_vy = np.zeros((X_test_vy.shape[0], output_dim_vy), dtype=float)
if TRAIN_VY:
    reg.fit(X_vy, Y_vy)
    # 模型存储
    #joblib.dump(reg, MODEL[1])
# 模型加载
#reg = joblib.load(MODEL[1])
print('start to predict vy')
s = datetime.datetime.now()
P_tst_vy = reg.predict(X_test_vy)
e = datetime.datetime.now()
print ('predicting vy uses', (e - s).microseconds, 'us')

pred_df = pd.concat([pd.DataFrame(P_tst_vx, columns=target_cols_vx), pd.DataFrame(P_tst_vy, columns=target_cols_vy)], axis=1)

predicted_x = pred_df['delta_x+'] + test_data['x']
predicted_y = pred_df['delta_y+'] + test_data['y']
diff_x_rate = (np.fabs((predicted_x - test_data['x+']) / (test_data['x+'] - test_data['x']))).mean()
diff_x = np.fabs(test_data['x+'] - predicted_x).mean()
diff_x_var = np.var(test_data['x+'] - predicted_x)
print(max(np.fabs(test_data['x+'] - predicted_x)))
diff_y_rate = (np.fabs((predicted_y - test_data['y+']) / (test_data['y+'] - test_data['y']))).mean()
diff_y = np.fabs(test_data['y+'] - predicted_y).mean()
diff_y_var = np.var(test_data['y+'] - predicted_y)
print(max(np.fabs(test_data['y+'] - predicted_y)))
diff_pos = np.sqrt(np.square([test_data['x+'] - predicted_x, test_data['y+'] - predicted_y])).mean()
print('predicted x error: ', diff_x, 'error rate: ', diff_x_rate, 'error var: ', diff_x_var)
print('predicted y error: ', diff_y, 'error rate: ', diff_y_rate, 'error var: ', diff_y_var)
print('predicted pos error: ', diff_pos)

plt.figure(1)
plt.scatter(test_data['time+'], test_data['x+'], s=10, c='r', label="real x")
plt.xlabel('time(ms)')
plt.ylabel('x(mm)')
plt.scatter(test_data['time+'], predicted_x, s=10, c='b', label="predicted x")
plt.legend(loc="upper right")

plt.figure(2)
plt.scatter(test_data['time+'], test_data['y+'], s=10, c='r', label="real y")
plt.xlabel('time(ms)')
plt.ylabel('y(mm)')
plt.scatter(test_data['time+'], predicted_y, s=10, c='b', label="predicted y")
plt.legend(loc="upper right")

plt.figure(3)
# plt.scatter(test_data['time+'], np.fabs(test_data['x+'] - predicted_x), s=10, c='r', label="error x")
# plt.scatter(test_data['time+'], np.fabs(test_data['x+'] - test_data['x']), s=10, c='b', label="error rate x")
plt.scatter(test_data['time+'], np.fabs(test_data['y+'] - predicted_y), s=10, c='r', label="error y")
plt.scatter(test_data['time+'], np.fabs(test_data['y+'] - test_data['y']), s=10, c='b', label="error rate y")

plt.figure(4)
# plt.scatter(test_data['time+'], test_data['vx'], s=10, c='r', label="velx")
plt.scatter(test_data['time+'], test_data['vy'], s=10, c='r', label="vely")

# plt.figure(5)
# plt.scatter(test_data['time+'], test_data['vx'], s=10, c='b', label="velx")
# plt.scatter(test_data['time+'], np.sqrt(np.square([test_data['x+'] - predicted_x, test_data['y+'] - predicted_y])), s=10, c='b', label="diff pos")

plt.figure(6)
plt.scatter(test_data['x+'], test_data['y+'], s=10, c='r', label="real pos")
plt.xlabel('x(mm)')
plt.ylabel('y(mm)')
plt.scatter(predicted_x, predicted_y, s=10, c='b', label="predicted pos")
plt.legend(loc="upper right")

plt.show()
