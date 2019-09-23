
import wx

def login(event):
  n = name.GetValue()
  p = password.GetValue()
  if n == 'test' and p == '111':
    context.SetValue('welcome')
  else:
    context.SetValue('name or pwd is incorrect')

# 构建一个新窗体
app = wx.App(False)
frame = wx.Frame(None, title="Login Page", size=(410, 335))
frame.Show()
# 定义两个输入框
name = wx.TextCtrl(frame, pos=(35, 5), size=(210, 25))
password = wx.TextCtrl(frame, pos=(35, 35), size=(210, 25))
# 定义按钮 绑定事件
login_Button = wx.Button(frame, label='login', pos=(65, 65), size=(80, 25))
login_Button.Bind(wx.EVT_BUTTON, login)
# 定义打印台
context = wx.TextCtrl(frame, pos=(35, 100), size=(300, 300))

app.MainLoop()
