import serial
import time

# Đổi lại tên cổng COM và Baudrate cho đúng với máy của bạn
COM_PORT = 'COM12' 
BAUD_RATE = 115200

def main():
    try:
        # Mở cổng Serial
        ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
        print(f"[*] Đã kết nối thành công tới {COM_PORT}.")
        print("[*] Đang đọc dữ liệu...\n" + "-"*40)
        
        while True:
            # Đọc từng dòng dữ liệu (nhận diện bằng ký tự \n)
            if ser.in_waiting > 0:
                line = ser.readline()
                try:
                    # Giải mã byte thành chuỗi String và in ra
                    decoded_line = line.decode('utf-8').strip()
                    print(decoded_line)
                except UnicodeDecodeError:
                    pass # Bỏ qua nếu có byte rác lúc mới cắm dây
                    
    except serial.SerialException:
        print(f"[!] Không thể mở cổng {COM_PORT}. Hãy kiểm tra lại dây cắm!")
    except KeyboardInterrupt:
        print("\n[*] Đã đóng chương trình.")
        ser.close()

if __name__ == "__main__":
    main()