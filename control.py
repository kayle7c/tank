import socket,math
import gps_turn 
import time
import threading
import select

poll_obj = select.poll()

service1_client_socket="None"
service2_client_socket="None"


def is_socket_connected(socket_obj):
    try:
        socket_obj.sendall(b"Heartbeat\n")  # 发送心跳消息
        # print(1)
    except Exception as e:
        print("Error sending heartbeat:", e)
        return False
    
def connect1():
    print("手柄连接!")
    global service1_client_socket,service2_client_socket,poll_obj
    tcp_server1_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server1_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    tcp_server1_socket.bind(("0.0.0.0", 9000))
    tcp_server1_socket.listen(4)
    service1_client_socket, ip_port = tcp_server1_socket.accept()
    print("客户端的ip地址和端口号:", ip_port)
    service2_client_socket, ip_port = tcp_server1_socket.accept()
    print("客户端的ip地址和端口号:", ip_port)
    service1_client_socket.send("1".encode("utf-8"))


def check_server1_state():
    global connect_num
    print("手柄连接成功!")
    while True:
        print(connect_num)
        if is_socket_connected(service1_client_socket) == False:
            connect_num-=1
            print(connect_num)
            service1_client_socket.close()
            connect1()
            connect_num+=1
        time.sleep(3)    



if __name__ == '__main__':
    connect1()
    time.sleep(3)
    print("已连接")
    while True:
        service1_client_socket.send("1".encode("utf-8"))
        recv_data = service1_client_socket.recv(1024)
        print(recv_data)
        service2_client_socket.send(recv_data)
