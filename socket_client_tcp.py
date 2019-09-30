
# 客户端
import socket
import json
import wx # gui界面
import threading

s = None

def init():
  global s
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  host = socket.gethostname()
  port = 12346

  try:
    s.connect((host,port)) # 定义连接
  except Exception as e:
    print("连接服务器失败",e)
    exit(-1)

def login():
  # 发送登陆信息
  name = input("input name: ")
  password = input("input password: ") # python 的getpass模块只能在指定ide中才起作用，故这里依然明文显示
  client_info = json.dumps({'name':name, 'password':password}).encode('utf-8')
  s.send(client_info)

  msg = s.recv(1024).decode(encoding='utf-8') # 大坑！！！！！！！！！！！
  # 只会接收一次，用msg去装载，如果先接受信息，再去赋值给msg那么就赋值失败了
  # 接收TCP数据，数据以字符串形式返回，参数指定要接收的最大数据量(BUFSIZE)
  print(msg)

  if msg == 'name or password is incorrect!':
    exit()

  s.sendall('Connected!'.encode(encoding='utf-8'))


def get_message():

  while True: # 不断接收消息
    data = s.recv(1024).decode(encoding='utf-8')
    if data == 'close':
      print('The server closed your client!')
      s.close()
      exit()
    if not data:
      break
    print("\nA message from server:", end=' ')
    print(data)
    break

def gui(): # 随便写的，没什么用

  app = wx.App(False)
  frame = wx.Frame(None, title="Login Page", size=(410, 335))
  frame.Show()

  name = wx.TextCtrl(frame, pos=(35, 5), size=(210, 25))
  password = wx.TextCtrl(frame, pos=(35, 35), size=(210, 25))
  login_Button = wx.Button(frame, label='login', pos=(65, 80), size=(80, 25))
  login_Button.Bind(wx.EVT_BUTTON, login(name.GetValue(),password.GetValue()))

  app.MainLoop()

def menu():

  print('''
                  |----------------------------------|
                  | input 1:Waiting for message...   |
                  | input 2:Sending message to client|
                  | input 3:Close server             |
                  |----------------------------------|
      ''')

  while True:
    n = input(">>>")
    if n == '1':
      get_message()
    elif n == '2':  # 发送exit可自动退出
      message = input("input you message here: ")
      s.sendall(message.encode(encoding='utf-8'))
      data = s.recv(1024).decode(encoding='utf-8')
      if data == 'close':
        print('The server closed your client!')
        s.close()
        exit()
    elif n == '3':
      print("The connection is closed")
      s.close()
      exit()


if __name__ == '__main__':

  init()
  login()

  thread1 = threading.Thread(target=get_message)
  thread2 = threading.Thread(target=menu)

  thread1.start()
  thread2.start()
