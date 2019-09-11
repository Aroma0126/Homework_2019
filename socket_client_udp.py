


import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host = socket.gethostname()
port = 8088

data = 'Hello,User!(UDP)!'
s.sendto(data.encode(), (host, port))
print(s.recv(1024))

s.close()  # 关闭









