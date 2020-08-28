
#include "Musicien.h"

Musicien::Musicien(uint8_t address) : Del(address)
{
	setTempo(DEFAULT_TEMPO);
	setLoudness(DEFAULT_LOUDNESS);
	stop();
}

void Musicien::setTempo(int tempo)
{
	if (tempo <= 0)
		_tempo = 1;
	else
	{
		_tempo = tempo;
	}

	_pulsation = (unsigned long)((60.0 / _tempo) * 1000);
}
int Musicien::getTempo()
{
	return _tempo;
}

void Musicien::setLoudness(float loudness)
{
	if (loudness < 0.0)
	{
		_loudness = 0;
	}
	else if (loudness >= 100.0)
	{
		_loudness = 100.0;
	}
	else
	{
		_loudness = loudness;
	}

	setBrightness(_loudness / 2);
}
float Musicien::getLoudness()
{
	return _loudness;
}

void Musicien::refresh()
{
	unsigned long now = millis();
	if (_playing && !_pausing)
	{

		if (now > _startTime + _duree)
		{

			_startTime = now;
			if (*_cursor)
			{

				trimSpace();
				double note = getNote();

				changeFrequency(note);
				_duree = (unsigned long)(getDureeNote() * _pulsation);
			}
			else
			{
				stop();
			}
		}
	}
	else
	{
		noTone();
	}
}

bool Musicien::isPlaying()
{
	return _playing;
}

void Musicien::play()
{
	_playing = true;
	_pausing = false;
	Serial.println(_pulsation);
}
void Musicien::setPause(bool value)
{
	_pausing = value;
}
bool Musicien::getPause()
{
	return _pausing;
}
void Musicien::stop()
{
	_playing = false;
	_pausing = false;
	_cursor = _song;
}
void Musicien::setPartition(char *song)
{
	_song = song;
	_startTime = millis();
	_duree = 0;
	_cursor = song;
}
char *Musicien::getPartition()
{
	return _song;
}

////  PITCH_C  PITCH_Cs PITCH_D  PITCH_Ds PITCH_E  PITCH_F  PITCH_Fs PITCH_G  PITCH_Gs PITCH_A  PITCH_As PITCH_B
//	4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902};

void Musicien::trimSpace()
{
	while (*_cursor == ' ')
	{
		_cursor++;
	}
}

double Musicien::getDureeNote()
{
	Serial.print(*_cursor);

	if (*_cursor == SYMBOLE_UN_QUART)
	{
		_cursor++;
		return 0.25;
	}
	else if (*_cursor == SYMBOLE_UNE_DEMI)
	{
		_cursor++;
		return 0.5;
	}
	else if (*_cursor == SYMBOLE_TROIS_QUART)
	{
		_cursor++;
		return 0.75;
	}
	else if (*_cursor == '1')
	{
		_cursor++;
		return 1.0;
	}
	else if (*_cursor == '2')
	{
		_cursor++;
		return 2.0;
	}
	else if (*_cursor == '3')
	{
		_cursor++;
		return 3.0;
	}
	else if (*_cursor == '4')
	{
		_cursor++;
		return 4.0;
	}
	else if (*_cursor == '5')
	{
		_cursor++;
		return 5.0;
	}
	else if (*_cursor == '6')
	{
		_cursor++;
		return 6.0;
	}
	else if (*_cursor == '7')
	{
		_cursor++;
		return 7.0;
	}
	else if (*_cursor == '8')
	{
		_cursor++;
		return 8.0;
	}
	else if (*_cursor == '9')
	{
		_cursor++;
		return 9.0;
	}
	return 1;
}

double Musicien::getNote()
{

	const uint16_t frequenceDeBaseNote[15] = {1, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 8372};
	int octave = DEFAULT_OCTAVE;

	if (*_cursor == '2')
	{
		_cursor++;
		octave = 2;
	}
	else if (*_cursor == '3')
	{
		_cursor++;
		octave = 3;
	}
	else if (*_cursor == '4')
	{
		_cursor++;
		octave = 4;
	}
	else if (*_cursor == '5')
	{
		_cursor++;
		octave = 5;
	}
	else if (*_cursor == '6')
	{
		_cursor++;
		octave = 6;
	}
	else if (*_cursor == '7')
	{
		_cursor++;
		octave = 7;
	}
	else if (*_cursor == '+')
	{
		_cursor++;
		octave += 1;
	}
	else if (*_cursor == '-')
	{
		_cursor++;
		octave -= 1;
	}

	int index = -5;
	if (*_cursor == 'C' || *_cursor == 'c')
	{
		_cursor++;
		index = 2;
	}
	else if (*_cursor == 'D' || *_cursor == 'd')
	{
		_cursor++;
		index = 4;
	}
	else if (*_cursor == 'E' || *_cursor == 'e')
	{
		_cursor++;
		index = 6;
	}
	else if (*_cursor == 'F' || *_cursor == 'f')
	{
		_cursor++;
		index = 7;
	}
	else if (*_cursor == 'G' || *_cursor == 'g')
	{
		_cursor++;
		index = 9;
	}
	else if (*_cursor == 'A' || *_cursor == 'a')
	{
		_cursor++;
		index = 11;
	}
	else if (*_cursor == 'B' || *_cursor == 'b')
	{
		_cursor++;
		index = 13;
	}
	else if (*_cursor == 'S' || *_cursor == 's')
	{
		_cursor++;
		index = -5;
	}

	if (*_cursor == SYMBOLE_DIESE)
	{
		_cursor++;
		index++;
	}
	else if (*_cursor == SYMBOLE_BEMOL)
	{
		_cursor++;
		index--;
	}

	if (index < 0)
	{
		index = 0;
	}

	return (double)frequenceDeBaseNote[index] / (double)(1 << (8 - octave));
}

void Musicien::noTone()
{
	changeState(false, getBrightness());
}

void Musicien::changeFrequency(double frequency)
{

	if (getChannel() >= 0)
	{
		if (frequency != 1)
		{
			ledcWriteTone(getChannel(), frequency);
			changeState(true, getBrightness());
		}
		else
		{
			//ledcWriteTone(getChannel(), 1);
			changeState(false, getBrightness());
		}
	}
}
