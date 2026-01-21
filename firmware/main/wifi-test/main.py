import requests
import json
import sys

esp32_ip = "10.0.0.28" # enter the ip of you esp32
post_url = f"http://{esp32_ip}/data/colors"
get_url_on = f"http://{esp32_ip}/led/on"
get_url_off = f"http://{esp32_ip}/led/off"
json_path = "colors.json"

command = sys.argv[1]


try:
    if command == "led_on":
        response = requests.get(get_url_on)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
        
    elif command == "led_off":
        response = requests.get(get_url_off)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
    
    elif command == "data_colors":
        with open(json_path, "r") as file:
            payload = json.load(file)

        response = requests.post(post_url, json = payload)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")

except Exception as e:
    print(e)    