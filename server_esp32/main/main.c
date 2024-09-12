#include "wifi.h"
#include <math.h>

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#define PORT 2000

const char *TAG = "Client";

void udp_server_task(){
    char rx_buffer[128] = {0};

    // Create the sockets
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0){
        ESP_LOGE(TAG, "Unable to create socket");
        while(1){}
    };
    ESP_LOGI(TAG, "Socket Created");

    struct sockaddr_in source_addr = {0};
    socklen_t socklen = sizeof(source_addr);

    // Bind the socket
    struct sockaddr_in dest_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0){
        ESP_LOGE(TAG, "Socket unable to bind");
        while(1){}
    }
    ESP_LOGI(TAG, "Socket Binded");
    
    // Simple echo server
    while(1){
        recvfrom(sock, rx_buffer, sizeof(rx_buffer), 0,(struct sockaddr *)&source_addr, &socklen);
        
        // Shut down the server if an empty string is sent from the client
        if(rx_buffer[0]== '\0'){
            ESP_LOGI(TAG,"Shutting down echo server");
            shutdown(sock, SHUT_RDWR);
            break;
        }
        
        ESP_LOGI(TAG, "%s", rx_buffer);
        sendto(sock, rx_buffer, sizeof(rx_buffer), 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
        memset(rx_buffer,0,sizeof(rx_buffer));
    }
    // Delete the task
    vTaskDelete(NULL);


}

void app_main(void)
{
    // Initialize wifi
    wifi_init_sta();

    // Create the udp server task
    xTaskCreate(udp_server_task, "udp_server", 4096, NULL, 5, NULL);
}