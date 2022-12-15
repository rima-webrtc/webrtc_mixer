/*
 *  Copyright (c) 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "MixerImpl.h"

#include <memory>
#include <string>

//#include "timing.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

using namespace ts;
using namespace webrtc;

void WebRtc_DeNoise(char* in_file, char* tts_file, char* out_file, uint32_t sampleRate, uint32_t num_channels) {
  std::ifstream in_stream;
  in_stream.open(in_file, std::ios::in | std::ios::binary);
  // std::ifstream tts_stream;
  // in_stream.open(tts_file, std::ios::in | std::ios::binary);
  std::ofstream out_stream;
  out_stream.open(out_file, std::ios::out | std::ios::binary);

  int in_size = 10000000;
  char* in_buffer = (char*)malloc(in_size);
  char* tts_buffer = (char*)malloc(in_size);
  char* out_buffer = (char*)malloc(in_size);

      in_stream.read((char *)in_buffer, in_size);
    size_t gcount_in_size = in_stream.gcount();
    in_stream.close();
      in_stream.open(tts_file, std::ios::in | std::ios::binary);
   in_stream.read((char *)tts_buffer, in_size);
    size_t gcount_tts_size = in_stream.gcount();

    std::cout<<"gcount_in_size: "<<gcount_in_size<<"gcount_tts_size: "<<gcount_tts_size<<std::endl;
  // wav or pcm
  in_stream.read((char*)in_buffer, 44);
  if (in_buffer[0] == 'R' && in_buffer[1] == 'I' && in_buffer[2] == 'F' && in_buffer[3] == 'F') {
    // wav
    in_stream.seekg(44, std::ios_base::beg);

  } else {
    in_stream.seekg(0, std::ios_base::beg);
  }
    MixerImpl mixerImpl(48000, 2);
   uint16_t* data[2];
    data[0]=(uint16_t*)in_buffer;
    data[1]=(uint16_t*)tts_buffer;
  // uint16_t* data[0];
  //  data[0]=(uint16_t*)in_buffer;
  int framesize=480*4;
  int mixlengthsize=gcount_tts_size/framesize*framesize;
for(int i=0; i< gcount_tts_size/framesize ;i++)
{
        mixerImpl.Mix(2,  data , framesize/2, (uint16_t *)out_buffer);
            out_stream.write((char *)out_buffer, framesize);
    data[0]+=framesize/2;
          data[1]+=framesize/2;
}
    std::cout<<" gcount_in_size: "<<gcount_in_size<<" mixlengthsize: "<<mixlengthsize<<std::endl;
    out_stream.write((char *)in_buffer+mixlengthsize, gcount_in_size-mixlengthsize);


  if (in_buffer)free(in_buffer);
  if (tts_buffer)free(tts_buffer);
  if (out_buffer)free(out_buffer);
  // corrupted size vs. prev_size
  // Aborted (core dumped)
  // out_stream.write((char*)in_buffer, sampleCout*2);
}

int main(int argc, char* argv[]) {
  WebRtc_DeNoise("/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/capture_NS_no_sample_2022.pcm","/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/tts.pcm",
                 "../lab1/recorder_tts_mix.pcm", 48000, 2);
                   WebRtc_DeNoise("/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/recorder_ns_1.pcm","/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/tts.pcm",
                 "../lab1/recorder_tts_mix_ns_1.pcm", 48000, 2);
                   WebRtc_DeNoise("/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/recorder_ns_1_ns_1.pcm","/home/fengmao/cowa_audio/backup_git/webrtc_mixer/resource/tts.pcm",
                 "../lab1/recorder_tts_mix_ns_1_ns_1.pcm", 48000, 2);
  printf("�������棬�������...\n");
  return 0;
}
