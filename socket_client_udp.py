import socket
import json

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) #使用UDP协议
host = socket.gethostname()
port = 12346


def login():
  # name = input("input name: ")
  # password = input("input password")
  name = 'flj'
  password = '12345'
  # info = name + password
  client_info = json.dumps({'name': name, 'password': password}).encode('utf-8')
  # info = info.encode('utf-8')
  s.sendto(client_info, (host, port))
  message, address = s.recvfrom(1024)
  print(message)

def get_mes():
  while True:
    data, address = s.recvfrom(1024)
    print(data)


if __name__ == '__main__':

  login()

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
      get_mes()

    elif n == '2':

      message = input("input you message here: ")
      s.sendto(message.encode('utf-8'), (host, port))
      data = s.recv(1024).decode(encoding='utf-8')
      if data == 'close':
        print('The server closed your client!')
        s.close()
        exit()

    elif n == '3':
      print("The connection is closed")
      s.close()
      exit()


  send_mes()
  get_mes()



s.close()







