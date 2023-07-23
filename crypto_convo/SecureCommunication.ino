#include <WiFi.h>
#include <WiFiClientSecure.h>

// WiFi network name and password:
const char * networkName = "Your_Network_Name";
const char * networkPswd = "Your_Network_Password";

// Internet server details
const char * serverName = "server.example.com"; 
int serverPort = 443;

// Create a WiFiClientSecure object
WiFiClientSecure client;

void setup() {
  // Initialize serial and wait for the port to open:
  Serial.begin(115200);
  delay(100);

  // Attempt to connect to the local WiFi network:
  Serial.print("Connecting to ");
  Serial.println(networkName);
  
  WiFi.begin(networkName, networkPswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Connected to WiFi network
  Serial.println("");
  Serial.println("Connected to WiFi");

  // Connect to the server (SSL/TLS)
  Serial.print("Connecting to ");
  Serial.println(serverName);

  if (!client.connect(serverName, serverPort)) {
    Serial.println("Connection failed!");
  } else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println("GET / HTTP/1.0");
    client.println("Host: " + String(serverName));
    client.println("Connection: close");
    client.println();

    // Read and print the response
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers received");
        break;
      }
    }
    String line = client.readStringUntil('\n');
    Serial.println("Reply: " + line);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
