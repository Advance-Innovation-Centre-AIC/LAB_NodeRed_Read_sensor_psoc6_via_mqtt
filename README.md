# LAB: NodeRed_Read_sensor_psoc6_via_mqtt

## **Overview**

**Node-red** 
→ Msg[TURN ON/TURN OFF] →Publish/topic1→ MQTT(QoS1)
      
→ MQTT(QoS1)→Subscribe/topic2→ Display data sensor

**PSoC6** 
→MQTT(QoS1)→ Subscribe/topic1 → control [LED ON/OFF]

    

→Msg[data sensor] →Publish/topic2 → MQTT(QoS1)

**Sequence of operation**
MQTT Topic1 

1. The user button is pressed. (use the button on node-red)
2. Node-red publishes a message TURN ON/TURN OFF  on a topic.
3. The MQTT broker sends back the message to the MQTT client because it is also subscribed to the same topic.
4. When the message is received, the subscriber task turns the LED ON or OFF. As a result, the user LED toggles every time the user presses the button.

MQTT Topic2

1. board อ่านค่า sensor และส่งข้อมูล ผ่าน mqtt topic2
2. node-red อ่านค่า sensor ผ่าน mqtt topic2
## **Requirements**
- [ModusToolbox™ software](https://www.infineon.com/modustoolbox) v3.0 or later (tested with v3.0)
- Board support package (BSP) minimum required version: 4.0.0
- Programming language: C
- Associated parts: All [PSoC™ 6 MCU](https://www.infineon.com/PSoC6) parts, [AIROC™ CYW43012 Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/cyw43012), [AIROC™ CYW4343W Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/cyw4343w/), [AIROC™ CYW4373 Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/cyw4373/), [AIROC™ CYW43439 Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/cyw43439/)
- Node-red(tested with v.19.12.1 LTS on Windows x64)
- npm(tested with v.9.1.2 on Windows x64)
## **Hardware setup**

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

## **Software setup**
1. ใช้ example [code Infineon/mtb-example-wifi-mqtt-client](https://github.com/Infineon/mtb-example-wifi-mqtt-client)
2. ใช้ Mosquitto MQTT broker online link https://test.mosquitto.org/
3. node-red on PC (Windows)
## **Supported toolchains (make variable 'TOOLCHAIN')**
- GNU Arm® embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm® compiler v6.16 (`ARM`)
- IAR C/C++ compiler v9.30.1 (`IAR`)
## **Using the code example**
- สร้างโปรเจคบน MTB ใช้ example [code Infineon/mtb-example-wifi-mqtt-client](https://github.com/Infineon/mtb-example-wifi-mqtt-client)


## **Operation**
1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.
2. การตั้งค่าให้ใช้งาน Broker ของ mosquitto >> link https://test.mosquitto.org/ แบบ

port 8884 : MQTT, encrypted, client certificate required

    1. ไปที่ config >> mqtt_client_config.h
        1. ตั้งค่าที่อยู่ broker และ port แบบ  secure 
        2. ตั้งค่าการเชื่อมต่อ MQTT เป็นแบบ secure 
        3. ตั้งชื่อ mqtt topic สำหรับใช้ในการสื่อสารระหว่าง  publisher และ subscriber 
        4. ตั้งค่า QoS เป็น mode 1 ในการสื่อผ่าน MQTT 
        
    ````
    /***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
    /* MQTT Broker/Server address and port used for the MQTT connection. */
    #define MQTT_BROKER_ADDRESS               "test.mosquitto.org"
    #define MQTT_PORT                         8884
    
    /* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is  
     * required to be established, else 0.
     */
    #define MQTT_SECURE_CONNECTION            ( 1 )
    
    /* Configure the user credentials to be sent as part of MQTT CONNECT packet */
    #define MQTT_USERNAME                     ""
    #define MQTT_PASSWORD                     ""
    
    
    /********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
    /* The MQTT topics to be used by the publisher and subscriber. */
    #define MQTT_PUB_TOPIC                    "PSoC6Status/temperature,pressure"
    #define MQTT_SUB_TOPIC                    "PSoC6Status/led"
    
    /* Set the QoS that is associated with the MQTT publish, and subscribe messages.
     * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
     */
    #define MQTT_MESSAGES_QOS                 ( 1 )
    
    ````



3. ดูตัวอย่างวิธีการสร้างไฟล์ client.crt, client.key, mosquitto.org.crt และ ตั้งค่าใน “**configs/mqtt_client_config.h**” 
- ได้จาก →หัวข้อ slide page 19 [MQTT via Mosquitto broker](https://github.com/Advance-Innovation-Centre-AIC/LAB_NodeRed_Read_sensor_psoc6_via_mqtt/blob/e38f6650f649b7e0c999de9d02b34da31a4ec703/docs/HOT_PSoC6_WIFI%20v3.pdf)

4. เปิด file source/publisher_task.c เก็บ copy จาก [link] ไปว่างแทน
5. เปิดไฟล์ configs/wifi_config.h แก้ไข ข้อมูล ชื่อ WiFi และ Password ที่ต้องการเชื่อมต่อ
6. Build และ upload โปรแกรมลงบอร์ด 
7. เปิดโปรแกรม Node-red ทำการ import code โปรแกรมและ ตรวจสอบการ ตั้งค่า node-red ตามตัวอย่าง [Setting Node-red](https://www.dropbox.com/scl/fi/8q7ld86c6wn4q79c7h1kr/LAB_-NodeRed_Read_sensor_psoc6_via_mqtt.paper?dl=0&rlkey=nwjwxnbk5wqrvkh2t1c75v2w3#:uid=879208286062881172009041&h2=Setting-Node-red)

8.  run โปรแกรม Node-red และเปิดเบราว์เซอร์ url: http://127.0.0.1:1880/ui

Figure: Output

![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683183597905_image.png)



## **Setting Node-red** 


1. เริ่มใช้งาน  node-red → [ติดตั้ง Node-red บน Windows](https://github.com/Advance-Innovation-Centre-AIC/EE_Curriculum/blob/main/term2_65_EMB62_IoT/LAB01/Get_started_Node-red.md#%E0%B8%95%E0%B8%B4%E0%B8%94%E0%B8%95%E0%B8%B1%E0%B9%89%E0%B8%87-node-red-%E0%B8%9A%E0%B8%99-windows)
2. import code Button control LED PSoC6
a. คลิ๊กที่ ไฟล์ source >> [Button control LED PSoC6](https://github.com/Advance-Innovation-Centre-AIC/LAB_NodeRed_Read_sensor_psoc6_via_mqtt/blob/367eff3d4db6d1fa1ef356fc44aca44c0235c3a7/flow/NodeRed_Read_sensor_psoc6_via_mqtt.json)

b.copy code ไปที่ แถบขวามือ>>คลิ๊กที่แถบ ขีดสามขีด>> เลือก import


![fig: import function](https://camo.githubusercontent.com/5a37c5f182695a69f125fdd207bf995385cf5c8d6ab5ed87048e6928f4595c9e/68747470733a2f2f70617065722d6174746163686d656e74732e64726f70626f7875736572636f6e74656e742e636f6d2f735f453532434539363336434332314535344342373834434341384132374342353633354439364536373037383033364238413842393236444142443634383644365f313637363139383932383536355f556e7469746c65642e706e67)



c. วาง code ลงหน้า cilpboard >> เลือก new flow >> คลิ๊ก import
    
![](https://camo.githubusercontent.com/a8fbe0623c069fe495f9b36538e32d60a5f637ba013be3131af2ea78ab35c78f/68747470733a2f2f70617065722d6174746163686d656e74732e64726f70626f7875736572636f6e74656e742e636f6d2f735f453532434539363336434332314535344342373834434341384132374342353633354439364536373037383033364238413842393236444142443634383644365f313637363139393230363238375f556e7469746c65642e706e67)



d. สังเกตที่แถบ flow จะมี flow ชื่อว่า “NodeRed_Read_sensor_psoc6_via_mqtt” ปรากฎ

Figure: flow node-red

![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683183811144_Screenshot+2023-05-04+135525.png)


*หมายเหตุ:* สำหรับหรับ node-red ที่ติดตั้งใหม่ ให้ติดตั้ง module dashboard เพิ่ม 
- ไปที่ Manage palette >>Install>> search modules >> พิมพ์ “Dashboard >> เลือก node-red-dashboard >> install
- ดูตัวอย่างการใช้งาน dashboard เบื้องต้นได้จาก [LAB: Basic Node-red Dashboard](https://github.com/Advance-Innovation-Centre-AIC/EE_Curriculum/tree/main/term2_65_EMB64_Applied_ES/LAB11#lab11-basic-node-red-dashboard)



3. ตรวจสอบการตั้งค่า ใช้ node-red เป็น Subscriber โดยดับเบิ้ลคลิ๊กที่ mqtt in node หรือ MQTT Subscriber ที่โปรแกรม node-red และ แก้ไขการตั้งค่าข้อมูลช่องให้ตรงตามข้อมูลด้านล่าง ดังนี้
a. Server >> แก้ไขเป็น “IP address ของ Broker” port: “8884”

b. Topic >> ตั้งค่าเป็น PSoC6Status/temperature,pressure

c. QoS >> ตั้งค่าเป็น “1”


![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184827889_image.png)



![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184240117_Screenshot+2023-05-04+134305.png)


d. ทำการตั้งค่าความปลอดภัยโดย คลิ๊กที่ ลูกศร
- ไปที่ sever >> Use TLS >> คลิ๊กที่ ลูกศร 

e. คลิ๊ก upload ไฟล์ จากไฟล์โปรเจคของบอร์ด ทั้ง 3 ไฟล์ ให้กับ node-red 


Figure: set Server use TLS of  node-red 


![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184551325_Screenshot+2023-05-04+134404.png)


f. หลังจากตั้งค่าเสร็จกด update 


4. ตรวจสอบการตั้งค่า ใช้ node-red เป็น Publisher โดยดับเบิ้ลคลิ๊กที่ mqtt out node หรือ PSoC6Status/led ที่โปรแกรม node-red และ แก้ไขการตั้งค่าข้อมูลช่องให้ตรงตามข้อมูลด้านล่าง ดังนี้
a. Server >> แก้ไขเป็น “IP address ของ Broker” port: “8884”

b. Topic >> ตั้งค่าเป็น PSoC6Status/led

c. QoS >> ตั้งค่าเป็น “1”


![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184765457_image.png)

![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184917073_Screenshot+2023-05-04+134638.png)




5. คลิ๊ก Deploy เพื่อให้ Node-red ทำงานตามโปรแกรมที่ได้ตั้งค่าไว้
6. เปิดหน้าเบราว์เซอร์ขึ้นมา ใส่ “your ip address:1883/ui” จะปรากฎหน้า dashboard ของ node-red

ตัวอย่าง

````
    http://127.0.0.1:1880/
   
````



Figure: Node-red dashboard


![](https://paper-attachments.dropboxusercontent.com/s_6B5130AC4896E700626DB737BBCA734D4979424F756C1CF38B36AD08FC90FD50_1683184937068_Screenshot+2023-05-04+135710.png)

---------------------
Date: 10 May 2023
 * Author: Soontree jaikhong (AIC-Researcher) 


