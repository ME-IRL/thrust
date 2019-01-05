#include <SPI.h>
#include <SD.h>
#include "HX711.h"

#define __calibration -7050.0 // Configure this
#define HX711_DATA 4
#define HX711_CLK 5

#define SD_CS 18

File thrustData;
boolean running = false;

void setup(){
	Serial.begin(9600);
	while(!Serial);

	sdInit(SD_CS);
	thrustData = sdCreateFile("data");
	sdWriteInfo(thrustData);

	Serial.println("Initializing HX711 scale...");
	HX711 scale(HX711_DATA, HX711_CLK);
	scale.set_scale(__calibration);
	scale.tare();

	running = true;
	println("Index,MS,thrustVal");
	for(int dpoint = 1; running; dpoint++){
		String dataString = String(dpoint)+","+millis();

		// Append data
		dataString += ","+String(scale.get_units());

		println(dataString);
		//if(dpoint == 1) running = false;
	}

	thrustData.close();
}

void println(String s){
	print(s+"\r\n");
}

void print(String s){
	thrustData.print(s);
	Serial.print(s);
}

void sdWriteInfo(File f){
	f.println("Data File: 1970-01-01 00:00:00");
	Serial.println("Data File: 1970-01-01 00:00:00");
}

File sdCreateFile(String fn){
	Serial.print("Attempting to create file \"");
	Serial.print(fn);
	Serial.print(".txt\"...");

	boolean e = false;
	String nfn = fn+".txt";
	int count = 1;
	while(SD.exists(nfn.c_str())){
		e = true;
		nfn = fn+count++;
		nfn += ".txt";
	}

	File f = SD.open(nfn.c_str(), FILE_WRITE);
	if(!f){
		Serial.println("Failed!");
		error();
	}
	Serial.println("Success!");
	e = true;

	if(e){
		Serial.print("NOTE: Using filename \"");
		Serial.print(nfn);
		Serial.println("\" instead.");
	}
	return f;
}

void sdInit(short cs){
	Serial.print("Initializing SD Card...");
	if(!SD.begin(cs)){
		Serial.println("Failed!");
		error();
	}
	Serial.println("Success!");
}

void error(){
	//return;
	while(1);
}

void loop(){}
