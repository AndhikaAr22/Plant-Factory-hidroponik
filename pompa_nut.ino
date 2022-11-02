void pompa_nutrisi () {
  //  if (nilai_TDS < takaranTDS) {
  digitalWrite (relay4, LOW);
  digitalWrite (relay5, LOW);
  digitalWrite (relay8, HIGH); // Nutup

}
void kelar_pompa_nutrisi() {
  digitalWrite (relay4, HIGH);
  digitalWrite (relay5, HIGH);
  digitalWrite (relay8, HIGH); // Nutup
}

void pompa_pH() {
  if (nilai_pH < 6 ) {
    digitalWrite (relay2, LOW);
    digitalWrite (relay8, HIGH); // Nutup valve
  } else if (nilai_pH > 7) {
    digitalWrite (relay3, LOW);
    digitalWrite (relay8, HIGH); // Nutup valve
  }
}
