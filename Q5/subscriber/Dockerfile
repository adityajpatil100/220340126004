FROM node:alpine
WORKDIR /usr/Jeet/subscriber
COPY subscriber.js /usr/Jeet/subscriber
RUN npm install mqtt
CMD ["node", "subscriber.js"]

# mosquitto_pub -t "test/sensor-data" -h localhost -p 6502 -f /home/diot/Desktop/Vishwajit/Q5/data.json
# This command will send the .json file to the subscriber