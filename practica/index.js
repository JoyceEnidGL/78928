// Create a client instance
client = new Paho.MQTT.Client("", 9001, "");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("World");
  message = new Paho.MQTT.Message("Hello");
  message.destinationName = "World";
  //client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  var idDiv = document.getElementById("idDiv")
  idDiv.innerHTML = idDiv.innerHTML + `<p>${message.payloadString}</p>`
  console.log("onMessageArrived:"+message.payloadString);
}

function enviarMsj() {
  
  var idText = document.getElementById("idTexto").value
  message = new Paho.MQTT.Message("-: " + idText);
  message.destinationName = "World";
  client.send(message);
  document.getElementById("idTexto").value = ""
  
}