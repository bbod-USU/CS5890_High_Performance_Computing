/* Generate the data */
Generate_data(min_meas, max_meas, data, data_count);

/* Create bins for storing counts */
Generate_bins(min_meas, max_meas, bin_maxes, bin_counts, bin_count);

/* Count number of values in each bin */
// gets thread count from command line
int thread_count = strtol(argv[1], Null, 10)
//sets up threads, share nescessary variables and make private variables that should not be shared. set up the reduction tree for bin_counts
#pragma omp parallel num_threads(thread_count)
shared(bin_counts) private(my_rank, my_offset, data_count, bin_count, local_bin_counts) reduction(+:bin_counts[])
int j;
//gets threads number/rank
int my_rank = omp_get_thread_num();
int my_offset = my_rank*bin_count;
//parallel for loop
#pragma omp for
for (i = 0; i < data_count; i++) {
    bin = What_bin(data[i], bin_maxes, bin_count, min_meas);
    loc_bin_counts[my_offset + bin]++;
}
//paralize the outer for loop
#pragma omp for
for (i = 0; i < bin_count; i++)
    for (j = 0; j < thread_count; j++) {
        bin_counts[i] += loc_bin_counts[j*bin_count + i];
    }
