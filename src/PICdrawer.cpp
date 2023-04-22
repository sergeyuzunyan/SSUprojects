#include "SUwav2img/PICdrawer.hpp"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

std::string PICdrawer::generate_ascii_image() const {
  // Check if the audio data is empty or the width is less than or equal to 0
  if (audio_data_.empty() || width_ <= 0) {
    cerr << "Failed to generate ASCII image: audio data is empty or width is less than or equal to 0." << endl;
    return "";
  }

  // Calculate the number of audio samples per pixel column
  int samples_per_column = audio_data_.size() / num_channels_ / (width_ - 1);

  // Calculate the height scaling factor based on the maximum amplitude of the audio data
  double max_amplitude = 0;
  for (int i = 0; i < audio_data_.size(); i += num_channels_) {
    int16_t sample = (audio_data_[i] & 0xff) | ((i+1 < audio_data_.size()) ? (audio_data_[i+1] << 8) : 0);
    double amplitude = abs(sample) / 32768.0;
    if (amplitude > max_amplitude) {
      max_amplitude = amplitude;
    }
  }
  double height_scale = height_ * 0.4 / max_amplitude;

  // Generate the ASCII image using the audio data
  cout << "Generating ASCII image..." << endl;

  // Declare the stringstream object
  stringstream ss;

  // ASCII image generation code
  for (int y = height_; y >= 0; y--) {
    for (int x = 0; x < width_; x++) {
      int start_index = x * samples_per_column * num_channels_;
      int end_index = start_index + samples_per_column * num_channels_;
      double sum = 0;
      for (int i = start_index; i < end_index; i += num_channels_) {
        int16_t sample = (audio_data_[i] & 0xff) | (audio_data_[i+1] << 8);
        double amplitude = abs(sample) / 32768.0;
        sum += amplitude;
      }
      double average_amplitude = sum / samples_per_column;
      int height = (int)(average_amplitude * height_scale);
      if (y == height) {
        ss << "*";
      } else if (y == height_ / 2) {
        ss << "|";
      } else {
        ss << " ";
      }
    }
    ss << endl;
  }

  return ss.str();
}
