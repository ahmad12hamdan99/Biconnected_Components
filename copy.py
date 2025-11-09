# recv.py
from pymavlink import mavutil

# Listen on UDP port 14550 on all interfaces
mav = mavutil.mavlink_connection('udpin:0.0.0.0:14550')

print("Waiting for MAVLink messages on 0.0.0.0:14550...")
while True:
    msg = mav.recv_match(blocking=True, timeout=5)
    if msg is not None:
        print(msg)
