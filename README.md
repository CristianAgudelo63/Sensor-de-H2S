# Sensor de Sulfuro

Código fuente del proyecto "Sensor Olfativo Tipo Nariz Para Detectar La Presencia De Sulfuro De Hidrógeno Cerca De Aguas Residuales", [ingresa a la página web del proyecto](https://cristiangudelo63.wixsite.com/misitio).

Clona el repositorio con Git Bash con el comando:

```sh
git clone https://github.com/CristianAgudelo63/Sensor-de-Sulfuro.git
```

## Código en Arduino
_Es necesario tener instalado el IDE de Arduino en nuestro ordenador._

Ingresar a la carpeta "Sensor-de-Sulfuro" y ejecuta el código del archivo `code.ino`.

## Código en JavaScript y NodeJS
_Es necesario tener instalado el IDE de Arduino en nuestro ordenador y  tener instalado NodeJS._
    
Ingresar a la carpeta "JS" y ejecutar con NodeJS los siguientes comandos:

```sh
npm install johnny-five
npm install firmata-party
```
Una vez instaladas ambas librerías, ingresar a la carpeta "StandardFirmata.ino" y abrir el archivo `StandardFirmata.ino` en el IDE de Arduino, compilan y suben ese archivo a la tarjeta de desarrollo Arduino. Luego, abren una terminal y se dirigen a la ruta donde se encuenta el archivo `js/code.js` ejecutan el suguiente comando:

```sh
node code.js
```
## Imágenes

![Sensor.](https://static.wixstatic.com/media/080105_53758c5d419a49c4b95e6abef440ab3e~mv2.jpeg/v1/fill/w_276,h_207,al_c,q_80,usm_0.66_1.00_0.01/WhatsApp%20Image%202019-10-16%20at%207_01_38%20AM%20.webp)
