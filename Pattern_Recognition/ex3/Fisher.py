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
import math
