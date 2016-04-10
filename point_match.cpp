#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <sstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

struct Point {
    double x;
    double y;
    string word;
};

size_t read_file(string filename, MatrixXd& points, vector<string>& words)
{
    vector<Point> output;
    Point tmp;
    string line;
    ifstream infile(filename);
    assert(infile.is_open());

    while(getline(infile, line)) {
        // read line in

        // read parts of line
        istringstream iss(line);
        iss >> tmp.x >> tmp.y >> tmp.word;

        // add point to list
        output.push_back(tmp);
    }


    points.resize(2, output.size());
    words.resize(output.size());
    for(unsigned int ii=0; ii<output.size(); ii++) {
        words[ii] = output[ii].word;
        points(0, ii) = output[ii].x;
        points(1, ii) = output[ii].y;
    }

    return output.size();
}

/**
 * @brief Computes the pseudo inverse with the SVD:
 *
 * A = USV*
 * A^-1 = VS^-1U*
 *
 * @param inmat
 * @param pinvtoler
 */
MatrixXd pseudo_inverse(MatrixXd& inmat, double pinvtoler=1.e-6)
{
    JacobiSVD<MatrixXd> svd(inmat, ComputeThinU | ComputeThinV);

    VectorXd s_inv = svd.singularValues();
    cerr << endl << s_inv << endl;
    for(unsigned int ii = 0; ii < s_inv.rows(); ii++) {
        if(s_inv[ii] > pinvtoler) {
            s_inv[ii] = 1.0/s_inv[ii];
        } else {
            s_inv[ii] = 0;
        }
    }
    return svd.matrixV()*s_inv.asDiagonal()*svd.matrixU().transpose();
}

/**
 * @brief Solves
 *
 * YW = AXW
 * A = YW (XW)^1
 *
 * where columns of R are points in the reference (fixed) point set, A is an
 * affine matrix (2x3, where column 3 is the shift), M is an augmented matrix
 * with 1' in the bottom row and the top two rows containing coordinates in the
 * moving dataset -- one point per column and W being a correspondance matrix
 * such that correponding points in the R and M matrixes 1 is
 *
 * @param ref
 * @param moving
 * @param weights
 *
 * @return
 */
void solve(const MatrixXd& ref_y, const MatrixXd& mov_x,
        const VectorXd& weights, Matrix<double, 2, 3>& affine)
{
    // Create augmented moving matrix, with lowest row of 1s
    MatrixXd aug_mov_x = MatrixXd::Ones(mov_x.rows() + 1, mov_x.cols());
    aug_mov_x.topRows(2) = mov_x;

    MatrixXd tmp = aug_mov_x*weights.asDiagonal();
    MatrixXd pinv = pseudo_inverse(tmp);
    affine = ref_y*weights.asDiagonal()*pinv;

    // enforce rigid + scaling ???

}

int main(int argc, char** argv)
{
    if(argc != 3) {
        cerr << "Need to provide two input files!" << endl;
        return -1;
    }

    vector<string> ref_words;
    MatrixXd ref_points;
    read_file(argv[1], ref_points, ref_words);

    vector<string> move_words;
    MatrixXd move_points;
    read_file(argv[2], move_points, move_words);

    map<string, int> word_counts;
    for(auto& word: ref_words) {
        auto ret = word_counts.insert(pair<string,int>(word,0));
        if(ret.second) {
            // element not inserted, so it exists, already existed so just
            // increment the old count
            ret.first->second++;
        }
    }

    for(auto& v: word_counts) {
        cerr << v.first << ":" << v.second << endl;
    }

    // Reorder points / duplicate / remove points that don't match. Also
    // initialize weights to down-weight repeated matches
    VectorXd weights = VectorXd::Ones(ref_points.cols());
    MatrixXd matches(move_points.cols(), ref_points.cols());
    for(unsigned int cc = 0; cc < ref_words.size(); cc++) {
        for(unsigned int rr = 0; rr< move_words.size(); rr++) {
            cerr << ref_words[cc] << " vs " << move_words[cc] << endl;
            if(ref_words[cc] == move_words[rr]) {
                matches(rr, cc) = 1;
                //weights[cc] /= 2.;
            } else {
                matches(rr, cc) = 0;
            }
        }
    }
    MatrixXd move_points_match = move_points*matches;
    MatrixXd err(ref_points.rows(), ref_points.cols());

    cerr << "Ref" << endl << ref_points << endl;
    cerr << "Moving" << endl << move_points_match << endl;
    cerr << "Matching" << endl << matches << endl;
    cerr << "Weights" << endl << weights << endl;

    Matrix<double, 2, 3>  affine(2, 3);
    affine << 1, 0, 0,
              0, 1, 0;

    for(int ii = 0; ii < 10; ii++) {
        MatrixXd adjusted = affine.leftCols(2)*move_points +
            affine.col(2)*MatrixXd::Ones(1, move_points.cols());
        cerr << "Adjusted " << endl << adjusted << endl;

        // Re-weight based on norms
        err = ref_points - adjusted;
        for(size_t rr = 0; rr < weights.rows(); rr++) {
            weights[rr] = 1./max(0.0001, err.col(rr).norm());
        }
        cerr << "Weights" << endl << weights << endl;

        cerr << "Affine" << endl << affine << endl;
        solve(ref_points, move_points_match, weights, affine);

    }
}
