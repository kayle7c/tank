import socket,math
import gps_turn 
import time
import threading
import select

poll_obj = select.poll()

service1_client_socket="None"
service2_client_socket="None"
connect_num=0

def is_socket_connected(socket_obj):
    try:
        socket_obj.sendall(b"Heartbeat\n")  # 发送心跳消息
        # print(1)
    except Exception as e:
        print("Error sending heartbeat:", e)
        return False

    

    
def connect1():
    print("下位机连接!")
    global service1_client_socket,poll_obj
    tcp_server1_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server1_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    tcp_server1_socket.bind(("0.0.0.0", 8000))
    tcp_server1_socket.listen(4)
    service1_client_socket, ip_port = tcp_server1_socket.accept()
    print("客户端的ip地址和端口号:", ip_port)

    # send_data = "Successful connect! \n".encode("gb2312")
    # service1_client_socket.send(send_data)


def connect2():
    print("上位机连接!")
    global service2_client_socket
    tcp_server2_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server2_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    tcp_server2_socket.bind(("0.0.0.0", 7000))
    tcp_server2_socket.listen(4)
    service2_client_socket, ip_port = tcp_server2_socket.accept()
    poll_obj.register(service2_client_socket.fileno(),select.POLLHUP | select.POLLERR)
    print("客户端的ip地址和端口号:", ip_port)

def check_server1_state():
    global connect_num
    while True:
        print(connect_num)
        if is_socket_connected(service1_client_socket) == False:
            connect_num-=1
            print(connect_num)
            service1_client_socket.close()
            connect1()
            connect_num+=1
        time.sleep(3)    

def check_server2_state():
    global connect_num
    while True:
        if is_socket_connected(service2_client_socket) == False:
            connect_num-=1
            service2_client_socket.close()
            connect2()
            connect_num+=1
        time.sleep(3)   


if __name__ == '__main__':
    connect1()
    connect2()
    connect_num=2
    threading.Thread(target=check_server1_state, daemon=True).start()
    threading.Thread(target=check_server2_state, daemon=True).start()
    while True:
        if(connect_num<2):
            continue
        else:
            #print(1)
            time.sleep(1)
            break
    while True:
        if(connect_num<2):
            continue
        recv_data = service1_client_socket.recv(1024)
        if recv_data != b'': 
            print(recv_data)
        try:
            data = recv_data.decode("utf-8").split('\r')
            timedata = data[0]
            hours = (int(timedata[0:2]) + 8) % 24
            minutes = int(timedata[2:4])
            seconds = int(timedata[4:6])

            latitude = float(data[1][0:2]) + float(data[1][2:])/60
            longitudedata = float(data[2][0:3]) + float(data[2][3:])/60
            
            time = str(hours) + ":" + str(minutes) + ":" + str(seconds)
            longitudedata, latitude = gps_turn.wgs84_to_gcj02(float(longitudedata), float(latitude))
            gps_data= str(time) + "*" + str(longitudedata) + "*" + str(latitude) + '\n'
            gps_data=gps_data.encode("gb2312")
            print(gps_data)
            service2_client_socket.send(gps_data)

        except:
            pass

