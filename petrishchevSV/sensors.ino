void sensors_read() 
{
light = analogRead(svet);
ground_hum = analogRead(humid);
vlazh.read();
humo = vlazh.hum;
temp = vlazh.tem;
}