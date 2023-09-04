#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 0;   // Red minimum value
int redMax = 0;   // Red maximum value
int greenMin = 0; // Green minimum value
int greenMax = 0; // Green maximum value
int blueMin = 0;  // Blue minimum value
int blueMax = 0;  // Blue maximum value
int whiteMin = 0; // White minimum value
int whiteMax = 0; // White maximum value
int blackMin = 0; // Black minimum value
int blackMax = 0; // Black maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int whitePW = 0;
int blackPW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;
int whiteValue;
int blackValue;

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read Red value
  redPW = getColorPW(LOW, LOW); // Set S2 and S3 to LOW for Red
  redValue = map(redPW, redMin, redMax, 255, 0);
  delay(200);

  // Read Green value
  greenPW = getColorPW(HIGH, HIGH); // Set S2 and S3 to HIGH for Green
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);
  delay(200);

  // Read Blue value
  bluePW = getColorPW(LOW, HIGH); // Set S2 to LOW and S3 to HIGH for Blue
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  delay(200);

  // Read White value
  whitePW = getColorPW(HIGH, LOW); // Set S2 to HIGH and S3 to LOW for White
  whiteValue = map(whitePW, whiteMin, whiteMax, 255, 0);
  delay(200);

  // Read Black value
  blackPW = getColorPW(HIGH, HIGH); // Set S2 and S3 to HIGH for Black
  blackValue = map(blackPW, blackMin, blackMax, 255, 0);
  delay(200);

  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" Green = ");
  Serial.print(greenValue);
  Serial.print(" Blue = ");
  Serial.print(blueValue);
  Serial.print(" White = ");
  Serial.print(whiteValue);
  Serial.print(" Black = ");
  Serial.println(blackValue);
}

// Function to read Pulse Widths for a specific color
int getColorPW(int s2State, int s3State) {
  // Set sensor to read the specified color
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  
  // Read the output Pulse Width
  int PW = pulseIn(sensorOut, LOW);
  
  return PW;
}
