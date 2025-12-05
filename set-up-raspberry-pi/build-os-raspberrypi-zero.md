Trong bài viết này chúng ta sẽ cùng nhau tìm hiểu cách cài OS Linux lên Raspberry Pi Zero W. Đây có thể coi như bước khởi đầu quan trọng khi làm việc với Raspberry Pi.

# 1. Các thiết bị phần cứng cần thiết.

Ở trong bài viết này sẽ hướng dẫn thông qua board Raspberry Pi Zero W:

![Pi zero](images/pi-zero-w.jpg)

Để flash image OS chúng ta cần :

- 1 thẻ nhớ SD 16gb trở lên + 1 thiết bị đọc thẻ:

![SD](images/sd.jpg)

- 1 dây cáp usb cấp nguồn:

![USB cap](images/usb.png)

# 2. Phần mềm cần cài đặt

Phía nhà sản xuất cung cấp phần mềm Rasberry Pi Imager giúp việc khởi tạo image OS đơn giản, không tốn nhiều thời gian. Các bạn có thể tải ở link sau : [Rasberry Pi Imager Software](https://www.raspberrypi.com/software/)

![Imager](images/imager.png)

Ngoài ra trong trường hợp không có màn hình và cáp hdmi ta cần tải các phần mềm kết nối ssh với Raspberry Pi như [**MobaXterm**](https://mobaxterm.mobatek.net/download.html) hoặc [**Putty**](https://putty.org/index.html).

# 3. Các bước tạo image OS 

Mở **Rasberry Pi Imager** và thực hiện các bước sau:

- **Bước 1** : Chọn loại board cần tạo image

![Bước 1](images/buoc-1.png)

- **Bước 2** : Lựa chọn loại OS cài đặt. Ở đây nhà sản xuất cung cấp nhiều loại OS với các tính năng bổ sung khác nhau, chi tiết xem tại đường dẫn sau [Raspberry Pi OS](https://www.raspberrypi.com/documentation/computers/os.html#get-raspberry-pi-os) .
Ở đây cơ bản chúng ta sẽ cài *Raspberry Pi OS 32 bit* được recommend:

![Bước 2](images/buoc-2.png)

- **Bước 3** : Cắm thẻ nhớ vào laptop và click chọn thẻ nhớ.

![Bước 3](images/buoc-3.png)

- **Bước 4** : Đặt hostname sẽ giúp bạn nhận ra thiết bị khi truy cập vào wifi.

![Bước 4](images/buoc-4.png)

- **Bước 5** : Cài location
  - Capital: Hanoi(Vietnam)
  - Time zone: Asia/Ho_Chi_Minh
  - Keyboard: us

- **Bước 6** : Cài username và password (nên cài password đơn giản ví dụ `1`)

![Bước 6](images/buo-6.png)

- **Bước 7** : Bật ssh

![Bước 7](images/buoc-7.png)

- **Bước 8** : Có thể bỏ qua Raspberry Pi Connect và bắt đầu Write image chọn *Erase and Write*

![Bước 8](images/buoc-8.png)

- **Bước 9**: Chờ imager hoàn thành và check lại trong thẻ SD như vậy chúng ta đã thành công tạo image OS.

# 4. Kết nối Rasberry Pi qua SSH

Sau khi flash image vào thẻ nhớ ta cắm thẻ nhớ vào Pi và cắp nguồn usb.

Đợi một lúc để Pi khởi động và kết nối wifi sau đó mở **Putty** để truy cập vào Pi (nhập hostname đã đặt trước đó):

![Putty 1](images/putty-1.png)

Tiếp theo nhập user và password đã cài trước đó:

![Putty 2](images/putty-2.png)

Kết nối thành công :

![Putty 3](images/putty-3.png)

***Note***: Trong trường hợp chưa thấy hostname để kiểm tra Raspberry Pi kết nối với wifi chưa chúng ta có thể check bằng phần mềm dò IP kết nối với mạng ví dụ như **Advanced IP Scaner**

![Ip Scan](images/ip-scan.png)

# 5. Kết luận

Như vậy trong bài viết này đã hướng dẫn cách build image OS cho Raspberry Pi Zero W mà không cần dùng màn hình và bàn phím.

