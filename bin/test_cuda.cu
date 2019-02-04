#include <cstdio>
#include <cstdlib>
#include <string>
#include <cuda_runtime.h>

#include <iostream>


__global__
void print(const char * message, size_t length)
{
  //printf("blockIdx.x, threadIdx.x: %d, %d\n", blockIdx.x, threadIdx.x);
  for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < length; i += blockDim.x * gridDim.x)
    printf("%c", message[i]);
}


int main(int argc, const char* argv[]) {
  std::string message;
  if (argc == 1) {
    message = "Hello world!";
  } else {
    message = argv[1];
  }
  
  char * buffer;
  cudaMalloc(& buffer, message.size());
  cudaMemcpy(buffer, message.data(), message.size(), cudaMemcpyDefault);
  
  print<<<16,1>>>(buffer, message.size());
  cudaDeviceSynchronize();
  cudaGetLastError();
  std::cout << std::endl;
  
  print<<<4,4>>>(buffer, message.size());
  cudaDeviceSynchronize();
  cudaGetLastError();
  std::cout << std::endl;
  
  print<<<1,16>>>(buffer, message.size());
  cudaDeviceSynchronize();
  cudaGetLastError();
  std::cout << std::endl;
  
  cudaFree(buffer);
}


