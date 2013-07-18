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

const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_MIRRORED_REPEAT | CLK_FILTER_NEAREST;


__kernel void  convolution(__read_only image2d_t input, __write_only image2d_t output, __global float * gaussian, __private __read_only uint size) 
{
  int width_output = get_global_size(0); 
  int width = get_global_size(0); 

  int i = get_global_id(0); //column number
  int j = get_global_id(1); //row number
  float4 sum = (0.0,0.0,0.0,0.0);
//  write_imagef(output, (int2)(i,j), sum);
  
  int sizeq = size;
  int gi = 0;
  for (int i_gaussian = -sizeq; i_gaussian <= sizeq; ++i_gaussian)
  {
	for (int j_gaussian = -sizeq; j_gaussian <= sizeq; ++j_gaussian)
	{
	 	sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)) * gaussian[gi++]);
	}
  }
  
  write_imagef(output, (int2)(i,j), sum);
    
}

__kernel void  convolution_image(__read_only image2d_t input, __write_only image2d_t output, __read_only image2d_t gaussian, __private __read_only uint size) 
{
  int width_output = get_global_size(0); 
  int width = get_global_size(0); 

  int i = get_global_id(0); //column number
  int j = get_global_id(1); //row number
  float4 sum = (0.0,0.0,0.0,0.0);
//  write_imagef(output, (int2)(i,j), sum);
  
  int sizeq = size;
  for (int i_gaussian = -sizeq; i_gaussian <= sizeq; ++i_gaussian)
  {
	for (int j_gaussian = -sizeq; j_gaussian <= sizeq; ++j_gaussian)
	{
	 	sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)) * read_imagef(gaussian, sampler, (int2)(i_gaussian + sizeq, j_gaussian + sizeq)));
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
	 	sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)) * read_imagef(gaussian, sampler, (int2)(i_gaussian + sizeq, j_gaussian + sizeq))).x;
	}
  }
  
  sum = fabs(sum * sigma[0]);
  
  write_imagef(output, (int2)(i,j), sum);
  
}
