#pragma once
#include <cstdio>
#include <string>
#include <stdexcept>
#include <cstdint>

/*
 * Låter en öppna, stänga, läsa från och skriva till filer. Poängen är
 * att filen ska ses som öppnad av programmet medan man jobbar med den
 * och att man bara ska kunna ha en fil öppen i taget.
*/
class Filehandler
{
private:
	FILE* currFile;
public:
	Filehandler();
	~Filehandler();

	Filehandler(const Filehandler&) = delete;
	Filehandler& operator=(const Filehandler&) = delete;

	/*
	 * Öppnar en fil (och stänger den förra filen, om det finns någon).
	 * Kastar ett std::runtime_error om det inte går.
	*/
	void open(std::string filename);
	// Stänger den öppnade filen (om det finns någon, annars händer inget)
	void close();

	/*
	 * Läser en byte från en fil.
	 * Kastar ett std::runtime_error om ingen fil är öppen eller
	 * om det inte går att läsa. (Detta händer när man är vid slutet av filen.)
	*/
	uint8_t readByte();
	/*
	 * Läser en byte vid en viss position från en fil.
	 * Kastar ett std::runtime_error om ingen fil är öppen, om det
	 * inte går att byta position eller om det inte går att läsa.
	 * (Detta händer när man är vid slutet av filen.)
	*/
	uint8_t readByte(long pos);
	/*
	 * Skriver en byte från en fil.
	 * Kastar ett std::runtime_error om ingen fil är öppen eller
	 * om det inte går att skriva.
	*/
	void writeByte(uint8_t byte);
	/*
	 * Skriver en byte vid en viss position till en fil.
	 * Kastar ett std::runtime_error om ingen fil är öppen, om det
	 * det inte går att byta position eller om det inte går att skriva.
	*/
	void writeByte(uint8_t byte, long pos);

	/*
	 * Ändrar var man läser ifrån och skriver till.
	 * Kaster ett std::runtime_error om det inte går att byta position.
	*/
	void setPos(long pos);
	/*
	 * Hämtar positionen som man läser ifrån.
	 * Kastar ett std::runtime_error om ingen fil är öppen eller
	 * om det inte går att hämta positionen.
	*/
	long getPos();

	// Returnerar FILE*:en
	FILE* getFilePtr() {return currFile;}

	// Om det finns någon fil som är öppnad
	bool fileOpen() {return currFile != nullptr;}
	// Om det finns någon fil som är öppnad
	operator bool() {return currFile != nullptr;}
};