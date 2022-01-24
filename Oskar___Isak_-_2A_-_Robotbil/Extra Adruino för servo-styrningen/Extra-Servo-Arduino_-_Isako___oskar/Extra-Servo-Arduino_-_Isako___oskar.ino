// denna koden har för syfte att ta in ir-siganler från en fjärrkontroll och styra två stycken servon.
// eftersom att bilkitet använder samma timer för både motorstyrningen och servo-pinnarna går det inte att ge PWM siganler till båda samtidigt, därför har vi en extra arduno med denna separata kod, för att styra servorna.



#include <IRremote.h>
int RECV_PIN = A0; // definerar att ir-motagaren sitter på pin A0.


IRrecv irrecv(RECV_PIN); // Definerar att ir-recieverna sitter på "RECV_PIN" (A0).
decode_results results; // funktion som tolkar och "decodar" resultaten.

#include <Servo.h> // inkludera bibloteket för servo.

Servo myservo; // servo nr1
Servo myservo2; // servo nr2

int pos = 90;    //variabler för servots position i grader.
int pos2 = 90;    //variabler för servots position i grader.

void setup()
{Serial.begin(9600);  // startar seriell monitor, bra för felsökning
  irrecv.enableIRIn(); //  Initialize the IR receiver 
 
  Serial.begin (9600);  //Serial Port begin
 
  pinMode(A1, OUTPUT);  //Definerar pinen A1 som output
pinMode(A2, OUTPUT);   //Definerar pinen A2 som output
 digitalWrite(A1, HIGH);  //ger pinen A1 konstant ström "high" / 5v, Detta använs som strömförsörjning till ir-mottagaren.
  digitalWrite(A2,LOW); //ger pinen A2 konstant ström "LOW" / 0v, Detta använs som strömförsörjning till ir-mottagaren.

  
   
myservo.attach(10);  // identifiera att servot sitter monterat på pin 10
myservo2.attach(9);  // identifiera att servot sitter monterat på pin 9
  
}
void loop() {
    Irservo(); //en funktion för nästan all kod i programmet, eftersom att det är ett mycket enkelt progrmm är det inte helt nödvändigt med fler funktioner, om du vill ha en bättre kod kolla på koden för "huvudardunon" i github.
}   //funktionen har inga argument men tar in värden från ir mottagaren och rör motorerna som output.

void Irservo(){
  if (irrecv.decode(&results)) {
if(results.value==0x1142 || results.value==0x1942) //Om 2 trycks ner 
{
  
 
pos = 90;   //sätt positionen till 90
myservo.write(pos); //be servot gå till den angedda positionen.
 


}
else if(results.value==0x1141 || results.value==0x1941) //Om 1 trycks ner 
{
{

  pos -= 20;  // sätt positionen till -20 grder mot det förra värdet.

myservo.write(pos); //be servot gå till den angedda positionen.
 


}

if(results.value==0x1143 || results.value==0x1943)
{
  

pos += 20; 
myservo.write(pos);
 

}



else if(results.value==0x1148 || results.value==0x1948)
{
  
  

pos = 90; 
myservo2.write(pos);
 





}
else if(results.value==0x1145 || results.value==0x1945)
{

  pos -= 20; 

myservo2.write(pos);


}

else if(results.value==0x1140 || results.value==0x1940) 
{
  

pos += 20; 
myservo2.write(pos);
 

}


    irrecv.resume(); //Tar emot nästa värde 
  }


}
}
