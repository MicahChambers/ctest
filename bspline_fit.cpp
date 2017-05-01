#include <Eigen/Sparse>
#include <Eigen/SPQRSupport>
#include <Eigen/OrderingMethods>
#include <Eigen/SparseQR>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>

// declares a column-major sparse matrix type of double
typedef Eigen::SparseMatrix<float> SparseMatrix;
typedef Eigen::Triplet<float> Triplet;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrixXf;

const float MIN_X = 0;
const float MAX_X = 359.9999;
const float MIN_Y = 30;
const float MAX_Y = 150;

template <typename T>
T clamp(const T& v, const T& min_v, const T& max_v)
{
    return v < min_v ? min_v : (v > max_v ? max_v : v);
}

void saveAsBitmap(const Eigen::VectorXf& x, size_t rows, size_t cols, const char* fname)
{
    std::ofstream ofs(fname);
    ofs << "P2\n" << cols << " " << rows << "\n255\n";
    for(size_t rr = 0; rr < rows; rr++) {
        for(size_t cc = 0; cc < cols; cc++) {
            ofs << clamp<int>((int)x[rr * cols + cc], 0, 255) << " ";
        }
        ofs << "\n";
    }
}

inline
int wrap(int v, int min_v, int max_v)
{
    int width = max_v - min_v + 1;
    while(v < min_v) v += width;
    while(v > max_v) v -= width;
    return v;
}

inline
float sqr(float x)
{
    return x*x;
}

inline
float cube(float x)
{
    return x*x*x;
}

inline
float bspline(float x)
{
    if(x < -2) {
        return 0;
    } else if(x < -1) {
        return (cube(x+2)/6.0);
    } else if(x < 0) {
        return (-3*cube(x+2-1)+3*sqr(x+2-1)+3*(x+2-1)+1)/6;
    } else if(x < 1) {
        return ((3*cube(x+2-2) - 6*sqr(x+2-2) + 4)/6);
    } else if(x < 2) {
        return cube(1 - (x + 2 - 3))/6.0;
    } else {
        return 0;
    }
}


float kernel(float x, float width=4)
{
    // bspline width is 4
    width /= 4;
    return bspline(x / width ) / width;
}

inline
size_t grid_index(size_t width, size_t height, size_t grid_x, size_t grid_y)
{
    return grid_y * width + grid_x;
}


struct BSpline
{
    float grid_dx = 5;
    float grid_dy = 5;
    float grid_min_x = MIN_Y;
    float grid_max_x = MAX_X;
    float grid_min_y = MIN_Y;
    float grid_max_y = MAX_Y;

    size_t x_knots = (grid_max_x - grid_min_x) / grid_dx;
    size_t y_knots = (grid_max_y - grid_min_y) / grid_dy;
    size_t n_knots = x_knots * y_knots;

    SparseMatrix getWeights(const Eigen::MatrixXf& points) const
    {
        assert(points.cols() >= 2);
        std::vector<Triplet> coeffs;
        coeffs.reserve(points.size()*5);

        for(size_t pp = 0; pp < points.rows(); pp++) {
            const auto& pt = points.row(pp);
            float c_xbin = x_knots * (pt.x() - grid_min_x)/(grid_max_x - grid_min_x);
            float c_ybin = y_knots * (pt.y() - grid_min_y)/(grid_max_y - grid_min_y);

            // add weights to adjacent knots
            for(int ii = -2; ii <= 2; ii++) {
                for(int jj = -2; jj <= 2; jj++) {
                    int raw_xbin = (int)c_xbin + ii;
                    int wrapped_xbin = wrap(raw_xbin, 0, x_knots - 1);

                    int ybin = (int)c_ybin + jj;
                    if(ybin < 0 || ybin >= y_knots)
                        continue;

                    float w = kernel(c_xbin - raw_xbin)*kernel(c_ybin - ybin);
                    size_t grid_ind = grid_index(x_knots, y_knots, wrapped_xbin, ybin);
                    coeffs.push_back(Triplet(pp, grid_ind, w));
                }
            }
        }

        size_t num_points = points.rows();
        SparseMatrix Bmat(num_points, n_knots);
        Bmat.setFromTriplets(coeffs.begin(), coeffs.end());
        return Bmat;
    }

};

Eigen::VectorXf solve(const BSpline& spl, const Eigen::MatrixXf& points)
{
    auto Bmat = spl.getWeights(points);

//    auto tmp = (RowMajorMatrixXf::Identity(Bmat.rows(), Bmat.rows()) * Bmat);
//    for(size_t rr = 0; rr < Bmat.rows(); rr++) {
//        RowMajorMatrixXf row = tmp.row(rr);
//        Eigen::Map<RowMajorMatrixXf> rmap(row.data(), spl.y_knots, spl.x_knots);
//        std::cerr << "\n-------\n" << rmap << "\n-----\n" << std::endl;
//    }
//    std::cerr << (RowMajorMatrixXf::Identity(Bmat.rows(), Bmat.rows()) * Bmat) << std::endl;

    // make it dense :(
    auto tmp = (RowMajorMatrixXf::Identity(Bmat.rows(), Bmat.rows()) * Bmat);
    Eigen::ColPivHouseholderQR<Eigen::MatrixXf> qr(tmp);

    // Right now this doesn't seem to work ...
    // Bmat.makeCompressed();
    //Eigen::SparseQR<SparseMatrix, Eigen::NaturalOrdering<int>> qr;
    //Eigen::SparseQR<SparseMatrix, Eigen::COLAMDOrdering<int>> qr;
    //Eigen::SPQR<SparseMatrix> qr;
    //qr.compute(Bmat);
    //Eigen::SparseLU<SparseMatrix> qr(Bmat);
    return qr.solve(points.col(2));
};

Eigen::VectorXf interpolate(const BSpline& spl,
        const Eigen::VectorXf& knot_values, const Eigen::MatrixXf& points)
{
    auto bmat = spl.getWeights(points);
    return bmat * knot_values;
}

void drawPoints(const BSpline& spl, const Eigen::MatrixXf& points, const char* fname)
{
    size_t x_bins = spl.x_knots * 10;
    size_t y_bins = spl.y_knots * 10;
    Eigen::VectorXf raster(x_bins * y_bins);
    raster.fill(0);
    for(size_t rr = 0; rr < points.rows(); rr++) {
        float x = points(rr, 0);
        float y = points(rr, 1);
        float c_xbin = x_bins * (x - spl.grid_min_x) / (spl.grid_max_x - spl.grid_min_x);
        float c_ybin = y_bins * (y - spl.grid_min_y) / (spl.grid_max_y - spl.grid_min_y);
        raster[(int)c_xbin + (int)c_ybin * x_bins] = 255;
    }
    saveAsBitmap(raster, y_bins, x_bins, fname);
}

int main(int argc, char** argv)
{
    size_t num_points = 30;
    Eigen::MatrixXf points = Eigen::MatrixXf::Random(num_points, 3); // x, y, value
    for(size_t rr = 0; rr < points.rows(); rr++) {
        points(rr, 0) = MIN_X + std::abs(points(rr, 0)) * (MAX_X - MIN_X);
        points(rr, 1) = MIN_Y + std::abs(points(rr, 1)) * (MAX_Y - MIN_Y);
        points(rr, 2) = 1;
    }

    BSpline spl;
    drawPoints(spl, points, "orig.pgm");

    // Matrix maps from knots to known points
    // v = Bx
    //
    // x is the value of the knots, B is the weights of values at each knot s.t.
    // the values reflect the positions of the input points and v is the value
    // at the input points
    Eigen::VectorXf knots = solve(spl, points);

    // Use the known knots to solve for the actual values at each knot location
    Eigen::MatrixXf grid_points(spl.x_knots*spl.y_knots, 2);
    for(size_t yy = 0; yy < spl.y_knots; yy++) {
        for(size_t xx = 0; xx < spl.x_knots; xx++) {
            grid_points(yy * spl.x_knots + xx, 0) = spl.grid_min_x + xx * spl.grid_dx;
            grid_points(yy * spl.x_knots + xx, 1) = spl.grid_min_y + yy * spl.grid_dy;
        }
    }

    Eigen::VectorXf interpolated = interpolate(spl, knots, grid_points);
    //Eigen::VectorXf interpolated = interpolate(spl, knots, points);

    saveAsBitmap(255*interpolated, spl.y_knots, spl.x_knots, "smoothed.pgm");
    return 0;
}
