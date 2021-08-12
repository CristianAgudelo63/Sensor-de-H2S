/*
 * SENSOR OLFATIVO TIPO NARIZ PARA DETECTAR LA PRESENCIA DE SULFURO DE HIDRÓGENO CERCA DE AGUAS RESIDUALES.
 * Open Source desarrollado por: Diego A. Trujillo, Cristian Agudelo, Juan E. Molina, Miguel Duque y Jary D. Monsalve.
 * Programación en JavaScript, ultima modificación al código: 20/07/2021
*/

const { Board, Led } = require('johnny-five');
const circuito = new Board({
	port: 'COM5' //Cambiar puerto dependiendo de donde esta conectado la placa
});

circuito.on('ready', () => {
	led = new Led(13);
	led.strobe(500);
});

circuito.on('error', (err) => {
	console.log(err);
});