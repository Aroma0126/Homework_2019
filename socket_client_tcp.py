
# 客户端
import socket
import json

s = None

def init():
  global s
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  host = socket.gethostname()
  port = 12346

  try:
    s.connect((host,port)) # 定义连接
  except Exception as e:
    print("连接服务器失败",e)
    exit(-1)

def login():
  # 发送登陆信息
  name = input("input name: ")
  password = input("input password: ") # python 的getpass模块只能在指定ide中才起作用，故这里依然明文显示
  client_info = json.dumps({'name':name, 'password':password}).encode('utf-8')
  s.send(client_info)

  msg = s.recv(1024).decode(encoding='utf-8') # 大坑！！！！！！！！！！！
  # 只会接收一次，用msg去装载，如果先接受信息，再去赋值给msg那么就赋值失败了
  # 接收TCP数据，数据以字符串形式返回，参数指定要接收的最大数据量(BUFSIZE)
  print(msg)

  if msg == 'name or password is incorrect!':
    exit()

  s.sendall('Connected!'.encode(encoding='utf-8'))


def get_message():

  while True: # 不断接收消息
    data = s.recv(1024).decode(encoding='utf-8')
    if data == 'close':
      print('The server closed your client!')
      s.close()
      exit()
    if not data:
      break
    print("\nA message from server:", end=' ')
    print(data)
    break



if __name__ == '__main__':

  init()
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
      get_message()
    elif n == '2': # 发送exit可自动退出
      message = input("input you message here: ")
      s.sendall(message.encode(encoding='utf-8'))
      data = s.recv(1024).decode(encoding='utf-8')
      if data == 'close':
        print('The server closed your client!')
        s.close()
        exit()
    elif n == '3':
      print("The connection is closed")
      s.close()
      exit()


# 待解决的问题： 当服务器关闭时客户端主动关闭
# 针对上面一个问题，即服务器关闭了而客户端不能
# 立即接收到，只能等到客服端主动发起动作的时候才能收到关闭的信息
# 解决：利用心跳包检测
#
# 客户端发送消息关闭
# 关闭客户端时打印文字，正常关闭
