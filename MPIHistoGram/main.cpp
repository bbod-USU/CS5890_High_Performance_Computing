#include <iostream>
#include <string>
#include <mpi.h>
#include <cstdlib>
#include <valarray>
#define MCW MPI_COMM_WORLD


MPI_Status status;
float *GenerateArray();
void ComputeHistogram(float *data_array, int rank, int &world_size);

void PrintResults(float *my_bin_max, float *my_bin_min, int *my_bins);
long stoi(const char *s);
void PrintTimingResults();
float stof(const char* s);
int bin_count, data_count;
float min_meas, max_meas;
const int Master = 0;
double total_time_start, total_time_stop;
double step_3to5_start, step_3to5_stop;
double step_3_stop;

int main(int argc, char *argv[]) {
    ///Initialize MPI
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    total_time_start = MPI_Wtime();
    float* data_array;
    if(!rank) {
        ///GetInputData
        bin_count = stoi(argv[1]);//static_cast<int>(argv[1]);
        data_count = stoi(argv[4]);//static_cast<int>(std::stoi(argv[4]));
        min_meas = stof(argv[2]);//static_cast<int>(std::stof(argv[2]));
        max_meas = stof(argv[3]);//static_cast<int>(std::stof(argv[3]));

        ///Create the array of floats
        data_array = static_cast<float *> (calloc(data_count, sizeof(float)));
        data_array = GenerateArray();

    }
    MPI_Barrier(MCW);
    ///BCast to all ranks
    MPI_Bcast(&bin_count, 1, MPI_INT, Master, MCW);
    MPI_Bcast(&min_meas, 1, MPI_FLOAT, Master, MCW);
    MPI_Bcast(&max_meas, 1, MPI_FLOAT, Master, MCW);
    MPI_Bcast(&data_count, 1, MPI_INT, Master, MCW);
    ComputeHistogram(data_array, rank, size);
    total_time_stop = MPI_Wtime();
    if(!rank)
        PrintTimingResults();
    MPI_Finalize();
    return 0;
}
long stoi(const char *s)
{
    long i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}
float stof(const char* s){
    float rez = 0, fact = 1;
    if (*s == '-'){
        s++;
        fact = -1;
    };
    for (int point_seen = 0; *s; s++){
        if (*s == '.'){
            point_seen = 1;
            continue;
        };
        int d = *s - '0';
        if (d >= 0 && d <= 9){
            if (point_seen) fact /= 10.0f;
            rez = rez * 10.0f + (float)d;
        };
    };
    return rez * fact;
};

void PrintTimingResults() {
    std::cout << std::fixed << "Timing Results \n\t"
    << "Total Time: " << total_time_stop-total_time_start
    << "\n\tStep 3 Time: " << step_3_stop-step_3to5_start
    << "\n\tStep 3 - 5 Time: " << step_3to5_stop-step_3to5_start << std::endl;
}

void ComputeHistogram(float *data_array, int rank, int &world_size) {
    int elements_per_rank = data_count / world_size;
    MPI_Barrier(MCW);
    float bin_range = (max_meas-min_meas)/bin_count;

    ///Allocate all the memory for arrays
    float *my_slice = static_cast<float *>(calloc(elements_per_rank, sizeof(float)));
    int *my_bins = static_cast<int *>(calloc(bin_count, sizeof(int)));
    float *my_bin_min = static_cast<float *>(calloc(bin_count, sizeof(int)));
    float *my_bin_max = static_cast<float *>(calloc(bin_count, sizeof(int)));

    ///if master split and send the data_array
    step_3to5_start = MPI_Wtime();
    if (!rank) {
        for (int i = 0; i < world_size; i++) {
            std::copy(data_array + (i * elements_per_rank), data_array + (i * elements_per_rank + elements_per_rank),
                      my_slice + 0);
            MPI_Send(my_slice, elements_per_rank, MPI_FLOAT, i, 0, MCW);
        }
    }
    MPI_Barrier(MCW);
    ///Get my piece of the pie from master
    MPI_Recv(my_slice, elements_per_rank, MPI_FLOAT, Master, 0, MCW, &status);
    step_3_stop = MPI_Wtime();

    ///Calculate the min and max of each bin
    for(int i = 0; i < bin_count; i++){
        int offset = 0;
        if(i == 0)
            offset = min_meas;
        my_bin_min [i] = i*(bin_range)+offset;
        my_bin_max[i] = i*(bin_range) + offset + bin_range;
    }
    ///Calculate bins
    for(int i = 0; i < elements_per_rank; i++){
        float value = my_slice[i];
        for(int j = 0; j < bin_count; j++){
            if(value < my_bin_max[j] && value >= my_bin_min[j])
                my_bins[j] ++;
        }
    }
    ///if not master send my data back to master
    if(rank){
        MPI_Send(my_bins, bin_count, MPI_INT, Master, 0, MCW);
    }
    ///if master compile bin counts.
    else{
        for(int i = 1; i<world_size; i++) {
            int *tmp_bins = static_cast<int *>(calloc(bin_count, sizeof(int)));
            MPI_Recv(tmp_bins, bin_count, MPI_INT, i, 0, MCW, &status);
            for(int j = 0; j<bin_count; j++){
                my_bins[j] += tmp_bins[j];
            }
            free(tmp_bins);
        }
        ///cleanup remaining data_array elements
        int remainder = data_count%bin_count;
        for(int i =data_count-remainder; i < data_count; i++){
            for(int j = 0; j < bin_count; j++){
                if(data_array[i] < my_bin_max[j] && data_array[i] >= my_bin_min[j])
                    my_bins[j] ++;
            }
        }
        PrintResults(my_bin_max, my_bin_min, my_bins);
    }
    step_3to5_stop = MPI_Wtime();
    free(my_bins);
    free(my_bin_min);
    free(my_bin_max);
    free(my_slice);
}

/// Prints the results from the master process.
/// \param my_bin_max
/// \param my_bin_min
/// \param my_bins
void PrintResults(float *my_bin_max, float *my_bin_min, int *my_bins) {
    std::cout << "Bins: \n\t";
    for(int i = 0; i < bin_count; i++){
        std::cout << "[" <<my_bin_min[i]<<","<<my_bin_max[i]<< ") ";
    }
    std::cout << "\nBin Counts: \n\t|";
    for(int i = 0; i < bin_count; i++){
        std::cout <<my_bins[i] <<"|";
    }
    std::cout << std::endl;
}

float* GenerateArray(){
    srand(100);
    float* returnArray = static_cast<float *>(calloc(data_count, sizeof(float)));
    int i;
    for(i = 0; i < data_count; ++i)
        returnArray[i] = (float) rand() / RAND_MAX * (max_meas- min_meas) + min_meas;
    return returnArray;
}
