# ESP32_WOL_Server

Wake your PC via ESP32 controller

```sh
curl --location --request POST 'http://<esp32_ip_address>/wake' --header 'Content-Type: text/plain' --data-raw '{ "wake": 1, }'
```
