
'''
ex1 可视化数据集1/2的数据
思路 先读取数据存到list里面 然后利用 matplotlib
dataset1 infos of student 从excel里读出

属性
1.height in cm
2.weight in kg
3.size of feet in 中国鞋码

利用散点图，身高体重xy轴，散点大小表示鞋码，颜色表示男女

iris.dat
属性
1. sepal length in cm
2. sepal width in cm
3. petal length in cm
4. petal width in cm
5. class:
	1-- Iris Setosa
	2-- Iris Versicolour
	3-- Iris Virginica

'''


from matplotlib import pyplot as plt
import matplotlib.cm as cm
import pandas as pd


excel1 = pd.read_excel('..\data\student2018.xlsx')
excel2 = pd.read_excel('..\data\student2019.xlsx')
iris = pd.read_table('..\data\iris.dat',header=None,sep='\s+')
# print(iris)



def Print_1():
# 想要指定颜色就只能循环
# 蓝色男生 粉色女生 黄色不知道男女
# 圆形18 三角形19
# df.index.values 行号索引
  for x in excel1.index.values:
    if excel1.ix[x,3] == '男':
      plt.scatter(excel1.ix[x,0], excel1.ix[x,1],color='#57faff',marker='o',label="16级")
      plt.text(excel1.ix[x,0], excel1.ix[x,1], excel1.ix[x,2], ha='center', va='bottom', fontsize=6)
    elif excel1.ix[x,3] == '女':
      plt.scatter(excel1.ix[x,0],excel1.ix[x,1],color='#ff8080',marker='o',label="16级")
      plt.text(excel1.ix[x,0],excel1.ix[x,1], excel1.ix[x,2], ha='center', va='bottom',fontsize=6)
    else:
      plt.scatter(excel1.ix[x,0], excel1.ix[x,1],s=excel1.ix[x,2],color='g',marker='o',label="16级")
      plt.text(excel1.ix[x,0], excel1.ix[x, 1], excel1.ix[x, 2], ha='center', va='bottom',fontsize=6)

  for x in excel2.index.values:
    if excel2.ix[x,3] == '男':
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='#57faff', marker='^',label="17级")
      plt.text(excel2.ix[x, 0], excel2.ix[x, 1], excel2.ix[x, 2], ha='center', va='bottom', fontsize=6)
    elif excel2.ix[x,3] == '女':
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='#ff8080', marker='^',label="17级")
      plt.text(excel2.ix[x, 0], excel2.ix[x, 1], excel2.ix[x, 2], ha='center', va='bottom', fontsize=6)
    else:
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='g', marker='^',label="17级")
      plt.text(excel2.ix[x, 0], excel2.ix[x, 1], excel2.ix[x, 2], ha='center', va='bottom', fontsize=6)
  # plt.legend(loc='best')
  plt.show()

def Print_2():

  for i in range(1,149):
    # print(iris.ix[i,3])
    if iris.ix[i,4] == 1:
      x_1 = []
      y_1 = []
      x_1.append(iris.ix[i, 0])
      x_1.append(iris.ix[i, 2])
      y_1.append(iris.ix[i, 1])
      y_1.append(iris.ix[i, 3])
      plt.plot(x_1, y_1, color='#9966CC', markerfacecolor='9966CC', label='Iris Setosa')
      # plt.scatter(iris.ix[i, 0],iris.ix[i, 1],color='#9966CC',label='Iris Setosa')
    elif iris.ix[i,4] == 2:
      x_2 = []
      y_2 = []
      x_2.append(iris.ix[i, 0])
      x_2.append(iris.ix[i, 2])
      y_2.append(iris.ix[i, 1])
      y_2.append(iris.ix[i, 3])
      plt.plot(x_2, y_2, color='#FE4C40', markerfacecolor='FE4C40', label='Iris Versicolour')
      # plt.scatter(iris.ix[i, 0], iris.ix[i, 1], color='#FE4C40', label='Iris Versicolou')
    else:
      x_3 = []
      y_3 = []
      x_3.append(iris.ix[i, 0])
      x_3.append(iris.ix[i, 2])
      y_3.append(iris.ix[i, 1])
      y_3.append(iris.ix[i, 3])
      plt.plot(x_3, y_3, color='#C3BED4', markerfacecolor='C3BED4', label='Iris Virginica')
      # plt.scatter(iris.ix[i, 0], iris.ix[i, 1], color='#C3BED4', label='Iris Virginica')

  #
  print("---",y_1)
  # plt.plot(x_1, y_1, color='red', markerfacecolor='9966CC', label='Iris Setosa')
  # plt.plot(x_2, y_2, color='green', markerfacecolor='FE4C40', label='Iris Versicolour')
  #plt.plot(x_3, y_3, color='blue', markerfacecolor='C3BED4', label='Iris Virginica')
  # plt.legend(loc='best')
  plt.show()

if __name__ == '__main__':

  Print_1()
  Print_2()


