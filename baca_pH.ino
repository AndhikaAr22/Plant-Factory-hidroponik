void pembacaan_pH () {
  for ( int i = 0; i < 10 ; i++ ) {
    int val = analogRead (A5);
    tegpH[i] = val * (5.0 / 1023);
    jumlahpH += tegpH[i];
  }
  rata_rata_tegpH = jumlahpH / 10;
  jumlahpH = 0;
  nilai_pH = (-5.6639 * rata_rata_tegpH) + 21.329 ;
  //
}
