#include "matrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#include <x86intrin.h>
#endif

/* Below are some intel intrinsics that might be useful
 * void _mm256_storeu_pd (double * mem_addr, __m256d a)
 * __m256d _mm256_set1_pd (double a)
 * __m256d _mm256_set_pd (double e3, double e2, double e1, double e0)
 * __m256d _mm256_loadu_pd (double const * mem_addr)
 * __m256d _mm256_add_pd (__m256d a, __m256d b)
 * __m256d _mm256_sub_pd (__m256d a, __m256d b)
 * __m256d _mm256_fmadd_pd (__m256d a, __m256d b, __m256d c)
 * __m256d _mm256_mul_pd (__m256d a, __m256d b)
 * __m256d _mm256_cmp_pd (__m256d a, __m256d b, const int imm8)
 * __m256d _mm256_and_pd (__m256d a, __m256d b)
 * __m256d _mm256_max_pd (__m256d a, __m256d b)
 */

 /*
  * Generates a random double between `low` and `high`.
  */
double rand_double(double low, double high) {
    double range = (high - low);
    double div = RAND_MAX / range;
    return low + (rand() / div);
}

/*
 * Generates a random matrix with `seed`.
 */
void rand_matrix(matrix* result, unsigned int seed, double low, double high) {
    srand(seed);
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            set(result, i, j, rand_double(low, high));
        }
    }
}

/*
 * Allocate space for a matrix struct pointed to by the double pointer mat with
 * `rows` rows and `cols` columns. You should also allocate memory for the data array
 * and initialize all entries to be zeros. Remember to set all fieds of the matrix struct.
 * `parent` should be set to NULL to indicate that this matrix is not a slice.
 * You should return -1 if either `rows` or `cols` or both have invalid values, or if any
 * call to allocate memory in this function fails. If you don't set python error messages here upon
 * failure, then remember to set it in numc.c.
 * Return 0 upon success and non-zero upon failure.
 */
int allocate_matrix(matrix** mat, int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    return allocate_matrix_ref(mat, NULL, 0, 0, rows, cols);
}

/*
 * Allocate space for a matrix struct pointed to by `mat` with `rows` rows and `cols` columns.
 * This is equivalent to setting the new matrix to be
 * from[row_offset:row_offset + rows, col_offset:col_offset + cols]
 * If you don't set python error messages here upon failure, then remember to set it in numc.c.
 * Return 0 upon success and non-zero upon failure.
 */
int allocate_matrix_ref(matrix** mat, matrix* from, int row_offset, int col_offset,
    int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    if (rows <= 0 || cols <= 0) {
        PyErr_SetString(PyExc_IndexError, "Rows and cols should be positive numbers");
        PyErr_Print();
        return -1;
    }

    if (from != NULL && ((rows + row_offset) > from->rows || (cols + col_offset) > from->cols)) {
        PyErr_SetString(PyExc_IndexError, "Index out of bounds");
        PyErr_Print();
        return -1;
    }

    *mat = (matrix*)malloc(sizeof(matrix));
    double** data = (double**)malloc(sizeof(double*) * rows);

    if (from == NULL) {
        for (int r = 0; r < rows; r++) {
            double* rData = (double*)malloc(sizeof(double) * cols);
            if (rData == NULL) {
                PyErr_SetString(PyExc_RuntimeError, "Fail to allocate the data of the matrix");
                PyErr_Print();
                return -1;
            }
            for (int c = 0; c < cols; c++) {
                rData[c] = 0.0;
            }
            data[r] = rData;
        }
    } else {
        for (int r = 0; r < rows; r++) {
            double* rData = from->data[r + row_offset] + col_offset;
            data[r] = rData;
        }
    }

    if (from != NULL) {
        from->ref_cnt += 1;
    }

    (*mat)->rows = rows;
    (*mat)->cols = cols;
    (*mat)->data = data;
    (*mat)->ref_cnt = 1;
    (*mat)->is_1d = (rows == 1 || cols == 1) ? 1 : 0;
    (*mat)->parent = from;

    return 0;
}

/*
 * This function will be called automatically by Python when a numc matrix loses all of its
 * reference pointers.
 * You need to make sure that you only free `mat->data` if no other existing matrices are also
 * referring this data array.
 * See the spec for more information.
 */
void deallocate_matrix(matrix* mat) {
    /* TODO: YOUR CODE HERE */
    if (mat == NULL || mat->ref_cnt > 1) {
        return;
    }
    if (mat->parent != NULL) {
        free(mat->data);
        mat->parent->ref_cnt -= 1;
        free(mat);
    } else {
        for (int r = 0; r < mat->rows; r++) {
            free(mat->data[r]);
        }
        free(mat->data);
        free(mat);
    }
}

/*
 * Return the double value of the matrix at the given row and column.
 * You may assume `row` and `col` are valid.
 */
double get(matrix* mat, int row, int col) {
    /* TODO: YOUR CODE HERE */
    return mat->data[row][col];
}

/*
 * Set the value at the given row and column to val. You may assume `row` and
 * `col` are valid
 */
void set(matrix* mat, int row, int col, double val) {
    /* TODO: YOUR CODE HERE */
    mat->data[row][col] = val;
}

/*
 * Set all entries in mat to val
 */
void fill_matrix(matrix* mat, double val) {
    /* TODO: YOUR CODE HERE */
    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            mat->data[r][c] = val;
        }
    }
}

/*
 * Store the result of adding mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int add_matrix(matrix* result, matrix* mat1, matrix* mat2) {
    /* TODO: YOUR CODE HERE */
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        PyErr_SetString(PyExc_ValueError, "Different dimension of two given matrices");
        PyErr_Print();
        return -1;
    }
    // allocate_matrix(&result, mat1->rows, mat1->cols);
    __m256d tmp_A = _mm256_setzero_pd();
    __m256d tmp_B = _mm256_setzero_pd();
    __m256d current = _mm256_setzero_pd();

#pragma omp parallel for
    for (int r = 0; r < mat1->rows; r++) {
        for (int c = 0; c < mat1->cols / 4; c++) {
            // double tmp1 = get(mat1, r, c);
            // double tmp2 = get(mat2, r, c);
            // set(result, r, c, tmp1 + tmp2);
            tmp_A = _mm256_loadu_pd(mat1->data[r] + c * 4);
            tmp_B = _mm256_loadu_pd(mat2->data[r] + c * 4);
            current = _mm256_add_pd(tmp_A, tmp_B);
            _mm256_storeu_pd(result->data[r] + c * 4, current);
        }
        for (int c = mat1->cols / 4 * 4; c < mat1->cols; c++) {
            set(result, r, c, get(mat1, r, c) + get(mat2, r, c));
        }
    }
    return 0;
}

/*
 * Store the result of subtracting mat2 from mat1 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int sub_matrix(matrix* result, matrix* mat1, matrix* mat2) {
    /* TODO: YOUR CODE HERE */

    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        PyErr_SetString(PyExc_ValueError, "Different dimension of two given matrices");
        PyErr_Print();
        return -1;
    }
    // allocate_matrix(&result, mat1->rows, mat1->cols);
    __m256d tmp_A = _mm256_setzero_pd();
    __m256d tmp_B = _mm256_setzero_pd();
    __m256d current = _mm256_setzero_pd();

#pragma omp parallel for
    for (int r = 0; r < mat1->rows; r++) {
        for (int c = 0; c < mat1->cols / 4; c++) {
            // double tmp1 = get(mat1, r, c);
            // double tmp2 = get(mat2, r, c);
            // set(result, r, c, tmp1 + tmp2);
            tmp_A = _mm256_loadu_pd(mat1->data[r] + c * 4);
            tmp_B = _mm256_loadu_pd(mat2->data[r] + c * 4);
            current = _mm256_sub_pd(tmp_A, tmp_B);
            _mm256_storeu_pd(result->data[r] + c * 4, current);
        }
        for (int c = mat1->cols / 4 * 4; c < mat1->cols; c++) {
            set(result, r, c, get(mat1, r, c) - get(mat2, r, c));
        }
    }
    return 0;

    /* Original Implementation of sub_matrix. Neat but inefficient
    * matrix* tmp;
    * allocate_matrix(&tmp, mat2->rows, mat2->cols);
    * neg_matrix(tmp, mat2);
    * int add_success = add_matrix(result, mat1, tmp);
    * free(tmp);
    * return add_success;
    */
}

/*
 * Store the result of multiplying mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that matrix multiplication is not the same as multiplying individual elements.
 */
int mul_matrix(matrix* result, matrix* mat1, matrix* mat2) {
    /* TODO: YOUR CODE HERE */

    /* By Me: */
    /* As matrix is row oriented, the formula is:
     * result[i * n + j] += mat1[i * n + k] * mat1[k * n + j]
     * And!
     * result[i * n + j] += mat1[i * n + k] * transpose[j * n + k]
     * To use the cache locality better, the innermost loop should be iterating over k when using tranposed mat2!
     */
    if (mat1->cols != mat2->rows) {
        PyErr_SetString(PyExc_ValueError, "Improper dimensions of two matrices to do multiplication");
        PyErr_Print();
        return -1;
    }
    // Wrong!:
    // allocate_matrix(&result, mat1->rows, mat2->cols);

    fill_matrix(result, 0.0);
    /* Transpose the second matrix */
    matrix* transpose = NULL;
    allocate_matrix(&transpose, mat2->cols, mat2->rows);
    transpose_matrix(transpose, mat2);

    __m256d current_result, mat1_elm, mat2_elm;
    double* tmp_array = (double*)malloc(sizeof(double) * 4);

#pragma omp parallel for
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {

            current_result = _mm256_setzero_pd();
            double tmp = 0.0;

            for (int k = 0; k < mat1->cols / 4; k++) {
                // result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
                mat1_elm = _mm256_loadu_pd(mat1->data[i] + k * 4);
                mat2_elm = _mm256_loadu_pd(transpose->data[j] + k * 4);
                current_result = _mm256_fmadd_pd(mat1_elm, mat2_elm, current_result);
            }
            _mm256_storeu_pd(tmp_array, current_result);
            for (int p = 0; p < 4; p++) {
                tmp += tmp_array[p];
            }
            for (int k = mat1->cols / 4 * 4; k < mat1->cols; k++) {
                tmp += mat1->data[i][k] * transpose->data[j][k];
            }
#pragma omp critical
            {
                result->data[i][j] += tmp;
            }
        }
    }

    deallocate_matrix(transpose);
    free(tmp_array);
    return 0;
}

/*
 * Store the result of raising mat to the (pow)th power to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that pow is defined with matrix multiplication, not element-wise multiplication.
 */
int pow_matrix(matrix* result, matrix* mat, int pow) {
    /* TODO: YOUR CODE HERE */
    if (mat->rows != mat->cols) {
        PyErr_SetString(PyExc_ValueError, "Given Matrix is not a square matrix");
        PyErr_Print();
        return -1;
    }
    int mat_size = mat->rows;
    matrix* tmp;
    allocate_matrix(&tmp, mat_size, mat_size);

    copy_data(tmp, mat);

    while (pow > 1) {
        pow--;
        mul_matrix(result, tmp, mat);
        copy_data(tmp, result);
    }
    return 0;
}

/*
 * Store the result of element-wise negating mat's entries to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int neg_matrix(matrix* result, matrix* mat) {
    /* TODO: YOUR CODE HERE */
    // allocate_matrix(&result, mat ->rows, mat ->cols);
    __m256d tmp = _mm256_setzero_pd();

    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols / 4; c++) {
            tmp = _mm256_loadu_pd(mat->data[r] + c * 4);
            _mm256_storeu_pd(result->data[r] + c * 4, tmp);
        }
        for (int c = mat->cols / 4 * 4; c < mat->cols; c++) {
            result->data[r][c] = -mat->data[r][c];
        }
    }
    return 0;
}

/*
 * Store the result of taking the absolute value element-wise to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int abs_matrix(matrix* result, matrix* mat) {
    /* TODO: YOUR CODE HERE */
    // allocate_matrix(&result, mat ->rows, mat ->cols);
    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            int tmp = mat->data[r][c];
            result->data[r][c] = tmp >= 0 ? tmp : -tmp;
        }
    }
    return 0;
}

void copy_data(matrix* dest, matrix* src) {
#pragma omp parallel for
    for (int r = 0; r < src->rows; r++) {
        for (int c = 0; c < src->cols; c++) {
            dest->data[r][c] = src->data[r][c];
        }
    }
}

int transpose_matrix(matrix* result, matrix* mat) {

    /* This piece of code comes from lab07 */
    if (result->rows != mat->cols || result->cols != mat->rows) {
        PyErr_SetString(PyExc_RuntimeError, "Can't transpose!");
        PyErr_Print();
        return -1;
    }
    int row = 0, col = 0, blocksize = 50;
#pragma omp parallel for
    for (row = 0; row < mat->rows; row += blocksize) {
        for (col = 0; col < mat->cols; col += blocksize) {
            for (int x = row; x < row + blocksize && x < mat->rows; x++) {
                for (int y = col; y < col + blocksize && y < mat->cols; y++) {
                    /* dst[x + y * n] = src[x * n + y]; */
                    result->data[y][x] = mat->data[x][y];
                }
            }
        }
    }
    return 0;
}

