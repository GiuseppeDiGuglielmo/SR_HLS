//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cfloat>

#include "firmware/myproject.h"
#include "firmware/nnet_utils/nnet_helpers.h"

//hls-fpga-machine-learning insert bram
#include "firmware/weights/w2.h"
#include "firmware/weights/b2.h"
#include "firmware/weights/w4.h"
#include "firmware/weights/b4.h"
#include "firmware/weights/w6.h"
#include "firmware/weights/b6.h"
#include "firmware/weights/w8.h"
#include "firmware/weights/b8.h"
#include "firmware/weights/w10.h"
#include "firmware/weights/b10.h"
#include "firmware/weights/w12.h"
#include "firmware/weights/b12.h"
#include "firmware/weights/w14.h"
#include "firmware/weights/b14.h"

#define CHECKPOINT 5000

namespace nnet {
    bool trace_enabled = true;
    std::map<std::string, void *> *trace_outputs = NULL;
    size_t trace_type_size = sizeof(double);
}

int main(int argc, char **argv)
{
  std::string OUTPUT_DAT = "0001.dat";
  std::ofstream fout(OUTPUT_DAT);

  hls::stream<input_t> input_1("input_1");
  std::vector<float> in = {
#include "csv/inputs/0001x3.csv"
  };
  nnet::copy_data<float, input_t, 0, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(in, input_1);
  hls::stream<result_t> layer14_out("layer14_out");

  std::cout << "INFO: Input image shape : " << N_INPUT_1_1 << "x" << N_INPUT_2_1 << "x" << N_INPUT_3_1 << std::endl;
  std::cout << "INFO: Input image pixels: " << N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1 << std::endl;


  myproject(input_1,layer14_out,w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14);

  //nnet::print_result<result_t, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out, std::cout, true);

  nnet::print_result<result_t, OUT_HEIGHT_DTS*OUT_WIDTH_DTS*N_CHAN_DTS>(layer14_out, fout);
  fout.close();

  std::cout << "INFO: Output image shape : " << OUT_HEIGHT_DTS << "x" << OUT_WIDTH_DTS << "x" << N_CHAN_DTS << std::endl;
  std::cout << "INFO: Output image pixels: " << OUT_HEIGHT_DTS*OUT_WIDTH_DTS*N_CHAN_DTS << std::endl;

  std::cout << "INFO: Saved inference results to file: " << std::experimental::filesystem::current_path().string() + "/" + OUTPUT_DAT << std::endl;

  return 0;
}
