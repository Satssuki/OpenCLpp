const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_MIRRORED_REPEAT | CLK_FILTER_NEAREST;

__kernel void  edge_detector(__read_only image2d_t input, __write_only image2d_t out_Lvv, __write_only image2d_t out_Lvvv)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float ul = read_imagef(input, sampler, (int2)(i - 1, j - 1)).x;
	float u = read_imagef(input, sampler, (int2)(i, j - 1)).x;
	float ur = read_imagef(input, sampler, (int2)(i + 1, j - 1)).x;
	float l = read_imagef(input, sampler, (int2)(i - 1, j)).x;
	float c = read_imagef(input, sampler, (int2)(i, j)).x;
	float r = read_imagef(input, sampler, (int2)(i + 1, j)).x;
	float dl = read_imagef(input, sampler, (int2)(i - 1, j + 1)).x;
	float d = read_imagef(input, sampler, (int2)(i, j + 1)).x;
	float dr = read_imagef(input, sampler, (int2)(i + 1, j + 1)).x;

	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;//*/
	float Lxy =  ul / 4.0 - ur / 4.0 +
				-dl / 4.0 + dr / 4.0;
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;
	float Lxxx =  0.5 * (ul + dl - ur - dr) + l - r;
	float Lxxy =  - ul / 8.0 + u / 4.0 - ur / 8.0
					+ dl / 8.0 - d / 4.0 + dr / 8.0;
	float Lxyy =  ul / 8.0 - ur / 8.0
					- l / 4.0 + r / 4.0
					+ dl / 8.0 - dr / 8.0;
	float Lyyy =  0.5 * (ul + ur - dr - dl) + u - d;
	
	float Lvv = Lx * Lx * Lxx + 2.0 * Lx * Ly * Lxy + Ly * Ly * Lyy;
	if (fabs(Lvv) < 1e-5)
	{
		Lvv = 0;
	}
	float Lvvv = (Lx * Lx * Lx * Lxxx + 3.0 * Lx * Lx * Ly * Lxxy + 3.0 * Lx * Ly * Ly * Lxyy + Ly * Ly * Ly * Lyyy);
	write_imagef(out_Lvv, (int2)(i, j), Lvv);
	write_imagef(out_Lvvv, (int2)(i, j), Lvvv);
}

__kernel void  corner_detector(__read_only image2d_t input, __write_only image2d_t output)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float ul = read_imagef(input, sampler, (int2)(i - 1, j - 1)).x;
	float u = read_imagef(input, sampler, (int2)(i, j - 1)).x;
	float ur = read_imagef(input, sampler, (int2)(i + 1, j - 1)).x;
	float l = read_imagef(input, sampler, (int2)(i - 1, j)).x;
	float c = read_imagef(input, sampler, (int2)(i, j)).x;
	float r = read_imagef(input, sampler, (int2)(i + 1, j)).x;
	float dl = read_imagef(input, sampler, (int2)(i - 1, j + 1)).x;
	float d = read_imagef(input, sampler, (int2)(i, j + 1)).x;
	float dr = read_imagef(input, sampler, (int2)(i + 1, j + 1)).x;

	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;
	float Lxy =  ul / 4.0 - ur / 4.0 +
				-dl / 4.0 + dr / 4.0;
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;
				
	float k = fabs(Lx * Lx * Lyy + Ly * Ly * Lxx - 2.0 * Lx * Ly * Lxy);
	write_imagef(output, (int2)(i,j), k);
}

__kernel void  blob_detector(__read_only image2d_t input, __write_only image2d_t output)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float ul = read_imagef(input, sampler, (int2)(i - 1, j - 1)).x;
	float u = read_imagef(input, sampler, (int2)(i, j - 1)).x;
	float ur = read_imagef(input, sampler, (int2)(i + 1, j - 1)).x;
	float l = read_imagef(input, sampler, (int2)(i - 1, j)).x;
	float c = read_imagef(input, sampler, (int2)(i, j)).x;
	float r = read_imagef(input, sampler, (int2)(i + 1, j)).x;
	float dl = read_imagef(input, sampler, (int2)(i - 1, j + 1)).x;
	float d = read_imagef(input, sampler, (int2)(i, j + 1)).x;
	float dr = read_imagef(input, sampler, (int2)(i + 1, j + 1)).x;

	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;//*/
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;
	
	write_imagef(output, (int2)(i, j), fabs(Lxx + Lyy));
	
}

__kernel void  ridge_detector(__read_only image2d_t input, __write_only image2d_t out_L1, __write_only image2d_t out_L2)
{
	int i = get_global_id(0); //column number
	int j = get_global_id(1); //row number

	float ul = read_imagef(input, sampler, (int2)(i - 1, j - 1)).x;
	float u = read_imagef(input, sampler, (int2)(i, j - 1)).x;
	float ur = read_imagef(input, sampler, (int2)(i + 1, j - 1)).x;
	float l = read_imagef(input, sampler, (int2)(i - 1, j)).x;
	float c = read_imagef(input, sampler, (int2)(i, j)).x;
	float r = read_imagef(input, sampler, (int2)(i + 1, j)).x;
	float dl = read_imagef(input, sampler, (int2)(i - 1, j + 1)).x;
	float d = read_imagef(input, sampler, (int2)(i, j + 1)).x;
	float dr = read_imagef(input, sampler, (int2)(i + 1, j + 1)).x;

	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;
	float Lxy =  ul / 4.0 - ur / 4.0 +
				-dl / 4.0 + dr / 4.0;//*/			
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;
	
	float L1 = Lx * Ly * (Lxx - Lyy) - (Lx * Lx - Ly * Ly) * Lxy;
	if (fabs(L1) < 1e-5)
	{
		L1 = 0;
	}
	float L2 = (Ly * Ly - Lx * Lx) * (Lxx - Lyy) - 4 * Lx * Ly * Lxy;
	if (fabs(L2) < 1e-5)
	{
		L2 = 0;
	}
	
	write_imagef(out_L1, (int2)(i, j), L1);
	write_imagef(out_L2, (int2)(i, j), L2);
}