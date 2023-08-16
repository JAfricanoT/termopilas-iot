# Termopilas IoT

Código fuente que permite usar un ESP32 con los módulos RC522 y PN532 por medio de SPI, para la lectura de tarjetas RFID o NFC. Luego realiza una petición a algún endpoint de una API donde verifica los permisos y registra los movimientos, al validar un usuario permitido se obtiene una respuesta positiva activando un módulo de relays que acciona un torniquete o cualquier otro método de control de acceso.

---

## Instalación

### Modulos

### Arduino IDE

En el directorio 'Arduino' se ejecutan los siguientes comandos:

```shell
mkdir termopilas
cd termopilas
git clone https://github.com/JAfricanoT/termopilas-iot.git
``` 

Desde el Arduino IDE y abrimos el sketch llamado 'termopilas'.

### Librerias


**Importante:** se debe borrar el header TermopilasConfig, para eso solo se debe eliminar la fila  

```c++
#include <TermopilasConfig.h>
```  

#### UNIT_PN532

Es la librería que nos permite conectar el modulo PN532 al ESP32. Basada en la libreria de Adafruit, esta modificada por "uelectronics" y se puede [descargar](https://blog.uelectronics.com/wp-content/uploads/2021/10/UNIT-PN532.zip) e instalar directamente en el directorio de "libraries" en "Arduino".

#### Otras
Las demás librerías se pueden descargar directamente desde el 'Library Manager' del Arduino IDE 

---
## Configuración

La configuración completa se realiza desde las variables en el archivo 'termopilas'

| Categoría | Variable | Tipo | Descripcion |
| --- | --- | --- | --- | 
| Miscellaneous | moduleID | String | Identificador único para el ESP32 |
| Relays | relay1Pin | int | Pin en el ESP32 al cual esta conectado el relay |
| Relays | relay2Pin | int | Pin en el ESP32 al cual esta conectado el relay |
| RF522 | SS_PIN | int | Pin en el ESP32 al cual esta conectado SS o SDA del modulo RF522 |
| RF522 | RST_PIN | int | Pin en el ESP32 al cual esta conectado RST del modulo RF522 |
| PN532 | PN532_SCK | int | Pin en el ESP32 al cual esta conectado SCK del modulo PN532 |
| PN532 | PN532_MOSI | int | Pin en el ESP32 al cual esta conectado MOSI del modulo PN532 |
| PN532 | PN532_SS | int | Pin en el ESP32 al cual esta conectado SS del modulo PN532 |
| PN532 | PN532_MISO | int | Pin en el ESP32 al cual esta conectado MISO del modulo PN532 |
| HTTP Request | apiUrl | String | Dirección del endpoint que se va a consumir |
| HTTP Request | apiKey | String | Llave de la API |
| Wifi | ssid | String | Nombre de la red de la red a la cual se va a conectar el ESP32 (SSID) |
| Wifi | password | String | Contraseña de la red a la cual se va a conectar el ESP32 |

