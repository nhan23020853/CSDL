import socket
import struct
import time

ESP_IP = '192.168.4.1'
PORT = 8080

def read_exact(sock, length):
    data = b''
    while len(data) < length:
        packet = sock.recv(length - len(data))
        if not packet: return None
        data += packet
    return data

while True:
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.settimeout(3.0) 
        client.connect((ESP_IP, PORT))
        client.settimeout(None) 
        print("[OK] Đã kết nối WiFi. Đang lắng nghe Telemetry...")

        while True:
            sof = read_exact(client, 1)
            if not sof: break 
                
            if sof == b'\xaa':
                rest = read_exact(client, 18)
                if not rest: break
                    
                msg_id, length = rest[0], rest[1]
                payload = rest[2:16]
                checksum_byte, eof_byte = rest[16], rest[17:18]
                
                if eof_byte == b'\x55' and msg_id == 1 and length == 14:
                    calc_cs = msg_id ^ length
                    for b in payload: calc_cs ^= b
                        
                    if calc_cs == checksum_byte:
                        sensors = struct.unpack('>HHHHH', payload[:10])
                        line_error = struct.unpack('<f', payload[10:14])[0]
                        print(f"Cam bien: {sensors} | Loi (Error): {line_error:+.2f}")

    except Exception as e:
        print(f"[CẢNH BÁO] Rớt kết nối ({e}). Đang thử lại...")
        time.sleep(2)