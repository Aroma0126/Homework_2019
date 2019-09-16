
# 客户端
import socket
import json


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
port = 12346


try:
  s.connect((host,port)) # 定义连接
except Exception as e:
  print("连接服务器失败",e)
  exit(-1)


while True:

  try:

    # 发送登陆信息
    msg = 'msg'
    name = input("input name: ")
    password = input("input password: ") # python 的getpass模块只能在指定ide中才起作用，故这里依然明文显示
    client_info = json.dumps({'name':name, 'password':password}).encode('utf-8')
    s.send(client_info)

    msg = s.recv(1024).decode(encoding='utf-8') # 大坑！！！！！！！！！！！
    # 只会接收一次，用msg去装载，如果
    print(msg) # 接收TCP数据，数据以字符串形式返回，参数指定要接收的最大数据量(BUFSIZE)

    if msg == 'name or password is incorrect!':
      exit()

    print('''
                  |----------------------------------|
                  | input 1:Sending message to server|
                  | input 2:Close client             |
                  | input 3:Client hanging           |
                  |----------------------------------|
      ''')

    while True:

      n = input()

      if n == '1':
        message = input("input you message here: ")
        s.sendall(message.encode(encoding='utf-8'))
      elif n == '2':
        print("The connection is closed")
        s.close()
        exit()
      elif n == '3':
        # 并不立刻关闭，一直挂起客户端等待服务端发送信息回来
        while True:

          if not s.recv(1024).decode(encoding='utf8'):
            print("The server closed you client")
            exit()

          print("A message from server:",end=' ')
          print(s.recv(1024).decode(encoding='utf8'))

  except Exception as e:
    print("Some mistakes: ", e)
    if not s.recv(1024).decode(encoding='utf8'):
      print("The server closed you client")
      exit()




# input("")

# 待解决的问题： 当服务器关闭时客户端主动关闭
# 客户端发送消息关闭
# 关闭客户端时打印文字，正常关闭
