#ifndef Musicien_h
#define Musicien_h

#define DEFAULT_TEMPO 120
#define DEFAULT_LOUDNESS 25
#define DEFAULT_OCTAVE 5

#define SYMBOLE_DIESE '#'
#define SYMBOLE_BEMOL '_'

#define SYMBOLE_UNE_DEMI '$'
#define SYMBOLE_UN_QUART '!'
#define SYMBOLE_TROIS_QUART '%'



#include "Del.h"

/******************************************************************************
* Definitions
******************************************************************************/
class Musicien : private Del
{

public:
	Musicien(uint8_t);

	void refresh();

	void play();
	bool isPlaying();
	void stop();

	void setPause(bool);
	bool getPause();
	
	void setTempo(int);
	int getTempo();

	void setLoudness(float);
	float getLoudness();

	void setPartition(char *song);
	char *getPartition();

protected:
    void changeFrequency(double);
private:
	double getNote();
	double getDureeNote();
	void trimSpace();
	
	int _tempo;
	unsigned long _pulsation;
	int _loudness;
	char *_song;
	char *_cursor;
	bool _playing;
	bool _pausing;
	unsigned long _startTime;
	unsigned long _duree;
	void noTone();
	
};

#endif
