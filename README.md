# esp8266-SerialOTA
Current version of ArduinoOTA for esp8266 does not allow to get serial messages when the modules is not connected physically
The class SerialOTA accepts telnet connection (port 23) and broadcast any message to any connected client when the function serialOTA.println is call
So far function only accepts const char*.
In future version all println accepted by Serial should be replicated
A elegant way to replace Serial by SerialOTA and make the operation transparent to user is to be found: so far I use a #define to replace at compliation Serial by SerialOTA....
maybe not that great ?
