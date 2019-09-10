
import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) #使用UDP协议
host = socket.gethostname()
port = 8088
s.bind((host,port))

while True:
  data,address = s.recvfrom(1024)
  print("Recevied from: ",address)
  s.sendto(data, address)

