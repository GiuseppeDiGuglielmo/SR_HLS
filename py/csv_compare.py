import csv
import sys
import argparse

csv.field_size_limit(sys.maxsize)

if __name__ == '__main__':
    #csim_file="../myproject_prj/solution1/csim/build/output.dat"
    #cosim_file="../myproject_prj/solution1/sim/wrapc/output.dat"
    parser = argparse.ArgumentParser()
    parser.add_argument('--csim_file', type=str, required=True)
    parser.add_argument('--cosim_file', type=str, required=True)
    args = parser.parse_args()
    csim_file = args.csim_file
    cosim_file = args.cosim_file

    csim_file = open(csim_file, "r")
    csim_reader = csv.reader(csim_file, delimiter=" ")
    csim_output = next(csim_reader)

    cosim_file = open(cosim_file, "r")
    cosim_reader = csv.reader(cosim_file, delimiter=" ")
    cosim_output = next(cosim_reader)

    if len(csim_output) != len(cosim_output):
        print("ERROR: CSV files have different length!")
        print("ERROR:", csim_file, "size:", len(csim_output))
        print("ERROR:", cosim_file, "size:", len(cosim_output))
        sys.exit(1)

    N = len(csim_output)

    differences = 0
    for i in range(N):
        if csim_output[i] != cosim_output[i]:
            differences = differences + 1
            print("ERROR: [", i, "] ", csim_output[i], "!=", cosim_output[i])

    print("Total differences:", differences)
    print("Total differences (%):", 100*differences/float(N))

