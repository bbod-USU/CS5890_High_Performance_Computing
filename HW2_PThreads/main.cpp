#include <iostream>
#include <pthread.h>
#include <cstdlib>

int thread_count, bin_count, data_count, thread_data_count, leftover_data_count;
float min_meas, max_meas, bin_size;
//setup global histogram with calloc.
int* global_histogram;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void ParseArgs(int argc, char **args);

float* GenerateArray();

void * Work(void *pVoid);

int main(int argc, char* argv[]) {
    ///serial functions
    ParseArgs(argc, argv);
    float *array = static_cast<float *>(calloc(data_count, sizeof(*array)));
    array = GenerateArray();

    global_histogram = static_cast<int*>(calloc(bin_count, sizeof(*global_histogram)));
    pthread_t thread[thread_count];
    for(int i = 0; i < thread_count; i++){
        //create all the threads
        pthread_create(&thread[i], nullptr, Work, &array[i*(data_count/thread_count)]);
    }
    for(auto i = 0; i<thread_count; i++){
        //wait for all the threads to finish.
        pthread_join(thread[i], nullptr);
    }
    //cleanup leftovers
    auto left_over_count = data_count % thread_count;
    pthread_create(&thread[0], nullptr, Work, &array[data_count-left_over_count]);
    pthread_join(thread[0], nullptr);


    printf("bin range: ");
    for (int i = 0; i < bin_count; i++){
        float lo_bin = (float)i * bin_size + min_meas;
        printf("[%f, %f) ", lo_bin, lo_bin+bin_size);
    }
    printf("\nbin count: ");
    for (int i = 0; i < bin_count; i++) {
        printf("bin %i [%i], ", i, global_histogram[i]);
    }
    pthread_exit(nullptr);
}

///Does the work to calculate the threads histogram
void * Work(void *pVoid){
    auto *thread = (float*)pVoid;
    for (int i = 0; i < data_count/thread_count ; i++){
        int binNum = (int)((thread[i] - min_meas) / bin_size);
        pthread_mutex_lock(&mutex);
        global_histogram[binNum]++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);

}
///Generates array of random.
float* GenerateArray(){
    srand(100);
    auto* returnArray = new float [data_count];
    for(int i = 0; i < data_count; ++i)
        returnArray[i] = (float) rand() / RAND_MAX * (max_meas - min_meas) + min_meas;
    return returnArray;
}

void ParseArgs(int argc, char **args) {
    //try and parse the args if anything is wrong throw an handle the exception.
    try {
        thread_count = std::stoi(args[1]);
        bin_count = std::stoi(args[2]);
        min_meas = std::stof(args[3]);
        max_meas = std::stof(args[4]);
        data_count = std::stoi(args[5]);
        if(argc > 6)
            throw;
        bin_size = (max_meas-min_meas)/(float)bin_count;
        // set the total data for each thread and account for the "extra"
        thread_data_count = data_count/thread_count;
        leftover_data_count = data_count % thread_count;
    } catch (std::exception& e) {
        std::cerr << "Invalid input data: " << std::endl << "\t"<<e.what() << std::endl;
    }
}
