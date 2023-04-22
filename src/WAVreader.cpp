#include "SUwav2img/WAVreader.hpp"

// Constructor that takes a filename as input
WAVreader::WAVreader(const string& filename) {
  // Open the file in binary mode
  file.open(filename, ios::binary);

  // Check if the file was opened successfully
  if (!file.is_open()) {
    cerr << "Failed to open file." << endl;
    throw runtime_error("Failed to open file.");
  }

  // Read the header of the WAV file
  file.read(reinterpret_cast<char*>(&header), sizeof(header));

  // Check if the WAV file is valid
  if (string(header.riff_tag, 4) != "RIFF" ||
      string(header.wave_tag, 4) != "WAVE" ||
      string(header.fmt_tag, 4) != "fmt " ||
      string(header.data_tag, 4) != "data") {
    cerr << "Invalid WAV file." << endl;
    throw runtime_error("Invalid WAV file.");
  }

  // Read the data of the WAV file
  data.resize(header.data_length);
  file.read(data.data(), data.size());
}
