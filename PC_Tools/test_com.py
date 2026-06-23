import serial

# Nhớ sửa COM5 thành cổng COM mạch CH340 của bạn
try:
    ser = serial.Serial('COM10', 9600) 
    print("Đã mở cổng COM thành công! Đang chờ dữ liệu...")
    while True:
        if ser.in_waiting > 0:
            # Đọc và in thẳng ra màn hình
            data = ser.readline()
            print(data.decode('utf-8', errors='ignore').strip())
except Exception as e:
    print(f"Lỗi: {e}")