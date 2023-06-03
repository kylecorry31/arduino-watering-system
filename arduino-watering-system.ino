int state;

int STATE_MONITORING = 1;
int STATE_WATERING = 2;

int GARDEN_BED_SENSOR_PIN = 2;
int GARDEN_BED_SENSOR_POWER_PIN = 3;
int GARDEN_BED_VALVE_PIN = 4;

long MONITORING_DELAY = 60 * 1000L;
long WATERING_DELAY = 1000L;

void setup() {
  Serial.begin(9600);

  close_valve();
  
  pinMode(GARDEN_BED_SENSOR_PIN, INPUT_PULLUP);
  pinMode(GARDEN_BED_SENSOR_POWER_PIN, OUTPUT);
  pinMode(GARDEN_BED_VALVE_PIN, OUTPUT);
  state = STATE_MONITORING;
  close_valve();
}

void loop() { 
  if (state == STATE_MONITORING){
    state_monitor();
  } else if (state == STATE_WATERING){
    state_water();
  }
}

void state_monitor(){
  if (is_low_moisture()){
    state = STATE_WATERING;
    return;
  }
  delay(MONITORING_DELAY);
}

void state_water(){
  if (!is_low_moisture()){
    close_valve();
    state = STATE_MONITORING;
    return;
  }
  open_valve();
  delay(WATERING_DELAY);
}

bool is_low_moisture(){
    digitalWrite(GARDEN_BED_SENSOR_POWER_PIN, HIGH);
    delay(1000);
    bool is_low = digitalRead(GARDEN_BED_SENSOR_PIN);
    digitalWrite(GARDEN_BED_SENSOR_POWER_PIN, LOW);
    return is_low;
}

void open_valve(){
  digitalWrite(GARDEN_BED_VALVE_PIN, LOW);
}

void close_valve(){
  digitalWrite(GARDEN_BED_VALVE_PIN, HIGH);
}
