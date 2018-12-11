# CS190-Project
Package Alert System using Seeduino

app.ino - Main file where the program execution happens

config.h - File for all the constants we defined and used throughout the code

credentials.ino - Credential checking and sending for WiFi connectivity

iotHubClient.ino - sends the data to the iot hub

message.ino - reads data from the FSR sensor

serialReader.ino - using only initSerial()


All the data is sent real time to the IoT Hub set up and the link to its visualization is:

https://app.powerbi.com/view?r=eyJrIjoiMmZlZjNmOTktZGU3ZS00YzI4LTgxNTEtZWE2ODIzMTBlZDhkIiwidCI6IjNlOTY2YjVkLWE2YzQtNGE0NC04MTMzLTgyMWVjNDc2OTdhMyIsImMiOjF9


Most of the code used is just a modified version of the code from what we saw in the tutorial for demo4 - 

https://docs.microsoft.com/en-us/azure/iot-hub/iot-hubsparkfun-esp8266-thing-dev-get-started

