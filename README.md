# ESP32 UDP Echo Server with Simple Client Written in C

[ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#) is required to build the program for the ESP32. The [lwIP lightweight TCP/IP stack](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/lwip.html) library provided is used as it provides the commonly used BSD Sockets API such as `socket()` and `bind()`

For the client side, `sys/socket.h` is used and can be run on most operating systems.

## How to build
Add your WiFi SSID and password in the `server_esp32/main/wifi.h`
```C
#define EXAMPLE_ESP_WIFI_SSID      "YOUR_SSID"
#define EXAMPLE_ESP_WIFI_PASS      "YOUR_PASSWORD"
```

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


## How to use
Start the serial monitor
```
idf.py monitor
```
The ESP32's IP Address can be obtained from the debug info
```
I (10748) esp_netif_handlers: sta ip: 192.168.100.62, mask: 255.255.255.0, gw: 192.168.100.1
I (10748) wifi station: got ip:192.168.100.62

```
Start another terminal session to run the client
```bash
./client/build/client
```

After running the `client` binary, it will request for the IP address of the server and port, by default the server will run on port 2000
```
Enter port: 2000
Enter address: 192.168.100.62 (change to the ESP32 IP address)
```
You can start typing in the client and press enter to send it to the server. The response from the server will be printed as well
```
You: ls 
Server: ls

You: test
Server: test

```

## Screenshots

![Server & Client Program Running][ss-1]

[ss-1]:https://i.imgur.com/8hUXGd7.png "INTRO"


## References
- [The GNU C Library - Sockets](https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_16.html#SEC300)
- [lwIP lightweight TCP/IP stack](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/lwip.html)
- [UDP Server Example](https://github.com/espressif/esp-idf/tree/v5.3.1/examples/protocols/sockets/udp_server)
- [UDP Socket Programming](https://users.cs.jmu.edu/bernstdh/web/common/lectures/summary_unix_udp.php)
