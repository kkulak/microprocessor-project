#include <SMSService.h>
#include <TemperatureCondition.h>
#include <CommandHandler.h>
#include <DallasTemperatureSensor.h>
#include <Timer.h>

Timer timer;

int dataPin = 2;
DallasTemperatureSensor temperatureSensor( dataPin );

SMSService smsService( &Serial1, 38400 );
TemperatureCondition temperatureCondition( &smsService );
CommandHandler commandHandler( &temperatureCondition, &timer );

void setup( ) {
  Serial.begin( 9600 );
  while( !Serial ) { }
  delay( 2000 );
}

void loop( ) {  
  timer.update( );
  String message = smsService.readSMS( );
  if( message.length( ) > 0 ) 
    commandHandler.handle( message );
  float actualTemperature = temperatureSensor.getTemperature( );
  Serial.println( "Aktualna temperatura: " + String( actualTemperature ) );
  temperatureCondition.checkCondition( actualTemperature );
  delay( 100 );
}

