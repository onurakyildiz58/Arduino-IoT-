int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 10000.0; //10K ohm direnç
float R2 = 1000.0;  //1K ohm direnç
int value = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(analogInput, INPUT);
}

void loop()
{
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2/(R1+R2));

  if (vin < 0.09)
  {
    vin = 0.0;
  }

  Serial.print("Pil Gerilimi: ");
  Serial.print(vin);
  Serial.println(" V");
  delay(500);
}
