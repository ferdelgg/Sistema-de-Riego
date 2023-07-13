var http = require('http').createServer(handler); //require http server, and create server with function handler()
var fs = require('fs'); //require filesystem module
var io = require('socket.io')(http) //require socket.io module and pass the http object (server)

http.listen(8080); //listen to port 8080

function handler (req, res) { //create server
  fs.readFile(__dirname + '/public/index.html', function(err, data) { //read file index.html in public folder
    if (err) {
      res.writeHead(404, {'Content-Type': 'text/html'}); //display 404 on error
      return res.end("404 Not Found");
    }
    res.writeHead(200, {'Content-Type': 'text/html'}); //write HTML
    res.write(data); //write data from index.html
    return res.end();
  });
}

const { SerialPort, ReadlineParser } = require('serialport')
const port = new SerialPort({
    path: '/dev/tty.usbserial-A50285BI',
    baudRate: 9600 }) //para Pico la velocidad de default es de 115200
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
//parser.on('data', (data) => {
//    console.log(data)
//})

io.sockets.on('connection', function (socket) {// WebSocket Connection
var secs=0;
    parser.on('data', (data) => {
    //    secs=data
        //console.log(data)
        process.stdout.write(data + "\r");
        socket.emit('Humedad', data); //send button status to client
    }) 
    });


io.sockets.on('connection', function (socket) {// WebSocket Connection
    var Bomba = 0; //static variable for current status
    socket.on('BombaOn', function(data) { //get light switch status from client
          Bomba = data;

          port.write(Bomba + '\n', (err) => {
            if (err) {
                return console.log('Error on write: ', err.message)
                }
            })
          if (Bomba) {
            console.log(Bomba); //turn LED on or off, for now we will just show it in console.log
          }
        });
      });