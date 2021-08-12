const express = require('express');
const io = require('socket.io');
const http = require('http');
const Serialport = require('serialport');

//Servidor
const App = express();
const server = http.createServer(App);
const Socket = io.on;

server.listen(8000, () => {
  console.log('Escuchado el servidor en el puerto: ', 8000)
})

App.use(express.static(__dirname + '/public'));

// Comunicación Serial
const ReadLine = Serialport.parsers.Readline;

const port = new Serialport('COM5', {
  baudRate: 9600
});

port.on('error', (err) => console.log(err));

const parser = port.pipe(new ReadLine ({
  delimiter: '\r\n'
}))

parser.on('open', () => console.log('El servidor está conectado'))

parser.on('data', (data) => {
  console.log(data);
  Socket.emit('temp', data)
})