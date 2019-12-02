
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
iris = pd.read_table('..\data\iris.dat',header=None)
print(iris)



def Print_1():
# 想要指定颜色就只能循环
# 蓝色男生 粉色女生 黄色不知道男女
# 圆形18 三角形19
# df.index.values 行号索引
  for x in excel1.index.values:
    if excel1.ix[x,3] == '男':
      plt.scatter(excel1.ix[x,0].values, excel1.ix[x,1].values,color='#57faff',marker='o',label="16级")
      plt.text(excel1.ix[x,0].values, excel1.ix[x,1].values, excel1.ix[x,2].values, ha='center', va='bottom', fontsize=15)
    elif excel1.ix[x,3] == '女':
      plt.scatter(excel1.ix[x,0].values,excel1.ix[x,1].values,color='#ff8080',marker='o',label="16级")
      plt.text(excel1.ix[x,0].values,excel1.ix[x,1].values, excel1.ix[x,2].values, ha='center', va='bottom',fontsize=15)
    else:
      plt.scatter(excel1.ix[x,0].values, excel1.ix[x,1].values,s=excel1.ix[x,2].values,color='g',marker='o',label="16级")
      plt.text(excel1.ix[x,0].values, excel1.ix[x, 1].values, excel1.ix[x, 2].values, ha='center', va='bottom',fontsize=15)

  for x in excel2.index.values:
    if excel2.ix[x,3] == '男':
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='#57faff', marker='^',label="17级")
    elif excel2.ix[x,3] == '女':
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='#ff8080', marker='^',label="17级")
    else:
      plt.scatter(excel2.ix[x:, 0].values, excel2.ix[x:, 1].values, s=excel2.ix[x:, 2].values, color='g', marker='^',label="17级")
  plt.legend(loc='best')
  plt.show()

def Print_2():

  for i in range(0,149):
    print(iris.ix[i,3])
    if iris.ix[i,4] == 1:
      plt.plot(iris.ix[i,0].values,iris.ix[i,1].values,color='483C32',markerfacecolor='9966CC',label='Iris Setosa')
    elif iris.ix[i,4].values == 2:
      plt.plot(iris.ix[i, 0].values, iris.ix[i, 1].values, color='483C32', markerfacecolor='FE4C40', label='Iris Versicolour')
    else:
      plt.plot(iris.ix[i, 0].values, iris.ix[i, 1].values, color='483C32', markerfacecolor='C3BED4',
               label='Iris Virginica')

  plt.legend(loc='best')
  plt.show()

if __name__ == '__main__':

  # Print_1()
  print('----')
  print(iris.ix[:,0])
  print(iris.ix[0,:].values)
  # Print_2()


