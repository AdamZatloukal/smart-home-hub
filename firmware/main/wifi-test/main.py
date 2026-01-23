import requests
import sys
from PIL import ImageColor

esp32_ip = "10.0.0.16" # enter the ip of you esp32
post_url_color = f"http://{esp32_ip}/set/color"
post_url_brightness = f"http://{esp32_ip}/set/brightness"
post_url_speed = f"http://{esp32_ip}/set/speed"
post_url_mode = f"http://{esp32_ip}/set/mode"

json_path = "colors.json"

command = sys.argv[1]

try:
    if command == "set-color":
        colorHEX = sys.argv[2]
        colorsRGB = ImageColor.getcolor(colorHEX, "RGB")

        colorsObj = {
            "red": colorsRGB[0],
            "green": colorsRGB[1],
            "blue": colorsRGB[2]
        }

        # .post automaticly turns the dictionary into json
        response = requests.post(post_url_color, json = colorsObj, timeout= 5)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")

    elif command == "set-brightness":
        brightness = sys.argv[2]

        brightnessObj = {
            "brightness" : brightness
        }

        # .post automaticly turns the dictionary into json
        response = requests.post(post_url_brightness, json = brightnessObj, timeout= 5)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
    
    elif command == "set-speed":
        speed = sys.argv[2]

        speedObj = {
            "speed" : speed
        }

        # .post automaticly turns the dictionary into json
        response = requests.post(post_url_speed, json = speedObj, timeout= 5)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")
    
    elif command == "set-mode":
        mode = sys.argv[2]

        modeObj = {
            "mode" : mode
        }

        # .post automaticly turns the dictionary into json
        response = requests.post(post_url_mode, json = modeObj, timeout= 5)
        print(f"Status code: {response.status_code}\nText: {response.text}\n")

    elif command == "help":
        print("set-color    Takes a HEX color turns it into RGB puts it into a JSON object\n" \
        "                   and sends it. Example use: py main.py set-color #FF00FF \n" \
        "                   in powershell '#FF00FF'")
        print("set-brightness   takes uint8_t")
        print("set-speed    takes uint16_t")
        print("set-mode     takes uint8_t")

except Exception as e:
    print(e)    