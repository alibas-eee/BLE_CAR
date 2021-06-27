# BLE_CAR
bluetooth car arduino code

ble uses bluetooth 4.0 need to add external aix file to app_inventor
ble module can work up to 5v but rx pin should 3.3v otherwise harmfull for moduel but tx pin can connect directly arduino
arduino can read over 1.8v as high voltage 
i connect 3s lipo battery to power car 2s pin goes to arduino raw pin 3s pin goes to motor power supply pin
arduino and ble uses very low current so internal regulator work fine in arduino pro mini

in arduino code there is software filter for motor control it keep an a whie command but not for direction control

video: https://www.youtube.com/watch?v=uACv1qKzi1w&t=44s
