import serial

# Thay đổi COM cho khớp với mạch USB-to-TTL của bạn
try:
    ser = serial.Serial('COM10', 9600)
    print("Đang lắng nghe cổng COM... (Ctrl+C để thoát)")
    
    while True:
        if ser.in_waiting > 0:
            # Đọc 1 byte và chuyển thành dạng Hex (VD: 'aa', '01')
            raw_byte = ser.read(1)
            hex_value = raw_byte.hex().upper()
            
            # In ra màn hình trên cùng một dòng, cách nhau bởi khoảng trắng
            print(f"{hex_value}", end=" ", flush=True)
            
            # Nếu gặp byte EOF (0x55), tự động xuống dòng cho dễ nhìn
            if hex_value == "55":
                print() 

except Exception as e:
    print(f"Lỗi: {e}")