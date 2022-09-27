#ifndef MYPROJECT_BRIDGE_H_
#define MYPROJECT_BRIDGE_H_

#include "firmware/myproject.h"
#include "firmware/nnet_utils/nnet_helpers.h"
#include <algorithm>
#include <map>

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


namespace nnet {
    bool trace_enabled = false;
    std::map<std::string, void *> *trace_outputs = NULL;
    size_t trace_type_size = sizeof(double);
}

extern "C" {

struct trace_data {
    const char *name;
    void *data;
};

void allocate_trace_storage(size_t element_size) {
    nnet::trace_enabled = true;
    nnet::trace_outputs = new std::map<std::string, void *>;
    nnet::trace_type_size = element_size;
}

void free_trace_storage() {
    for (std::map<std::string, void *>::iterator i = nnet::trace_outputs->begin(); i != nnet::trace_outputs->end(); i++) {
        void *ptr = i->second;
        free(ptr);
    }
    nnet::trace_outputs->clear();
    delete nnet::trace_outputs;
    nnet::trace_outputs = NULL;
    nnet::trace_enabled = false;
}

void collect_trace_output(struct trace_data *c_trace_outputs) {
    int ii = 0;
    for (std::map<std::string, void *>::iterator i = nnet::trace_outputs->begin(); i != nnet::trace_outputs->end(); i++) {
        c_trace_outputs[ii].name = i->first.c_str();
        c_trace_outputs[ii].data = i->second;
        ii++;
    }
}

// Wrapper of top level function for Python bridge
void myproject_float(
    float input_1[N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1]
    , float layer14_out[OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14]
) {
    
    hls::stream<input_t> input_1_ap("input_1");
    nnet::convert_data<float, input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1, input_1_ap);

    hls::stream<result_t> layer14_out_ap("layer14_out");

    myproject(input_1_ap,layer14_out_ap,w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14);

    nnet::convert_data<result_t, float, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out_ap, layer14_out);
}

void myproject_double(
    double input_1[N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1]
    , double layer14_out[OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14]
) {
    hls::stream<input_t> input_1_ap("input_1");
    nnet::convert_data<double, input_t, N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1>(input_1, input_1_ap);

    hls::stream<result_t> layer14_out_ap("layer14_out");

    myproject(input_1_ap,layer14_out_ap,w2,b2,w4,b4,w6,b6,w8,b8,w10,b10,w12,b12,w14,b14);

    nnet::convert_data<result_t, double, OUT_HEIGHT_14*OUT_WIDTH_14*N_FILT_14>(layer14_out_ap, layer14_out);
}

}

#endif
