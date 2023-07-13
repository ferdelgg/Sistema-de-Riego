#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

#define HumedadA A6
#define HumedadD 2
#define Bomba 3

void setup() 
{
  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);
  display.println("Sistema De Riego");
  display.setTextSize(1);
  display.setCursor(30, 40);
  display.println("Automatico");
  display.display();


  pinMode(HumedadA, INPUT);
  pinMode(HumedadD, INPUT);

  pinMode(Bomba, OUTPUT);

  digitalWrite(Bomba, LOW);

  delay(3000);

}

void loop() 
{
  int HumA = analogRead(HumedadA); 
  int HumD = digitalRead(HumedadD);


  HumA = map(HumA, 0, 1023, 100, 0);

  Serial.println(HumA);

  String datoHume = String(HumA);    
  
  String Encendido = Serial.readStringUntil('\n');
  int on = Encendido.toInt();

  if(on == HIGH)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25, 15);
    display.println("Bomba De Agua");
    display.setCursor(35, 40);
    display.println("Endendida");
    display.display();

    digitalWrite(Bomba, LOW);
    delay(10000);
  }


  else if(HumD ==  HIGH)
  { 
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25, 15);
    display.println("Bomba De Agua");
    display.setCursor(35, 40);
    display.println("Endendida");
    display.display();

    digitalWrite(Bomba, LOW);

  }
  else
  {

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15, 15);
    display.println("Nivel de Humedad");
    display.setCursor(50, 40);
    display.println(datoHume);
    display.setCursor(68, 40);
    display.println("%");
    display.display();


    digitalWrite(Bomba, HIGH);

  }

}
