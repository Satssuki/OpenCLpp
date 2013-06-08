const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_MIRRORED_REPEAT | CLK_FILTER_NEAREST;


__kernel void findLocalMax(__read_only image3d_t input, __write_only image2d_t output)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number
	int k = get_global_id(2); //depth number
	if (k == get_global_size(2))
	{
		return;
	}
	float4 sum = read_imagef(input, sampler, (int4)(i, j, k, 0));
	for (int ii = -1; ii < 2; ++ii)
	{
		for (int jj = -1; jj < 2; ++jj)
		{
			for (int kk = -1; kk < 2; ++kk)
			{
				if (read_imagef(input, sampler, (int4)(i + ii, j + jj, k + kk, 0)).x > sum.x)
				{
					return;
				}
			}
		}
	}
	
	
	if (sum.x > 1)
	{
		write_imageui(output, (int2)(i, j), k);
	}
}