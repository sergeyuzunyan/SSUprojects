#include <iostream>
#include <vector>
#include <cstdlib>
#include "SUwav2img/WAVreader.hpp"
#include "SUwav2img/PICdrawer.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  // Check if the correct number of arguments were passed in
  if (argc != 2) {
    cerr << "Failed to recognize file." << endl;
    return 1;
  }

  // Create a WAV file reader object
  WAVreader sound_reader(argv[1]);

  // Print out the sample rate and number of channels of the WAV file
  cout << "Sample rate: " << sound_reader.get_sample_rate() << endl;
  cout << "Number of channels: " << sound_reader.get_num_channels() << endl;

  // Create a PICdrawer object and generate the ASCII image
  int width = 80;
  int height = 40;
  PICdrawer pic_drawer(sound_reader.get_data(), sound_reader.get_num_channels(), sound_reader.get_sample_rate(), width, height);
  string ascii_image = pic_drawer.generate_ascii_image();

  // Print out the size of the generated ASCII image
  cout << "ASCII image size: " << ascii_image.size() << endl;

  // Save the ASCII image to a file
  ofstream outfile("image.txt");
  if (outfile.is_open()) {
    outfile << ascii_image;
    outfile.close();
  } else {
    cerr << "Failed to save image." << endl;
    return 1;
  }
  return 0;
}
