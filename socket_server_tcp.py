# 服务器端/创建服务
import socket
import threading
import json
import tkinter as tk  # 使用Tkinter前需要先导入
from tkinter import messagebox


s = None
connection_pool = list()  # 连接池

# 账户密码列表
info_list = [
  {'name': 'flj' ,'password': 12345},
  {'name': 'wyn', 'password': 12346},
  {'name': 'cc', 'password': 12347},
  {'name': 'teacher', 'password': 66666}
]
client_index_list = list() # 用来存储相应的端口号和下表索引

def init():
  global s  # 全局变量
  s = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # 创建一个socket对象,使用TCP协议
  host = socket.gethostname() # 获取本地主机名
  port = 12346 # 定义端口号
  s.bind((host,port)) # 绑定端口和主机/bind(): 绑定地址（host,port）到套接字，
                      # 在AF_INET下,以元组（host,port）的形式表示地址。
  # 开始TCP监听。backlog指定在拒绝连接之前，操作系统可以
  # 挂起的最大连接数量。该值至少为1，大部分应用程序设为5就可以了。/最大等待数
  s.listen(5)
  print("Socket server is started,waiting for client...")

def accept_client():
  while True: # 不断接受新连接
    try:
      global address
      client, address = s.accept()
      print('client:',client)
      print('address:', address)
      client_index_list.append(address[1])  # 存储每个端口号，发送消息时直接根据端口号来找出索引
      connection_pool.append(client)
      # 创建一个新的线程
      t = threading.Thread(target=handle_message,args=(client,address))
      t.setDaemon(True)
      t.start()
    except Exception as e:
      print("\nSome mistakes: ", e)

def handle_message(client,address):
  try:
    ret = client.recv(1024)
    client_info = json.loads(ret.decode(encoding='utf-8'))
    success = False
    for i_info in info_list:
      name = i_info['name']
      password = i_info['password']
      if (name == client_info['name'] and str(password) == client_info['password']):
        success = True
        break
    if success:
      client.sendall("Connected Successfully!".encode(encoding='utf8'))
      t1.insert('end','The client '+str(address[1])+' has connected!'+'\n')
      while True:
        data = client.recv(1024)
        t = str(data, encoding="utf-8")
        if t == 'close':
          t1.insert('end', 'The port ' + str(address[1]) + ' has closed!' + '\n')
          t1.see('end')
          connection_pool.remove(client)
          client_index_list.remove(address[1])
          break
        if len(data) != 0 and data != b'exit':
          t1.insert('end', 'message from '+str(address[1])+' : '+t+'\n')
          t1.see('end')
    else:
      client.sendall("name or password is incorrect!".encode('utf-8'))
      client.close()
  except Exception as e:
    print("\nSome mistakes: ",e)




def client_close():
  close_port = imf.get()
  msg = 'close'
  index = 0
  for i in range(len(client_index_list)):
    k = int(client_index_list[i])
    if k == int(close_port):
      index = i
      break
  connection_pool[int(index)].sendall(msg.encode(encoding='utf8'))
  del connection_pool[index]
  del client_index_list[index]  # delete the port
  t1.insert('end','The server has closed '+str(close_port)+'\n')
  t1.see('end')
  imf.set('')


def send_message():
  port = imf.get()
  message = msg.get()
  index = 0
  for i in range(len(client_index_list)):
    k = int(client_index_list[i])
    if k == int(port):
      index = i
      break
  if index < len(client_index_list):
    connection_pool[int(index)].sendall(message.encode(encoding='utf8'))
    t1.insert('end', 'message send to ' + port + ' : ' + message + '\n')
    t1.see('end')
  else:
    messagebox.showerror('错误', '该客户端不存在！')
  imf.set('')
  msg.set('')


def online_number():
  num=str(len(connection_pool))
  t1.insert('end','Online number is : '+num+'\n')
  t1.see('end')


def close():
  t = 'the server has closed!'
  for i in range(len(client_index_list)):
    connection_pool[i].sendall(t.encode(encoding='utf8'))
  s.close()
  window.destroy()



if __name__ == '__main__':

  init()
  thread = threading.Thread(target=accept_client)
  thread.setDaemon(True)
  thread.start()

  window = tk.Tk()
  window.title('服务器界面')
  window.geometry('400x400')


  t1 = tk.Text(window, height=15, width=50)
  t1.pack()
  imf = tk.StringVar()
  tk.Label(window, text='端口号:', font=('Arial', 10)).place(x=22, y=210)
  btn_close_client = tk.Button(window, width=12, text='关闭该客户端', command=client_close)
  btn_close_client.place(x=250,y=203)
  t2 = tk.Entry(window, width=20, textvariable=imf).place(x=75, y=210)
  msg = tk.StringVar()
  tk.Label(window, text='消息:', font=('Arial', 10)).place(x=22, y=240)
  t3 = tk.Entry(window, width=40, textvariable=msg).place(x=75, y=240)
  btn_send = tk.Button(window, width=30, text='发送', command=send_message)
  btn_send.place(x=80, y=270)
  btn_number = tk.Button(window, width=30, text='查询在线客户数', command=online_number)
  btn_number.place(x=80, y=310)
  btn_close = tk.Button(window, width=30, text='关闭服务器', command=close)
  btn_close.place(x=80, y=350)
  window.mainloop()
