# 服务器端/创建服务
import socket
import threading
import json
import tkinter as tk
import tkinter.messagebox

s = None
connection_pool = list()
flag = 0

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
    t1.insert('end', 'The client ' + str(address[1]) + ' has connected!' + '\n')
  else:
    s.sendto("name or password is incorrect!".encode('utf-8'), address)


def get_mes():
  while True:
    global address
    data, address = s.recvfrom(1024)
    string = data.decode('utf-8')
    print('str:',str)
    if string[0] == '{':
      verify_info(data)
    elif string == 'close':
        t1.insert('end', 'The port ' + str(address[1]) + ' has closed!' + '\n')
        t1.see('end')
        index = 0
        for i in range(len(address_index_list)):
            k = int(address_index_list[i])
            if k == address[1]:
                index = i
                break
        del connection_pool[index]
    else:
      print("recieve from port: ",address[1],end=" ")
      print("message is: ",data)
      t1.insert('end','message form port '+str(address[1])+' : '+string+'\n')
      t1.see('end')

def send_message():
    port = imf.get()
    message = msg.get()
    index = 0
    for i in range(len(address_index_list)):
        k = int(address_index_list[i])
        if k == int(port):
            index = i
            break
    if index < len(address_index_list):
        s.sendto(message.encode(encoding='utf8'), connection_pool[index])
        t1.insert('end', 'message send to ' + port + ' : ' + message + '\n')
        t1.see('end')
    else:
        tk.messagebox.showerror('错误','该客户端不存在！')
    imf.set('')
    msg.set('')

def online_number():
  num=str(len(connection_pool))
  t1.insert('end','Online number is : '+num+'\n')
  t1.see('end')

def client_close():
  close_port = imf.get()
  msg = 'close'
  for i in range(len(address_index_list)):
      k = int(address_index_list[i])
      if k == int(close_port):
          index = i
          break
  s.sendto(msg.encode(encoding='utf8'), connection_pool[index])
  del connection_pool[index]  # delete the port
  print(address_index_list)
  print(close_port)
  address_index_list.remove(int(close_port))
  t1.insert('end','The server has closed '+str(close_port)+'\n')
  t1.see('end')
  imf.set('')

def close():
  t = 'the server has closed!'
  for i in range(len(address_index_list)):
      s.sendto(t.encode(encoding='utf8'), connection_pool[i])
  s.close()
  window.destroy()



if __name__ == '__main__':

  init()
  thread = threading.Thread(target=get_mes)
  thread.setDaemon(True)
  thread.start()

  window = tk.Tk()
  window.title('服务器界面')
  window.geometry('400x400')

  t1 = tk.Text(window, height=15, width=50)
  t1.pack()
  imf = tk.StringVar()
  tk.Label(window, text='端口号:', font=('Arial', 10)).place(x=22, y=210)
  btn_close_client = tk.Button(window, width=12, text='关闭该客户端', command=client_close)
  btn_close_client.place(x=250, y=203)
  t2 = tk.Entry(window, width=20, textvariable=imf).place(x=75, y=210)
  msg = tk.StringVar()
  tk.Label(window, text='消息:', font=('Arial', 10)).place(x=22, y=240)
  t3 = tk.Entry(window, width=40, textvariable=msg).place(x=75, y=240)
  btn_send = tk.Button(window, width=30, text='发送', command=send_message)
  btn_send.place(x=80, y=270)
  btn_number = tk.Button(window, width=30, text='查询在线客户数', command=online_number)
  btn_number.place(x=80, y=310)
  btn_close = tk.Button(window, width=30, text='关闭服务器', command=close)
  btn_close.place(x=80, y=350)
  window.mainloop()
