'''

模式识别课程设计

基于opencv的表格识别
输入：一个带文字的表格图片
输出：一个识别出内容的excel表格，内容为图片内容的填充

'''

import cv2






if __name__ == '__main__':
    img = cv2.imread('.\pic_1.png')
    cv2.namedWindow('picture_1', cv2.WINDOW_NORMAL)
    cv2.imshow('picture_1',img)
    cv2.waitKey() # avoid picture showing too fast