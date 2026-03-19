import streamlit as st
import pandas as pd

st.set_page_config(page_title="Flood Monitor", layout="wide")

st.title("🌊 Flood Prediction Monitoring Dashboard")

data_file = "../data_logs/sensor_data.csv"

data = pd.read_csv(data_file)

# Remove index column if present
if "Unnamed: 0" in data.columns:
    data = data.drop(columns=["Unnamed: 0"])

st.subheader("Latest Sensor Data")
st.dataframe(data.tail())

col1, col2 = st.columns(2)

with col1:
    st.subheader("Rainfall Trend")
    if "rain" in data.columns:
        st.line_chart(data["rain"])

with col2:
    st.subheader("Water Level Trend")
    if "water_level" in data.columns:
        st.line_chart(data["water_level"])

st.subheader("Flood Risk Count")

if "risk" in data.columns:
    risk_counts = data["risk"].value_counts()
    st.bar_chart(risk_counts)