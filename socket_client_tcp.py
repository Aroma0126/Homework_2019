
# 客户端
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
port = 12346

s.connect((host,port)) # 定义连接

print(s.recv(2048).decode(encoding='utf-8')) # 接收TCP数据，数据以字符串形式返回，参数指定要接收的最大数据量(BUFSIZE)

s.sendall("online...".encode(encoding='utf-8'))

while True:
  print(s.recv(1024).decode(encoding='utf8'))
  if s.recv(1024).decode(encoding='utf8') == 'out':
    s.close()

input("")



# s.close() # 关闭

