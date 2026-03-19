import joblib
import numpy as np

model = joblib.load("../ml_model/flood_model.pkl")

def predict_flood(rain,water,temp,humidity):

    data = np.array([[rain,water,temp,humidity]])

    prediction = model.predict(data)[0]

    if prediction == 1:
        return "Danger"
    else:
        return "Safe"