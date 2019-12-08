'''

模式识别课程设计

基于opencv的表格识别
输入：一个带文字的表格图片
输出：一个识别出内容的excel表格，内容为图片内容的填充

'''

'''
import cv2



def show_pic(img,name):
    cv2.namedWindow('picture_1', cv2.WINDOW_NORMAL)
    cv2.imshow(name, img)
    cv2.waitKey()  # avoid picture showing too fast


if __name__ == '__main__':
    img = cv2.imread('.\pic_1.png')
    show_pic(img,'row_pic')

    # 二值化之前进行灰度化处理
    img_gray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
    # 二值化
    thresh_img = cv2.adaptiveThreshold(~img_gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, -5)

    show_pic(thresh_img,'after threshold')

'''

# 利用算法来识别一个表格不如直接图像处理来的方便，遂放弃这个主题
# Salary prediction using adult data set


# data_train =
# data_test =


