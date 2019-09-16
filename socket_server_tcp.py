
# 服务器端/创建服务
import socket
import threading
import json

s = None
connection_pool = []  # 连接池
# 账户密码列表
info_list = [
  {'name': 'flj' ,'password': 12345},
  {'name': 'tom', 'password': 54321},
  {'name': 'fiona', 'password': 11111},
  {'name': 'jack', 'password': 22222}
]


def init():
  global s  # 全局变量
  global i
  i = 0
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
      # accept() : 被动接受TCP客户端连接,(阻塞式)等待连接的到来
      client, address = s.accept()
      # 为每个客户端添加一个独立的线程
      connection_pool.append(client)
      # i += 1
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
      data = client.recv(1024)
      print("\nThe client host: ", address, end='')
      print(" Client message: ", data.decode(encoding='utf-8'))

      while True:
        data = client.recv(1024)
        if len(data) == 0 or data == b'exit':
          msg = 'close'
          client.sendall(msg.encode(encoding='utf8'))
          client.close() # 删除连接
          connection_pool.remove(client)
          print("\nOne client closed.")
          break
        client.sendall('get message'.encode(encoding='utf8'))
        print("\nThe client host: ", address,end='')
        print(" Client message: ", data.decode(encoding='utf-8'))
    else:
      client.sendall("name or password is incorrect!".encode('utf-8'))
      client.close()
      connection_pool.remove(client)

  except Exception as e:
    print("\nSome mistakes: ",e)

if __name__ == '__main__':

  init()
  thread = threading.Thread(target=accept_client)
  thread.setDaemon(True)
  thread.start()

  print('''
              |----------------------------------|
              | input 1:Checking online numbers  |
              | input 2:Sending message to client|
              | input 3:Close server             |
              | input 4:Close client             |
              |----------------------------------|
  ''')

  while True:

    n = input(">>>")

    if n == '1':
      print("Online number is : ",len(connection_pool))

    elif n == '2':
      index, msg = input("Please input “index/message” ").split("/")
      connection_pool[int(index)].sendall(msg.encode(encoding='utf8'))

    elif n == '3':
      s.close()
      exit()

    elif n == '4':
      close_i = input("Please input the close index ")
      msg = 'close'
      connection_pool[int(close_i)].sendall(msg.encode(encoding='utf8'))
      connection_pool[int(close_i)].close()
      # connection_pool[int(close_i)].remove()
      # 还没有解决



