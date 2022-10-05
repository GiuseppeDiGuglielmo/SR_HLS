# Quick Start

Run inference with SR model and generate a few more files that you may need
```
make run
```

## Details
- The script loads as input a low-resolution (LR) image in JPG format (`./jpg/input.jpg`)
- It converts the input LR image in NPY and CSV format (`./npy/input.npy`, `./csv/input.csv`)
- The script runs inference and saves the output high-resolution (HR) image as NPY, JPG, and CSV format (`./npy/output.npy`, `./jpg/output.jpg`, and `./csv/output.csv`)

Please note that you can visualize the JPG images to compare input and output results. The CSV files instead are used during the compilation of the application (csim) to hardcode inputs and (expected) outputs.
