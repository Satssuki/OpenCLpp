const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_MIRRORED_REPEAT | CLK_FILTER_NEAREST;

__kernel void  edge_detector(__read_only image2d_t input, __write_only image2d_t output)
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
///*
	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;//*/
	float Lxy =  ul / 6.0 + 2.0 * u / 3.0 + ur / 6.0 +
                2.0 * l / 3.0 - 10.0 * c / 3.0 + 2.0 * r / 3.0 +
				dl / 6.0 + 2.0 * d / 3.0 + dr / 6.0;//*/
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;//*/
	//	*/		
		///*
	//float Lx =  0.5 * (l - r);
	//float Ly =  0.5 * (u - d);
	//float Lxx =  l - 2.0 * c + r;
	//float Lyy =  d + u - 2.0 * c;
/*	float Lxy = - ul / 4.0 + ur / 4.0 +
				dl / 4.0 - dr / 4.0;//*/
				/*
	float Lx =  0.25 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.25 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  l -  c + r;
	float Lxy =  d + u - c;
		*/
	float Lxxx =  0.5 * (r - l);
	float Lxxy =  - ul / 8.0 + u / 4.0 - ur / 8.0
					+ dl / 8.0 - d / 4.0 + dr / 8.0;
	float Lxyy =  ul / 8.0 - ur / 8.0
					- l / 4.0 + r / 4.0
					+ dl / 8.0 - dr / 8.0;
	float Lyyy =  0.5 * (d - u);
	
	float4 Lvv = (0.0, 0.0, 0.0, 0.0);
	Lvv.x = fabs(Lx * Lx * Lxx + 2.0 * Lx * Ly * Lxy + Ly * Ly * Lyy);
	float4 Lvvv = (0.0, 0.0, 0.0, 0.0);
	Lvvv.x = (Lx * Lx * Lx * Lxxx + 3.0 * Lx * Lx * Ly * Lxxy + 3.0 * Lx * Ly * Ly * Lxyy + Ly * Ly * Ly * Lyyy);
	//write_imagef(output, (int2)(i, j), Lvv);

	if (Lvv.x <= 0.0001)
	{
		write_imagef(output, (int2)(i, j), 1.0);
	}
	else
	{
		write_imagef(output, (int2)(i, j), 0.0);
	}//*/
	
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
///*
	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;//*/
	float Lxy =  ul / 6.0 + 2.0 * u / 3.0 + ur / 6.0 +
                2.0 * l / 3.0 + 10.0 * c / 3.0 + 2.0 * r / 3.0 +
				dl / 6.0 + 2.0 * d / 3.0 + dr / 6.0;//*/
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;//*/
	//	*/		
		///*
	//float Lx =  0.5 * (l - r);
	//float Ly =  0.5 * (u - d);
	//float Lxx =  l - 2.0 * c + r;
	//float Lyy =  d + u - 2.0 * c;
/*	float Lxy = - ul / 4.0 + ur / 4.0 +
				dl / 4.0 - dr / 4.0;//*/
				/*
	float Lx =  0.25 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.25 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  l -  c + r;
	float Lxy =  d + u - c;
		*/
	float Lxxx =  0.5 * (r - l);
	float Lxxy =  - ul / 8.0 + u / 4.0 - ur / 8.0
					+ dl / 8.0 - d / 4.0 + dr / 8.0;
	float Lxyy =  ul / 8.0 - ur / 8.0
					- l / 4.0 + r / 4.0
					+ dl / 8.0 - dr / 8.0;
	float Lyyy =  0.5 * (d - u);
	
	float4 k = (0.0, 0.0, 0.0, 0.0);
	k.x = Lx * Lx * Lyy + Ly * Ly * Lxx - 2.0 * Lx * Ly * Lxy;
	
	if (k.x > 0.1)
	{
		write_imagef(output, (int2)(i, j), 1.0);
	}
	else
	{
		write_imagef(output, (int2)(i, j), 0.0);
	}
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
///*
	float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +
                5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +
				dl / 12.0 - d / 6.0 + dr / 12.0;//*/
	float Lxy =  ul / 6.0 + 2.0 * u / 3.0 + ur / 6.0 +
                2.0 * l / 3.0 + 10.0 * c / 3.0 + 2.0 * r / 3.0 +
				dl / 6.0 + 2.0 * d / 3.0 + dr / 6.0;//*/
	float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -
                l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +
				dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;//*/
	//	*/		
		///*
	//float Lx =  0.5 * (l - r);
	//float Ly =  0.5 * (u - d);
	//float Lxx =  l - 2.0 * c + r;
	//float Lyy =  d + u - 2.0 * c;
/*	float Lxy = - ul / 4.0 + ur / 4.0 +
				dl / 4.0 - dr / 4.0;//*/
				/*
	float Lx =  0.25 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);
	float Ly =  0.25 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);
	float Lxx =  l -  c + r;
	float Lxy =  d + u - c;
		*/
	float Lxxx =  0.5 * (r - l);
	float Lxxy =  - ul / 8.0 + u / 4.0 - ur / 8.0
					+ dl / 8.0 - d / 4.0 + dr / 8.0;
	float Lxyy =  ul / 8.0 - ur / 8.0
					- l / 4.0 + r / 4.0
					+ dl / 8.0 - dr / 8.0;
	float Lyyy =  0.5 * (d - u);
	
	float4 d2L = (0.0, 0.0, 0.0, 0.0);
	d2L.x = fabs(Lx) + fabs(Ly);
	float d22L = Lxx + Lyy;
	
	if (d2L.x <= 0.1 && d22L > 0.1)
	{
		write_imagef(output, (int2)(i, j), 1.0);
	}
	else
	{
		write_imagef(output, (int2)(i, j), 0.0);
	}
	//write_imagef(output, (int2)(i, j), fabs(Lxx) + fabs(Lyy));
	//write_imagef(output, (int2)(i, j), d22L);
}
