import socket
import json
import tkinter as tk  # 使用Tkinter前需要先导入
from tkinter import messagebox
import threading

s = None
flag = 0
flag2 = 0

def init():
    global s
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = socket.gethostname()
    port = 12346
    try:
        s.connect((host, port))  # 定义连接
        print(s)
    except Exception as e:
        print("连接服务器失败", e)
        exit(-1)

def login():
    # 发送登陆信息
    global flag
    init()
    name = var_usr_name.get()
    print('type:', type(name))
    password = var_usr_pwd.get()
    client_info = json.dumps({'name': name, 'password': password}).encode('utf-8')
    s.send(client_info)
    msg = s.recv(1024).decode(encoding='utf-8')
    print(msg)
    if msg == 'name or password is incorrect!':
        tk.Label(window, text='用户名或密码错误!', font=('Arial', 14)).place(x=110, y=190)
        var_usr_name.set('')
        var_usr_pwd.set('')
        flag = 0
    else:
        tk.Label(window, text='登陆成功!', font=('Arial', 14)).place(x=120, y=190)
        window.destroy()
        flag = 1


def get_message():
    global flag2
    while True:
        data = s.recv(1024).decode(encoding='utf-8')
        print('get message:', data)
        if data == 'close':
            flag2 = 2
            gui.Text.insert('end', 'The server has closed you!'+ '\n')
            gui.Text.see('end')
            messagebox.showinfo('提示', '服务器已关闭你的客户端！')

            s.close()
        elif data == 'the server has closed!':
            flag2 = 1
            gui.Text.insert('end', 'The server has closed!' + '\n')
            gui.Text.see('end')
            messagebox.showinfo('提示', '服务器已关闭！')
        else:
            gui.Text.insert('end', 'message from the server : ' + data + '\n')
            gui.Text.see('end')

class GUI:
  def __init__(self, root):
    self.root = root
    self.Text = tk.Text(self.root, height=15, width=50)
    self.Text.pack()
    self.Text.insert('end','Connected Successfully!'+'\n')
    tk.Label(self.root, text='消息:', font=('Arial', 10)).place(x=22, y=210)
    self.msg = tk.StringVar()
    self.entry = tk.Entry(self.root, width=40,textvariable=self.msg).place(x=75, y=210)
    self.btn_send = tk.Button(self.root, width=30, text='发送', command=self.send)
    self.btn_send.place(x=80, y=240)
    # self.btn_close = tk.Button(self.root, width=30, text='关闭客户端', command=self.close)
    self.btn_close = tk.Button(self.root, width=30, text='关闭客户端', command=lambda:self.close(root))
    self.btn_close.place(x=80, y=280)

  def send(self):
    if flag2 == 0:
        send_data = self.msg.get()
        self.Text.insert('end', 'message send to the server : ' + send_data + '\n')
        self.Text.see('end')
        s.send(send_data.encode())
        self.msg.set('')
    elif flag2 == 1:
        self.msg.set('')
        tk.messagebox.showerror('错误', '服务器已关闭！')
    elif flag2 == 2:
        self.msg.set('')
        tk.messagebox.showerror('错误', '服务器已关闭你的客户端！')

  def close(self,root):
      send_data = 'close'
      s.send(send_data.encode())
      s.close()
      root.destroy()
      exit()

def createGUI():
  global gui
  root = tk.Tk()
  gui = GUI(root)
  root.geometry('400x320')
  root.title('客户端')
  root.mainloop()

if __name__ == '__main__':
    window = tk.Tk()
    window.title('客户登陆窗口')
    window.geometry('400x400')

    tk.Label(window, text='User name:', font=('Arial', 14)).place(x=30, y=115)
    tk.Label(window, text='Password:', font=('Arial', 14)).place(x=30, y=155)

    var_usr_name = tk.StringVar()
    entry_usr_name = tk.Entry(window, textvariable=var_usr_name, font=('Arial', 14))
    entry_usr_name.place(x=140, y=120)

    var_usr_pwd = tk.StringVar()
    entry_usr_pwd = tk.Entry(window, textvariable=var_usr_pwd, font=('Arial', 14), show='*')
    entry_usr_pwd.place(x=140, y=160)

    btn_login = tk.Button(window, width=30, text='Login', command=login)
    btn_login.place(x=90, y=220)
    window.mainloop()

    if (flag == 1):
        t1 = threading.Thread(target=get_message, args=(), name='get_message')
        t2 = threading.Thread(target=createGUI, args=(), name='gui')
        t1.start()
        t2.start()
