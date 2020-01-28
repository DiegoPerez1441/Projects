/*

Download Time Calculator

Created by Diego Perez
July 6, 2019


TODO:
* Program Termination with options
* Add Live speed check
* Design and impliment GUI
* Get Download Info from other Apps
------------------------------------
Debug:
* Differences in download types

*/


#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>


enum dataType {
	K, M, G, T
};

// Convert Int to String
std::string IntToString(int number) {
	// Initialize stream used for the conversion
	std::ostringstream convert;
	convert << number;

	return convert.str();
}

// Got from https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
// Check if a String is all digits
bool StringIsAllDigits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

struct time {
	float raw;

	int hours;
	int minutes;
	int seconds;

	void calculate() {
		float tmp_seconds = raw;
		float tmp_minutes = tmp_seconds / 60;
		float tmp_hours = tmp_minutes / 60;

		hours = int(tmp_hours);
		minutes = int((tmp_hours - hours) * 60);
		seconds = int((((tmp_hours - hours) * 60) - (minutes)) * 60);

	}

	void display() {
		std::string s_seconds, s_minutes, s_hours;

		s_seconds = IntToString(seconds);
		s_minutes = IntToString(minutes);
		s_hours = IntToString(hours);

		// Fix into correct time format
		if (seconds < 10) { s_seconds = "0" + s_seconds; }
		if (minutes < 10) { s_minutes = "0" + s_minutes; }

		std::cout << s_hours << ":" << s_minutes << ":" << s_seconds << std::endl;
	}
};

void Log(std::string text, bool endl = true) {
	if (endl) {
		std::cout << text << std::endl;
	}
	else {
		std::cout << text;
	}
}


int main() {
	float fileSize;
	dataType download_Units;

	float downloadSpeed;
	dataType downloadSpeed_Units;

	time downloadTime;

	// Get a temporary user input string
	std::string userInput;

	Log("Enter File Size: ", false);
	std::cin >> fileSize;
	Log("Enter download units: KB, MB, GB, TB: ", false);
	std::cin >> userInput; std::cout << std::endl;

	// Lowercase user input and associate it with datatype
	std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	if (userInput == "kb") { download_Units = K; }
	else if (userInput == "mb") { download_Units = M; }
	else if (userInput == "gb") { download_Units = G; }
	else if (userInput == "tb") { download_Units = T; }

	Log("Enter download speed: ", false);
	std::cin >> downloadSpeed;
	Log("Enter download speed units: Kb/sec, Mb/sec, Gb/sec: ", false);
	std::cin >> userInput;

	// Lowercase user input and associate it with datatype
	std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	if (userInput == "kb/sec") { downloadSpeed_Units = K; }
	else if (userInput == "mb/sec") { downloadSpeed_Units = M; }
	else if (userInput == "gb/sec") { downloadSpeed_Units = G; }

	Log("____________________________________________________");

	// Convert units
	if (download_Units > downloadSpeed_Units) {
		unsigned int diff = download_Units - downloadSpeed_Units;
		for (int i = 0; i < diff; i++) {
			fileSize *= 1024;
		}
	}
	else if (download_Units < downloadSpeed_Units) {
		unsigned int diff = downloadSpeed_Units - download_Units;
		for (int i = 0; i < diff; i++) {
			fileSize /= 1024;
		}
	}

	// Calculate download time and display
	downloadTime.raw = (fileSize / (downloadSpeed / 8));
	downloadTime.calculate();
	Log("Download Time: ", false);
	downloadTime.display();

	// Leave space between program and console termination
	std::cout << std::endl;
}
