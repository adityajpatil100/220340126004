var mqtt = require('mqtt')
const client = mqtt.connect("mqtt://broker:1883")

var topic = "test/sensor-data"

client.on("connect", function(res, err) {
    if(err) {
        console.log(err)
    } else {
        console.log("Successfully connected to broker!")
        client.subscribe(topic, function(err) {
            if(err) {
                console.log(err)
            } else {
                console.log("Successfully subscribed!")
            }
        })
    }
})

client.on("message", function(topic, data) {
    console.log(data.toString())
})