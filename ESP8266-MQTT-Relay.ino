
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// wifi and MQTT broker vars

const char* ssid = "SKY23BEA";
const char* password = "YEAPARTT";
const char* mqtt_server = "192.168.0.6";
boolean pin1 = false;
boolean pin2 = false;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  if( (char)topic[0] == 'A') {
    if ((char)payload[0] == '1') {
        digitalWrite(5, LOW);   // Turn the LED on (Note that LOW is the voltage level
    }
    if ((char)payload[0] == '0') {
        digitalWrite(5, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    }
  }
 
  if( (char)topic[0] == 'B') {
    if ((char)payload[0] == '1') {
        digitalWrite(4, LOW);   // Turn the LED on (Note that LOW is the voltage level
    }
    if ((char)payload[0] == '0') {
        digitalWrite(4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    }
  }
}
  
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("A");
      client.subscribe("B");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    if(pin1) {
    client.publish("Switch2Status", msg);
  }
}
