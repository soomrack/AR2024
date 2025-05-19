#include <iarduino_DHT.h> 
iarduino_DHT sensor(13);
#define pin_ill A0 // датчик света
#define pin_sol A1 // датчик влажности почвы
#define ledPin 13 // порт для подключения светодиода
#define pin_fan 7 // порт для подключения вентилятора
#define pin_led 6 // свет выход
#define pin_pump 5 // помпа
#define pin_heater 4 // нагреватель только с вентилятором
#define Pin9 9 // датчик температуры и влажности


struct Data_parameters { 
  int min_sol = 200; // минимальное значение влажности почвы
  int min_lum = 300;
  int sol = analogRead(pin_sol);
  int lum = analogRead(pin_ill);
}; 
 
 
struct Data_parameters Parameters; 
int flag_tem = 0; 
int flag_hum = 0; 
int dellay_time = 1000; 
 
 
void setup() 
{ 
  Serial.begin(9600); 
  pinMode(pin_heater, OUTPUT); 
  pinMode(pin_pump, OUTPUT); 
  pinMode(pin_led, OUTPUT); 
  pinMode(pin_fan, OUTPUT);
  pinMode(pin_sol, INPUT);
  pinMode(pin_ill, INPUT);
} 

void data(){
    Serial.print ("CEHCOP B KOMHATE: ");
  switch(sensor.read()){ // Читаем показания датчика темп и влажности
    case DHT_OK:             Serial.println((String) sensor.hum + "% - " + sensor.tem + "*C"); break;
    case DHT_ERROR_CHECKSUM: Serial.println("HE PABEHCTBO KC");                                  break;
    case DHT_ERROR_DATA:     Serial.println("OTBET HE COOTBETCTB. CEHCOPAM 'DHT'");              break;
    case DHT_ERROR_NO_REPLY: Serial.println("HET OTBETA");                                       break;
    default:                 Serial.println("ERROR");                                            break;
  } 
  Serial.print("Влажность почвы:");
  Serial.println(analogRead(pin_sol));
  Serial.print("Освещенность:");
  Serial.println(analogRead(pin_ill));    
}
 

void termoregul() 
{ 
  if (sensor.tem >= 30.) { 
    digitalWrite(pin_heater, LOW); 
    digitalWrite(pin_fan, HIGH); 
    flag_tem = 1; 
  } else { 
    if (sensor.tem <= 15.) { 
      digitalWrite(pin_heater, HIGH); 
      digitalWrite(pin_fan, HIGH); 
      flag_tem = 1; 
    } else { 
      if (flag_hum == 0) { 
        digitalWrite(pin_heater, LOW); 
        digitalWrite(pin_fan, LOW); 
        flag_tem = 0; 
      }; 
    }; 
  }; 
} 
 
 
void air_hum_regul() 
{ 
  if (sensor.hum >= 70.) { 
    digitalWrite(pin_fan, HIGH); 
    flag_hum = 1; 
  } else { 
    if (flag_tem == 0) { 
      digitalWrite(pin_fan, LOW); 
      flag_hum = 0; 
    }; 
  }; 
} 
 
 
void soil_hum_regul() 
{ 
  if (Parameters.sol >= Parameters.min_sol) { 
    digitalWrite(pin_pump, HIGH);
    delay(7000);
    digitalWrite(pin_pump, LOW);
    delay(3000);
    }
}
 
void ill_regul() 
{ 
  if (Parameters.lum <= Parameters.min_lum) { 
    digitalWrite(pin_led, HIGH); 
  } else { 
    digitalWrite(pin_led, LOW); 
  }; 
} 
 
 
void pause() 
{ 
  delay(dellay_time); 
} 
 
 
void loop() 
{ 
  data();
 
  termoregul(); 
 
  air_hum_regul(); 
 
  soil_hum_regul(); 
 
  ill_regul(); 
 
  pause(); 
}

