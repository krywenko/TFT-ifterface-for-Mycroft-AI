# TFT-ifterface-for-Mycroft-AI

for those who might want to add AI to Open Energy Monitoring project.
here a sketch for driving TFT_eSPI compatible screen also compatible RA8875 screen ( just point it away from the TFT-eSPI libary and point it at RA8875 library)
it based on my other TFT graphing sketches so you can incorporate in to my other MQTT remote monitors and touch screen interfaces if you wish .

this is the web music stream interface - it displays the Station, the Artists and the song titles.
you can easily addin weather weather display or energy display…
the blue ring informs you that Mycroft is ready

![alt text](https://github.com/krywenko/TFT-ifterface-for-Mycroft-AI/blob/master/828c65228515fd22b0ee6870a9f30f20c1c962a5_2_1035x688.jpeg)

the green Ring informs you the Mycroft is listening for your command

![alt text](https://github.com/krywenko/TFT-ifterface-for-Mycroft-AI/blob/master/1ddfbf3520b62dc213e5bee336c7c551d883a17c_2_1035x688.jpeg)

simply copy to the ai home directory
you may have to modify them slightly as I set it to operate in the home dir of ai ( home/ai )



it communicates via serial connection to /dev/ttyS2 and esp (wemos_mini ). The ESP and screen are powered off the the two 5 volt pins on the Pi .
once hooked up and you verified that you can talk to the screen from command line

sudo echo "cmd_9( xxx)" > /dev/ttyS2

this will tell the screen to clear itself and will display blue ring you can change the cmd_3 or 4 to turn from blue to green

then just add these lines to /etc/rc.local

sudo -H -u ai /home/ai/./startup

/home/ai/./ChNam >nul 2>&1 & echo "started station "  

/home/ai/./META  >nul 2>&1 & echo "started Meta data" 

/home/ai/./onlight >nul 2>&1 & echo "started ligt on" 

/home/ai/./offlight>nul 2>&1 & echo "started light off" 

/home/ai/./ont >nul 2>&1 & echo "started ont " 

sudo -H -u root  echo "cmd_9(start)" > /dev/ttyS2

/home/ai/./DandTime >nul 2>&1 & echo "sent time "

/home/ai/./starttime >nul 2>&1 & echo "started timer "  

if using orange pi on armbian OS such as I do you need to enable the Uarts just cd to /boot
nano armbianEnv.txt

and add

overlays=uart1 uart2

now reboot and your uarts will be enabled

okay good luck have fun


  I can be found here if you wish comment or question 
  https://community.openenergymonitor.org/t/mycroft-open-source-ai/10357/3

ai_Mqtt_esp.ino is a remote screen  that will display what the master serial screen does. or you can disable the serial screen and  only display through the mqtt screens 

Update  june 18th -- added a weather alert script to display weather warning and sound off on them -- file "ALERT" modify that one it based on enviroment Canada RSS feed but adaptable to other weather Alert RSS   feeds from other countries  
![alt text](https://github.com/krywenko/TFT-ifterface-for-Mycroft-AI/blob/master/DSC05157.JPG)

