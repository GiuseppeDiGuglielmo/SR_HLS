#ifndef NNET_UPSAMPLE_STREAM_H_
#define NNET_UPSAMPLE_STREAM_H_

#include "nnet_common.h"
#include "hls_stream.h"

namespace nnet {

template<class datain_T, class dataout_T>
void upsample_channels(
    hls::stream<datain_T> &image,
    hls::stream<dataout_T> &resized
) {
	assert(dataout_T::size % datain_T::size == 0);
	constexpr unsigned ratio = dataout_T::size / datain_T::size;

	datain_T  in_data = image.read();
    dataout_T out_data;

    Upsample: for (unsigned r = 0; r < ratio; r++) {
        #pragma HLS UNROLL
        const unsigned outbase = r * datain_T::size;

        ChanIter: for (unsigned i = 0; i < datain_T::size; i++) {
            #pragma HLS UNROLL
            const unsigned outidx = outbase + i;
            out_data[outidx] = in_data[i];
        }
    }
}

}

#endif
