#include<WiFi.h>;
#include "ESP32_MailClient.h"
int trigger=12;
int echo=14;
int mesure=1000;
bool b;
int cmpt=0;
char*  ssid="louness";
char* password="Ha123456789";
long d;
SMTPData smtpData;
void setup()
{
  //initialisation
    Serial.begin(115200);
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
    WiFi.begin(ssid,password);

    Serial.print(" CONNECTION EN COURS .");
    while(WiFi.status()!=WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
//affichage de ladreess IP obtenue à l'issue de connection au WIFI
                Serial.print("   YOUR IP@ IS : ");
                Serial.println(WiFi.localIP());
}
void loop()
{
           //partie pour le detecteur de mouvement
                digitalWrite(trigger,LOW);
                delayMicroseconds(2);
                digitalWrite(trigger,HIGH);
                delayMicroseconds(10);
               mesure=pulseIn(echo,HIGH)/58.0;
                Serial.print(" DISTANCE : ");
               Serial.println(mesure);

         //dans le cas où on detecte une lettre on envoie le mail par le code suivant
              if(mesure<20){
                 if(cmpt=0)
                 {
                    cmpt=cmpt+1;
                 }
                 else{
                        Serial.println(" detecté");
                             smtpData.setLogin("smtp.googlemail.com",465, "hadjalilounas@gmail.com", "Ha123456789");    
                                 smtpData.setSender("ESP32", "hadjalilounas@gmail.com");
                                  smtpData.setPriority("High");
                                     smtpData.setSubject("alerte courier");
                                         smtpData.setMessage("un nouveau courier est déposé dans votre boite aux lettres",false);
                                         smtpData.addRecipient("hadjalilounas@gmail.com");
                                               if (!MailClient.sendMail(smtpData))
                                                   Serial.println("Error sending Email, " + MailClient.smtpErrorReason());       
                       delay(2000);
                       mesure=100;
                       cmpt=cmpt+1;
               }
              }
               
}
