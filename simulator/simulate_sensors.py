import requests
import random
import time

server_url = "http://127.0.0.1:5000/predict"

while True:

    # simulate sensor values
    rain = random.randint(0,2500)
    temp = random.randint(20,32)
    humidity = random.randint(60,95)
    water = random.randint(10,60)

    payload = {
        "rain": rain,
        "temp": temp,
        "humidity": humidity,
        "waterLevel": water
    }

    response = requests.post(server_url,json=payload)

    print("Sent Data:",payload)
    print("Prediction:",response.text)
    print("-------------")

    time.sleep(3)