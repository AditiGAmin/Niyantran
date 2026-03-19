from flask import Flask,request,jsonify
from model_loader import predict_flood
import csv
from datetime import datetime

app = Flask(__name__)

@app.route('/predict',methods=['POST'])

def predict():

    data = request.get_json()

    rain = data['rain']
    water = data['waterLevel']
    temp = data['temp']
    humidity = data['humidity']

    risk = predict_flood(rain,water,temp,humidity)

    with open('../data_logs/sensor_data.csv','a',newline='') as f:
        writer = csv.writer(f)
        writer.writerow([datetime.now(),rain,water,temp,humidity,risk])

    return jsonify({"risk":risk})


if __name__ == '__main__':
    app.run(host="0.0.0.0",port=5000)