import requests
import json
import sys
from PIL import ImageColor

esp32_ip = "10.0.0.28" # enter the ip of you esp32
post_url = f"http://{esp32_ip}/set/color"
get_url_on = f"http://{esp32_ip}/led/on"
get_url_off = f"http://{esp32_ip}/led/off"
json_path = "colors.json"

command = sys.argv[1]

try:
    if command == "led-on":
        response = requests.get(get_url_on)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
        
    elif command == "led-off":
        response = requests.get(get_url_off)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
    
    elif command == "set-color":
        colorHEX = sys.argv[2]
        colorsRGB = ImageColor.getcolor(colorHEX, "RGB")

        colorsObj = {
            "red": colorsRGB[0],
            "green": colorsRGB[1],
            "blue": colorsRGB[2]
        }

        # .post automaticly turns the dictionary into json
        response = requests.post(post_url, json = colorsObj)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
    
    elif command == "help":
        print("led-on       Turns on an LED")
        print("led-off      Turns off an LED")
        print("set-color    Takes a HEX color turns it into RGB puts it into a JSON object\n" \
        "                   and sends it. Example use: py main.py set-color #FF00FF \n" \
        "                   in powershell '#FF00FF'")

except Exception as e:
    print(e)    