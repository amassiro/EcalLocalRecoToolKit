#include "fitrechit_kernel.cuh"


__global__ void 
kernel_print() {
  printf("Hello!\n");
}

void non_kernel_print(int nblocks, int nthreads_per_block) {
  kernel_print<<<nblocks, nthreads_per_block>>>();
}




