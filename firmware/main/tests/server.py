from flask import Flask, request
import matplotlib.pyplot as plt
import datetime as dtm
import numpy as np


from flask import send_file
import io

times = []
values = []


app = Flask(__name__)

@app.route("/plot")
def plot():
    fig, ax = plt.subplots()
    ax.plot(times, values)
    ax.set_xlabel("Time")
    ax.set_ylabel("Sample value")
    buf = io.BytesIO()
    fig.savefig(buf, format="png")
    buf.seek(0)
    plt.close(fig)
    return send_file(buf, mimetype="image/png")

@app.route("/upload", methods=["POST"])
def upload():
    data = request.data
    with open("data-samples.raw", "ab") as file:
        file.write(data)
        print(f"wrote {request.content_length} bytes into {file.name}")
        now = dtm.datetime.now()
        samples = np.frombuffer(data, dtype=np.int32)
        times.extend([now] * len(samples))
        values.extend(samples.tolist())
    return "OK", 200

if __name__ == "__main__":
    app.run(host="0.0.0.0", port= 8080)