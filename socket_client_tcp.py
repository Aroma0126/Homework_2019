
# 客户端
import socket
import json


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
port = 12346

s.connect((host,port)) # 定义连接

while True:
  name = input("input name: ")
  password = input("input password: ")
  client_info = json.dumps({'name':name, 'password':password}).encode('utf-8')
  s.send(client_info)
  print(s.recv(1024).decode(encoding='utf-8')) # 接收TCP数据，数据以字符串形式返回，参数指定要接收的最大数据量(BUFSIZE)
  message = input("input you message here: ")
  s.sendall(message.encode(encoding='utf-8'))

  while True:
    print(type(s.recv(1024).decode(encoding='utf8')))
    ret = s.recv(1024).decode(encoding='utf8')
    print( type(str) )
    if  ret == str :
      print("success!")
      s.close()
      break

input("")
