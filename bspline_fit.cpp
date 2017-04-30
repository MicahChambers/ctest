#include <Eigen/Sparse>
#include <vector>
#include <QtGui/QImage>

// declares a column-major sparse matrix type of double
typedef Eigen::SparseMatrix<float> SparseMatrix;
typedef Eigen::Triplet<float> Triplet;


void saveAsBitmap(const Eigen::VectorXf& x, size_t rows, size_t cols, const char* fname)
{
    Eigen::Array<unsigned char, Eigen::Dynamic, Eigen::Dynamic> bits = (x*255).cast<unsigned char>();
    QImage img(bits.data(), rows, cols, QImage::Format_Indexed8);
    img.setColorCount(256);

    for(int i = 0; i < 256; i++) {
        img.setColor(i,qRgb(i,i,i));
    }
    img.save(fname);
}

template <typename T>
T clamp(const T& v, const T& min_v, const T& max_v)
{
    return v < min_v ? min_v : (v > max_v ? max_v : v);
}

inline
int wrap(const int& v, const int& min_v, const int& max_v)
{
    return v < min_v ? max_v + 1 - v : (v > max_v ? v - max_v : v);
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
    float grid_dx = 0.1;
    float grid_dy = 0.2;
    float grid_min_x = 0;
    float grid_min_y = 0;
    float grid_max_x = 1;
    float grid_max_y = 1;

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
            float c_xbin = (pt.x() - grid_min_x)/(grid_max_x - grid_min_x);
            float c_ybin = (pt.y() - grid_min_y)/(grid_max_y - grid_min_y);

            // add weights to adjacent knots
            for(int ii = -2; ii <= 2; ii++) {
                for(int jj = -2; jj <= 2; jj++) {
                    int xbin = wrap(xbin + ii, 0, x_knots - 1);
                    int ybin = clamp<int>(ybin + jj, 0, y_knots - 1);
                    float w = kernel(pt.x() - (xbin + ii)) *
                              kernel(pt.y() - (ybin + jj));

                    size_t grid_ind = grid_index(x_knots, y_knots, xbin, ybin);
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

    Eigen::SimplicialCholesky<SparseMatrix> chol(Bmat);
    return chol.solve(points.col(2));
};

Eigen::VectorXf interpolate(const BSpline& spl,
        const Eigen::VectorXf& knot_values, const Eigen::MatrixXf& points)
{
    auto bmat = spl.getWeights(points);
    return bmat * knot_values;
}

int main(int argc, char** argv)
{
    size_t num_points = 100;
    auto points = Eigen::MatrixXf::Random(num_points, 3); // x, y, value
    BSpline spl;

    // Matrix maps from knots to known points
    // v = Bx
    //
    // x is the value of the knots, B is the weights of values at each knot s.t.
    // the values reflect the positions of the input points and v is the value
    // at the input points
    Eigen::VectorXf knots = solve(spl, points);

    // Use the known knots to solve for the actual values at each knot location
    Eigen::MatrixXf grid_points((spl.x_knots - 1)*(spl.y_knots - 1), 2);
    for(size_t yy = 0; yy < spl.y_knots; yy++) {
        for(size_t xx = 0; xx < spl.x_knots; xx++) {
            grid_points(yy * spl.x_knots + xx, 0) = xx + 0.5;
            grid_points(yy * spl.x_knots + xx, 1) = yy + 0.5;
        }
    }

    Eigen::VectorXf interpolated = interpolate(spl, knots, grid_points);

    saveAsBitmap(interpolated, spl.x_knots - 1, spl.y_knots - 1, argv[1]);
    return 0;
}
