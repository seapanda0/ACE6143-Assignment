    # ESP32 UDP Echo Server with Simple Client Written in C

[ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#) is required to build the program for the ESP32. The [lwIP lightweight TCP/IP stack](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/lwip.html) library provided is used as it provides the commonly used BSD Sockets API such as `socket()` and `bind()`

For the client side, `sys/socket.h` is used and can be run on most operating systems.

## How to build
Build and flash the server firmware for the ESP32
```bash
cd server_esp32/
idf.py flash monitor
```
Build the client
```bash
cd client/
mkdir build
cmake -S . -B build
cmake --build build
```
Run the client 
```bash
./build/client
```

## How to use


## References
- [The GNU C Library - Sockets](https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_16.html#SEC300)
- [lwIP lightweight TCP/IP stack](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/lwip.html)
- [UDP Server Example](https://github.com/espressif/esp-idf/tree/v5.3.1/examples/protocols/sockets/udp_server)
- [UDP Socket Programming](https://users.cs.jmu.edu/bernstdh/web/common/lectures/summary_unix_udp.php)
