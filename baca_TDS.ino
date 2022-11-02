void pembacaan_TDS () {
  for ( int i = 0; i < 10 ; i++ ) {
    int val = analogRead (A1);
    tegTDS[i] = val * (5.0 / 1023);
    jumlahTDS += tegTDS[i];
  }
  rata_rata_tegTDS = jumlahTDS / 10;
  jumlahTDS = 0;
  nilai_TDS = (445.79 * rata_rata_tegTDS) - 34.81 ;
