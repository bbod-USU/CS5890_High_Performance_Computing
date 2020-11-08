#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct calc_hist_data_t
{
    float *data_start; // start of the sequence chunk
    float *data_end; // end of the sequence chunk
    int a, b; // min and max range element values
    int bin_count; // length of histogram
    float interval; // how much to jump from bin to bin
} calc_hist_data_t;

// Computes a histogram based off on a sequence chunk.
void *calculate_histogram(void *hist_data)
{
    calc_hist_data_t *arg = (calc_hist_data_t *)hist_data;

    // Allocate some space to hold our locally computed histogram.
    int *local_histogram = static_cast<int *>(calloc(arg->bin_count, sizeof(*local_histogram)));

    // Computes the histogram of this data chunk.
    for (float *pos = arg->data_start; pos != arg->data_end; ++pos)
    {
        int bin_index = (*pos - arg->a) / arg->interval;
        local_histogram[bin_index] += 1;
    }

    // Exits the thread and returns my local histogram to the joiner.
    pthread_exit(local_histogram);
}

int main(int argc, char *argv[])
{
    // Selects a "random" seed for the rand engine.
    srand((unsigned int)time(NULL));

    float a, b; // Min and max range values.
    int data_count; // Length of the random numbers sequence.
    int bin_count; // Number of bins in the histogram.

    printf("Type in the values for: <a> <b> <data_count> <bin_count>: ");
    fflush(stdout);
    scanf("%f %f %d %d", &a, &b, &data_count, &bin_count);

    // Interval between each bin.
    float bin_size = (b - a) / (float)bin_count;

    // Query the number of processors on this machine.
    int thread_count = 1;

    // Chunk size for each thread.
    int thread_data_count = data_count / thread_count;

    // Extra size that will be distributed to chunks later.
    int spare_data_count = data_count % thread_count;

    // Holds the sequence of the generated random numbers in the range [a, b].
    float *data = static_cast<float *>(malloc(data_count * sizeof(*data)));

    // Generate the sequence of random numbers in ther range [a, b].
    for (int i = 0; i < data_count; ++i)
    {
        data[i] = (float)rand() / (float)RAND_MAX * (b - a) + a;
    }

    // Holds the handle of each thread.
    pthread_t threads[thread_count];

    // Holds the argument for each thread.
    calc_hist_data_t *args = static_cast<calc_hist_data_t *>(calloc(thread_count, sizeof(*args)));

    // Current chunk data start for an iteration.
    float *local_data = data;

    for (int i = 0; i < thread_count; ++i)
    {
        // Take `spare_data_count` into account when separating a chunk and
        // decrement it at each iteration. This works because
        // `spare_data_count` will never be equal to or greater than
        // `thread_data_count`.
        int chunk_start_length = thread_data_count + !!spare_data_count;

        // Assigns this sequence chunk to this thread to process.
        args[i] = (calc_hist_data_t){
                .data_start = local_data,
                .data_end = local_data + thread_data_count + !!spare_data_count,
                .a = static_cast<int>(a),
                .b = static_cast<int>(b),
                .bin_count = bin_count,
                .interval = bin_size,
        };

        // Advances the chunk start for the next iteration.
        local_data += thread_data_count + !!spare_data_count;

        if (spare_data_count)
            --spare_data_count;

        // Instantiate a thread to compute this chunk's histogram.
        pthread_create(&threads[i], NULL, calculate_histogram,
                       (void *)&args[i]);
    }

    // Holds the sum of all local histograms.
    int *histogram = static_cast<int *>(calloc(bin_count, sizeof(*histogram)));

    // Computes the sum of all local histograms.
    for (long i = 0; i < thread_count; ++i)
    {
        int *local_histogram = NULL;
        // Wait for the thread `i` to finish running and sum its returned local
        // histogram into our global histogram.
        pthread_join(threads[i], (void **)&local_histogram);
        for (int i = 0; i < bin_count; ++i)
        {
            histogram[i] += local_histogram[i];
        }
        free(local_histogram);
    }

    // Now, let's pretty print some information.
    {
        int max_bin_count = 0;

        // Get the maximum bin counting value.
        for (int i = 0; i < bin_count; ++i)
        {
            if (histogram[i] > max_bin_count)
                max_bin_count = histogram[i];
        }

        // Pretty prints the histogram vector.
        printf(
                "sequence range: [%.2f, %.2f]\nsequence length: %d\nnumber of "
                "bins: %d\n"
                "bin_size: %.2f\n",
                a, b, data_count, bin_count, bin_size);
        for (int i = 0; i < bin_count; ++i)
        {
            float bin_index = (float)i * bin_size + a;
            printf("[%.2f, %.2f) |", bin_index, bin_index + bin_size);
            int row_width = ((float)histogram[i] / (float)max_bin_count) * 40.f;
            for (int j = 0; j < row_width; ++j)
            {
                printf("#");
            }
            printf(" %d\n", histogram[i]);
        }
        fflush(stdout);
    }

    // You already know: looking for freeeeeedom!
    free(data);
    free(args);
    free(histogram);

    // Last thing that main() should do.
    pthread_exit(NULL);
}