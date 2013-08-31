__kernel void  gaussian_not_image( __constant float * mask, __global float* input, __global float* output) 
{
  int width_output = get_global_size(0); 
  int width = get_global_size(0) + 2; 

  int j = get_global_id(0); //column number
  int i = get_global_id(1) + 1; //row number
  int iout = get_global_id(1); 

  int ptr = i * width + j; 
  int ptro = iout * width_output+ j; 

  output[ptro] = 
  input[(i-1)*width + j -1] * mask[0] + 
  input[(i-1)*width + j] * mask[1] + 
  input[(i-1)*width + j+1] * mask[2] +
  input[(i)*width + j-1] * mask[3] +
  input[(i)*width + j] * mask[4] +
  input[(i)*width + j+1] * mask[5] +
  input[(i+1)*width + j-1] * mask[6] +
  input[(i+1)*width + j] * mask[7] +
  input[(i+1)*width + j+1] *mask[8] ;
  
}

#define BLOCK_SIZE 32

const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_MIRRORED_REPEAT | CLK_FILTER_NEAREST;


__kernel void  convolution(__read_only image2d_t input, __write_only image2d_t output, __global float * gaussian, __private __read_only uint size) 
{
  int2 pos = {get_global_id(0), get_global_id(1)};
  __local float sum;
  sum = 0.0;
  
  __local float4 P[BLOCK_SIZE][BLOCK_SIZE]; //Identification of this workgroup
	int i = get_group_id(0);
	int j = get_group_id(1); //Identification of work-item
	int idX = get_local_id(0);
	int idY = get_local_id(1); 
	int ii = i*BLOCK_SIZE + idX; // == get_global_id(0);
	int jj = j*BLOCK_SIZE + idY; // == get_global_id(1);
	int w = SIZE * 2 + 1;
  //Reads pixels
P[idX][idY] = read_imagef(input, sampler, pos);
//Needs to read extra elements for the filter in the borders
if (idX < w) 
{    pos.x = ii + BLOCK_SIZE; pos.y = jj;  
    P[idX + BLOCK_SIZE][idY] = read_imagef(input, sampler, pos);  
}

if (idY < w)
{    pos.x = ii; pos.y = jj + BLOCK_SIZE;
    P[idX][idY + BLOCK_SIZE] = 
read_imagef(input, sampler, pos); 
}
barrier(CLK_LOCAL_MEM_FENCE);
  //int sizeq = size;
  int gi = 0;
  int j_gaussian;
  for (int i_gaussian = -SIZE; i_gaussian <= SIZE; ++i_gaussian)
  {
	for (j_gaussian = -SIZE; j_gaussian <= SIZE; ++j_gaussian)
	{
	 	sum += (read_imagef(input, sampler, pos + (int2)(i_gaussian, j_gaussian)).x * gaussian[gi++]);
	}
  }
  barrier(CLK_LOCAL_MEM_FENCE);
  pos = (int2)(ii+SIZE, jj+SIZE);
write_imagef(output, pos, P[idX+SIZE][idY+SIZE]);
  
  //write_imagef(output, pos, sum);  
}

__kernel void  convolution_image(__read_only image2d_t input, __write_only image2d_t output, __read_only image2d_t gaussian, __private __read_only uint size) 
{
  int width_output = get_global_size(0); 
  int width = get_global_size(0); 

  int i = get_global_id(0); //column number
  int j = get_global_id(1); //row number
  float sum = 0.0;
//  write_imagef(output, (int2)(i,j), sum);
  
  int sizeq = size;
  for (int i_gaussian = -sizeq; i_gaussian <= sizeq; ++i_gaussian)
  {
	for (int j_gaussian = -sizeq; j_gaussian <= sizeq; ++j_gaussian)
	{
	 	sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)).x * read_imagef(gaussian, sampler, (int2)(i_gaussian + sizeq, j_gaussian + sizeq))).x;
	}
  }
  
  write_imagef(output, (int2)(i,j), sum);
    
}

__kernel void  laplacian(__read_only image2d_t input, __write_only image2d_t output, __read_only image2d_t gaussian, __global __read_only uint * size, __global __read_only float * sigma) 
{
  int width_output = get_global_size(0); 
  int width = get_global_size(0); 

  int i = get_global_id(0); //column number
  int j = get_global_id(1); //row number
  float sum = 0.0;
  
  int sizeq = size[0];
  for (int i_gaussian = -sizeq; i_gaussian <= sizeq; ++i_gaussian)
  {
	for (int j_gaussian = -sizeq; j_gaussian <= sizeq; ++j_gaussian)
	{
	 	sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)).x * read_imagef(gaussian, sampler, (int2)(i_gaussian + sizeq, j_gaussian + sizeq))).x;
	}
  }
  
  sum = fabs(sum * sigma[0]);
  
  write_imagef(output, (int2)(i,j), sum);
  
}
