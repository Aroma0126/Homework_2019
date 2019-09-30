'''

import socket
import threading
import time

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host = socket.gethostname()
port = 8833
s.bind((host,port))

print('Bind UDP on ...')

info_list = list()
info_list_port = list()

def get_mes():

  while True:
    data,addr = s.recvfrom(1024)
    print('Received from ',addr)
    info_list.append(addr)
    info_list_port.append(addr[1])
    print(info_list_port)

def send_msg():
  while True:
    data, addr = s.recvfrom(1024)
    s.sendto(b'Hello, %s!' % data, addr)

def menu():

    n = input("inout you number >>>")
    if n == '1':
      print("Online number is : ", len(info_list_port))

    elif n == '2':
      port, data = input("Please input “port/message” ").split("/")
      data = data.encode("utf-8")

      index = 0
      for i in range(len(info_list_port)):
        k = int(info_list_port[i])
        if k == int(port):
          index = i
          break
      addr = info_list[index]
      s.sendto(data, addr)

    elif n == '3':
      print("hang on...")

if __name__ == '__main__':

  #
  while True:
    get_mes()
    menu()

s.close()  # 关闭

'''



# 服务器端/创建服务
import socket
import threading
import json

s = None
connection_pool = list()  # 连接池
# 账户密码列表
info_list = [
  {'name': 'flj' ,'password': 12345},
  {'name': 'wyn', 'password': 12346},
  {'name': 'cc', 'password': 12347},
  {'name': 'teacher', 'password': 66666}
]

address_index_list = list() # 用来存储相应的端口号和下表索引

def init():

  global s  # 全局变量
  s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
  host = socket.gethostname()
  port = 12346
  s.bind((host,port))
  print("Socket server is started,waiting for client...")


def accept_client():
  while True:
    global address
    data, address = s.recvfrom(1024)
    verify_info(data)

def verify_info(data):

  client_info = json.loads(data.decode(encoding='utf-8'))
  success = False

  for i_info in info_list:
    name = i_info['name']
    password = i_info['password']
    if (name == client_info['name'] and str(password) == client_info['password']):
      success = True
      break

  if success:
    # 创建一个新的线程
    t = threading.Thread(target=get_mes)
    t.setDaemon(True)
    t.start()
    print("connected...", address)
    connection_pool.append(address)
    address_index_list.append(address[1])
    s.sendto("Connected Successfully!".encode(encoding='utf8'), address)
  else:
    s.sendto("name or password is incorrect!".encode('utf-8'), address)


def get_mes():

  while True:
    global address
    data, address = s.recvfrom(1024)
    str = data.decode('utf-8')
    if str[0] == '{':
      verify_info(data)
    else:
      print("recieve from ",address[1],end=" ")
      print(data)


if __name__ == '__main__':

  init()

  thread = threading.Thread(target=get_mes)
  thread.start()

  print('''
              |----------------------------------|
              | input 1:Checking online numbers  |
              | input 2:Sending message to client|
              | input 3:Close server             |
              |----------------------------------|
  ''')

  while True:

    n = input(">>>")

    if n == '1':
      print("Online number is : ",len(connection_pool))

    elif n == '2':
      port, msg = input("Please input “port/message” ").split("/")
      index = 0
      # print(len(client_index_list))
      # print(client_index_list)
      for i in range(len(address_index_list)):
        k = int(address_index_list[i])
        if k == int(port):
          index = i
          break
      s.sendto(msg.encode(encoding='utf8'),connection_pool[index])

    elif n == '3':
      s.close()
      exit()

