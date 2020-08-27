/* Nom du programme : gamme.ino
 * Auteur : Claude Bouchard
 * Date : septembre 2020
 * Description : Cet exemple montre comment jouer des notes de musicien
 * sur une broche numérique d'une plaquette ESP32. 
 * 
 * 
 * Pour tester ce programme, il est essentiel d'utiliser un "buzzer" et non pas
 * un piezo. De plus, le "buzzer" doit être piloté par une transitor afin
 * de ne pas endommager la sortie numérique du ESP32. Selon le "buzzer" 
 * utilisé, il est nécessaire de contrôler le courant dans ce dernier en utilisant
 * une résistance série. 
 * 
 * Ce programme a été testé avec un "buzzer" CEM-1203(42) branché via un transistor 
 * IRLU014 et une résistance série de 51 Ohms. Il ne faut pas oublier de brancher 
 * une diode de roue libre 1N4001 aux bornes du "buzzer". Le tout doit être alimenté 
 * à 3.3V
 */

//Appel de la bibliothèque Musicien qui contient les fonctions pour jouer des notes.
#include <Musicien.h>

//Numéro de la broche sur laquelle est contrôlé le "buzzer".
const uint8_t BROCHE_BUZZER = 12;
//Déclaration de l'instance musicien du type Musicien 
Musicien musicien(BROCHE_BUZZER);


void setup() {
  //Initialise le port de communication série à 115200 bps pour être conforme
  //à la vitesse de transmission des messages du RTOS du ESP32 :
  Serial.begin(115200);

  musicien.setPartition("c c# d d# e f f# g g# a a# b +c +c# +d +d# +e s c -b -b_ -a -a_ -g -a -b c2 s2  c1 s c!s! c$ s c%  2c 3c 4c 5c 6c 7c a ");

}

void loop() {

  musicien.refresh(); //Permet d'actualiser l'état du musicien. CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.
  
  if (!musicien.isPlaying()){ //Lorsque le musicien ne joue plus:
    musicien.play(); //Faire jouer le musicien.
  }

}