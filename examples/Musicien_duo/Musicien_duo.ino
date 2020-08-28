/* Nom du programme : musicien_duo.ino
   Auteur : Claude Bouchard
   Date : septembre 2020
   Description : Cet exemple montre comment jouer des notes en duo
   sur deux broches numériques d'une plaquette ESP32.


   Pour tester ce programme, il est essentiel d'utiliser deux "buzzers" et non pas
   un piezo. De plus, les "buzzers" doient être pilotés par une transitor afin
   de ne pas endommager la sortie numérique du ESP32. Selon les "buzzers"
   utilisés, il est nécessaire de contrôler le courant dans ce dernier en utilisant
   une résistance série.

   Ce programme a été testé avec deux "buzzers" CEM-1203(42) branchés via un transistor
   IRLU014 et une résistance série de 51 Ohms. Il ne faut pas oublier de brancher
   une diode de roue libre 1N4001 aux bornes du "buzzer". Le tout doit être alimenté
   à 3.3V
*/

//Appel de la bibliothèque Musicien qui contient les fonctions pour jouer des notes.
#include <Musicien.h>

//Numéro de la broche sur laquelle est contrôlé les "buzzers".
const uint8_t BROCHE_BUZZER_A = 12;
const uint8_t BROCHE_BUZZER_B = 15;

//Déclaration de l'instance des musiciens du type Musicien
Musicien musicienA(BROCHE_BUZZER_A);
Musicien musicienB(BROCHE_BUZZER_B);

void setup()
{
  musicienA.setPartition("cdec cdec  efg2  efg2 g$a$g$f$ec   g$a$g$f$ec  c -g c2     c -g c2");                      //Frère Jacques
  musicienB.setPartition("ssss ssss  cdec  cdec efg2         efg2        g$a$g$f$ec  g$a$g$f$ec  c -g c2 c -g c2 "); //Frère Jacques, décalé de 2 mesures

  musicienA.play();
  musicienB.play();
}

void loop()
{

  musicienA.refresh(); //Permet d'actualiser l'état du musicienA. CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.
  musicienB.refresh(); //Permet d'actualiser l'état du musicienB. CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.

}