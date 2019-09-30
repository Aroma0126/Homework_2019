
# 服务器端/创建服务
import socket
import threading
import json

s = None
connection_pool = list()

info_list = [
  {'name': 'flj' ,'password': 12345},
  {'name': 'wyn', 'password': 12346},
  {'name': 'cc', 'password': 12347},
  {'name': 'teacher', 'password': 66666}
]

address_index_list = list()

def init():

  global s
  s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
  host = socket.gethostname()
  port = 12346
  s.bind((host,port))
  print("Socket server is started,waiting for client...")


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
      print("recieve from port: ",address[1],end=" ")
      print("message is: ",data)


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
      for i in range(len(address_index_list)):
        k = int(address_index_list[i])
        if k == int(port):
          index = i
          break
      s.sendto(msg.encode(encoding='utf8'),connection_pool[index])

    elif n == '3':
      s.close()
      exit()

