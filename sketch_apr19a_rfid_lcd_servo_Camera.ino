
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>

SoftwareSerial mySerial(10, 11); // RX, TX
Servo myservo;  // create servo object to control a servo


//.........Declearations..........................................
String Card_A="030088AC2502";  // RFID tag of Card A
String Card_B="030087C65416";  // RFID tag of Card B
String Card_read="0000000000000"; // used for read comparisons
int i;
int pos = 0;    // variable to store the servo position
//............................................................... 

LiquidCrystal lcd(12,9,8,7,6,5);

void setup() 
{
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  lcd.begin(16,2);
// Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // do nothing untill a card is presented
  }

  Serial.println("Please swip your ID card!");
  
  
 // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
 
}

void loop() 
{ // run for ever

  lcd.setCursor(1,0);
  lcd.print("PLS SWIPE YOUR ID CARD!");

  for (int positionCounter=0; positionCounter<20; positionCounter++){
    lcd.scrollDisplayLeft();
    delay(150);
    }
  
  if (mySerial.available() > 0) 
  {
    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
    delay(500);
  
    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
    delay(500);

    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
    delay(500);
    
    Read_ID(); // The function for the reading ID
    Identify_ID(); // Identifies the ID 
    Clean_ID(); // Clean the ID   
   }
   delay(100); //Wait 100 milliseconds   
}

//.....................Read_ID........................................................
void Read_ID() // function that reads the TAG and store the ID's TAG in a variable tag_read
 {
  i=0;   //Resets the variable to read
  while(mySerial.available() > 0) //While the mySerial receive data (ID) 
  {
    Card_read[i]= mySerial.read();  //Store the character that entered in serial on Card_read’s position  
    i++;  //Increments a variable of count 
    }
Serial.print("\n\nCARD Detected:"); //Jump 2 lines and print at serial the phrase"TAG Read:" 

lcd.clear();
lcd.setCursor(1,0);
lcd.print("CARD DETECTED!");

for(i=0;i<13;i++) Serial.print(Card_read[i]); //Print Card ID   



Serial.println(); //Jump a line 
 }

//.......................................................................................

//..................Clean_ID............................................................
void Clean_ID() //Function that cleans the variable tag_read and resets the module ID 12/20 for a new read leitura 
{    

for(i=0;i<13;i++) Card_read[i] = '0'; //Clean variable Card_read   

}
//........................................................................................


//.................Identify_ID...........................................................
void Identify_ID()  // This Function identifies the ID
{
  
    boolean validate=true;  //Creates a boolean variable to validate the CARD  
//Compare the ID of the Card_read with the ID of the CARD A   
    for(i=0; i<13; i++)
    {
      if(Card_read[i+1]!=Card_A[i]){
        validate=false;  //Invalidates the CARD A 

       // lcd.print("ACCESS DENIED!");
        }
      }
 

      if(validate==true)  //If the " CARD A" is not invalidated   
    {
    Serial.println("Accepted Card A");

    lcd.clear();

    lcd.print("ACCESS GRANTED!");
  for (pos = 0; pos <= 90; pos += 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }   
    
    lcd.setCursor(0,1);

    lcd.print("WELCOME Mr. LAGBAJA!");
    delay(3000);    
     for (int positionCounter=0; positionCounter<20; positionCounter++){
    lcd.scrollDisplayLeft();
    delay(500);
    } 

   for (pos = 90; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    

    
    lcd.clear();
        }

//lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll



validate = true; //Validates the variable validate to a new comparison of IDs     

// Compare the ID of the Card_read with the ID of the Card B   
for(i=0 ; i<13 ; i++)   
{   

if(Card_read[i+1] != Card_B[i]) //If ID Card_read is different from the ID Card B     
{       
validate=false; //Invalidates the Card B 

     //lcd.print("ACCESS DENIED!");
} 

}   

//===========================================================   

if(validate == true) //If the Card B is not Invalidate   
{
Serial.println("Accepted Card B");

lcd.clear();

lcd.print("ACCESS GRANTED!");

  for (pos = 0; pos <= 90; pos += 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }  


lcd.setCursor(0,1);

lcd.print("WELCOME Mr. TAMEDUN!");
 for (int positionCounter=0; positionCounter<20; positionCounter++){
    lcd.scrollDisplayLeft();
    delay(500);
    } 

   
   for (pos = 90; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

lcd.clear();
//============================ 

delay(2000); //Wait 2 seconds to make a new reading;   
}   

}

 
