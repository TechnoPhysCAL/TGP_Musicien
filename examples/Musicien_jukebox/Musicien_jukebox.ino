/* Nom du programme : jukebox.ino
   Auteur : Claude Bouchard
   Date : septembre 2020
   Description : Cet exemple montre comment jouer des notes de musicien
   sur une broche numérique d'une plaquette ESP32.


   Pour tester ce programme, il est essentiel d'utiliser un "buzzer" et non pas
   un piezo. De plus, le "buzzer" doit être piloté par une transitor afin
   de ne pas endommager la sortie numérique du ESP32. Selon le "buzzer"
   utilisé, il est nécessaire de contrôler le courant dans ce dernier en utilisant
   une résistance série.

   Ce programme a été testé avec un "buzzer" CEM-1203(42) branché via un transistor
   IRLU014 et une résistance série de 51 Ohms. Il ne faut pas oublier de brancher
   une diode de roue libre 1N4001 aux bornes du "buzzer". Le tout doit être alimenté
   à 3.3V
*/

//Appel de la bibliothèque qui contient les fonctions pour jouer des notes.
#include <Musicien.h>

//Appel de la bibliothèque ProtoTGP pour faciliter le contrôle des boutons et de l'écran.
#include <ProtoTGP.h>

//Numéro de la broche sur laquelle est contrôlé le "buzzer".
const uint8_t BROCHE_BUZZER = 12;

//Déclaration de l'instance musicien du type Musicien
Musicien musicien(BROCHE_BUZZER);

ProtoTGP proto;
void setup()
{
  proto.begin();
}

void loop()
{
  musicien.refresh(); //Permet d'actualiser l'état du musicien. CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.
  proto.refresh();    //Permet d'actualiser l'état de la plateforme ProtoTPhys. CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.

  if (proto.haut.isPressed() || proto.haut.isLongPressed()) //Si le bouton HAUT est appuyé ou appuyé longuement
  {
    musicien.setTempo(musicien.getTempo() + 10); // Agmenter le tempo de 10;
    afficherTempo();                             //Afficher le tempo;
  }
  if (proto.bas.isPressed() || proto.bas.isLongPressed()) //Si le bouton BAS est appuyé ou appuyé longuement
  {
    musicien.setTempo(musicien.getTempo() - 10); // Diminuer le tempo de 10;
    afficherTempo();                             //Afficher le tempo;
  }
  if (proto.gauche.isPressed()) //Si le bouton GAUCHE est appuyé
  {
    proto.ecran.ecrire("Frere\nJacques", 2);                                                  // Afficher le titre de la chanson;
    musicien.setPartition("cdec cdec  efg2  efg2 g$a$g$f$ec   g$a$g$f$ec  c -g c2 c -g c2 "); // Fournir la partition voulue;
    musicien.play();                                                                          // Jouer la chanson.
  }
  if (proto.droite.isPressed()) //Si le bouton DROITE est appuyé
  {
    proto.ecran.ecrire("Au clair\nde la lune", 2);                                                              // Afficher le titre de la chanson;
    musicien.setPartition("cccde2ds ceddc3s cccde2ds ceddc3s dddd -a2 -a s d c -b -a -g3 s cccde2ds ceddc3s "); // Fournir la partition voulue;
    musicien.play();                                                                                            // Jouer la chanson.
  }
  if (proto.selection.isPressed()) //Si le bouton SELECTION est appuyé
  {
    musicien.setPause(!musicien.getPause()); //Pauser/Depauser la lecture du musicien.
   }
  if (proto.selection.isLongPressed()) //Si le bouton SELECTION est appuyé longuement
  {
    musicien.stop(); //Arrêter la lecture du musicien.
    
  }
}

static char tempoMsg[20];

void afficherTempo() //routine pour afficher le tempo à l'écran.
{
  sprintf(tempoMsg, "Tempo : %d bpm", musicien.getTempo()); //Formater le message.
  proto.ecran.ecrire(tempoMsg);                             //Afficher le message sur l'écran.
}
