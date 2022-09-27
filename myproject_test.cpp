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
  //load input data from text file
  std::ifstream fin("tb_data/tb_input_features.dat");
  //load predictions from text file
  std::ifstream fpr("tb_data/tb_output_predictions.dat");

#ifdef RTL_SIM
  std::string RESULTS_LOG = "tb_data/rtl_cosim_results.log";
#else
  std::string RESULTS_LOG = "tb_data/csim_results.log";
#endif
  std::ofstream fout(RESULTS_LOG);

  std::string iline;
  std::string pline;
  int e = 0;

  //hls-fpga-machine-learning insert weights

  //hls-fpga-machine-learning insert load weights

  if (fin.is_open() && fpr.is_open()) {
    while ( std::getline(fin,iline) && std::getline (fpr,pline) ) {
      if (e % CHECKPOINT == 0) std::cout << "Processing input " << e << std::endl;
      char* cstr=const_cast<char*>(iline.c_str());
      char* current;
      std::vector<float> in;
      current=strtok(cstr," ");
      while(current!=NULL) {
        in.push_back(atof(current));
        current=strtok(NULL," ");
      }
      cstr=const_cast<char*>(pline.c_str());
      std::vector<float> pr;
      current=strtok(cstr," ");
      while(current!=NULL) {
        pr.push_back(atof(current));
        current=strtok(NULL," ");
      }

      //hls-fpga-machine-learning insert data
      hls::stream<input_t> input_1("input_1");
      nnet::copy_data<float, input_t, 0, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(in, input_1);
      hls::stream<result_t> layer14_out("layer14_out");

      //hls-fpga-machine-learning insert top-level-function
      myproject(input_1,layer14_out,w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14);

      if (e % CHECKPOINT == 0) {
        std::cout << "Predictions" << std::endl;
        //hls-fpga-machine-learning insert predictions
        for(int i = 0; i < OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14; i++) {
          std::cout << pr[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Quantized predictions" << std::endl;
        //hls-fpga-machine-learning insert quantized
        nnet::print_result<result_t, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out, std::cout, true);
      }
      e++;

      //hls-fpga-machine-learning insert tb-output
      nnet::print_result<result_t, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out, fout);

    }
    fin.close();
    fpr.close();
  } else {
    std::cout << "INFO: Unable to open input/predictions file, using default input." << std::endl;

    //hls-fpga-machine-learning insert zero
    hls::stream<input_t> input_1("input_1");
    nnet::fill_zero<input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1);
    hls::stream<result_t> layer14_out("layer14_out");

    //hls-fpga-machine-learning insert top-level-function
    myproject(input_1,layer14_out,w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14);

    //hls-fpga-machine-learning insert output
    nnet::print_result<result_t, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out, std::cout, true);

    //hls-fpga-machine-learning insert tb-output
    nnet::print_result<result_t, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out, fout);

  }

  fout.close();
  std::cout << "INFO: Saved inference results to file: " << RESULTS_LOG << std::endl;

  return 0;
}
