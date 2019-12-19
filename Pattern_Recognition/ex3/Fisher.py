'''
线性分类器设计
（1）同时采用身高和体重数据作为特征，用Fisher 线性判别方法求分类器，
将该分类器应用到训练和测试样本，考察训练和测试错误情况。将训练样本和求
得的决策边界画到图上，同时把以往用Bayes方法求得的分类器也画到图上，比
较结果的异同。
（2）选择上述实验的Fisher 线性判别方法，用留一法在训练集上估计错误
率，与在测试集上得到的错误率进行比较。
'''
import numpy as np
from matplotlib import pyplot as plt
import pandas as pd

def fisher(w1, w2):
    # 将行向量转置为列向量
    w1 = w1.T
    w2 = w2.T

    sz1 = np.size(w1, 1)
    sz2 = np.size(w2, 1)

    #  1.求wi均值
    m1 = np.mean(w1, axis=1)
    m2 = np.mean(w2, axis=1)

    # 2.计算样本内离散度 Si 和总类内离散度矩阵 Sw
    s1 = np.zeros((w1.shape[0], w1.shape[0]))
    n, m = w1.shape
    for i in range(m):
        tmp = w1[:, i] - m1
        s1 = s1 + tmp * tmp.T

    s2 = np.zeros((w2.shape[0], w2.shape[0]))
    n, m = w2.shape
    for i in range(m):
        tmp = w2[:, i] - m2
        s2 = s2 + tmp * tmp.T
    sw = (sz1 * s1 + sz2 * s2) / (sz1 + sz2)

    # 3.计算样本间离散度 sb
    sb = (m1 - m2) * (m1 - m2).T

    # 4.计算w_star
    w_star = np.linalg.inv(sw) * (m1 - m2)
    res1 = 0
    for i in range(sz1):
        res1 = res1 + w1[:, i].T * w_star
    res1 /= sz1

    res2 = 0
    for i in range(sz2):
        res2 = res2 + w2[:, i].T * w_star
    res2 /= sz2

    return -(res1 * sz1 + res2 * sz2) / (sz1 + sz2), w_star


def get_res(X, w0, w_star):
    res = X * w_star + w0
    if res >= 0:
        print('男')
    else:
        print('女')


def get_line(w, w0):
    # 换两类之间的分界线
    w = np.array(w)
    x = np.linspace(150, 200, 50)
    y = -w[0, 0] * x / w[1, 0] - w0 / w[1, 0]
    y = y.reshape(-1, 1)  # 将行向量转置
    return x, np.array(y)


def show_fig(w):
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.scatter(np.array(w1[:, 0]), np.array(w1[:, 1]), c='r')
    ax1.scatter(np.array(w2[:, 0]), np.array(w2[:, 1]), c='y')
    ax1.plot(wx, wy)
    ax1.scatter(np.array(w[0, 0]), np.array(w[0, 1]), c='b')
    plt.show()

def set_data():
    datasets = pd.read_excel('..\data\student2019.xlsx')  # 默认跳过头了
    test_datasets = pd.read_excel('..\data\student2018.xlsx')
    datasets = (np.array(datasets)).tolist()
    print(datasets)
    test_datasets = (np.array(test_datasets)).tolist()
    boy_list = list()
    girl_list = list()
    for i in range(len(datasets)):
        student = datasets[i]
        temp = [student[0], student[1]]
        if student[-1] == '男':
            boy_list.append(temp)
        elif student[-1] == '女':
            girl_list.append(temp)
    for i in range(len(test_datasets)):
        student = test_datasets[i]
        temp = [student[0], student[1]]
        if student[-1] == '男':
            boy_list.append(temp)
        elif student[-1] == '女':
            girl_list.append(temp)
    # print(boy_list)
    # print(girl_list)
    return boy_list,girl_list




if __name__ == '__main__':

    # w1 = np.mat([[2.95, 6.63], [2.53, 7.79], [3.57, 5.65], [3.16, 5.47]]) # 合格
    # w2 = np.mat([[2.58, 4.46], [2.16, 6.22], [3.27, 3.52]]) # 不合格

    w1,w2 = set_data() # 男/女
    w1 = np.mat(w1)
    w2 = np.mat(w2)

    w0, w_star = fisher(w1, w2)

    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    plt.xlim(150, 200)
    plt.ylim(0, 100)
    ax1.scatter(np.array(w1[:, 0]), np.array(w1[:, 1]), c='r')
    ax1.scatter(np.array(w2[:, 0]), np.array(w2[:, 1]), c='y')

    wx, wy = get_line(w_star, w0)
    print(wx,wy)
    # 显示分类情况
    for i in range(len(wy)):
        wy[i] = wy[i] - 10
    print(wx, wy)
    ax1.plot(wx, wy)
    plt.show()





'''
    # 输入样例
    while True:
        n1, n2 = map(float, input().split())
        # print(n1,n2)
        w = np.mat([n1, n2])
        show_fig(w)
        get_res(w, np.array(w0), w_star)

'''