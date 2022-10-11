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
#include <iostream>

#include "myproject.h"
#include "parameters.h"

void myproject(
    hls::stream<input_t> &input_1,
    hls::stream<result_t> &result,
    conv2d_weight_t w2[756], 
    conv2d_bias_t b2[28], 
    conv2d_1_weight_t w4[7056], 
    conv2d_1_bias_t b4[28], 
    conv2d_2_weight_t w6[7056], 
    conv2d_2_bias_t b6[28], 
    conv2d_3_weight_t w8[7056], 
    conv2d_3_bias_t b8[28], 
    conv2d_4_weight_t w10[7056], 
    conv2d_4_bias_t b10[28], 
    conv2d_5_weight_t w12[6804], 
    conv2d_5_bias_t b12[27], 
    conv2d_6_weight_t w14[6561], 
    conv2d_6_bias_t b14[27]
) {

    //hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=input_1,result 
    #pragma HLS INTERFACE bram port=w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14 
    #pragma HLS DATAFLOW 

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        //hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<conv2d_weight_t, 756>(w2, "w2.txt");
        nnet::load_weights_from_txt<conv2d_bias_t, 28>(b2, "b2.txt");
        nnet::load_weights_from_txt<conv2d_1_weight_t, 7056>(w4, "w4.txt");
        nnet::load_weights_from_txt<conv2d_1_bias_t, 28>(b4, "b4.txt");
        nnet::load_weights_from_txt<conv2d_2_weight_t, 7056>(w6, "w6.txt");
        nnet::load_weights_from_txt<conv2d_2_bias_t, 28>(b6, "b6.txt");
        nnet::load_weights_from_txt<conv2d_3_weight_t, 7056>(w8, "w8.txt");
        nnet::load_weights_from_txt<conv2d_3_bias_t, 28>(b8, "b8.txt");
        nnet::load_weights_from_txt<conv2d_4_weight_t, 7056>(w10, "w10.txt");
        nnet::load_weights_from_txt<conv2d_4_bias_t, 28>(b10, "b10.txt");
        nnet::load_weights_from_txt<conv2d_5_weight_t, 6804>(w12, "w12.txt");
        nnet::load_weights_from_txt<conv2d_5_bias_t, 27>(b12, "b12.txt");
        nnet::load_weights_from_txt<conv2d_6_weight_t, 6561>(w14, "w14.txt");
        nnet::load_weights_from_txt<conv2d_6_bias_t, 27>(b14, "b14.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    hls::stream<input_t> layer0_out("layer0_out");
    #pragma HLS STREAM variable=layer0_out depth=146880
    hls::stream<input_t> layer1_out("layer1_out");
    #pragma HLS STREAM variable=layer1_out depth=1048576
    nnet::clone_stream<input_t, input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1, layer0_out, layer1_out); // clone_input_1

    hls::stream<layer16_t> layer16_out("layer16_out");
    #pragma HLS STREAM variable=layer16_out depth=146550
    nnet::zeropad2d_cl<input_t, layer16_t, config16>(layer0_out, layer16_out); // zp2d_conv2d

    hls::stream<layer2_t> layer2_out("layer2_out");
    #pragma HLS STREAM variable=layer2_out depth=1
    nnet::conv_2d_cl<layer16_t, layer2_t, config2>(layer16_out, layer2_out, w2, b2); // conv2d

    hls::stream<layer3_t> layer3_out("layer3_out");
    #pragma HLS STREAM variable=layer3_out depth=1
    nnet::relu<layer2_t, layer3_t, relu_config3>(layer2_out, layer3_out); // conv2d_relu

    hls::stream<layer17_t> layer17_out("layer17_out");
    #pragma HLS STREAM variable=layer17_out depth=36329
    nnet::zeropad2d_cl<layer3_t, layer17_t, config17>(layer3_out, layer17_out); // zp2d_conv2d_1

    hls::stream<layer4_t> layer4_out("layer4_out");
    #pragma HLS STREAM variable=layer4_out depth=1
    nnet::conv_2d_cl<layer17_t, layer4_t, config4>(layer17_out, layer4_out, w4, b4); // conv2d_1

    hls::stream<layer5_t> layer5_out("layer5_out");
    #pragma HLS STREAM variable=layer5_out depth=1
    nnet::relu<layer4_t, layer5_t, relu_config5>(layer4_out, layer5_out); // conv2d_1_relu

    hls::stream<layer18_t> layer18_out("layer18_out");
    #pragma HLS STREAM variable=layer18_out depth=678
    nnet::zeropad2d_cl<layer5_t, layer18_t, config18>(layer5_out, layer18_out); // zp2d_conv2d_2

    hls::stream<layer6_t> layer6_out("layer6_out");
    #pragma HLS STREAM variable=layer6_out depth=1
    nnet::conv_2d_cl<layer18_t, layer6_t, config6>(layer18_out, layer6_out, w6, b6); // conv2d_2

    hls::stream<layer7_t> layer7_out("layer7_out");
    #pragma HLS STREAM variable=layer7_out depth=1
    nnet::relu<layer6_t, layer7_t, relu_config7>(layer6_out, layer7_out); // conv2d_2_relu

    hls::stream<layer19_t> layer19_out("layer19_out");
    #pragma HLS STREAM variable=layer19_out depth=678
    nnet::zeropad2d_cl<layer7_t, layer19_t, config19>(layer7_out, layer19_out); // zp2d_conv2d_3

    hls::stream<layer8_t> layer8_out("layer8_out");
    #pragma HLS STREAM variable=layer8_out depth=1
    nnet::conv_2d_cl<layer19_t, layer8_t, config8>(layer19_out, layer8_out, w8, b8); // conv2d_3

    hls::stream<layer9_t> layer9_out("layer9_out");
    #pragma HLS STREAM variable=layer9_out depth=1
    nnet::relu<layer8_t, layer9_t, relu_config9>(layer8_out, layer9_out); // conv2d_3_relu

    hls::stream<layer20_t> layer20_out("layer20_out");
    #pragma HLS STREAM variable=layer20_out depth=678
    nnet::zeropad2d_cl<layer9_t, layer20_t, config20>(layer9_out, layer20_out); // zp2d_conv2d_4

    hls::stream<layer10_t> layer10_out("layer10_out");
    #pragma HLS STREAM variable=layer10_out depth=1
    nnet::conv_2d_cl<layer20_t, layer10_t, config10>(layer20_out, layer10_out, w10, b10); // conv2d_4

    hls::stream<layer11_t> layer11_out("layer11_out");
    #pragma HLS STREAM variable=layer11_out depth=1
    nnet::relu<layer10_t, layer11_t, relu_config11>(layer10_out, layer11_out); // conv2d_4_relu

    hls::stream<layer21_t> layer21_out("layer21_out");
    #pragma HLS STREAM variable=layer21_out depth=678
    nnet::zeropad2d_cl<layer11_t, layer21_t, config21>(layer11_out, layer21_out); // zp2d_conv2d_5

    hls::stream<layer12_t> layer12_out("layer12_out");
    #pragma HLS STREAM variable=layer12_out depth=1
    nnet::conv_2d_cl<layer21_t, layer12_t, config12>(layer21_out, layer12_out, w12, b12); // conv2d_5

    hls::stream<layer13_t> layer13_out("layer13_out");
    #pragma HLS STREAM variable=layer13_out depth=1
    nnet::relu<layer12_t, layer13_t, relu_config13>(layer12_out, layer13_out); // conv2d_5_relu

    hls::stream<layer22_t> layer22_out("layer22_out");
    #pragma HLS STREAM variable=layer22_out depth=7937
    nnet::zeropad2d_cl<layer13_t, layer22_t, config22>(layer13_out, layer22_out); // zp2d_conv2d_6

    hls::stream<layer14_t> layer14_out("layer14_out");
    #pragma HLS STREAM variable=layer14_out depth=1
    nnet::conv_2d_cl<layer22_t, layer14_t, config14>(layer22_out, layer14_out, w14, b14); // conv2d_6

    // the other branch
    hls::stream<layer23_t> layer23_out("layer23_out");
    #pragma HLS STREAM variable=layer14_out depth=1
    nnet::upsample_channels<input_t, layer23_t, config_upsample>(layer1_out, layer23_out);

    hls::stream<layer24_t> layer24_out("layer24_out");
    #pragma HLS STREAM variable=layer14_out depth=1
    nnet::add<layer23_t, layer14_t, layer24_t, config_merge>(layer23_out, layer14_out, layer24_out); // teacher_layer_skip

    nnet::depth_to_space<layer24_t, result_t, config_dts>(layer24_out, result);

}
