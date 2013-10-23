const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;

__kernel void findLocalMax(__read_only image2d_t input, __write_only image2d_t output)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float sum = read_imagef(input, sampler, (int2)(i, j)).x;
	for (int ii = -1; ii < 2; ++ii)
	{
		for (int jj = -1; jj < 2; ++jj)
		{
			if (read_imagef(input, sampler, (int2)(i + ii, j + jj)).x > sum)
			{
				return;
			}
		}
	}

	if (sum > 1e-5)
	{
		write_imageui(output, (int2)(i, j), 255);
	}
	else
	{
		write_imageui(output, (int2)(i, j), 0);
	}
}

__kernel void  edge_max(__read_only image2d_t Lvv_image, __write_only image2d_t output, __read_only image2d_t Lvvv_image)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float c = read_imagef(Lvv_image, sampler, (int2)(i, j)).x;
	float r = read_imagef(Lvv_image, sampler, (int2)(i + 1, j)).x;
	float d = read_imagef(Lvv_image, sampler, (int2)(i, j + 1)).x;
	float dr = read_imagef(Lvv_image, sampler, (int2)(i + 1, j + 1)).x;

	float Lvvv = read_imagef(Lvvv_image, sampler, (int2)(i, j)).x;
	if (
		(c * r < 0
		|| c * dr <0
		|| c * d <0)
		&& Lvvv < 0
		)
	{
		write_imageui(output, (int2)(i, j), 255);
	}
	else
	{
		write_imageui(output, (int2)(i, j), 0);
	}
}

__kernel void  ridge_max(__read_only image2d_t L1_image, __write_only image2d_t output, __read_only image2d_t L2_image)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float L1 = read_imagef(L1_image, sampler, (int2)(i, j)).x;
	float L2 = read_imagef(L2_image, sampler, (int2)(i, j)).x;
	if (L1 == 0 && L2 > 0)
	{
		write_imageui(output, (int2)(i, j), 255);
	}
	else
	{
		write_imageui(output, (int2)(i, j), 0);
	}
}
