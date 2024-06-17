import pygame
import time

axis_0_value=0.0
axis_1_value=0.0
button_0_state=0
button_1_state=0

def Send_Control_Data():
    X_Offset = int(axis_0_value*100)
    Y_Offset = int(axis_1_value * 100)
   # print(X_Offset)
   # print(Y_Offset)
    Data_List=[X_Offset,Y_Offset,button_0_state]
    print(Data_List)

if __name__ == '__main__':
    # 初始化Pygame
    pygame.init()
    pygame.joystick.init()

    # 检查是否有连接的操纵杆
    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        print("没有检测到操纵杆")
    else:
        # 初始化第一个操纵杆
        joystick = pygame.joystick.Joystick(0)
        joystick.init()
        print(f"检测到操纵杆：{joystick.get_name()}")
        print(f"轴数: {joystick.get_numaxes()}")
        print(f"按钮数: {joystick.get_numbuttons()}")
        print(f"hat数: {joystick.get_numhats()}")

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # 持续输出 Axis 0 和 Axis 1 的值
        axis_0_value = joystick.get_axis(0)
        axis_1_value = joystick.get_axis(1)

        # 持续输出 Button 0 和 Button 1 的状态
        button_0_state = joystick.get_button(0)
        button_1_state = joystick.get_button(1)
        Send_Control_Data()

        # 为了避免输出过快，可以适当休眠一段时间
        time.sleep(0.1)

# 退出Pygame
pygame.quit()
