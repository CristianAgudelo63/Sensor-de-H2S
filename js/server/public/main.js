const { Socket } = require("socket.io");

const Socket = io();

Socket.on('temp', (datos) => {
  console.log(datos);
})

const ug = document.getElementById('microGramo');
const ppm = document.getElementById('partesPorMillon');

if (ug.value >= 7) {
  ug.style.background="#ce1818"
} else {
  ug.style.background="#fff";
}