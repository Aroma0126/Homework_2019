from tkinter import *
import socket
import threading
import json


def init():
  global s
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  host = socket.gethostname()
  port = 12346

  s.connect((host, port))  # 定义连接


  name = 'flj'
  password = '12345'
  client_info = json.dumps({'name': name, 'password': password}).encode('utf-8')
  s.send(client_info)

  msg = s.recv(1024).decode(encoding='utf-8')
  print(msg)

  message = 'i am here!'  # 只是为了让服务器打印出来端口号方便发消息，没别的意思
  s.sendall(message.encode(encoding='utf-8'))


def recv():
  while True:
    data = s.recv(1024).decode(encoding='utf-8')
    print('\n' + data + '\n')


class GUI:

  def __init__(self, root):
    self.root = root
    self.listBox = Listbox(self.root)
    self.listBox.pack()
    self.entry = Entry(self.root)
    self.entry.pack()
    self.sendBtn = Button(self.root, text='发送', command=self.send)
    self.sendBtn.pack()

  def send(self):
    send_data = self.entry.get()
    s.send(send_data.encode())

def createGUI():
  global gui
  root = Tk()
  gui = GUI(root)
  root.title('客户端')
  root.mainloop()


if __name__ == '__main__':

  init()
  # 同时做两件事情
  t1 = threading.Thread(target=recv, args=(), name='recv')
  t2 = threading.Thread(target=createGUI, args=(), name='gui')

  t1.start()
  t2.start()

