#ifndef SOUND_H
#define SOUND_H


class Sound
{
public:
	static void initAudio(void);
	static void exitAudio(void);

	static void PlayMusic(bool play);
};

#endif