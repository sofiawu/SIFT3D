/* imutil.h
 * ----------------------------------------------------------------
 * Rice MRI Team
 * ----------------------------------------------------------------
 * Internal header for imutil.c
 *-----------------------------------------------------------------
 * Created: Blaine Rister 12/26/2013
 * Last updated: Blaine Rister 11/16/2013
 */

#include <sys/types.h>
#include "types.h"

#ifndef UTIL_H
#define UTIL_H

/* Use OpenCL acceleration? */
//#define USE_OPENCL

/* Vendor-specific info */
#define PLATFORM_NAME_NVIDIA "NVIDIA CUDA"

/* Basic constants */
#define UTIL_PI 3.14159265358979323846
#define UTIL_PI_F 3.141592653589793f
#define SQRT2 1.4142135623730950488
#define SQRT2_F 1.4142135623730950488f

/* Externally-visible routines */
void clFinish_all();

void check_cl_error(int err, const char *msg);

int init_cl(CL_data *user_cl_data, const char *platform_name, 
			cl_device_type device_type,	cl_mem_flags mem_flags, 
			cl_image_format image_format);

double robust_error(double err, double cutoff);

int im_get_bins(Image *im, int x, int y, int z, Svec *bins);

int Svec_compar(Svec *s1, Svec *s2);

int convert_Mat_rm(Mat_rm *in, Mat_rm *out, data_type type);

int init_Mat_rm(Mat_rm *mat, int num_rows, int num_cols,
				data_type type, int set_zero);

int init_Mat_rm_p(Mat_rm *mat, const void *p, int num_rows, 
				  int num_cols,	data_type type, int set_zero);

int set_Mat_rm_zero(Mat_rm *mat);

int copy_Mat_rm(const Mat_rm *const src, Mat_rm *const dst);

int print_Mat_rm(Mat_rm *mat);

int resize_Mat_rm(Mat_rm *mat); 

int eigen_Mat_rm(Mat_rm *A, Mat_rm *Q, Mat_rm *L);

int solve_Mat_rm(Mat_rm *A, Mat_rm *B, double limit, Mat_rm *X);

int solve_Mat_rm_ls(Mat_rm *A, Mat_rm *B, Mat_rm *X);

int transpose_Mat_rm(Mat_rm *src, Mat_rm *dst);

int det_symm_Mat_rm(Mat_rm *mat, void *det);

int zero_Mat_rm(Mat_rm *mat);
 
void cleanup_Mat_rm(Mat_rm *mat);

int init_tform(void *tform, const tform_type type);

int init_Affine(Affine *affine, int dim);

int copy_tform(void *src, void *dst, const tform_type type);

int copy_Affine(Affine *src, Affine *dst);

int Affine_set_mat(Mat_rm *mat, Affine *affine);

int apply_tform_xyz(double x_in, double y_in, double z_in, 
					double *x_out, double *y_out, double *z_out,
					const tform_type type, void *tform);

void apply_Affine_xyz(Affine *affine, double x_in, double y_in, 
					  double z_in, double *x_out, double *y_out, 
					  double *z_out);
					  
void apply_Tps_xyz(Tps *tps, double x_in, double y_in, 
					  double z_in, double *x_out, double *y_out, 
					  double *z_out);

int apply_tform_Mat_rm(Mat_rm *mat_in, Mat_rm *mat_out, const tform_type type,
					   void *tform);
					   
int apply_Affine_Mat_rm(Affine *affine, Mat_rm *mat_in, Mat_rm *mat_out);

int apply_Tps_Mat_rm(Tps *tps, Mat_rm *mat_in, Mat_rm *mat_out);

size_t tform_get_size(tform_type type);

int cleanup_tform(void *tform, tform_type type);

void cleanup_Affine(Affine *affine);

void cleanup_Tps(Tps *tps);

int mul_Mat_rm(Mat_rm *mat_in1, Mat_rm *mat_in2, Mat_rm *mat_out);

int apply_Sep_FIR_filter(Image *src, Image *dst,
	Sep_FIR_filter *f, int dim);

int draw_grid(Image *grid, int nx, int ny, int nz, int spacing, 
					   int line_width);

int draw_points(const Mat_rm *const in, int nx, int ny, int nz, int radius, Image *out);

int draw_lines(const Mat_rm *const points1, const Mat_rm *const points2, 
	       const int nx, const int ny, const int nz, Image *const out);

int read_nii(const char *path, Image *im);

int write_nii(const char *path, Image *im);

int write_Keypoint_store(const char *path, Keypoint_store *kp);

int write_Mat_rm(const char *path, Mat_rm *mat);

int init_im_first_time(Image *im, const int nx, const int ny, const int nz);

int im_load_cl(Image *im, int blocking);

int im_copy_dims(Image *src, Image *dst);

int im_copy_data(Image *src, Image *dst);

void im_free(Image *im);

int im_downsample_2x(Image *src, Image *dst);

int im_downsample_2x_cl(Image *src, Image *dst);

int im_read_back(Image *im, int blocking);

int im_set_kernel_arg(cl_kernel kernel, int n, Image *im);

int im_transpose(const Image *const src, const int dim1, const int dim2, 
		 Image *const dst);

int im_upsample_2x(Image *src, Image *dst);

int im_pad(Image *im, Image *pad);

int im_resize(Image *im);

int im_concat(const Image *const src1, const Image *const src2, const int dim, 
	      Image *const dst);

void im_scale(Image *im);

int im_subtract(Image *src1, Image *src2, Image *dst);

void im_zero(Image *im);

void im_Hessian(Image *im, int x, int y, int z, Mat_rm *H);

int im_inv_transform(Image *in, Image *out, tform_type type, 
					 void *tform);

int convolve_sep(const Image *const src,
	Image *const dst, const Sep_FIR_filter *const f, int dim);

int convolve_sep_cl (const Image *const src, Image *const dst, 
		     const Sep_FIR_filter *const f, const int dim);

int convolve_sep_sym(const Image *const src, Image *const dst, 
		     const Sep_FIR_filter *const f, const int dim);

void init_im(Image *im);

int init_gauss_filter(Gauss_filter *gauss, double sigma, int dim);

int init_gss(GSS_filters *gss, Pyramid *pyr);

int init_pyramid(Pyramid *pyr, Image *im);

void init_Slab(Slab *slab);

int resize_Slab(Slab *slab, int num, size_t size);

int write_pyramid(const char *path, Pyramid *pyr);

void err_exit(const char *str);

int mkpath(const char *path, mode_t mode);

#endif