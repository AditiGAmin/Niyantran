import pandas as pd
from sklearn.ensemble import RandomForestClassifier
import joblib

data = pd.read_csv("dataset.csv")

X = data[['rain','water_level','temperature','humidity']]
y = data['flood']

model = RandomForestClassifier()
model.fit(X,y)

joblib.dump(model,"flood_model.pkl")

print("Model trained and saved")