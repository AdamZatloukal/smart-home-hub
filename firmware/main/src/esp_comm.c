#include "esp_now.h"
#include "esp_log.h"
#include "stdlib.h"
#include "esp_comm.h"

void send_cb(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    ESP_LOGI("ESPNOW", "Send status: %s",
             status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void recv_cb(const esp_now_recv_info_t *info,
             const uint8_t *data, int len)
{
    ESP_LOGI("ESPNOW", "Packet from: %02X:%02X:%02X:%02X:%02X:%02X",
             info->src_addr[0], info->src_addr[1], info->src_addr[2],
             info->src_addr[3], info->src_addr[4], info->src_addr[5]);

    ESP_LOGI("ESPNOW", "Data: %.*s", len, data);
    printf("%s", (char *)data);
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
    uint8_t peer_mac_addr[6]= {0x98, 0x88, 0xE0, 0x14, 0xCE, 0xE8};    // MAC address of the receiver
    memcpy(peer->peer_addr, peer_mac_addr, 6);
    peer->channel = 0;
    peer->ifidx = WIFI_IF_STA;
    peer->encrypt = false;
    esp_now_add_peer(peer);
    free(peer);   
}