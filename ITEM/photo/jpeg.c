#include <fcntl.h>
#include "main.h"

        
u_char *decode_jpeg (const char *file_name, fb_info *jpeg_inf)
{
	register JSAMPARRAY lineBuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err_mgr;
	int bytesPerPix;
	FILE *inFile;
	u_char *retBuf;
    
    
	FILE * f;

    jpeg_file = open(file_name, O_RDONLY);
	if (NULL == jpeg_file)	{ 
		fprintf (stderr, "Error Open %s: %s\n",
			    filename, strerror(errno));
		return NULL;
	}

	cinfo.err = jpeg_std_error (&err_mgr);
	err_mgr.error_exit = jpeg_error_exit;	

	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, inFile);
	jpeg_read_header (&cinfo, 1);
	cinfo.do_fancy_upsampling = 0;
	cinfo.do_block_smoothing = 0;
	jpeg_start_decompress (&cinfo);

	/* 2010.2.6 and some... */
	jpeg_inf->w = cinfo.output_width;
	jpeg_inf->h = cinfo.output_height;

	short w,h;
	short *widthPtr = &w;
	short *heightPtr = &h;
	w = jpeg_inf->w;
	h = jpeg_inf->h;
	

	bytesPerPix = cinfo.output_components;

	lineBuf = cinfo.mem->alloc_sarray ((j_common_ptr) &cinfo, JPOOL_IMAGE, (*widthPtr * bytesPerPix), 1);
	retBuf = (u_char *) malloc (3 * (*widthPtr * *heightPtr));
		
	if (NULL == retBuf) {
		perror (NULL);
		return NULL;
	}
		

	if (3 == bytesPerPix) {
		int y;
			
		for (y = 0; y < cinfo.output_height; ++y)	{	
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
			memcpy ((retBuf + y * *widthPtr * 3),lineBuf[0],3 * *widthPtr);
		}
	}
	else if (1 == bytesPerPix) { 
		unsigned int col;
		int lineOffset = (*widthPtr * 3);
		int lineBufIndex;
		int x ;
		int y;
						
		for (y = 0; y < cinfo.output_height; ++y) {
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			lineBufIndex = 0;
			for (x = 0; x < lineOffset; ++x) {
				col = lineBuf[0][lineBufIndex];
			
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				
				++lineBufIndex;
			}			
		}
	}
	else {
		fprintf (stderr, "Error: the number of color channels is %d.  This program only handles 1 or 3\n", bytesPerPix);
		return NULL;
	}
	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);
	fclose (inFile);
			
	return retBuf;
}
u32_t * rgb24to32(u8_t *buf24, PFBDEV pFbdev)
{
    int w = fb_get_width(pFbdev);
    int h = fb_get_height(pFbdev);

    u32_t *buf32 = malloc(w * h * 4);
    if(NULL == buf) 
    {
        printf("rgb24to32 malloc error\n");
        return NULL;
    }
    
    int i;
    for(i = 0; i < w * h; ++i)
    {
        *((u8_t *)&buf32[i] + 2) = buf24[i * 3 + 0];
        *((u8_t *)&buf32[i] + 1) = buf24[i * 3 + 1];
        *((u8_t *)&buf32[i] + 0) = buf24[i * 3 + 2];
        *((u8_t *)&buf32[i] + 3) = 0x30;
    }
    return (u32_t *)buf;
}

u16_t * rgb24to16(u8_t *buf24, PFBDEV pFbdev)
{
	u16_t *buf16 = NULL;
	u32_t r16,g16,b16;

    buf16 = malloc (fb_get_width(pFbdev)*fb_get_height(pFbdev)*2);
	if (buf16 == NULL)
    {
        printf("rgb24to16 malloc error\n");
		return NULL;
    }

	int i;
	for (i = 0 ;i < jpeg_inf.w * jpeg_inf.h ; i++)	
    {
		b16 = (buf24[i * 3 + 2] * 0x1f) / 0xff;
		g16 = (buf24[i * 3 + 1] * 0x3f) / 0xff;
		r16 = (buf24[i * 3 + 0] * 0x1f) / 0xff;
	
		buf16[i] = b16 | (g16 <<5) | (r16 <<11);
	}
	return buf16;
}

u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf)
{
	int i,j;
	int dtw,dth;
	
	u8_t *buf = malloc(new_inf.w * new_inf.h * 3);

	if (buf == NULL) return NULL;
	
	for(j = 0; j < new_inf.h; j++){
		for(i = 0; i < new_inf.w; i++){

			dtw = i * jpeg_inf.w / new_inf.w;
			dth = j * jpeg_inf.h / new_inf.h;

			buf[0+i*3 + j*new_inf.w*3] = 
				buf24[0+(dtw+dth*jpeg_inf.w)*3];

			buf[1+i*3 + j*new_inf.w*3] = 
				buf24[1+(dtw+dth*jpeg_inf.w)*3];
			
			buf[2+i*3 + j*new_inf.w*3] =
				buf24[2+(dtw+dth*jpeg_inf.w)*3];
		}
	}

	return buf;
}
