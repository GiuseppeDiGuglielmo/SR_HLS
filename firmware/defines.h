#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_int.h"
#include "ap_fixed.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 216
#define N_INPUT_2_1 680
#define N_INPUT_3_1 3
#define OUT_HEIGHT_16 218
#define OUT_WIDTH_16 682
#define N_CHAN_16 3
#define OUT_HEIGHT_2 216
#define OUT_WIDTH_2 680
#define N_FILT_2 28
#define OUT_HEIGHT_17 218
#define OUT_WIDTH_17 682
#define N_CHAN_17 28
#define OUT_HEIGHT_4 216
#define OUT_WIDTH_4 680
#define N_FILT_4 28
#define OUT_HEIGHT_18 218
#define OUT_WIDTH_18 682
#define N_CHAN_18 28
#define OUT_HEIGHT_6 216
#define OUT_WIDTH_6 680
#define N_FILT_6 28
#define OUT_HEIGHT_19 218
#define OUT_WIDTH_19 682
#define N_CHAN_19 28
#define OUT_HEIGHT_8 216
#define OUT_WIDTH_8 680
#define N_FILT_8 28
#define OUT_HEIGHT_20 218
#define OUT_WIDTH_20 682
#define N_CHAN_20 28
#define OUT_HEIGHT_10 216
#define OUT_WIDTH_10 680
#define N_FILT_10 28
#define OUT_HEIGHT_21 218
#define OUT_WIDTH_21 682
#define N_CHAN_21 28
#define OUT_HEIGHT_12 216
#define OUT_WIDTH_12 680
#define N_FILT_12 27
#define OUT_HEIGHT_22 218
#define OUT_WIDTH_22 682
#define N_CHAN_22 27
#define OUT_HEIGHT_14 216
#define OUT_WIDTH_14 680
#define N_FILT_14 27

//hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<16,6> model_default_t;
typedef nnet::array<ap_fixed<16,6>, 3*1> input_t;
typedef nnet::array<ap_fixed<16,6>, 3*1> layer16_t;
typedef nnet::array<ap_fixed<16,6>, 28*1> layer2_t;
typedef ap_fixed<16,6> conv2d_weight_t;
typedef ap_fixed<16,6> conv2d_bias_t;
typedef ap_fixed<18,8> conv2d_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer3_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer17_t;
typedef nnet::array<ap_fixed<16,6>, 28*1> layer4_t;
typedef ap_fixed<16,6> conv2d_1_weight_t;
typedef ap_fixed<16,6> conv2d_1_bias_t;
typedef ap_fixed<18,8> conv2d_1_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer5_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer18_t;
typedef nnet::array<ap_fixed<16,6>, 28*1> layer6_t;
typedef ap_fixed<16,6> conv2d_2_weight_t;
typedef ap_fixed<16,6> conv2d_2_bias_t;
typedef ap_fixed<18,8> conv2d_2_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer7_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer19_t;
typedef nnet::array<ap_fixed<16,6>, 28*1> layer8_t;
typedef ap_fixed<16,6> conv2d_3_weight_t;
typedef ap_fixed<16,6> conv2d_3_bias_t;
typedef ap_fixed<18,8> conv2d_3_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer9_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer20_t;
typedef nnet::array<ap_fixed<16,6>, 28*1> layer10_t;
typedef ap_fixed<16,6> conv2d_4_weight_t;
typedef ap_fixed<16,6> conv2d_4_bias_t;
typedef ap_fixed<18,8> conv2d_4_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer11_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 28*1> layer21_t;
typedef nnet::array<ap_fixed<16,6>, 27*1> layer12_t;
typedef ap_fixed<16,6> conv2d_5_weight_t;
typedef ap_fixed<16,6> conv2d_5_bias_t;
typedef ap_fixed<18,8> conv2d_5_relutable_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 27*1> layer13_t;
typedef nnet::array<ap_fixed<16,6,AP_RND_CONV,AP_SAT>, 27*1> layer22_t;
typedef nnet::array<ap_fixed<16,6>, 27*1> result_t;
typedef nnet::array<ap_fixed<16,6>, 27*1> layer14_t;
typedef ap_fixed<16,6> conv2d_6_weight_t;
typedef ap_fixed<16,6> conv2d_6_bias_t;

typedef nnet::array<ap_fixed<16,6>, 27*1> layer_up_t;

typedef nnet::array<ap_fixed<16,6>, 27*1> layer_merge_t;

#endif
