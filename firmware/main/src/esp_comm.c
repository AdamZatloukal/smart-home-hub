#include "esp_now.h"

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    ESP_LOGI("ESPNOW", "Send status: %s",
             status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void recv_cb(const esp_now_recv_info_t *info,
             const uint8_t *data, int len)
{
    ESP_LOGI("ESPNOW", "Received %d bytes", len);
}

/* wifi must be started before esp now is initialized*/
void esp_now_setup(void)
{
    esp_now_init();

    esp_now_register_send_cb(send_cb); // will be called when we send data
    esp_now_register_recv_cb(recv_cb); // esp_now_recv_callback will be called when we receive data

    //esp_now_set_pmk((uint8_t *)"smart-hh-key123"); // primary master key encrypts local master key which encripts esp now data
    
    esp_now_peer_info_t *peer = malloc(sizeof(esp_now_peer_info_t));

    /* fill the peer with 0s to be sure we dont have garbage values*/
    memset(peer, 0, sizeof(esp_now_peer_info_t));

    /* peer params*/
    uint8_t peer_mac_addr[6]= {0x14, 0x33, 0x5C, 0x66, 0x60, 0x68};    // MAC address of the receiver
    memcpy(peer->peer_addr, peer_mac_addr, 6); // set tje mac address of the peer
    peer->channel = 0;
    peer->ifidx = WIFI_IF_STA;
    peer->encrypt = false;
    esp_now_add_peer(peer);
    free(peer);   

    char msg[] = "Hello ESP-NOW";
    esp_now_send(peer->peer_addr, (uint8_t *)msg ,sizeof(msg));
}