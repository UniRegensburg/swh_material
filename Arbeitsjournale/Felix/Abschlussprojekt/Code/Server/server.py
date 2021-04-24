from flask import Flask, request, render_template
from datetime import datetime
from time import strftime

app = Flask(__name__)

ref = 0
recs = []

@app.route('/', methods=["Get"])
def page():
    print(recs)
    return render_template(
        'page.html',
        values=recs
    )

@app.route('/value', methods=["POST"])
def value():
    json = request.get_json()

    v = json["value"]
    recs.append({"timestamp": get_time(), "value": v})
    return 'OK'

@app.route('/ref', methods=["POST"])
def reference():
    json = request.get_json()
    ref = json["value"]
    del recs[:]

    return 'OK'

@app.context_processor
def inject_values():
    return dict(recs=recs, ref=ref)


# Get the current time in the format: 2021-03-20T16:51:23.644+01:00
def get_time():
        datetime_now = datetime.utcnow()
        # Remove the microseconds
        datetime_now_ms = datetime_now.strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3]
        # Add the timezone as "+/-HHMM", and the colon in "+/-HH:MM"
        datetime_now_ms_tz = datetime_now_ms + strftime("%z")
        rfc3339_ms_now = datetime_now_ms_tz[:-2] + ":" + datetime_now_ms_tz[-2:]
        # print(f"Current time in ms in RFC-3339 format: {rfc3339_ms_now}")
        return rfc3339_ms_now

if __name__ == "__main__":
    app.run(debug=False, host='0.0.0.0')