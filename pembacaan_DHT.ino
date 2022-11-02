void pembacaan_DHT () {
suhu_DHT11 = dht.readTemperature();
kelembapan_DHT11 = dht.readHumidity();

Serial.print("Kelembapan : ");
Serial.print(kelembapan_DHT11);
Serial.println(" %\t");

Serial.print("Suhu : ");
Serial.print(suhu_DHT11);
Serial.println(" C");

 }
