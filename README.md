## Họ và tên: Vũ Thuỳ Linh  
## MSSV: 24021548  
## Lớp: INT2215_7  

# Project: Snake Evolution

## Game Rules

1. Ấn **START** để bắt đầu trò chơi  
2. Bắt đầu chơi và điều khiển rắn

### *Các chức năng cơ bản*  
+ Sử dụng các phím mũi tên **trái / phải / trên / dưới** để điều khiển rắn  
+ Rắn có thể đi xuyên tường và xuất hiện ở phía đối diện  
+ Mỗi lần ăn mồi sẽ được cộng **1 điểm**  
+ Rắn **tăng tốc độ** theo mỗi level  
+ Nếu rắn **va vào tường hoặc thân mình** thì sẽ thua → Ấn **RESTART** để chơi lại  
+ Hệ thống sẽ **lưu lại điểm cao nhất (high score)**  

### *Cải tiến*  
+ Ấn phím **A** để kích hoạt **tốc biến** (dash) giúp đi xuyên thân hoặc tường  
  → **Thời gian hồi chiêu: 7s** sau mỗi lần dùng  
+ Khi bắt đầu, người chơi được cấp **3 viên đạn**  
  → Dùng phím **SPACE** để bắn  
  → Muốn hồi lại **1 viên đạn**, cần ăn **3 mồi**  
  → **Lưu ý**:  
    - Đạn **không xuyên tường**, nếu trúng tường sẽ biến mất nhưng **không trừ điểm**  
    - Nếu **trúng mồi** sẽ được cộng **10 điểm**  
    - Nếu **ra ngoài biên** sẽ bị **trừ 15 điểm**

+ Cứ mỗi lần ăn **5 mồi**, sẽ xuất hiện **hộp bí ẩn (mystery box)**  
  → Tự động biến mất sau **10s**  
  → Nếu ăn được sẽ **ngẫu nhiên**:  
    - Nhận hoặc mất điểm từ **-20 đến +30**  
    - Làm **giảm tốc độ rắn tạm thời**

+ **Tường di động (moving wall)**  
  → Di chuyển theo **chiều ngang**  
  → Tác dụng giống tường cố định  
  → Xuất hiện **ngẫu nhiên** sau mỗi **3 lần ăn mồi**

---

## References

+ Cách viết chữ trên nền: ChatGPT  
+ Hướng dẫn sử dụng thư viện `SDL_image`:  
  https://glusoft.com/sdl2-tutorials/display-image-sdl_image/
