const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;


__kernel void findLocalMax(__read_only image3d_t input, __write_only image2d_t output)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number
	int k = get_global_id(2); //depth number
	//if (k == get_global_size(2))
	//{
//		return;
//	}
	float4 sum = read_imagef(input, sampler, (int4)(i, j, k, 0));
	for (int ii = -1; ii < 2; ++ii)
	{
		for (int jj = -1; jj < 2; ++jj)
		{
			for (int kk = -1; kk < 2; ++kk)
			{
				if ((jj != 0 || kk != 0 || ii != 0) && read_imagef(input, sampler, (int4)(i + ii, j + jj, k + kk, 0)).x >= sum.x)
				{
					return;
				}
			}
		}
	}
	
	
	if (sum.x > 1e-5) //TODO: think about it (scale selection)
	{
		write_imageui(output, (int2)(i, j), k+1);
	}
}

__kernel void  edge_max(__read_only image3d_t Lvv_image, __write_only image2d_t output, __read_only image3d_t Lvvv_image)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number
	int k = get_global_id(2); //depth number

	float ul = read_imagef(Lvv_image, sampler, (int4)(i - 1, j - 1, k, 0)).x;
	float u = read_imagef(Lvv_image, sampler, (int4)(i, j - 1, k, 0)).x;
	float ur = read_imagef(Lvv_image, sampler, (int4)(i + 1, j - 1, k, 0)).x;
	float l = read_imagef(Lvv_image, sampler, (int4)(i - 1, j, k, 0)).x;
	float c = read_imagef(Lvv_image, sampler, (int4)(i, j, k, 0)).x;
	float r = read_imagef(Lvv_image, sampler, (int4)(i + 1, j, k, 0)).x;
	float dl = read_imagef(Lvv_image, sampler, (int4)(i - 1, j + 1, k, 0)).x;
	float d = read_imagef(Lvv_image, sampler, (int4)(i, j + 1, k, 0)).x;
	float dr = read_imagef(Lvv_image, sampler, (int4)(i + 1, j + 1, k, 0)).x;
	
	float Lvvv = read_imagef(Lvvv_image, sampler, (int4)(i - 1, j - 1, k, 0)).x;
	if (
		(c * r < 0 
		|| c * ur <0
		|| c * dr <0
		|| c * l <0
		|| c * dl <0
		|| c * ul <0
		|| c * u <0
		|| c * d <0)
		&& Lvvv < 0
		)
	{
		write_imageui(output, (int2)(i, j), 255);
	}
	
/*	if (Lvvv.x < 0.0 && Lvv.x <= 0.1)
	{
		write_imagef(output, (int2)(i, j), 1.0);
	}
	else
	{
		write_imagef(output, (int2)(i, j), 0.0);
	}//*/
	
	//write_imagef(output, (int2)(i, j), fabs(2.0 * Lx * Ly * Lxy));
	
}
